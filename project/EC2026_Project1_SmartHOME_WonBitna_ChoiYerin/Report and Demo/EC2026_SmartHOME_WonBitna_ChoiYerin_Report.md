## Smart-Home Management System

Date: 2026-11-10

### **I. Introduction**

-----

##### Overview

Design an STM32-based smart home system that provides motion-based lighting, temperature and humidity ventilation, and away-mode intrusion detection![Smart Home Concept Illustration](img/img_1.png)

*Figure 1. Smart home concept illustration.*

![](img/img_2.png)

*Figure 2. System overview with the given sensors, displays and actuators.*

##### Requirements

**Hardware**

| Category           | Component                           | Qty         | Notes                                                                |
| ------------------ | ----------------------------------- | ----------- | -------------------------------------------------------------------- |
| **MCU**            | STM32 Nucleo-F411RE board           | 1           | Makes all control decisions                                          |
| **Digital Sensor** | DHT11 temperature / humidity sensor | 1           | Needs an external pull-up on the data line                           |
|                    | PIR motion sensor                   | 1           | Detects intruder                                                     |
|                    | Push button                         | 1           | Toggles HOME / AWAY                                                  |
| **Analog Sensor**  | Light sensor                        | 1           | light detection                                                      |
|                    | Air-quality sensor                  | 1           | Supplied, not required; see the optional extension                   |
|                    | Potentiometer                       | 1           | Sets the darkness threshold                                          |
| **Display**        | I2C LCD                             | 1           | use provided I2C library                                             |
| **Actuator**       | RGB LED                             | 1           | Three digital outputs, one per colour. Check common anode or cathode |
|                    | Ventilation fan                     | 1           | needs DC motor driver                                                |
|                    | Window servo motor                  | 1           | Operates the ventilation window; separate supply                     |
| **Communication**  | Bluetooth module                    | 1           | Serial link to USART6                                                |
| **Others**         | Door lock                           | 1           | Supplied, not required                                               |
|                    | Ceiling fan                         | 1           | Supplied, not required                                               |
|                    | Acrylic home model, motor drivers   | As supplied |                                                                      |

**Software**

- IDE: VS Code

- Compiler: PlatformIO `framework=cmsis`

- Library: EC-STM32F4

- Extra Library: EC-STM32F4 `ecDHT11`, `ecI2C2`

  - `TU_DHT11.c` and `TU_I2C_LCD.c`

### II. Problem

-----

##### Overview

The purpose of this project is building a smart home system that controls the lighting, ventilation and alarms under the following conditions.

| State     | Condition                  | Required behavior                                            |
| :-------- | :------------------------- | :----------------------------------------------------------- |
| **HOME**  | `mode == HOME`             | Provide motion-based lighting and run ventilation as needed. Motion is not an intrusion. |
| **AWAY**  | `mode == AWAY`             | Suspend the motion-based lighting and monitor motion as intrusion. |
| **ALARM** | `alarm == INTRUSION_ALARM` | Show the warning and perform the matching response. Clearing the alarm returns to previous mode, HOME or AWAY as selected. |

The push-button selects HOME/AWAY. AWAY starts a **5 s exit delay** before intrusion monitoring, so the user can leave. And showed the countdown on the LCD.

##### Basic Functions

| Function        | Behavior                                                                                                                                                                                                                 |
| --------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **Lighting**    | In HOME, when PIR detects motion at the entrance, light the RGB LED **yellow** for 3 seconds. When the light sensor in the living room reports darkness, turn on **White** LED. Under mode='Intrusion' blink **Red** LED |
| **Ventilation** | In HOME only, run the ventilation fan and open the servo window when temperature **or** humidity exceeds its upper threshold. Stop and close only after **both** readings fall below their lower thresholds              |
| **Intrusion**   | Under mode == AWAY only, PIR motion detection raises `INTRUSION_ALARM`.                                                                                                                                                  |
| **Button**      | Pressing the button toggles HOME/AWAY. Acknowledge alarms through Bluetooth, display on LCD                                                                                                                              |
| **LCD**         | Shows the current mode and specific information as instructed                                                                                                                                                            |

