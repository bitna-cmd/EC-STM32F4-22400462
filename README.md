# Tutorial: Documentation

## Tutorial: Documentation

## EC API Documentation

[See Class Github](https://github.com/ykkimhgu/EC-student/blob/main/docs/EC_HAL_Documentation.md) for the example documentation

[See Tutorial: Documentation with Markdown](https://ykkim.gitbook.io/ec/numerical-programming/ta-tutorial/tutorial-documentation-with-markdown#preparation)

### Embedded Controller - STM32F411 Driver Library

Written by: Won Bitna

Program: C/C++

IDE/Compiler: Keil uVision 5

OS: WIn10/11

MCU: STM32F411RE, Nucleo-64

**Table of Contents**

* [ecGPIO2](#ecgpio2)
  * [Header File](#header-file)
  * [GPIO_init()](#gpio_init)
  * [GPIO_mode()](#gpio_mode)
  * [GPIO_ospeed()](#gpio_ospeed)
  * [GPIO_otype()](#gpio_otype)
  * [GPIO_pupd()](#gpio_pupd)
  * [GPIO_write()](#gpio_write)
  * [GPIO_read()](#gpio_read)
  * [GPIO_init_all()](#gpio_init_all)
  * [pinMode()](#pinmode)
  * [digitalWrite()](#digitalwrite)
  * [digitalRead()](#digitalread)
  * [FND_init()](#fnd_init)
  * [FND_select_init()](#fnd_select_init)
  * [FND_display()](#fnd_display)
  * [FND_select()](#fnd_select)
  * [led_toggle()](#led_toggle)
* [ecRCC2](#ecrcc2)
  * [Header File](#header-file-1)
  * [delay_ms_HSI()](#delay_ms_hsi)
  * [RCC_HSI_init()](#rcc_hsi_init)
  * [RCC_PLL_init()](#rcc_pll_init)
  * [RCC_GPIOA_enable()](#rcc_gpioa_enable)
  * [RCC_GPIOB_enable()](#rcc_gpiob_enable)
  * [RCC_GPIOC_enable()](#rcc_gpioc_enable)
  * [RCC_GPIOD_enable()](#rcc_gpiod_enable)
  * [RCC_GPIOE_enable()](#rcc_gpioe_enable)
  * [RCC_GPIOH_enable()](#rcc_gpioh_enable)
* [ecPinNames](#ecpinnames)
  * [Header File](#header-file-2)
  * [ecPinmap()](#ecpinmap)
* [ecEXTI2](#ecexti2)
  * [Header File](#header-file-3)
  * [EXTI_init()](#exti_init)
  * [EXTI_disable()](#exti_disable)
  * [is_pending_EXTI()](#is_pending_exti)
  * [clear_pending_EXTI](#clear_pending_exti)
* [ecStepper2](#ecstepper2)
  * [Header File](#header-file-4)
  * [stepper_init()](#stepper_init)
  * [stepper_speed()](#stepper_speed)
  * [stepper_step()](#stepper_step)
  * [stepper_out()](#stepper_out)
  * [stepper_stop()](#stepper_stop)
* [ecSysTick2](#ecsystick2)
  * [Header File](#header-file-5)
  * [SysTick_init()](#systick_init)
  * [SysTick_Handler()](#systick_handler)
  * [SysTick_counter()](#systick_counter)
  * [delay_ms()](#delay_ms)
  * [delay_us](#delay_us)
  * [SysTick_reset()](#systick_reset)
  * [SysTick_val()](#systick_val)
* [ecUART2](#ecuart2)
  * [Header File](#header-file-6)
  * [USART_init()](#usart_init)
  * [USART_baud()](#usart_baud)
  * [USART_pins()](#usart_pins)
  * [USART1_baud()](#usart1_baud)
  * [USART2_baud()](#usart2_baud)
  * [USART1_init()](#usart1_init)
  * [USART2_init()](#usart2_init)
  * [USART1_write()](#usart1_write)
  * [USART2_write()](#usart2_write)
  * [USART1_read()](#usart1_read)
  * [USART2_read()](#usart2_read)
  * [is_USART1_RXNE()](#is_usart1_rxne)
  * [is_USART2_RXNE()](#is_usart2_rxne)
  * [USART_clock_enable()](#usart_clock_enable)
  * [USART_write()](#usart_write)
  * [USART_read()](#usart_read)
  * [is_USART_RXNE()](#is_usart_rxne)
  * [USART_delay()](#usart_delay)
* [ecTIM2](#ectim2)
  * [Header File](#header-file-7)
  * [TIM_UI_init()](#tim_ui_init)
  * [TIM_UI_init_us()](#tim_ui_init_us)
  * [TIM_UI_enable()](#tim_ui_enable)
  * [TIM_UI_disable()](#tim_ui_disable)
  * [is_UIF()](#is_uif)
  * [clear_UIF()](#clear_uif)
  * [TIM_init()](#tim_init)
  * [TIM_init_us()](#tim_init_us)
  * [TIM_period()](#tim_period)
  * [TIM_period_us()](#tim_period_us)
  * [TIM_clock_enable()](#tim_clock_enable)
  * [get_TIM_IRQn()](#get_tim_irqn)
* [ecPWM2](#ecpwm2)
  * [Header File](#header-file-8)
  * [PWM_init_config()](#pwm_init_config)
  * [PWM_duty()](#pwm_duty)
  * [PWM_init()](#pwm_init)
  * [PWM_init_us()](#pwm_init_us)
  * [PWM_pulsewidth()](#pwm_pulsewidth)
  * [PWM_pulsewidth_us()](#pwm_pulsewidth_us)
  * [PWM_mode_config()](#pwm_mode_config)
  * [PWM_pinmap()](#pwm_pinmap)
* [ecADC2](#ecadc2)
  * [Header File](#header-file-9)
  * [ADC_init()](#adc_init)
  * [ADC_read_poll()](#adc_read_poll)
  * [ADC_read()](#adc_read)
  * [ADC_trigger_init()](#adc_trigger_init)
  * [JADC_init()](#jadc_init)
  * [JADC_read_poll()](#jadc_read_poll)
  * [JADC_read()](#jadc_read)
  * [JADC_trigger_init()](#jadc_trigger_init)
  * [ADC_EOC_enable()](#adc_eoc_enable)
  * [ADC_EOC_disable()](#adc_eoc_disable)
  * [ADC_start()](#adc_start)
  * [ADC_stop()](#adc_stop)
  * [ADC_sequence()](#adc_sequence)
  * [ADC_conversion()](#adc_conversion)
  * [is_ADC_EOC()](#is_adc_eoc)
  * [clear_ADC_EOC()](#clear_adc_eoc)
  * [is_ADC_OVR()](#is_adc_ovr)
  * [clear_ADC_OVR()](#clear_adc_ovr)
  * [JADC_JEOC_enable()](#jadc_jeoc_enable)
  * [JADC_JEOC_disable()](#jadc_jeoc_disable)
  * [JADC_start()](#jadc_start)
  * [JADC_sequence()](#jadc_sequence)
  * [is_ADC_JEOC()](#is_adc_jeoc)
  * [clear_ADC_JEOC()](#clear_adc_jeoc)
  * [ADC_pinmap()](#adc_pinmap)
* [ecICAP2](#ecicap2)
  * [Header File](#header-file-10)
  * [ICAP_init()](#icap_init)
  * [ICAP_ICn_init()](#icap_icn_init)
  * [ICAP_tick()](#icap_tick)
  * [ICAP_read()](#icap_read)
  * [is_CCIF()](#is_ccif)
  * [clear_CCIF()](#clear_ccif)
  * [ICAP_pinmap()](#icap_pinmap)
  * [ICAP_filter()](#icap_filter)
  * [ICAP_ICn_select()](#icap_icn_select)
* [ecI2C2](#eci2c2)
  * [Header File](#header-file-11)
  * [I2C1_init()](#i2c1_init)
  * [I2C2_init()](#i2c2_init)
  * [I2C3_init()](#i2c3_init)
  * [I2C1_write()](#i2c1_write)
  * [I2C2_write()](#i2c2_write)
  * [I2C3_write()](#i2c3_write)
  * [I2C1_read()](#i2c1_read)
  * [I2C2_read()](#i2c2_read)
  * [I2C3_read()](#i2c3_read)
  * [LCD_init()](#lcd_init)
  * [LCD_command()](#lcd_command)
  * [LCD_data()](#lcd_data)
  * [LCD_print()](#lcd_print)
  * [LCD_setCursor()](#lcd_setcursor)
* [ecDHT11](#ecdht11)
  * [Header File](#header-file-12)
  * [DHT11_init()](#dht11_init)
  * [DHT11_read()](#dht11_read)
  * [DHT11_temperature()](#dht11_temperature)
  * [DHT11_humidity()](#dht11_humidity)
* [ecSTM32F4v2](#ecstm32f4v2)
  * [Header File](#header-file-13)
  * [MCU_init()](#mcu_init)

---


### ecGPIO2

#### Header File

`#include "ecGPIO2.h"`

```c
// GPIO modes (MODER)
#define INPUT       0x00
#define OUTPUT      0x01
#define AF          0x02
#define ANALOG      0x03

// Input and output levels (IDR / ODR)
#define HIGH        1
#define LOW         0

// Output speed (OSPEEDR)
#define LOW_SPEED   0x00
#define MIDEUM_SPEED   0x01
#define FAST_SPEED  0x02
#define HIGH_SPEED  0x03

// Output type (OTYPER)
#define PUSH_PULL   0
#define OPEN_DRAIN  1

// Pull-up / pull-down (PUPDR)
#define NO_PUPD     0x00
#define PULL_UP     0x01
#define PULL_DOWN   0x02
#define RESERVED    0x03

// Pin numbers
#define LED_PIN     5
#define BUTTON_PIN  13

// GPIO digital input/output
void GPIO_init(PinName_t pinName, uint32_t mode);
void GPIO_mode(PinName_t pinName, uint32_t mode);
void GPIO_ospeed(PinName_t pinName, uint32_t speed);
void GPIO_otype(PinName_t pinName, uint32_t type);
void GPIO_pupd(PinName_t pinName, uint32_t pupd);
void GPIO_write(PinName_t pinName, uint32_t Output);
uint32_t GPIO_read(PinName_t pinName);
void GPIO_init_all(PinName_t pinName, uint32_t mode, uint32_t speed, uint32_t type, uint32_t pupd);

// Arduino-style API (optional)
void pinMode(PinName_t pin, uint32_t mode);
void digitalWrite(PinName_t pin, uint32_t value);
uint32_t digitalRead(PinName_t pin);

// FND (7-segment display) for JKIT board
extern int numberFND[12][8];
void FND_init(PinName_t *pinFND);
void FND_select_init(PinName_t *selectFND);
void FND_display(uint8_t num);
void FND_select(uint8_t digit);

// Toggle GPIO output
void led_toggle(PinName_t pinName);
```

#### GPIO_init()

Initializes a GPIO pin with the selected mode and enables the corresponding GPIO port clock.

```c
void GPIO_init(PinName_t pinName, uint32_t mode);
```

**Parameters**

* **pinName**: GPIO pin name (e.g., PA_5, PC_13).
* **mode**: GPIO mode: INPUT(0), OUTPUT(1), AF(2), ANALOG(3).

**Example Code**

```c
GPIO_init(PA_5, OUTPUT); // PA5 as output
GPIO_init(PC_13, INPUT); // PC13 as input
```

#### GPIO_mode()

Changes the operating mode of a GPIO pin to input, output, alternate function, or analog.

```c
void GPIO_mode(PinName_t pinName, uint32_t mode);
```

**Parameters**

* **pinName**: GPIO pin name (e.g., PA_5).
* **mode**: GPIO mode: INPUT(0), OUTPUT(1), AF(2), ANALOG(3).

**Example Code**

```c
GPIO_init(PA_5, OUTPUT);
GPIO_mode(PA_5, AF); // Change PA5 to alternate-function mode
```

#### GPIO_ospeed()

Sets the GPIO output speed through the OSPEEDR register.

```c
void GPIO_ospeed(PinName_t pinName, uint32_t speed);
```

**Parameters**

* **pinName**: GPIO pin name.
* **speed**: LOW_SPEED(0), MID_SPEED(1), FAST_SPEED(2), or HIGH_SPEED(3).

**Example Code**

```c
GPIO_init(PA_5, OUTPUT);
GPIO_ospeed(PA_5, FAST_SPEED);
```

#### GPIO_otype()

Sets the GPIO output type to push-pull or open-drain.

```c
void GPIO_otype(PinName_t pinName, uint32_t type);
```

**Parameters**

* **pinName**: GPIO pin name.
* **type**: PUSH_PULL(0) or OPEN_DRAIN(1).

**Example Code**

```c
GPIO_init(PA_5, OUTPUT);
GPIO_otype(PA_5, PUSH_PULL);
```

#### GPIO_pupd()

Configures the GPIO internal pull-up/pull-down resistors.

```c
void GPIO_pupd(PinName_t pinName, uint32_t pupd);
```

**Parameters**

* **pinName**: GPIO pin name.
* **pupd**: NO_PUPD(0), PULL_UP(1), PULL_DOWN(2), or RESERVED(3).

**Example Code**

```c
GPIO_init(PC_13, INPUT);
GPIO_pupd(PC_13, PULL_UP);
```

#### GPIO_write()

Writes a HIGH or LOW output level to the selected GPIO pin.

```c
// Write output on the pin (output: HIGH, LOW)
void GPIO_write(PinName_t pinName, uint32_t Output){
    GPIO_TypeDef *port;
    unsigned int pin;
    ecPinmap(pinName, &port, &pin);

    if(Output == 1)
        port->ODR |= (1UL << pin);
    else
        port->ODR &= ~(1UL << pin);
}
```

**Parameters**

* **pinName**: GPIO pin name (e.g., PA_5).
* **Output**: HIGH(1) or LOW(0).

**Example Code**

```c
GPIO_init(PA_5, OUTPUT);
GPIO_write(PA_5, HIGH);
```

#### GPIO_read()

Reads and returns the logic level of the selected GPIO input pin.

```c
// Read and return the input value through the pin
uint32_t GPIO_read(PinName_t pinName){
    GPIO_TypeDef *Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);

    uint32_t reVal = (Port->IDR >> pin) & 1UL;
    return reVal;
}
```

**Parameters**

* **pinName**: GPIO pin name (e.g., PC_13).

**Returns**

* Current pin logic level: LOW(0) or HIGH(1).

**Example Code**

```c
GPIO_init(PC_13, INPUT);
uint32_t val = GPIO_read(PC_13);
```

#### GPIO_init_all()

Configures GPIO mode, output speed, output type, and pull-up/pull-down setting in one call.

```c
// Initialize the pin mode, speed, type and pull-up/down at once
// mode: INPUT, OUTPUT, AF, ANALOG
// speed: LOW_SPEED, MID_SPEED, FAST_SPEED, HIGH_SPEED
// type: OPEN_DRAIN, PUSH_PULL
// pupd: NO_PUPD, PULL_UP, PULL_DOWN, RESERVED
void GPIO_init_all(PinName_t pinName, uint32_t mode, uint32_t speed, uint32_t type, uint32_t pupd){
    GPIO_TypeDef *Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);

    GPIO_init(pinName, mode);
    GPIO_ospeed(pinName, speed);
    GPIO_otype(pinName, type);
    GPIO_pupd(pinName, pupd);
}
```

**Parameters**

* **pinName**: GPIO pin name.
* **mode**: INPUT(0), OUTPUT(1), AF(2), or ANALOG(3).
* **speed**: LOW_SPEED(0), MID_SPEED(1), FAST_SPEED(2), or HIGH_SPEED(3).
* **type**: PUSH_PULL(0) or OPEN_DRAIN(1).
* **pupd**: NO_PUPD(0), PULL_UP(1), PULL_DOWN(2), or RESERVED(3).

**Example Code**

```c
GPIO_init_all(PA_5, OUTPUT, MID_SPEED, PUSH_PULL, NO_PUPD);
```

#### pinMode()

Arduino-style wrapper for GPIO initialization.

```c
void pinMode(PinName_t pin, uint32_t mode){
    GPIO_init(pin, mode);
}
```

**Parameters**

* **pin**: GPIO pin name.
* **mode**: INPUT(0), OUTPUT(1), AF(2), or ANALOG(3).

**Example Code**

```c
pinMode(PA_5, OUTPUT);
```

#### digitalWrite()

Arduino-style wrapper for writing a GPIO output level.

```c
void digitalWrite(PinName_t pin, uint32_t value){
    GPIO_write(pin, value);
}
```

**Parameters**

* **pin**: GPIO pin name.
* **value**: HIGH(1) or LOW(0).

**Example Code**

```c
pinMode(PA_5, OUTPUT);
digitalWrite(PA_5, HIGH);
```

#### digitalRead()

Arduino-style wrapper for reading a GPIO input level.

```c
uint32_t digitalRead(PinName_t pin){
    uint32_t reVal = GPIO_read(pin);
    return reVal;
}
```

**Parameters**

* **pin**: GPIO pin name.

**Returns**

* Current pin logic level: LOW(0) or HIGH(1).

**Example Code**

```c
pinMode(PC_13, INPUT);
uint32_t val = digitalRead(PC_13);
```

#### FND_init()

Initializes the eight GPIO output pins connected to the 7-segment display segments.

```c
// Initialize DOUT pins for 7-segment LEDs
void FND_init(PinName_t *pinFND){
    for (int i = 0; i < 8; i++){
        _fndPins[i] = pinFND[i];
        GPIO_init(_fndPins[i], OUTPUT);
    }
}
```

**Parameters**

* **pinFND**: Array of eight GPIO pin names for FND segments.

**Example Code**

```c
// pinFND must contain eight GPIO pin names selected for the board.
FND_init(pinFND);
```

#### FND_select_init()

Initializes four GPIO output pins used to select one of the four FND digits.

```c
// Initialize select pins (FND0–FND3) as digital outputs
void FND_select_init(PinName_t *selectFND){
    for (int i = 0; i < 4; i++){
        _fndSel[i] = selectFND[i];
        GPIO_init(_fndSel[i], OUTPUT);
    }
}
```

**Parameters**

* **selectFND**: Array of four GPIO pin names for FND digit selection.

**Example Code**

```c
// selectFND must contain four GPIO pin names selected for the board.
FND_select_init(selectFND);
```

#### FND_display()

Outputs the segment pattern for the given number on the 7-segment display.

```c
// Display a number 0–9 only on a 7-segment display
void FND_display(uint8_t num){
    for(int i = 0; i < 8; i++){
        GPIO_write(_fndPins[i], numberFND[num][i]);
    }
}
```

**Parameters**

* **num**: Number to display (0–9).

**Example Code**

```c
FND_display(5); // Display digit 5
```

#### FND_select()

Selects an FND digit (0–3) by setting its selection pin HIGH and the others LOW.

```c
// Select display: FND0 to FND3
void FND_select(uint8_t digit){
    for(int i = 0; i < 4; i++){
        if(i == digit)
            GPIO_write(_fndSel[i], HIGH);
        else
            GPIO_write(_fndSel[i], LOW);
    }
}
```

**Parameters**

* **digit**: Index of the FND digit to select (0–3).

**Example Code**

```c
FND_select(0); // Select the first digit
```

#### led_toggle()

Toggles the logic level of the selected GPIO output pin.

```c
// Toggle the output level
void led_toggle(PinName_t pinName){
    GPIO_TypeDef *Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);

    Port->ODR ^= (1UL << pin);
}
```

**Parameters**

* **pinName**: GPIO output pin name.

**Example Code**

```c
GPIO_init(PA_5, OUTPUT);
led_toggle(PA_5);
```



***

### ecRCC2

#### Header File

`#include "ecRCC2.h"`

```c
extern volatile int EC_SYSCLK;		// current SYSCLK [Hz], set by RCC_HSI_init()/RCC_PLL_init()
void delay_ms_HSI(uint32_t ms); 
void RCC_HSI_init(void);
void RCC_PLL_init(void);
void RCC_GPIOA_enable(void);
void RCC_GPIOB_enable(void);
void RCC_GPIOC_enable(void);
void RCC_GPIOD_enable(void);
void RCC_GPIOE_enable(void);
void RCC_GPIOH_enable(void);
```


#### delay_ms_HSI()

```c
void delay_ms_HSI(uint32_t ms) {
	//uint32_t EC_SYSCLK=16000000;
	volatile uint32_t cnt = ((uint32_t)EC_SYSCLK / (1000UL * 6)) * ms;
	while (cnt > 0) cnt--;
}
```

**Parameters**

* **ms**: delay time in millisecond unit

**Example Code**

```c
delay_ms_HSI(15);
```


#### RCC_HSI_init()

```c
void RCC_HSI_init() {
// Enable High Speed Internal Clock (HSI = 16 MHz)
  //RCC->CR |= ((uint32_t)RCC_CR_HSION);
	RCC->CR |= 0x00000001U;
	
  // wait until HSI is ready
  //while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}
	while ( (RCC->CR & 0x00000002U) == 0 ) {;}
	
  // Select HSI as system clock source 
  	RCC->CFGR &= (uint32_t)(~RCC_CFGR_SW); 								// not essential
  	RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI; 								//00: HSI16 oscillator used as system clock

	// Wait till HSI is used as system clock source
  	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != 0 ) {;}  

	EC_SYSCLK=16000000;	
}
```

**Parameters**
none

**Example Code**

```c
RCC_HSI_init();
```


#### RCC_PLL_init()

```c
// Initialize system clock to 84 MHz using PLL
void RCC_PLL_init() {	
	// To correctly read data from FLASH memory, the number of wait states (LATENCY)
  // must be correctly programmed according to the frequency of the CPU clock
  // (HCLK) and the supply voltage of the device.		
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |=  FLASH_ACR_LATENCY_2WS;
		
	// Enable the Internal High Speed oscillator (HSI)
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);
	
	// Disable PLL for configuration
	RCC->CR    &= ~RCC_CR_PLLON;
	
	// Select clock source to PLL
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC; 		// Set source for PLL: clear bits
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI; // Set source for PLL: 0 =HSI, 1 = HSE
	
	// Make PLL as 84 MHz
	// f(VCO clock) = f(PLL clock input) * (PLLN / PLLM) = 16MHz * 84/8 = 168 MHz
	// f(PLL_R) = f(VCO clock) / PLLP = 168MHz/2 = 84MHz
	RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLN) | 84U << 6;
	RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLM) | 8U ; 
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;  // 00: PLLP = 2, 01: PLLP = 4, 10: PLLP = 6, 11: PLLP = 8	
	
	
	// Enable PLL after configuration
	RCC->CR   |= RCC_CR_PLLON; 
	while((RCC->CR & RCC_CR_PLLRDY)>>25 != 0);
	
	// Select PLL as system clock
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	
	// Wait until System Clock has been selected
	while ((RCC->CFGR & RCC_CFGR_SWS) != 8UL);
	
	// The maximum frequency of the AHB and APB2 is 100MHz,
	// The maximum frequency of the APB1 is 50 MHz.
	RCC->CFGR &= ~RCC_CFGR_HPRE;  		// AHB prescaler = 1; SYSCLK not divided (84MHz)
	RCC->CFGR &= ~RCC_CFGR_PPRE1; 		// APB high-speed prescaler (APB1) = 2, HCLK divided by 2 (42MHz)
	RCC->CFGR |=  RCC_CFGR_PPRE1_2;
	RCC->CFGR &= ~RCC_CFGR_PPRE2; 		// APB high-speed prescaler (APB2) = 1, HCLK not divided	(84MHz)
	
	EC_SYSCLK=84000000;
}
```

**Parameters**
none

**Example Code**
```c
RCC_PLL_init();
```


#### RCC_GPIOA_enable()

```c
void RCC_GPIOA_enable()
{
	// RCC Peripheral Clock Enable Register 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}
```

**Parameters**
none

**Example Code**

```c
RCC_GPIOA_enable();
```


#### RCC_GPIOB_enable()

```c
void RCC_GPIOB_enable()
{
	// RCC Peripheral Clock Enable Register 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
}
```

**Parameters**
none

**Example Code**

```c
RCC_GPIOB_enable();
```


#### RCC_GPIOC_enable()

```c
void RCC_GPIOC_enable()
{
	// RCC Peripheral Clock Enable Register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
}
```

**Parameters**
none

**Example Code**

```c
RCC_GPIOC_enable();
```


#### RCC_GPIOD_enable()

```c
void RCC_GPIOD_enable(void){
	// RCC Peripheral Clock Enable Register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
}
```

**Parameters**
none

**Example Code**

```c
RCC_GPIOD_enable();
```


#### RCC_GPIOE_enable()
```c
void RCC_GPIOE_enable(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
}
```


**Parameters**
none

**Example Code**

```c
RCC_GPIOE_enable();
```


#### RCC_GPIOH_enable()

```c
void RCC_GPIOH_enable(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
}
```

**Parameters**
none

**Example Code**

```c
RCC_GPIOH_enable();
```



***

### ecPinNames

#### Header File

`#include "ecPinNames.h"`

```c
// Bitwise Macro Definition
#define BIT_SET(REG, BIT)      	((REG) |= 1<< (BIT))
#define BIT_CLEAR(REG, BIT)     ((REG) &= ~1<<(BIT))
#define BIT_READ(REG, BIT)      ((REG)>>BIT & (1))
#define BITS_SET(REG, BIT,NUM)     ((REG) |= NUM<< (BIT))
#define BITS_CLEAR(REG, BIT,NUM)   ((REG) &= ~(NUM<< (BIT))
//#define BITS_CLEAR(REG, BIT,NUM)   ((REG) &= ~((0x1<< NUM)-1)<<(BIT))


// Pinname Config
typedef enum {
    PortA = 0,
    PortB = 1,
    PortC = 2,
    PortD = 3,
    PortE = 4,
    PortF = 5,
    PortG = 6,
    PortH = 7,
    PortI = 8,
    PortJ = 9,
    PortK = 10
} PortName_t;



typedef enum {
    PA_0  = 0x00,
    PA_1  = 0x01,    
    PA_2  = 0x02,
    PA_3  = 0x03,
    PA_4  = 0x04,    
    PA_5  = 0x05,
    PA_6  = 0x06,
    PA_7  = 0x07,
    PA_8  = 0x08,
    PA_9  = 0x09,
    PA_10 = 0x0A,
    PA_11 = 0x0B,
    PA_12 = 0x0C,
    PA_13 = 0x0D,
    PA_14 = 0x0E,
    PA_15 = 0x0F,
    
    PB_0  = 0x10,
    PB_1  = 0x11,
    PB_2  = 0x12,
    PB_3  = 0x13,
    PB_4  = 0x14,
    PB_5  = 0x15,
    PB_6  = 0x16,
    PB_7  = 0x17,
    PB_8  = 0x18,
    PB_9  = 0x19,
    PB_10 = 0x1A,
    PB_12 = 0x1C,
    PB_13 = 0x1D,
    PB_14 = 0x1E,
    PB_15 = 0x1F,

    PC_0  = 0x20,
    PC_1  = 0x21,
    PC_2  = 0x22,
    PC_3  = 0x23,
    PC_4  = 0x24,
    PC_5  = 0x25,
    PC_6  = 0x26,
    PC_7  = 0x27,
    PC_8  = 0x28,
    PC_9  = 0x29,
    PC_10 = 0x2A,
    PC_11 = 0x2B,
    PC_12 = 0x2C,
    PC_13 = 0x2D,
    PC_14 = 0x2E,
    PC_15 = 0x2F,

    PD_2  = 0x32,

    PH_0  = 0x70,
    PH_1  = 0x71,


    // Arduino connector namings
    A0          = PA_0,
    A1          = PA_1,
    A2          = PA_4,
    A3          = PB_0,
    A4          = PC_1,
    A5          = PC_0,
    D0          = PA_3,
    D1          = PA_2,
    D2          = PA_10,
    D3          = PB_3,
    D4          = PB_5,
    D5          = PB_4,
    D6          = PB_10,
    D7          = PA_8,
    D8          = PA_9,
    D9          = PC_7,
    D10         = PB_6,
    D11         = PA_7,
    D12         = PA_6,
    D13         = PA_5,
    D14         = PB_9,
    D15         = PB_8,


    // Not connected
    NC = (int)0xFFFFFFFF
} PinName_t;


void ecPinmap(PinName_t pinName, GPIO_TypeDef **GPIOx, unsigned int *pin);
```

#### ecPinmap()

```c
void ecPinmap(PinName_t pinName, GPIO_TypeDef **GPIOx, unsigned int *pin)
{
	
	unsigned int pinNum= pinName & (0x000F);
	*pin=pinNum;

	unsigned int portNum=(pinName>>4);
	
	
	if (portNum==0)
		*GPIOx=GPIOA;
	else if (portNum==1)
		*GPIOx=GPIOB;
	else if (portNum==2)
		*GPIOx=GPIOC;
	else if (portNum==3)
		*GPIOx=GPIOD;
	else if (portNum==7)
		*GPIOx=GPIOH;
	else 
		*GPIOx=GPIOA;
}
```

**Parameters**

* **pinName**: pin number (int) 0~15
* **GPIOx**: Pointer to a GPIO port pointer that receives the GPIO port address.
* **pin**: Pointer to a variable that receives the pin number (0–15)

**Example Code**

```c
GPIO_TypeDef *Port;
unsigned int pin;
ecPinmap(PA_4, &Port, &pin)
```

***

### ecEXTI2

#### Header File

`#include "ecEXTI2.h"`

```c
#define FALL 0
#define RISE 1
#define BOTH 2

void EXTI_init(PinName_t pinName, uint32_t trig_type,uint32_t priority);
void EXTI_enable(PinName_t pinName);
void EXTI_disable(PinName_t pinName);
uint32_t is_pending_EXTI(PinName_t pinName);
void clear_pending_EXTI(PinName_t pinName);
```

#### EXTI_init()

```c
// Initialize EXTI with trigger type and interrupt priority
// trig_type: trigger type (FALL(0), RISE(1), BOTH(2))
// priority: Priorities for handling
void EXTI_init(PinName_t pinName, uint32_t trig_type,uint32_t priority){

	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);
	
	// Enable EXTI Clock with SYSCFG controller clock 	
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;		
	

	// Connect EXTI to the GPIO Port_y Pin_x
	// Pin 0~3: EXTICR1 // EXTICR[0]
	// Pin 4~7: EXTICR2 // EXTICR[1]
	// Pin 8~11: EXTICR3 // EXTICR[2]
	// Pin 12~15: EXTICR4 // EXTICR[3]	
	uint32_t EXTICR_port=0;
	if		(Port == GPIOA) EXTICR_port = 0;
	else if	(Port == GPIOB) EXTICR_port = 1;
	else if	(Port == GPIOC) EXTICR_port = 2;
	else if	(Port == GPIOD) EXTICR_port = 3;
	else					EXTICR_port = 4;
	
	SYSCFG->EXTICR[pin/4] &= ~(0xFUL << (pin%4)*4);			// clear 4 bits
	SYSCFG->EXTICR[pin/4] |= (EXTICR_port << (pin%4)*4);			// Set 4 bits
	

	// Select  Trigger edge (RISE, FALL, BOTH)
	if (trig_type == FALL) 		EXTI->FTSR |= 1UL << pin;  // Falling trigger enable 
	else if	(trig_type == RISE) EXTI->RTSR |= 1UL << pin;   // Rising trigger enable 
	else if	(trig_type == BOTH) {			// Both falling/rising trigger enable
		EXTI->RTSR |= (1UL << pin); 
		EXTI->FTSR |= (1UL << pin);
	} 
	
	// Enable EXTI, with Not-Masked Interrupt Request 
	// Not-mask (==Enable) EXTIx
 	EXTI->IMR |= 1UL << pin;
	
	
	// NVIC(IRQ) Setting
	uint32_t EXTI_IRQn = 0;
	if (pin < 5) 		EXTI_IRQn = EXTI0_IRQn + pin;
	else if	(pin < 10) 	EXTI_IRQn = EXTI9_5_IRQn;
	else 				EXTI_IRQn = EXTI15_10_IRQn;
		
	NVIC_SetPriority(EXTI_IRQn, priority);	
	NVIC_EnableIRQ(EXTI_IRQn); 				
}
```


```c
// Enable EXTI interrupt
void EXTI_enable(PinName_t pinName) {
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);
	
	EXTI->IMR |= (1UL << pin);     // not masked (i.e., Interrupt enabled)
}
```

**Parameters**

* **pinName**: * pinName: pin number (int) 0~15
* **trig_type**: Interrupt trigger type: FALL(0), RISE(1), or BOTH(2)
* **priority**: NVIC interrupt priority (lower numerical values indicate higher priority)

**Example Code**

```c
EXTI_init(PA_4, FALL, 5);
```


#### EXTI_disable()

```c
// Disable EXTI interrupt
void EXTI_disable(PinName_t pinName) {
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	EXTI->IMR &= ~(1UL << pin);     // masked (i.e., Interrupt disabled)
}
```

**Parameters**

* **pinName**: * pinName: pin number (int) 0~15

**Example Code**

```c
EXTI_disable(PA_4);
```


#### is_pending_EXTI()

```c
// Check whether EXTI interrupt is pending
uint32_t is_pending_EXTI(PinName_t pinName) {
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	uint32_t EXTI_PRx = (EXTI->PR >> pin) & 1UL;     // read PRx, EXTI pending bit.  Use  (REG>>k & 1) to read.
	return  EXTI_PRx; 	// Return only 0 or 1
}
```

**Parameters**

* **pinName**: * pinName: pin number (int) 0~15

**Example Code**

```c
is_pending_EXTI(PA_4);
```


#### clear_pending_EXTI

```c
// Clear EXTI interrupt pending flag after handling interrupt
void clear_pending_EXTI(PinName_t pinName){
	// Port, Pin Configuration
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);

	// clear by writing 1 to the pending bit
	EXTI->PR  = (1 << pin);     
}

```
**Parameters**

* **pinName**: * pinName: pin number (int) 0~15

**Example Code**

```c
clear_pending_EXTI(PA_4);
```


***

### ecStepper2

#### Header File

`#include "ecStepper2.h"`

```c
// Stepper Mode
#define HALF 0
#define FULL 1	 
#define DIR_CW 0
#define DIR_CCW 1	  
#define MS 0        // millisec
#define US 1        // microsec

// 28BYJ-48 nominal steps per output revolution
// Gear reduction ratio: 64:1
#define FULL_STEP_PER_REV (32UL * 64UL)  // 2048
#define HALF_STEP_PER_REV (64UL * 64UL)  // 4096

// Select the steps per revolution based on the mode
// You should select the stepper motor mode (mode: HALF(0), FULL(1))
#define STEP_PER_REV ((STEPPER_MODE == FULL) ? FULL_STEP_PER_REV : HALF_STEP_PER_REV)

#define STEPPER_MODE	FULL

//State number 
typedef enum {
	S0, S1, S2, S3, S4, S5, S6, S7
} StateNum;

// FULL stepping sequence  - FSM
typedef struct {
    uint32_t next[2];  // Next state for CW(0) and CCW(1)
    uint8_t out[4];    // Output signals for A, B, A', B'
} StateStepper_t;

// Initialization of Stepper Motor (mode: HALF(0), FULL(1) / pinStepper: [A, B, AN, BN])
void stepper_init(uint32_t mode, PinName_t *pinStepper);

// Converts Motor [rpm] to step delay in [msec] or [usec]
// speed_mode: MS(millisec, 0), US(microsec, 1)
void stepper_speed (uint32_t speedRPM, uint32_t speed_mode);

// Run Stepper Motor for given steps, direction and speed mode
// (dir: DIR_CW(0), DIR_CCW(1))
// speed_mode: MS(millisec, 0), US(microsec,1))
void stepper_step(uint32_t steps, uint32_t direction, uint32_t speed_mode);

// Stepper Motor Output for given state
void stepper_out(uint32_t state);

// Stop Stepper Motor
void stepper_stop(void);
```


#### stepper_init()

```c
// Initialization of Stepper Motor (mode: HALF(0), FULL(1) / pinStepper: [A, B, AN, BN])
void stepper_init(uint32_t mode, PinName_t *pinStepper){
	if (mode == HALF) 
		fsm = fsm_Half;
	else
		fsm = fsm_Full;

	//  GPIO Digital Out Initiation
	// For A, B, AN, BN
	for (int i=0; i<4; i++){
		stepperPins[i] = pinStepper[i];
		GPIO_init(stepperPins[i], OUTPUT);
	}
}
```

**Parameters**

* **mode**: Stepper motor operating mode (HALF(0) or FULL(1))
* **pinStepper**: Pointer to an array of four GPIO pins corresponding to the motor coils [A, B, AN, BN].

**Example Code**

```c
stepper_init(HALF, pinStepper);
```


#### stepper_speed()

```c
// Converts Motor [rpm] to step delay in [msec] or [usec]
void stepper_speed (uint32_t speedRPM, uint32_t speed_mode){      // rpm
	// [usec] can be used for a higher accuracy, but needs delay_us() 

	// Divide it by STEP_PER_REV to get one step delay
	if(speed_mode == MS)
		_step_delay_ms = 60*1000UL/(STEP_PER_REV*speedRPM); 		//in [msec]	
	else if(speed_mode == US)
		_step_delay_us = 60*1000000UL/(STEP_PER_REV*speedRPM); 		//in [microsec]	

}
```

**Parameters**

* **speedRPM**: Desired motor speed in revolutions per minute (RPM). This must be greater than 0
* **speed_mode**: Delay time unit (MS(0) for milliseconds or US(1) for microseconds)

**Example Code**
```c
stepper_speed(10, US);
```


#### stepper_step()

```c
// Run Stepper Motor for given steps, direction and speed mode
// (dir: DIR_CW(0), DIR_CCW(1))
// speed_mode: MS(millisec, 0), US(microsec,1))
void stepper_step(uint32_t steps, uint32_t direction, uint32_t speed_mode){
	// Exit if stepper_init() not called 
	if (fsm == 0) return;

	// Save the number of steps
	_steps = steps;

	// run for step size: 
	for (uint32_t i = 0; i < _steps; i++){
		// Update Present State
		state = fsm[state].next[direction];
		
		// Output of Present State
		stepper_out(state);
	
		// Delay for steppermotor speed
		if(speed_mode == MS)
			delay_ms(_step_delay_ms);
		else if(speed_mode == US)
			delay_us(_step_delay_us);
	}
}
```

**Parameters**

* **steps**: Number of steps the motor should rotate
* **direction**: Motor rotation direction(DIR_CW(0), DIR_CCW(1))
* **speed_mode**: Delay time unit (MS(0) for milliseconds, US(1) for microseconds)

**Example Code**

```c
stepper_step(2048, DIR_CW, US);
```


#### stepper_out()

```c
// Stepper Motor Output for given state
void stepper_out(uint32_t state){
	
	// stepperPins[0]=A, stepperPins[1]=B, ...
	// out[0]=A, out[1]=B, ...

	for(int i=0; i<4; i++){
		GPIO_write(stepperPins[i], fsm[state].out[i]);
	}
}
```

**Parameters**

* **state**: Current FSM state index (S0–S3 for FULL mode / S0–S7 for HALF mode)

**Example Code**

```c
stepper_out(S0);
```


#### stepper_stop()

```c
// Stop Stepper Motor
void stepper_stop(void) {
    _steps = 0;    
    
	// All pins DigitalOut '0'
	for(int i=0; i<4; i++){
		GPIO_write(stepperPins[i], LOW);
	}
}
```

**Parameters**
none

**Example Code**

```c
stepper_stop();
```


***

### ecSysTick2

#### Header File

`#include "ecSysTick2.h"`


```c
extern volatile uint32_t msTicks;	

// Initialize 1 ms tick of SysTick timer. 
// Must call AFTER RCC_HSI_init() (16 MHz) or RCC_PLL_init() (84 MHz)
// Updates  EC_SYSCLK either 84 MHz or 16 MHz
void SysTick_init(void);
// SysTick_Handler() is called every 1 ms by the SysTick IRQ
void SysTick_Handler(void);
// Increment msTicks every 1 ms
void SysTick_counter(void);
// Blocking delay in milliseconds
void delay_ms(uint32_t msec);
// Blocking delay in microseconds
void delay_us(uint32_t usec);
// Reset the SysTick counter to 0
void SysTick_reset(void);
// Return the current value of the SysTick counter
uint32_t SysTick_val(void);
```

#### SysTick_init()

```c
// Initialize 1 ms tick of SysTick timer. 
// Must call AFTER RCC_HSI_init() (16 MHz) or RCC_PLL_init() (84 MHz)
// Updates  EC_SYSCLK either 84 MHz or 16 MHz
void SysTick_init(void){
	//  SysTick Control and Status Register
	// Disable SysTick IRQ and SysTick Counter
	SysTick->CTRL = 0;											
	
	// Select processor clock
	// 1 = processor clock;  0 = external clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

	// SysTick Reload Value Register : (SYSCLK / 1000) - 1  ->  1 ms
	//   HSI 16 MHz :  15999      PLL 84 MHz : 83999 
	SysTick->LOAD = (uint32_t)EC_SYSCLK *1UL/ 1000UL - 1UL;   // 1[ms] = 1/1000[s] 

	// SysTick Current Value Register : Reset counter value to 0
	SysTick->VAL = 0;

	// Enables SysTick exception request
	// 1 = counting down to zero --> SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	// Enable SysTick IRQ and SysTick Timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
		
	// Enable interrupt in NVIC
	NVIC_SetPriority(SysTick_IRQn, 15);		// Set Priority to 1
	NVIC_EnableIRQ(SysTick_IRQn);			// Enable interrupt in NVIC
}
```

**Parameters**
none

**Example Code**

```c
SysTick_init();
```


#### SysTick_Handler()

```c
// SysTick_Handler() is called every 1 ms by the SysTick IRQ
void SysTick_Handler(void){
	SysTick_counter();	
}
```

**Parameters**
none

**Example Code**
none


#### SysTick_counter()

```c
// Increment msTicks every 1 ms
void SysTick_counter(void){
	msTicks++;
}	
```

**Parameters**
none

**Example Code**

```c
SysTick_counter();
```


#### delay_ms()

```c
// Blocking delay in milliseconds
void delay_ms (uint32_t msec){
  	uint32_t curTicks;
  	curTicks = msTicks;
	while ((msTicks - curTicks) < msec){;}		// unsigned math: safe across wrap-around
}
```

**Parameters**

* **msec**: delay time in millisec unit

**Example Code**

```c
delay_ms(1000);		// delay 1sec
```


#### delay_us

```c
// Blocking delay in microseconds
void delay_us(uint32_t usec){
    
    uint32_t reload = SysTick->LOAD + 1;				// Total clock cycles in one SysTick period
    uint32_t prev = SysTick->VAL;						// Previous SysTick counter value
    uint32_t curr;										// Current SysTick counter value 
    uint32_t elapsed = 0;								// Total clock cycles passed
    uint32_t target = usec * (EC_SYSCLK / 1000000UL);	// Convert time (us) to clock cycles

    // Wait until the target time is reached
    while(elapsed < target){

        curr = SysTick->VAL;					// Read the current counter value
        if(prev >= curr){
            elapsed += prev - curr;				// Normal countdown
        } else {
            elapsed += prev + reload - curr;	// Counter reloads after reaching 0
        }

        prev = curr;		// Update the previous counter value
    }
}
```

**Parameters**

* **usec**: delay time in microsec unit

**Example Code**

```c
delay_us(1000*1000);		// delay 1sec
```


#### SysTick_reset()

```c
// Reset the SysTick counter to 0
void SysTick_reset(void)
{
	SysTick->VAL = 0;
}
```

**Parameters**
none

**Example Code**

```c
SysTick_reset();
```


#### SysTick_val()

```c
// Return the current value of the SysTick counter
uint32_t SysTick_val(void) {
	return SysTick->VAL;
}
```

**Parameters**
none

**Example Code**

```c
uint32_t val;
val = SysTick_val;
```


***

### ecUART2

#### Header File

`#include "ecUART2.h"`


```c
// USART configuration and baud rate
void USART_init(USART_TypeDef* USARTx, PinName_t pin_GPIO_TX, PinName_t pin_GPIO_RX, uint32_t baud);
void USART_baud(USART_TypeDef* USARTx, uint32_t baud);
void USART_pins(USART_TypeDef* USARTx, PinName_t pin_GPIO_TX, PinName_t pin_GPIO_RX);
void USART1_baud(uint32_t baud);
void USART2_baud(uint32_t baud);
void USART1_init(void);
void USART2_init(void);

// Data transmission and reception
void USART1_write(uint8_t* buffer, uint32_t nBytes);
void USART2_write(uint8_t* buffer, uint32_t nBytes);
uint8_t USART1_read(void);
uint8_t USART2_read(void);
uint32_t is_USART1_RXNE(void);
uint32_t is_USART2_RXNE(void);

// Internal/helper functions
void USART_clock_enable(USART_TypeDef* USARTx);
void USART_write(USART_TypeDef* USARTx, uint8_t* buffer, uint32_t nBytes);
uint8_t USART_read(USART_TypeDef* USARTx);
uint32_t is_USART_RXNE(USART_TypeDef* USARTx);
void USART_delay(uint32_t us);
```


#### USART_init()

```c
// Initialize the selected USART configuration of TX, RX, and baud rate
// (baud: BAUD_xxxx)
void USART_init(USART_TypeDef* USARTx, PinName_t pin_GPIO_TX, PinName_t pin_GPIO_RX, uint32_t baud){
    //1. GPIO Pin for TX and RX
	USART_pins(USARTx, pin_GPIO_TX, pin_GPIO_RX);

	//2. USARTx (x=2,1,6) configuration
	USART_clock_enable(USARTx);

	// Disable USARTx.
	USARTx->CR1 &= ~USART_CR1_UE; 	// USART disable

	// No Parity / 8-bit word length / Oversampling x16 / Stop bit =1
	USARTx->CR1 &= ~(1UL<<10);		// No parity
	USARTx->CR1 &= ~(1UL<<12);		// 8-bit word length
	USARTx->CR1 &= ~(1UL<<15);		// Oversampling x16
	USARTx->CR2 &= ~(3UL<<12);		// Stop bit = 1

	// Set baud rate using the corresponding APB clock
	// USART1/6: APB2 (84 MHz), USART2: APB1 (42 MHz)
	// If oversampling by 16, Tx/Rx baud = f_CK / (16*USARTDIV),
	// If oversampling by 8,  Tx/Rx baud = f_CK / (8*USARTDIV)
	USART_baud(USARTx, baud);

	// Enable TX, RX, and USARTx
	USARTx->CR1 |= (USART_CR1_RE | USART_CR1_TE);   	// Transmitter and Receiver enable
	USARTx->CR1 |= USART_CR1_UE; 						          // USART enable

	// 3. RX interrupt (data ready to be read)
    // Enable RXNE interrupt
	USARTx->CR1 |= USART_CR1_RXNEIE;
    // USART_IRQn
	uint32_t USART_IRQ = USART2_IRQn;
    // Set the priority and enable interrupt
	if(USARTx == USART1)
		USART_IRQ = USART1_IRQn;
	else if(USARTx == USART6)
		USART_IRQ = USART6_IRQn;
	
	// Give the RX interrupt priority and enable it
	NVIC_SetPriority(USART_IRQ, 1);
	NVIC_EnableIRQ(USART_IRQ);

}
```

**Parameters**

* USARTx: USART peripheral (USART1, USART2, or USART6)
* pin_GPIO_TX: GPIO pin used for data transmission (TX)
* pin_GPIO_RX: GPIO pin used for data reception (RX)
* baud: Communication speed in bits per second (bps)

**Example Code**

```c
// Initialize USART1 with PA9 (TX), PA10 (RX), and 9600 bps
USART_init(USART1, PA_9, PA_10, 9600);
```

#### USART_baud()

```c
// Set the baud rate of USARTx (baud: BAUD_xxxx)
void USART_baud(USART_TypeDef* USARTx, uint32_t baud){
	// Disable USARTx.
	USARTx->CR1  &= ~USART_CR1_UE; 						// USART disable
	USARTx->BRR = 0;

	// Configure Baud-rate
	float fCK = EC_SYSCLK;                                   // if(USARTx==USART1 || USARTx==USART6), APB2
	                                                         // (84MHz after RCC_PLL_init(), 16MHz after RCC_HSI_init())
	if(USARTx == USART2) fCK =fCK/2;      // APB1
    float USARTDIV = (float) fCK/16.0/baud;

	// Method 1 : build the two BRR fields explicitly
	//   BRR[15:4] = DIV_Mantissa (integer part of USARTDIV)
	//   BRR[3:0]  = DIV_Fraction (counts 1/16 steps -> multiply the fraction by 16)
	USARTx->BRR |= ((uint32_t)USARTDIV<<4);			// mastissa
	USARTx->BRR |= (uint32_t)round((USARTDIV-(uint32_t)USARTDIV) * 16);	// fraction
  
	// Enable TX, RX, and USARTx
	USARTx->CR1 |= USART_CR1_UE;
}
```

**Parameters**

* USARTx: USART peripheral (USART1, USART2, or USART6).
* baud: Desired communication speed in bps.

**Example Code**

```c
// Set USART2 baud rate to 57600 bps
USART_baud(USART2, BAUD_57600);
```


#### USART_pins()

```c
// GPIO pin setup for USARTx TX/RX (any of USART1, USART2, USART6)
void USART_pins(USART_TypeDef* USARTx, PinName_t pin_GPIO_TX, PinName_t pin_GPIO_RX){
	GPIO_TypeDef *GPIO_TX;
	unsigned int pinTX;
	ecPinmap(pin_GPIO_TX, &GPIO_TX, &pinTX);

	GPIO_TypeDef *GPIO_RX;
	unsigned int pinRX;
	ecPinmap(pin_GPIO_RX, &GPIO_RX, &pinRX);

	// Alternate Function, Push-Pull, No Pull-up/down, High speed
	GPIO_init(pin_GPIO_TX, AF);
	GPIO_otype(pin_GPIO_TX, PUSH_PULL);
	GPIO_pupd(pin_GPIO_TX, NO_PUPD);
	GPIO_ospeed(pin_GPIO_TX, HIGH_SPEED);

	GPIO_init(pin_GPIO_RX, AF);
	GPIO_otype(pin_GPIO_RX, PUSH_PULL);
	GPIO_pupd(pin_GPIO_RX, NO_PUPD);
	GPIO_ospeed(pin_GPIO_RX, HIGH_SPEED);

	// Set Alternate Function Register for USARTx
	//   AF7 - USART1, USART2
	//   AF8 - USART6
	uint32_t AF_num = (USARTx == USART6) ? 8 : 7;
	if (pinTX < 8) { 
		GPIO_TX->AFR[0] &= ~(0xFUL << (4*pinTX));     
		GPIO_TX->AFR[0] |= AF_num << (4*pinTX); 
	} else { 
		GPIO_TX->AFR[1] &= ~(0xFUL << (4*(pinTX-8))); 
		GPIO_TX->AFR[1] |= AF_num << (4*(pinTX-8)); 
	}
	
 	if (pinRX < 8) {
		GPIO_RX->AFR[0] &= ~(15UL<<(pinRX*4));
		GPIO_RX->AFR[0] |= (AF_num<<(pinRX*4));
    } else {
		GPIO_RX->AFR[1] &= ~(15UL<<((pinRX-8)*4));
		GPIO_RX->AFR[1] |= (AF_num<<((pinRX-8)*4));
    }

}
```

**Parameters**

* USARTx: USART peripheral (USART1, USART2, or USART6).
* pin_GPIO_TX: GPIO pin for TX.
* pin_GPIO_RX: GPIO pin for RX.

**Example Code**

```c
// Configure USART1 TX/RX pins (AF7)
USART_pins(USART1, PA_9, PA_10);
```

#### USART1_baud()

```c
// Set baud rate of USART1 (baud: BAUD_xxxx)
void USART1_baud(uint32_t baud){
	USART_baud(USART1, baud);
}
```

**Parameters**

* baud: Communication speed in bps.

**Example Code**

```c
// Set USART1 to 57600 bps
USART1_baud(BAUD_57600);
```

#### USART2_baud()

```c
// Set baud rate of USART2 (baud: BAUD_xxxx)
void USART2_baud(uint32_t baud){
	USART_baud(USART2, baud);
}
```

**Parameters**

* baud: Communication speed in bps.

**Example Code**

```c
// Set USART2 to 9600 bps
USART2_baud(BAUD_9600);
```


#### USART1_init()


```c
// Initialize USART1 with its default pins and 9600 bps configuration.
void USART1_init(void){
	// ********************** USART 1 ***************************
	// PA_9 = USART1_TX (default)	// PB_6  (option)
	// PA_10 = USART1_RX (default)	// PB_3 (option)
	// APB2
	// **********************************************************
	//USART_init(USART1, PA_9, PA_10, 9600);

  ////////////////////////////////////////////
  //  for USART1  ONLY
  ////////////////////////////////////////////
  USART_TypeDef *USARTx= USART1;

//1. GPIO Pin for TX and RX
// Default : PA_9 = USART1_TX, PA_10 = USART1_RX
	PinName_t pin_GPIO_TX  =PA_9;
	PinName_t pin_GPIO_RX  =PA_10;

	GPIO_TypeDef *GPIO_TX;
	unsigned int pinTX;
	ecPinmap(pin_GPIO_TX, &GPIO_TX, &pinTX);
	GPIO_TypeDef *GPIO_RX;
	unsigned int pinRX;
	ecPinmap(pin_GPIO_RX, &GPIO_RX, &pinRX);

	// Alternate Function, Push-Pull, No Pull-up/down, High speed
	GPIO_init(pin_GPIO_TX, AF);
	GPIO_otype(pin_GPIO_TX, PUSH_PULL);
	GPIO_pupd(pin_GPIO_TX, NO_PUPD);
	GPIO_ospeed(pin_GPIO_TX, HIGH_SPEED);

	GPIO_init(pin_GPIO_RX, AF);
	GPIO_otype(pin_GPIO_RX, PUSH_PULL);
	GPIO_pupd(pin_GPIO_RX, NO_PUPD);
	GPIO_ospeed(pin_GPIO_RX, HIGH_SPEED);

 	// Set Alternate Function Register for USARTx
	//   AF7 - USART1, USART2
	//   AF8 - USART6
	uint32_t AF_num = (USARTx == USART6) ? 8 : 7;
	if (pinTX < 8) { GPIO_TX->AFR[0] &= ~(0xFUL << (4*pinTX));     GPIO_TX->AFR[0] |= AF_num << (4*pinTX); }
	else           { GPIO_TX->AFR[1] &= ~(0xFUL << (4*(pinTX-8))); GPIO_TX->AFR[1] |= AF_num << (4*(pinTX-8)); }
	if (pinRX < 8) { GPIO_RX->AFR[0] &= ~(0xFUL << (4*pinRX));     GPIO_RX->AFR[0] |= AF_num << (4*pinRX); }
	else           { GPIO_RX->AFR[1] &= ~(0xFUL << (4*(pinRX-8))); GPIO_RX->AFR[1] |= AF_num << (4*(pinRX-8)); }


//2. USARTx (x=2,1,6) configuration
  // Enable USART peripheral clock
  	//      USART2   = APB1
  	//      USART1,6 = APB2
	USART_clock_enable(USARTx);

  // Disable USARTx.
	USARTx->CR1 &= ~USART_CR1_UE;			// disable while configuring

  // No Parity / 8-bit word length / Oversampling x16
	USARTx->CR1 &= ~USART_CR1_M;			// 8 data bits
	USARTx->CR1 &= ~USART_CR1_PCE;			// no parity
	USARTx->CR1 &= ~USART_CR1_OVER8;		// oversampling by 16
	USARTx->CR2 &= ~USART_CR2_STOP;			// 1 stop bit

  // BAUD RATE (Default: 9600)
  //    Baud rate : BRR[15:4]=mantissa, BRR[3:0]=fraction (1/16 steps)
  //    USARTDIV = f_APB1 / (16 x baud)
  //    USART_baud(USARTx, 9600);
  uint32_t baud=  9600;				// Default baud rate for USART2
  float fCK      = (float)EC_SYSCLK;		// APB1 : 84MHz PLL -> 42MHz
  float USARTDIV = fCK / 16 / baud;
  uint32_t MNT   = (uint32_t)USARTDIV;
  uint32_t FRC   = round((USARTDIV - MNT) * 16);
	if (FRC > 15) { MNT += 1; FRC = 0; }		// carry into the mantissa
	USARTx->BRR = (MNT << 4) | FRC;

  // Enable TX, RX
	USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE);	// transmitter + receiver
  // Enable USART
  	USARTx->CR1 |= USART_CR1_UE;

// 3. RX interrupt (data ready to be read)
  // Enable RXNE interrupt
	USARTx->CR1 |= USART_CR1_RXNEIE;
  // USART2 IRQ
	uint32_t USART_IRQ = USART2_IRQn;
	if (USARTx == USART1){
		USART_IRQ = USART1_IRQn;
	}
	NVIC_SetPriority(USART_IRQ, 1);
	NVIC_EnableIRQ(USART_IRQ);
}
```

**Parameters**

* None

**Example Code**

```c
// Initialize USART1 (PA9: TX, PA10: RX; default 9600 bps)
USART1_init();
```


#### USART2_init()

```c
// Initialize USART2 with its default pins and 9600 bps configuration.
void USART2_init(void){
// ********************** USART 2 ***************************
// PA2 = USART2_TX
// PA3 = USART2_RX
// Alternate function(AF7), High Speed, Push pull, Pull up
// **********************************************************
// USART_init(USART2, PA_2, PA_3, 9600);

////////////////////////////////////////////
//  for USART2  ONLY
////////////////////////////////////////////
  USART_TypeDef *USARTx= USART2;

//1. GPIO Pin for TX and RX
// Default : PA_2 = USART2_TX, PA_3 = USART2_RX
	PinName_t pin_GPIO_TX  =PA_2;
	PinName_t pin_GPIO_RX  =PA_3;

	GPIO_TypeDef *GPIO_TX;
	unsigned int pinTX;
	ecPinmap(pin_GPIO_TX, &GPIO_TX, &pinTX);
	GPIO_TypeDef *GPIO_RX;
	unsigned int pinRX;
	ecPinmap(pin_GPIO_RX, &GPIO_RX, &pinRX);

	// Alternate Function, Push-Pull, No Pull-up/down, High speed
	GPIO_init(pin_GPIO_TX, AF);
	GPIO_otype(pin_GPIO_TX, PUSH_PULL);
	GPIO_pupd(pin_GPIO_TX, NO_PUPD);
	GPIO_ospeed(pin_GPIO_TX, HIGH_SPEED);

	GPIO_init(pin_GPIO_RX, AF);
	GPIO_otype(pin_GPIO_RX, PUSH_PULL);
	GPIO_pupd(pin_GPIO_RX, NO_PUPD);
	GPIO_ospeed(pin_GPIO_RX, HIGH_SPEED);

 	// Set Alternate Function Register for USARTx
	//   AF7 - USART1, USART2
	//   AF8 - USART6
	uint32_t AF_num = (USARTx == USART6) ? 8 : 7;
	if (pinTX < 8) { GPIO_TX->AFR[0] &= ~(0xFUL << (4*pinTX));     GPIO_TX->AFR[0] |= AF_num << (4*pinTX); }
	else           { GPIO_TX->AFR[1] &= ~(0xFUL << (4*(pinTX-8))); GPIO_TX->AFR[1] |= AF_num << (4*(pinTX-8)); }
	if (pinRX < 8) { GPIO_RX->AFR[0] &= ~(0xFUL << (4*pinRX));     GPIO_RX->AFR[0] |= AF_num << (4*pinRX); }
	else           { GPIO_RX->AFR[1] &= ~(0xFUL << (4*(pinRX-8))); GPIO_RX->AFR[1] |= AF_num << (4*(pinRX-8)); }


//2. USARTx (x=2,1,6) configuration
  // Enable USART peripheral clock
  	//      USART2   = APB1
  	//      USART1,6 = APB2
	USART_clock_enable(USARTx);

  // Disable USARTx.
	USARTx->CR1 &= ~USART_CR1_UE;			// disable while configuring

  // No Parity / 8-bit word length / Oversampling x16
	USARTx->CR1 &= ~USART_CR1_M;			// 8 data bits
	USARTx->CR1 &= ~USART_CR1_PCE;			// no parity
	USARTx->CR1 &= ~USART_CR1_OVER8;		// oversampling by 16
	USARTx->CR2 &= ~USART_CR2_STOP;			// 1 stop bit

  // BAUD RATE (Default: 9600)
  //    Baud rate : BRR[15:4]=mantissa, BRR[3:0]=fraction (1/16 steps)
  //    USARTDIV = f_APB1 / (16 x baud)
  //    USART_baud(USARTx, 9600);
  uint32_t baud=  9600;				// Default baud rate for USART2
  float fCK      = (float)EC_SYSCLK / 2;		// APB1 : 84MHz PLL -> 42MHz
  float USARTDIV = fCK / 16 / baud;
  uint32_t MNT   = (uint32_t)USARTDIV;
  uint32_t FRC   = round((USARTDIV - MNT) * 16);
	if (FRC > 15) { MNT += 1; FRC = 0; }		// carry into the mantissa
	USARTx->BRR = (MNT << 4) | FRC;

  // Enable TX, RX
	USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE);	// transmitter + receiver
  // Enable USART
  	USARTx->CR1 |= USART_CR1_UE;

// 3. RX interrupt (data ready to be read)
  // Enable RXNE interrupt
	USARTx->CR1 |= USART_CR1_RXNEIE;
  // USART2 IRQ
	uint32_t USART_IRQ = USART2_IRQn;
	if (USARTx == USART1){
		USART_IRQ = USART1_IRQn;
	}
	NVIC_SetPriority(USART_IRQ, 1);
	NVIC_EnableIRQ(USART_IRQ);
}
```

**Parameters**

* None

**Example Code**

```c
// Initialize USART2 (PA2: TX, PA3: RX; default 9600 bps)
USART2_init();
```


#### USART1_write()

```c
//Send data through USART1.
void USART1_write(uint8_t* buffer, uint32_t nBytes){
	USART_write(USART1, buffer, nBytes);
}
```

**Parameters**

* buffer: Pointer to the data to send.
* nBytes: Number of bytes to transmit.

**Example Code**

```c
uint8_t message[] = "Hello";
USART1_write(message, sizeof(message) - 1);
```


#### USART2_write()

```c
// Send data through USART2.
void USART2_write(uint8_t* buffer, uint32_t nBytes){
	USART_write(USART2, buffer, nBytes);
}
```

**Parameters**

* buffer: Pointer to the data to send.
* nBytes: Number of bytes to transmit.

**Example Code**

```c
uint8_t message[] = "Hello";
USART2_write(message, sizeof(message) - 1);
```


#### USART1_read()

```c
// Read one received character from USART1.
uint8_t USART1_read(void){
	return USART_read(USART1);
}
```

**Parameters**

* None

**Returns**

Return received 8-bit character.

**Example Code**

```c
// Wait for one character from USART1
uint8_t ch = USART1_read();
```


#### USART2_read()

```c
// Read one received character from USART2.
uint8_t USART2_read(void){
	return USART_read(USART2);
}
```

**Parameters**

* None

**Returns**

Return received 8-bit character.

**Example Code**

```c
// Wait for one character from USART2
uint8_t ch = USART2_read();
```


#### is_USART1_RXNE()

```c
// Check whether USART1 has received new data.
uint32_t is_USART1_RXNE(void){
	return is_USART_RXNE(USART1);
}
```

**Parameters**

* None

**Returns**

return 1 if RXNE is set. otherwise return 0.

**Example Code**

```c
if (is_USART1_RXNE()) {
    uint8_t ch = USART1_read();
}
```


#### is_USART2_RXNE()

```c
// Check whether USART2 has received new data.
uint32_t is_USART2_RXNE(void){
	return is_USART_RXNE(USART2);
}
```

**Parameters**

* None

**Returns**

return 1 if RXNE is set. otherwise return 0.

**Example Code**

```c
if (is_USART2_RXNE()) {
    uint8_t ch = USART2_read();
}
```


#### USART_clock_enable()

```c
// Enable the peripheral clock for the selected USART.
void USART_clock_enable(USART_TypeDef* USARTx){
	if (USARTx == USART1)
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 	// Enable USART 1 clock (APB2 clock: AHB clock = 84MHz)
	else if(USARTx == USART2)
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;  	// Enable USART 2 clock (APB1 clock: AHB clock/2 = 42MHz)
	else
		RCC->APB2ENR |= RCC_APB2ENR_USART6EN;  	// Enable USART 6 clock (APB2 clock: AHB clock = 84MHz)
}
```

**Parameters**

* USARTx: USART peripheral (USART1, USART2, or USART6).

**Example Code**

```c
// Enable the peripheral clock for USART2 (APB1)
USART_clock_enable(USART2);
```


#### USART_write()

```c
// Send multiple bytes through the selected USART using polling.
void USART_write(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t nBytes) {
	// TXE is set by hardware when the content of the TDR
	// register has been transferred into the shift register.
	int i;
	for (i = 0; i < nBytes; i++) {
		// wait until TXE (TX empty) bit is set
		while (!(USARTx->SR & USART_SR_TXE));
		// Writing USART_DR automatically clears the TXE flag
		USARTx->DR = buffer[i] & 0xFF;
		USART_delay(300);
	}
	// wait until TC bit is set
	while (!(USARTx->SR & USART_SR_TC));
	// TC bit clear
	USARTx->SR &= ~USART_SR_TC;
}
```

**Parameters**

* USARTx: USART peripheral (USART1, USART2, or USART6).
* buffer: Pointer to the data to send.
* nBytes: Number of bytes to transmit.

**Example Code**

```c
uint8_t message[] = "Hello";
USART_write(USART1, message, sizeof(message) - 1);
```


#### USART_read()

```c
// Wait for and read one character from the selected USART.
uint8_t USART_read(USART_TypeDef * USARTx){
	// Wait until RXNE (RX not empty) bit is set by HW -->Read to read
	while (is_USART_RXNE(USARTx) == 0);
	// Reading USART_DR automatically clears the RXNE flag
	return ((uint8_t)(USARTx->DR & 0xFF));
}
```

**Parameters**

* USARTx: USART peripheral (USART1, USART2, or USART6).

**Returns**

Return received 8-bit character.

**Example Code**

```c
// Receive one character through USART1
uint8_t ch = USART_read(USART1);
```


#### is_USART_RXNE()

```c
// Check the RXNE (Receive Data Register Not Empty) flag.
uint32_t is_USART_RXNE(USART_TypeDef * USARTx){
	return (USARTx->SR & USART_SR_RXNE) != 0;
}
```

**Parameters**

- USARTx: USART peripheral (USART1, USART2, or USART6).

**Returns**

return 1 if data is ready. otherwise return 0.

**Example Code**

```c
if (is_USART_RXNE(USART2)) {
    uint8_t ch = USART_read(USART2);
}
```


#### USART_delay()

```c
// Generate an approximate software delay using a busy-wait loop.
void USART_delay(uint32_t us) {
   uint32_t time = 100*us/7;
   while(--time);
}
```

**Parameters**

* us: Requested delay value (microsecond-oriented, but not precisely timed).

**Example Code**

```c
// Insert a short approximate delay
USART_delay(300);
```


***

### ecTIM2

#### Header File

`#include "ecTIM2.h"`


```c
// Timer update interrupt
void TIM_UI_init(TIM_TypeDef* TIMx, uint32_t msec);
void TIM_UI_init_us(TIM_TypeDef* TIMx, uint32_t usec);
void TIM_UI_enable(TIM_TypeDef* TIMx);
void TIM_UI_disable(TIM_TypeDef* TIMx);
uint32_t is_UIF(TIM_TypeDef* TIMx);
void clear_UIF(TIM_TypeDef* TIMx);

// Timer counter and peripheral clock
void TIM_init(TIM_TypeDef* TIMx, uint32_t msec);
void TIM_init_us(TIM_TypeDef* TIMx, uint32_t usec);
void TIM_period(TIM_TypeDef* TIMx, uint32_t msec);
void TIM_period_us(TIM_TypeDef* TIMx, uint32_t usec);
void TIM_clock_enable(TIM_TypeDef* TIMx);
uint32_t get_TIM_IRQn(TIM_TypeDef* TIMx);
```



#### TIM_UI_init()

Initializes a timer with a millisecond period, enables its update interrupt, and sets the NVIC priority to 2.

```c
void TIM_UI_init(TIM_TypeDef* TIMx, uint32_t msec){
    // 1. Initialize Timer
    TIM_init(TIMx,msec);

    // 2. Enable Update Interrupt
    TIM_UI_enable(TIMx);

    // 3. NVIC Setting
    uint32_t IRQn_reg = get_TIM_IRQn(TIMx);
    NVIC_EnableIRQ(IRQn_reg);
    NVIC_SetPriority(IRQn_reg,2);
}
```

**Parameters**

- **TIMx**: Timer peripheral (e.g., TIM2).
- **msec**: Timer period in milliseconds.

**Example Code**

```c
TIM_UI_init(TIM2, 1000); // TIM2 update interrupt every 1 s
```


#### TIM_UI_init_us()

Initializes a timer with a microsecond period and enables its update interrupt with NVIC priority 2.

```c
void TIM_UI_init_us(TIM_TypeDef* TIMx, uint32_t usec){
    // 1. Initialize Timer
    TIM_init_us(TIMx,usec);

    // 2. Enable Update Interrupt
    TIM_UI_enable(TIMx);

    // 3. NVIC Setting
    uint32_t IRQn_reg = get_TIM_IRQn(TIMx);
    NVIC_EnableIRQ(IRQn_reg);
    NVIC_SetPriority(IRQn_reg,2);
}
```

**Parameters**

- **TIMx**: Timer peripheral (e.g., TIM2).
- **usec**: Timer period in microseconds.

**Example Code**

```c
TIM_UI_init_us(TIM2, 10000); // 10 ms timer update period
```


#### TIM_UI_enable()

Clears the timer update interrupt flag and enables update interrupt generation (UIE).

```c
void TIM_UI_enable(TIM_TypeDef* TIMx){
    TIMx->SR = ~TIM_SR_UIF;
    TIMx->DIER |= TIM_DIER_UIE;
}
```

**Parameters**

- **TIMx**: Timer peripheral to enable the update interrupt for.

**Example Code**

```c
TIM_UI_enable(TIM2);
```

#### TIM_UI_disable()

Disables update interrupt generation (UIE) for the selected timer.

```c
void TIM_UI_disable(TIM_TypeDef* TIMx){
    TIMx->DIER &= ~(TIM_DIER_UIE);
}
```

**Parameters**

- **TIMx**: Timer peripheral whose update interrupt is disabled.

**Example Code**

```c
TIM_UI_disable(TIM2);
```

#### is_UIF()

Checks the timer update interrupt flag (UIF) in the status register.

```c
uint32_t is_UIF(TIM_TypeDef *TIMx){
    return TIMx->SR & TIM_SR_UIF;
}
```

**Parameters**

- **TIMx**: Timer peripheral to check.

**Returns**

Nonzero if UIF is set, otherwise 0.

**Example Code**

```c
if (is_UIF(TIM2)) {
    clear_UIF(TIM2);
}
```

#### clear_UIF()

Clears the timer update interrupt flag (UIF).

```c
void clear_UIF(TIM_TypeDef *TIMx){
    TIMx->SR &= ~TIM_SR_UIF;
}
```

**Parameters**

- **TIMx**: Timer peripheral whose update flag is cleared.

**Example Code**

```c
clear_UIF(TIM2);
```

#### TIM_init()

Enables and starts an up-counting timer with a period specified in milliseconds; the code uses a 10 kHz counter clock.

```c
void TIM_init(TIM_TypeDef* TIMx, uint32_t msec){
    // 1. Enable Timer CLOCK
    TIM_clock_enable(TIMx);

    // 2. Set CNT period
    TIM_period(TIMx, msec);

    // 3. COUNTER Direction: Up-Counter
    TIMx->CR1 &= ~TIM_CR1_DIR;

    // 4. Enable Timer Counter
    TIMx->CR1 |= TIM_CR1_CEN;
}
```

**Parameters**

- **TIMx**: Timer peripheral to initialize.
- **msec**: Counter period in milliseconds.

**Example Code**

```c
TIM_init(TIM2, 1000); // Timer period = 1 s
```

#### TIM_init_us()

Enables and starts an up-counting timer with a period specified in microseconds; the code uses a 1 MHz counter clock.

```c
void TIM_init_us(TIM_TypeDef* TIMx, uint32_t usec){
    // 1. Enable Timer CLOCK
    TIM_clock_enable(TIMx);

    // 2. Set CNT period
    TIM_period_us(TIMx, usec);

    // 3. CNT Direction: up-counter
    TIMx->CR1 &= ~TIM_CR1_DIR;

    // 4. Enable Timer Counter
    TIMx->CR1 |= TIM_CR1_CEN;
}
```

**Parameters**

- **TIMx**: Timer peripheral to initialize.
- **usec**: Counter period in microseconds.

**Example Code**

```c
TIM_init_us(TIM2, 10000); // Timer period = 10 ms
```

#### TIM_period()

Configures the prescaler (PSC) and auto-reload register (ARR) for a millisecond timer period.

```c
void TIM_period(TIM_TypeDef* TIMx, uint32_t msec){
    uint32_t Sys_CLK = EC_SYSCLK;  // 84MHz (PLL) or 16MHz (HSI)

    // Counter Frequency (f_cnt)
    uint32_t f_cnt = 10000UL;      // 10 kHz

    // Prescaler: 84MHz / 10kHz = 8400; register PSC = 8399
    uint32_t PSCval = Sys_CLK / f_cnt;
    TIMx->PSC = PSCval - 1;

    // Reload Value (ARR) for msec unit
    uint32_t ARRval = (f_cnt / 1000UL) * msec;
    TIMx->ARR = ARRval - 1;
}
```

**Parameters**

- **TIMx**: Timer peripheral to configure.
- **msec**: Requested period in milliseconds.

**Example Code**

```c
TIM_clock_enable(TIM2);
TIM_period(TIM2, 10); // Configure period; counter not started here
```

#### TIM_period_us()

Configures PSC and ARR for a microsecond timer period.

```c
void TIM_period_us(TIM_TypeDef* TIMx, uint32_t usec){
    uint32_t Sys_CLK = EC_SYSCLK;  // 84MHz (PLL) or 16MHz (HSI)
    uint32_t ARRval = 0;

    // Counter Frequency (f_cnt)
    uint32_t f_cnt = 1000000UL;    // 1 MHz

    // Prescaler: 84MHz / 1MHz = 84; register PSC = 83
    uint32_t PSCval = Sys_CLK / f_cnt;
    TIMx->PSC = PSCval - 1;

    // Reload Value (ARR) for usec unit
    ARRval = (f_cnt / 1000000UL) * usec;
    TIMx->ARR = ARRval - 1;
}
```

**Parameters**

- **TIMx**: Timer peripheral to configure.
- **usec**: Requested period in microseconds.

**Example Code**

```c
TIM_clock_enable(TIM2);
TIM_period_us(TIM2, 10000); // Configure 10 ms period
```

#### TIM_clock_enable()

Enables the peripheral clock for the selected timer using the RCC APB register.

```c
void TIM_clock_enable(TIM_TypeDef* TIMx){
    if(TIMx == TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    else if(TIMx == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    else if(TIMx == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    else if(TIMx == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    else if(TIMx == TIM5) RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
    else if(TIMx == TIM9) RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
    else if(TIMx == TIM10) RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
    else if(TIMx == TIM11) RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
}
```

**Parameters**

- **TIMx**: Timer peripheral (TIM1–TIM5, TIM9–TIM11 supported in code).

**Example Code**

```c
TIM_clock_enable(TIM2);
```

#### get_TIM_IRQn()

Returns the corresponding timer interrupt number for NVIC configuration.

```c
uint32_t get_TIM_IRQn(TIM_TypeDef* TIMx){
    uint32_t IRQn_reg = 0x00000000;
    if(TIMx == TIM1) IRQn_reg = TIM1_UP_TIM10_IRQn;
    else if(TIMx == TIM2) IRQn_reg = TIM2_IRQn;
    else if(TIMx == TIM3) IRQn_reg = TIM3_IRQn;
    else if(TIMx == TIM4) IRQn_reg = TIM4_IRQn;
    else if(TIMx == TIM5) IRQn_reg = TIM5_IRQn;
    else if(TIMx == TIM9) IRQn_reg = TIM1_BRK_TIM9_IRQn;
    else if(TIMx == TIM10) IRQn_reg = TIM1_UP_TIM10_IRQn;
    else if(TIMx == TIM11) IRQn_reg = TIM1_TRG_COM_TIM11_IRQn;
    return IRQn_reg;
}
```

**Parameters**

- **TIMx**: Timer peripheral.

**Returns**

Corresponding timer IRQ number (e.g., TIM2_IRQn for TIM2).

**Example Code**

```c
uint32_t timerIRQ = get_TIM_IRQn(TIM2);
NVIC_SetPriority(timerIRQ, 2);
```


***

### ecPWM2

Pulse-width modulation (PWM) driver library for STM32F411RE, including timer/channel configuration, duty cycle, and pulse-width control.

#### Header File

`#include "ecPWM2.h"`



```c
// PWM initialization and duty ratio
void PWM_init_config(PinName_t pinName, uint32_t usec);
void PWM_duty(PinName_t pinName, float duty);
void PWM_init(PinName_t pinName, uint32_t msec);
void PWM_init_us(PinName_t pinName, uint32_t usec);

// Pulse width control
void PWM_pulsewidth(PinName_t pinName, uint32_t pulse_width_ms);
void PWM_pulsewidth_us(PinName_t pinName, uint32_t pulse_width_us);

// Internal helper functions
void PWM_mode_config(TIM_TypeDef* TIMx, int chN, uint32_t PWMmode);
void PWM_pinmap(PinName_t pinName, TIM_TypeDef** TIMx, int* chN);
```



#### PWM_init_config()

Maps the pin to a timer/channel, configures the GPIO alternate function, initializes the timer and enables PWM mode 1.

```c
void PWM_init_config(PinName_t pinName, uint32_t usec){
	// 0. Match TIMx from given Port_y and Pin_x
	GPIO_TypeDef *port;
	unsigned int pin;
	ecPinmap(pinName, &port, &pin);
	TIM_TypeDef *TIMx;
	int chN;
	PWM_pinmap(pinName, &TIMx, &chN);

	// 1. Initialize GPIO port and pin as AF
	GPIO_init(pinName, AF);  

	// 2. Configure GPIO AFR by Pin x num.
	//  AFR[0] holds pin 0~7, AFR[1] holds pin 8~15 : 4 bits per pin
	uint32_t afrIdx   = pin >> 3;				// same as (pin/8)
	uint32_t afrShift = 4 * (pin % 8);
	uint32_t afNum    = 0;

	//  AF1 for TIM1,TIM2     AF2 for TIM3,TIM4
	if((TIMx == TIM1)||(TIMx == TIM2))		afNum = 1;	// AF1
	else if(TIMx== TIM3 || TIMx == TIM4)	afNum = 2;	// AF2
	// You can add more  for TIM5 to TIM11, if necessary!	


	// Set AFR register for the pin
	port->AFR[afrIdx] &= ~(0xFUL << afrShift);	// 4 bits per pin	
	port->AFR[afrIdx] |= (afNum <<afrShift);


	// 3. Initialize Timer : select CLK_CNT according to PWM period 
	//   TIM2/TIM5 			(32-bit ARR) : 1 < usec < 2^32 usec 	-> TIM_init_us() 
	//   TIM1/TIM3/TIM4    	(16-bit ARR) : 1 < usec <=65,536 usec 	-> TIM_init_us() 
	//                            			65 < msec <65,536 msec	-> TIM_init() 
	if((TIMx == TIM2) || (TIMx == TIM5) || (usec <= 65536)){
		TIM_init_us(TIMx, usec);					
	}
	else {
		uint32_t msec = usec / 1000;
		if(msec > 6553) msec = 6553;			// 16-bit ARR has limit of 6.5sec
		TIM_init(TIMx, msec);					// 65 < msec <65,536 msec	-> TIM_init() 	
	}
	// 4. Configure Timer Output mode as PWM
	// Default: PWM Mode 1, active high, duty ratio = 50%
	PWM_mode_config(TIMx, chN, EC_PWM_MODE1);

	// 5. Enable Timer Counter
	// For TIM1 ONLY
	if(TIMx == TIM1) TIMx->BDTR |= TIM_BDTR_MOE;					// Main output enable (MOE): 0 = Disable, 1 = Enable		
	// All Timer: First, Clear the counter and Clear UI Flag
	TIMx->EGR |= TIM_EGR_UG;					
	TIMx->SR   = ~TIM_SR_UIF;					
	// Enable timers
	TIMx->CR1  |= TIM_CR1_CEN;  	
}
```

**Parameters**

- **pinName**: PWM output pin, such as PA_5 (TIM2_CH1).
- **usec**: PWM period in microseconds.

**Example Code**

```c
PWM_init_config(PA_5, 10000); // TIM2_CH1, 100 Hz
```

#### PWM_duty()

Clamps duty ratio to 0.0–1.0 and converts it to the appropriate timer CCR value.

```c
void PWM_duty(PinName_t pinName, float duty){
// 0. Match TIMx from  Port and Pin
	GPIO_TypeDef *port;
	unsigned int pin;
	ecPinmap(pinName, &port, &pin);
	TIM_TypeDef *TIMx;
	int chN;
	PWM_pinmap(pinName, &TIMx, &chN);

// 1. Check the duty ratio range from 0.0 to 1.0
	if (duty < 0.0f)	duty = 0.0f;
	if (duty > 1.0f)	duty = 1.0f;

// 2. Duty ratio -> CCR counts.  Assume PWM mode 1 :
	uint32_t CCvalue = (TIMx->ARR + 1) * duty;
	
	if(chN == 1)      { TIMx->CCR1 = CCvalue; }	//set channel
	else if(chN == 2) { TIMx->CCR2 = CCvalue; }
	else if(chN == 3) { TIMx->CCR3 = CCvalue; }
	else if(chN == 4) { TIMx->CCR4 = CCvalue; }
}
```

**Parameters**

- **pinName**: PWM output pin.
- **duty**: Duty ratio from 0.0 (0%) to 1.0 (100%).

**Example Code**

```c
PWM_init(PA_5, 10);
PWM_duty(PA_5, 0.2f); // 20% duty ratio
```

#### PWM_init()

Initializes a PWM output using a period in milliseconds, with PWM mode 1 and approximately 50% default duty.

```c
void PWM_init(PinName_t pinName, uint32_t msec){
	if(msec == 0) msec = 1;		// minimum 1 msec
	PWM_init_config(pinName, msec * 1000);		
}
```

**Parameters**

- **pinName**: PWM output pin.
- **msec**: PWM period in milliseconds (minimum 1 ms in this function).

**Example Code**

```c
PWM_init(PA_5, 10); // 10 ms period, 100 Hz
```

#### PWM_init_us()

Initializes PWM using a period in microseconds; a requested period below 10 µs is raised to 10 µs.

```c
void PWM_init_us(PinName_t pinName, uint32_t usec){	
	if(usec < 10) usec = 10;  // Minimum 10us (100kHz) 
	PWM_init_config(pinName, usec);
}
```

**Parameters**

- **pinName**: PWM output pin.
- **usec**: PWM period in microseconds.

**Example Code**

```c
PWM_init_us(PA_5, 1000); // 1 kHz PWM
```

#### PWM_pulsewidth()

Converts a requested pulse width (milliseconds) into duty ratio and updates the timer CCR register.

```c
void PWM_pulsewidth(PinName_t pinName, uint32_t pulse_width_ms){
// 0. Match TIMx from  Port and Pin 	
	GPIO_TypeDef *port;
	unsigned int pin;	
	ecPinmap(pinName, &port, &pin);	
	TIM_TypeDef *TIMx;
	int chN;		
	PWM_pinmap(pinName, &TIMx, &chN);

	float duty=0.0f;
	uint32_t f_cnt =0;

	
// 1. Counter clock : CK_CNT = EC_SYSCLK / (PSC+1)
	f_cnt = (uint32_t)EC_SYSCLK / (TIMx->PSC + 1);		// [Hz]

// 2. Convert Pulse_width [msec] -> duty ratio (0~1.0) 
	uint32_t counts = (uint32_t)(((uint64_t)f_cnt * pulse_width_ms) / 1000UL);
	duty = (float)counts / (float)(TIMx->ARR + 1);

// 3. Set duty ratio
	PWM_duty(pinName, duty);
}
```

**Parameters**

- **pinName**: PWM output pin, initialized beforehand.
- **pulse_width_ms**: Desired pulse width in milliseconds.

**Example Code**

```c
PWM_init(PA_5, 10);
PWM_pulsewidth(PA_5, 2); // 2 ms pulse, 20% duty
```

#### PWM_pulsewidth_us()

Converts a requested pulse width (microseconds) into duty ratio and updates the timer CCR register.

```c
void PWM_pulsewidth_us(PinName_t pinName, uint32_t pulse_width_us){
// 0. Match TIMx from  Port and Pin 	
	GPIO_TypeDef *port;
	unsigned int pin;	
	ecPinmap(pinName, &port, &pin);	
	TIM_TypeDef *TIMx;
	int chN;		
	PWM_pinmap(pinName, &TIMx, &chN);
	
	float duty=0.0f;
	
// 1. Counter clock : CK_CNT = EC_SYSCLK / (PSC+1)
	uint32_t f_cnt = (uint32_t)EC_SYSCLK / (TIMx->PSC + 1);		// [Hz]

// 2. Convert Pulse_width [usec] -> duty ratio (0~1.0) 
	uint32_t counts = (uint32_t)(((uint64_t)f_cnt * pulse_width_us) / 1000000UL);
	duty = (float)counts / (float)(TIMx->ARR + 1);

// 3. Set duty ratio
	PWM_duty(pinName, duty);
}
```

**Parameters**

- **pinName**: PWM output pin, initialized beforehand.
- **pulse_width_us**: Desired pulse width in microseconds.

**Example Code**

```c
PWM_init_us(PA_5, 1000);
PWM_pulsewidth_us(PA_5, 200); // 200 us pulse, 20% duty
```

#### PWM_mode_config()

Configures the selected timer output channel as PWM mode 1 or 2, enables its preload and channel output, and sets an initial compare value.

```c
void PWM_mode_config(TIM_TypeDef *TIMx, int chN, uint32_t PWMmode){
	
	int mode=0x6; // default value for PWM mode 1
	if (PWMmode == EC_PWM_MODE2)	mode=0x7;  
	
	uint32_t ccVal = TIMx->ARR/2;  // default value  CC=ARR/2
	if(chN == 1){
		TIMx->CCMR1 &= ~TIM_CCMR1_OC1M;                     // Clear ouput compare mode bits for channel 1
		TIMx->CCMR1 |= ((mode << TIM_CCMR1_OC1M_Pos) & TIM_CCMR1_OC1M);   // OCxM = 110 (PWM1) / 111 (PWM2) on ch1
		TIMx->CCMR1	|= TIM_CCMR1_OC1PE;                     // Output 1 preload enable (make CCR1 value changable)
		TIMx->CCR1  = ccVal; 								// Output Compare Register for channel 1 (default duty ratio = 50%)		
		TIMx->CCER &= ~TIM_CCER_CC1P;                       // select output polarity: active high	
		TIMx->CCER  |= TIM_CCER_CC1E;						// Enable output for ch1
	}
	else if(chN == 2){
		TIMx->CCMR1 &= ~TIM_CCMR1_OC2M;                     // Clear ouput compare mode bits for channel 2
		TIMx->CCMR1 |= ((mode << TIM_CCMR1_OC2M_Pos) & TIM_CCMR1_OC2M);   // OCxM = 110 (PWM1) / 111 (PWM2) on ch2
		TIMx->CCMR1	|= TIM_CCMR1_OC2PE;                     // Output 1 preload enable (make CCR1 value changable)	
		TIMx->CCR2  = ccVal; 								// Output Compare Register for channel 2 (default duty ratio = 50%)		
		TIMx->CCER &= ~TIM_CCER_CC2P;                       // select output polarity: active high	
		TIMx->CCER |= TIM_CCER_CC2E;						// Enable output for ch2
	}
	else if(chN == 3){
		TIMx->CCMR2 &= ~TIM_CCMR2_OC3M;                     // Clear ouput compare mode bits for channel 3
		TIMx->CCMR2 |= ((mode << TIM_CCMR2_OC3M_Pos) & TIM_CCMR2_OC3M);   // OCxM = 110 (PWM1) / 111 (PWM2) on ch3
		TIMx->CCMR2	|= TIM_CCMR2_OC3PE;                     // Output 1 preload enable (make CCR1 value changable)	
		TIMx->CCR3  = ccVal; 								// Output Compare Register for channel 3 (default duty ratio = 50%)		
		TIMx->CCER &= ~TIM_CCER_CC3P;                       // select output polarity: active high	
		TIMx->CCER  |= TIM_CCER_CC3E;						// Enable output for ch3
	}
	else if(chN == 4){
		TIMx->CCMR2 &= ~TIM_CCMR2_OC4M;                     // Clear ouput compare mode bits for channel 4
		TIMx->CCMR2 |= ((mode << TIM_CCMR2_OC4M_Pos) & TIM_CCMR2_OC4M);   // OCxM = 110 (PWM1) / 111 (PWM2) on ch4
		TIMx->CCMR2	|= TIM_CCMR2_OC4PE;                     // Output 1 preload enable (make CCR1 value changable)
		TIMx->CCR4  = ccVal;			 					// Output Compare Register for channel 4 (default duty ratio = 50%)				
		TIMx->CCER &= ~TIM_CCER_CC4P;                       // select output polarity: active high	
		TIMx->CCER  |= TIM_CCER_CC4E;						// Enable output for ch4
	}	
}
```

**Parameters**

- **TIMx**: Timer peripheral.
- **chN**: Timer channel (1–4).
- **PWMmode**: EC_PWM_MODE1 or EC_PWM_MODE2.

**Example Code**

```c
// After the timer is configured
PWM_mode_config(TIM2, 1, EC_PWM_MODE1);
```

#### PWM_pinmap()

Looks up the timer peripheral and channel for a supported GPIO PWM pin.

```c
void PWM_pinmap(PinName_t pinName, TIM_TypeDef **TIMx, int *chN)
{
	GPIO_TypeDef *port;
	unsigned int pin;
	ecPinmap(pinName, &port, &pin);

  	// Only  TIM1 to TIM4 are defined.
	// TIM5, 9 to 11 needs to be added, if necessary
  if(port == GPIOA) {
      switch(pin){
         case 0 : *TIMx = TIM2; *chN	= 1; break;
         case 1 : *TIMx = TIM2; *chN = 2; break;
         case 5 : *TIMx = TIM2; *chN = 1; break;
         case 6 : *TIMx = TIM3; *chN = 1; break;
         //case 7: TIMx = TIM1; *chN = 1N; break;
         case 8 : *TIMx = TIM1; *chN = 1; break;
         case 9 : *TIMx = TIM1; *chN = 2; break;
         case 10: *TIMx = TIM1; *chN = 3; break;
         case 15: *TIMx = TIM2; *chN = 1; break;
         default: break;
      }
   }
   else if(port == GPIOB) {
      switch(pin){
         //case 0: TIMx = TIM1; *chN = 2N; break;
         //case 1: TIMx = TIM1; *chN = 3N; break;
         case 3 : *TIMx = TIM2; *chN = 2; break;
         case 4 : *TIMx = TIM3; *chN = 1; break;
         case 5 : *TIMx = TIM3; *chN = 2; break;
         case 6 : *TIMx = TIM4; *chN = 1; break;
         case 7 : *TIMx = TIM4; *chN = 2; break;
         case 8 : *TIMx = TIM4; *chN = 3; break;
         case 9 : *TIMx = TIM4; *chN = 4; break;
         case 10: *TIMx = TIM2; *chN = 3; break;
         default: break;
      }
   }
   else if(port == GPIOC) {
      switch(pin){
         case 6 : *TIMx = TIM3; *chN = 1; break;
         case 7 : *TIMx = TIM3; *chN = 2; break;
         case 8 : *TIMx = TIM3; *chN = 3; break;
         case 9 : *TIMx = TIM3; *chN = 4; break;
         default: break;
      }
   }
	// TIM5, 9, 11 needs to be added, if used.
	// if necessary
}
```

**Parameters**

- **pinName**: Pin name (such as PA_5).
- **TIMx**: Output pointer receiving the selected timer peripheral.
- **chN**: Output pointer receiving the channel number.

**Example Code**

```c
TIM_TypeDef *timer;
int channel;
PWM_pinmap(PA_5, &timer, &channel); // TIM2, channel 1
```

***

### ecADC2

ADC1 regular/injected conversion, polling, sequences, and timer-triggered interrupts.

#### Header File

`#include "ecADC2.h"`

```c
#define ADC_RISE		1
#define ADC_FALL		2
#define ADC_BOTH		3
#define ADC_SINGLE		0		// one conversion per trigger
#define ADC_CONT		1		// keep converting after the first trigger

void ADC_init(PinName_t pinName);
uint32_t ADC_read_poll(void);
uint32_t ADC_read(void);
int ADC_trigger_init(TIM_TypeDef *TIMx, uint32_t msec, uint32_t edge);
void JADC_init(PinName_t pinName);
uint32_t JADC_read_poll(void);
uint32_t JADC_read(uint32_t JDRn);
int JADC_trigger_init(TIM_TypeDef *TIMx, uint32_t msec, uint32_t edge);
void ADC_EOC_enable(void);
void ADC_EOC_disable(void);
void ADC_start(void);
void ADC_stop(void);
void ADC_sequence(PinName_t *seqCHn, uint32_t seqCHnums);
void ADC_conversion(uint32_t convMode);
uint32_t is_ADC_EOC(void);
void clear_ADC_EOC(void);
uint32_t is_ADC_OVR(void);
void clear_ADC_OVR(void);
void JADC_JEOC_enable(void);
void JADC_JEOC_disable(void);
void JADC_start(void);
void JADC_sequence(PinName_t *seqCHn, uint32_t seqCHnums);
uint32_t is_ADC_JEOC(void);
void clear_ADC_JEOC(void);
void ADC_pinmap(PinName_t pinName, uint32_t *chN);
```


#### ADC_init()

Configures the selected analog pin and ADC1 for a 12-bit, single-channel, software-triggered regular conversion.

```c
void ADC_init(PinName_t pinName){
	uint32_t chN;
	ADC_pinmap(pinName, &chN);

// 1. GPIO as ANALOG, no pull-up / pull-down
	GPIO_init(pinName, ANALOG);				// ANALOG = 3
	GPIO_pupd(pinName, NO_PUPD);

// 2. ADC clock, prescaler, resolution
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC->CCR     &= ~ADC_CCR_ADCPRE;		// 00 : PCLK2 / 2 = 42 MHz
	ADC1->CR1    &= ~ADC_CR1_RES;			// 00 : 12-bit

// 3. Channel sampling time : 84 ADC cycles = 2 usec at 42 MHz
	if(chN < 10){
		ADC1->SMPR2 &= ~(7UL << (3 * chN));
		ADC1->SMPR2 |=  (4UL << (3 * chN));
	}
	else{
		ADC1->SMPR1 &= ~(7UL << (3 * (chN - 10)));
		ADC1->SMPR1 |=  (4UL << (3 * (chN - 10)));
	}

// 4. Default: Regular Group, One-channel sequence
	ADC1->CR1  &= ~ADC_CR1_SCAN;			// 0 : one-channel mode
	ADC1->SQR1 &= ~ADC_SQR1_L;				// 0000 : sequence length 1
	ADC1->SQR3 &= ~ADC_SQR3_SQ1;
	ADC1->SQR3 |= (chN & ADC_SQR3_SQ1);		// SQ1 = this channel

// 5. EOC after EVERY conversion, so one sample can be polled or read per EOC.
//    EOCS = 1 also switches overrun detection on - see clear_ADC_OVR().
	ADC1->CR2 |= ADC_CR2_EOCS;

// 6. Default : software trigger, ONE conversion, NO interrupt
	ADC1->CR2 &= ~ADC_CR2_EXTEN;			// no hardware trigger
	ADC1->CR2 &= ~ADC_CR2_CONT;				// single conversion
	ADC1->CR1 &= ~ADC_CR1_EOCIE;
	ADC1->CR1 &= ~ADC_CR1_OVRIE;

// 7. Enable ADC
	ADC1->SR   = 0;							// flags are cleared by writing 0
	ADC1->CR2 |= ADC_CR2_ADON;
}
```

**Parameters**

* **pinName**: ADC-capable analog GPIO pin (e.g., PA_0 or PC_1).

**Example Code**

```c
ADC_init(PA_0);
```


#### ADC_read_poll()

Starts one regular conversion, waits for end-of-conversion (EOC), and returns the result.

```c
uint32_t ADC_read_poll(void){
	ADC1->CR2 &= ~ADC_CR2_CONT;				// one conversion only
	ADC_start();							// clears a latched OVR, then SWSTART

	while(!is_ADC_EOC()){;}					// 12-bit + 84 cycles = about 2.5 usec

	return ADC_read();						// reading DR clears EOC
}
```

**Parameters**

None

**Returns**

12-bit regular conversion value (0–4095).

**Example Code**

```c
ADC_init(PA_0);
uint32_t value = ADC_read_poll();
```


#### ADC_read()

Reads ADC1 regular data register; reading DR clears the EOC flag.

```c
uint32_t ADC_read(void){
	return ADC1->DR;
}
```

**Parameters**

None

**Returns**

Regular ADC1 conversion result read from DR.

**Example Code**

```c
if (is_ADC_EOC()) {
    uint32_t value = ADC_read();
    // Process value inside ADC_IRQHandler().
}
```


#### ADC_trigger_init()

Selects TIM2 or TIM3 update events (TRGO) as the regular ADC trigger and enables EOC interrupts.

```c
int ADC_trigger_init(TIM_TypeDef *TIMx, uint32_t msec, uint32_t edge){
	uint32_t extsel;

	// Allowed : TIM2, TIM3 ONLY
	if     (TIMx == TIM2)	extsel = 0x6;	// 0110 : TIM2 TRGO
	else if(TIMx == TIM3)	extsel = 0x8;	// 1000 : TIM3 TRGO
	else					return -1;

// 1. TIMx Update Event : one TRGO pulse per update event, every msec.
	TIM_init(TIMx, msec);					// clock on, 10 kHz tick, ARR, CEN
	TIMx->CR2 &= ~TIM_CR2_MMS;
	TIMx->CR2 |= TIM_CR2_MMS_1;				// 010 : Update event as TRGO

// 2. ADC HW Trigger Select : trigger source and edge
	ADC1->CR2 &= ~ADC_CR2_EXTSEL;
	ADC1->CR2 |= (extsel << ADC_CR2_EXTSEL_Pos);

	ADC1->CR2 &= ~ADC_CR2_EXTEN;
	if     (edge == ADC_RISE)	ADC1->CR2 |= ADC_CR2_EXTEN_0;	// 01 rising
	else if(edge == ADC_FALL)	ADC1->CR2 |= ADC_CR2_EXTEN_1;	// 10 falling
	else if(edge == ADC_BOTH)	ADC1->CR2 |= ADC_CR2_EXTEN;		// 11 both

// 3. Arm the EOC interrupt - without it, a triggered conversion that nothing
//    reads in time just gets overwritten by the next one (see ecADC2.h).
	ADC_EOC_enable();

	return 0;
}
```

**Parameters**

* **TIMx**: TIM2 or TIM3 timer peripheral.
* **msec**: Update/trigger period in milliseconds.
* **edge**: Hardware ADC trigger edge: ADC_RISE(1), ADC_FALL(2), or ADC_BOTH(3).

**Returns**

`0` on success, `-1` if the chosen timer cannot trigger the regular ADC group.

**Note**

Call `ADC_init()` first and handle `ADC_IRQHandler()` to read each EOC result and avoid overrun. Only TIM2 and TIM3 are supported for the regular group.

**Example Code**

```c
ADC_init(PA_0);
int status = ADC_trigger_init(TIM3, 100, ADC_RISE);
```


#### JADC_init()

Configures an analog pin as a single-channel injected ADC sequence, initially software-triggered.

```c
void JADC_init(PinName_t pinName){
	uint32_t chN;
	ADC_pinmap(pinName, &chN);

// 1. GPIO as ANALOG, no pull-up / pull-down
	GPIO_init(pinName, ANALOG);
	GPIO_pupd(pinName, NO_PUPD);

// 2. ADC clock, prescaler, resolution, alignment
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC->CCR     &= ~ADC_CCR_ADCPRE;		// 00 : PCLK2 / 2 = 42 MHz
	ADC1->CR1    &= ~ADC_CR1_RES;			// 00 : 12-bit
	ADC1->CR2    &= ~ADC_CR2_ALIGN;			// 0  : right alignment

// 3. Channel sampling time : 84 ADC cycles = 2 usec at 42 MHz
	if(chN < 10){
		ADC1->SMPR2 &= ~(7UL << (3 * chN));
		ADC1->SMPR2 |=  (4UL << (3 * chN));
	}
	else{
		ADC1->SMPR1 &= ~(7UL << (3 * (chN - 10)));
		ADC1->SMPR1 |=  (4UL << (3 * (chN - 10)));
	}

// 4. One-channel injected sequence.
//    The injected sequence is RIGHT-aligned : with JL = 0 the single channel
//    belongs in JSQ4, not JSQ1, and its result lands in JDR1.
	ADC1->CR1  |= ADC_CR1_SCAN;				// JSQR drives the sequence
	ADC1->JSQR &= ~ADC_JSQR_JL;				// 00 : one injected conversion
	ADC1->JSQR &= ~ADC_JSQR_JSQ4;
	ADC1->JSQR |= (chN << ADC_JSQR_JSQ4_Pos);

// 5. Idle defaults : software trigger, no interrupt.
//    RM0383 11.3.5 : "Injected channels cannot be converted continuously",
//    the only exception being JAUTO, so CONT stays 0 here.
	ADC1->CR2 &= ~ADC_CR2_JEXTEN;
	ADC1->CR2 &= ~ADC_CR2_CONT;
	ADC1->CR1 &= ~ADC_CR1_JEOCIE;

// 6. Power on. Nothing converts until JADC_read_poll() or a trigger arrives.
	ADC1->SR   = 0;
	ADC1->CR2 |= ADC_CR2_ADON;
}
```

**Parameters**

* **pinName**: ADC-capable analog GPIO pin (e.g., PA_0 or PC_1).

**Example Code**

```c
JADC_init(PC_1);
```


#### JADC_read_poll()

Starts one injected software conversion, waits for JEOC, reads JDR1, and clears JEOC.

```c
uint32_t JADC_read_poll(void){
	ADC1->CR2 |= ADC_CR2_JSWSTART;

	while(!is_ADC_JEOC()){;}

	uint32_t jvalue = JADC_read(1);		// conversion 1 of the sequence
	clear_ADC_JEOC();			// JEOC is cleared by SOFTWARE only - unlike EOC,
	return jvalue;				// reading JDRx does not clear it (RM0383)
}
```

**Parameters**

None

**Returns**

12-bit injected conversion value read from JDR1.

**Example Code**

```c
JADC_init(PC_1);
uint32_t value = JADC_read_poll();
```


#### JADC_read()

Reads one injected data register (JDR1 to JDR4). Reading does not clear JEOC.

```c
uint32_t JADC_read(uint32_t JDRn){
	switch(JDRn){
		case 1:	return ADC1->JDR1;
		case 2:	return ADC1->JDR2;
		case 3:	return ADC1->JDR3;
		case 4:	return ADC1->JDR4;
		default: return 0;
	}
}
```

**Parameters**

* **JDRn**: Injected data register index (1–4).

**Returns**

Value in the selected JDR1–JDR4; `0` for an invalid JDR index.

**Example Code**

```c
if (is_ADC_JEOC()) {
    uint32_t value = JADC_read(1);
    clear_ADC_JEOC();
}
```


#### JADC_trigger_init()

Configures TIM1, TIM2, TIM4, or TIM5 update events (TRGO) to trigger injected conversions and enables JEOC interrupts.

```c
int JADC_trigger_init(TIM_TypeDef *TIMx, uint32_t msec, uint32_t edge){
	uint32_t jextsel;

	if     (TIMx == TIM1)	jextsel = 0x1;
	else if(TIMx == TIM2)	jextsel = 0x3;
	else if(TIMx == TIM4)	jextsel = 0x9;
	else if(TIMx == TIM5)	jextsel = 0xB;
	else					return -1;

// 1. TIMx as the master : one TRGO pulse per update event, every msec.
//    No compare channel of TIMx is consumed.
	TIM_init(TIMx, msec);
	TIMx->CR2 &= ~TIM_CR2_MMS;
	TIMx->CR2 |= TIM_CR2_MMS_1;				// 010 : Update event as TRGO

// 2. ADC side : trigger source and edge
	ADC1->CR2 &= ~ADC_CR2_JEXTSEL;
	ADC1->CR2 |= (jextsel << ADC_CR2_JEXTSEL_Pos);

	ADC1->CR2 &= ~ADC_CR2_JEXTEN;
	if     (edge == ADC_RISE)	ADC1->CR2 |= ADC_CR2_JEXTEN_0;	// 01 rising
	else if(edge == ADC_FALL)	ADC1->CR2 |= ADC_CR2_JEXTEN_1;	// 10 falling
	else if(edge == ADC_BOTH)	ADC1->CR2 |= ADC_CR2_JEXTEN;	// 11 both

// 3. Arm the JEOC interrupt - same reason as ADC_trigger_init().
	JADC_JEOC_enable();

	return 0;
}
```

**Parameters**

* **TIMx**: TIM1, TIM2, TIM4, or TIM5 timer peripheral.
* **msec**: Update/trigger period in milliseconds.
* **edge**: Hardware ADC trigger edge: ADC_RISE(1), ADC_FALL(2), or ADC_BOTH(3).

**Returns**

`0` on success, `-1` if the chosen timer cannot trigger the injected ADC group.

**Note**

Call `JADC_init()` first; a JEOC interrupt handler must read JDR data and clear JEOC. The supported timers are TIM1, TIM2, TIM4, and TIM5.

**Example Code**

```c
JADC_init(PC_1);
int status = JADC_trigger_init(TIM5, 125, ADC_RISE);
```


#### ADC_EOC_enable()

Enables regular end-of-conversion interrupts and configures the shared ADC NVIC interrupt.

```c
void ADC_EOC_enable(void){
	ADC1->SR = 0;							// do not enter the ISR on a stale flag
	ADC1->CR1 |= ADC_CR1_EOCIE;
	NVIC_SetPriority(ADC_IRQn, 2);
	NVIC_EnableIRQ(ADC_IRQn);
}
```

**Parameters**

None

**Example Code**

```c
ADC_init(PA_0);
ADC_EOC_enable();
```


#### ADC_EOC_disable()

Disables the regular EOC interrupt and disables the shared ADC NVIC IRQ.

```c
void ADC_EOC_disable(void){
	ADC1->CR1 &= ~ADC_CR1_EOCIE;
	NVIC_DisableIRQ(ADC_IRQn);
}
```

**Parameters**

None

**Note**

The implementation disables the shared `ADC_IRQn` even if injected JEOC interrupts are enabled; coordinate both modes when using them together.

**Example Code**

```c
ADC_EOC_disable();
```


#### ADC_start()

Ensures ADC1 is enabled, clears the overrun flag, and requests a software-started regular conversion.

```c
void ADC_start(void){
	clear_ADC_OVR();						// a latched OVR blocks every start
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->CR2 |= ADC_CR2_SWSTART;
}
```

**Parameters**

None

**Example Code**

```c
ADC_init(PA_0);
ADC_start();
```


#### ADC_stop()

Clears ADC1 ADON to stop conversions until it is enabled again.

```c
void ADC_stop(void){						// clears ADON : the trigger stops converting
	ADC1->CR2 &= ~ADC_CR2_ADON;
}
```

**Parameters**

None

**Example Code**

```c
ADC_stop();
```


#### ADC_sequence()

Configures the order and length of the regular ADC channel sequence and scan mode.

```c
void ADC_sequence(PinName_t *seqCHn, uint32_t seqCHnums){
	if(seqCHnums < 1)	return;

	ADC1->CR2 &= ~ADC_CR2_ADON;				// SQRx must not change while running

	if(seqCHnums > 1)	ADC1->CR1 |= ADC_CR1_SCAN;		// multi-channel scan
	else				ADC1->CR1 &= ~ADC_CR1_SCAN;

	ADC1->SQR1 &= ~ADC_SQR1_L;
	ADC1->SQR1 |= ((seqCHnums - 1) << ADC_SQR1_L_Pos);

	for(uint32_t i = 0; i < seqCHnums; i++){
		uint32_t chN;
		ADC_pinmap(seqCHn[i], &chN);

		if(i < 6){
			ADC1->SQR3 &= ~(0x1FUL << (i * 5));
			ADC1->SQR3 |=  (chN    << (i * 5));
		}
		else if(i < 12){
			ADC1->SQR2 &= ~(0x1FUL << ((i - 6) * 5));
			ADC1->SQR2 |=  (chN    << ((i - 6) * 5));
		}
		else{
			ADC1->SQR1 &= ~(0x1FUL << ((i - 12) * 5));
			ADC1->SQR1 |=  (chN    << ((i - 12) * 5));
		}
	}

	ADC1->CR2 |= ADC_CR2_ADON;
}
```

**Parameters**

* **seqCHn**: Array of analog GPIO pins in desired conversion order.
* **seqCHnums**: Number of channels in the sequence.

**Note**

Initialize all required GPIO pins in analog mode separately when using more than one input.

**Example Code**

```c
PinName_t channels[] = {PA_0, PC_1};
ADC_init(PA_0);
ADC_sequence(channels, 2);
```


#### ADC_conversion()

Selects single or continuous conversion mode for the regular ADC group.

```c
void ADC_conversion(uint32_t convMode){		// ADC_SINGLE / ADC_CONT
	if(convMode == ADC_CONT)	ADC1->CR2 |=  ADC_CR2_CONT;
	else						ADC1->CR2 &= ~ADC_CR2_CONT;
}
```

**Parameters**

* **convMode**: ADC_SINGLE(0) or ADC_CONT(1).

**Example Code**

```c
ADC_conversion(ADC_SINGLE);
```


#### is_ADC_EOC()

Checks whether ADC1 regular end-of-conversion has occurred.

```c
uint32_t is_ADC_EOC(void){
	return (ADC1->SR & ADC_SR_EOC) == ADC_SR_EOC;
}
```

**Parameters**

None

**Returns**

`1` if EOC is set, otherwise `0`.

**Example Code**

```c
if (is_ADC_EOC()) {
    uint32_t value = ADC_read();
}
```


#### clear_ADC_EOC()

Clears the ADC1 regular EOC status flag.

```c
void clear_ADC_EOC(void){
	ADC1->SR &= ~ADC_SR_EOC;
}
```

**Parameters**

None

**Example Code**

```c
clear_ADC_EOC();
```


#### is_ADC_OVR()

Checks whether ADC1 regular conversion data was overwritten before the previous result was read.

```c
uint32_t is_ADC_OVR(void){
	return (ADC1->SR & ADC_SR_OVR) == ADC_SR_OVR;
}
```

**Parameters**

None

**Returns**

`1` if OVR is set, otherwise `0`.

**Example Code**

```c
if (is_ADC_OVR()) {
    clear_ADC_OVR();
}
```


#### clear_ADC_OVR()

Clears the ADC1 overrun (OVR) status flag.

```c
void clear_ADC_OVR(void){
	ADC1->SR &= ~ADC_SR_OVR;
}
```

**Parameters**

None

**Example Code**

```c
clear_ADC_OVR();
```


#### JADC_JEOC_enable()

Enables the injected end-of-conversion interrupt using the shared ADC NVIC line.

```c
void JADC_JEOC_enable(void){
	ADC1->SR = 0;
	ADC1->CR1 |= ADC_CR1_JEOCIE;
	NVIC_SetPriority(ADC_IRQn, 2);
	NVIC_EnableIRQ(ADC_IRQn);
}
```

**Parameters**

None

**Example Code**

```c
JADC_init(PC_1);
JADC_JEOC_enable();
```


#### JADC_JEOC_disable()

Disables injected JEOC interrupts; disables the shared NVIC IRQ only if regular EOC interrupts are also off.

```c
void JADC_JEOC_disable(void){
	ADC1->CR1 &= ~ADC_CR1_JEOCIE;
	// ADC_IRQn is SHARED with the regular group, so the NVIC line is only
	// released once neither group wants it.
	if((ADC1->CR1 & ADC_CR1_EOCIE) == 0)	NVIC_DisableIRQ(ADC_IRQn);
}
```

**Parameters**

None

**Example Code**

```c
JADC_JEOC_disable();
```


#### JADC_start()

Starts an injected conversion by setting ADON and JSWSTART.

```c
void JADC_start(void){
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->CR2 |= ADC_CR2_JSWSTART;
}
```

**Parameters**

None

**Example Code**

```c
JADC_init(PC_1);
JADC_start();
```


#### JADC_sequence()

Configures a 1- to 4-channel injected conversion sequence, storing results in successive JDR registers.

```c
void JADC_sequence(PinName_t *seqCHn, uint32_t seqCHnums){
	if(seqCHnums < 1 || seqCHnums > 4)	return;

	ADC1->CR2 &= ~ADC_CR2_ADON;				// JSQR must not change while running
	ADC1->CR1 |= ADC_CR1_SCAN;

	ADC1->JSQR &= ~ADC_JSQR_JL;
	ADC1->JSQR |= ((seqCHnums - 1) << ADC_JSQR_JL_Pos);

	// RIGHT-aligned sequence : the i-th conversion of n sits at
	// JSQ(4 - (n-1-i)), i.e. bit 15 - 5*(n-1-i). Its result lands in JDR(i+1).
	for(uint32_t i = 0; i < seqCHnums; i++){
		uint32_t chN;
		ADC_pinmap(seqCHn[i], &chN);
		uint32_t shift = 15 - 5 * (seqCHnums - 1 - i);
		ADC1->JSQR &= ~(0x1FUL << shift);
		ADC1->JSQR |=  (chN    << shift);
	}

	ADC1->CR2 |= ADC_CR2_ADON;
}
```

**Parameters**

* **seqCHn**: Array of analog GPIO pins in desired conversion order.
* **seqCHnums**: Number of injected channels (1–4).

**Note**

Only 1–4 channels are accepted. Initialize all required GPIO pins in analog mode separately.

**Example Code**

```c
PinName_t channels[] = {PA_0, PC_1};
JADC_init(PA_0);
JADC_sequence(channels, 2);
```


#### is_ADC_JEOC()

Checks whether the injected ADC conversion sequence has finished.

```c
uint32_t is_ADC_JEOC(void){
	return (ADC1->SR & ADC_SR_JEOC) == ADC_SR_JEOC;
}
```

**Parameters**

None

**Returns**

`1` if JEOC is set, otherwise `0`.

**Example Code**

```c
if (is_ADC_JEOC()) {
    uint32_t value = JADC_read(1);
    clear_ADC_JEOC();
}
```


#### clear_ADC_JEOC()

Clears the injected end-of-conversion (JEOC) status flag.

```c
void clear_ADC_JEOC(void){
	ADC1->SR &= ~ADC_SR_JEOC;
}
```

**Parameters**

None

**Example Code**

```c
clear_ADC_JEOC();
```


#### ADC_pinmap()

Maps a supported STM32F411 analog GPIO pin to its ADC1 channel number.

```c
void ADC_pinmap(PinName_t pinName, uint32_t *chN){
	GPIO_TypeDef *port;
	unsigned int pin;
	ecPinmap(pinName, &port, &pin);

	*chN = 0;

	if(port == GPIOA){
		switch(pin){
			case 0 : *chN =  0; break;
			case 1 : *chN =  1; break;
			case 4 : *chN =  4; break;
			case 5 : *chN =  5; break;
			case 6 : *chN =  6; break;
			case 7 : *chN =  7; break;
			default: break;
		}
	}
	else if(port == GPIOB){
		switch(pin){
			case 0 : *chN =  8; break;
			case 1 : *chN =  9; break;
			default: break;
		}
	}
	else if(port == GPIOC){
		switch(pin){
			case 0 : *chN = 10; break;
			case 1 : *chN = 11; break;
			case 2 : *chN = 12; break;
			case 3 : *chN = 13; break;
			case 4 : *chN = 14; break;
			case 5 : *chN = 15; break;
			default: break;
		}
	}
}
```

**Parameters**

* **pinName**: ADC-capable analog GPIO pin (e.g., PA_0 or PC_1).
* **chN**: Output pointer receiving the ADC1 channel index.

**Example Code**

```c
uint32_t channel;
ADC_pinmap(PC_1, &channel); // ADC1 channel 11
```


***

### ecICAP2

Timer input-capture configuration, capture/compare interrupts, and counter tick control.

#### Header File

`#include "ecICAP2.h"`

```c
#define IC_RISE 0
#define IC_FALL 1
#define IC_BOTH 2
#define IC_1 1
#define IC_2 2
#define IC_3 3
#define IC_4 4
#define IC_FILTER_0		0		// no filter, transition sampled at fDTS
#define IC_FILTER_1		1		// N = 2 samples at fCK_INT
#define IC_FILTER_2		2		// N = 4 samples at fCK_INT
#define IC_FILTER_3		3		// N = 8 samples at fCK_INT

void ICAP_init(PinName_t pinName, uint32_t edge_type);
void ICAP_ICn_init(PinName_t pinName, uint32_t edge_type, uint32_t ICn);
void ICAP_tick(PinName_t pinName, uint32_t usec);
uint32_t ICAP_read(PinName_t pinName, uint32_t ICn);
uint32_t is_CCIF(TIM_TypeDef *TIMx, uint32_t  ICn);
void clear_CCIF(TIM_TypeDef *TIMx, uint32_t  ICn);
void ICAP_pinmap(PinName_t pinName, TIM_TypeDef **TIMx, int *chN);
void ICAP_filter(TIM_TypeDef *TIMx, uint32_t ICn, uint16_t filterOpt);
void ICAP_ICn_select(TIM_TypeDef *TIMx, uint32_t TIn, uint32_t ICn);
```


#### ICAP_init()

Initializes the timer channel associated with the given pin for input capture at a default 1 us timer tick.

```c
void ICAP_init(PinName_t pinName, uint32_t edge_type) {
    TIM_TypeDef *TIMx;
    int TIn;
    ICAP_pinmap(pinName, &TIMx, &TIn);

    ICAP_ICn_init(pinName, edge_type, TIn);		// ICn = TIn
}
```

**Parameters**

* **pinName**: GPIO pin mapped to a supported timer input (e.g., PA_0).
* **edge_type**: Input-capture edge: IC_RISE(0), IC_FALL(1), or IC_BOTH(2).

**Example Code**

```c
ICAP_init(PA_0, IC_RISE); // TIM2_CH1
```


#### ICAP_ICn_init()

Configures a selected input-capture channel with the GPIO alternate function, filter, polarity, and capture interrupts.

```c
void ICAP_ICn_init(PinName_t pinName, uint32_t edge_type, uint32_t ICn) {
// 0. Match Input Capture Port and Pin for TIMx
    GPIO_TypeDef *port;
    unsigned int pin;
    ecPinmap(pinName, &port, &pin);
    TIM_TypeDef *TIMx;
    int TIn;
    ICAP_pinmap(pinName, &TIMx, &TIn);

// GPIO configuration
// ---------------------------------------------------------------------
// 1. Initialize GPIO port and pin as AF
    GPIO_init(pinName, AF);         // AF=2
    GPIO_pupd(pinName,NO_PUPD);
    GPIO_ospeed(pinName, HIGH_SPEED);  // speed VHIGH=3

// 2. Configure GPIO AFR by Pin num.
    // AFR[0] holds pin 0~7, AFR[1] holds pin 8~15 
	uint32_t afrIdx   = pin >> 3;	// same as (pin/8)
	uint32_t afrShift = 4 * (pin % 8);
	uint32_t afNum    = 0;
	
	//  AF1 for TIM1,TIM2     AF2 for TIM3,TIM4
	if((TIMx == TIM1)||(TIMx == TIM2))		afNum = 1;	// AF1
	else if(TIMx== TIM3 || TIMx == TIM4 || TIMx == TIM5)	afNum = 2;	// AF2
    else if (TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11) afNum = 3;// AF3
	
	// Set AFR register for the pin
	port->AFR[afrIdx] &= ~(0xFUL << afrShift);	// 4 bits per pin
	port->AFR[afrIdx] |=  (afNum << afrShift);


// TIMER configuration (shared by all four channels)
// ---------------------------------------------------------------------
// 1. Timer clock, Update Interrupt and NVIC
    TIM_UI_init_us(TIMx, 1);        // TIMx Interrupt initialize at 1us=1MHz

// 2. Default tick = 1 usec, ARR at maximum
    ICAP_tick(pinName, 1);

// 3. Disable Counter during configuration
    TIMx->CR1 &= ~TIM_CR1_CEN;   


// Input Capture configuration (this channel only)
// ---------------------------------------------------------------------
// 1. Select Timer channel(TIx) for Input Capture channel(ICx)            
    ICAP_ICn_select(TIMx, TIn, ICn);

// 2. Filter Duration for THIS channel. Writing all four channels would
//    corrupt any channel of this timer that is used as an output: in CCMRx
//    the ICxF bits are the OCxM bits of an output channel.
    ICAP_filter(TIMx, ICn, IC_FILTER_3);    // N = 8 samples at fCK_INT
    
// 3. IC Prescaler (use default)

// 4. Activation Edge: CCyNP/CCyP        
    TIMx->CCER  &= ~(0b1010 << 4*(ICn - 1));  			// Clear CCnNP/CCnP bits
	switch(edge_type){
		case IC_RISE: TIMx->CCER &= ~(0b1010 << 4*(ICn - 1)); break; //rising:  00
		case IC_FALL: TIMx->CCER |= 0b0010 << 4*(ICn - 1); 	 break; //falling: 01
		case IC_BOTH: TIMx->CCER |= 0b1010 << 4*(ICn - 1); 	 break; //both:    11
	}

// 5.	Enable CCy Capture, Capture/Compare interrupt
    TIMx->CCER |= 1 << (4 * (ICn - 1));  // CCn(ICn) Capture Enable

// 6.	Enable Interrupt of CC(CCyIE), Update (UIE) per ICn
    TIMx->DIER |= 1 << ICn;      // Capture/Compare Interrupt Enable
    TIMx->DIER |= TIM_DIER_UIE;  // Update Interrupt enable

// 7.	Enable Counter
    TIMx->CR1 |= TIM_CR1_CEN;  // Counter enable
}
```

**Parameters**

* **pinName**: GPIO pin mapped to a supported timer input (e.g., PA_0).
* **edge_type**: Input-capture edge: IC_RISE(0), IC_FALL(1), or IC_BOTH(2).
* **ICn**: Input-capture channel number (IC_1 to IC_4).

**Note**

The selected IC channel must correspond to a supported direct or indirect input pairing for that timer.

**Example Code**

```c
ICAP_init(PA_0, IC_RISE);
ICAP_ICn_init(PA_0, IC_FALL, IC_2);
```


#### ICAP_tick()

Sets the input-capture timer tick interval in microseconds, using the timer prescaler and maximum ARR.

```c
void ICAP_tick(PinName_t pinName, uint32_t usec) {
    // 0. Match Input Capture Port and Pin for TIMx
    TIM_TypeDef *TIMx;
    int CHn;
    ICAP_pinmap(pinName, &TIMx, &CHn);

    if(usec == 0)	usec = 1;			// usec is unsigned : 0 would give PSC = -1
    
    // 1. Prescaler for the requested tick. PSC is 16-bit, < 65536
    uint32_t presc = (uint32_t)(((uint64_t)usec * (uint32_t)EC_SYSCLK) / 1000000UL);
    if(presc < 1)		presc = 1;
    if(presc > 65536)	presc = 65536;			// clamp, PSC = presc - 1
    TIMx->PSC = presc - 1;

    // 2. Configure ARR to be Maximum 
    TIMx->ARR = 0xFFFF;  // Set auto reload register to maximum (count up to 65535)
    if((TIMx == TIM2)||(TIMx == TIM5))		TIMx->ARR = 0xFFFFFFFF;

    // 3. Clear the UIF 
    TIMx->EGR |= TIM_EGR_UG;
    TIMx->SR   = ~TIM_SR_UIF;
}
```

**Parameters**

* **pinName**: GPIO pin mapped to a supported timer input (e.g., PA_0).
* **usec**: Timer tick duration in microseconds (clamped to supported prescaler range).

**Note**

Call after all input-capture channel initialization if a custom tick period is required.

**Example Code**

```c
ICAP_init(PA_0, IC_RISE);
ICAP_tick(PA_0, 10); // 10 us per count
```


#### ICAP_read()

Returns the captured counter value from the requested input-capture channel.

```c
uint32_t ICAP_read(PinName_t pinName, uint32_t ICn) {
    TIM_TypeDef *TIMx;
	int CHn;		
	ICAP_pinmap(pinName, &TIMx, &CHn);
    
    uint32_t capture_Value;

    if (ICn == 1)
        capture_Value = TIMx->CCR1;
    else if (ICn == 2)
        capture_Value = TIMx->CCR2;
    else if (ICn == 3)
        capture_Value = TIMx->CCR3;
    else
        capture_Value = TIMx->CCR4;

    return capture_Value;
}
```

**Parameters**

* **pinName**: GPIO pin mapped to a supported timer input (e.g., PA_0).
* **ICn**: Input-capture channel number (IC_1 to IC_4).

**Returns**

Captured timer counter value from the selected CCR register.

**Note**

Read in the relevant timer IRQ handler or after a capture event, and check/clear the channel interrupt flag.

**Example Code**

```c
uint32_t captured = ICAP_read(PA_0, IC_1);
```


#### is_CCIF()

Checks the capture/compare interrupt status flag for a given timer channel.

```c
uint32_t is_CCIF(TIM_TypeDef *TIMx, uint32_t ICn) {
    return (TIMx->SR & (0x1UL <<  ICn)) != 0;
}
```

**Parameters**

* **TIMx**: Target timer peripheral.
* **ICn**: Input-capture channel number (IC_1 to IC_4).

**Returns**

Nonzero if the selected CC interrupt flag is set, otherwise `0`.

**Example Code**

```c
if (is_CCIF(TIM2, IC_1)) {
    uint32_t count = ICAP_read(PA_0, IC_1);
    clear_CCIF(TIM2, IC_1);
}
```


#### clear_CCIF()

Clears the capture/compare interrupt flag for the selected timer channel.

```c
void clear_CCIF(TIM_TypeDef *TIMx, uint32_t  ICn) {
    // Clear the UIF  by writing
    TIMx->SR = ~(0x1UL << ICn);
}
```

**Parameters**

* **TIMx**: Target timer peripheral.
* **ICn**: Input-capture channel number (IC_1 to IC_4).

**Example Code**

```c
clear_CCIF(TIM2, IC_1);
```


#### ICAP_pinmap()

Maps a supported GPIO pin to its timer peripheral and associated timer input channel.

```c
void ICAP_pinmap(PinName_t pinName, TIM_TypeDef **TIMx, int *chN){
	 GPIO_TypeDef *port;
	 unsigned int pin;		
	 ecPinmap(pinName, &port, &pin);	
   
   if(port == GPIOA) {
      switch(pin){  
         case 0 : *TIMx = TIM2; *chN = 1; break;
         case 1 : *TIMx = TIM2; *chN = 2; break;
         case 5 : *TIMx = TIM2; *chN = 1; break;
         case 6 : *TIMx = TIM3; *chN = 1; break;
         //case 7: *TIMx = TIM1; *chN = 1N; break;
         case 8 : *TIMx = TIM1; *chN = 1; break;
         case 9 : *TIMx = TIM1; *chN = 2; break;
         case 10: *TIMx = TIM1; *chN = 3; break;
         case 15: *TIMx = TIM2; *chN = 1; break;
         default: break;
      }         
   }
   else if(port == GPIOB) {
      switch(pin){
         //case 0: *TIMx = TIM1; *chN = 2N; break;
         //case 1: *TIMx = TIM1; *chN = 3N; break;
         case 3 : *TIMx = TIM2; *chN = 2; break;
         case 4 : *TIMx = TIM3; *chN = 1; break;
         case 5 : *TIMx = TIM3; *chN = 2; break;
         case 6 : *TIMx = TIM4; *chN = 1; break;
         case 7 : *TIMx = TIM4; *chN = 2; break;
         case 8 : *TIMx = TIM4; *chN = 3; break;
         case 9 : *TIMx = TIM4; *chN = 4; break;
         case 10: *TIMx = TIM2; *chN = 3; break;
         
         default: break;
      }
   }
   else if(port == GPIOC) {
      switch(pin){
         case 6 : *TIMx = TIM3; *chN = 1; break;
         case 7 : *TIMx = TIM3; *chN = 2; break;
         case 8 : *TIMx = TIM3; *chN = 3; break;
         case 9 : *TIMx = TIM3; *chN = 4; break;
         
         default: break;
      }
   }
}
```

**Parameters**

* **pinName**: GPIO pin mapped to a supported timer input (e.g., PA_0).
* **TIMx**: Output pointer receiving the selected timer peripheral.
* **chN**: Output pointer receiving the mapped timer input channel number.

**Example Code**

```c
TIM_TypeDef *timer;
int channel;
ICAP_pinmap(PA_0, &timer, &channel); // TIM2, CH1
```


#### ICAP_filter()

Sets the digital filter option for one timer input-capture channel.

```c
void ICAP_filter(TIM_TypeDef *TIMx, uint32_t ICn, uint16_t filterOpt)
{
	// 4 bits per channel: ICnF at bit 4 (ch 1, 3) and bit 12 (ch 2, 4)
	uint32_t shift = (ICn % 2) ? 4 : 12;			// odd channel -> 4, even -> 12

	if(ICn == 1 || ICn == 2){
		TIMx->CCMR1 &= ~(0xFUL  << shift);
		TIMx->CCMR1 |=  (filterOpt << shift);
	}
	else{
		TIMx->CCMR2 &= ~(0xFUL  << shift);
		TIMx->CCMR2 |=  (filterOpt << shift);
	}
}
```

**Parameters**

* **TIMx**: Target timer peripheral.
* **ICn**: Input-capture channel number (IC_1 to IC_4).
* **filterOpt**: Capture digital filter setting (IC_FILTER_0 to IC_FILTER_3).

**Example Code**

```c
ICAP_filter(TIM2, IC_1, IC_FILTER_3);
```


#### ICAP_ICn_select()

Selects whether an input capture channel receives its direct or indirect timer input.

```c
void ICAP_ICn_select(TIM_TypeDef *TIMx, uint32_t TIn, uint32_t ICn){
// 2. Configure  IC number(user selected) with given IC pin(TIMx_CHn)
	switch(ICn){
			case 1:
					TIMx->CCMR1 &= ~TIM_CCMR1_CC1S;						//reset   CC1S
					if (ICn==TIn) TIMx->CCMR1 |= 	TIM_CCMR1_CC1S_0;   //01<<0   CC1S    Tx_Ch1=IC1
					else TIMx->CCMR1 |= 	TIM_CCMR1_CC1S_1;      		//10<<0   CC1S    Tx_Ch2=IC1
					break;
			case 2:
					TIMx->CCMR1 &= ~TIM_CCMR1_CC2S;						//reset   CC2S
					if (ICn==TIn) TIMx->CCMR1 |= 	TIM_CCMR1_CC2S_0;   //01<<0   CC2S    Tx_Ch2=IC2
					else TIMx->CCMR1 |= 	TIM_CCMR1_CC2S_1;      		//10<<0   CC2S    Tx_Ch1=IC2
					break;
			case 3:
					TIMx->CCMR2 &= ~TIM_CCMR2_CC3S;						//reset   CC3S
					if (ICn==TIn) TIMx->CCMR2 |= 	TIM_CCMR2_CC3S_0;   //01<<0   CC3S    Tx_Ch3=IC3
					else TIMx->CCMR2 |= 	TIM_CCMR2_CC3S_1;      		//10<<0   CC3S    Tx_Ch4=IC3
					break;
			case 4:
					TIMx->CCMR2 &= ~TIM_CCMR2_CC4S;						//reset   CC4S
					if (ICn==TIn) TIMx->CCMR2 |= 	TIM_CCMR2_CC4S_0;   //01<<0   CC4S    Tx_Ch4=IC4
					else TIMx->CCMR2 |= 	TIM_CCMR2_CC4S_1;      		//10<<0   CC4S    Tx_Ch3=IC4
					break;
			default: break;
		}

}
```

**Parameters**

* **TIMx**: Target timer peripheral.
* **TIn**: Physical timer input channel number.
* **ICn**: Input-capture channel number (IC_1 to IC_4).

**Example Code**

```c
ICAP_ICn_select(TIM2, 1, IC_1);
```


***

### ecI2C2

I2C1/I2C2/I2C3 master communication and character LCD control over I2C1.

#### Header File

`#include "ecI2C2.h"`

```c
#define LM75_ADDR      0x4C
#define LM75_REG_TEMP  0x00
#define LM75_REG_CONF  0x01
#define LCD_ADDR       0x27
#define LCD_BACKLIGHT  0x08
#define LCD_ENABLE_BIT 0x04
#define LCD_CMD        0x00
#define LCD_DATA       0x01

void I2C1_init(void);
void I2C2_init(void);
void I2C3_init(void);
int I2C1_write(uint8_t devAddr, uint8_t data);
int I2C2_write(uint8_t devAddr, uint8_t data);
int I2C3_write(uint8_t devAddr, uint8_t data);
int I2C1_read(uint8_t devAddr, uint8_t *buf, uint32_t len);
int I2C2_read(uint8_t devAddr, uint8_t *buf, uint32_t len);
int I2C3_read(uint8_t devAddr, uint8_t *buf, uint32_t len);
void LCD_init(void);
void LCD_command(uint8_t cmd);
void LCD_data(uint8_t data);
void LCD_print(char *str);
void LCD_setCursor(uint8_t col, uint8_t row);
```


#### I2C1_init()

Initializes I2C1 on PB8 (SCL, AF4) and PB9 (SDA, AF4), with standard-mode 100 kHz timing.

```c
void I2C1_init(void){
	I2C_pin_init(I2C1, PB_8, PB_9);
	I2C_timing_init(I2C1);
}
```

**Parameters**

None

**Note**

External SCL/SDA pull-up resistors are required for the open-drain bus.

**Example Code**

```c
I2C1_init();
```


#### I2C2_init()

Initializes I2C2 on PB10 (SCL, AF4) and PB3 (SDA, AF9), with standard-mode 100 kHz timing.

```c
void I2C2_init(void){
	I2C_pin_init(I2C2, PB_10, PB_3);
	I2C_timing_init(I2C2);
}
```

**Parameters**

None

**Note**

External pull-ups are required. PB11 is unavailable on the target Nucleo-F411RE package.

**Example Code**

```c
I2C2_init();
```


#### I2C3_init()

Initializes I2C3 on PA8 (SCL, AF4) and PC9 (SDA, AF4), with standard-mode 100 kHz timing.

```c
void I2C3_init(void){
	I2C_pin_init(I2C3, PA_8, PC_9);
	I2C_timing_init(I2C3);
}
```

**Parameters**

None

**Note**

External SCL/SDA pull-up resistors are required for the open-drain bus.

**Example Code**

```c
I2C3_init();
```


#### I2C1_write()

Sends one data byte to a 7-bit I2C device address over I2C1.

```c
int I2C1_write(uint8_t devAddr, uint8_t data){
	return I2C_write_byte(I2C1, devAddr, data);
}
```

**Parameters**

* **devAddr**: 7-bit I2C slave address (unshifted, without the read/write bit).
* **data**: One byte to transmit.

**Returns**

`0` on success; `-1` on timeout/NACK/error.

**Example Code**

```c
I2C1_init();
int status = I2C1_write(LM75_ADDR, LM75_REG_TEMP);
```


#### I2C2_write()

Sends one data byte to a 7-bit I2C device address over I2C2.

```c
int I2C2_write(uint8_t devAddr, uint8_t data){
	return I2C_write_byte(I2C2, devAddr, data);
}
```

**Parameters**

* **devAddr**: 7-bit I2C slave address (unshifted, without the read/write bit).
* **data**: One byte to transmit.

**Returns**

`0` on success; `-1` on timeout/NACK/error.

**Example Code**

```c
I2C2_init();
int status = I2C2_write(LM75_ADDR, LM75_REG_TEMP);
```


#### I2C3_write()

Sends one data byte to a 7-bit I2C device address over I2C3.

```c
int I2C3_write(uint8_t devAddr, uint8_t data){
	return I2C_write_byte(I2C3, devAddr, data);
}
```

**Parameters**

* **devAddr**: 7-bit I2C slave address (unshifted, without the read/write bit).
* **data**: One byte to transmit.

**Returns**

`0` on success; `-1` on timeout/NACK/error.

**Example Code**

```c
I2C3_init();
int status = I2C3_write(LM75_ADDR, LM75_REG_TEMP);
```


#### I2C1_read()

Receives the requested number of bytes from an I2C device using I2C1.

```c
int I2C1_read(uint8_t devAddr, uint8_t *buf, uint32_t len){
	return I2C_read_buf(I2C1, devAddr, buf, len);
}
```

**Parameters**

* **devAddr**: 7-bit I2C slave address (unshifted, without the read/write bit).
* **buf**: Pointer to the destination buffer for received bytes.
* **len**: Number of bytes to read (0 is accepted).

**Returns**

`0` on success; `-1` on timeout/NACK/error.

**Note**

To read a particular register, write its register address first, then call the read function.

**Example Code**

```c
uint8_t buf[2];
I2C1_init();
I2C1_write(LM75_ADDR, LM75_REG_TEMP);
int status = I2C1_read(LM75_ADDR, buf, 2);
```


#### I2C2_read()

Receives the requested number of bytes from an I2C device using I2C2.

```c
int I2C2_read(uint8_t devAddr, uint8_t *buf, uint32_t len){
	return I2C_read_buf(I2C2, devAddr, buf, len);
}
```

**Parameters**

* **devAddr**: 7-bit I2C slave address (unshifted, without the read/write bit).
* **buf**: Pointer to the destination buffer for received bytes.
* **len**: Number of bytes to read (0 is accepted).

**Returns**

`0` on success; `-1` on timeout/NACK/error.

**Note**

To read a particular register, write its register address first, then call the read function.

**Example Code**

```c
uint8_t buf[2];
I2C2_init();
I2C2_write(LM75_ADDR, LM75_REG_TEMP);
int status = I2C2_read(LM75_ADDR, buf, 2);
```


#### I2C3_read()

Receives the requested number of bytes from an I2C device using I2C3.

```c
int I2C3_read(uint8_t devAddr, uint8_t *buf, uint32_t len){
	return I2C_read_buf(I2C3, devAddr, buf, len);
}
```

**Parameters**

* **devAddr**: 7-bit I2C slave address (unshifted, without the read/write bit).
* **buf**: Pointer to the destination buffer for received bytes.
* **len**: Number of bytes to read (0 is accepted).

**Returns**

`0` on success; `-1` on timeout/NACK/error.

**Note**

To read a particular register, write its register address first, then call the read function.

**Example Code**

```c
uint8_t buf[2];
I2C3_init();
I2C3_write(LM75_ADDR, LM75_REG_TEMP);
int status = I2C3_read(LM75_ADDR, buf, 2);
```


#### LCD_init()

Sends the LCD startup command sequence to initialize a character LCD in 4-bit, two-line mode using I2C1.

```c
void LCD_init(void){
    delay_ms(50);
    LCD_command(0x33);  // Function set: Initialize LCD in 8-bit mode first (to reset LCD)
    LCD_command(0x32);  // Function set: Switch to 4-bit mode
    LCD_command(0x28);  // Function set: 4-bit, 2-line, 5x8 dots
    LCD_command(0x0C);  // Display ON, Cursor OFF, Blink OFF
    LCD_command(0x06);  // Entry mode set: Increment cursor, no display shift
    LCD_command(0x01);  // Clear display and return home
    delay_ms(2);
}
```

**Parameters**

None

**Note**

Initialize the system clock and SysTick before `LCD_init()` because it uses `delay_ms()`. This LCD implementation uses I2C1 and `LCD_ADDR` (0x27).

**Example Code**

```c
I2C1_init();
LCD_init();
```


#### LCD_command()

Sends an LCD controller command through the I2C1 LCD interface.

```c
void LCD_command(uint8_t cmd){ LCD_send(cmd, LCD_CMD); }
```

**Parameters**

* **cmd**: LCD controller command byte.

**Example Code**

```c
LCD_command(0x01); // Clear display
```


#### LCD_data()

Sends one character byte to the LCD controller.

```c
void LCD_data(uint8_t data){ LCD_send(data, LCD_DATA); }
```

**Parameters**

* **data**: One byte to transmit.

**Example Code**

```c
LCD_data('A');
```


#### LCD_print()

Prints a null-terminated string to the LCD, one character at a time.

```c
void LCD_print(char *str){
    while(*str){ LCD_data(*str++); }
}
```

**Parameters**

* **str**: Null-terminated string to display.

**Example Code**

```c
LCD_print("Hello STM32");
```


#### LCD_setCursor()

Moves the LCD cursor to the selected column and row using a 20x4 row offset table.

```c
void LCD_setCursor(uint8_t col, uint8_t row){
    uint8_t addr[] = {0x00, 0x40, 0x14, 0x54}; // 20x4
    LCD_command(0x80 | (addr[row] + col));
}
```

**Parameters**

* **col**: Zero-based LCD column index.
* **row**: Zero-based LCD row index (0–3 for the 20x4 row address table).

**Note**

The implementation uses a 20x4 row address table and does not bounds-check the row or column.

**Example Code**

```c
LCD_setCursor(0, 1);
LCD_print("Temperature");
```


***

### ecDHT11

DHT11 temperature and humidity sensor driver with timing and checksum validation.

#### Header File

`#include "ecDHT11.h"`

```c
#define DHT11_OK			 0
#define DHT11_ERR_TOOSOON	-1		// called again before DHT11_MIN_PERIOD_MS
#define DHT11_ERR_NO_REPLY	-2		// the sensor never answered the start pulse
#define DHT11_ERR_TIMEOUT	-3		// a bit edge did not arrive in time
#define DHT11_ERR_CHECKSUM	-4		// 40 bits arrived but the checksum is wrong
#define DHT11_MIN_PERIOD_MS	2000	// datasheet minimum between two reads

void DHT11_init(PinName_t pinName);
int  DHT11_read(void);
int  DHT11_temperature(void);
int  DHT11_humidity(void);
```


#### DHT11_init()

Stores the DHT11 data pin, configures it as a pulled-up input, and resets the driver read-history flag.

```c
void DHT11_init(PinName_t pinName){
	_pin = pinName;

	GPIO_init(_pin, INPUT);
	GPIO_pupd(_pin, PULL_UP);				// idle high between transactions

	_everRead = 0;
}
```

**Parameters**

* **pinName**: GPIO pin connected to the DHT11 data line (e.g., PA_6).

**Note**

Initialize SysTick before reading the sensor. The data line needs a pull-up resistor (typically on the DHT11 breakout board).

**Example Code**

```c
DHT11_init(PA_6); // D12
```


#### DHT11_read()

Reads a 40-bit DHT11 frame, checks the minimum sample interval and checksum, and updates saved measurements on success.

```c
int DHT11_read(void){
	uint8_t  data[5] = {0, 0, 0, 0, 0};
	uint32_t primask;
	int      err = DHT11_OK;

	// The sensor needs 2 s between conversions. Asking sooner returns stale or
	// corrupt data, so say so rather than hand back a bad reading.
	if(_everRead && (msTicks - _lastRead) < DHT11_MIN_PERIOD_MS)
		return DHT11_ERR_TOOSOON;

// 1. Start pulse : hold the line low for at least 18 ms. This is a minimum,
//    so interrupts stay enabled and delay_ms() may be used.
	GPIO_init(_pin, OUTPUT);
	GPIO_otype(_pin, PUSH_PULL);
	GPIO_write(_pin, LOW);
	delay_ms(DHT11_START_MS);

// 2. Release the line. Everything from here is timed in microseconds, so the
//    interrupts go off. PRIMASK is saved and restored instead of enabling
//    blindly, in case the caller had already disabled them.
	primask = __get_PRIMASK();
	__disable_irq();

	GPIO_init(_pin, INPUT);
	GPIO_pupd(_pin, PULL_UP);

	// The sensor answers with 80 us low, then 80 us high, then the first bit
	if(wait_level(LOW,  DHT11_EDGE_US) ||
	   wait_level(HIGH, DHT11_EDGE_US) ||
	   wait_level(LOW,  DHT11_EDGE_US))
		err = DHT11_ERR_NO_REPLY;

// 3. 40 bits, MSB first. Every bit opens with 50 us low; the high that follows
//    is short for a 0 and long for a 1, so one sample taken 40 us after the
//    rising edge separates them without measuring any width.
	if(!err){
		for(uint32_t i = 0; i < 40; i++){
			if(wait_level(HIGH, DHT11_EDGE_US)){		// the 50 us low ends
				err = DHT11_ERR_TIMEOUT;
				break;
			}

			wait_us(DHT11_SAMPLE_US);
			data[i / 8] <<= 1;
			if(GPIO_read(_pin) == HIGH)	data[i / 8] |= 0x01;

			if(wait_level(LOW, DHT11_EDGE_US)){			// the bit ends
				err = DHT11_ERR_TIMEOUT;
				break;
			}
		}
	}

	__set_PRIMASK(primask);
	_lastRead = msTicks;
	_everRead = 1;

	if(err)	return err;

// 4. Checksum : the low byte of the sum of the first four
	if((uint8_t)(data[0] + data[1] + data[2] + data[3]) != data[4])
		return DHT11_ERR_CHECKSUM;

	_humidity    = data[0];				// data[1] is always 0 on a DHT11
	_temperature = data[2];				// data[3] is always 0 on a DHT11
	return DHT11_OK;
}
```

**Parameters**

None

**Returns**

`DHT11_OK` (0), `DHT11_ERR_TOOSOON` (-1), `DHT11_ERR_NO_REPLY` (-2), `DHT11_ERR_TIMEOUT` (-3), or `DHT11_ERR_CHECKSUM` (-4).

**Note**

Keep at least `DHT11_MIN_PERIOD_MS` (2000 ms) between attempts after the first read. Data values remain unchanged after a failed read. The driver briefly disables interrupts during bit sampling.

**Example Code**

```c
DHT11_init(PA_6);
int status = DHT11_read();
if (status == DHT11_OK) {
    int temp = DHT11_temperature();
    int humi = DHT11_humidity();
}
```


#### DHT11_temperature()

Returns the temperature in degrees Celsius from the most recent successful DHT11 read.

```c
int DHT11_temperature(void){	return _temperature;	}
```

**Parameters**

None

**Returns**

Temperature in °C from the last successful read.

**Note**

Only meaningful after `DHT11_read()` returns `DHT11_OK`.

**Example Code**

```c
int temperatureC = DHT11_temperature();
```


#### DHT11_humidity()

Returns the relative humidity percentage from the most recent successful DHT11 read.

```c
int DHT11_humidity(void){		return _humidity;		}
```

**Parameters**

None

**Returns**

Relative humidity in %RH from the last successful read.

**Note**

Only meaningful after `DHT11_read()` returns `DHT11_OK`.

**Example Code**

```c
int humidityRH = DHT11_humidity();
```


***

### ecSTM32F4v2

Umbrella header for the course drivers, board pin definitions, and optional MCU initialization.

#### Header File

`#include "ecSTM32F4v2.h"`

```c
#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "math.h"
#include "ecPinNames.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecEXTI2.h"
#include "ecSysTick2.h"
#include "ecTIM2.h"
#include "ecPWM2.h"
#include "ecStepper2.h"
#include "ecADC2.h"
#include "ecUART2.h"
#include "ecICAP2.h"
#include "ecI2C2.h"
#include "ecDHT11.h"
#define LED0_PIN        PB_12 		//EVAL board JKIT LED0
#define LED7_PIN        PC_3 		//EVAL board JKIT LED7
#define SW1_PIN         PD_2        //EVAL board JKIT SW1
#define SW2_PIN         PA_4	    //EVAL board JKIT SW2
#define LD2             PA_5        //NUCLEO board LED2
#define BUTTON_PIN      PC_13       //NUCLEO board BUTTON1
#define DELAY_UNIT		US			// microsec
#define MOTOR_RPM		10			// 1rpm
void MCU_init(void);
```


#### MCU_init()

Performs the default board/course initialization: 84 MHz PLL, SysTick, LEDs, switches and EXTI, stepper, and USART1/2.

```c
void MCU_init(void){
	RCC_PLL_init();                 // System Clock = 84MHz
	SysTick_init();                 // SysTick Timer Initialization. SysTick: programming manual (STK)
	// Initialize GPIOB_12 for Output
	GPIO_init(LED0_PIN, OUTPUT);    // LED0 for EVAL board	
	GPIO_init(LED7_PIN, OUTPUT);    // LED7 for EVAL board
		
	// Initialize GPIOA_4 for Input Button
	GPIO_init(SW2_PIN, INPUT);  // INPUT for EVAL board
	GPIO_pupd(SW2_PIN, PULL_UP);  // PULL-UP for EVAL board

    // Initialize GPIOD_2 for Input Button
	GPIO_init(SW1_PIN, INPUT);  // INPUT for EVAL board
	GPIO_pupd(SW1_PIN, PULL_UP);  // PULL-UP for EVAL board

    // Initialize GPIOA_5 for Output Button and clear
    GPIO_init(LD2, OUTPUT);
	GPIO_write(LD2, LOW);

    // FND_init(pinFND);
    // FND_select_init(selectFND);

    // // Initialize 7-segment pins
    // for(int i=0; i<8; i++){
    //     GPIO_init_all(pinFND[i], OUTPUT, MEDIUM_SPEED, PUSH_PULL, NO_PUPD);
    // }

    // // Initialize GPIOA_10 for Output Button
	// GPIO_init(selectFND[0], OUTPUT);  // INPUT for EVAL board
	// GPIO_otype(selectFND[0], PUSH_PULL);  // PULL-UP for EVAL board
		
	// Initialize EXTI PA_4
	EXTI_init(SW2_PIN, FALL, 10);	
    // Initialize EXTI PD_2
    EXTI_init(SW1_PIN, FALL, 5);	

    // Initialize Stepper Motor
    GPIO_init(BUTTON_PIN, INPUT);           		// GPIOC pin13 initialization
    EXTI_init(BUTTON_PIN, FALL,0);           		// External Interrupt Setting

	stepper_init(STEPPER_MODE, pinStepper); 		// Stepper GPIO pin initialization
	stepper_speed(MOTOR_RPM, DELAY_UNIT);           //  set stepper motor speed (rpm)    

    // Initialize USART1,2
    // No Parity / 8-bit word length / Oversampling x16 / Stop bit =1
    // USART2: USB serial init
    USART_init(USART2, PA_2, PA_3, 9600);
    //USART2_baud(BAUD_38400);
    // USART1: MCU2 serial init
    USART_init(USART1, PA_9, PA_10, 9600);
    //USART1_baud(BAUD_38400);
        

    
    // TIMx Default Initialization
    // ...
    // PWM Default Initialization
    // ...  
    // Others
}
```

**Parameters**

None

**Note**

This header defines both `MCU_init()` and a global `pinStepper` array. Include it in only one compilation unit if using this definition as-is, and avoid its default pin initialization when those pins are needed by other hardware.

**Example Code**

```c
MCU_init(); // Call once at startup if these default peripherals and pins are intended.
```


