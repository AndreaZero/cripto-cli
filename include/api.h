#ifndef API_H
#define API_H

/**
 * @file api.h
 * @brief HTTP API client for CoinGecko API
 */

/**
 * @brief Fetch cryptocurrency data from CoinGecko API
 * 
 * @param symbol Cryptocurrency symbol (e.g., "bitcoin", "ethereum")
 * @param buffer Output buffer to store JSON response
 * @param buffer_size Size of the output buffer
 * @return int 0 on success, -1 on error
 */
int fetch_crypto_data(const char *symbol, char *buffer, size_t buffer_size);

/**
 * @brief Get CoinGecko API URL for a cryptocurrency symbol
 * 
 * @param symbol Cryptocurrency symbol (e.g., "bitcoin")
 * @return char* Allocated string with URL (must be freed by caller)
 */
char *get_api_url(const char *symbol);

#endif /* API_H */

