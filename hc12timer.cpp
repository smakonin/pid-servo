/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "hc12ictlr.h"
#include "hc12timer.h"

hc12timer::hc12timer(size_t stack, int p, ictlr &ic)
: timer(stack, p, ic, hc12ictlr::is_rti, 1 << (_rtr - 1))
{
	rtictl = rti + _rtr;
	fork();
}

hc12timer::~hc12timer()
{
	rtictl &= ~_rtr;
}

void hc12timer::handler()
{
	rtiflg = rti;
	timer::handler(); 	
}
