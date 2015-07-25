/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "isr.h"

isr::isr(class ictlr &ii, uint i)
: ic(ii), index(i)
{
	ic.attach(this);
}	

isr::~isr()
{
	ic.detach(this);
}

void isr::handler()
{
}

ictlr::ictlr(uint len) : 
length(len),
isr_table(new isr *[length])
{
	for(uint i = 0; i < length; i++)
		isr_table[i] = 0;
}

ictlr::~ictlr()
{
	delete[] isr_table;
}

void ictlr::attach(isr *i)
{
	if(i->index < length)
		isr_table[i->index] = i;
}

void ictlr::detach(isr *i)
{
	if(i->index < length)
		isr_table[i->index] = 0;
}

