/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef OPCOMPARE_H
#define OPCOMPARE_H

#include "stddef.h"
#include "no_copy.h"
#include "chipio.h"

class opcompare : private no_copy
{
	private:
		volatile uint &tcx; 
		uint mask;
		uint level;
		uint mode;

	public:
		opcompare(int num, bool enabled = false) : tcx((&tc0)[num]), mask(1 << num), level(ol << num * 2), mode(om << num * 2)
		{
			tscr |= (ten | tffca);
			tcx = tcnt - 1; // push first event into the future
			tios |= mask; // choose compare mode

			if(enabled)
			{
				tflg1 = mask; // tflag1 gets mask, reset any existing int request
				tmsk1 |= mask; // enable int from this channel
			}
		}

		~opcompare()
		{
			tmsk1 &= ~mask;
			tios &= ~mask;
			tctl1 &= ~(mode|level);
			oc7m &= ~mask;
			oc7d &= ~mask;
		
		}
	
		unsigned at() const
		{
			return tcx;
		}


		void at(uint time)
		{
			tcx = time;
		}

		void raise_at(uint time)
		{
			tctl1 |= mode;
			tctl1 |= level;
			at(time);
		}

		void drop_at(uint time)
		{
			tctl1 |= mode;
			tctl1 &= ~level;
			at(time);
		}
	
	
		void oc7(int level)
		{
			if(level < 0) // disconnect oc7
			{
				oc7m &= ~mask; // oc7 no longer controls output line
				oc7d &= ~mask;
			}
			else // oc7 also drives this pin
			{
				if(level)
					oc7d |= mask;
				else
					oc7d &= ~mask;

				oc7m |= mask;
			}
		}
};


#endif

