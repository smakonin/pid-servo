/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "pidservo.h"
#include "string.h"
#include "error.h"

pidservo::pidservo(size_t size, int p, pwmchannel &ch, ltc1404 &tt) 
: task(size, p), _tec(ch), _temp(tt)
{ 
	_params._proportional_gain =    1.000;
	_params._integral_gain     =    0.001;
	_params._derivative_gain   =    0.100;
	_params._set_point         =   20.000;
	_params._integral_limit    =  100.000;
	_params._dead_band         =    0.250;
	_params._output_limit      =    0.000;
	_params._output_safe_value =    0.000;
	_params._run_mode          =    1.000;
	_stats._raw                =    0.000;
	_stats._temp               =    0.000;
	_stats._cur_error          =    0.000;
	_stats._prev_error         =    0.000;
	_stats._accum_error        =    0.000;
	_stats._diff_error         =    0.000;
	_stats._response           =    0.000;
	_stats._pwm_fraction       =    0.000;
	
	fork();
}

pidservo::~pidservo()
{
}
		
void pidservo::main()
{
	while(true)
	{
	    timer::delay(1000);
	    mutex::lock l(_mutex);

	    _stats._raw = _temp.read();
	    _stats._temp = _stats._raw * 100.0;

	    _stats._prev_error = _stats._cur_error;
	    _stats._cur_error = _stats._temp - _params._set_point;
	    _stats._diff_error = _stats._cur_error - _stats._prev_error;	    
	    _stats._accum_error += _stats._cur_error;
	    
	    _stats._response = _stats._cur_error * _params._proportional_gain
	    				 + _stats._accum_error * _params._integral_gain
	    				 + _stats._diff_error * _params._derivative_gain;
	    	    
	   	float modifier = 0;
	   	if(_stats._temp > _params._set_point)
	   		modifier = 1;
	   	else if(_stats._temp < _params._set_point)
	   		modifier = -1;
	   	
	    _stats._pwm_fraction = modifier * abs(_stats._response);	    
	    _stats._pwm_fraction = (_stats._pwm_fraction > 1.0) ? 1.0 : _stats._pwm_fraction;
	    _stats._pwm_fraction = (_stats._pwm_fraction < -1.0) ? -1.0 : _stats._pwm_fraction;

	    if(_params._run_mode)
	        _tec.setduty(_stats._pwm_fraction);	    
	}
}

float pidservo::get(const char *ch)
{
    float ret;   
    mutex::lock l(_mutex);
    
    ret = _params.get(ch);
    if(ret == ~0)
        ret = _stats.get(ch);
        
    return ret;
}

const char *pidservo::set(const char *ch, float value)
{
    mutex::lock l(_mutex);
    return _params.set(ch, value);
}

void pidservo::print_values(ostream &sout)
{
    sout.setf(ios::fixed, ios::floatfield);
    sout.precision(10);
    sout << endl << "pgain    =" << setw(20) << _params._proportional_gain;
    sout << endl << "igain    =" << setw(20) << _params._integral_gain;
    sout << endl << "dgain    =" << setw(20) << _params._derivative_gain;
    sout << endl << "setpoint =" << setw(20) << _params._set_point;
    sout << endl << "ilimit   =" << setw(20) << _params._integral_limit;
    sout << endl << "deadband =" << setw(20) << _params._dead_band;
    sout << endl << "oplimit  =" << setw(20) << _params._output_limit;
    sout << endl << "safeval  =" << setw(20) << _params._output_safe_value;
    sout << endl << "mode     =" << setw(20) << _params._run_mode; 
    sout << endl << "raw      =" << setw(20) << _stats._raw;
    sout << endl << "temp     =" << setw(20) << _stats._temp;
    sout << endl << "curerr   =" << setw(20) << _stats._cur_error;
    sout << endl << "preverr  =" << setw(20) << _stats._prev_error;
    sout << endl << "accumerr =" << setw(20) << _stats._accum_error;
    sout << endl << "response =" << setw(20) << _stats._response;
    sout << endl << "pwm      =" << setw(20) << _stats._pwm_fraction;
}

void pidservo::print_line(ostream &sout)	
{
    sout.setf(ios::fixed, ios::floatfield);
    sout.precision(4);
    
    sout << "\r"
     << "  Temp =" << setw(8) << _stats._temp
     << "  Err  =" << setw(8) << _stats._cur_error
     << "  Resp =" << setw(8) << _stats._response
     << "  PWM  =" << setw(8) << _stats._pwm_fraction;    
}

servo_param::servo_param()
{
}

servo_param::~servo_param()
{
}

float servo_param::get(const char *ch)
{
    if(strcmp(ch, "pgain") == 0)
        return _proportional_gain;
    else if(strcmp(ch, "igain") == 0)
        return _integral_gain;
    else if(strcmp(ch, "dgain") == 0)
        return _derivative_gain;
    else if(strcmp(ch, "setpoint") == 0)
        return _set_point;
    else if(strcmp(ch, "ilimit") == 0)
        return _integral_limit;
    else if(strcmp(ch, "deadband") == 0)
        return _dead_band;
    else if(strcmp(ch, "oplimit") == 0)
        return _output_limit;
    else if(strcmp(ch, "safeval") == 0)
        return _output_safe_value;
    else if(strcmp(ch, "mode") == 0)
        return _run_mode;

    return ~0;
}

const char *servo_param::set(const char *ch, float value)
{

    if(strcmp(ch, "pgain") == 0)
        _proportional_gain = value;
    else if(strcmp(ch, "igain") == 0)
        _integral_gain = value;
    else if(strcmp(ch, "dgain") == 0)
        _derivative_gain = value;
    else if(strcmp(ch, "setpoint") == 0)
       _set_point = value;
     else if(strcmp(ch, "ilimit") == 0)
        _integral_limit = value;
    else if(strcmp(ch, "deadband") == 0)
        _dead_band = value;
    else if(strcmp(ch, "oplimit") == 0)
        _output_limit = value;
    else if(strcmp(ch, "safeval") == 0)
        _output_safe_value = value;
    else if(strcmp(ch, "mode") == 0)
        _run_mode = value;
    else
        return "unable to set param";

    return 0;
}

servo_status::servo_status()
{
}

servo_status::~servo_status()
{
}

float servo_status::get(const char *ch)
{
    if(strcmp(ch, "raw") == 0)
        return _raw;
    else if(strcmp(ch, "temp") == 0)
        return _temp;
    else if(strcmp(ch, "curerr") == 0)
        return _cur_error;
    else if(strcmp(ch, "preverr") == 0)
        return _prev_error;
    else if(strcmp(ch, "accumerr") == 0)
        return _accum_error;
    else if(strcmp(ch, "response") == 0)
        return _response;
    else if(strcmp(ch, "pwm") == 0)
        return _pwm_fraction;
    
    return ~0;
}

