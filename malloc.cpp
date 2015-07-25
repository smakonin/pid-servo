/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "stddef.h"
#include "error.h"

extern char heap_beg[];
extern char heap_lim[];

size_t fill = 0;

void *malloc(size_t size)
{
	char *ptr = 0;
	
	if(&heap_beg[fill + size] >= &heap_lim[0])
		handle_error("no more heap");

	ptr = &heap_beg[fill];
	fill += size;
			
	return ptr;
}

void free(void *)
{
}


