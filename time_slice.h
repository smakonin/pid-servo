/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef TIME_SLICE_H
#define TIME_SLICE_H

#include "stddef.h"
#include "no_copy.h"
#include "task.h"
#include "timer.h"
#include "testpin.h"

class time_slice : public task
{		
	private:
	    int interval;
	    
	protected:
		virtual void main()
		{
			while(true)
			{
				timer::delay(interval);
				slice();
			}
		}

	public:
		time_slice(size_t size, int p, int t) : task(size, p), interval(t)
		{ 
			fork();
		}
};

#endif