> Threshold Settings
>
> - Potentio: around 2760
>
> - Temperature(upper): 30 [deg*C]
>
> - Temperature(lower): 28 [deg*C]
>
> - Humidity(upper): 55 (%)
>
> - Humidity(lower): 50 (%)

##### Light and Display Response

The RGB LED is driven as **three digital outputs**, one per color.

- Away Intrusion: **Red,** blinking every 0.5s

- AWAY countdown: **Yellow**, R=H, G=H for 3 sec

- HOME light on: **White**, R=H, G=H, B=H

- HOME entrance: **Yellow**, R=H, G=H for 3 sec

- HOME ventilation: **Green**, blinking 1 sec

  

LCD Display:

- Mode name: HOME, AWAY, ALARM

- Mode = HOME

  - Temp, humidity reading (00°, 00%)

- Mode = HOME+Ventilation

  - Temp, humidity reading, VENT (00°, 00%, VENT)

- Mode = AWAY

  - Away-Countdown

- Mode = ALARM

  - INTRUDER (blink 1 sec)

> Lighting Condition Priority Settings
>
> 1. Ventilation(Green): The blinking green LED shows that the fan and the window are operating. We gave it the highest priority because the user should always know when a device is running. 
> 2. Motion detect(Yellow): The LED is short, 3 second response to motion at the entrance. It is useful, but it is temporary, so we placed it below ventilation. 
> 3. Brightness(White): The white LED is normal room lighting that stays on as long as the room is dark. Since it is a background condition rather than an event, it has the lowest priority. 

##### Communication Message to server

Using the bluetooth, send a message and display on laptop's monitor whenever a condition is changed.

- Remote Control : Turned off the intrusion alarm using bluetooth by pressing 'O' or 'o' key. e.g. mode=ALARM to mode=AWAY

### III. Hardware Configuration

----

##### MCU Configuration

| Function        | Peripheral                                      | Pin (Arduino)                    | Configuration            |
| --------------- | ----------------------------------------------- | -------------------------------- | ------------------------ |
| Ventilation fan | TIM4 CH2 (PWM)                                  | PB_7                             | 1 ms (1 kHz)             |
| Window servo    | TIM3 CH2 (PWM)                                  | PC_7 (D9)                        | 20 ms (50 Hz)            |
| RGB LED, red    | GPIO output                                     | PB_13 (D23)                      | DOUT                     |
| RGB LED, green  | GPIO output                                     | PB_14 (D35)                      | DOUT                     |
| RGB LED, blue   | GPIO output                                     | PB_15 (D36)                      | DOUT                     |
| Control loop    | TIM1 (update interrupt)                         | none                             | 250 ms                   |
| Light sensor    | ADC1 injected, result in JDR1                   | PA_0 (A0)                        | TIM5 TRGO of 125 ms      |
| Potentiometer   | ADC1 injected, result in JDR2                   | PC_1 (A4)                        | TIM5 TRGO of 125 ms      |
| DHT11           | GPIO, bit-banged (SysTick µs timing, `ecDHT11`) | PA_6 (D12)                       | one read per 2.5 s       |
| Push button     | GPIO + EXTI10                                   | PA_10 (D2)                       | interrupt on press       |
| PIR motion      | GPIO + EXTI3                                    | PB_3 (D3)                        | interrupt on rising edge |
| I2C LCD         | I2C1                                            | PB_8 (D21, SCL), PB_9 (D20, SDA) | —                        |
| Bluetooth       | USART6                                          | PA_11 (D18, TX), PA_12 (D19, RX) | 9600 baud                |
| Debug serial    | USART2                                          | PA_2 (TX), PA_3 (RX)             | —                        |
| Spare           | TIM4 CH1                                        | PB_6 free                        | —                        |

##### Circuit Diagram

![pin connection](img/Circuit_Diagram.png)

