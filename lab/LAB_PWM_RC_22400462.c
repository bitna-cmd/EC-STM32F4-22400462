/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 11-05-2026
Language/ver     : C++ in VS Code

Description      : LAB - PWM RC
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"

#define BUTTON      PC_13

// Serve motor pulse width(HIGH duration) in microsec
#define SERVO_MIN_US  500
#define SERVO_MAX_US  2500
#define SERVO_MAX_ANGLE 180

volatile int32_t angle = 0;             // Angle of servo motor
volatile int32_t dir = 1;               // Direction of servo motor
volatile int32_t pulse_width = 0;       // HIGH duration in microsec

void setup(void){
    RCC_PLL_init();

    // Button pin initialization
    GPIO_init(BUTTON, INPUT);
    GPIO_pupd(BUTTON, PULL_UP);

    // PWM: TIM2_CH2, period = 20ms
    PWM_init(PA_1, 20);
    PWM_pulsewidth_us(PA_1, SERVO_MIN_US);
    // PWM_pulsewidth_us(PA_1, 1500);

    // TIM3: Interrupt every 500ms
    TIM_UI_init(TIM3, 500);

    // EXTI initialization
    EXTI_init(BUTTON, FALL, 1);
}

int main(void){
    setup();
    while(1){
    }
}

void TIM3_IRQHandler(void){
    if(is_UIF(TIM3)){
        // Change angle value of servo motor
        if(angle<=0)
            dir = 1;
        else if(angle>=180)
            dir = -1;
        angle += 10 * dir;

        // Update pulse width to change angle of servo motor
        pulse_width = SERVO_MIN_US + angle * (SERVO_MAX_US - SERVO_MIN_US) / SERVO_MAX_ANGLE;
        PWM_pulsewidth_us(PA_1, pulse_width);

        clear_UIF(TIM3);
    }
}

void EXTI15_10_IRQHandler(void){
    if(is_pending_EXTI(BUTTON)){
        angle = 0;
        dir = 1;
        PWM_pulsewidth_us(PA_1, SERVO_MIN_US);
        TIM3->CNT = 0;      // Restart 500ms timer instantly
        clear_pending_EXTI(BUTTON);
    }
}