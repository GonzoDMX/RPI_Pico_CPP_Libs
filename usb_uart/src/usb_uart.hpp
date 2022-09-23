/*
 *	USB UART Library for Raspberry Pi Pico
 *
 *	Created by: Andrew O'Shei
 *
 */
 
 
#ifndef USB_UART_H
#define USB_UART_H

#include <stdio.h>
#include "pico/stdlib.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cstdint>

class UsbUart
{
	private:
		std::string buffer;
		
	public:
		UsbUart();
		
		std::string read();
};

#endif
