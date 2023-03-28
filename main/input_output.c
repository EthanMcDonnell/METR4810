#include "input_output.h"



char *robot_state_strings[] = {"Still", "Forward", "Reverse", "FLeft", "FRight"};

/*
    Returns current state from character
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
    Returns current state from character 
    Used on robot side 
*/
RobotState input_handling(char c) {
    switch (c)
    {
    case 'w':
        return Forward;
    case 's':
        return Reverse;
    case 'a':
        return FLeft;
    case 'd':
        return FRight;
    default:
        return Still;
    }
}