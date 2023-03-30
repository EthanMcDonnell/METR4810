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
#include "driver/ledc.h"

#include "input_output.h"

#define MOTOR_LEFT_GPIO1 21
#define MOTOR_LEFT_GPIO2 21
#define MOTOR_RIGHT_GPIO1 21
#define MOTOR_RIGHT_GPIO2 21
#define ONBOARDLED_GPIO 25
#define LED_GPIO 12
#define V_BAT_GPIO 1

#define MOTOR_LEFT_SPEED 500
#define MOTOR_RIGHT_SPEED 500

#define ML_IDENTIFIER 1
#define MR_IDENTIFIER 0

RobotState robot_state = Still;
uint8_t s_led_state = 0;

#define PWM_CHANNELS_NUM 5
ledc_channel_config_t ledc_channels[PWM_CHANNELS_NUM]; //PWM channels

#define ML1_PWM_INDEX 0
#define ML2_PWM_INDEX 1
#define MR1_PWM_INDEX 2
#define MR2_PWM_INDEX 3
#define LED_PWM_INDEX 4

static void update_pwm(int ledc_index, int val){
    ledc_set_duty(ledc_channels[ledc_index].speed_mode, ledc_channels[ledc_index].channel, val);
    ledc_update_duty(ledc_channels[ledc_index].speed_mode, ledc_channels[ledc_index].channel);
}

static void init_pwm()
{
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = 1000,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
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

    ledc_channels[LED_PWM_INDEX].channel = LEDC_CHANNEL_4;
    ledc_channels[LED_PWM_INDEX].gpio_num = LED_GPIO;
    for (int i = 0; i < PWM_CHANNELS_NUM; i++)
    {
        ledc_channels[i].duty = 0;
        ledc_channels[i].speed_mode = LEDC_HIGH_SPEED_MODE;
        ledc_channels[i].hpoint = 0;
        ledc_channels[i].timer_sel = LEDC_TIMER_0;
        ledc_channel_config(&ledc_channels[i]);
    }

    update_pwm(ML1_PWM_INDEX, MOTOR_LEFT_SPEED);
    update_pwm(ML2_PWM_INDEX, MOTOR_LEFT_SPEED);
    update_pwm(MR1_PWM_INDEX, MOTOR_RIGHT_SPEED);
    update_pwm(MR2_PWM_INDEX, MOTOR_RIGHT_SPEED);
}

/* Sets gpio to input output*/
static void configure_gpio(int gpio){
    gpio_reset_pin(gpio);
    gpio_set_direction(gpio, GPIO_MODE_INPUT_OUTPUT);
}

// mode -1: Reverse, 0: still, 1: forward
static void set_motor_gpio(int mode, int motor_identifier){
    int out[2] = {0,0};
    if (mode == 1){
        out[0] = 1;
        out[1] = 0;
    }
    else if (mode == -1){
        out[0] = 0;
        out[1] = 1;
    }
    else if (mode == 0){
        out[0] = 1;
        out[1] = 1;
    }
    if (motor_identifier == ML_IDENTIFIER)
    {
        update_pwm(ML1_PWM_INDEX, out[0] * MOTOR_LEFT_SPEED);
        update_pwm(ML2_PWM_INDEX, out[1] * MOTOR_LEFT_SPEED);
    }
    else if (motor_identifier == MR_IDENTIFIER){
        update_pwm(MR1_PWM_INDEX, out[0] * MOTOR_RIGHT_SPEED);
        update_pwm(MR2_PWM_INDEX, out[1] * MOTOR_RIGHT_SPEED);
    }
}
static void set_motors(RobotState state){
    switch (state) {
    case Forward:
        set_motor_gpio(1, ML_IDENTIFIER);
        set_motor_gpio(1, MR_IDENTIFIER);
        break;
    case Reverse:
        set_motor_gpio(-1, ML_IDENTIFIER);
        set_motor_gpio(-1, MR_IDENTIFIER);
        break;
    case Left:
        set_motor_gpio(-1, ML_IDENTIFIER);
        set_motor_gpio(1, MR_IDENTIFIER);
        break;
    case Right:
        set_motor_gpio(1, ML_IDENTIFIER);
        set_motor_gpio(-1, MR_IDENTIFIER);
        break;
    case Still:
        set_motor_gpio(0, ML_IDENTIFIER);
        set_motor_gpio(0, MR_IDENTIFIER);
        break;
    default:
        break;
    }
}

void app_main(void)
{
    printf("Hello World it's Ethan\n");
    configure_gpio(ONBOARDLED_GPIO);
    configure_gpio(LED_GPIO);
    init_monitor();
    init_pwm();
    int led_pwm = 0;
    while (1)
    {
        //char inputc = read_from_monitor();    // Pauses until reads char
        // robot_state = input_handling(inputc);
        printf("%s\n", robot_state_strings[(int) robot_state]);

        
        gpio_set_level(ONBOARDLED_GPIO, s_led_state); // blink led
        
        s_led_state = !s_led_state; //toggle LED state

        update_pwm(LED_PWM_INDEX, led_pwm);
        led_pwm +=2;
        if(led_pwm > 50) led_pwm = 0;

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}