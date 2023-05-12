
#include <stdio.h>
#include "esp_vfs_dev.h"
#include "esp_vfs_fat.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_system.h"
#include "esp_console.h"
/*

    NOT USED 

*/

/* States */
typedef enum
{
    Still = 0,
    Forward = 1,
    Reverse = 2,
    Left = 3,
    Right = 4,

} RobotCommand;

char *robot_command_strings[] = {"Still", "Forward", "Reverse", "Left", "Right"};

/*
    Returns current command from character
*/
void init_monitor() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    ESP_ERROR_CHECK(uart_driver_install(CONFIG_ESP_CONSOLE_UART_NUM, 256, 0, 0, NULL, 0));
    esp_vfs_dev_uart_use_driver(CONFIG_ESP_CONSOLE_UART_NUM);
    esp_vfs_dev_uart_port_set_rx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM, ESP_LINE_ENDINGS_CR);
    esp_vfs_dev_uart_port_set_tx_line_endings(CONFIG_ESP_CONSOLE_UART_NUM, ESP_LINE_ENDINGS_CRLF);
}

/* Test function for input handling while wifi/bluetooth is being developed*/
char read_from_monitor()
{
    char chr;
    scanf(" %c", &chr);
    return chr;
}

/* 
    Returns current command from character 
    Used on robot side 
*/
RobotCommand input_handling(char c) {
    switch (c)
    {
    case 'w':
        return Forward;
    case 's':
        return Reverse;
    case 'a':
        return Left;
    case 'd':
        return Right;
    default:
        return Still;
    }
}