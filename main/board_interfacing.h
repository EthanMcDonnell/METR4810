#ifndef BOARD_INTERFACING_H
#define BOARD_INTERFACING_H

#include "driver/ledc.h"

/* States */
typedef enum
{
    Still = 0,
    Forward = 1,
    Reverse = 2,
    Left = 3,
    Right = 4,

} RobotCommand;

void update_pwm(int ledc_index, int val);
void init_pwm();
void set_motors(RobotCommand comm);



#endif