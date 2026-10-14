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

* [GPIO Digital In/Out](/ec/ec-course/tutorial.md#gpio-digital-inout)
  * [Header File](/ec/ec-course/tutorial.md#header-file)
  * [GPIO\_init()](/ec/ec-course/tutorial.md#gpio-init----)
  * [GPIO\_mode()](/ec/ec-course/tutorial.md#gpio-mode----)
  * [GPIO\_write()](/ec/ec-course/tutorial.md#gpio-write----)
  * [GPIO\_read()](/ec/ec-course/tutorial.md#gpio-read----)
  * [GPIO\_ospeed()](/ec/ec-course/tutorial.md#gpio-ospeed----)
  * [GPIO\_otype()](/ec/ec-course/tutorial.md#gpio-otype----)
  * [GPIO\_pupdr()](/ec/ec-course/tutorial.md#gpio-pupdr----)
  * [Example Code](/ec/ec-course/tutorial.md)
* [EXTI](/ec/ec-course/tutorial.md#gpio-digital-inout)
  * [Header File](/ec/ec-course/tutorial.md#header-file)

***

### GPIO Digital InOut

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

void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
void GPIO_mode(GPIO_TypeDef* Port, int pin, int mode);
void GPIO_write(GPIO_TypeDef *Port, int pin, int output);
int  GPIO_read(GPIO_TypeDef *Port, int pin);
void GPIO_ospeed(GPIO_TypeDef* Port, int pin, int speed);
void GPIO_otype(GPIO_TypeDef* Port, int pin, int type);
void GPIO_pupdr(GPIO_TypeDef* Port, int pin, int pupd);

```

#### GPIO\_init()

Initializes GPIO pins with default setting and Enables GPIO Clock. Mode: In/Out/AF/Analog

```
void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **mode**: INPUT(0), OUTPUT(1), AF(02), ANALOG (03)

**Example code**

```
GPIO_init(GPIOA, 5, OUTPUT);
GPIO_init(GPIOC, 13, INPUT); //GPIO_init(GPIOC, 13, 0);
```

#### GPIO\_mode()

Configures GPIO pin modes: In/Out/AF/Analog

```
void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **mode**: INPUT (0), OUTPUT (1), AF(02), ANALOG (03)

**Example code**

```
GPIO_mode(GPIOA, 5, OUTPUT);
```

#### GPIO\_write()

Write the data to GPIO pin: High, Low

```
write(GPIO_TypeDef *Port, int pin, int output);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **output**: LOW(0), HIGH(1)

**Example code**

```
GPIO_write(GPIOA, 5, 1);  // 1: High
```

#### GPIO\_read()

Read the data from GPIO pin

```
int  GPIO_read(GPIO_TypeDef *Port, int pin);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15

**Example code**

```
GPIO_read(GPIOC, 13);
```

#### GPIO\_ospeed()

Configures output speed of GPIO pin : Low, Mid, Fast, High

```
void GPIO_ospeed(GPIO_TypeDef* Port, int pin, int speed);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **speed**: LOW\_SPEED(0), MID\_SPEED(1), FAST\_SPEED(2) , HIGH\_SPEED(3)

**Example code**

```
GPIO_ospeed(GPIOA, 5, 2);  // 2: FAST_SPEED
```

#### GPIO\_otype()

Configures output type of GPIO pin: Push-Pull / Open-Drain

```
void GPIO_otype(GPIO_TypeDef* Port, int pin, int type);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **type**: PUSH\_PULL(0), OPEN\_DRAIN(1)

**Example code**

```
GPIO_otype(GPIOA, 5, 0);  // 0: Push-Pull
```

#### GPIO\_pupdr()

Configures Pull-up/Pull-down mode of GPIO pin: No Pull-up, Pull-down/ Pull-up/ Pull-down/ Reserved

```
void GPIO_pupdr(GPIO_TypeDef* Port, int pin, int pupd);
```

**Parameters**

* **Port:** Port Number, GPIOA\~GPIOH
* **pin**: pin number (int) 0\~15
* **pupd**: NO\_PUPD(0), PULL\_UP(1), PULL\_DOWN(2), RESERVED(3)

**Example code**

```
GPIO_pupdr(GPIOA, 5, 0);  // 0: No Pull-up, Pull-down
```

#### Example Code

```c++
#include "ecSTM32F411.h"

#define LED_PIN 5
#define BUTTON_PIN 13

// Initialiization 
void setup(void) {
	RCC_PLL_init();
	SysTick_init();
	GPIO_init(GPIOA, LED_PIN, OUTPUT);    
}
	
int main(void) { 
	setup();
	
	while(1){
		delay_ms(500);  
		GPIO_write(GPIOA, LED_PIN, LOW);
		delay_ms(500);  
		GPIO_write(GPIOA, LED_PIN, HIGH);
	}
}
```

***

### EXTI

#### GPIO_init()

```c
// Enable and set the mode of a pin (mode: INPUT, OUTPUT, AF, ANALOG)
void GPIO_init(PinName_t pinName, uint32_t mode){     
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);
	
	// mode  : Input(0), Output(1), AlterFunc(2), Analog(3)   
	if (Port == GPIOA)
		RCC_GPIOA_enable();
	if (Port == GPIOB)
		RCC_GPIOB_enable();
	
	// Make it for GPIOC, GPIOD..GPIOH
	if (Port == GPIOC)
		RCC_GPIOC_enable();
		
	if (Port == GPIOD)
		RCC_GPIOD_enable();
	
	if (Port == GPIOE)
		RCC_GPIOE_enable();

	if (Port == GPIOH)
		RCC_GPIOH_enable();

	// You can also make and use a more general function of
	// void RCC_GPIO_enable(GPIO_TypeDef *Port); 

	GPIO_mode(pinName, mode);
}
```

**Parameters**

* pinName: pin number (int) 0~15
* mode: INPUT(00), OUTPUT(01), AF(10), ANALOG(11)

**Example code**

```c
GPIO_init(GPIOB, OUTPUT);
```

#### GPIO_Mode()

```c
// GPIO Mode          : Input(00), Output(01), AlterFunc(10), Analog(11)
void GPIO_mode(PinName_t pinName, uint32_t mode){
   GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);

   Port->MODER &= ~(3UL<<(2*pin));     
   Port->MODER |= mode<<(2*pin);    
}
```

**Parameters**

* pinName: pin number (int) 0~15
* mode: INPUT(00), OUTPUT(01), AF(10), ANALOG(11)

**Example Code**

```c
GPIO_mode(GPIOA, INPUT)
```

#### GPIO_ospeed()

```c
// GPIO Speed          : Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
void GPIO_ospeed(PinName_t pinName, uint32_t speed){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	Port->OSPEEDR &= ~(3UL<<pin * 2);
	Port->OSPEEDR |= (speed<<pin * 2);
}
```

**Parameters**

* pinName: pin number (int) 0~15
* speed: Low_speed (00), Medium_speed (01), Fast_speed (10), High_speed (11)

**Example Code**

```c
GPIO_ospeed(GPIOA, LOW_speed);
```


#### GPIO_otype

```c
// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
void GPIO_otype(PinName_t pinName, uint32_t type){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	Port->OTYPER &= ~(1UL<<pin);
	Port->OTYPER |= (type<<pin);
}
```

**Parameters**

* pinName: pin number (int) 0~15
* type: PUSH_PULL(0), OPEN_DRAIN(1)

**Example Code**

```c
GPIO_otype(GPIOB, PUSH_PULL);
```


#### GPIO_pupd()

```c
// GPIO Push-Pull    : No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
void GPIO_pupd(PinName_t pinName, uint32_t pupd){
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	Port->PUPDR &= ~(3UL<<pin * 2);
	Port->PUPDR |= (pupd<<pin * 2);
}
```

**Parameters**

* pinName: pin number (int) 0~15
* pupd: NO_PUPD(0x00), PULL_UP(0x01), PULL_DOWN(0x10), RESERVED(0x11)

**Example Code**
```c
GPIO_pupd(GPIOC, PULL_UP);
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


#### GIPD_read()

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


#### pinMode

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


#### FND

```c 
// FND - JKIT board
static PinName_t _fndPins[8];
static PinName_t _fndSel[4];

//Each led that has to light up gets a 1, every other led gets a 0
//its in order  { (a,b,c,d,e,f,g,dp) }
int numberFND[12][8]={
                    {1,1,1,1,1,1,0,0},          //zero
                    {0,1,1,0,0,0,0,0},          //one
                    {1,1,0,1,0,1,0,0},          //two
                    
					{1,1,1,1,0,0,1,0},			//three
					{0,1,1,0,0,1,1,0},			//four
					{1,0,1,1,0,1,1,0},			//five
					{1,0,1,1,1,1,1,0},			//six
					{1,1,1,0,0,1,0,0},			//seven
					{1,1,1,1,1,1,1,0},			//eight
					{1,1,1,1,0,1,1,0},			//nine

                    {0,0,0,0,0,0,0,1},          //dot
                   	{0,0,0,0,0,0,0,0}		      //blank
                  };
                  

// Initialize DOUT pins for 7 segment leds
void FND_init(PinName_t *pinFND){
	for (int i=0; i<8; i++){
		_fndPins[i] = pinFND[i];
		GPIO_init(_fndPins[i], OUTPUT);
	}
}

// Initialize select pins (FND0~FND3) as DOUT
void FND_select_init(PinName_t *selectFND){	
    // [YOUR CODE GOES HERE]
	for (int i=0; i<4; i++){
		_fndSel[i] = selectFND[i];
		GPIO_init(_fndSel[i], OUTPUT);
	}
}

// Display a number 0 - 9 only
void FND_display(uint8_t num){
    // [YOUR CODE GOES HERE]    
    for(int i=0; i<8; i++){
		GPIO_write(_fndPins[i], numberFND[num][i]);
	}
}

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

* _fndPins: GPIO pins for 8 FND segments (a~g, dp)
* _fndSel: GPIO pins for selecting FND0~FND3
* pinFND: Input pin array for 8 FND segments
* selectFND: Input pin array for FND selection
* num: Number to display on FND
* digit: FND digit to select (0~3)


**Example Code**

```c
#include "ecSTM32F4v2.h"

#define BUTTON_PIN PC_13

// Initialiization 
void setup(void)
{
	RCC_PLL_init();
	SysTick_init();
	GPIO_init(BUTTON_PIN, INPUT);  
	sevensegment_init();
}
	
int main(void) { 
	setup();
	unsigned int cnt = 0;
		
	while(1){
		// display 7-segment 0 to 9
		sevensegment_decode(cnt % 10);
		// increase number with button push
		if(GPIO_read(BUTTON_PIN) == 0) {
			cnt++; 
			delay_ms(500);
		}
		if (cnt > 9) cnt = 0;
	}
}
```

