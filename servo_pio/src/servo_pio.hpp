/*
 *	SERVO MOTOR CONTROL Library for Raspberry Pi Pico
 *
 *	Created by: Andrew O'Shei
 *
 */



#ifndef SERVO_PIO_H
#define SERVO_PIO_H

#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "servo_pio.pio.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cstdint>


class ServoPio
{
	private:
		const uint PWM_PIN;
		
		PIO pio;
		const uint sm;
		
		uint32_t min_dc;
		uint32_t max_dc;
		uint32_t diff_dc;
		float frequency;
		uint32_t period;
		
		void init_servo_pio();
		
		void pio_pwm_set_period(PIO pio, uint sm, uint32_t period);
		
		void pio_pwm_set_level(PIO pio, uint sm, uint32_t level);

	public:
		ServoPio(const uint pwm, PIO pio = pio0, const uint sm = 0, uint32_t min_dc = 500, uint32_t max_dc = 2600, float freq = 50.0f);
		
		void set_position(uint angle);
};

#endif
