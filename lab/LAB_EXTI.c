/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 10-01-2026
Language/ver     : C++ in VS Code

Description      : Tutorial - EXTI & SysTick(eval)
/----------------------------------------------------------------*/


// #include "ecRCC2.h"
// #include "ecGPIO2.h"
// #include "ecSysTick2.h"
// #include "ecEXTI2.h"
#include "ecSTM32F4v2.h"

// #define LED0_PIN   PB_12 		//EVAL board JKIT LED0
// #define SW2_PIN    PA_4			//EVAL board JKIT SW2


// void led_toggle(PinName_t pinName);  // in ecGPIO2.h

// Initialiization 
// void setup(void)
// {
//     RCC_PLL_init();                 // System Clock = 84MHz
//     SysTick_init();                 // SysTick Timer Initialization
//     // Initialize GPIOB_12 for Output
//     GPIO_init(LED0_PIN, OUTPUT);    // LED0 for EVAL board	

//     // Initialize GPIOA_4 for Input Button
//     GPIO_init(SW2_PIN, INPUT);  // INPUT for EVAL board
//     GPIO_pupd(SW2_PIN, PULL_UP);  // PULL-UP for EVAL board

//     // Initialize EXTI PA_4
//     EXTI_init(SW2_PIN, FALL, 10);		
// }


// MAIN  ----------------------------------------
int main(void) {
    uint8_t count = 0;
    MCU_init();
	while (1){
        count++;
        delay_ms(1000);
        if(count > 9)
            count = 0;
    }
}

void EXTI4_IRQHandler(void) {
	if (is_pending_EXTI(SW2_PIN)) {   
			led_toggle(LED0_PIN);
			clear_pending_EXTI(SW2_PIN);
	}
}

void EXTI2_IRQHandler(void) {
	if (is_pending_EXTI(SW2_PIN)) {   
			led_toggle(LED0_PIN);
			clear_pending_EXTI(SW2_PIN);
	}
}