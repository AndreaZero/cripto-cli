#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * @file display.h
 * @brief Display formatting for cryptocurrency data
 */

#include "parser.h"

/**
 * @brief Display full cryptocurrency information
 * 
 * @param data Cryptocurrency data structure
 */
void display_full_info(const crypto_data_t *data);

/**
 * @brief Display only the price
 * 
 * @param data Cryptocurrency data structure
 */
void display_price_only(const crypto_data_t *data);

/**
 * @brief Display error message
 * 
 * @param message Error message to display
 */
void display_error(const char *message);

#endif /* DISPLAY_H */

