

#include "controller_interfacing.h"

#define LEFT_VERT 1
#define LEFT_HORI 0
#define RIGHT_VERT 3
#define RIGHT_HORI 2
#define RIGHT_TRIGG 5
#define LEFT_TRIGG 4
double pwm_power_factor = 0;

/*
    Example data format: 0,0.027436140018921477,-0.027466658528397473,0,0.003906369212927641,-1,-1
*/
void read_controller_data(char* data){
    char* controllerDataArray[7];
    int i = 0;

    // Convert comma seperated char* into char**
    controllerDataArray[i] = strtok(data, ",");
    while (controllerDataArray[i] != NULL) controllerDataArray[++i] = strtok(NULL, ",");
    
    // Convert char* to doubles
    double left_vert = -atof(controllerDataArray[LEFT_VERT]);
    double right_vert = -atof(controllerDataArray[RIGHT_VERT]);
    double left_trigger = atof(controllerDataArray[LEFT_TRIGG]);
    double right_trigger = atof(controllerDataArray[RIGHT_TRIGG]);

    // Analog pwm increase implementation
    if(left_trigger > 0.4) pwm_power_factor -= 0.1;
    if(right_trigger > 0.4)pwm_power_factor += 0.1;
    if(pwm_power_factor < 0) pwm_power_factor = 0;
    if(pwm_power_factor > 1) pwm_power_factor = 1;

    // Update pwm of motors
    set_analog_motor_pwm(left_vert * pwm_power_factor, 0);
    set_analog_motor_pwm(right_vert * pwm_power_factor, 1);
}