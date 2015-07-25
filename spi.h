/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef SPI_H
#define SPI_H

#include "stddef.h"
#include "no_copy.h"
#include "task.h"

class spi : private no_copy
{
	public:
		spi() 
		{
		}

		virtual ~spi()
		{
		}
	
		class user : private no_copy //handle object
		{
			private:
				spi &_spi;
				mutex::lock _lock;
			
			public:
				user(spi &s) : 
				_spi(s), 
				_lock(s._mutex)
				{
				}
				
				void put(void *buf, int bits)
				{
					_spi.put(buf, bits); //reflection
				}

				void get(void *buf, int bits)
				{
					_spi.get(buf, bits);
				}
		};		
		
	private:
		mutex _mutex;
		virtual void put(void *buf, int bits) = 0;
		virtual void get(void *buf, int bits) = 0;
		friend class user;
};

#endif

