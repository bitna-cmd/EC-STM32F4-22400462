/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 10-08-2026
Modified         : 10-19-2026
Language/ver     : C in VS Code

Description      : USART2 Problem 1
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"  // this should include #include "ecUART2.h"

#define MAX_BUF 32          // maximum size of buffer
#define END_CHAR 13         // this means enter. ASCII 13: \r

static volatile uint8_t buffer[MAX_BUF]={0, };          // temporarily store the recieved letters
static volatile uint8_t PC_string[MAX_BUF+1]={0, };       // store the completed letters
static volatile uint8_t PC_data = 0;                    // store one recieved character 

static volatile int idx = 0;            // index for next letter
static volatile int bReceive =0;        // flag for check if the string is completed

void setup(void){
    RCC_PLL_init();
    SysTick_init();

	GPIO_init(PA_5, OUTPUT);
	GPIO_write(PA_5, LOW);

    // USART2: USB serial init
	USART_init(USART2, PA_2, PA_3, 9600);
    //USART2_baud(BAUD_38400);
    // USART1: MCU2 serial init
	USART_init(USART1, PA_9, PA_10, 9600);
    //USART1_baud(BAUD_38400);
}

int main(void){
    setup();
    printf("MCU Initialized\r\n");

    while(1){
        if (bReceive == 1){
            printf("PC_string: %s\r\n", PC_string);
            bReceive = 0;
        }
    }
}

void USART2_IRQHandler(){       // USART2 RX Interrupt
    if(is_USART2_RXNE()){
        PC_data = USART2_read();     // RX from UART2 (PC)
        USART2_write(&PC_data,1);    // TX to USART2 (PC) Echo of keyboard typing
        USART1_write(&PC_data, 1);   // TX to USART1 (other MCU)

        // Creates a String from received serial character
        if(PC_data != END_CHAR && (idx < MAX_BUF)){
            buffer[idx] = PC_data;
            idx++;
        }
        else if (PC_data== END_CHAR) {
            bReceive = 1;
            // reset PC_string
            memset(PC_string, 0, sizeof(char) * MAX_BUF);
            // copy to PC_string
            memcpy(PC_string, buffer, sizeof(char) * idx);
            // reset buffer
            memset(buffer, 0, sizeof(char) * MAX_BUF);
            idx = 0;
        }
        else{       // if(idx >= MAX_BUF)
            idx = 0;
            // reset PC_string
            memset(PC_string, 0, sizeof(char) * MAX_BUF);
            // reset buffer
            memset(buffer, 0, sizeof(char) * MAX_BUF);
            printf("ERROR : Too long string\r\n");
        }
    }
}

// Added: receive a string from the other MCU through PA9/PA10.
void USART1_IRQHandler(){
    if(is_USART1_RXNE()){
        PC_data = USART1_read();
        //USART2_write(&PC_data,1); // Echo received character to local PC

		// if other MCU get 'H' or 'L' from my PC, its LED(PA_5) will change
		if(PC_data == 'H')
			GPIO_write(PA_5, HIGH);
		else if (PC_data == 'L')
			GPIO_write(PA_5, LOW);

		// get string
        if(PC_data != END_CHAR && (idx < MAX_BUF)){
            buffer[idx] = PC_data;
            idx++;
        }
        else if (PC_data == END_CHAR){
            bReceive = 1;
            memset(PC_string, 0, sizeof(char) * MAX_BUF);
            memcpy(PC_string, buffer, sizeof(char) * idx);
            memset(buffer, 0, sizeof(char) * MAX_BUF);
            idx = 0;
        }
        else{
            idx = 0;
            memset(PC_string, 0, sizeof(char) * MAX_BUF);
            memset(buffer, 0, sizeof(char) * MAX_BUF);
            printf("ERROR : Too long string\r\n");
        }
    }
}
