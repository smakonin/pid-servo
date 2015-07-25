/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef HC12SPI_H
#define HC12SPI_H

#include "stddef.h"
#include "no_copy.h"
#include "chipio.h"
#include "spi.h"

class hc12spi : public spi
{
	private:
		volatile spiport &_port; //as def in chipio

		virtual void put(void *buf, int bits)
		{
			char *p = static_cast<char *>(buf);
			for(int i = 0; i < bits / 8; i++)
			{
				_port.spdr = *p++;
				while(_port.spsr & _port.spif == 0)
				{
				}
			}
		}

		virtual void get(void *buf, int bits)
		{
			char *p = static_cast<char *>(buf);
			for(int i = 0; i < bits / 8; i++)
			{
				_port.spdr = 0;
				while((_port.spsr & _port.spif) == 0)
				{
				}

				*p++ = _port.spdr;
			}
		}

	public:
		hc12spi(volatile spiport &s) :
		_port(s)
		{
			ddrs |= 0xe0; //turns on slave select (ss), sck, mosi bits
			_port.spcr1 = _port.spe | _port.mstr | _port.cpha; //config the port
			_port.spdr = 0; //send 1 byte to clear port
		}

		virtual ~hc12spi()
		{
			_port.spcr1 = _port.cpha;
		}
};

#endif

