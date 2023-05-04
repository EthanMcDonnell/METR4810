
#include "board_interfacing.h"

#define MOTOR_LEFT_GPIO1 8
#define MOTOR_LEFT_GPIO2 7
#define MOTOR_RIGHT_GPIO1 35
#define MOTOR_RIGHT_GPIO2 37

#define MOTOR_LEFT_SPEED 3000   // 0 to 2000 (NEEDS TESTING)
#define MOTOR_RIGHT_SPEED 3000  // 0 to 2000 (NEEDS TESTING)

#define ML_IDENTIFIER 1
#define MR_IDENTIFIER 0

#define M_FORWARD 1             // Motor Identifier Forward
#define M_REVERSE -1            // Motor Identifier Reverse
#define M_STILL 0               // Motor Identifier Still


#define PWM_CHANNELS_NUM 5
ledc_channel_config_t ledc_channels[PWM_CHANNELS_NUM]; // PWM channels
#define ML1_PWM_INDEX 0
#define ML2_PWM_INDEX 1
#define MR1_PWM_INDEX 2
#define MR2_PWM_INDEX 3
#define LED_PWM_INDEX 4

/* 
    Updates values of pwm
    Used for disabling pins as well
*/
void update_pwm(int ledc_index, int val)
{
    ledc_set_duty(ledc_channels[ledc_index].speed_mode, ledc_channels[ledc_index].channel, val);
    ledc_update_duty(ledc_channels[ledc_index].speed_mode, ledc_channels[ledc_index].channel);
}

/*
    Initialises all pwm pins needed
*/
void init_pwm()
{
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = 1000,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ledc_timer_config(&ledc_timer);
    ledc_channels[ML1_PWM_INDEX].channel = LEDC_CHANNEL_0;
    ledc_channels[ML1_PWM_INDEX].gpio_num = MOTOR_LEFT_GPIO1;
    ledc_channels[ML2_PWM_INDEX].channel = LEDC_CHANNEL_1;
    ledc_channels[ML2_PWM_INDEX].gpio_num = MOTOR_LEFT_GPIO2;
    ledc_channels[MR1_PWM_INDEX].channel = LEDC_CHANNEL_2;
    ledc_channels[MR1_PWM_INDEX].gpio_num = MOTOR_RIGHT_GPIO1;
    ledc_channels[MR2_PWM_INDEX].channel = LEDC_CHANNEL_3;
    ledc_channels[MR2_PWM_INDEX].gpio_num = MOTOR_RIGHT_GPIO2;
    for (int i = 0; i < PWM_CHANNELS_NUM; i++)
    {
        ledc_channels[i].duty = 0;
        ledc_channels[i].speed_mode = LEDC_LOW_SPEED_MODE;
        ledc_channels[i].hpoint = 0;
        ledc_channels[i].timer_sel = LEDC_TIMER_0;
        ledc_channel_config(&ledc_channels[i]);
    }

    update_pwm(ML1_PWM_INDEX, MOTOR_LEFT_SPEED);
    update_pwm(ML2_PWM_INDEX, MOTOR_LEFT_SPEED);
    update_pwm(MR1_PWM_INDEX, MOTOR_RIGHT_SPEED);
    update_pwm(MR2_PWM_INDEX, MOTOR_RIGHT_SPEED);
}

/* 
    Sets gpio to input output
*/
void configure_gpio(int gpio)
{
    gpio_reset_pin(gpio);
    gpio_set_direction(gpio, GPIO_MODE_OUTPUT);
}

/*
    Set individual motor pwm depending on motor identifier
*/
void set_motor_pwm(int mode, int motor_identifier)
{
    int out[2] = {0, 0};
    if (mode == M_FORWARD)
    {
        out[0] = 0;
        out[1] = 1;
    }
    else if (mode == M_REVERSE)
    {
        out[0] = 1;
        out[1] = 0;
    }
    else if (mode == M_STILL)
    {
        out[0] = 1;
        out[1] = 1;
    }
    if (motor_identifier == ML_IDENTIFIER)
    {
        update_pwm(ML1_PWM_INDEX, out[0] * MOTOR_LEFT_SPEED);
        update_pwm(ML2_PWM_INDEX, out[1] * MOTOR_LEFT_SPEED);
    }
    else if (motor_identifier == MR_IDENTIFIER)
    {
        update_pwm(MR1_PWM_INDEX, out[0] * MOTOR_RIGHT_SPEED);
        update_pwm(MR2_PWM_INDEX, out[1] * MOTOR_RIGHT_SPEED);
    }
}

/*
    Set pair of motors depending on RobotCommand given
*/
void set_motors(RobotCommand comm)
{
    switch (comm)
    {
    case Forward:
        set_motor_pwm(M_FORWARD, ML_IDENTIFIER);
        set_motor_pwm(M_FORWARD, MR_IDENTIFIER);
        break;
    case Reverse:
        set_motor_pwm(M_REVERSE, ML_IDENTIFIER);
        set_motor_pwm(M_REVERSE, MR_IDENTIFIER);
        break;
    case Left:
        set_motor_pwm(M_REVERSE, ML_IDENTIFIER);
        set_motor_pwm(M_FORWARD, MR_IDENTIFIER);
        break;
    case Right:
        set_motor_pwm(M_FORWARD, ML_IDENTIFIER);
        set_motor_pwm(M_REVERSE, MR_IDENTIFIER);
        break;
    case Still:
        set_motor_pwm(M_STILL, ML_IDENTIFIER);
        set_motor_pwm(M_STILL, MR_IDENTIFIER);
        break;
    default:
        break;
    }
}