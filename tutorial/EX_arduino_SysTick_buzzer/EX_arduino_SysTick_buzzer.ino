#include "STM32TimerInterrupt.h"

#define HW_TIMER_INTERVAL_MS  1000

STM32Timer ITimer(TIM1);    // Init STM32 timer TIM1

// constants won't change. They're used here to set pin numbers:
const int ledPin =  13;   // the number of the LED pin
const int buzzPin = 8;    // the number of the buzzer pin

// variables will change:
int buzzState = LOW;
int cnt = 0;

void setup() {
  // initialize the LED pin as an output:
  // your code

  // Interval in microsecs
  // your code

  // Timer interrupt every 1sec
  // your code
}

void loop(){
  if (buzzState == HIGH)
    tone(buzzPin, 100);
    
  else if (buzzState == LOW)
    noTone(buzzPin);
}

// Whenever ISR Timer interrupts, this function is excuted.
void timerInterrupt(){
  // Use 'cnt' and 'buzzState' variables
  // your code 
  
}