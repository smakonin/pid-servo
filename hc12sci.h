/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef HC12SCI_H
#define HC12SCI_H

#include "stddef.h"
#include "no_copy.h"
#include "chipio.h"
#include "iostream.h"
#include "scibuf.h"

class hc12sci : public scibuf
{
	private:
		volatile sciport &sci;
		
		virtual bool poll();
		virtual char recv();
		virtual void send(char);
		
	public:
		hc12sci(volatile sciport &, size_t, size_t);
		~hc12sci();
};


#endif
