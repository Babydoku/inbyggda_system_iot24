#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <stdbool.h>


typedef void (*OnThresholdCallback)(int channel_index, int value);

typedef struct {
    int channel_index;        
    int value;                 
    int threshold;              
    bool risingEdge;  
    bool abovethreshold;          
    OnThresholdCallback callback; 
} Potentiometer;


void Potentiometer_init(Potentiometer *pot, int channel_index);
void Potentiometer_update(Potentiometer *pot);
int Potentiometer_getValue(Potentiometer *pot);
void Potentiometer_setOnThreshold(Potentiometer *pot, int threshold, bool risingEdge, OnThresholdCallback callback);

#endif 