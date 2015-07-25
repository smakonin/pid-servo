/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef NEW_H
#define NEW_H

#include "stddef.h"

void * operator new(size_t);
void * operator new[](size_t);
void operator delete(void *);
void operator delete[](void *);

#endif
