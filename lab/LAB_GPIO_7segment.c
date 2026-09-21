/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 09-17-2026
Modified         : 09-21-2026
Language/ver     : C++ in VS Code

Description      : LAB: GPIO 7-segment(eval board)
/----------------------------------------------------------------*/

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
			FND_display(numDisplay);
			numDisplay++;

			while(GPIO_read(SW_2) == LOW)
				continue;
		}
		if(numDisplay > 9)
			numDisplay = 0;
	}
}