### IV. Algorithm

----

##### Logic Design (Flow Chart)

![Flow Chart](img/Flow_Chart.png)

###### 1. Macros

**Pin macros**

| Macro                       | Pin                   | Description                                                 |
| --------------------------- | --------------------- | ----------------------------------------------------------- |
| `FAN`                       | PB_7                  | Ventilation fan (TIM4 CH2 PWM)                              |
| `WINDOW`                    | PC_7                  | Window servo motor (TIM3 CH2 PWM)                           |
| `LED_R` / `LED_G` / `LED_B` | PB_13 / PB_14 / PB_15 | RGB LED, one digital output per color                       |
| `LIGHT`                     | PA_0                  | Light sensor (JADC channel 1)                               |
| `POT`                       | PC_1                  | Potentiometer, sets the darkness threshold (JADC channel 2) |
| `DHT11`                     | PA_6                  | Temperature and humidity sensor                             |
| `BUTTON`                    | PA_10                 | Mode toggle button (EXTI10)                                 |
| `PIR`                       | PB_3                  | PIR motion sensor (EXTI3)                                   |
| `LCD_SCL` / `LCD_SDA`       | PB_8 / PB_9           | I2C LCD clock / data                                        |

**Threshold macros**

| Macro             | Value | Description                                                  |
| ----------------- | ----- | ------------------------------------------------------------ |
| `TRSH_TEMP_UPPER` | 30 °C | Ventilation starts if temperature reaches this value         |
| `TRSH_HUMI_UPPER` | 55 %  | Ventilation starts if humidity reaches this value            |
| `TRSH_TEMP_LOWER` | 28 °C | Ventilation stops only if temperature is below this value and humidity is below its lower threshold |
| `TRSH_HUMI_LOWER` | 50 %  | Ventilation stops only if humidity is below this value and temperature is below its lower threshold |

**Servo and mode macros**

| Macro             | Value   | Description                                      |
| ----------------- | ------- | ------------------------------------------------ |
| `SERVO_MID_US`    | 900 µs  | Pulse width for the closed window (0°)           |
| `SERVO_MAX_US`    | 1500 µs | Pulse width for the fully open window            |
| `SERVO_MAX_ANGLE` | 50°     | Maximum window opening angle                     |
| `HOME`            | 0       | Mode when user is at home                        |
| `AWAY`            | 1       | Mode when user is away (includes 5 s exit delay) |
| `ALARM`           | 2       | Mode when intrusion detected                     |

###### 2. State and condition flags

| Flag             | Set to 1                                                 | Cleared to 0                                                              | Meaning                                                                                             |
| ---------------- | -------------------------------------------------------- | ------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------- |
| `mode`           | —                                                        | —                                                                         | Main system state (`HOME`, `AWAY`, `ALARM`). Changed by the button ISR, PIR ISR, and Bluetooth ISR. |
| `dht_flag`       | TIM1 ISR, every 10 ticks (2.5 s)                         | `main()` after reading                                                    | Tells the main loop to read the DHT11.                                                              |
| `pir_flag`       | PIR ISR, in HOME                                         | `lighting()` after 3 s, or button ISR                                     | Entrance motion → yellow LED for 3 s.                                                               |
| `exit_flag`      | Button ISR, HOME → AWAY                                  | `lighting()` after 3 s                                                    | Yellow LED for 3 s when leaving the house.                                                          |
| `intrusion_flag` | PIR ISR, in AWAY after the 5 s exit delay                | Bluetooth ISR (`'o'`), or button ISR                                      | Intrusion detected → red LED blinking.                                                              |
| `vent_flag`      | `ventilation()`, when temp or humidity ≥ upper threshold | `ventilation()`, when temp and humidity < lower threshold, or mode ≠ HOME | Ventilation ON/OFF state. Controls fan, servo, green LED, LCD “VENT”.                               |
| `previous_mode`  | `main()`                                                 | —                                                                         | Last mode. If different from `mode`, a status message is sent.                                      |
| `previous_vent`  | `main()`                                                 | —                                                                         | Last ventilation state. If different from `vent_flag`, a status message is sent.                    |

