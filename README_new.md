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

- [GPIO Digital In/Out](#gpio-digital-inout)
  - [Header File](#header-file)
  - [GPIO_init()](#gpio_init)
  - [GPIO_mode()](#gpio_mode)
  - [GPIO_write()](#gpio_write)
  - [GPIO_read()](#gpio_read)
  - [GPIO_ospeed()](#gpio_ospeed)
  - [GPIO_otype()](#gpio_otype)
  - [GPIO_pupdr()](#gpio_pupdr)
  - [Example Code](#example-code)
- [EXTI](#exti)
  - [Header File](#header-file)

---

### GPIO Digital InOut

#### Header File

`#include "ecGPIO.h"`

```c
// MODER
#define INPUT       0x00
#define OUTPUT      0x01
#define AF          0x02
#define ANALOG      0x03

// IDR & ODR
#define HIGH        1
#define LOW         0

// OSPEED
#define LOW_SPEED       0x00
#define MID_SPEED       0x01
#define FAST_SPEED      0x02
#define HIGH_SPEED      0x03

// OTYPER
#define PUSH_PULL       0   // Push-pull
#define OPEN_DRAIN      1   // Open-Drain

// PUDR
#define NO_PUPD         0x00    // No pull-up, pull-down
#define PULL_UP         0x01    // Pull-up
#define PULL_DOWN       0x02    // Pull-down
#define RESERVED        0x03    // Reserved

// PIN
#define LED_PIN         5
#define BUTTON_PIN      13

void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
void GPIO_mode(GPIO_TypeDef* Port, int pin, int mode);
void GPIO_write(GPIO_TypeDef *Port, int pin, int output);
int  GPIO_read(GPIO_TypeDef *Port, int pin);
void GPIO_ospeed(GPIO_TypeDef* Port, int pin, int speed);
void GPIO_otype(GPIO_TypeDef* Port, int pin, int type);
void GPIO_pupdr(GPIO_TypeDef* Port, int pin, int pupd);
```

#### GPIO_init()

Initializes GPIO pins with default setting and Enables GPIO Clock. Mode: In/Out/AF/Analog

```c
void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15
- **mode**: INPUT(0), OUTPUT(1), AF(02), ANALOG (03)

**Example code**

```c
GPIO_init(GPIOA, 5, OUTPUT);
GPIO_init(GPIOC, 13, INPUT); //GPIO_init(GPIOC, 13, 0);
```

#### GPIO_mode()

Configures GPIO pin modes: In/Out/AF/Analog

```c
void GPIO_init(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15
- **mode**: INPUT (0), OUTPUT (1), AF(02), ANALOG (03)

**Example code**

```c
GPIO_mode(GPIOA, 5, OUTPUT);
```

#### GPIO_write()

Write the data to GPIO pin: High, Low

```c
write(GPIO_TypeDef *Port, int pin, int output);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15
- **output**: LOW(0), HIGH(1)

**Example code**

```c
GPIO_write(GPIOA, 5, 1);  // 1: High
```

#### GPIO_read()

Read the data from GPIO pin

```c
int  GPIO_read(GPIO_TypeDef *Port, int pin);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15

**Example code**

```c
GPIO_read(GPIOC, 13);
```

#### GPIO_ospeed()

Configures output speed of GPIO pin : Low, Mid, Fast, High

```c
void GPIO_ospeed(GPIO_TypeDef* Port, int pin, int speed);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15
- **speed**: LOW_SPEED(0), MID_SPEED(1), FAST_SPEED(2) , HIGH_SPEED(3)

**Example code**

```c
GPIO_ospeed(GPIOA, 5, 2);  // 2: FAST_SPEED
```

#### GPIO_otype()

Configures output type of GPIO pin: Push-Pull / Open-Drain

```c
void GPIO_otype(GPIO_TypeDef* Port, int pin, int type);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15
- **type**: PUSH_PULL(0), OPEN_DRAIN(1)

**Example code**

```c
GPIO_otype(GPIOA, 5, 0);  // 0: Push-Pull
```

#### GPIO_pupdr()

Configures Pull-up/Pull-down mode of GPIO pin: No Pull-up, Pull-down/ Pull-up/ Pull-down/ Reserved

```c
void GPIO_pupdr(GPIO_TypeDef* Port, int pin, int pupd);
```

**Parameters**

- **Port:** Port Number, GPIOA~GPIOH
- **pin**: pin number (int) 0~15
- **pupd**: NO_PUPD(0), PULL_UP(1), PULL_DOWN(2), RESERVED(3)

**Example code**

```c
GPIO_pupdr(GPIOA, 5, 0);  // 0: No Pull-up, Pull-down
```

#### Example Code

```c
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

---

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

- pinName: pin number (int) 0~15
- mode: INPUT(00), OUTPUT(01), AF(10), ANALOG(11)

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

- pinName: pin number (int) 0~15
- mode: INPUT(00), OUTPUT(01), AF(10), ANALOG(11)

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

- pinName: pin number (int) 0~15
- speed: Low_speed (00), Medium_speed (01), Fast_speed (10), High_speed (11)

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

- pinName: pin number (int) 0~15
- type: PUSH_PULL(0), OPEN_DRAIN(1)

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

- pinName: pin number (int) 0~15
- pupd: NO_PUPD(0x00), PULL_UP(0x01), PULL_DOWN(0x10), RESERVED(0x11)

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

- pinName: pin number (int) 0~15
- Output: HIGH(1), LOW(0)

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

- pinName: pin number (int) 0~15

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

- pinName: pin number (int) 0~15
- mode: INPUT(00), OUTPUT(01), AF(10), ANALOG(11)
- speed: Low_speed (00), Medium_speed (01), Fast_speed (10), High_speed (11)
- type: PUSH_PULL(0), OPEN_DRAIN(1)
- pupd: NO_PUPD(0x00), PULL_UP(0x01), PULL_DOWN(0x10), RESERVED(0x11)

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

- pinName: pin number (int) 0~15
- mode: INPUT(00), OUTPUT(01), AF(10), ANALOG(11)

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

- pinName: pin number (int) 0~15
- mode: HIGH(1), LOW(0)

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

- pinName: pin number (int) 0~15

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

                    {1,1,1,1,0,0,1,0},          //three
                    {0,1,1,0,0,1,1,0},          //four
                    {1,0,1,1,0,1,1,0},          //five
                    {1,0,1,1,1,1,1,0},          //six
                    {1,1,1,0,0,1,0,0},          //seven
                    {1,1,1,1,1,1,1,0},          //eight
                    {1,1,1,1,0,1,1,0},          //nine

                    {0,0,0,0,0,0,0,1},          //dot
                    {0,0,0,0,0,0,0,0}             //blank
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

- _fndPins: GPIO pins for 8 FND segments (a~g, dp)
- _fndSel: GPIO pins for selecting FND0~FND3
- pinFND: Input pin array for 8 FND segments
- selectFND: Input pin array for FND selection
- num: Number to display on FND
- digit: FND digit to select (0~3)

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


**Header File**

`#include "ecGPIO2.h"`

`led_toggle()` is the only function declared in `ecGPIO2.h` that was not already documented in the original text. All other GPIO and FND functions are left untouched.

**Function Declarations**

```c
void led_toggle(PinName_t pinName);
```

#### led_toggle()

Toggles the current output level of a GPIO pin using XOR on the output data register (ODR).

```c
void led_toggle(PinName_t pinName){
	GPIO_TypeDef *Port;    
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);
    
	// YOUR CODE GOES HERE - Use XOR 
    Port->ODR ^= (1UL << pin);
}
```

**Parameters**

- **pinName:** GPIO pin identifier, e.g. `PA_5` or `PB_12` (`PinName_t`).

**Example Code**

```c
GPIO_init(PB_12, OUTPUT);
led_toggle(PB_12);  // HIGH becomes LOW, or LOW becomes HIGH
```

**Notes:** Initialize the pin as an output before toggling.

---

### External Interrupt (EXTI)

**Header File**

`#include "ecEXTI2.h"`

The EXTI library configures edge-triggered external interrupts and manages EXTI pending flags. Trigger macros: `FALL = 0`, `RISE = 1`, `BOTH = 2`.

**Function Declarations**

```c
void EXTI_init(PinName_t pinName, uint32_t trig_type,uint32_t priority);
void EXTI_enable(PinName_t pinName);
void EXTI_disable(PinName_t pinName);
uint32_t is_pending_EXTI(PinName_t pinName);
void clear_pending_EXTI(PinName_t pinName);
```

#### EXTI_init()

Maps a GPIO pin to an EXTI line, selects the trigger edge, unmasks the line, and sets/enables the NVIC interrupt with the specified priority.

```c
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

**Parameters**

- **pinName:** GPIO pin identifier, e.g. `PA_4`.
- **trig_type:** `FALL(0)`, `RISE(1)`, or `BOTH(2)`.
- **priority:** NVIC interrupt priority; smaller numerical values have higher priority.

**Example Code**

```c
GPIO_init(PA_4, INPUT);
GPIO_pupd(PA_4, PULL_UP);
EXTI_init(PA_4, FALL, 10);  // Falling-edge interrupt on PA_4
```

**Notes:** The ISR name depends on the line: EXTI0_IRQHandler through EXTI4_IRQHandler, EXTI9_5_IRQHandler, or EXTI15_10_IRQHandler. Clear the pending flag in the ISR.

#### EXTI_enable()

Unmasks the specified EXTI line so it can generate an interrupt request.

```c
void EXTI_enable(PinName_t pinName) {
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);
	
	EXTI->IMR |= (1UL << pin);     // not masked (i.e., Interrupt enabled)
}
```

**Parameters**

- **pinName:** GPIO pin whose EXTI line should be enabled.

**Example Code**

```c
EXTI_enable(PA_4);  // Unmask EXTI line 4
```

**Notes:** This does not configure the GPIO-to-EXTI mapping or NVIC priority. Configure those using `EXTI_init()` first.

#### EXTI_disable()

Masks the specified EXTI line, preventing its interrupt request from being forwarded.

```c
void EXTI_disable(PinName_t pinName) {
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	EXTI->IMR &= ~(1UL << pin);     // masked (i.e., Interrupt disabled)
}
```

**Parameters**

- **pinName:** GPIO pin whose EXTI line should be disabled.

**Example Code**

```c
EXTI_disable(PA_4);  // Mask EXTI line 4
```

**Notes:** This changes the EXTI interrupt mask (IMR); it does not change the GPIO pin mode.

#### is_pending_EXTI()

Reads the EXTI pending register (PR) and returns whether the selected line has a pending interrupt.

```c
uint32_t is_pending_EXTI(PinName_t pinName) {
	GPIO_TypeDef *Port;
	unsigned int pin;
	ecPinmap(pinName,&Port,&pin);

	uint32_t EXTI_PRx = (EXTI->PR >> pin) & 1UL;     // read PRx, EXTI pending bit.  Use  (REG>>k & 1) to read.
	return  EXTI_PRx; 	// Return only 0 or 1
}
```

**Parameters**

- **pinName:** GPIO pin corresponding to the EXTI line.

**Example Code**

```c
if (is_pending_EXTI(PA_4)) {
    // Handle PA_4 interrupt
    clear_pending_EXTI(PA_4);
}
```

**Notes:** Returns `1` when the pending flag is set, and `0` otherwise.

#### clear_pending_EXTI()

Clears the selected EXTI pending flag by writing 1 to the corresponding bit in EXTI->PR.

```c
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

- **pinName:** GPIO pin corresponding to the pending EXTI line.

**Example Code**

```c
void EXTI4_IRQHandler(void) {
    if (is_pending_EXTI(PA_4)) {
        // Handle button press
        clear_pending_EXTI(PA_4);
    }
}
```

**Notes:** EXTI pending flags use write-one-to-clear behavior; clearing the flag avoids repeated handling of the same request.

---

### Reset and Clock Control (RCC)

**Header File**

`#include "ecRCC2.h"`

The RCC library initializes the system clock and enables individual GPIO peripheral clocks. `EC_SYSCLK` is the global clock-frequency variable updated by `RCC_HSI_init()` and `RCC_PLL_init()`.

**Function Declarations**

```c
void RCC_HSI_init(void);
void RCC_PLL_init(void);
void delay_ms_HSI(uint32_t ms);
void RCC_GPIOA_enable(void);
void RCC_GPIOB_enable(void);
void RCC_GPIOC_enable(void);
void RCC_GPIOD_enable(void);
void RCC_GPIOE_enable(void);
void RCC_GPIOH_enable(void);
```

#### RCC_HSI_init()

Enables the internal high-speed oscillator (HSI), selects it as the system clock, and updates `EC_SYSCLK` to 16,000,000 Hz.

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

- None.

**Example Code**

```c
RCC_HSI_init();  // SYSCLK = 16 MHz
SysTick_init();  // Initialize SysTick after selecting clock
```

**Notes:** Use before `SysTick_init()` when the application runs from HSI.

#### RCC_PLL_init()

Configures the clock source and PLL to target an 84 MHz system clock and updates `EC_SYSCLK`.

```c
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

- None.

**Example Code**

```c
RCC_PLL_init();  // Target SYSCLK = 84 MHz
SysTick_init();
```

**Notes:** This documentation reproduces the uploaded implementation as written; it is not a separate validation of PLL lock or clock switching.

#### delay_ms_HSI()

Implements a busy-wait delay using a decrementing counter derived from `EC_SYSCLK`.

```c
void delay_ms_HSI(uint32_t ms) {
	//uint32_t EC_SYSCLK=16000000;
	volatile uint32_t cnt = ((uint32_t)EC_SYSCLK / (1000UL * 6)) * ms;
	while (cnt > 0) cnt--;
}
```

**Parameters**

- **ms:** Requested approximate delay in milliseconds.

**Example Code**

```c
RCC_HSI_init();
delay_ms_HSI(100);  // Approximate blocking delay
```

**Notes:** Timing is approximate because it depends on instruction execution and compiler optimization. It does not use the SysTick tick counter.

#### RCC_GPIOA_enable()

Enables the AHB1 peripheral clock for GPIO port A.

```c
void RCC_GPIOA_enable()
{
	// RCC Peripheral Clock Enable Register 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}
```

**Parameters**

- None.

**Example Code**

```c
RCC_GPIOA_enable();
GPIO_mode(PA_5, OUTPUT);
```

**Notes:** `GPIO_init()` calls the required per-port RCC enable routine automatically.

#### RCC_GPIOB_enable()

Enables the AHB1 peripheral clock for GPIO port B.

```c
void RCC_GPIOB_enable()
{
	// RCC Peripheral Clock Enable Register 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
}
```

**Parameters**

- None.

**Example Code**

```c
RCC_GPIOB_enable();
GPIO_mode(PB_12, OUTPUT);
```

**Notes:** `GPIO_init()` calls the required per-port RCC enable routine automatically.

#### RCC_GPIOC_enable()

Enables the AHB1 peripheral clock for GPIO port C.

```c
void RCC_GPIOC_enable()
{
	// RCC Peripheral Clock Enable Register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
}
```

**Parameters**

- None.

**Example Code**

```c
RCC_GPIOC_enable();
GPIO_mode(PC_13, INPUT);
```

**Notes:** `GPIO_init()` calls the required per-port RCC enable routine automatically.

#### RCC_GPIOD_enable()

Enables the AHB1 peripheral clock for GPIO port D.

```c
void RCC_GPIOD_enable(void){
	// RCC Peripheral Clock Enable Register
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
}
```

**Parameters**

- None.

**Example Code**

```c
RCC_GPIOD_enable();
GPIO_mode(PD_2, INPUT);
```

**Notes:** `GPIO_init()` calls the required per-port RCC enable routine automatically.

#### RCC_GPIOE_enable()

Enables the AHB1 peripheral clock for GPIO port E.

```c
void RCC_GPIOE_enable(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
}
```

**Parameters**

- None.

**Example Code**

```c
RCC_GPIOE_enable();
```

**Notes:** GPIOE availability depends on the MCU/package. The uploaded `ecPinmap()` does not provide an explicit GPIOE mapping.

#### RCC_GPIOH_enable()

Enables the AHB1 peripheral clock for GPIO port H.

```c
void RCC_GPIOH_enable(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
}
```

**Parameters**

- None.

**Example Code**

```c
RCC_GPIOH_enable();
GPIO_mode(PH_0, INPUT);
```

**Notes:** `GPIO_init()` calls the required per-port RCC enable routine automatically.

---

### Pin Names and Mapping

**Header File**

`#include "ecPinNames.h"`

`PinName_t` identifies the GPIO port and pin in one encoded value (for example, `PB_12`).

**Function Declarations**

```c
void ecPinmap(PinName_t pinName, GPIO_TypeDef **GPIOx, unsigned int *pin);
```

#### ecPinmap()

Decodes a `PinName_t` value into a GPIO port pointer and a port-local pin index.

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

- **pinName:** Encoded pin name such as `PA_5`, `PB_12`, or `PC_13`.
- **GPIOx:** Output parameter (`GPIO_TypeDef **`) receiving the GPIO port address.
- **pin:** Output parameter (`unsigned int *`) receiving the pin index (0–15).

**Example Code**

```c
GPIO_TypeDef *port;
unsigned int pin;
ecPinmap(PB_12, &port, &pin);  // port = GPIOB, pin = 12
```

**Notes:** The supplied implementation explicitly maps ports A, B, C, D, and H. Other encoded ports fall back to GPIOA; do not assume unsupported ports are decoded correctly.

---

### SysTick Timer and Delay

**Header File**

`#include "ecSysTick2.h"`

The SysTick library supplies a millisecond tick counter and blocking millisecond/microsecond delays. `msTicks` is declared `extern volatile uint32_t` in the header.

**Function Declarations**

```c
void SysTick_init(void);
void SysTick_Handler(void);
void SysTick_counter(void);
void delay_ms(uint32_t msec);
void delay_us(uint32_t usec);
void SysTick_reset(void);
uint32_t SysTick_val(void);
```

#### SysTick_init()

Initializes the SysTick timer using `EC_SYSCLK` to generate periodic 1 ms exceptions and enables the SysTick counter.

```c
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

- None.

**Example Code**

```c
RCC_PLL_init();
SysTick_init();  // 1 ms tick
```

**Notes:** Call after `RCC_HSI_init()` or `RCC_PLL_init()`, because the reload value depends on `EC_SYSCLK`.

#### SysTick_Handler()

Interrupt handler executed when the 1 ms SysTick counter reaches zero; calls `SysTick_counter()`.

```c
void SysTick_Handler(void){
	SysTick_counter();	
}
```

**Parameters**

- None.

**Example Code**

```c
// Existing ecSysTick2.c handler runs automatically every 1 ms.
// No explicit call is needed from main().
SysTick_init();
```

**Notes:** The handler is already defined in the uploaded `ecSysTick2.c`. Do not define another handler with the same name unless replacing the original implementation.

#### SysTick_counter()

Increments the global millisecond tick count `msTicks` by one.

```c
void SysTick_counter(void){
	msTicks++;
}
```

**Parameters**

- None.

**Example Code**

```c
// Existing SysTick_Handler() invokes SysTick_counter() each tick.
uint32_t before = msTicks;
// After a timer tick, msTicks increases by 1.
```

**Notes:** This helper is called inside `SysTick_Handler()`; normally application code should not call it manually.

#### delay_ms()

Provides a blocking delay by waiting until `msTicks` has advanced by the requested number of milliseconds.

```c
void delay_ms (uint32_t msec){
  	uint32_t curTicks;
  	curTicks = msTicks;
	while ((msTicks - curTicks) < msec){;}		// unsigned math: safe across wrap-around
}
```

**Parameters**

- **msec:** Delay duration in milliseconds (`uint32_t`).

**Example Code**

```c
SysTick_init();
delay_ms(500);  // Block for 500 ms
```

**Notes:** The SysTick interrupt must be running. This busy-wait should not be used inside an ISR that prevents SysTick from advancing.

#### delay_us()

Provides a blocking microsecond delay by accumulating elapsed processor clock cycles from the SysTick down-counter.

```c
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

- **usec:** Delay duration in microseconds (`uint32_t`).

**Example Code**

```c
SysTick_init();
delay_us(500);  // Block for about 500 us
```

**Notes:** Requires a running SysTick counter. The multiplication used for the target cycle count can overflow for very large delays.

#### SysTick_reset()

Resets the current SysTick counter value register (VAL) to zero.

```c
void SysTick_reset(void)
{
	SysTick->VAL = 0;
}
```

**Parameters**

- None.

**Example Code**

```c
SysTick_reset();  // Reset SysTick->VAL
```

**Notes:** This resets the hardware counter value, not the global `msTicks` accumulator.

#### SysTick_val()

Returns the current value of the SysTick down-counter register (VAL).

```c
uint32_t SysTick_val(void) {
	return SysTick->VAL;
}
```

**Parameters**

- None.

**Example Code**

```c
uint32_t currentCount = SysTick_val();
```

**Notes:** This value represents hardware clock cycles remaining in the current SysTick period, not elapsed milliseconds.

---

### Stepper Motor Control

**Header File**

`#include "ecStepper2.h"`

The stepper library drives a four-pin motor using a full-step or half-step FSM. Modes are `HALF(0)`, `FULL(1)`; directions are `DIR_CW(0)`, `DIR_CCW(1)`; timing modes are `MS(0)`, `US(1)`; step count constant is `STEP_PER_REV (64*32)`.

**Function Declarations**

```c
void stepper_init(uint32_t mode, PinName_t *pinStepper);
void stepper_speed (uint32_t speedRPM, uint32_t speed_mode);
void stepper_step(uint32_t steps, uint32_t direction, uint32_t speed_mode);
void stepper_out(uint32_t state);
void stepper_stop(void);
```

#### stepper_init()

Selects full-step or half-step finite state machine (FSM) and initializes the motor coil pins as GPIO outputs.

```c
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

- **mode:** `HALF(0)` or `FULL(1)`.
- **pinStepper:** Pointer to four `PinName_t` values ordered as `[A, B, AN, BN]`.

**Example Code**

```c
PinName_t motorPins[4] = {PB_0, PB_1, PB_2, PB_3};
stepper_init(HALF, motorPins);
```

**Notes:** Call before `stepper_out()`, `stepper_step()`, or `stepper_stop()` so the FSM and pins are initialized.

#### stepper_speed()

Converts a requested motor speed in RPM to a per-step delay in either milliseconds or microseconds.

```c
void stepper_speed (uint32_t speedRPM, uint32_t speed_mode){      // rpm
	// [usec] can be used for a higher accuracy, but needs delay_us() 
	if(speed_mode == MS)
		_step_delay_ms = 60*1000UL/(STEP_PER_REV*speedRPM); 		//in [msec]	
	else if(speed_mode == US)
		_step_delay_us = 60*1000000UL/(STEP_PER_REV*speedRPM); 		//in [microsec]	

}
```

**Parameters**

- **speedRPM:** Requested rotational speed in revolutions per minute. Must be nonzero.
- **speed_mode:** `MS(0)` to update `_step_delay_ms`, or `US(1)` to update `_step_delay_us`.

**Example Code**

```c
stepper_speed(10, MS);  // Compute delay in milliseconds
stepper_speed(10, US);  // Compute delay in microseconds
```

**Notes:** The calculation uses `STEP_PER_REV = 64*32`. Integer division truncates the result; `MS` can give 0 ms at higher speeds. Use the same mode in `stepper_step()`.

#### stepper_step()

Advances the stepper FSM for the requested number of steps in the chosen direction, writing coil outputs and delaying after each step.

```c
void stepper_step(uint32_t steps, uint32_t direction, uint32_t speed_mode){
	// Exit if stepper_init() not called 
	if (fsm == 0) return;
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

- **steps:** Number of motor steps to execute.
- **direction:** `DIR_CW(0)` or `DIR_CCW(1)`; used as an index into the FSM transitions.
- **speed_mode:** `MS(0)` for `delay_ms()`, or `US(1)` for `delay_us()`.

**Example Code**

```c
PinName_t motorPins[4] = {PB_0, PB_1, PB_2, PB_3};
stepper_init(FULL, motorPins);
stepper_speed(10, US);
stepper_step(STEP_PER_REV, DIR_CW, US);
```

**Notes:** The function blocks until the step loop completes, unless externally stopped by changing its internal `_steps` value. `stepper_speed()` and `stepper_step()` must use matching time units.

#### stepper_out()

Writes the four coil-output values stored in the FSM entry for the selected state.

```c
void stepper_out(uint32_t state){
	
	// stepperPins[0]=A, stepperPins[1]=B, ...
	// out[0]=A, out[1]=B, ...

	for(int i=0; i<4; i++){
		GPIO_write(stepperPins[i], fsm[state].out[i]);
	}
}
```

**Parameters**

- **state:** FSM state index: `S0`–`S3` in FULL mode or `S0`–`S7` in HALF mode.

**Example Code**

```c
PinName_t motorPins[4] = {PB_0, PB_1, PB_2, PB_3};
stepper_init(FULL, motorPins);
stepper_out(S0);  // Write coil pattern for S0
```

**Notes:** Initialize the motor first; otherwise the FSM pointer is not set.

#### stepper_stop()

Requests a stop by setting the remaining step count to zero and drives all four motor output pins LOW.

```c
void stepper_stop(void) {
    _steps = 0;    
    
	// All pins DigitalOut '0'
	for(int i=0; i<4; i++){
		GPIO_write(stepperPins[i], LOW);
	}
}
```

**Parameters**

- None.

**Example Code**

```c
PinName_t motorPins[4] = {PB_0, PB_1, PB_2, PB_3};
stepper_init(HALF, motorPins);
stepper_stop();  // Outputs LOW
```

**Notes:** Uses the same initialized motor pin array as `stepper_init()`. The blocking `stepper_step()` routine is not independently scheduled.

---

### STM32F4v2 MCU Initialization

**Header File**

`#include "ecSTM32F4v2.h"`

The top-level course header defines the board pin assignments, FND pin arrays, and `MCU_init()` directly in the header.

**Function Declarations**

```c
void MCU_init(void);
```

#### MCU_init()

Initializes the JKIT/NUCLEO setup: PLL clock, SysTick, LED pins, pull-up buttons, FND pins, and EXTI settings.

```c
void MCU_init(void){
		RCC_PLL_init();                 // System Clock = 84MHz
		SysTick_init();                 // SysTick Timer Initialization
		// Initialize GPIOB_12 for Output
		GPIO_init(LED0_PIN, OUTPUT);    // LED0 for EVAL board	
		GPIO_init(LED7_PIN, OUTPUT);    // LED7 for EVAL board
		
		// Initialize GPIOA_4 for Input Button
		GPIO_init(SW2_PIN, INPUT);  // INPUT for EVAL board
		GPIO_pupd(SW2_PIN, PULL_UP);  // PULL-UP for EVAL board

        // Initialize GPIOD_2 for Input Button
		GPIO_init(SW1_PIN, INPUT);  // INPUT for EVAL board
		GPIO_pupd(SW1_PIN, PULL_UP);  // PULL-UP for EVAL board

        FND_init(pinFND);
        FND_select_init(selectFND);

        // Initialize 7-segment pins
        for(int i=0; i<8; i++){
            GPIO_init_all(pinFND[i], OUTPUT, MEDIUM_SPEED, PUSH_PULL, NO_PUPD);
        }

        // Initialize GPIOA_10 for Output Button
		GPIO_init(selectFND[0], OUTPUT);  // INPUT for EVAL board
		GPIO_otype(selectFND[0], PUSH_PULL);  // PULL-UP for EVAL board
		
		// Initialize EXTI PA_4
		EXTI_init(SW2_PIN, FALL, 10);	
        // Initialize EXTI PD_2
        EXTI_init(SW1_PIN, FALL, 5);	

    // TIMx Default Initialization
    // ...
    // PWM Default Initialization
    // ...        
    // USART Default Initialization
    // ...
    // Others
}
```

**Parameters**

- None.

**Example Code**

```c
#include "ecSTM32F4v2.h"
int main(void) {
    MCU_init();
    while (1) {
        // Application / interrupt-driven logic
    }
}
```

**Notes:** This function is defined inside the uploaded `ecSTM32F4v2.h` and uses the pin arrays and macros declared in that header. Its EXTI setup targets SW2 (PA_4) and SW1 (PD_2).

---
