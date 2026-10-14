/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Won Bitna
Created          : 05-03-2021
Modified         : 10-12-2026
Language/ver     : C++ in VS Code

Description      : Stepper Library. Stepper Motor Control with FSM
/----------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "ecStepper2.h"


// Stepper Motor variable
static PinName_t stepperPins[4];
static volatile uint32_t _steps;
static volatile uint32_t _step_delay_ms = 100;		// millisec	
static volatile uint32_t _step_delay_us = 100000;		// microsec
static const StateStepper_t *fsm;				// points at fsm_full or fsm_half (chosen in stepper_init)
static volatile uint32_t state = 0;				// current FSM state



// FSM States for Full Stepping (S0~S3)
static const StateStepper_t fsm_Full[4] = {	
 	{{S1,S3},{HIGH,HIGH,LOW,LOW}},		// S0 
	{{S2,S0},{LOW,HIGH,HIGH,LOW}},		// S1
	{{S3,S1},{LOW,LOW,HIGH,HIGH}},		// S2
	{{S0,S2},{HIGH,LOW,LOW,HIGH}}		// S3
};

// FSM States for Half Stepping (S0~S7)
static const StateStepper_t fsm_Half[8] = {  
	{{S1,S7},{1,0,0,0}},		// S0
	{{S2,S0},{1,1,0,0}},		// S1
	{{S3,S1},{0,1,0,0}},		// S2
	{{S4,S2},{0,1,1,0}},		// S3
	{{S5,S3},{0,0,1,0}},		// S4
	{{S6,S4},{0,0,1,1}},		// S5
	{{S7,S5},{0,0,0,1}},		// S6
	{{S0,S6},{1,0,0,1}},		// S7
};


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

// Converts Motor [rpm] to step delay in [msec] or [usec]
void stepper_speed (uint32_t speedRPM, uint32_t speed_mode){      // rpm
	// [usec] can be used for a higher accuracy, but needs delay_us() 

	// Divide it by STEP_PER_REV to get one step delay
	if(speed_mode == MS)
		_step_delay_ms = 60*1000UL/(STEP_PER_REV*speedRPM); 		//in [msec]	
	else if(speed_mode == US)
		_step_delay_us = 60*1000000UL/(STEP_PER_REV*speedRPM); 		//in [microsec]	

}

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

// Stepper Motor Output for given state
void stepper_out(uint32_t state){
	
	// stepperPins[0]=A, stepperPins[1]=B, ...
	// out[0]=A, out[1]=B, ...

	for(int i=0; i<4; i++){
		GPIO_write(stepperPins[i], fsm[state].out[i]);
	}
}


// Stop Stepper Motor
void stepper_stop(void) {
    _steps = 0;    
    
	// All pins DigitalOut '0'
	for(int i=0; i<4; i++){
		GPIO_write(stepperPins[i], LOW);
	}
}