###### 3. Timing Counters

(1 tick = 250ms)

| Variable          | Description                                                             |
| ----------------- | ----------------------------------------------------------------------- |
| `current_count`   | Increases by 1 every TIM1 interrupt. Acts as the system clock.          |
| `pir_start_count` | Tick when entrance motion was detected (yellow LED timing).             |
| `exit_count`      | Tick when the mode changed to AWAY (exit delay, countdown, yellow LED). |
| `intrusion_count` | Tick when the intrusion was detected.                                   |
| `last_lcd_count`  | Last tick when the LCD was updated, so the LCD refreshes once per tick. |

**Tick-to-time reference**

| Ticks | Time   | Used for                                      |
| ----- | ------ | --------------------------------------------- |
| 2     | 0.5 s  | Red LED blinking period                       |
| 3     | 0.75 s | Servo moves 10° each step                     |
| 4     | 1 s    | Green LED and LCD blinking, countdown step    |
| 10    | 2.5 s  | DHT11 reading period                          |
| 12    | 3 s    | Yellow LED duration                           |
| 20    | 5 s    | Exit delay before intrusion monitoring starts |

###### 4. Data variables

| Variable       | Description                                                  |
| -------------- | ------------------------------------------------------------ |
| `temp`, `humi` | Last valid temperature and humidity from the DHT11           |
| `light_value`  | Light sensor ADC value (updated by the ADC ISR every 125 ms) |
| `pot_value`    | Potentiometer ADC value, used as the darkness threshold      |
| `angle`        | Current window angle                                         |
| `pulsewidth`   | Servo PWM pulse width calculated from `angle`                |
| `err`          | Return value of the DHT11 and I2C functions                  |
| `PC_data`      | Last character received through Bluetooth                    |
| `lcd_line`     | Text buffer for one LCD line                                 |

**Mode Logic**

The system has three modes: HOME, AWAY, and ALARM. Mode transitions are controlled by button inputs, PIR detection, and Bluetooth command inputs. (In AWAY mode, PIR detection is ignored during the first 5 seconds)

<p align="center">
  <img src="./img/StateTable_Mode.png" width="440">
</p>
<p align="center">Table 1. Mode state transition table.</p>

<p align="center">
  <img src="./img/StateDiagram_Mode.png" width="400">
</p>
<p align="center">Figure 3. Mode state transition diagram.</p>

**Ventilation Logic**

Ventilation is controlled by using two states, ON and OFF. Used upper and lower thresholds to prevent frequent switching. (Ventilation is disabled in AWAY and ALARM modes)

<p align="center">
  <img src="./img/StateTable_Vent.png" width="540">
</p>
<p align="center">Table 2. Ventilation state transition table.</p>

<p align="center">
  <img src="./img/StateDiagram_Vent.png" width="470">
</p>
<p align="center">Figure 4. Ventilation state transition diagram.</p>

**Lighting Logic**

The RGB LED output is determined by the current mode and priorities. Unlike mode and ventilation control, lighting control does not involve state transitions. Instead, the LED output changes depending on the conditions.

In HOME mode, the priority is ventilation (green), PIR detection (yellow), and darkness (white). In AWAY and ALARM modes, the LED indicates the exit delay or intrusion warning.

<p align="center">
  <img src="./img/StateTable_Light.png" width="560">
</p>
<p align="center">Table 3. Lighting priority and output table.</p>

##### Code

Bitna Won: https://github.com/bitna-cmd/EC-STM32F4-22400462/blob/main/README.md

Yerin Choi: https://github.com/choie2022/EC-STM32F4-22400741/blob/main/README.md

**void setup(void)**

