
/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 10-19-2026
Language/ver     : C in VS Code

Description      : LAB USART LED
/----------------------------------------------------------------*/

#include "ecSTM32F4v2.h"

#define MAX_BUF 32       // Maximum string length + 1
#define END_CHAR 13      // Enter (\r)

static volatile uint8_t PC_Data = 0;
static volatile uint8_t BT_Data = 0;

// [추가] Example 2: String buffer
static volatile uint8_t buffer[MAX_BUF] = {0, };
static volatile uint8_t BT_string[MAX_BUF] = {0, };

static volatile int idx = 0;
static volatile int bReceive = 0;
static volatile int bOverflow = 0;

void setup(void){
    RCC_PLL_init();
    SysTick_init();

    // [추가] LD2 initialization
    GPIO_init(PA_5, OUTPUT);
    GPIO_write(PA_5, LOW);

    // USART2: USB serial init
    USART_init(USART2, PA_2, PA_3, BAUD_9600);

    // USART1: MCU2 serial init
    USART_init(USART1, PA_9, PA_10, BAUD_9600);
}

int main(void){
    setup();
    printf("MCU Initialized\r\n");

    while(1){
        // USART Receive: Use Interrupt only
        // USART Transmit: Polling

        // Example 2: Process completed string
        if(bReceive == 1){
            printf("RX: %s\r\n", (char*)BT_string);

            // LED Control
            if(BT_string[0] == 'H' && BT_string[1] == '\0'){
                GPIO_write(PA_5, HIGH);
            }
            else if(BT_string[0] == 'L' && BT_string[1] == '\0'){
                GPIO_write(PA_5, LOW);
            }

            bReceive = 0;
        }
    }
}

void USART2_IRQHandler(void){       // USART2 RX Interrupt
    if(is_USART2_RXNE()){
        PC_Data = USART2_read();     // RX from UART2 (PC)

        USART2_write(&PC_Data, 1);  // Echo keyboard typing
        USART1_write(&PC_Data, 1);  // TX to Other MCU
    }
}

void USART1_IRQHandler(void){       // USART1 RX Interrupt
    if(is_USART1_RXNE()){
        BT_Data = USART1_read();    // RX from other MCU

        // Example 2: Create string
        if(BT_Data != END_CHAR && BT_Data != '\n'){
            if(idx < MAX_BUF - 1 && bOverflow == 0){    // -1 is for '\0'
                buffer[idx] = BT_Data;
                idx++;
            }
            else{
                bOverflow = 1;
            }
        }
        else if(BT_Data == END_CHAR){
            if(bOverflow == 0 && bReceive == 0){
                buffer[idx] = '\0';

                // Copy completed string
                for(int i = 0; i <= idx; i++){
                    BT_string[i] = buffer[i];
                }

                bReceive = 1;
            }

            idx = 0;
            bOverflow = 0;
        }
    }
}
