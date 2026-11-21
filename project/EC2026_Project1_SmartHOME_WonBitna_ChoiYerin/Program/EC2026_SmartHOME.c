/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna / Choi Yerin
Created          : 05-03-2021
Modified         : 11-19-2026
Language/ver     : C++ in VS Code

Description      : Project1 Smart Home Management System
/----------------------------------------------------------------*/

// #error CHECK_MY_SOURCE_FILE

#include "ecSTM32F4v2.h"

// Output macros
#define FAN         PB_7    // Ventilation fan
#define WINDOW      PC_7    // Ventilation window servo, D9
#define LED_R       PB_13   // LED red, D23
#define LED_G       PB_14   // LED green, D35
#define LED_B       PB_15   // LED blue, D36

// Input macros
#define LIGHT       PA_0    // light sensor, A0
#define POT         PC_1    // potentiometer, A4
#define DHT11       PA_6    // D12
#define BUTTON      PA_10   // D2, interrupt
#define PIR         PB_3    // pin for motion detect
#define LCD_SCL     PB_8    // I2C Clock: Provide data transfer timing
#define LCD_SDA     PB_9    // I2C Data: Transfers commands and display data

// Threshold values
#define TRSH_TEMP_UPPER   30      // Upper threshold temperature
#define TRSH_HUMI_UPPER   55      // Upper threshold humidity
#define TRSH_TEMP_LOWER   28      // Lower threshold temperature
#define TRSH_HUMI_LOWER   50      // Lower threshold humidity

// Serve motor pulse width(HIGH duration) in microsec
#define SERVO_MID_US  500      // Neutral Position
#define SERVO_MAX_US  1500      // Maximum Position
#define SERVO_MAX_ANGLE 50      // Maximum Angle
#define HOME        0           // mode HOME
#define AWAY        1           // mode AWAY
#define ALARM       2           // mode ALARM

volatile uint32_t temp = 0;    // temperature
volatile uint32_t humi = 0;     // humidity
volatile uint32_t pulsewidth = SERVO_MID_US;
volatile uint32_t err = DHT11_OK;

volatile uint32_t current_count = 0;        // store the current timer count
volatile uint32_t pir_start_count = 0;      // starting count after motion detected
volatile uint32_t exit_count = 0;           // count after exit
volatile uint32_t intrusion_count = 0;      // for blinking intrusion message
volatile uint32_t last_lcd_count = 0;       // last count for lcd blinking

volatile uint8_t dht_flag = 0;          // flag for read or not dht
volatile uint32_t angle = 0;            // window angle
volatile uint8_t pir_flag = 0;          // flag for motion detection(motion: 1 / no motion: 0)
volatile uint8_t intrusion_flag = 0;    // flag to check intrusion
volatile uint8_t mode = 0;              // HOME(0), AWAY(1), or ALARM(2)
volatile float light_value = 0;         // brightness level value from photosensor
volatile float pot_value = 1;           // brightness standard value from potentiometer
volatile uint8_t exit_flag = 0;         // flag to check exit
volatile uint8_t vent_flag = 0;         // flag to check if reached upper threshold

volatile uint8_t previous_mode = 0;     // flag for check mode is changed
volatile uint8_t previous_vent = 0;     // flag for check ventilation ON/OFF change

volatile uint32_t dht_error_count = 0;  // for debugging the count of occured errors



char lcd_line[20];                      // lcd message buffer
static volatile uint8_t PC_data = 0;    // store one recieved character 

// turn off all LED (R,G,B)
void all_led_off(void);
// ventilation when temperature and humidity is above threshold (fan, window)
void ventilation(void);
// LED lighting function
// HOME: entrance->yellow / ventilation->green / dark->white
// AWAY: initial_3sec->yellow
// ALARM: intrusion->red
void lighting(void);
// LCD display function
// display mode, temp, humi, vent, intrusion
void lcd(void);
// initialize function
void setup(void);
// Send message to display on bluetooth (tera term)
void send_status(const char *msg);


