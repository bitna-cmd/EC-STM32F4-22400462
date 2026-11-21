/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : [ YOUR NAME GOES HERE !!!!!]
Created          : 10-26-2026
Modified         : 00-00-2026 [WRITE THE DATE!!!!]
Language/ver     : C in VS Code

Description      : Tutorial - I2C LCD (16x2 with a PCF8574 backpack)
                   SCL = PB_8,  SDA = PB_9,  module address = 0x27
/----------------------------------------------------------------*/
#include <stdio.h>
#include "ecRCC2.h"
#include "ecSysTick2.h"
#include "ecUART2.h"
#include "ecI2C2.h"


char     lcd_line[20];
uint32_t count = 0;
int      err   = 0;

// Initialiization
void setup(void)
{
	RCC_PLL_init();			// System Clock = 84MHz
	SysTick_init();
	USART2_init();			// USB serial init
	I2C1_init();			// SCL = PB_8,  SDA = PB_9
}


int main(void) {
	// Initialiization --------------------------------------------------------
	setup();

	// Does the LCD answer ?  A module with the wrong address stays blank.
	err = I2C1_write(LCD_ADDR, LCD_BACKLIGHT);
	if(err)	printf("LCD NOT found. Check the wiring\r\n");
	else	printf("LCD found at 0x%02X\r\n", LCD_ADDR);

	LCD_init();				// 4-bit mode, display ON, screen cleared

	// Line 1 : text that never changes, so write it once
	LCD_setCursor(0, 0);
	LCD_print("EC2026  I2C LCD");

	// Inifinite Loop ----------------------------------------------------------
	while(1){
		// Line 2 : a number that keeps counting.
		// The trailing blanks erase the leftover digits of a longer number.
		sprintf(lcd_line, "count = %lu   ", count);
		LCD_setCursor(0, 1);
		LCD_print(lcd_line);

		printf("count = %lu \r\n", count);
		count++;

		delay_ms(1000);
	}
}
