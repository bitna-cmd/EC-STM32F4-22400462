# Tutorial: Documentation

## Tutorial: Documentation

## EC API Documentation

[See Class Github](https://github.com/ykkimhgu/EC-student/blob/main/docs/EC_HAL_Documentation.md) for the example documentation

[See Tutorial: Documentation with Markdown](https://ykkim.gitbook.io/ec/numerical-programming/ta-tutorial/tutorial-documentation-with-markdown#preparation)

You must submit your API documentation before the last day of class

### Embedded Controller - STM32F411 Driver Library

Written by: Won Bitna

Program: C/C++

IDE/Compiler: Keil uVision 5

OS: WIn10/11

MCU: STM32F411RE, Nucleo-64

**Table of Contents**

* [GPIO Digital In/Out](#gpio-digital-inout)
  * [Header File](#header-file)
  * [GPIO\_init()](#gpio_init)
  * [GPIO\_mode()](#gpio_mode)
  * [GPIO\_write()](#gpio_write)
  * [GPIO\_read()](#gpio_read)
  * [GPIO\_ospeed()](#gpio_ospeed)
  * [GPIO\_otype()](#gpio_otype)
  * [GPIO\_pupdr()](#gpio_pupdr)
* [GPIO 7segment Display]()
  * [Header File]()
* [EXTI](/ec/ec-course/tutorial.md#gpio-digital-inout)
  * [Header File](/ec/ec-course/tutorial.md#header-file)

***

### ecGPIO2

#### Header File

`#include "ecGPIO2.h"`

```c++
// MODER
#define INPUT  		0x00
#define OUTPUT 		0x01
#define AF     		0x02
#define ANALOG 		0x03

// IDR & ODR
#define HIGH 		1
#define LOW  		0

// OSPEED
#define LOW_SPEED		0x00
#define MID_SPEED		0x01
#define FAST_SPEED		0x02
#define HIGH_SPEED		0x03

// OTYPER
#define PUSH_PULL 		0	// Push-pull
#define OPEN_DRAIN 		1 	// Open-Drain

// PUDR
#define NO_PUPD			0x00 	// No pull-up, pull-down
#define PULL_UP			0x01 	// Pull-up
#define PULL_DOWN 		0x02 	// Pull-down	
#define RESERVED 		0x03 	// Reserved

// PIN
#define LED_PIN 		5
#define BUTTON_PIN 		13
	 
void GPIO_init(PinName_t pinName, uint32_t mode);     
void GPIO_mode(PinName_t pinName, uint32_t mode);
void GPIO_ospeed(PinName_t pinName, uint32_t speed);
void GPIO_otype(PinName_t pinName, uint32_t type);
void GPIO_pupd(PinName_t pinName, uint32_t pupd);
void GPIO_write(PinName_t pinName, uint32_t Output);
uint32_t  GPIO_read(PinName_t pinName);
void GPIO_init_all(PinName_t pinName, uint32_t mode, uint32_t speed, uint32_t type, uint32_t pupd);

// ARDUINO Syntax  (Optional)
void pinMode(PinName_t pin, uint32_t mode);
void digitalWrite(PinName_t pin, uint32_t value);
uint32_t  digitalRead(PinName_t pin);

// FND for JKIT board 
extern int numberFND[12][8];
void FND_init(PinName_t *pinFND);
void FND_select_init(PinName_t *selectFND);
void FND_display(uint8_t num);
void FND_select(uint8_t digit);

void led_toggle(PinName_t pinName);

```

#### GPIO_init

Initializes GPIO pins with default setting and Enables GPIO Clock. Mode: In/Out/AF/Analog

```
void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **mode**: INPUT(0), OUTPUT(1), AF(02), ANALOG (03)

**Example code**

```c
GPIO_init(GPIOA, 5, OUTPUT);
GPIO_init(GPIOC, 13, INPUT); //GPIO_init(GPIOC, 13, 0);
```

#### GPIO\_mode

Configures GPIO pin modes: In/Out/AF/Analog

```c
void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **mode**: INPUT (0), OUTPUT (1), AF(02), ANALOG (03)

**Example code**

```c
GPIO_mode(GPIOA, 5, OUTPUT);
```

#### GPIO_write

Write the data to GPIO pin: High, Low

```c
write(GPIO_TypeDef *Port, int pin, int output);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **output**: LOW(0), HIGH(1)

**Example code**

```c
GPIO_write(GPIOA, 5, 1);  // 1: High
```

#### GPIO\_read()

Read the data from GPIO pin

```c
int  GPIO_read(GPIO_TypeDef *Port, int pin);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15

**Example code**

```c
GPIO_read(GPIOC, 13);
```

#### GPIO\_ospeed()

Configures output speed of GPIO pin : Low, Mid, Fast, High

```c
void GPIO_ospeed(GPIO_TypeDef* Port, int pin, int speed);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **speed**: LOW\_SPEED(0), MID\_SPEED(1), FAST\_SPEED(2) , HIGH\_SPEED(3)

**Example code**

```c
GPIO_ospeed(GPIOA, 5, 2);  // 2: FAST_SPEED
```

#### GPIO\_otype()

Configures output type of GPIO pin: Push-Pull / Open-Drain

```c
void GPIO_otype(GPIO_TypeDef* Port, int pin, int type);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **type**: PUSH\_PULL(0), OPEN\_DRAIN(1)

**Example code**

```c
GPIO_otype(GPIOA, 5, 0);  // 0: Push-Pull
```

#### GPIO\_pupd()

Configures Pull-up/Pull-down mode of GPIO pin: No Pull-up, Pull-down/ Pull-up/ Pull-down/ Reserved

```c
void GPIO_pupd(GPIO_TypeDef* Port, int pin, int pupd);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **pupd**: NO\_PUPD(0), PULL\_UP(1), PULL\_DOWN(2), RESERVED(3)

**Example code**

```c
GPIO_pupd(GPIOA, 5, 0);  // 0: No Pull-up, Pull-down
```


#### GPIO_write()

```c
// Write output on the pin (output: HIGH, LOW)
void GPIO_write(PinName_t pinName, uint32_t Output){
	GPIO_TypeDef *port;
	unsigned int pin;
	ecPinmap(pinName, &port, &pin);

	if(Output == 1)	
		port->ODR |= (1UL<<pin);
	else
		port->ODR &= ~(1UL<<pin);
}
```

**Parameters**

* pinName: pin number (int) 0~15
* Output: HIGH(1), LOW(0)

**Example Code**

```c
GPIO_write(GPIOA, HIGH);
```


#### GPIO_read()

```c
// Read and return the input value through the pin
uint32_t GPIO_read(PinName_t pinName){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	uint32_t reVal = (Port->IDR >> pin) & 1UL;
	return reVal;
}
```

**Parameters**

* pinName: pin number (int) 0~15

**Example Code**

```c
uint32_t val = GPIO_read(GPIOA);
```


#### GPIO_init_all()

```c
// Initialize the pin mode, speed, type pupd at once
// mode: INPUT, OUTPUT, AF, ANALOG
// speed: MEDIUM_SPEED, FAST_SPEED, LOW_SPEED, HIGH_SPEED
// type: OPEN_DRAIN, PUSH_PULL
// pupd: NO_PUPD, PULL_UP, PULL_DOWN, RESERVED
void GPIO_init_all(PinName_t pinName, uint32_t mode, uint32_t speed, uint32_t type, uint32_t pupd){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);

	GPIO_init(pinName, mode);
	GPIO_ospeed(pinName, speed);
	GPIO_otype(pinName, type);
	GPIO_pupd(pinName, pupd);
}
```

**Parameters**

* pinName: pin number (int) 0~15
* mode: INPUT(00), OUTPUT(01), AF(10), ANALOG(11)
* speed: Low_speed (00), Medium_speed (01), Fast_speed (10), High_speed (11)
* type: PUSH_PULL(0), OPEN_DRAIN(1)
* pupd: NO_PUPD(0x00), PULL_UP(0x01), PULL_DOWN(0x10), RESERVED(0x11)

**Example Code**

```c
GPIO_init_all(GPIOA, OUTPUT, MEDIUM_SPEED, PUSH_PULL, PULL_UP);
```


#### pinMode()

```c
void pinMode(PinName_t pin, uint32_t mode){
	GPIO_init(pin, mode);
}
```

**Parameters**

* pinName: pin number (int) 0~15
* mode: INPUT(00), OUTPUT(01), AF(10), ANALOG(11)

**Example Code**

```c
pinMode(GPIOA, INPUT);
```


#### digitalWrite()

```c
void digitalWrite(PinName_t pin, uint32_t value){
	GPIO_write(pin, value);
}
```

**Parameters**

* pinName: pin number (int) 0~15
* mode: HIGH(1), LOW(0)

**Example Code**

```c
digitalWrite(GPIOA, HIGH);
```


#### digitalRead()

```c
uint32_t  digitalRead(PinName_t pin){
	uint32_t reVal = GPIO_read(pin);
	return reVal;
}
```

**Parameters**

* pinName: pin number (int) 0~15

**Example Code**

```c
uint32_t val = digitalRead(GPIOA);
```


#### FND_init()

```c 
// Initialize DOUT pins for 7 segment leds
void FND_init(PinName_t *pinFND){
	for (int i=0; i<8; i++){
		_fndPins[i] = pinFND[i];
		GPIO_init(_fndPins[i], OUTPUT);
	}
}
```

**Parameters**

* **pinFND**: Input pin array for 8 FND segments


**Example Code**

```c
FND_init(pinFND);	// PinName_t pinFND[8]    = {PB_0, PB_1, ...};
```


#### FND_select_init()

```c
// Initialize select pins (FND0~FND3) as DOUT
void FND_select_init(PinName_t *selectFND){	
    // [YOUR CODE GOES HERE]
	for (int i=0; i<4; i++){
		_fndSel[i] = selectFND[i];
		GPIO_init(_fndSel[i], OUTPUT);
	}
}
```

**Parameters**

* **selectFND**: Input pin array for FND selection

**Example Code**

```c
FND_select_init(selectFND);		// PinName_t selectFND[4] = {PA_10, PA_11, ...};
```


#### FND_display()

```c
// Display a number 0 - 9 only on a 7-segment display
void FND_display(uint8_t num){
    // [YOUR CODE GOES HERE]    
    for(int i=0; i<8; i++){
		GPIO_write(_fndPins[i], numberFND[num][i]);
	}
}
```

**Parameters**

* **num**: Number to display on FND (0-9)

**Example Code**

```c
FND_display(5);			// display 5 on the display
```


#### FND_select()

```c
// Select display: FND0 to FND3
void FND_select(uint8_t digit){
    // [YOUR CODE GOES HERE]    
	for(int i=0; i<4; i++){
		if(i == digit)
			GPIO_write(_fndSel[i], HIGH);
		else
			GPIO_write(_fndSel[i], LOW);
	}

}
```

**Parameters**

* **digit**: FND digit to select (0~3)

**Example Code**

```c
FND_select(0);		// select the 0th digit
```


#### led_toggle()

```c
// toggle the led
void led_toggle(PinName_t pinName){
	GPIO_TypeDef *Port;    
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);
    
    Port->ODR ^= (1UL << pin);
}
```

**Parameters**

* **pinName**: pin number (int) 0~15

**Example Code**

```c
led_toggle(PA_4);
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


#### SysTick_Handler();

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
