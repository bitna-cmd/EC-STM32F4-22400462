/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 10-08-2026
Modified         : 10-19-2026
Language/ver     : C in VS Code

Description      : USART2 Problem 2
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"

#define REV     2           // revolution to rotate

static volatile uint8_t PC_data = 0;                    // store one recieved character 

uint32_t steps = STEP_PER_REV * REV;        // total steps of stepper motor
static volatile uint8_t motor_act = 0;                      // actions mode of motor (J(CW),K(CCW),P(Pause))

int main(void){
    MCU_init();   // Initialize MCU 
    printf("MCU Initialized\r\n");

    while(1){
        if(motor_act == 'J') {
            motor_act = 0;      // Clear the action flag before starting rotation
            stepper_step(steps, DIR_CW, DELAY_UNIT);       // Rotate CW for 2 revolutions.
        } else if(motor_act == 'K') {
            motor_act = 0;
            stepper_step(steps, DIR_CCW, DELAY_UNIT);      // Rotate CCW for 2 revolutions.
        } // when motor_act is other case, then just skip
    }
}


// USART1 (RX interrupt) : Handle characters received from bluetooth (PA10: RX)
// USART2 is connected to PC through STM port
void USART1_IRQHandler(void){
    if(is_USART1_RXNE()){   
        PC_data = USART1_read();    // Read one character from USART1->DR

        // Echo the received character to both serial terminals
        // USART2 -> STM PC terminal & USART1 -> Bluetooth terminal
        USART2_write(&PC_data,1);   // Echo received character to local PC
        USART1_write(&PC_data,1);   // show recieved character to Tera Term

		// Control the LED High or Low commands which are received through Bluetooth
		if(PC_data == 'H')
			GPIO_write(PA_5, HIGH);     // H: LED ON
		else if (PC_data == 'L')
			GPIO_write(PA_5, LOW);      // L: LED OFF

        // Update the motor action flag
        // stepper_stop() sets the current step count to zero, 
        // so the current stepper_step() can finish and main() can process new action
        if (PC_data == 'J') {
            motor_act = 'J';        // Set motor action flag CW rotation
            stepper_stop();         // if recieved other key, it can change the motor action immediately
        }
        else if (PC_data == 'K') {
            motor_act = 'K';        // Set motor action flag CCW rotation
            stepper_stop();
        }
        else if (PC_data == 'P') {
            motor_act = 0;        // Set motor action flag as stop
            stepper_stop();
        }
    }
}