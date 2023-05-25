#ifndef CONTROLLER_INTERFACING_H
#define CONTROLLER_INTERFACING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board_interfacing.h"

/*
    Function to help read and deal with incoming controller data
    Example data format: 0,0.027436140018921477,-0.027466658528397473,0,0.003906369212927641,-1,-1
*/
void read_controller_data(char* data);

#endif