This function initializes the sensor and output devices need for the system. Fan and servo motor are controlled with PWM, and the photo sensor and potentiometer are measured using the JADC functions. EXTI is used for the button and their PIR sensor. USART2 was used to show messages in the STM window of Tera Term so that we could check the system status, and USART6 was initialized for Bluetooth communication. TIM1 was set to a 250 ms period and used as the base timer for the control loop.



```c
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
```

**TIM1_UP_TIM10_IRQHandler()**

The TIM1 update interrupt increases current_count every 250 ms. This counter was used to calculate the operating time of each function. Every 10 counts, dht_flag is updated so that the DHT11 is measured every 2.5 seconds. The ventilation function and the LED control function are also run periodically in this interrupt.

```c
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
```

##### **int main(void)**

The main function checks for changes in the mode and the ventilation state and shows them on the serial monitor. It also updates the LCD display and measures the temperature and humidity. The variables previous_mode and previous_vent store the previous states, so a Bluetooth message is sent when a state changes. The DHT11 is measured only when dht_flag is 1. This happens every time current_count increases by 10, which is every 2.5 seconds. If the DHT11 reading is successful, the temperature and humidity values are updated. If the reading fails, a reading error message is printed and the previous values are kept..

```c
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
```

**void EXTI15_10_IRQHandler(void)**

The falling edge of the button input is used to switch between HOME and AWAY mode. When the mode changes from HOME to AWAY, exit_count is updated so that intrusion can be detected starting 5 seconds after leaving. When the button is pressed in AWAY or ALARM mode, the system returns to HOME, and the existing intrusion and motion detection flags are reset.

```c
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
```

**void EXTI3_IRQHandler(void )**

The PIR sensor detects motion using a rising edge interrupt. In HOME mode, when motion is detected, pir_flag is updated and the starting current_count is saved for LED control. In AWAY mode, the system first checks whether 5 seconds have passed since leaving. If motion is detected after that time, intrusion_flag is set and the mode changes to ALARM. This way, the same PIR sensor input leads to different actions depending on the mode.

```c
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
```

**void ADC_IRQHandler(void)**

The JADC functions were used to measure the values of the light sensor and the potentiometer. TIM5 is set to a 125 ms period to start the analog-to-digital conversion, and when the conversion is complete, each value is read and saved. The two measured values are compared in lighting() to turn on the white light, and the potentiometer can be used to adjust the brightness level at which the light turns on.

```c
// Read the current brightness and standard brightness by JADC
void ADC_IRQHandler(void){
    if(is_ADC_JEOC()){
        light_value = JADC_read(1);
        pot_value = JADC_read(2);
        clear_ADC_JEOC();
    }
}
```

**void ventilation(void)**

When the temperature or humidity reaches the upper threshold, the fan starts and vent_flag is set to 1. After that, even if the values drop below the upper threshold, the ventilation stays on until both values fall below the lower threshold. 

The upper thresholds are 30°C for temperature and 55% for humidity, and the lower thresholds are 28°C and 50%.

```c
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
```

The servo motor opens and closes the window using the PWM signal from TIM3. In the control loop that runs every 250 ms, the angle changes by 10° every 3 counts, and the PWM pulse width for that angle is calculated. In AWAY and ALARM mode, the fan stops and the window closes.

```c
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
```

**void lighting(void)**

The RGB LED shows different colors depending on the system state. Since several conditions can happen at the same time, the priority in HOME mode was set in this order: ventilation state, PIR detection, and surrounding brightness. When ventilation is running, the green LED blinks every 1 second, and when the PIR sensor detects motion, the yellow LED turns on for about 3 seconds. If neither condition applies and the room is dark, the white LED turns on.

```c
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
}
```

Right after switching to AWAY mode, the yellow LED turns on for 3 seconds, and if an intrusion happens after that, the red LED blinks. The starting time of each action is saved separately and compared with the current count to control how long each action lasts.

```c
else if (mode == AWAY || mode == ALARM){
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
```

**void lcd(void)**

