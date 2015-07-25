/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef ISR_H
#define ISR_H

#include "stddef.h"
#include "no_copy.h"
#include "error.h"

class isr : private no_copy
{
	private:
		class ictlr &ic;
		uint index;
		friend class ictlr;

		virtual void handler();

	protected:
		isr(class ictlr &, uint);
		virtual ~isr();
};

class ictlr : private no_copy
{
	private:
		uint length;
		class isr **isr_table;

	protected:
		void run_handler(uint index)
		{
			if(isr_table[index])
				isr_table[index]->handler();
			else
				handle_error("no isr handle");
		}

	public:
		ictlr(uint );
		virtual ~ictlr();
		void attach(isr *);
		void detach(isr *);
};

#endif 

