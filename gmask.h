// $Id: gmask.h,v 1.11 2009-03-21 04:27:34 smakonin Exp $

#ifndef GMASK_H
#define GMASK_H

#include "stddef.h"
#include "no_copy.h"

class gmask : private no_copy
{
	private:
  		int pstate;

	public:
  		gmask()
  		{
			asm(" 
				tfr	ccr,b		; get current state of mask
				std	%0			; save it
				sei				; mask interrupts globally
				" : "=m" (pstate) : : "d"
				); 
		}
  
		~gmask()
		{
			asm("
				ldd	%0			; get previous state of mask
				tfr	b,ccr		; restore it
				" : : "m" (pstate) : "d"
				);
		}		
};

#endif 

