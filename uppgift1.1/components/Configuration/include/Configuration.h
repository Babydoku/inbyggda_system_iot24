#pragma once
#include <stddef.h>


// Ladda alla parametrar från NVS
void Configuration_init();

// Returnera device name parameter från arbetsminne
char* getDeviceName();

// Returnera serial number parameter från arbetsminne
char* getSerialNumber();

// Kopiera in nytt device name till arbetsminne och spara på nvs
void setDeviceName(char* new_name);

//Kopiera in nytt serial number till arbetsminne och spara på nvs
void setSerialNumber(char* new_serial);

