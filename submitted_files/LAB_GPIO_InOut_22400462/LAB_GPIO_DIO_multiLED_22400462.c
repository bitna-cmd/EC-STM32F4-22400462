/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 09-14-2026
Modified         : 09-14-2026
Language/ver     : C++ in VS Code

Description      : Prob3. Toggle multiple LEDs with a button
/----------------------------------------------------------------*/

#include "ecRCC2.h"
#include "ecGPIO2.h"

#define LED_0       PB_12
#define LED_1       PB_13
#define LED_2       PB_14
#define LED_3       PB_15

#define SW_2        PA_4

void setup(void);
	
int main(void) { 
	// Initialization
    // Set ledNum as 3 so that the first button press turns on LED_0.
    int ledNum = 3;     // LED number for the sequence
	setup();

	// Infinite Loop
	while(1){
		if (GPIO_read(SW_2) == LOW) {
            // Turn off the LED which was turned on.
            if (ledNum == 0)
                GPIO_write(LED_0, LOW);
            else if (ledNum == 1)
                GPIO_write(LED_1, LOW); 
            else if (ledNum == 2)
                GPIO_write(LED_2, LOW);
            else {
                GPIO_write(LED_3, LOW);
            }
            
            ledNum++;           //ledNum renew

            if(ledNum>3)        //Check the last step of the sequence.
                ledNum = 0;

            // Turn on the new LED
            if (ledNum == 0)
                GPIO_write(LED_0, HIGH);
            else if (ledNum == 1)
                GPIO_write(LED_1, HIGH); 
            else if (ledNum == 2)
                GPIO_write(LED_2, HIGH);
            else {
                GPIO_write(LED_3, HIGH);
            }

            while(GPIO_read(SW_2) == LOW)
                continue;
        }
        delay_ms_HSI(50);             					// delay 100 ms
	}
}

// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
	GPIO_init(SW_2, INPUT);
	GPIO_pupd(SW_2, PULL_UP);
    GPIO_init_all(LED_0, OUTPUT, MEDIUM_SPEED, OPEN_DRAIN, PULL_UP);
    GPIO_init_all(LED_1, OUTPUT, MEDIUM_SPEED, OPEN_DRAIN, PULL_UP);
    GPIO_init_all(LED_2, OUTPUT, MEDIUM_SPEED, OPEN_DRAIN, PULL_UP);
    GPIO_init_all(LED_3, OUTPUT, MEDIUM_SPEED, OPEN_DRAIN, PULL_UP);
    
    GPIO_write(LED_0, LOW);
    GPIO_write(LED_1, LOW);
    GPIO_write(LED_2, LOW);
    GPIO_write(LED_3, LOW);
}