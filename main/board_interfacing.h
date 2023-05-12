#ifndef BOARD_INTERFACING_H
#define BOARD_INTERFACING_H

#include "driver/ledc.h"

#define ML_IDENTIFIER 1
#define MR_IDENTIFIER 0

void update_pwm(int ledc_index, int val);
void init_pwm();
void set_analog_motor_pwm(double value, int motor_identifier);

#endif