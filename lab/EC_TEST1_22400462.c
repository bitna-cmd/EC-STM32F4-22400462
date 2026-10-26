/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Student ID       : 22400462
Created          : 10-22-2026
Language/ver     : C in VS Code

Description      : EC Test 1 (2026) Programming Test
                   
                   Rename this file to  EC_Test1_yourID.c
/----------------------------------------------------------------*/


#include "stm32f411xe.h"

//==================================================================
//  EC Library Include
//==================================================================
#include "ecSTM32F4v2.h"



//==================================================================
// User GPIO Pin definitions
//==================================================================
// YOUR CODE GOES HERE
// YOUR CODE GOES HERE
#define LED0_TEST    	    PB_12 		//EVAL board JKIT LED0
#define SW1_TEST       		PD_2        //EVAL board JKIT SW1
#define SW2_TEST             PA_4	    //EVAL board JKIT SW2
#define PHOTO_TEST	        PA_0        // Photodetector

#define BUTTON_PIN_TEST      PC_13       //NUCLEO board BUTTON1
#define DELAY_UNIT_TEST		US			// microsec
#define MOTOR_RPM_TEST		10			// 1rpm


// FND segments
// YOUR CODE GOES HERE
PinName_t pinFND_test[8] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};

// FND digit select : FND_0 ~ FND_3
// YOUR CODE GOES HERE
PinName_t selectFND_test[4] = {PA_10, PA_11, PC_4, PC_3};

PinName_t pinStepper_test[4] = {PC_5,PC_6,PC_7,PC_8};

// Global Variables
// use   volatile uint32_t   instead of uint32_t if used in Interrupt ISR
volatile uint32_t motor_mode   = 0;	
volatile uint32_t motor_dir    = 0;	
volatile uint32_t motor_speed  = 0;	
volatile uint32_t dummy_speed  = 0;	
// YOUR CODE GOES HERE
// YOUR CODE GOES HERE
// YOUR CODE GOES HERE
volatile uint8_t PC_data = 0;                    // store one recieved character 
volatile uint32_t led_flag  = 1;	





//==================================================================
//  Setup 
//==================================================================
void setup(void){
	RCC_PLL_init();					// System Clock = 84MHz
	SysTick_init();					// SysTick, 1 msec
	
	// USART2, 9600 baud
	// YOUR CODE GOES HERE			
	USART_init(USART2, PA_2, PA_3, 9600);	

	// GPIO Inputs
	// YOUR CODE GOES HERE
	GPIO_init(PD_2, INPUT);
	GPIO_pupd(PD_2, PULL_UP);
	GPIO_init(PA_4, INPUT);
	GPIO_pupd(PA_4, PULL_UP);

	GPIO_init(PA_0, INPUT);
	GPIO_pupd(PA_0, PULL_UP);

	GPIO_init(PB_12, OUTPUT);

	for(int i=0; i<8; i++){
		GPIO_init(pinFND_test[i], OUTPUT);
		GPIO_otype(pinFND_test[i], PUSH_PULL);
    }
    for(int j=0; j<4; j++){
		GPIO_init(selectFND_test[j], OUTPUT);
        GPIO_otype(selectFND_test[j], PUSH_PULL);
    }
	FND_init(pinFND_test);
	FND_select_init(selectFND_test);

	// EXTI 
	// YOUR CODE GOES HERE
	// YOUR CODE GOES HERE
	EXTI_init(PD_2, FALL, 3);
	EXTI_init(PA_4, FALL, 4);

	// GPIO Outputs	
	// YOUR CODE GOES HERE
	// YOUR CODE GOES HERE
	// YOUR CODE GOES HERE

	// Other Setup
	// YOUR CODE GOES HERE
	stepper_init(motor_mode, pinStepper_test); 				// Stepper GPIO pin initialization
	stepper_speed(MOTOR_RPM_TEST, DELAY_UNIT_TEST);                          	//  set stepper motor speed (rpm)

}


