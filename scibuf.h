/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef SCIBUF_H
#define SCIBUF_H

#include "stddef.h"
#include "no_copy.h"
#include "iostream.h"

class scibuf : public streambuf, private no_copy
{
	private:
		char *rxbuf;
		char *rxend;
		char *txbuf;
		char *txend;
		
		virtual bool poll() = 0;
		virtual char recv() = 0;
		virtual void send(char a) = 0;

	protected:
		virtual int sync();
		virtual int overflow(int);
		virtual int underflow();

	public:
		scibuf(size_t, size_t);
		virtual ~scibuf();
};

#endif
