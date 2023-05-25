#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wireless_comms.h"
#include "led_strip_encoder.h"
#include "board_interfacing.h"

void app_main(void)
{
    init_pwm();                                                 // Initialises PWM motor outputs
    xTaskCreate(led_task, "LED Task", 4096, NULL, 10, NULL);    // Starts new LED FreeRTOS task
    run_BLE_server();                                           // Code which sets up ESP32-s3 as a server
    printf("Everything Initialised\n");
}