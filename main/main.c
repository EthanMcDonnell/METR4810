#include <stdio.h>
#include <string.h>
#include <inttypes.h>
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
    printf("Hello World it's Ethan\n");
    //init_monitor(); //DONT USE
    init_pwm();
    xTaskCreate(led_task, "LED Task", 4096, NULL, 10, NULL); // Starts new LED FreeRTOS task
    RobotCommand robot_command = Still;
    while (1)
    {
        //char inputc = read_from_monitor(); // Pauses until reads char
        //char inputc = 'w';
        
        robot_command = input_handling(inputc); // Finds robot command from given char
        //set_motors(robot_command);              
        printf("%s\n", robot_command_strings[(int)robot_command]);// Print current command to terminal
        vTaskDelay(40 / portTICK_PERIOD_MS);                    //FreeRTOS delay
    }
}