//==================================================================
//  Main
//==================================================================
int main(void){
	setup();


	// YOUR CODE GOES HERE
	GPIO_write(LED0_TEST, HIGH);
	FND_select(0);
	msTicks = 0;


	while(1){
		// Check PAUSE/RESUME 
		// YOUR CODE GOES HERE
		// YOUR CODE GOES HERE


		// stepper_speed(motor_speed, MS);
		// if(led_flag == 1)
		// 	stepper_stop();
		// else
		// 	stepper_step(1, motor_dir, MS);

		// while(led_flag == 1)
		// 	stepper_stop()


		if((msTicks%2000) == 0){
			if(led_flag == 1)
				led_flag = 0;
			else
				led_flag = 1;
			if(GPIO_read(PHOTO_TEST) == 1 && (msTicks%2000) == 0)	
				GPIO_write(LED0_TEST, HIGH);
				
			else if (GPIO_read(PHOTO_TEST) == 0 && (msTicks%2000) == 0){
				GPIO_write(LED0_TEST, led_flag);
				stepper_stop();
			}
			if((msTicks%2000) == 0){
			printf("Mode=%lu Speed=%lu DIR=%lu\r\n", motor_mode, motor_speed, motor_dir);
			}	
		}

		// Related to controlling motor speed/dir etc
		// HINT:  use  stepper_speed(vel);	only when vel>0
		// stepper_step(1, motor_dir, MS);	 // Keep step=1 or a low value to stop blocking other code
		// // YOUR CODE GOES HERE
		// // YOUR CODE GOES HERE
		// // YOUR CODE GOES HERE

		// if(led_flag == 0){
		// 	dummy_speed = motor_speed;
		// 	motor_speed = 0;
		// }
		
		// dummy_speed = motor_speed;


		// if(led_flag == 0){
		// 	stepper_stop();
		// 	// dummy_speed = motor_speed;
		// 	// motor_speed = 0;
		// }
		// else{
		// 	if(motor_speed>=0){
		// 		stepper_step(1, motor_dir, MS);
		// 	}
		// }
		
		if(GPIO_read(PHOTO_TEST) == 0){
			dummy_speed = motor_speed;
			motor_speed = 0;
		}



		stepper_speed(motor_speed, MS);
		stepper_step(1, motor_dir, MS);


		if(dummy_speed != 0){
			motor_speed = dummy_speed;
			dummy_speed = 0;
		}

		// Print to the serial monitor every 2 sec
		// PAUSE, blink at 2 sec
		//     e.g.  printf("Mode=%lu Speed=%lu DIR=%lu\r\n", ... );
		// HINT:  msTicks in ecSysTick2.h  is increasing at a 1 msec rate accurately.
		// You can use msTicks  to count every 2000 msec 
		// YOUR CODE GOES HERE
		// YOUR CODE GOES HERE
		// if((msTicks%2000) == 0){
		// 	printf("Mode=%lu Speed=%lu DIR=%lu\r\n", motor_mode, motor_speed, motor_dir);
		// }			
	}
}


//==================================================================
//  EXTI Interrupt Service Routines
//==================================================================

	// YOUR CODE GOES HERE
	// YOUR CODE GOES HERE
	// YOUR CODE GOES HERE
	// YOUR CODE GOES HERE
void EXTI2_IRQHandler(void) {
    if (is_pending_EXTI(SW1_TEST)) {   // Check SW1 interrupt
		if(GPIO_read(PHOTO_TEST) != 0){
			if(motor_speed == 0){
				motor_speed = 2;
				motor_mode = 1;
			}
			else if(motor_speed == 2){
				motor_speed = 6;
				motor_mode = 2;
			}
			else if(motor_speed == 6){
				motor_speed = 10;
				motor_mode = 3;
			}
			else if(motor_speed = 10){
				motor_speed = 10;
				motor_mode = 3;
			}
    	}
		clear_pending_EXTI(SW1_TEST);
	}
}


void EXTI4_IRQHandler(void) {
    if (is_pending_EXTI(SW2_TEST)) {   // Check SW2 interrupt
		if(GPIO_read(PHOTO_TEST) != 0){
			if(motor_speed == 10){
				motor_speed = 6;
				motor_mode = 2;
			}
			else if(motor_speed == 6){
				motor_speed = 2;
				motor_mode = 1;
			}
			else if(motor_speed == 2){
				motor_speed = 0;
				motor_mode = 0;
			}
			else if(motor_speed == 0){
				motor_speed = 0;
				motor_mode = 0;
			}
    	}
		clear_pending_EXTI(SW2_TEST);
	}
}

void SysTick_Handler(void){

    SysTick_counter();                // Increase msTicks every 1 ms

    if(msTicks == 2001){
        msTicks = 0;                  // Reset tick count for next 1 second
    }

	
	if(motor_dir == 0)
		FND_select(0);
	else
		FND_select(1);

	if(motor_mode == 0){
		FND_display(0);
		motor_mode = 0;
	}
	else if(motor_mode == 1){
		FND_display(1);
		motor_mode = 1;
	}
	else if(motor_mode == 2){
		FND_display(2);
		motor_mode = 2;
	}
	else if(motor_mode == 3){
		FND_display(3);
		motor_mode = 3;
	}
}

//==================================================================
//  UART2 Interrupt Service Routines
//==================================================================
void USART2_IRQHandler(void){
	if(is_USART2_RXNE()){
		USART2_write(&PC_data,1);   // Echo received character to local PC
     	//USART1_write(&PC_data,1);   // show recieved character to Tera Term
	// HINT: 	comparing a character:  
	//  		uint8_t ch = USART2_read();		
	//			if(ch == 'C' || ch == 'c')	 etc..
	//
	// YOUR CODE GOES HERE
	// YOUR CODE GOES HERE
		PC_data = USART2_read();
		if(PC_data == 'C' || PC_data == 'c')
			motor_dir = 0;
		else if (PC_data == 'B' || PC_data == 'b')
			motor_dir = 1;
	}
}