The LCD shows different information depending on the current mode. In HOME mode, it displays the temperature and humidity, and it also shows VENT while ventilation is running. In AWAY mode, it shows a countdown for 5 seconds after leaving, and in ALARM mode, it displays MODE: ALARM and an INTRUDER message. The warning message blinks every 1 second based on intrusion_count.

```c
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
```

**void USART6_IRQHandler(void)**

USART6 was used for Bluetooth communication. When a character is received through Bluetooth, it is read and echoed to both USART2 and USART6. Also, when ‘O’ or ‘o’ is received in ALARM mode, the intrusion alarm is turned off and the system returns to AWAY mode. This made it possible to turn off the alarm remotely through Bluetooth.

```c
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
```

**void send_status(void)**

The send_status() function sends status change messages to Bluetooth through USART6. This function is called in the state change detection part of main() to report information such as mode changes and when ventilation starts and stops.

```c
// Send message to display on bluetooth (tera term)
void send_status(const char *msg){
    // Bluetooth
    USART_write(USART6, (uint8_t*)msg, strlen(msg));
}
```

**void all_led_off(void)**

A separate function was written to set all RGB LED outputs to LOW. This function is called when the LED control condition changes or when the light needs to be turned off, so that the previous LED state does not remain. Because one RGB LED is used to show several colors, it was necessary to reset the state of each color.

```c
// Turn off all LED (R,G,B)
void all_led_off(void){
    GPIO_write(LED_R, LOW);
    GPIO_write(LED_G, LOW);
    GPIO_write(LED_B, LOW);
    return;
}
```

**Summary**

The whole system runs based on the 250 ms TIM1 interrupt. Each function is controlled using sensor interrupts and state flags. The PIR sensor and the button are handled with external interrupts, and the light sensor is measured periodically using JADC. Temperature and humidity are measured separately in the main loop, so the waiting time during the DHT11 reading does not directly affect the timer interrupt. The HOME, AWAY, and ALARM modes and state variables such as vent_flag, pir_flag, and intrusion_flag connect the sensor inputs to the output devices. As a result, even when several functions are needed at the same time, the system works according to the set conditions and priorities.

### V. Results and Analysis

-----

##### Results

|                                                   |                                                          |
| :-----------------------------------------------: | :------------------------------------------------------: |
| <img src="./img/Initial_cleared.png" width="250"> | <img src="./img/Light_Yellow_by_Motion.png" width="250"> |
|        (a) Initial HOME state with LED off        |        (b) Yellow LED during PIR motion detection        |
| <img src="./img/Light_White_OFF.png" width="250"> |     <img src="./img/Light_White_ON.png" width="250">     |
|    (c) White LED off under sufficient lighting    |        (d) White LED on when darkness is detected        |

<p align="center">Figure 5. HOME mode lighting responses</p>

|                                                              |                                                              |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| <img src="./img/Light_Green_Over_TRSH_UPPER.png" width="250"> | <img src="./img/Light_Green_Over_TRSH_LOWER.png" width="250"> |
|      (a) Green LED activated above the upper threshold       |     (b) Ventilation maintained above the lower threshold     |
| <img src="./img/Light_Green_Under_TRSH_LOWER.png" width="250"> |       <img src="./img/Window_Closed.png" width="250">        |
|         (c) Green LED off below the lower thresholds         |       (d) Servo window closed after ventilation stops        |
| <img src="./img/Vent_Fan_ON_Over_TRSH_UPPER.png" width="250"> | <img src="./img/Vent_Fan_ON_Over_TRSH_LOWER.png" width="250"> |
| (e) Ventilation ON above the upper threshold. | (f) Ventilation remains ON above the lower threshold. |
| <img src="./img/Vent_Fan_OFF_Under_TRSH_LOWER.png" width="250"> | |
| (g) Ventilation OFF below the lower thresholds. | |

<p align="center">Figure 6. Ventilation control</p>