int main(void){
    setup();

    // Does the LCD answer ?  A module with the wrong address stays blank.
	err = I2C1_write(LCD_ADDR, LCD_BACKLIGHT);
	if(err)	printf("LCD NOT found. Check the wiring\r\n");

    previous_mode = mode;
    previous_vent = vent_flag;

    send_status("MODE: HOME\r\n");

    // first line
	LCD_setCursor(0, 0);
	LCD_print("EC2026  I2C LCD");

    while(1){

        // Check mode change
        if(mode != previous_mode){
            uint8_t old_mode = previous_mode;
            previous_mode = mode;
            if(mode == HOME){
                send_status("MODE: HOME\r\n");
            }
            else if(mode == AWAY){
                if(old_mode == ALARM){
                    send_status("ALARM CLEARED\r\n");
                }
                send_status("MODE: AWAY\r\n");
            }
            else if(mode == ALARM){
                send_status("WARNING: INTRUSION!\r\n");
                send_status("MODE: ALARM\r\n");
            }
        }
        // Check ventilation change
        if(vent_flag != previous_vent){
            previous_vent = vent_flag;
            if(vent_flag == 1){
                send_status("VENTILATION ON\r\n");
            }
            else{
                send_status("VENTILATION OFF\r\n");
            }
        }
        // LCD update
        if(current_count != last_lcd_count){
            last_lcd_count = current_count;     // when current count is updated, lcd display update
            lcd();
        }

        // check DHT reading every 2.5sec
        if(dht_flag == 1){
            dht_flag = 0;
            err = DHT11_read();
            // check DHT reading is OK
            if(err == DHT11_OK){
                temp = DHT11_temperature();
                humi = DHT11_humidity();
                printf("Temperature=%d, Humidity=%d, potentio: %f \r\n", temp, humi, pot_value);
            } else {
                printf("DHT READING ERROR\r\n");
                dht_error_count++;
                printf("DHT ERROR COUNT: %lu\r\n", dht_error_count);
            } 
        }
    }
}


void setup(void){
    RCC_PLL_init();     // set system clock as 84MHz
    SysTick_init();     //Initialize SysTick timer

    // Initialize Fan PWM: TIM4 CH2, 1 ms period
    PWM_init(FAN, 1);
    PWM_duty(FAN, 0.0f);

    // Initialize Window PWM: TIM3 CH2, 20ms period
    PWM_init(WINDOW, 20);
    PWM_pulsewidth_us(WINDOW, SERVO_MID_US);

    // Initialize LED
    GPIO_init(LED_R, OUTPUT);   // Red
    GPIO_init(LED_G, OUTPUT);   // Green
    GPIO_init(LED_B, OUTPUT);   // Blue

    // Initialize lighting trigger timer 
    JADC_init(LIGHT);
    JADC_init(POT);
    PinName_t seqCHn[2] = {LIGHT, POT};
    JADC_sequence(seqCHn, 2);   
    JADC_trigger_init(TIM5, 125, ADC_RISE);

    // Initialize DHT sensor (temperature, humidity)
    DHT11_init(DHT11);  

    // Initialize button pin (GPIO+EXTI10)
    GPIO_init(BUTTON, INPUT);
    EXTI_init(BUTTON, FALL, 1);
    // GPIO_pupd(BUTTON, PULL_UP);

    // Initialize PIR (motion) pin (GPIO+EXTI3)
    GPIO_init(PIR, INPUT);
    EXTI_init(PIR, RISE, 2);

    // Initialize I2C LCD
    I2C1_init();        // Initialize I2C1
    LCD_init();         // Initialize LCD display

    // Initialize Debug Serial USART2
    USART_init(USART2, PA_2, PA_3, 9600);
    // Initialize Bluetooth USART6
    USART_init(USART6, PA_11, PA_12, 9600);

    TIM_UI_init(TIM1, 250);    // Control Loop Timer for update interrupt as 250msec
}

// Controller loop
void TIM1_UP_TIM10_IRQHandler(void){
    if(is_UIF(TIM1)){
        current_count++;

        // DHT11 flag control (to read every 2.5sec)
        if(current_count%10 == 0){
            dht_flag = 1;
        }

        // operate ventilation
        ventilation();
        // operate LED action
        lighting();
        // clear timer interrupt
        clear_UIF(TIM1);
    }   
}

