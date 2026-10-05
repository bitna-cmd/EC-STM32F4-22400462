/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 10-01-2026
Language/ver     : C++ in VS Code

Description      : Tutorial - EXTI & SysTick(eval)
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"

uint8_t count = 0;      // Counter number for 7-segment
uint8_t pause = 0;      // Check the counter is pause or not
uint8_t digit = 0;      // A flag for alternately displaying two-digit numbers


// MAIN  ----------------------------------------
int main(void) {
    MCU_init();         // Initialize MCU, GPIO, EXTI and SysTick

    while (1){
        // Main loop is empty because main operation is done by interrupts
    }
}


// SW2 interrupt : pause
// Handle SW2 interrupt for pause and resume
void EXTI4_IRQHandler(void) {
    if (is_pending_EXTI(SW2_PIN)) {   // Check SW2 interrupt

        pause = !pause;               // Change pause each time SW2 is pressed

        clear_pending_EXTI(SW2_PIN);  // Clear pending flag after interrupt
    }
}


// SW1 interrupt : reset counter
// Handle SW1 interrupt for counter reset
void EXTI2_IRQHandler(void) {
    if (is_pending_EXTI(SW1_PIN)) {   // Check SW1 interrupt

        count = 0;                    // Reset displayed number to 0
        msTicks = 0;                  // Reset tick count to restart 1 sec tick

        clear_pending_EXTI(SW1_PIN);  // Clear pending flag after interrupt
    }
}


// SysTick interrupt : called every 1 ms
void SysTick_Handler(void){

    SysTick_counter();                // Increase msTicks every 1 ms

    if(msTicks == 1000){
        msTicks = 0;                  // Reset tick count for next 1 second

        if(pause == 0){               // Increase count only when it is not paused
            count++;

            if(count > 59)
                count = 0;            // 0 after number 59
        }
    }

    if(digit == 0){
        FND_select(0);                    // Select LED0
        FND_display(count%10);               // Display current count number
        digit = 1;
    } else {
        FND_select(1);
        FND_display(count/10);
        digit = 0;
    }
}