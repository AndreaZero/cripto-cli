#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>  // For strcasecmp (POSIX)
#include <ctype.h>
#include <cjson/cJSON.h>
#include "../include/parser.h"

// Mapping of common symbols to CoinGecko IDs
static const struct {
    const char *symbol;
    const char *coingecko_id;
} symbol_map[] = {
    {"BTC", "bitcoin"},
    {"ETH", "ethereum"},
    {"BNB", "binancecoin"},
    {"SOL", "solana"},
    {"ADA", "cardano"},
    {"XRP", "ripple"},
    {"DOT", "polkadot"},
    {"DOGE", "dogecoin"},
    {"AVAX", "avalanche-2"},
    {"MATIC", "matic-network"},
    {"LINK", "chainlink"},
    {"UNI", "uniswap"},
    {"LTC", "litecoin"},
    {"ATOM", "cosmos"},
    {"ETC", "ethereum-classic"},
    {"XLM", "stellar"},
    {"ALGO", "algorand"},
    {"FIL", "filecoin"},
    {"TRX", "tron"},
    {"VET", "vechain"},
    {"ICP", "internet-computer"},
    {"THETA", "theta-token"},
    {"EOS", "eos"},
    {"AAVE", "aave"},
    {"MKR", "maker"},
    {"SUSHI", "sushi"},
    {NULL, NULL}
};

char *symbol_to_id(const char *symbol) {
    if (!symbol) {
        return NULL;
    }
    
    // Check symbol map first
    for (int i = 0; symbol_map[i].symbol != NULL; i++) {
        if (strcasecmp(symbol, symbol_map[i].symbol) == 0) {
            size_t len = strlen(symbol_map[i].coingecko_id);
            char *id = malloc(len + 1);
            if (id) {
                strncpy(id, symbol_map[i].coingecko_id, len);
                id[len] = '\0';
            }
            return id;
        }
    }
    
    // Convert to lowercase for direct CoinGecko ID match
    size_t len = strlen(symbol);
    char *id = malloc(len + 1);
    if (!id) {
        return NULL;
    }
    
    for (size_t i = 0; i < len; i++) {
        id[i] = tolower((unsigned char)symbol[i]);
    }
    id[len] = '\0';
    
    return id;
}

crypto_data_t parse_crypto_json(const char *json_string) {
    crypto_data_t data = {0};
    data.success = 0;
    
    if (!json_string) {
        return data;
    }
    
    cJSON *json = cJSON_Parse(json_string);
    if (!json) {
        return data;
    }
    
    // Get first (and typically only) key in the response
    cJSON *item = json->child;
    if (!item) {
        cJSON_Delete(json);
        return data;
    }
    
    // Extract coin ID
    if (item->string) {
        size_t id_len = strlen(item->string);
        data.id = malloc(id_len + 1);
        if (data.id) {
            strncpy(data.id, item->string, id_len);
            data.id[id_len] = '\0';
        }
    }
    
    // Parse USD data
    cJSON *usd = cJSON_GetObjectItem(item, "usd");
    if (cJSON_IsNumber(usd)) {
        data.current_price = usd->valuedouble;
    }
    
    // Parse price change 24h
    cJSON *change_24h = cJSON_GetObjectItem(item, "usd_24h_change");
    if (cJSON_IsNumber(change_24h)) {
        data.price_change_24h = change_24h->valuedouble;
        data.price_change_percentage_24h = change_24h->valuedouble;
    }
    
    // Parse market cap
    cJSON *market_cap = cJSON_GetObjectItem(item, "usd_market_cap");
    if (cJSON_IsNumber(market_cap)) {
        data.market_cap = market_cap->valuedouble;
    }
    
    // Parse 24h volume
    cJSON *volume_24h = cJSON_GetObjectItem(item, "usd_24h_vol");
    if (cJSON_IsNumber(volume_24h)) {
        data.volume_24h = volume_24h->valuedouble;
    }
    
    // Parse last updated timestamp
    cJSON *last_updated = cJSON_GetObjectItem(item, "last_updated_at");
    if (cJSON_IsNumber(last_updated)) {
        data.last_updated_at = (long)last_updated->valuedouble;
    }
    
    // Extract symbol and name from ID
    if (data.id && strlen(data.id) > 0) {
        size_t id_len = strlen(data.id);
        
        // Create symbol (uppercase version, but handle special cases)
        // Check if we have a mapping for this ID
        const char *mapped_symbol = NULL;
        for (int i = 0; symbol_map[i].symbol != NULL; i++) {
            if (strcmp(data.id, symbol_map[i].coingecko_id) == 0) {
                mapped_symbol = symbol_map[i].symbol;
                break;
            }
        }
        
        if (mapped_symbol) {
            size_t sym_len = strlen(mapped_symbol);
            data.symbol = malloc(sym_len + 1);
            if (data.symbol) {
                strncpy(data.symbol, mapped_symbol, sym_len);
                data.symbol[sym_len] = '\0';
            }
        } else {
            // Convert to uppercase
            data.symbol = malloc(id_len + 1);
            if (data.symbol) {
                for (size_t i = 0; i < id_len; i++) {
                    data.symbol[i] = toupper((unsigned char)data.id[i]);
                }
                data.symbol[id_len] = '\0';
            }
        }
        
        // Create name from ID (capitalize first letter and replace hyphens with spaces)
        data.name = malloc(id_len * 2 + 1); // Extra space for potential replacements
        if (data.name) {
            size_t j = 0;
            int capitalize_next = 1;
            for (size_t i = 0; i < id_len; i++) {
                if (data.id[i] == '-' || data.id[i] == '_') {
                    data.name[j++] = ' ';
                    capitalize_next = 1;
                } else if (capitalize_next) {
                    data.name[j++] = toupper((unsigned char)data.id[i]);
                    capitalize_next = 0;
                } else {
                    data.name[j++] = data.id[i];
                }
            }
            data.name[j] = '\0';
        }
    }
    
    // High/Low not available in simple/price endpoint
    data.high_24h = 0.0;
    data.low_24h = 0.0;
    
    data.success = 1;
    cJSON_Delete(json);
    
    return data;
}

void free_crypto_data(crypto_data_t *data) {
    if (!data) {
        return;
    }
    
    if (data->id) {
        free(data->id);
        data->id = NULL;
    }
    
    if (data->symbol) {
        free(data->symbol);
        data->symbol = NULL;
    }
    
    if (data->name) {
        free(data->name);
        data->name = NULL;
    }
}
