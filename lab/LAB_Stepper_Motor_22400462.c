/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 10-12-2026
Language/ver     : C++ in VS Code

Description      : Source Code. Stepper Motor Control with FSM
/----------------------------------------------------------------*/

// #include "stm32f411xe.h"
// #include "ecGPIO2.h"
// #include "ecRCC2.h"
// #include "ecEXTI2.h"
// #include "ecSysTick2.h"
// #include "ecStepper2.h"
#include "ecSTM32F4v2.h"

#define BUTTON_PIN      PC_13
#define DELAY_UNIT		US			// microsec
#define MOTOR_RPM		10			// 1rpm

// ( A, B,  AN,  BN)
PinName_t pinStepper[4]    = {PB_10,PB_4,PB_5,PB_3};

// Initialiization 
void setup(void){	
	RCC_PLL_init();                                 // System Clock = 84MHz
	SysTick_init();                                 // Systick init
	
	GPIO_init(BUTTON_PIN, INPUT);           		// GPIOC pin13 initialization
    EXTI_init(BUTTON_PIN, FALL,0);           		// External Interrupt Setting

	stepper_init(STEPPER_MODE, pinStepper); 				// Stepper GPIO pin initialization
	stepper_speed(MOTOR_RPM, DELAY_UNIT);                          	//  set stepper motor speed (rpm)
}


int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();							// Initialize System Clock, SysTick, GPIO, EXTI, Stepper
	uint32_t rev=5;						// The number of revolutions
	uint32_t steps=STEP_PER_REV*rev;	// The number of the total steps of every revolutions
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		stepper_step(steps, DIR_CW, DELAY_UNIT);    // (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)
		delay_ms(2000);				    // Delay 2 sec
		stepper_step(steps, DIR_CCW, DELAY_UNIT);   // (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)
		delay_ms(2000);				    // Delay 2 sec
	}
}

// stop the stepper motor when BUTTON is pressed
void EXTI15_10_IRQHandler(void) {  
	if (is_pending_EXTI(BUTTON_PIN)) {
		stepper_stop();
		clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
	}
}
