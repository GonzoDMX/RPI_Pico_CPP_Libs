/*
 *	SERVO MOTOR CONTROL Library for Raspberry Pi Pico
 *
 *	Created by: Andrew O'Shei
 *
 */



#include "servo_pio.hpp"


ServoPio::ServoPio(const uint pwm, PIO pio, const uint sm, uint32_t min_dc, uint32_t max_dc, float freq) : PWM_PIN(pwm), pio(pio), sm(sm), min_dc(min_dc), max_dc(max_dc), frequency(freq)
{
	init_servo_pio();
}

// Move Servo to position
void ServoPio::set_position(uint angle)
{
	uint32_t ms = (angle / 180.0f) * diff_dc + min_dc;
	
	// Error value out of bounds
	if (ms > max_dc)
	{
		return;
	}

	uint level = (ms / 20000.f) * period;
	pio_pwm_set_level(pio, sm, level);
}

// Initialize PIO and setup the servo
void ServoPio::init_servo_pio()
{
	diff_dc = max_dc - min_dc;
    uint offset = pio_add_program(pio, &servo_pio_program);
	// Make the clock slower
    uint clk_div = 64;

    servo_pio_program_init(pio, sm, offset, clk_div, PWM_PIN);

    uint cycles = clock_get_hz(clk_sys) / (frequency * clk_div);
    period = (cycles -3) / 3;  
    pio_pwm_set_period(pio, sm, period);
}

// Write `period` to the input shift register
void ServoPio::pio_pwm_set_period(PIO pio, uint sm, uint32_t period) {
	pio_sm_set_enabled(pio, sm, false);
	pio_sm_put_blocking(pio, sm, period);
	pio_sm_exec(pio, sm, pio_encode_pull(false, false));
	pio_sm_exec(pio, sm, pio_encode_out(pio_isr, 32));
	pio_sm_set_enabled(pio, sm, true);
}

// Write `level` to TX FIFO. State machine will copy this into X.
void ServoPio::pio_pwm_set_level(PIO pio, uint sm, uint32_t level) {
	pio_sm_put_blocking(pio, sm, level);
}

