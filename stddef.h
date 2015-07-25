/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef STDDEF_H
#define STDDEF_H

typedef unsigned int uint;
typedef uint size_t;
typedef int ptrdiff_t;

#define SYSTEM_MHZ 8
#define SPEED_MHZ 1000000
#define SPEED_KHZ 1000
#define CALC_PERIOD(khz) ((SYSTEM_MHZ * SPEED_MHZ) / (khz * SPEED_KHZ))

inline int abs(int i)
{
	return (i < 0) ? (i * -1) : i;
}

inline float abs(float i)
{
	return (i < 0) ? (i * -1) : i;
}

#endif

