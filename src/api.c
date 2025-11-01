#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../include/api.h"

#define COINGECKO_API_BASE "https://api.coingecko.com/api/v3/simple/price"

/**
 * @brief Write callback for libcurl
 */
struct write_result {
    char *data;
    size_t size;
};

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    struct write_result *result = (struct write_result *)userp;
    
    char *ptr = realloc(result->data, result->size + total_size + 1);
    if (!ptr) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 0;
    }
    
    result->data = ptr;
    memcpy(&(result->data[result->size]), contents, total_size);
    result->size += total_size;
    result->data[result->size] = 0;
    
    return total_size;
}

char *get_api_url(const char *symbol) {
    if (!symbol) {
        return NULL;
    }
    
    size_t url_len = strlen(COINGECKO_API_BASE) + strlen(symbol) + 50;
    char *url = malloc(url_len);
    if (!url) {
        return NULL;
    }
    
    snprintf(url, url_len, "%s?ids=%s&vs_currencies=usd&include_24hr_change=true&include_market_cap=true&include_24hr_vol=true&include_last_updated_at=true", 
             COINGECKO_API_BASE, symbol);
    
    return url;
}

int fetch_crypto_data(const char *symbol, char *buffer, size_t buffer_size) {
    if (!symbol || !buffer || buffer_size == 0) {
        return -1;
    }
    
    CURL *curl;
    CURLcode res;
    struct write_result result;
    
    result.data = malloc(1);
    result.size = 0;
    
    if (!result.data) {
        return -1;
    }
    
    curl = curl_easy_init();
    if (!curl) {
        free(result.data);
        return -1;
    }
    
    char *url = get_api_url(symbol);
    if (!url) {
        curl_easy_cleanup(curl);
        free(result.data);
        return -1;
    }
    
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&result);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "crypto-cli/1.0");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    
    res = curl_easy_perform(curl);
    
    long response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    
    curl_easy_cleanup(curl);
    free(url);
    
    if (res != CURLE_OK) {
        free(result.data);
        return -1;
    }
    
    if (response_code != 200) {
        free(result.data);
        return -1;
    }
    
    if (result.size >= buffer_size) {
        free(result.data);
        return -1;
    }
    
    strncpy(buffer, result.data, buffer_size - 1);
    buffer[buffer_size - 1] = '\0';
    free(result.data);
    
    return 0;
}

