
#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>
#include "esp_vfs_dev.h"
#include "esp_vfs_fat.h"
#include "driver/uart.h"

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

/* States */
typedef enum
{
    Still = 0,
    Forward = 1,
    Reverse = 2,
    FLeft = 3,
    FRight = 4,

} RobotState;

extern read_from_monitor();
extern char *robot_state_strings[];

extern void init_monitor();

extern RobotState input_handling(char c);

#endif