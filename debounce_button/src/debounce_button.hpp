/*
*	DEBOUNCE BUTTON Library for Raspberry Pi Pico
*
*	Created by: Andrew O'Shei
*
*/



#ifndef DEBOUNCE_BUTTON_H
#define DEBOUNCE_BUTTON_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <functional>


class DebounceButton
{
	private:
		uint pin;
		int state;

		bool event;

		uint32_t delay;
		uint32_t time;

		int pull_dir;

		std::function<void(int, int)> btn_callback;

	public:
		DebounceButton(uint pin, uint32_t delay);
	
		// An example of the constructor which inits pull_up/down TODO change to ENUM
		DebounceButton(uint pin, uint32_t delay, int pull_dir);

		void set_callback(std::function<void(int, int)> callback) {
			btn_callback = std::bind(callback, std::placeholders::_1, std::placeholders::_2);
		}

		int update();

		int get_state();		
};

#endif
