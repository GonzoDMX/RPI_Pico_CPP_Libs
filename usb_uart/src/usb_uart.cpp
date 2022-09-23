/*
 *	USB UART Library for Raspberry Pi Pico
 *
 *	Created by: Andrew O'Shei
 *
 */
 
 
#include "usb_uart.hpp"


UsbUart::UsbUart()
{
  stdio_usb_init();
}

std::string UsbUart::read()
{
  if (stdio_usb_connected())
  {
    uint32_t c = getchar_timeout_us(0);
    if (c != 0xFFFFFFFF)
    {
      buffer.clear();
      while ( c != '\n')
      {
        buffer.push_back(c);
        c = getchar_timeout_us(1000000);
      }
      return buffer;
    }
  }
  return std::string();
}



/*
std::vector<char> UsbUart::get_data()
{
  if (stdio_usb_connected())
  {
    uint32_t c = getchar_timeout_us(0);
    if (c != 0xFFFFFFFF)
    {
      while ( c != 0xFFFFFFFF && c != 0x0A )
      {
        buffer.push_back(c);
        c = getchar_timeout_us(0);
      }
      if ( c == 0x0A )
      {
        buffer.push_back(0x0A);
        std::vector<char> ret = buffer;
        buffer.clear();
        return ret;
      }
    }
  }
  return {};
}
*/

