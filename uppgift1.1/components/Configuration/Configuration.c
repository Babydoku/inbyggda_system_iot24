#include "configuration.h"
#include "nvs_flash.h"
#include "nvs.h"
#include <string.h>
#include <stdio.h>
#include "esp_log.h"

static char device_name[20];
static char serial_number[20];

void Configuration_init() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
   
    nvs_handle_t nvs_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &nvs_handle));

    size_t required_size;
    
 
    ret = nvs_get_str(nvs_handle, "device_name", NULL, &required_size);
    if (ret == ESP_OK && required_size <= sizeof(device_name)) {
        nvs_get_str(nvs_handle, "device_name", device_name, &required_size);
    } else {
        strcpy(device_name, "DefaultDevice");
    }

   
    ret = nvs_get_str(nvs_handle, "serial_number", NULL, &required_size);
    if (ret == ESP_OK && required_size <= sizeof(serial_number)) {
        nvs_get_str(nvs_handle, "serial_number", serial_number, &required_size);
    } else {
        strcpy(serial_number, "123456789");
    }

    nvs_close(nvs_handle);
}

char* getDeviceName() {
    return device_name;
}

char* getSerialNumber() {
    return serial_number;
}

void setDeviceName(char* new_name) {
    if (strlen(new_name) >= sizeof(device_name)) {
        printf("Device name is too long (max 19 characters)\n");
        return;
    }

   
    strncpy(device_name, new_name, sizeof(device_name) - 1);
    device_name[sizeof(device_name) - 1] = '\0';  

    nvs_handle_t nvs_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &nvs_handle));
    
    esp_err_t err = nvs_set_str(nvs_handle, "device_name", device_name);
    if (err != ESP_OK) {
        printf("Failed to set device name in NVS: %s\n", esp_err_to_name(err));
    } else {
        ESP_ERROR_CHECK(nvs_commit(nvs_handle));
        printf("Device name updated to: %s\n", device_name);
    }
    
    nvs_close(nvs_handle);
}

void setSerialNumber(char* new_serial) {
    if (strlen(new_serial) >= sizeof(serial_number)) {
        printf("Serial number is too long (max 19 characters)\n");
        return;
    }

    strncpy(serial_number, new_serial, sizeof(serial_number) - 1);
    serial_number[sizeof(serial_number) - 1] = '\0'; 

    nvs_handle_t nvs_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &nvs_handle));
    
    esp_err_t err = nvs_set_str(nvs_handle, "serial_number", serial_number);
    if (err != ESP_OK) {
        printf("Failed to set serial number in NVS: %s\n", esp_err_to_name(err));
    } else {
        ESP_ERROR_CHECK(nvs_commit(nvs_handle));
        printf("Serial number updated to: %s\n", serial_number);
    }
    
    nvs_close(nvs_handle);
}
