#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"





#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (5) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (4096) // Set duty to 50%. (2 ** 13) * 50% = 4096
#define LEDC_FREQUENCY          (4000) // Frequency in Hertz. Set frequency at 4 kHz
#define GPIO_INPUT_IO_0         0


void app_main(void)
{
    gpio_config_t buttengpio;
    buttengpio.mode =  GPIO_MODE_INPUT;
    buttengpio.pin_bit_mask = 1 << GPIO_NUM_18;
    buttengpio.pull_up_en = GPIO_PULLUP_ENABLE;
    buttengpio.pull_down_en = GPIO_PULLDOWN_DISABLE;
    buttengpio.intr_type = GPIO_INTR_DISABLE;
     
     
     esp_err_t  error = gpio_config(&buttengpio);

     ledc_timer_config_t ledtimerconfig;
        ledtimerconfig.clk_cfg = LEDC_AUTO_CLK;
        ledtimerconfig.duty_resolution =  false;
        ledtimerconfig.freq_hz = 1000;
        ledtimerconfig.speed_mode = LEDC_LOW_SPEED_MODE;
        ledtimerconfig.timer_num = LEDC_TIMER_0;
        ledc_timer_config(&ledtimerconfig);

        ledc_channel_config_t ledchannelconfig;
        ledchannelconfig.channel = LEDC_CHANNEL_0;
        ledchannelconfig.duty = 0;
        ledchannelconfig.flags.output_invert = 0;
        ledchannelconfig.gpio_num = LEDC_OUTPUT_IO;



ledc_channel_config(&ledchannelconfig);


    int level=gpio_get_level(GPIO_NUM_18);
    TickType_t startTick = xTaskGetTickCount();
    int latch = 0;

    int duty = 0;
    int prevduty = 0;

    ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0, 0,0);
    
    while(1){
   vTaskDelay(pdMS_TO_TICKS(25));
   level = gpio_get_level(GPIO_NUM_18);
   if(level==1&& latch == 0){
      TickType_t tickdiffrense = xTaskGetTickCount() - startTick;
      if(tickdiffrense>= pdMS_TO_TICKS(38))
      {
        startTick = xTaskGetTickCount();
        latch = 1;
           printf("level: %d\n", level);

         }
    }
        else if(level==0 && latch == 1){
            TickType_t tickdiffrense = xTaskGetTickCount() - startTick;
            if(tickdiffrense>= pdMS_TO_TICKS(38))
            {
                startTick = xTaskGetTickCount();
                latch = 0;
                   printf("level: %d\n", level);
            }
        
                if(prevduty != duty)
                {
                    prevduty = duty;

                }

        }
            
    }   
        
    
    

