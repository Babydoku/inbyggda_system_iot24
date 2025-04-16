#include "lampa.h"
#include "esp_log.h"


void setupLamp() {
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); 

    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY); 
}

void blinkLamp(int blinkCount) {
    for (int i = 0; i < blinkCount; i++) {
        gpio_set_level(LED_PIN, 1); // Tänd LED
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
        gpio_set_level(LED_PIN, 0); // Släck LED
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}
