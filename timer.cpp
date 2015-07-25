/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "timer.h"

timer *timer::inst;
//uint ticks_since_dawn = 0;

timer::timer(size_t size, int p, ictlr &ic, int index, int r)
: task(size, p), isr(ic, index), rate(r)
{
	inst = this;
}

timer::~timer()
{
	inst = 0;
}

void timer::delay(int millisec)
{
	inst->delta_list.block(millisec);
}

/*uint timer::gettime()
{
    return ticks_since_dawn;
}*/

/*uint timer::until(uint millisec)
{
    uint diff = ticks_since_dawn - millisec;
    
    if(millisec < ticks_since_dawn)
    {
        inst->delta_list.block(diff);
        return diff;
    }
    
    return 0;
}*/

void timer::main()
{
	while(true)
	{
		ticker.block();
		//ticks_since_dawn += rate;
		for(int i = 0; i < rate; i++)
		{
			delta_list.deincroment();
			while(delta_list.zero())
				delta_list.unblock();
		}
	}
}

void timer::handler()
{
	ticker.unblock();
}
