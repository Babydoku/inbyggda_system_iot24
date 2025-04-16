#include <stdio.h>
#include "printer.h"
#include "esp_log.h"
#include "helper_component.h"

extern "C" void app_main(void)
{
    int a=ovning_2::func();
    ESP_LOGI("MAIN", " got value %d", a);
    
    
    

}