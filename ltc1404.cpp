/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "timer.h"
#include "ltc1404.h"
#include "gmask.h"

ltc1404::ltc1404(size_t size, int pri, spi &s)
: task(size, pri), _spi(s)
{
	{
		gmask stop_all_interrupts;
		ddrs |= _sel_mask;
	}

	_filt = user(_spi).measure();  //set Y[0] = X[0] create a uers obj scope 1 line
	fork();	
}

ltc1404::~ltc1404()
{
	//join() or stop the task
	gmask stop_all_interrupts;
	ddrs &= ~_sel_mask;
}

float ltc1404::read() const
{
	mutex::lock l(_mutex);
	return (_filt / 32768.0) * _vref;  //convet to a fraction of full scale
}

int ltc1404::read_raw() const
{
	mutex::lock l(_mutex);
	return _raw;
}

int ltc1404::read_filtered() const
{
	mutex::lock l(_mutex);
	return _filt;
}

void ltc1404::main()
{
	while(true)
	{
		timer::delay(3);
		mutex::lock l(_mutex);
		_raw = user(_spi).measure();
		_filt = _filt + (_raw - _filt) / _filt_const;	
	}
}

ltc1404::user::user(spi &s)
: spi::user(s)
{
	gmask stop_all_interrupts;
	ports |= _sel_mask;
}

ltc1404::user::~user()
{
	gmask stop_all_interrupts;
	ports &= ~_sel_mask;
}

int ltc1404::user::measure()
{
	int buf;
	
	get(&buf, sizeof(buf) * 8);
	buf = buf << _offset;
	buf &= _valid_bits;
	buf |= _jam_bit;

	return buf;
}

