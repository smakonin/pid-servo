/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef TESTPIN_H
#define TESTPIN_H

#include "stddef.h"
#include "no_copy.h"

class testpin : private no_copy
{
	private:
		volatile char *data;
		volatile char *dir;
		char mask;
	
	public:
		testpin(volatile char *da, volatile char *di, int bit)
		: data (da), dir(di), mask(1 << bit)
		{
			*dir |= mask;
		}
		
		~testpin()
		{
			*dir &= ~mask;
		}
		
		void raise()
		{
			*data |= mask;
		}
		
		void lower()
		{
			*data &= ~mask;
		}		
};

#endif
