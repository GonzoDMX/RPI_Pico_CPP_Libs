/*
 *	Usage example for: STEPPER MOTOR Library for Raspberry Pi Pico
 *
 *	Created by: Andrew O'Shei
 *
 *	Description:	This library can be used to control stepper motors using
 *					a stepper motor driver (like the TMC2208), which uses
 *					STEP, DIR and ENABLE pins. Steps are made using timed
 *					interrupts.
 */


#include "pico/stdlib.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include "src/stepper_motor.hpp"

// Declare the GPIO pins used for the stepper motor driver
const uint ENABLE_PIN = 2;
const uint DIR_PIN = 3;
const uint STEP_PIN = 4;


// Declare the StepperMotor object
// This is referenced to control the stepper motor driver
StepperMotor my_stepper = StepperMotor(ENABLE_PIN, DIR_PIN, STEP_PIN);

// Main program
int main()
{
	// Enable the stepper motor driver (sets the enable pin low)
	my_stepper.enable(true);
	
	// Set the stepper motors speed in steps per second
	my_stepper.set_speed(2000);
	
	// Main loop
	while(1)
	{
		// Move the stepper motor 5000 steps clockwise
		my_stepper.move_motor(5000);
		// Wait 5 seconds for movement to complete
		sleep_ms(5000);
		// Move the stepper motor 5000 steps anti-clockwise
		my_stepper.move_motor(-5000);
		// Wait 5 seconds for movement to complete
		sleep_ms(5000);
	}
}
