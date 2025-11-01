#include <stdio.h>
#include <time.h>
#include "../include/display.h"

void display_full_info(const crypto_data_t *data) {
    if (!data || !data->success) {
        display_error("Failed to retrieve cryptocurrency data");
        return;
    }
    
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  %s (%s)\n", data->name ? data->name : "N/A", 
           data->symbol ? data->symbol : "N/A");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    printf("  Current Price:      $%.2f\n", data->current_price);
    
    if (data->price_change_24h != 0.0) {
        const char *sign = data->price_change_24h >= 0 ? "+" : "";
        const char *color = data->price_change_24h >= 0 ? "↑" : "↓";
        printf("  24h Change:         %s$%.2f (%s%.2f%%)\n", 
               sign, data->price_change_24h, 
               color, data->price_change_percentage_24h);
    }
    
    if (data->market_cap > 0) {
        if (data->market_cap >= 1e12) {
            printf("  Market Cap:         $%.2fT\n", data->market_cap / 1e12);
        } else if (data->market_cap >= 1e9) {
            printf("  Market Cap:         $%.2fB\n", data->market_cap / 1e9);
        } else if (data->market_cap >= 1e6) {
            printf("  Market Cap:         $%.2fM\n", data->market_cap / 1e6);
        } else {
            printf("  Market Cap:         $%.2f\n", data->market_cap);
        }
    }
    
    if (data->volume_24h > 0) {
        if (data->volume_24h >= 1e9) {
            printf("  24h Volume:         $%.2fB\n", data->volume_24h / 1e9);
        } else if (data->volume_24h >= 1e6) {
            printf("  24h Volume:         $%.2fM\n", data->volume_24h / 1e6);
        } else {
            printf("  24h Volume:         $%.2f\n", data->volume_24h);
        }
    }
    
    // Market Cap to Volume ratio (indicator of activity)
    if (data->market_cap > 0 && data->volume_24h > 0) {
        double mcv_ratio = data->market_cap / data->volume_24h;
        printf("  Market Cap / Volume: %.2f\n", mcv_ratio);
    }
    
    // Last updated timestamp
    if (data->last_updated_at > 0) {
        time_t timestamp = (time_t)data->last_updated_at;
        struct tm *timeinfo = localtime(&timestamp);
        char time_str[64];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
        printf("  Last Updated:        %s\n", time_str);
    }
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}

void display_price_only(const crypto_data_t *data) {
    if (!data || !data->success) {
        display_error("Failed to retrieve cryptocurrency data");
        return;
    }
    
    printf("$%.2f\n", data->current_price);
}

void display_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
}

