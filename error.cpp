/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "stddef.h"
#include "chipio.h"
#include "testpin.h"
#include "iostream.h"
#include "hc12sci.h"
#include "error.h"

/*void handle_error() 
{
	testpin led(&portp, &ddrp, 7);
	led.raise();
	while(true)
	{
	}	
}*/

void handle_warning(const char *text) 
{	
	hc12sci mysci(sci0, 16, 32);
	ostream sout(&mysci);
	istream sin(&mysci);
	
	sout << endl << text;
}

void handle_error(const char *text) 
{	
	hc12sci mysci(sci0, 16, 32);
	ostream sout(&mysci);
	istream sin(&mysci);
	
	sout << endl << text << endl << flush;
	
	while(true)
	{
		int c = sin.get();
		sout << char(c) << flush;
	}
}

void pure_virtual()
{
	handle_error("call to pure virtual");
}
