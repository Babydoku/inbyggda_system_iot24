#include "ledd.h"
#include "driver/ledc.h"
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <inttypes.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void led_init(int pin, led_t *led) {
    led->pin = pin;
    led->channel = LEDC_CHANNEL_0;  
    led->timer = LEDC_TIMER_0;   
    led->value = -1;            
    led->period = 0;
    led->startTick = 0;

    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = led->timer,
        .duty_resolution = LEDC_TIMER_12_BIT,
        .freq_hz = 5000,
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .gpio_num = led->pin,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = led->channel,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = led->timer,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel);
}

void led_setLed(int value, led_t *led) {
    led->sinActive = false;  
    led->value = value;    

    ledc_set_duty(LEDC_LOW_SPEED_MODE, led->channel, value);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, led->channel);
}



void led_sin(int period, led_t *led) {
    led->value = -1;        
    led->period = period;
    led->sinActive = true;
    led->startTick = xTaskGetTickCount();
}

void led_update(led_t *led) {
    if (led->value != -1) { 
        ledc_set_duty(LEDC_LOW_SPEED_MODE, led->channel, led->value);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, led->channel);
    } else if (led->sinActive) { 
        TickType_t elapsed = xTaskGetTickCount() - led->startTick;

        double phase = ((double)(elapsed % pdMS_TO_TICKS(led->period))) / pdMS_TO_TICKS(led->period);
        double angle = phase * 2.0 * M_PI;
        double sineValue = sin(angle);

        
        uint32_t duty = (uint32_t)round(((sineValue + 1.0) / 2.0) * 4095.0);
        
        //printf("Duty Cycle: %d\n", duty);

        ledc_set_duty(LEDC_LOW_SPEED_MODE, led->channel, duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, led->channel);
    }
}
