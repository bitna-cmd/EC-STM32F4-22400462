/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 10-12-2026
Language/ver     : C++ in VS Code

Description      : Stepper Library. Stepper Motor Control with FSM
/----------------------------------------------------------------*/

#include "stm32f411xe.h"
#include "ecPinNames.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecSysTick2.h"
			
#ifndef __EC_STEPPER2_H
#define __EC_STEPPER2_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

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


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __EC_STEPPER2_H
