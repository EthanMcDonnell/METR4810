
#include "board_interfacing.h"

#define MOTOR_LEFT_GPIO1 8
#define MOTOR_LEFT_GPIO2 7
#define MOTOR_RIGHT_GPIO1 35
#define MOTOR_RIGHT_GPIO2 36

#define MOTOR_MAX_PWM 500

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

    update_pwm(ML1_PWM_INDEX, 0);
    update_pwm(ML2_PWM_INDEX, 0);
    update_pwm(MR1_PWM_INDEX, 0);
    update_pwm(MR2_PWM_INDEX, 0);
}

/* 
    Initialise gpio to input output
*/
void configure_gpio(int gpio)
{
    gpio_reset_pin(gpio);
    gpio_set_direction(gpio, GPIO_MODE_OUTPUT);
}

void set_analog_motor_pwm(double value, int motor_identifier)
{
    int out[2] = {0, 0};
    if (value > 0.4) //FORWARD
    {
        out[0] = 0;
        out[1] = 1 * value * MOTOR_MAX_PWM;
    }
    else if (value < -0.4)
    {
        out[0] = 1 * -value * MOTOR_MAX_PWM;
        out[1] = 0;
    }
    else
    {
        out[0] = 1;
        out[1] = 1;
    }
    if (motor_identifier == ML_IDENTIFIER)
    {
        update_pwm(ML1_PWM_INDEX, out[0]);
        update_pwm(ML2_PWM_INDEX, out[1]);
    }
    else if (motor_identifier == MR_IDENTIFIER)
    {
        update_pwm(MR1_PWM_INDEX, out[1]);
        update_pwm(MR2_PWM_INDEX, out[0]);
    }
}