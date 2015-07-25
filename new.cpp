/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "malloc.h"

void * operator new(size_t size)
{
	return malloc(size);
}

void * operator new[](size_t size)
{
	return malloc(size);
}

void operator delete(void *buf)
{
	free(buf);
}

void operator delete[](void *buf)
{
	free(buf);
}