|                                                              |                                                              |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| <img src="./img/Light_Yellow_by_Exit_N_Count5.png" width="250"> | <img src="./img/Light_Yellow_by_Exit_N_Count4.png" width="250"> |
|          (a) AWAY countdown at 5 s with yellow LED           |          (b) AWAY countdown at 4 s with yellow LED           |
| <img src="./img/Light_Yellow_by_Exit_N_Count3.png" width="250"> | <img src="./img/Light_Yellow_OFF_N_After_Exit_Count2.png" width="250"> |
|          (c) AWAY countdown at 3 s with yellow LED           |        (d) AWAY countdown at 2 s with yellow LED off         |
|     <img src="./img/After_Exit_Count1.png" width="250">      |    <img src="./img/ALARM_Intrusion_OFF.png" width="250">     |
|                  (e) AWAY countdown at 1 s                   |       (f) AWAY mode without an active intrusion alarm        |

<p align="center">Figure 7. AWAY mode countdown and exit delay</p>

|                                                              |                                                             |
| :----------------------------------------------------------: | :---------------------------------------------------------: |
|  <img src="./img/ALARM_Intrusion_Blink_ON.png" width="250">  | <img src="./img/ALARM_Intrusion_Blink_OFF.png" width="250"> |
|         (a) Red LED on during the intrusion warning          |          (b) Red LED off during the blinking cycle          |
| <img src="./img/ALARM_OFF_by_Switch_to_HOME.png" width="250"> |     <img src="./img/BT_ALARM_TO_HOME.png" width="250">      |
|           (c) ALARM cleared by pressing the button           |    (d) Serial message after switching from ALARM to HOME    |

<p align="center">Figure 8. Intrusion alarm indication and return to HOME.</p>

|                                           |                                                     |
| :---------------------------------------: | :-------------------------------------------------: |
| <img src="./img/BT_VENT.png" width="250"> |  <img src="./img/BT_ALARM_CLEAR.png" width="250">   |
|  (a) Ventilation ON/OFF status messages.  | (b) Alarm cleared with the Bluetooth 'O/o' command. |

<p align="center">Figure 9. Bluetooth status and alarm cleared messages.</p>

