#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "wireless_comms.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_console.h"


#include "led_strip_encoder.h"
#include "input_output.h"
#include "board_interfacing.h"


void app_main(void)
{
    // Code which sets up ESP32-s3 as a server 
    run_BLE_server();

    printf("Hello World it's Ethan\n");
    //init_monitor(); Dont Use
    init_pwm();
    xTaskCreate(led_task, "LED Task", 4096, NULL, 10, NULL); // Starts new LED FreeRTOS task
    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);                    //FreeRTOS delay
    }
}