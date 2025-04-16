#include "lampa.h"
#include "driver/gpio.h"

void app_main() {
    setupLamp();

    while (1) {
        if (gpio_get_level(BUTTON_PIN) == 0) { 
            blinkLamp(BLINK_COUNT);
            vTaskDelay(pdMS_TO_TICKS(500)); 
        }
    }
}
