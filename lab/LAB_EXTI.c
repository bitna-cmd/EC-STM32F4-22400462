/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 10-01-2026
Language/ver     : C++ in VS Code

Description      : Tutorial - EXTI & SysTick(eval)
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"

uint8_t count = 0;
uint8_t pause = 0;

// MAIN  ----------------------------------------
int main(void) {
    MCU_init();
	while (1){
    }
}

void EXTI4_IRQHandler(void) {
	if (is_pending_EXTI(SW2_PIN)) {   
        pause = !pause;
		clear_pending_EXTI(SW2_PIN);
	}
}

void EXTI2_IRQHandler(void) {
	if (is_pending_EXTI(SW1_PIN)) {   
        count = 0;
        msTicks = 0;
		clear_pending_EXTI(SW1_PIN);
	}
}

void SysTick_Handler(void){
    SysTick_counter();
    if(msTicks == 1000){
        msTicks = 0;
        if(pause == 0){
            count++;
            if(count>9)
                count = 0;
        }
    }
    FND_select(0);
    FND_display(count);
}