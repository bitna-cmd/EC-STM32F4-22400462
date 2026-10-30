/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 09-29-2026 
Language/ver     : C++ in VS Code

Description      : SysTick Library. Distributed to Students for LAB_SYSTICK
/----------------------------------------------------------------*/


#ifndef __EC_SYSTICK2_H
#define __EC_SYSTICK2_H

#include "stm32f4xx.h"
#include "ecRCC2.h"
#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */


extern volatile uint32_t msTicks;	

// Initialize 1 ms tick of SysTick timer. 
// Must call AFTER RCC_HSI_init() (16 MHz) or RCC_PLL_init() (84 MHz)
// Updates  EC_SYSCLK either 84 MHz or 16 MHz
void SysTick_init(void);
// SysTick_Handler() is called every 1 ms by the SysTick IRQ
void SysTick_Handler(void);
// Increment msTicks every 1 ms
void SysTick_counter(void);
// Blocking delay in milliseconds
void delay_ms(uint32_t msec);
// Blocking delay in microseconds
void delay_us(uint32_t usec);
// Reset the SysTick counter to 0
void SysTick_reset(void);
// Return the current value of the SysTick counter
uint32_t SysTick_val(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_SYSTICK2_H
