

#include "controller_interfacing.h"

#define LEFT_VERT 1
#define LEFT_HORI 0
#define RIGHT_VERT 3
#define RIGHT_HORI 2

/*
    Example data format: 0, 0.027436140018921477,-0.027466658528397473,0,0.003906369212927641,-1,-1
*/
void read_controller_data(char* data){
    char* controllerDataArray[5];
    int i = 0;
    controllerDataArray[i] = strtok(data, ",");

    while (controllerDataArray[i] != NULL) controllerDataArray[++i] = strtok(NULL, ",");
    double left_vert = -atof(controllerDataArray[LEFT_VERT]);
    double left_horiz = atof(controllerDataArray[LEFT_HORI]);
    double right_vert = -atof(controllerDataArray[RIGHT_VERT]);
    double right_horiz = atof(controllerDataArray[RIGHT_HORI]);

    set_analog_motor_pwm(left_vert, 0);
    set_analog_motor_pwm(right_vert, 1);
}