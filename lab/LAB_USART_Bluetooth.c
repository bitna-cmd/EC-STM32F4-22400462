/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 10-08-2026
Modified         : 10-19-2026
Language/ver     : C in VS Code

Description      : USART2 Problem 1
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"  // this should include #include "ecUART2.h"

#define MAX_BUF 10          // maximum size of buffer
#define END_CHAR 13         // this means enter. ASCII 13: \r

#define REV     2           // revolution to rotate

static volatile uint8_t buffer[MAX_BUF]={0, };          // temporarily store the recieved letters
static volatile uint8_t PC_string[MAX_BUF]={0, };       // store the completed letters
static volatile uint8_t PC_data = 0;                    // store one recieved character 

uint32_t steps = STEP_PER_REV * REV;        // total steps of stepper motor
static volatile uint8_t motor_act = 0;                      // actions mode of motor (J(CW),K(CCW),P(Pause))

static volatile int idx = 0;            // index for next letter
static volatile int bReceive =0;        // flag for check if the string is completed

// int main(void){
//     MCU_init();
//     printf("MCU Initialized\r\n");

//     while(1){
//         if(motor_act == 'J') {
//             motor_act = 0;
//             stepper_step(steps, DIR_CW, DELAY_UNIT);// (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)
//         } else if(motor_act == 'K') {
//             motor_act = 0;
//             stepper_step(steps, DIR_CCW, DELAY_UNIT);// (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)
//         } // when motor_act is other case, then just skip
//         else if (PC_data == 'P') {
//             motor_act = 0;
//             stepper_stop();
//         }
//     }
// }

int main(void){
    MCU_init();
    printf("MCU Initialized\r\n");

    while(1){
        if(motor_act == 'J') {
            motor_act = 0;
            stepper_step(steps, DIR_CW, DELAY_UNIT);// (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)
        } else if(motor_act == 'K') {
            motor_act = 0;
            stepper_step(steps, DIR_CCW, DELAY_UNIT);// (Step : 2048, Direction : 0 or 1, Mode : FULL or HALF)
        } // when motor_act is other case, then just skip
        else if (PC_data == 'P') {
            motor_act = 0;
            stepper_stop();
        }
    }
}




void USART1_IRQHandler(){
    if(is_USART1_RXNE()){
        PC_data = USART1_read();
        USART2_write(&PC_data,1);   // Echo received character to local PC
        USART1_write(&PC_data,1);   // show recieved character to Tera Term

		// if other MCU get 'H' or 'L' from my PC, its LED(PA_5) will change
		if(PC_data == 'H')
			GPIO_write(PA_5, HIGH);
		else if (PC_data == 'L')
			GPIO_write(PA_5, LOW);

        if (PC_data == 'J') {
            motor_act = 'J';
            stepper_stop();         // if recieved other key, it can change the motor action immediately
        }
        else if (PC_data == 'K') {
            motor_act = 'K';
            stepper_stop();
        }
        else if (PC_data == 'P') {
            motor_act = 'P';
            stepper_stop();
        }
    }
}