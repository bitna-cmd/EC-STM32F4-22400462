#include "ecRCC2_22400462.h"
#include "ecGPIO2_22400462.h"

#define LED_0       PB_12
#define SW_2        PA_4

int main(void){
    uint32_t val = 0;

    GPIO_init(SW_2, INPUT);
    GPIO_ospeed(SW_2, FAST_SPEED);
    GPIO_pupd(SW_2, PULL_UP);

    GPIO_init_all(LED_0, OUTPUT, MEDIUM_SPEED, OPEN_DRAIN, PULL_UP);

    val = GPIO_read(SW_2);
    if (val == HIGH)
        printf("SW_2 is pressed");
    else
        printf("SW_2 is not pressed");
}