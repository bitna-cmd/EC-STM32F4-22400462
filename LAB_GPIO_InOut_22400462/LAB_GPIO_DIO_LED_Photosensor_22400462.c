/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 09-14-2026
Language/ver     : C++ in VS Code

Description      : Prob2. Toggle a single LED with Digital Sensor(Photodetector)
/----------------------------------------------------------------*/

#include "ecRCC2_22400462.h"
#include "ecGPIO2_22400462.h"

#define PHOTO_PIN   PA_0      // Photodetector
#define LED_PIN     PB_12     // LED0 on JKIT

void setup(void);
	
int main(void) { 
	// Initialiization
	setup();

	// Inifinite Loop
	while(1){		
		if(GPIO_read(PHOTO_PIN) == 0)	GPIO_write(LED_PIN, HIGH);
		else 							GPIO_write(LED_PIN, LOW);
		delay_ms_HSI(100);             					// delay 100 ms
	}
}


// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
	GPIO_init(PHOTO_PIN, INPUT);   // calls RCC_GPIOA_enable()
	GPIO_init(LED_PIN, OUTPUT);    // calls RCC_GPIOB_enable()
	GPIO_otype(LED_PIN, OPEN_DRAIN);
	GPIO_pupd(LED_PIN, PULL_UP);
	GPIO_pupd(PHOTO_PIN, PULL_UP);
	GPIO_ospeed(LED_PIN, MEDIUM_SPEED);
}