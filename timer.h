/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef TIMER_H
#define TIMER_H

#include "stddef.h"
#include "no_copy.h"
#include "isr.h"
#include "task.h"

class timer : public task, public isr
{
	private:
		int rate;
		static timer *inst;
		delta_task_list delta_list;
		task_list ticker;
		virtual void main();

	protected:
		timer(size_t, int, ictlr &, int index, int rate); //# of millisec per interrupt
		virtual ~timer();
		virtual void handler();

	public:
		static void delay(int millisec);
		//static uint gettime();
		//static uint until(uint millisec);
};

#endif
