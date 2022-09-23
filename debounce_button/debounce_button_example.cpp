/*
*	Example usage for: DEBOUNCE BUTTON Library for Raspberry Pi Pico
*
*	Created by: Andrew O'Shei
*
*	Description:	This library allows the use of buttons on the RPI
*					Pico's GPIO pins, it includes a debounce delay in
*					order to avoid false button presses
*/

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include "src/debounce_button.hpp"

// GPIO Pin used to read the button presses
const uint BUTTON_PIN = 2;

// Sets the delay in milliseconds before the
// button can be read again after a press or release
uint32_t DB_DELAY = 50;

// Declare a DebounceButton Object
DebouncButton db_button = DebounceButton(BUTTON_PIN, DB_DELAY);

// Declaration of an example callback function for the debounce button
// Note:	Callback functions must take pin_num and state as arguments
//			pin_num and state are returned from the button object when
//			a button press or release event triggers a callback
void example_callback(int pin_num, int state);

// Declare LED Pin so the debounc button has something to do
const uint LED_PIN = 25;

// Enter main program function
int main()
{
	// Setup the LED Pin GPIO
	gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Set the debounce button's callback function
    db_button.set_callback(example_callback);
    
    // Enter main program loop here
    while (1)
    {
    	// Update the button object in the main program loop to check
    	// if an event has occurred
    	db_button.update();
    }
}

// Callback function called when button event has occurred
// When button is pressed the RPI Pico's LED turns on
// When the button is released the RPI Pico's LED turns off
void example_callback(int pin_num, int state)
{
	// If button is pressed
	if (state)
	{
		gpio_put(LED_PIN, 1);
	}
	// Else button is released
	else
	{
		gpio_put(LED_PIN, 0);
	}
}
