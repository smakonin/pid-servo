/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef HC12TIMER_H
#define HC12TIMER_H

#include "stddef.h"
#include "no_copy.h"
#include "chipio.h"
#include "timer.h"

class hc12timer : public timer
{
	private:
		const int _rtr = rtr1;
		virtual void handler();

	public:
		hc12timer(size_t, int, ictlr &);
		virtual ~hc12timer();
};

#endif
