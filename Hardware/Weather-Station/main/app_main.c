#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"

#include "gpio.h"
#include "dht.h"
#include "ds3231.h"

#define DHT11_PIN   GPIO_NUM_5
#define SCL_PIN     GPIO_NUM_22
#define SDA_PIN     GPIO_NUM_21

static TaskHandle_t get_dht_task;
static TaskHandle_t get_ds3231_task;

dht11_data_t DHT11;
rtc_data_t DS3231;

void DHT11_ReadValue(void *arg)
{

    for( ;; )
    {
        DHT11_Get_Data(&DHT11);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
    
}

void DS3231_ReadValue(void *arg)
{
    for ( ;; )
    {
        DS3231_Register_Read((&DS3231));
        printf("[%02d/%02d/20%02d] %02d:%02d:%02d\n", DS3231.date, DS3231.month, 
                        DS3231.year, DS3231.hour, DS3231.minute, DS3231.second);
    }
    
}

void app_main(void)
{   
    DHT11_Init(&DHT11, DHT11_PIN);
    xTaskCreate(DHT11_ReadValue, "DHT11_ReadValue", 2048, NULL, 10, &get_dht_task);
    DS3231_Init(&DS3231, SCL_PIN, SDA_PIN);

    xTaskCreate(DS3231_ReadValue, "DS3231_ReadValue", 2048, NULL, 11, &get_ds3231_task);
    // xTaskCreate(task1, "task1", 1024, NULL, 1, NULL);
}