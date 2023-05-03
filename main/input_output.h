
#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include "board_interfacing.h"
#include <stdio.h>
#include "esp_vfs_dev.h"
#include "esp_vfs_fat.h"
#include "driver/uart.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_console.h"



extern char read_from_monitor();
extern char *robot_command_strings[];

extern void init_monitor();

extern RobotCommand input_handling(char c);

#endif