// PIR function: check is motion detected
void EXTI3_IRQHandler(void){
    if(is_pending_EXTI(PIR)){
        // clear EXTI pending
        clear_pending_EXTI(PIR);

        if(mode == HOME){
            pir_start_count = current_count;    // for LED displaying time 
            pir_flag = 1;
        } else if (mode == AWAY){
            // intrusion should be detected after 5 sec from exit
            if((current_count - exit_count)>=20){
                intrusion_flag = 1;
                intrusion_count = current_count;
                mode = ALARM;
            }
        }
    }
}


// USART6 is connected to PC through STM port
void USART6_IRQHandler(void){
    if(is_USART_RXNE(USART6)){   
        PC_data = USART_read(USART6);    // Read one character from USART6->DR

        // Echo the received character to both serial terminals
        // USART2 -> STM PC terminal & USART6 -> Bluetooth terminal
        USART_write(USART2, &PC_data,1);   // Echo received character to local PC
        USART_write(USART6, &PC_data,1);   // show recieved character to Tera Term

		// Control warning flag which are received through Bluetooth
		if((PC_data == 'O' || PC_data == 'o') && mode == ALARM){
			intrusion_flag = 0;
            mode = AWAY;
        }
    }
}

// Button function - change mode (HOME / AWAY), flags and count when button is pressed
void EXTI15_10_IRQHandler(void){
    if(is_pending_EXTI(BUTTON)){
        clear_pending_EXTI(BUTTON);
        // Change to current mode and update flags and count
        if(mode == HOME){
            mode = AWAY;            // change mode to AWAY
            exit_flag = 1;          // report exit
            exit_count = current_count;     // store current count in exit count
            intrusion_flag = 0;     // clear intrusoin flag
            pir_flag = 0;           // clear PIR flag
        } else if (mode == AWAY || mode == ALARM){
            mode = HOME;            // change mode to HOME
            intrusion_flag = 0;     // clear intrusion flag
            pir_flag = 0;           // clear PIR flag
        }
    }
}

// Read the current brightness and standard brightness by JADC
void ADC_IRQHandler(void){
    if(is_ADC_JEOC()){
        light_value = JADC_read(1);
        pot_value = JADC_read(2);
        clear_ADC_JEOC();
    }
}

// Turn off all LED (R,G,B)
void all_led_off(void){
    GPIO_write(LED_R, LOW);
    GPIO_write(LED_G, LOW);
    GPIO_write(LED_B, LOW);
    return;
}

// Ventilation (Fan, Window)
void ventilation(void){
    if(mode == HOME){
        // TIM4 fan control
        // The current temparature and humidity are above upper threshold
        if(temp>=TRSH_TEMP_UPPER || humi>=TRSH_HUMI_UPPER){
            PWM_duty(FAN, 0.5f);
            vent_flag = 1;
        // The current temparature and humidity are above lower threshold
        } else if ((temp>=TRSH_TEMP_LOWER || humi>=TRSH_HUMI_LOWER) && vent_flag == 1) {
            PWM_duty(FAN, 0.5f);
        // The current temparature and humidity are below lower threshold
        } else {
            PWM_duty(FAN, 0.0f);    // turn off fan
            vent_flag = 0;
        }
        // TIM3 window control
        if(current_count%3 == 0){
            // check threshold condition
            // The current temparature and humidity are above upper threshold
            if (temp>=TRSH_TEMP_UPPER || humi>=TRSH_HUMI_UPPER){
                if (angle < SERVO_MAX_ANGLE)
                    angle += 10;    // increase angle upto maximum angle
            // The current temparature and humidity are above lower threshold
            } else if ((temp>=TRSH_TEMP_LOWER || humi>=TRSH_HUMI_LOWER) && vent_flag == 1) {
                if (angle < SERVO_MAX_ANGLE)
                    angle += 10;    // increase angle upto 90 deg
            // The current temparature and humidity are below lower threshold
            } else {
                if(angle > 0)
                    angle -= 10;    // decrease angle down to 0 deg
                vent_flag = 0;
            }
            // update pulsewidth of servo motor of window
            pulsewidth = SERVO_MID_US + angle * (SERVO_MAX_US - SERVO_MID_US) / SERVO_MAX_ANGLE;
            PWM_pulsewidth_us(WINDOW, pulsewidth);
        }
    } else if (mode == AWAY || mode == ALARM){
        PWM_duty(FAN, 0.0f);        // turn off fan
        vent_flag = 0;              // report that ventilation is off
        // If angle is not closed yet, close window.
        if((angle > 0) && (current_count%3 == 0))
            angle -= 10;
        // update pulsewidth of motor of fan
        pulsewidth = SERVO_MID_US + angle * (SERVO_MAX_US - SERVO_MID_US) / SERVO_MAX_ANGLE;
        PWM_pulsewidth_us(WINDOW, pulsewidth);
    }
}

