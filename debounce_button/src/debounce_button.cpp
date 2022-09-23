/*
*	DEBOUNCE BUTTON Library for Raspberry Pi Pico
*
*	Created by: Andrew O'Shei
*
*/


#include "debounce_button.hpp"


DebounceButton::DebounceButton(uint pin, uint32_t delay)
{
	this->pin = pin;
	this->delay = delay;
	time = to_ms_since_boot(get_absolute_time());
	gpio_init(pin);
	if (gpio_get(this->pin))
	{
		state = 1;
	}
	else
	{
		state = 0;
	}
}


DebounceButton::DebounceButton(uint pin, uint32_t delay, int pull_dir)
{
	this->pin = pin;
	this->delay = delay;
	time = to_ms_since_boot(get_absolute_time());
	gpio_init(pin);
	// Set pullup direction
	if (pull_dir)
	{
		if (pull_dir == 1)
		{
			gpio_pull_up(pin);
		}
		else if (pull_dir == 2)
		{
			gpio_pull_down(pin);
		}
	}
	// Initialize State
	if (gpio_get(this->pin))
	{
		state = 1;
	}
	else
	{
		state = 0;
	}
}

int DebounceButton::update()
{
	if ((to_ms_since_boot(get_absolute_time()) - time) > delay)
	{
		if (gpio_get(pin) && !state)
		{
			time = to_ms_since_boot(get_absolute_time());
			state = 1;
			if (btn_callback)
			{
				btn_callback(pin, state);
			}
			return 1;
		}
		else if (!gpio_get(pin) && state)
		{
			time = to_ms_since_boot(get_absolute_time());
			state = 0;
			if (btn_callback)
			{
				btn_callback(pin, state);
			}
			return 1;
		}
	}
	return 0;
}

int DebounceButton::get_state()
{
	return state;
}

