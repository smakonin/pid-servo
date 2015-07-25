/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "stddef.h"
#include "sys_objects.h"
#include "myshell.h"
#include "hc12timer.h"
#include "hc12ictlr.h"
#include "task.h"
#include "hc12spi.h"
#include "ltc1404.h"
#include "pidservo.h"

int main()
{	
	hc12ictlr ic;
	pwmdriver drv(ic, CALC_PERIOD(2));
	pwmchannel tec(drv, 0); 
	pwmchannel res(drv, 1);
	hc12sci com(sci0, 16, 32);
	hc12spi myspi(spi0);
	
	hc12timer clock(512, priority_timer, ic);
	ltc1404 temp(1024, priority_adc, myspi);
	pidservo servo(1024, priority_servo, tec, temp);

    sys_objects so(drv, tec, res, com, temp, servo);
	myshell sh(1024, priority_shell, so);
	
	while(true)
	{
	}
	
	return 0;
}