**Demo Video: [[EC26] Project1 SmartHOME](https://youtu.be/4G_vAPCNfbs)**

##### Analysis

| Function    | Condition                    | Expected                                | Observed                                                     |
| ----------- | ---------------------------- | --------------------------------------- | ------------------------------------------------------------ |
| Lighting    | HOME, motion at entrance     | Yellow LED for 3 s                      | Motion detected more sensitive than expected, therefore light turned on more frequently. |
|             | HOME, dark                   | White LED on                            | Yellow light was turned on during testing because of PIR sensor in the beginning. |
|             | Ventilation running          | Green LED blinks every 1 s              | Same as expected.                                            |
|             | ALARM                        | Red LED blinks every 0.5 s              | Same as expected.                                            |
| Ventilation | Temp ≥ 30 °C or humi ≥ 55 %  | Fan on, window opens                    | Same as expected.                                            |
|             | Temp < 28 °C and humi < 50 % | Fan off, window closes                  | Same as expected.                                            |
|             | Between thresholds           | Keeps previous state                    | Same as expected.                                            |
| Button      | Pressed in HOME              | Changes to AWAY, 5 s countdown          | Same as expected.                                            |
|             | Pressed in AWAY / ALARM      | Changes to HOME                         | Same as expected.                                            |
| Intrusion   | Motion during countdown      | Ignored                                 | Same as expected.                                            |
|             | Motion after countdown       | ALARM                                   | Same as expected.                                            |
| Bluetooth   | `o` sent in ALARM            | Returns to AWAY                         | Same as expected.                                            |
|             | Mode or vent changes         | Status message on terminal              | Same as expected.                                            |
| LCD         | HOME                         | Temp, humi, `MODE: HOME` (`VENT` if on) | Same as expected.                                            |
|             | AWAY                         | `MODE: AWAY` + countdown                | Same as expected.                                            |
|             | ALARM                        | `MODE: ALARM`, `INTRUDER` blinking      | Had display problems due to counter setting and lcd condition in the beginning. |
| DHT11       | Sensor disconnected          | Error message, last value kept          | Same as expected.                                            |

##### Discussions

1. Lighting priority: The system has only one RGB LED, so different conditions can ask for different colors at the same time. To prevent conflicts, we decided on a fixed priority order. In the code, this order is set by the sequence of the if - else chain inside the lighting() function, so only one color can be chosen in each control cycle.
2. Trouble - shooting
    1) Upload failure
    The code built successfully, but the upload failed with the error `unable to connect to the target`. The old program kept running on the board, and the motor was still spinning. The ST-Link debugger could not connect to the microcontroller while it was running. According to our professor, this may have been caused by a voltage difference between the connected boards. We turned off the power, unplugged all the cables, and reconnected them. We also uploaded the code while holding down the RESET button on the expansion board.

  2) Printing stopped and interrupts repeated endlessly (Bluetooth not connected)
   The `printf` output appeared once or twice and then stopped completely. When we connected the Bluetooth module, printing worked normally again. Without the Bluetooth module, the USART6 receive pin was left floating. Electrical noise or an overrun error probably caused the USART6 interrupt to trigger again and again. Since the processor kept running the interrupt handler, the main loop never got a chance to run, so `printf` was never reached. We connected the Bluetooth module so that the receive line stayed in a stable idle state. We learned that when an interrupt is enabled for a peripheral, we also need to pay attention to the state of its input pins and its error flags.

  3) Overlapping timers due to a shared counter
   Timed actions, such as the 3 second yellow light, the 5 second exit delay, and the alarm blinking, overlapped with each other and did not behave as expected. Several events used the same starting count. In addition, the PIR interrupt saved the starting time and then immediately checked how much time had passed, so the result was always zero. We gave each event its own starting count (`pir_start_count`, `exit_count`, and `intrusion_count`). We also moved the starting point of the exit delay to the moment the button is pressed. We learned that "When to start counting" and "how much time has passed" must be tracked separately for each event. We also learned that clearing the interrupt pending flag is essential. If it is not cleared, the interrupt handler runs again immediately and never stops.

3. Takeaways
- Using timers: We learned how to use a timer interrupt. TIM1 creates an interrupt every 250 ms, and each time it does, `current_count` increases by one. By subtracting a starting count from the current count, we can measure how much time has passed. For example, 12 ticks x 250 ms = 3 seconds. This let us handle several timed actions at once without using `delay()`, which would have stopped the whole program while waiting.
- Reading header files: Even when we were not familiar with a library, we could still use it by reading its header file. The header file shows each function's name, its inputs, and what it returns.

### VI. Reference

[LAB: GPIO Digital InOut](https://ykkim.gitbook.io/ec/ec-course/lab/lab-gpio-digital-inout-eval)

[Smart Home Management System](https://ykkimhgu.github.io/EC-STM32F4-Book/chapters/ch18-project/07-smart-home.html)

### Appendix

-----

1. Additional Library

**DHT11 API:** `ecDHT11.h`

- [Example Code for DHT](https://github.com/ykkimhgu/EC-student/blob/main/tutorial/tutorial-student/TU_DHT11.c)
- `DHT11_read()` blocks for about 25 ms, of which roughly 5 ms runs with interrupts off.
- `DHT11_read()` was called from `main()`, not from an interrupt handler.
- The system treats `DHT11_ERR_CHECKSUM` and `DHT11_ERR_NO_REPLY` as invalid readings. When an error occurs, the system keeps the last valid temperature and humidity values, reports the error, and increments the `dht_error_count` variable.
- During normal operation, no DHT11 reading errors were observed (error count: 0). However, when the DHT11 sensor was intentionally disconnected, an error message was displayed, and the error count increased and was printed.

**I2C2 API:** `ecI2C2.h`

- [Example Code for I2C LCD](https://github.com/ykkimhgu/EC-student/blob/main/tutorial/tutorial-student/TU_I2C_LCD.c)
