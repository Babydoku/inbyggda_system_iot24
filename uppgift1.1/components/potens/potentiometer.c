#include "potentiometer.h"
#include "driver/adc.h"
#include "esp_log.h"

#define TAG "POTENTIOMETER"


void Potentiometer_init(Potentiometer *pot, int channel_index) {
    pot->channel_index = channel_index; 
    pot->value = 0;
    pot->threshold = 0;
    pot->abovethreshold = false;
    pot->risingEdge = false;  
    pot->callback = NULL;

    
    adc1_config_width(ADC_WIDTH_BIT_12); 
    adc1_config_channel_atten(pot->channel_index, ADC_ATTEN_DB_11); 
}


void Potentiometer_update(Potentiometer *pot) {
    int newValue = adc1_get_raw(pot->channel_index); 
    pot->value = newValue; 
    



    if (pot->callback != NULL) {
     // if (pot->risingEdge) {
      //printf("%d\n", pot->abovethreshold);
        if (pot->value >= pot->threshold && pot->abovethreshold) {
            if (pot->risingEdge) {
                pot->callback(pot->channel_index, pot->value);
            }
            pot->abovethreshold = false; 
        }
        //printf("rising edge är false\n");
        //printf("%d\n", pot->abovethreshold);
        if (pot->value < pot->threshold && !pot->abovethreshold) {
            if (!pot->risingEdge) {
                pot->callback(pot->channel_index, pot->value);
            }
            pot->abovethreshold = true; 
        }
    }
}


int Potentiometer_getValue(Potentiometer *pot) {
    return pot->value;
}


void Potentiometer_setOnThreshold(Potentiometer *pot, int threshold, bool risingEdge, OnThresholdCallback callback) {
    pot->threshold = threshold;
    pot->risingEdge = risingEdge;
    pot->callback = callback;
    
}


