#ifndef PARSER_H
#define PARSER_H

/**
 * @file parser.h
 * @brief JSON parser for cryptocurrency data
 */

/**
 * @brief Cryptocurrency data structure
 */
typedef struct {
    char *id;
    char *symbol;
    char *name;
    double current_price;
    double price_change_24h;
    double price_change_percentage_24h;
    double market_cap;
    double volume_24h;
    double high_24h;
    double low_24h;
    long last_updated_at;
    int success;
} crypto_data_t;

/**
 * @brief Parse JSON response from CoinGecko API
 * 
 * @param json_string JSON response string
 * @return crypto_data_t Parsed cryptocurrency data structure
 */
crypto_data_t parse_crypto_json(const char *json_string);

/**
 * @brief Free memory allocated for crypto_data_t structure
 * 
 * @param data Pointer to crypto_data_t structure to free
 */
void free_crypto_data(crypto_data_t *data);

/**
 * @brief Convert symbol to CoinGecko ID (lowercase)
 * 
 * @param symbol Cryptocurrency symbol (e.g., "BTC")
 * @return char* Allocated lowercase string (must be freed by caller)
 */
char *symbol_to_id(const char *symbol);

#endif /* PARSER_H */

