# LAB: Timer & PWM

**Date:** 2026-11-04

**Author/Partner:** Won Bitna

**Demo Video:** Youtube link!!!!!!!!!!!!

## Introduction

In this lab, I created a simple program that control a sevo motor and a DC motor with PWM output.

### Requirement

**Hardware**

* MCU
  * NUCLEO-F411RE (disconnected JKIT Eval Board)
* Actuator/Sensor/Others:
  * RC Servo Motor (SG90)
  * DC motor (5V)
  * DC motor driver(LS9110s or L298N)

**Software**

* PlatformIO, CMSIS, EC\_HAL library

***

## Prelab: Timer Out Register

I refer to [PreLAB: Timer Interrupt & PWM](/ec/ec-course/lab/prelab-timer-interrupt-and-pwm.md)

I declared and defined the following functions in my library. 

**TIMER Interrupt API**

```c
// Timer Update Interrupt Initialization
void TIM_UI_init(TIM_TypeDef* TIMx, uint32_t msec);     // 16-bit  msec < 65,530 msec 
void TIM_UI_init_us(TIM_TypeDef* TIMx, uint32_t usec);  // 16-bit  usec < 65,530 usec 

// Timer Update Interrupt On/OFf
void TIM_UI_enable(TIM_TypeDef* TIMx);
void TIM_UI_disable(TIM_TypeDef* TIMx);

// Timer Update Interrupt Flag
uint32_t is_UIF(TIM_TypeDef *TIMx);
void clear_UIF(TIM_TypeDef *TIMx);
```

**PWM API**

```c
//  Low Frequency PWM initialization in msec. (below 1kHz)
void PWM_init(PinName_t pinName, uint32_t msec);	// 1 to 6,553 msec (16-bit)
//  High-Frequency PWM initialization in usec (1kHz to 100 kHz)
void PWM_init_us(PinName_t pinName, uint32_t usec);	// 10 usec and up
// Duty ratio 0~1.0
void PWM_duty(PinName_t pinName, float duty);
// Set Pulse width in msec
void PWM_pulsewidth(PinName_t pinName, uint32_t pulse_width_ms);
// Set Pulse width in usec
void PWM_pulsewidth_us(PinName_t pinName, uint32_t pulse_width_us);
```

***

## Tutorial: DC Motor Driver

I learned how to connect a DC motor to the LS9110s motor driver

<https://ykkim.gitbook.io/ec/ec-course/tutorial/tutorial-dcmotor-motor-driver-connection>

***

## Problem 0: STM-Arduino

I created a simple program to control a DC motor using a PWM input signal.

* Connect the DC motor to the DC motor driver
* Pressing the user button will turn on the DC motor

### Procedure

1. Create a new project under the directory **`lab\`**
2. Open *Arduino IDE* and Create a new program named as ‘**TU\_arduino\_PWM.ino**’.
3. Write the following code.
4. Upload and Run

{% code expandable="true" %}

```c
const int pwmPin = 11;   // PWM pin
const int buttonPin = 3;  // button pin

int buttonState = HIGH;

void setup() {
  pinMode(pwmPin, OUTPUT);
 
 // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), motorOperation, CHANGE);
}

void loop() {

  if (buttonState == LOW){
    for (int i = 0; i < 10; i++){
      analogWrite(pwmPin, 100 + 10*i);
      delay(100);
    }
  
    for (int i = 10; i > 0; i--){
      analogWrite(pwmPin, 100 + 10*i);
      delay(100);
    }
  }
  else{
    analogWrite(pwmPin, 0);
  }
}

