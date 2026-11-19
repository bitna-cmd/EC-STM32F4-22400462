/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 11-05-2026
Language/ver     : C++ in VS Code

Description      : LAB - TIMER ICAP
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"

#define PWM_PIN     PA_6  // TIM3_CH1, TRIG
#define ICAP_PIN    PB_6  // TIM4_CH1, ECHO
#define LED_PIN     PA_5

uint32_t pwm_period_ms = 100;
uint32_t uTick = 10;
uint32_t timer_arr  = 65536;    // ticks per counter wrap (ARR+1)

// volatile uint32_t ovf_cnt = 0;      //counts overflows
volatile uint32_t cap_prev   = 0;   // CCR of the previous rising edge
volatile uint32_t cap_curr    = 0;  // CCR of the current falling edge
volatile uint32_t counts = 0;       // [ticks]
volatile float timeInterval = 0;    // [usec]
volatile uint8_t  _started   = 0;   
volatile float distance = 0;        // [cm]

void setup(void){
    RCC_PLL_init();
    SysTick_init();

    // Initialize LED pin
    GPIO_init(LED_PIN,OUTPUT);

    // Initialize Input Capture pin
    GPIO_init(ICAP_PIN, AF);
    GPIO_pupd(ICAP_PIN, NO_PUPD);

    // Initialize USART2 (baudrate: 9600)
    USART_init(USART2, PA_2, PA_3, 9600);

    // Initialize PWM (pwm period: 100ms, pulsewidth: 10us)
    PWM_init(PWM_PIN, pwm_period_ms);
    GPIO_otype(PWM_PIN, PUSH_PULL);
    GPIO_pupd(PWM_PIN, NO_PUPD);
    GPIO_ospeed(PWM_PIN, FAST_SPEED);
    PWM_pulsewidth_us(PWM_PIN, 10);

    // Input capture  rising edge TIn=ICn, tick = uTick usec    
    ICAP_init(ICAP_PIN, IC_RISE);
    ICAP_ICn_init(ICAP_PIN, IC_FALL, IC_2);     //TI1 -> IC2, falling
    ICAP_tick(ICAP_PIN, uTick);         

    timer_arr=TIM4->ARR + 1;
}

int main(void){
    setup();
    printf("HC-SR04 Distance Measurement\r\n");

    while(1){
        // Calculate distance
        distance = timeInterval / 58.0;     // (cm)

        // Print message
        if(2.0<=distance && distance<=400.0){
            printf("counts %lu, timeInterval = %.2f ms, distance: %.2f cm\r\n", 
                counts, timeInterval/1000, distance);  
        } else {
            printf("Out of range\r\n");
        }
   
        led_toggle(LED_PIN);
        delay_ms(2000);
    }
}

void TIM4_IRQHandler(void){

    // Counter Overflow
    if(is_UIF(TIM4)){
        clear_UIF(TIM4);
    }

    // Rising Edge
    if(is_CCIF(TIM4, IC_1)){
        cap_prev = ICAP_read(ICAP_PIN, IC_1);
        _started = 1;
        clear_CCIF(TIM4, IC_1);
    }

    // Falling Edge
    if(is_CCIF(TIM4, IC_2)){
        cap_curr = ICAP_read(ICAP_PIN, IC_2);

        // Calculate counts
        if(_started){
            if(cap_curr >= cap_prev){
                counts = cap_curr - cap_prev;
            }
            else{
                counts = timer_arr - cap_prev + cap_curr;
            }

            // Calulate timeInterval
            timeInterval = counts * uTick;
            _started = 0;
        }

        clear_CCIF(TIM4, IC_2);
    }
}