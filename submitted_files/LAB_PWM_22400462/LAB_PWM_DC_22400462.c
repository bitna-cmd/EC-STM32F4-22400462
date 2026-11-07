/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 11-05-2026
Language/ver     : C++ in VS Code

Description      : LAB - PWM DC motor control
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"

// Pin definitions
#define BUTTON_PIN      PC_13   // USER button (B1)
#define DIR_PIN         PC_2    // DC motor direction control
#define IR_PIN          PA_4    // IR proximity sensor (Digital Output)
#define PWM_PIN         PA_0    // DC motor PWM output (TIM2_CH1)
#define LED_PIN         PA_5    // On-board LED (LD2)

volatile int8_t state = 0;              // Current FSM state (S0: OFF, S1: MID, S2: HIGH)
volatile float duty = 0;                // Current PWM duty ratio (0.0 ~ 1.0)
volatile int8_t uart_flag = 0;          // flag for displaying on serial monitor
static int8_t uart_count = 0;           // count for serial monitor timing
volatile uint8_t button_lock = 0;       // Prevent bouncing

// FSM States for DC motor fan (S0~S2)
// Input combination (BUTTON,IR) is like : (0,F), (0,T), (1,F), (1,T)
// Output combination is (Velocity(duty), LED(mode))
static const StateFan_t fsm_FAN[3] = {	
 	{{FAN_S0,FAN_S0,FAN_S1,FAN_S0},{ 
		{VEL_S0, LED_OFF}, {VEL_S0, LED_BLINK}, {VEL_S1, LED_ON}, {VEL_S0, LED_BLINK}}},	// S0: OFF
	{{FAN_S1,FAN_S1,FAN_S2,FAN_S1},{
		{VEL_S1, LED_ON}, {VEL_S0, LED_BLINK}, {VEL_S2, LED_ON}, {VEL_S0, LED_BLINK}}},	    // S1: MID
	{{FAN_S2,FAN_S2,FAN_S0,FAN_S2},{
		{VEL_S2, LED_ON}, {VEL_S0, LED_BLINK}, {VEL_S0, LED_OFF}, {VEL_S0, LED_BLINK}}},	// S2: HIGH
};

void setup(void){
    RCC_PLL_init();

    // Initialize button pin as input
    GPIO_init(BUTTON_PIN, INPUT);
    GPIO_pupd(BUTTON_PIN, PULL_UP);

    // Initialize direction pin as output, push-pull
    GPIO_init(DIR_PIN, OUTPUT);
    GPIO_otype(DIR_PIN, PUSH_PULL);
    GPIO_write(DIR_PIN, LOW);

    // Initialize IR pin as input, pull-up
    GPIO_init(IR_PIN, INPUT);
    GPIO_pupd(IR_PIN, PULL_UP);

    // Initialize LED pin as output
    GPIO_init(LED_PIN, OUTPUT);
    GPIO_write(LED_PIN, LOW);   // Initial LED state: OFF

    // PWM: TIM2_CH1, period = 1ms
    PWM_init(PWM_PIN, 1);
    PWM_duty(PWM_PIN, 0.0f);     // Initial duty: 0 (OFF)

    // TIM3: Interrupt every 500ms
    TIM_UI_init(TIM3, 500);

    // Initialize button pin interrupt (trigger: falling edge)
    EXTI_init(BUTTON_PIN, FALL, 1);

    // Initialize USART2
    USART2_init();  // USART2: 9600 baud
}

int main(void){
    setup();
    while(1){
        // this can make code easier to read
        // uint8_t input = (GPIO_read(IR_PIN) == HIGH)? 0 : 1;
        // OutputFan_t output = fsm_FAN[state].out[input];

        // Check IR sensor continuously using GPIO polling
        if(GPIO_read(IR_PIN) == HIGH){      // object not deteched
            // Apply PWM duty according to the current FSM state
            // out[0] corresponds to (BUTTON=0, IR=F)
            duty = fsm_FAN[state].out[0].V;
            PWM_duty(PWM_PIN, duty);   // assume not button pressed. button pressed is about EXTI handler.

            // Control LED according to the current FSM output
            if(fsm_FAN[state].out[0].L == LED_OFF){
                GPIO_write(LED_PIN, LOW);
            } else {
                GPIO_write(LED_PIN, HIGH);
            }
        } else {
            // Stop the motor without changing the current FSM state
            // out[1] corresponds to (BUTTON=0, IR=T)
            duty = fsm_FAN[state].out[1].V;
            PWM_duty(PWM_PIN, duty);
            // toggle action is in TIM3_IRQHandler. because it depands on timer interrupt
        }

        // Display the current mode and PWM duty every 2 seconds
        if(uart_flag){
            // clear UART flag after detecting the request
            uart_flag = 0;

            // Display PAUSE mode when the object is detected
            if(GPIO_read(IR_PIN) == LOW)
                printf("MODE: PAUSE, duty: %.2f\r\n", duty);
            // Display OFF mode
            else if(state == FAN_S0)
                printf("MODE: OFF, duty: %.2f\r\n", duty);
            // Display MID mode
            else if(state == FAN_S1)
                printf("MODE: MID, duty: %.2f\r\n", duty);
            // Display HIGH mode
            else if(state == FAN_S2)
                printf("MODE: HIGH, duty: %.2f\r\n", duty);
        }
    }
}

// TIM3 update interrupt: executed every 500ms
void TIM3_IRQHandler(void){
    if(is_UIF(TIM3)){
        clear_UIF(TIM3);

        // button input can be accepted after TIM3 check
        // debounce: unlock after release
        if(button_lock && GPIO_read(BUTTON_PIN) == HIGH){
            button_lock = 0;
        }

        // blink LED during PAUSE
        // toggle every 500ms -> blinking period = 1 second
        if(GPIO_read(IR_PIN) == LOW){
            led_toggle(LED_PIN);    // if object is deteched, LED blink
        }

        // update count TIM3 interrupt for UART output
        uart_count++;

        // 500 * 4 = 2 sec
        if(uart_count >= 4){
            uart_count = 0;
            uart_flag = 1;      // request to display serial monitor
        }
    }
}

// Button interrupt: change the motor mode
void EXTI15_10_IRQHandler(void){
    if(is_pending_EXTI(BUTTON_PIN)){
        clear_pending_EXTI(BUTTON_PIN);

        // Object is not deteched and button is not locked
        if(GPIO_read(IR_PIN) == HIGH && button_lock == 0){
            // Lock button input to prevent repeated state transitions
            button_lock = 1;
            // Input index 2 corresponds to (BUTTON=1, IR=F)
            state = fsm_FAN[state].next[2];     // state update
        }
    }
}