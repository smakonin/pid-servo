/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "scibuf.h"

scibuf::scibuf(size_t rxlen, size_t txlen)
: rxbuf(new char[rxlen]), rxend(rxbuf + rxlen), txbuf(new char[txlen]), txend(txbuf + txlen)
{
	setg(rxbuf, rxend, rxend);
	setp(txbuf, txend);
}

scibuf::~scibuf()
{
	delete rxbuf;
	delete txbuf;
}

int scibuf::sync()
{
	for(char *p = txbuf; p < pptr(); p++)
		send(*p);

	setp(txbuf, txend);
	return 0;	
}

int scibuf::overflow(int c)
{
	sync();
	return sputc(c);
}

int scibuf::underflow()
{
	char *p = rxbuf;

	do
	{
		*p++ = recv();
	} while(p < rxend && poll());

	setg(rxbuf, rxbuf, p);
	return rxbuf[0];	
}

