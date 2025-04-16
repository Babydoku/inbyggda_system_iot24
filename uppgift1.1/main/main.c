/*#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "ledd.h"
#include "driver/ledc.h"
#include "esp_log.h"

#define LED_PIN 21
#define LED_CHANNEL LEDC_CHANNEL_0
#define LED_TIMER LEDC_TIMER_0

void app_main(void) {
     led_t led;
    
   led_init(LED_PIN, &led);
     
     led_setLed( 5000, &led);
   led_setLed( 5000, &led);
   led_sin (200, &led);
     led_setLed( 5000, &led);
     led_sin (200, &led);
  led_setLed( 200, &led);
   //led_sin (200, &led);
    
   
    while (1) {
        led_update(&led); 
        vTaskDelay(pdMS_TO_TICKS(30)); 
    }
}*/

/*#include <stdio.h>
#include "configuration.h"

// Definiera färger
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[0;31m"
#define COLOR_GREEN   "\033[0;32m"
#define COLOR_YELLOW  "\033[0;33m"
#define COLOR_BLUE    "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CYAN    "\033[0;36m"
#define COLOR_WHITE   "\033[0;37m"


void app_main() {
    Configuration_init();

    printf(COLOR_RED "Device Name: %s\n" COLOR_RESET, getDeviceName());
    printf(COLOR_RED "Serial Number: %s\n" COLOR_RESET, getSerialNumber());

    setDeviceName("ibrasfel");
    setSerialNumber("3256694070");

    printf(COLOR_BLUE "Updated Device Name: %s\n" COLOR_RESET, getDeviceName());
    printf(COLOR_BLUE "Updated Serial Number: %s\n" COLOR_RESET, getSerialNumber());

    
    setDeviceName("ibrasnummer");
    setSerialNumber("0704966523");

    printf("Final Device Name: %s\n", getDeviceName());
    printf("Final Serial Number: %s\n", getSerialNumber());
}*/





/*#include <stdio.h>
#include "led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "button.h"  // Add this line to include the button header file

#define LED_PIN 5 


void set_led(bool state, led_config_t *led);



void app_main() {
    led_config_t led = {
        .pin = LED_PIN,
        .is_active_low = 0,  
        .is_blinking = false, 
        .milliseconds_on = 0,
        .milliseconds_off = 0
    };

    led_init(&led);

    //set_led(false, &led);
    led_set(false, &led);
    led_blink(1000, 200, &led);
    
    while (1) {
        led_update(&led); 
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
*/

/*

#include "potentiometer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"



void onThresholdReached(int channel_index, int value) {
    printf("Threshold reached over  Value: %d\n", value);
}

void app_main() {
    Potentiometer pot;
    Potentiometer_init(&pot, ADC1_CHANNEL_1); 

    
    Potentiometer_setOnThreshold(&pot, 2000, false, onThresholdReached);

    while (1) {
        Potentiometer_update(&pot); 
        //int value = Potentiometer_getValue(&pot); 
        //printf("Current value: %d\n", value);

        vTaskDelay(pdMS_TO_TICKS(100)); 
    }
}*/


/*#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED_PIN 5  // GPIO5

void app_main() {
    // Initiera GPIO5
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(LED_PIN, 1);  // Tänd LED
        vTaskDelay(pdMS_TO_TICKS(500));  // Vänta 500 ms

        gpio_set_level(LED_PIN, 0);  // Släck LED
        vTaskDelay(pdMS_TO_TICKS(500));  // Vänta 500 ms
    }
}*/

