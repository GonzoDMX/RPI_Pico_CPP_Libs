/*
 *	STEPPER MOTOR Library for Raspberry Pi Pico
 *
 *	Created by: Andrew O'Shei
 *
 */
 
 
#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cstdint>


struct StepperState{
			const uint step_pin;
			long global_steps;
			long current_steps;
		};	

class StepperMotor
{
	private:	
		StepperState state;
		const uint en_pin, dir_pin, step_pin;
		int64_t step_delay;

		struct repeating_timer timer;

		static bool move_callback(struct repeating_timer *t);
		
	public:
		StepperMotor(uint en, uint dir, uint step);

		void enable(bool set);

		void set_speed(int64_t speed);

		void move_motor(long steps);
};


#endif
