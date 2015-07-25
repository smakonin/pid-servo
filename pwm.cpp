/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "stddef.h"
#include "gmask.h"
#include "chipio.h"
#include "hc12ictlr.h"
#include "pwm.h"

static const int delay1usec = SYSTEM_MHZ; //1 usec
static const int delay2usec = delay1usec * 2;
static const int delay4usec = delay1usec * 4;

pwmdriver::pwmdriver(ictlr &ic, uint p)
: isr(ic, hc12ictlr::is_tc3), first(0), period(p), phase(0), octic(3, true), ocoff(7)
{
	octic.at(tcnt + period / 2);
}

void pwmdriver::attach(pwmchannel *chan)
{
	gmask stop_all_interrupts;

	chan->next = first;
	first = chan;
}

void pwmdriver::handler()
{
	octic.at(octic.at() + period / 2);
	phase = (phase + 1) & 1;
	
	if(phase == 0)
		ocoff.at(octic.at() + period / 2);

	for(pwmchannel *chan = first; chan; chan = chan->next)
		chan->handler(phase, ocoff.at());

}

pwmchannel::pwmchannel(pwmdriver &drv, int chno)
: next(0), driver(drv), duty_cycle(0), newontime(0), ontime(0), ocdur(chno * 4 + 0), ocpwm(chno * 4 + 1), ocbrake(chno * 4 + 2)
{
	gmask stop_all_interrupts;
	
	ocpwm.oc7(0);
	driver.attach(this);
}

float pwmchannel::getduty() const
{
	gmask stop_all_interrupts;
	
	return duty_cycle;
}

void pwmchannel::setduty(float duty)
{
	int dir = duty > 0 ? 1 : -1;
	uint ton = uint(driver.getperiod() * duty * dir);
	uint max_period = driver.getperiod() - delay4usec;

	ton = ton < max_period ? ton : max_period;

	gmask stop_all_interrupts;

	duty_cycle = duty;
	direction = dir;
	newontime = ton;
}

void pwmchannel::handler(int phase, uint next_cycle)
{
	uint period = driver.getperiod();

	if(phase == 0)
	{
		ontime = newontime;
		if(ontime < period / 2)
			ocpwm.at(next_cycle - ontime);

		ocbrake.raise_at(next_cycle + period + delay2usec);

	}
	else
	{
		if(ontime >= period / 2)
			ocpwm.raise_at(next_cycle + period - ontime);

		if(direction >= 0)
			ocdur.raise_at(next_cycle + delay1usec);
		else
			ocdur.drop_at(next_cycle + delay1usec);
	}
}

