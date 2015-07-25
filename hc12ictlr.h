/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef HC12ICTLR_H
#define HC12ICTLR_H

#include "stddef.h"
#include "no_copy.h"
#include "isr.h"


class hc12ictlr : public ictlr
{
    private:
		static hc12ictlr *inst;
  		static void handler_table() __attribute__ ((unused));
        
	public:
        hc12ictlr();        
        ~hc12ictlr();
        		
		enum sources
		{
			is_bdl,
			is_atd,
			is_sc0,
			is_spi,
			is_pai,
			is_pao,
			is_tof,
			is_tc7,
			is_tc6,
			is_tc5,
			is_tc4,
			is_tc3,
			is_tc2,
			is_tc1,
			is_tc0,
			is_rti,
			is_irq,

			sources_count
		}; 		
};

#endif

