#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../include/api.h"
#include "../include/parser.h"
#include "../include/display.h"

#define BUFFER_SIZE 4096
#define VERSION "1.0.0"

static void print_usage(const char *program_name) {
    printf("Usage: %s [SYMBOL] [COMMAND]\n\n", program_name);
    printf("Commands:\n");
    printf("  [SYMBOL]              Display full cryptocurrency information\n");
    printf("  [SYMBOL] price        Display only the current price\n");
    printf("\n");
    printf("Examples:\n");
    printf("  %s bitcoin            Show full info for Bitcoin\n", program_name);
    printf("  %s btc price          Show only the price for Bitcoin\n", program_name);
    printf("  %s ethereum           Show full info for Ethereum\n", program_name);
    printf("\n");
    printf("Version: %s\n", VERSION);
}

static void print_version(void) {
    printf("crypto-cli version %s\n", VERSION);
}

int main(int argc, char *argv[]) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    int show_price_only = 0;
    char *symbol = NULL;
    
    // Parse arguments
    if (argc < 2) {
        print_usage(argv[0]);
        curl_global_cleanup();
        return 1;
    }
    
    // Check for version flag
    if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) {
        print_version();
        curl_global_cleanup();
        return 0;
    }
    
    // Check for help flag
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        print_usage(argv[0]);
        curl_global_cleanup();
        return 0;
    }
    
    symbol = argv[1];
    
    // Check if second argument is "price"
    if (argc >= 3 && strcmp(argv[2], "price") == 0) {
        show_price_only = 1;
    } else if (argc > 3) {
        fprintf(stderr, "Error: Too many arguments\n");
        print_usage(argv[0]);
        curl_global_cleanup();
        return 1;
    }
    
    // Convert symbol to CoinGecko ID format
    char *coin_id = symbol_to_id(symbol);
    if (!coin_id) {
        display_error("Invalid symbol");
        curl_global_cleanup();
        return 1;
    }
    
    // Fetch data from API
    char buffer[BUFFER_SIZE] = {0};
    int result = fetch_crypto_data(coin_id, buffer, BUFFER_SIZE);
    
    if (result != 0) {
        display_error("Failed to fetch data from API. Please check your internet connection and try again.");
        free(coin_id);
        curl_global_cleanup();
        return 1;
    }
    
    // Check if response is empty or error
    if (strlen(buffer) == 0 || strstr(buffer, "error") != NULL) {
        display_error("Cryptocurrency not found or invalid symbol");
        free(coin_id);
        curl_global_cleanup();
        return 1;
    }
    
    // Parse JSON response
    crypto_data_t crypto_data = parse_crypto_json(buffer);
    
    if (!crypto_data.success) {
        display_error("Failed to parse API response");
        free(coin_id);
        curl_global_cleanup();
        return 1;
    }
    
    // Display data
    if (show_price_only) {
        display_price_only(&crypto_data);
    } else {
        display_full_info(&crypto_data);
    }
    
    // Cleanup
    free_crypto_data(&crypto_data);
    free(coin_id);
    curl_global_cleanup();
    
    return 0;
}

