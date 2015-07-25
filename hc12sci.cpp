/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "hc12sci.h"
#include "task.h"

hc12sci::hc12sci(volatile sciport &s, size_t rxlen, size_t txlen)
: scibuf(rxlen, txlen), sci(s)
{
	sci.sccr2 |= (sci.te | sci.re); //control reg, tx enable, rx enable
}

hc12sci::~hc12sci()
{
	sci.sccr2 &= ~(sci.te | sci.re);
}

bool hc12sci::poll()
{
	return sci.scsr1 & sci.rdrf; //rx data reg fll
}

char hc12sci::recv()
{
	while(!poll())
	{
		task::yield();
	}
		
	return sci.scdrl; //sci data reg low
}

void hc12sci::send(char c)
{
	while(!(sci.scsr1 & sci.tdre)) //tx data reg empty
	{
		task::yield();
	}
	
	sci.scdrl = c;
}
