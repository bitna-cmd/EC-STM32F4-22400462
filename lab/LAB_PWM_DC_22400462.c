/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 11-05-2026
Language/ver     : C++ in VS Code

Description      : LAB - PWM RC
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"

#define BUTTON_PIN      PC_13
#define DIR_PIN         PC_2
#define IR_PIN          PA_4
#define PWM_PIN         PA_0
#define LED_PIN         PA_5

volatile int8_t state = 0;
volatile int8_t next_state = 0;
volatile float duty = 0;
volatile int8_t uart_flag = 0;          // flag for displaying on serial monitor
static int8_t uart_count = 0;           // count for serial monitor timing
volatile int8_t led_mode = 0;

// FSM States for DC motor fan (S0~S2)
// Input combination (BUTTON,IR) is like : (0,F), (0,T), (1,F), (1,T)
// Output combination is (Velocity(duty), LED(mode))
static const StateFan_t fsm_FAN[3] = {	
 	{{FAN_S0,FAN_S0,FAN_S1,FAN_S0},{ 
		{VEL_S0, LED_OFF}, {VEL_S0, LED_BLINK}, {VEL_S1, LED_ON}, {VEL_S0, LED_BLINK}}},		// S0 
	{{FAN_S1,FAN_S1,FAN_S2,FAN_S1},{
		{VEL_S1, LED_ON}, {VEL_S0, LED_BLINK}, {VEL_S2, LED_ON}, {VEL_S0, LED_BLINK}}},		// S1
	{{FAN_S2,FAN_S2,FAN_S0,FAN_S2},{
		{VEL_S2, LED_ON}, {VEL_S0, LED_BLINK}, {VEL_S0, LED_OFF}, {VEL_S0, LED_BLINK}}},		// S2
};

void setup(void){
    RCC_PLL_init();

    // Initialize button pin
    GPIO_init(BUTTON_PIN, INPUT);
    GPIO_pupd(BUTTON_PIN, PULL_UP);

    // Initialize direction pin
    GPIO_init(DIR_PIN, OUTPUT);
    GPIO_otype(DIR_PIN, PUSH_PULL);
    GPIO_write(DIR_PIN, LOW);

    // Initialize IR pin
    GPIO_init(IR_PIN, INPUT);

    // Initialize LED pin
    GPIO_init(LED_PIN, OUTPUT);

    // PWM: TIM2_CH1, period = 1ms
    PWM_init(PWM_PIN, 1);
    PWM_duty(PWM_PIN, 0.0f);            // duty should be higher than 0.5, but this is initial value

    // TIM3: Interrupt every 500ms
    TIM_UI_init(TIM3, 500);

    // Initialize EXTI 
    EXTI_init(BUTTON_PIN, FALL, 1);

    // Initialize USART
    USART2_init();  // USART2: 9600 baud
}

int main(void){
    setup();
    while(1){
        // uint8_t input = (GPIO_read(IR_PIN) == HIGH)? 0 : 1;
        // OutputFan_t output = fsm_FAN[state].out[input];

        if(GPIO_read(IR_PIN) == HIGH){      // object not detached
            duty = fsm_FAN[state].out[0].V;
            PWM_duty(PWM_PIN, duty);   // assume not button pressed. button pressed is about EXTI handler.
            if(fsm_FAN[state].out[0].L == LED_OFF){
                GPIO_write(LED_PIN, LOW);
            } else {
                GPIO_write(LED_PIN, HIGH);
            }
        } else {
            duty = fsm_FAN[state].out[1].V;
            PWM_duty(PWM_PIN, duty);
            // toggle action is in TIM3_IRQHandler. because it depands on timer interrupt
        }

        // display serial monitor
        if(uart_flag){
            uart_flag = 0;
            if(GPIO_read(IR_PIN) == LOW)
                printf("MODE: PAUSE, duty: %.2f\r\n", duty);
            else if(state == FAN_S0)
                printf("MODE: OFF, duty: %.2f\r\n", duty);
            else if(state == FAN_S1)
                printf("MODE: MID, duty: %.2f\r\n", duty);
            else if(state == FAN_S2)
                printf("MODE: HIGH, duty: %.2f\r\n", duty);
        }
    }
}

void TIM3_IRQHandler(void){
    if(is_UIF(TIM3)){
        clear_UIF(TIM3);
        if(GPIO_read(IR_PIN) == LOW){
            // led_mode = LED_BLINK;
            led_toggle(LED_PIN);    // if object is detached, LED blink
        }
        // should display serial monitor every 2sec
        uart_count++;
        if(uart_count >= 4){
            uart_count = 0;
            uart_flag = 1;
        }
    }
}

void EXTI15_10_IRQHandler(void){
    if(is_pending_EXTI(BUTTON_PIN)){
        clear_pending_EXTI(BUTTON_PIN);
        if(GPIO_read(IR_PIN) == HIGH){
            // duty = fsm_FAN[state].out[2].V;     // out[2] means input: (BUTTON_PRESSED, OBJECT_NOT_DETACHED)
            state = fsm_FAN[state].next[2];     // state update
            // PWM_duty(PWM_PIN, duty);
        }
    }
}