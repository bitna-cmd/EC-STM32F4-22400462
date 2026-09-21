/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 09-17-2026
Modified         : 09-14-2026
Language/ver     : C++ in VS Code

Description      : LAB: GPIO 7-segment(eval board)
/----------------------------------------------------------------*/


///////////////////////////////////////////////
//              Problem 1                    //
///////////////////////////////////////////////

#include "stm32f4xx.h"
#include "ecGPIO2_22400462.h"
#include "ecRCC2_22400462.h"

PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
// PinName_t selectFND[4]={PA_10, ... }
// [YOUR CODE GOES HERE]
PinName_t selectFND[4] = {PA_10, PA_11, PC_4, PC_3};
PinName_t SW_2 = PA_4;

void setup(void){
    int i, j;
    // Intialize System Clock
    RCC_HSI_init();    
    // Intialize FND pins and Others
    FND_init(pinFND);
    FND_select_init(selectFND);    
    // Intialize  Others
	GPIO_init(SW_2, INPUT);
	GPIO_pupd(SW_2, PULL_UP);

    for(i=0; i<8; i++){
		GPIO_init_all(pinFND[i], OUTPUT, MEDIUM_SPEED, PUSH_PULL, NO_PUPD);
    }
    for(j=0; j<4; j++){
        GPIO_otype(selectFND[j], PUSH_PULL);
    }
};

int main(void) {
    setup();
    uint8_t numDisplay  = 0;
    uint8_t selectFND  = 0;

	FND_select(selectFND);

	while(1){
		if(GPIO_read(SW_2) == LOW){
			numDisplay++;
			FND_display(numDisplay);

			while(GPIO_read(SW_2) == LOW)
				continue;
		}
		if(numDisplay > 9)
			numDisplay = 0;
	}
}

///////////////////////////////////////////////
//              Problem 2                    //
///////////////////////////////////////////////
// 0~9

// // Problem 2 source code
// //#include "ecSTM32F4v2.h"
// #include "ecRCC2_22400462.h"
// #include "ecGPIO2_22400462.h"
// #include "ecSysTick2_22400462.h"

// #define BUTTON_PIN PC_13

// // Initialiization 
// void setup(void)
// {
// 	RCC_PLL_init();
// 	SysTick_init();
// 	GPIO_init(BUTTON_PIN, INPUT);  
// 	sevensegment_init();
// }
	
// int main(void) { 
// 	setup();
// 	unsigned int cnt = 0;
		
// 	while(1){
// 		// display 7-segment 0 to 9
// 		sevensegment_decode(cnt % 10);
// 		// increase number with button push
// 		if(GPIO_read(BUTTON_PIN) == 0) {
// 			cnt++; 
// 			delay_ms(500);
// 		}
// 		if (cnt > 9) cnt = 0;
// 	}
// }