// Lighting control function
void lighting(void){
    // Lighting control (MODE: HOME)
    if(mode == HOME){
        // Temperature and humidity detected
        if(vent_flag == 1){
            all_led_off();
            // blink green LED every 1 sec
            if((current_count/4)%2 == 0){
                GPIO_write(LED_G, HIGH);
            } else {
                GPIO_write(LED_G, LOW);
            }
        }
        // PIR motion detected
        else if(pir_flag == 1){
            GPIO_write(LED_R, HIGH);
            GPIO_write(LED_G, HIGH);
            GPIO_write(LED_B, LOW);
            // turn off all led after 3sec
            if((current_count - pir_start_count) >= 12){
                pir_flag = 0;   // clear pir detected flag
                all_led_off();
            }
        }
        // Darkness detected
        else if(light_value>=pot_value){
            GPIO_write(LED_R, HIGH);
            GPIO_write(LED_G, HIGH);
            GPIO_write(LED_B, HIGH);
        } else {
            all_led_off();
        }
    } else if (mode == AWAY || mode == ALARM){
        // PIR motion detected
        if(exit_flag == 1){
            GPIO_write(LED_R, HIGH);
            GPIO_write(LED_G, HIGH);
            GPIO_write(LED_B, LOW);
            // turn off all LED after 3sec
            if((current_count - exit_count) >= 12){
                exit_flag = 0;  // clear exit flag
                all_led_off();
            }
        }
        // If intrusion occurs, blink red LED
        else if(intrusion_flag == 1){
            GPIO_write(LED_G, LOW);
            GPIO_write(LED_B, LOW);
            // toggle red LED every 0.5sec
            if(current_count%2 == 0){
                led_toggle(LED_R);
            }
        } else {
            GPIO_write(LED_R, LOW);
            all_led_off();
        }
    }
}

// LCD display function
void lcd(void){
    if(mode == ALARM){
        LCD_setCursor(0,0);                 // first row
        LCD_print("MODE: ALARM     ");
        LCD_setCursor(0,1);                 // second row
        // Blink message every 1sec
        if(((current_count - intrusion_count)/4)%2 == 0){
            LCD_print("INTRUDER      ");
        } else {
            LCD_print("              ");
        }
        return;
    }
    // store message in 'lcd_line'
    snprintf(lcd_line, sizeof(lcd_line), "TEMP:%lu HUMI:%lu", (unsigned long)temp, (unsigned long)humi);
    LCD_setCursor(0, 0);    // first row
    LCD_print(lcd_line);    // display message on LCD
    LCD_setCursor(0, 1);    // second row
    if(mode == HOME){
        LCD_print("MODE: HOME      ");
        LCD_setCursor(12, 1);
        // If ventilation on, display "VENT"
        if (vent_flag == 1){
            LCD_print("VENT");
        }
        return;
    } else {
        LCD_print("MODE: AWAY      ");
        LCD_setCursor(12, 1);
        
        // Display count from 5 to 1 for 5 sec
        if(current_count - exit_count < 20){
            snprintf(lcd_line, sizeof(lcd_line), "%lu",
                     (unsigned long)(5 - (current_count - exit_count) / 4));
            LCD_print(lcd_line);
        }
        return;
    }
}

// Send message to display on bluetooth (tera term)
void send_status(const char *msg){
    // Bluetooth
    USART_write(USART6, (uint8_t*)msg, strlen(msg));
}

