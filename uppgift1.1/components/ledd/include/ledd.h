#pragma once
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"

typedef struct {
    ledc_channel_t channel;
    ledc_timer_t timer;
    int pin;
    int value;
    int period;
    TickType_t startTick;
    bool sinActive;
} led_t;

void led_init(int pin, led_t *led);
void led_setLed(int value, led_t *led);
void led_sin(int period, led_t *led);
void led_update(led_t *led);

