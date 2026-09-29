#include "stm32f411xe.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecSysTick2.h"  // < --  added !!!!

void SysTick_init(void){
	//  SysTick Control and Status Register
	// Reset to CTRL to Disable SysTick IRQ and SysTick Counter
	SysTick->CTRL = 0;											
	// SysTick->CTRL &=~1UL<<0;											

	// Select processor clock
	// 1 = processor clock;  0 = external clock
	SysTick->CTRL |=  (1UL << 2UL);  // [YOUR CODE GOES HERE!!]


	// Enables SysTick exception request
	// 1 = counting down to zero --> SysTick exception request 
	SysTick->CTRL |=  (1UL << 0UL);  // [YOUR CODE GOES HERE!!]


	// SysTick Reload Value Register : (SYSCLK / 1000) - 1  ->  1 ms
    // EC_SYSCLK :  HSI 16 MHz or PLL 84 MHz
	SysTick->LOAD =  (uint32_t)16000000 * 1UL / 1000UL - 1UL;  // [YOUR CODE GOES HERE!!]

        
	// SysTick Current Value Register : Reset counter value to 0
	SysTick->VAL = 0;
	
	// Enable SysTick IRQ and SysTick Timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
		
	// Enable interrupt in NVIC
	NVIC_SetPriority(SysTick_IRQn, 15);		// Set Priority to 1
	NVIC_EnableIRQ(SysTick_IRQn);			// Enable interrupt in NVIC
}

volatile uint32_t msTicks;

// SysTick_Handler() is called every 1 ms by the SysTick IRQ
void SysTick_Handler(void){
	SysTick_counter();	
}

// Increment msTicks every 1 ms
void SysTick_counter(void){
	msTicks++;
}	

// Blocking delay in milliseconds
void delay_ms (uint32_t msec){
  	uint32_t curTicks;
  	curTicks = msTicks;
		while ((msTicks - curTicks) < msec){;}		
}
