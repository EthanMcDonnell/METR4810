#ifndef BOARD_INTERFACING_H
#define BOARD_INTERFACING_H

#include "driver/ledc.h"

#define ML_IDENTIFIER 1
#define MR_IDENTIFIER 0

/*
    Initialises all pwm pins needed
*/
void init_pwm();

/*
    Set pwm of left or right motor to value
*/
void set_analog_motor_pwm(double value, int motor_identifier);

#endif