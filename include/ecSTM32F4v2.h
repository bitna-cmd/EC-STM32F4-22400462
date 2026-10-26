//ecSTM32F4v2.h

/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 10-01-2026
Language/ver     : C++ in VS Code

Description      : STM32F411 Library.
/----------------------------------------------------------------*/

#ifndef __EC_STM_H
#define __EC_STM_H

// STM built-In Library
#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "math.h"

// EC course Library
#include "ecPinNames.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"
//#include "ecTIM2.h"
//#include "ecPWM2.h"
#include "ecStepper2.h"
//#include "ecADC2.h"
#include "ecUART2.h"





#define LED0_PIN        PB_12 		//EVAL board JKIT LED0
#define LED7_PIN        PC_3 		//EVAL board JKIT LED7
#define SW1_PIN         PD_2        //EVAL board JKIT SW1
#define SW2_PIN         PA_4	    //EVAL board JKIT SW2
#define LD2             PA_5        //NUCLEO board LED2
// stepper motor macro
#define BUTTON_PIN      PC_13       //NUCLEO board BUTTON1
#define DELAY_UNIT		US			// microsec
#define MOTOR_RPM		10			// 1rpm

// // FND segment pins (a~g, dot)
// PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
// // FND selection pins (FND0~FND3)
// PinName_t selectFND[4] = {PA_10, PA_11, PC_4, PC_3};
// ( A, B,  AN,  BN)
PinName_t pinStepper[4]    = {PC_5,PC_6,PC_7,PC_8};

// Initialize MCU clock, SysTick, GPIO, FND, EXTI, Stepper motor, and USART
void MCU_init(void){
	RCC_PLL_init();                 // System Clock = 84MHz
	SysTick_init();                 // SysTick Timer Initialization. SysTick: programming manual (STK)
	// Initialize GPIOB_12 for Output
	GPIO_init(LED0_PIN, OUTPUT);    // LED0 for EVAL board	
	GPIO_init(LED7_PIN, OUTPUT);    // LED7 for EVAL board
		
	// Initialize GPIOA_4 for Input Button
	GPIO_init(SW2_PIN, INPUT);  // INPUT for EVAL board
	GPIO_pupd(SW2_PIN, PULL_UP);  // PULL-UP for EVAL board

    // Initialize GPIOD_2 for Input Button
	GPIO_init(SW1_PIN, INPUT);  // INPUT for EVAL board
	GPIO_pupd(SW1_PIN, PULL_UP);  // PULL-UP for EVAL board

    // Initialize GPIOA_5 for Output Button and clear
    GPIO_init(LD2, OUTPUT);
	GPIO_write(LD2, LOW);

    // FND_init(pinFND);
    // FND_select_init(selectFND);

    // // Initialize 7-segment pins
    // for(int i=0; i<8; i++){
    //     GPIO_init_all(pinFND[i], OUTPUT, MEDIUM_SPEED, PUSH_PULL, NO_PUPD);
    // }

    // // Initialize GPIOA_10 for Output Button
	// GPIO_init(selectFND[0], OUTPUT);  // INPUT for EVAL board
	// GPIO_otype(selectFND[0], PUSH_PULL);  // PULL-UP for EVAL board
		
	// Initialize EXTI PA_4
	EXTI_init(SW2_PIN, FALL, 10);	
    // Initialize EXTI PD_2
    EXTI_init(SW1_PIN, FALL, 5);	

    // Initialize Stepper Motor
    GPIO_init(BUTTON_PIN, INPUT);           		// GPIOC pin13 initialization
    EXTI_init(BUTTON_PIN, FALL,0);           		// External Interrupt Setting

	stepper_init(STEPPER_MODE, pinStepper); 		// Stepper GPIO pin initialization
	stepper_speed(MOTOR_RPM, DELAY_UNIT);           //  set stepper motor speed (rpm)    

    // Initialize USART1,2
    // No Parity / 8-bit word length / Oversampling x16 / Stop bit =1
    // USART2: USB serial init
    USART_init(USART2, PA_2, PA_3, 9600);
    //USART2_baud(BAUD_38400);
    // USART1: MCU2 serial init
    USART_init(USART1, PA_9, PA_10, 9600);
    //USART1_baud(BAUD_38400);
        

    
    // TIMx Default Initialization
    // ...
    // PWM Default Initialization
    // ...  
    // Others
}


#endif