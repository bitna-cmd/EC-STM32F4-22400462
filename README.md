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

`#include "ecGPIO.h"`

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

