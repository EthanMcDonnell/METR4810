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


#include "input_output.h"

#define MOTOR_LEFT_GPIO 1
#define MOTOR_RIGHT_GPIO 1
#define BLINK_GPIO 25

RobotState robot_state = Still;
uint8_t s_led_state = 0;

static void configure_led(void){
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

void app_main(void)
{
    printf("Hello World\n");
    configure_led();
    init_monitor();
    while (1)
    {
        char inputc = read_from_monitor(); //Pauses until reads char
        robot_state = input_handling(inputc);
        printf("%s\n", robot_state_strings[(int) robot_state]);
        // printf("Turning the LED %s!\n", s_led_state == true ? "ON" : "OFF");
        gpio_set_level(BLINK_GPIO, s_led_state); //blink led
        s_led_state = !s_led_state; //toggle LED state
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}