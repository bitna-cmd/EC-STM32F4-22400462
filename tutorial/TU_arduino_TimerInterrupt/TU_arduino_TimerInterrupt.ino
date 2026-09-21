#include "STM32TimerInterrupt.h"

#define HW_TIMER_INTERVAL_MS  1000

STM32Timer ITimer(TIM1);    // Init STM32 timer TIM1

const int ledPin =  13;

void setup() {
  pinMode(ledPin, OUTPUT);

  ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, timerInterrupt);
}

void loop(){
}

void timerInterrupt(){
  digitalWrite(ledPin, !digitalRead(ledPin));
}