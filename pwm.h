/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef PWM_H
#define PWM_H

#include "stddef.h"
#include "no_copy.h"
#include "isr.h"
#include "opcompare.h"

class pwmdriver : public isr
{
	private:
		void attach(class pwmchannel *);

		uint getperiod() const
		{
			return period;
		}
		
		friend class pwmchannel;

	private:
		class pwmchannel *first;
		const uint period;
		int phase; // 0 or 1
		opcompare octic; 
		opcompare ocoff;

	protected:
		virtual void handler();

	public:
		pwmdriver(ictlr &, uint); 
};

class pwmchannel : private no_copy
{
	private:
		pwmchannel *next;
		void handler(int, uint);
		friend class pwmdriver;

	private:
		pwmdriver &driver;
		float duty_cycle;
		int direction;
		uint newontime;
		uint ontime;
		opcompare ocdur;	
		opcompare ocpwm;	
		opcompare ocbrake;	

	public:
		pwmchannel(pwmdriver &, int);
		float getduty() const;
		void setduty(float);
};

#endif
