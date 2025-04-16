#ifndef LAMP_H
#define LAMP_H

#include "driver/gpio.h" // Ensure the include path is correctly set in your build configuration
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN GPIO_NUM_2       /
#define BUTTON_PIN GPIO_NUM_4    
#define BLINK_COUNT 5            
#define DELAY_MS 200             

void setupLamp();
void blinkLamp(int blinkCount);


#endif

