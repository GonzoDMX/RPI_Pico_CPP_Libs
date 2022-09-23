/*
 *	STEPPER MOTOR Library for Raspberry Pi Pico
 *
 *	Created by: Andrew O'Shei
 *
 */
 
 
#include "stepper_motor.hpp"
 

StepperMotor::StepperMotor(uint en, uint dir, uint step) : state{step, 0, 0}, en_pin(en), dir_pin(dir), step_pin(step)
{
	step_delay = 1000;
	
    // Initialize direction control
    gpio_init(dir_pin);
    gpio_set_dir(dir_pin, GPIO_OUT);
    gpio_put(dir_pin, 0);
    
    // Initialize step pin
    gpio_init(step_pin);
    gpio_set_dir(step_pin, GPIO_OUT);
    gpio_put(step_pin, 0);
    
	// Initialize and cycle motor driver enable
    gpio_init(en_pin);
    gpio_set_dir(en_pin, GPIO_OUT);
	gpio_put(en_pin, 1);
}

void StepperMotor::enable(bool set)
{
	if (set)
	{
		gpio_put(en_pin, 0);
	}
	else
	{
		gpio_put(en_pin, 1);
	}
}

bool StepperMotor::move_callback(struct repeating_timer *t)
{
	StepperState *data = &(*(StepperState *)t->user_data);

	gpio_put( data->step_pin, 1 );
	sleep_us(5);
	gpio_put( data->step_pin, 0 );
	
	// Increment or decrement steps
	if ( data->current_steps < 0 )
	{
		data->current_steps++;
		data->global_steps--;
	}
	else if ( data->current_steps )
	{
		data->current_steps--;
		data->global_steps++;
	}

	// Stop motor when move is complete
	if ( data->current_steps == 0 )
	{
		return cancel_repeating_timer(t);
	}
	return true;
}

// Set the speed in steps per second
void StepperMotor::set_speed(int64_t speed)
{
	if (!speed)
	{
		step_delay = (int64_t)1000000;
	}
	else
	{
		step_delay = (int64_t)1000000 / speed;
	}
}

void StepperMotor::move_motor(long steps)
{	
	state.current_steps = steps;
	if (state.current_steps < 0)
	{
		gpio_put(dir_pin, 1);
	}
	else
	{
		gpio_put(dir_pin, 0);
	}
	std::cout << "Global Steps: " << state.global_steps << std::endl;
	add_repeating_timer_us(-(step_delay), move_callback, &state, &timer);
}

