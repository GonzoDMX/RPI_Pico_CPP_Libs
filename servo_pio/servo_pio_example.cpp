/*
 *	Usage example for: SERVO MOTOR CONTROL Library for Raspberry Pi Pico
 *
 *	Created by: Andrew O'Shei
 *
 *	Description:	This library allows control of a basic servomotor using
 *					the RPI Pico's PIO state machine.
 */
 

#include "pico/stdlib.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include "src/servo_pio.hpp"


// Declare the pin used to control the servo motor
const uint SERVO_PIN = 2;

// Set the min and max Pulse width (in microseconds)
// The min should correspond to the servo in 0 position
// The max should correspond to the servo at 180 position
// Note:	For accurate positions, min_dc and max_dc may need
//			adjustment for the particular servo you are using
uint32_t min_dc = 500;
uint32_t max_dc = 2600;

// Declare which state machine will be used, there are 4
// (0-3) for each of the RPI Pico's 2 PIOs
const uint state_machine = 0;

// Declare a ServoPio object
// this will be reference to control the servomotor
ServoPio my_servo = ServoPio(SERVO_PIN, pio0, state_machine, min_dc, max_dc);

// Main program function
int main()
{
	// Main program loop
	while(1)
	{
		// Set the servomotor to an angle of 0 degrees
		my_servo.set_position(0);
		// Wait 2s for movement to complete
		sleep_ms(2000);
		// Set the servomotor to an angle of 180 degrees
		my_servo.set_position(180);
		// Wait again for 2 secs
		sleep_ms(2000);
	}
}
