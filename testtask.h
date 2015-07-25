/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef TESTTASK_H
#define TESTTASK_H

#include "stddef.h"
#include "no_copy.h"
#include "task.h"
#include "timer.h"
#include "testpin.h"

class testtask : public task
{
	private:
		int millisec;
		testpin tp;
		
	protected:
		virtual void main()
		{
			while(true)
			{
				tp.raise();
				timer::delay(1);
				tp.lower();
				timer::delay(millisec);
			}
		}

	public:
		testtask(size_t size, int p, int pin, int n) : 
		task(size, p), 
		millisec(n),  
		tp(&portdlc, &ddrdlc, pin)
		{ 
			fork();
		}
};

#endif
