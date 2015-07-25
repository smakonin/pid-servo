/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef PIDSERVO_H
#define PIDSERVO_H

#include "stddef.h"
#include "no_copy.h"
#include "task.h"
#include "timer.h"
#include "pwm.h"
#include "ltc1404.h"
#include "iostream.h"
#include "iomanip.h"

class servo_param
{
    friend class pidservo;
    
    private:
        float _proportional_gain;
        float _integral_gain;
        float _derivative_gain;
        float _set_point;
        float _integral_limit;
        float _dead_band;
        float _output_limit;
        float _output_safe_value;
        float _run_mode;
        
    public:
        servo_param();
        virtual ~servo_param();
        float get(const char *);
        const char *set(const char *, float);
};

class servo_status
{
    friend class pidservo;
    
    private:
        float _raw;
        float _temp;
        float _cur_error;
        float _prev_error;
        float _accum_error;
        float _diff_error;
        float _response;
        float _pwm_fraction;
    
    public:
        servo_status();
        virtual ~servo_status();
        float get(const char *);
};

class pidservo : public task
{
	private:
	    servo_param _params;
	    servo_status _stats;
	    pwmchannel &_tec;
	    ltc1404 &_temp;
	    mutable mutex _mutex;
		
	protected:
		virtual void main();

	public:
		pidservo(size_t, int, pwmchannel &, ltc1404 &);
		virtual ~pidservo();
        float get(const char *);
        const char *set(const char *, float);
        void print_values(ostream &);
        void print_line(ostream &);	
};

#endif

