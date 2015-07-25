/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef SYS_OBJECTS_H
#define SYS_OBJECTS_H

#include "stddef.h"
#include "no_copy.h"
#include "hc12sci.h"
#include "pwm.h"
#include "hc12ictlr.h"
#include "ltc1404.h"
#include "pidservo.h"

class sys_objects : private no_copy
{
	public:
		pwmdriver &drv;
		pwmchannel &tec; 
		pwmchannel &res;
		hc12sci &com;
		ltc1404 &temp;
		pidservo &servo;
		
		sys_objects(pwmdriver &dd, pwmchannel &ct, pwmchannel &cr, hc12sci &sc, ltc1404 &tt, pidservo &ps)
		: drv(dd), tec(ct), res(cr), com(sc), temp(tt), servo(ps)
		{
		}
		
		~sys_objects()
		{
		}
};

#endif

