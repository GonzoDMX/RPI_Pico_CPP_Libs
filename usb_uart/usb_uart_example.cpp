/*
 *	Usage example for: SERVO MOTOR CONTROL Library for Raspberry Pi Pico
 *
 *	Created by: Andrew O'Shei
 *
 *	Description:	Wraps the USB UART serial interface in an object and
 *					providessome helper functions to simplify the use of
 *					the interface
 */

#include "pico/stdlib.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include "src/usb_uart.hpp"

// Declare the USB UART object
UsbUart my_usbSerial = UsbUart();

// Main program
int main()
{
  // Main loop
  while(1)
  {
    // Get a data string from the usb serial object 
    std::string my_data = my_usbSerial.read();
    // If data was received
    if (!my_data.empty())
    {
      // Echo back the received data
      std::cout << my_data << std::endl;
    }
  }
}
