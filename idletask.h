/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef IDLETASK_H
#define IDLETASK_H

#include "stddef.h"
#include "no_copy.h"
#include "task.h"

class idletask : public task
{
	protected:
		virtual void main()
		{
			while(true)
			{
			}
		}

	public:
		idletask(size_t size, int p) : 
		task(size, p)
		{ 
			main();
		}
};

#endif
