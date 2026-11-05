/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 11-05-2026
Language/ver     : C++ in VS Code

Description      : LAB - PWM RC
/----------------------------------------------------------------*/
#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"
#include "ecSysTick2.h"
#include "ecTIM2.h"
#include "ecICAP2.h"
#include "ecPWM2.h"
#include "ecUART2.h"

// #define ICAP_PIN    PA_6        // TIM4_CH1 : capture input
// #define PWM_PIN     PB_6        // TIM3_CH1 : test signal (jumper PA_6 -> PB_6)
#define ICAP_PIN    PB_6  // TIM4_CH1, ECHO
#define PWM_PIN     PA_6  // TIM3_CH1, TRIG
#define LED_PIN     PA_5


//조건 이것저것 추가해야함!! 측정가능범위 넘어가면 어떻게 처리하라 그런것도 있지 않았나?


uint32_t pwm_period_ms=50;
uint32_t uTick=10;
uint32_t timer_arr  = 65536;    // ticks per counter wrap (ARR+1)

volatile uint32_t ovf_cnt = 0;      //counts overflows
volatile uint32_t cap_prev   = 0;   // CCR of the previous rising edge
volatile uint32_t cap_curr    = 0;  // CCR of the current rising edge
volatile uint32_t counts = 0;       // [pulses]
volatile float timeInterval = 0;    // [usec]
volatile uint8_t  _started   = 0;   
volatile float distance = 0;


void setup(void){
    RCC_PLL_init();
    SysTick_init();
    GPIO_init(LED_PIN,OUTPUT);
    //USART2_init();                    
    USART_init(USART2, PA_2, PA_3, 9600);

    // PWM: Test signal of period_ms of 50% duty 
    PWM_init(PWM_PIN, pwm_period_ms);
    // PWM_duty(PWM_PIN, 0.5f);
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
        printf("counts %lu, timeInterval = (%.2f msec)\r\n", counts, timeInterval/1000);  
        distance = timeInterval/1000.0*340.0/2.0/10.0;
        printf("distance: %.2f [cm]\r\n", distance);       
        led_toggle(LED_PIN);
        delay_ms(2000);
    }
}


void TIM4_IRQHandler(void){
    // Counter overflow 
    if(is_UIF(TIM4)){
        ovf_cnt++;
        clear_UIF(TIM4);
    }

    // Rising edge captured on IC1
    if(is_CCIF(TIM4, IC_1)){                    // IC1 : rising edge, SAME pin (TI1)
        cap_prev = ICAP_read(ICAP_PIN, IC_1);
        clear_CCIF(TIM4,IC_1);                                
    }
    // Falling edge captured on IC2
    if(is_CCIF(TIM4, IC_2)){                // IC2 : falling edge, SAME pin (TI1)       
        cap_curr = ICAP_read(ICAP_PIN, IC_2);

        // Ticks between the two edges, then scaled to usec.        
        counts = (cap_curr-cap_prev) + (ovf_cnt*timer_arr);
        timeInterval=counts*uTick;

        ovf_cnt    = 0; 
        clear_CCIF(TIM4, IC_2);
    }   
}