/*#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"  // För esp_rom_delay_us
#include "esp_timer.h"   // För esp_timer_get_time

#define TRIG_PIN GPIO_NUM_15  // TRIG pin
#define ECHO_PIN GPIO_NUM_21   // ECHO pin, testa GPIO 21 eller 22 om 18 inte fungerar
#define LAMP_PIN GPIO_NUM_9 // Lampan kopplas till GPIO 23

void app_main() {
    // Konfigurera TRIG som utgång
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << TRIG_PIN),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };
    gpio_config(&io_conf);

    // Konfigurera ECHO som ingång
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << ECHO_PIN);
    gpio_config(&io_conf);

    // Konfigurera LAMP_PIN som utgång
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << LAMP_PIN);
    gpio_config(&io_conf);

    while (1) {
        // Skicka en 10 µs puls till TRIG
        gpio_set_level(TRIG_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(2));  // Vänta 2 ms

        gpio_set_level(TRIG_PIN, 1);
        esp_rom_delay_us(20);  // 20 µs puls
        gpio_set_level(TRIG_PIN, 0);

        // Vänta på att eko ska starta
        int64_t timeout = esp_timer_get_time() + 1000000;  // 1 sekund timeout
        int64_t start_time = 0;
        while (gpio_get_level(ECHO_PIN) == 0) {
            if (esp_timer_get_time() > timeout) {
                printf("Timeout: Väntar på eko start!\n");
                gpio_set_level(LAMP_PIN, 0);  // Släck lampan vid timeout
                vTaskDelay(pdMS_TO_TICKS(1000));
                continue;
            }
            start_time = esp_timer_get_time();
        }

        // Vänta på att eko ska sluta
        timeout = esp_timer_get_time() + 1000000;
        int64_t end_time = 0;
        while (gpio_get_level(ECHO_PIN) == 1) {
            if (esp_timer_get_time() > timeout) {
                printf("Timeout: Väntar på eko slut!\n");
                gpio_set_level(LAMP_PIN, 0);
                vTaskDelay(pdMS_TO_TICKS(1000));
                continue;
            }
            end_time = esp_timer_get_time();
        }

        // Beräkna avståndet
        int64_t duration = end_time - start_time;  // Tid i mikrosekunder
        float distance = (duration / 2.0) / 29.1;  // Avstånd i cm

        printf("Avstånd: %.2f cm\n", distance);

        // Tänd lampan om avståndet är mindre än 10 cm
        if (distance < 10.0) {
            gpio_set_level(LAMP_PIN, 1);  // Tänd lampan
        } else {
            gpio_set_level(LAMP_PIN, 0);  // Släck lampan
        }

        vTaskDelay(pdMS_TO_TICKS(500));  // Vänta 0.5 sekund innan nästa mätning
    }
}*/

#include <stdio.h>
#include "ultrasonic.h"
#include "led.h"
#include "Buzzer.h"
#include "button.h"
#include "freertos/FreeRTOS.h"if
#include "freertos/task.h"
#include "esp_sleep.h"

#define LED_PIN_RED 6
#define LED_PIN_YELLOW 7
#define BUZZER_PIN 19 
#define BUTTON_PIN GPIO_NUM_5
#define TRIG_PIN GPIO_NUM_4
#define ECHO_PIN GPIO_NUM_23

void app_main(void) {
    led_config_t led_RED = { .pin = LED_PIN_RED, .is_active_low = false };
    led_config_t led_YELLOW = { .pin = LED_PIN_YELLOW, .is_active_low = false };
    buzzer_config_t buzzer = { .pin = BUZZER_PIN, .is_active_low = false };
    button_config_t button = { .pin = BUTTON_PIN, .pullup_enabled = true, .system_active = false };
    ultrasonic_config_t ultrasonic = { .trig_pin = TRIG_PIN, .echo_pin = ECHO_PIN };


    led_init(&led_RED);
    led_init(&led_YELLOW);
    buzzer_init(&buzzer);
    ultrasonic_init(&ultrasonic);
    button_init(&button);

    printf("Tryck på knappen för att aktivera.\n");

    while (!button_is_active(&button)) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    while (1) {
        if (!button_is_active(&button)) {
            button_handle_sleep(&button);
            
        }

        float distance = ultrasonic_measure();
        printf("Avstånd: %.2f cm\n", distance);

        led_set(distance <= 20.0, &led_RED);
        led_set(distance <= 40.0, &led_YELLOW);
        buzzer_set(distance <= 20.0, &buzzer);

        led_update(&led_RED);
        led_update(&led_YELLOW);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
