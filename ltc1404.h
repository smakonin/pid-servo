/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef LTC1404_H
#define LTC1404_H

#include "stddef.h"
#include "no_copy.h"
#include "chipio.h"
#include "spi.h"
#include "task.h"

class ltc1404 : public task
{
	private:
		spi &_spi;
		static const int _sel_mask = 1 << 7; //bit in cs port
		static const int _offset = 2; //# of dumby bits
		static const int _valid_bits = (~0 << (16 - 12));  //0xfff0
		static const int _jam_bit = (~_valid_bits + 1) >> 1;  //.5 1 ls bit a/d i/p 0x0008
		static const int _filt_const = 32;//64;//128;
		static const float _vref = 2.048; //ref voltage to a/d converter
		mutable mutex _mutex;  //okay to mod in const func
		int _raw;
		int _filt;

		class user : public spi::user
		{
			private:
			public:
				user(spi &s);
				~user();
				int measure();
		};

	protected:
		virtual void main();

	public:
		ltc1404(size_t, int, spi &);
		virtual ~ltc1404();
		float read() const;		
		int read_raw() const;		
		int read_filtered() const;
};


#endif