void motorOperation(){
  buttonState = digitalRead(buttonPin);
}
```

{% endcode %}

***

## Problem 1: RC servo motor

An RC servo motor is a lightweight motor with high output power. It is used to control rotation angles of approximately 180 degrees (90 degrees in each direction) and is commonly applied in RC cars and small-scale robots. The angle of the motor can be controlled by the pulse width (duty ratio) of a PWM signal. The PWM period should be set to 20ms (or 50Hz). Refer to the datasheet of the RC servo motor for detailed specifications

![image](https://user-images.githubusercontent.com/38373000/195773601-f0f19e35-0a6f-49af-aa87-574c86bfec62.png)

I made a program that changes the angle of the RC servo motor that rotates back and forth from 0 deg to 180 degree within a given period of time.

The procedure is as below.

* Connect the RC servo motor to MCU pin (PA15) , VCC and GND
  * Use Port A Pin 15 as PWM output pin for TIM2\_CH1.
  * Use Timer interrupt of period 500msec.
* Increase the angle of RC servo motor from 0° to 180° with a step of 10° every 500msec.
* After reaching 180°, decrease the angle back to 0°.
  * Use timer interrupt IRQ.
* When the user button (PA\_4) is pressed, it should reset to the angle 0° and start over.
  * Use EXT interrupt.

> You need to observe how the PWM signal output is generated as the input button is pushed, using an oscilloscope. You need to capture the Oscilloscope output in the report.

### Procedure

1. Create a new project under the directory `EC\lab\`

* Enviornment: “**LAB\_PWM\_RC”.**
* Source File: “**LAB\_PWM\_RC.c”**

> You MUST write your name on the source file inside the comment section.

\
2\. You must modify the `platformio.ini` **,** to add new environment.

#### Configuration

| Type                       | Port - Pin      | Configuration                                  |
| -------------------------- | --------------- | ---------------------------------------------- |
| **Button**                 | (PC13)          | DIN, Pull-Up                                   |
| **PWM**                    | TIM2\_CH2 (PA1) | TIM2 (PWM) period: 20msec, Duty : 0.5\~2.5msec |
| **Timer Update Interrupt** | TIM3            | TIM3: Timer Interrupt of 500 msec              |

####

#### Circuit Diagram

> You need to include the circuit diagram (if necessary)

![image](https://user-images.githubusercontent.com/38373000/192134563-72f68b29-4127-42ac-b064-2eda95a9a52a.png)

####

#### Code

Your code goes here:

Explain your source code with necessary comments.

```
// YOUR MAIN CODE ONLY
// YOUR CODE
```

#### Results

Experiment images and results

> Show experiment images /results

Add [demo video link](https://github.com/ykkimhgu/course-doc/blob/master/ec-course/lab/link/README.md)

#### Discussion

1. Derive a simple logic to calculate CRR and ARR values to generate x\[Hz] and y\[%] duty ratio of PWM. How can you read the values of input clock frequency and PSC?

> Answer discussion questions

2. What is the smallest and highest PWM frequency that can be generated for Q1?

   > Answer discussion questions

***

## Problem 2: DC motor

> **you MUST read** [Tutorial: DC motor driver connection](https://ykkim.gitbook.io/ec/ec-course/tutorial/tutorial-dcmotor-motor-driver-connection)

### Problem

The program needs to design a smart mini-fan device that runs only when the face is near the fan. Otherwise stops the fan from running.

* As the button **B1** is pressed, change the fan velocity Mode.
* The velocity MODE(states) are
  * MODE(state): **OFF(0%), MID(50%), HIGH(100%)**
* PAUSE: When the object(face) is detected neraby, it automatically pauses the fan temporarily.
  * PAUSE: the MODE should NOT be changed if the button **B1** is pressed
* RESUME: When the object(face) is away, it automatically resumes the fan running
  * It must maintain return to the previous MODE run at the speed of the current MODE
* LED
  * MODE=OFF, LED=OFF
  * MODE=MID, HIGH, LED=ON
  * PAUSE, LED=Blinking 1 sec
* Serial Display
  * Print the Mode, PWM duty ratio and other necessary information every 2seconds
* Use FSM to design the code
  * Draw a FSM(finite-state-machine) table and state diagram
  * Example Table. See below for example codes

<figure><img src="https://3453146497-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MgmrEstOHxu62gXxq1t%2Fuploads%2Fgit-blob-ad2250252c1942a9c8e45d9e7e5d23bdfe1e17f5%2Fimage.png?alt=media" alt=""><figcaption></figcaption></figure>

### Procedure

1. Create a new environment

* Environment: “**LAB\_PWM\_DC”**
* Source FIle: “**LAB\_PWM\_DC.c”**

> You MUST write your name on the source file inside the comment section.

2\. You must modify the `platformio.ini` **,** to add new environment.

#### Configuration

| Function                   | Port - Pin        | Configuration                       |
| -------------------------- | ----------------- | ----------------------------------- |
| **Button**                 | PC13              | DIN, Pull-Up                        |
| **Direction Pin**          | PC2               | DOUT, Push-Pull                     |
| **PWM Timer**              | TIM2\_CH1 (PA\_0) | TIM2 (PWM) period: **1msec (1kHz)** |
| **Timer Update Interrupt** | TIM3              | TIM3: Timer Interrupt of 500 msec   |
| **LED**                    |                   |                                     |
| **IR Proximity Sensor**    |                   | DIN, Pull-Up                        |

#### Circuit Diagram

> You need to include the circuit diagram

![image](https://user-images.githubusercontent.com/38373000/192134563-72f68b29-4127-42ac-b064-2eda95a9a52a.png)

#### Code

Your code goes here:

Explain your source code with necessary comments.

```
// YOUR MAIN CODE ONLY
// YOUR CODE
```

#### Results

Experiment images and results

> Show experiment images /results

Add [demo video link](https://github.com/ykkimhgu/course-doc/blob/master/ec-course/lab/link/README.md)

### Reference

List of all references used (github, blog, paper, etc)

```

```

## Troubleshooting

#### 1. motor PWM duty ratio for different DIR

When, DIR=0 duty=0.8--> PWM 0.8 // 실제 모터에 전달되는 pwm

Whe, DIR=1 duty=0.8--> PWM 0.2 // 실제 모터에 전달되는 PWM

* Sample Solution

```c++
float targetPWM;  // pwm for motor input 
float duty=abs(DIR-targetPWM); // duty with consideration of DIR=1 or 0

PWM_duty(PWM_PIN, duty);
```

#### 2. Motor does not run under duty 0.5

Configure motor PWM period above 1kHz

#### 3. Check and give different Interrupt Priority

Check if you have different NVIC priority number for each IRQs

####