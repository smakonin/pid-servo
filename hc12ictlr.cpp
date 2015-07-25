/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "chipio.h"
#include "hc12ictlr.h"

hc12ictlr *hc12ictlr::inst;

hc12ictlr::hc12ictlr()
: ictlr(sources_count)
{
	inst = this;
  	ddrdlc |= (1 << 5);		// DEBUG
}


hc12ictlr::~hc12ictlr()
{
	inst = 0;
}

void hc12ictlr::handler_table()
{

	#define	vsr(src)							\
		asm("		public	vsr%c0"	: : "i" (hc12ictlr::src)	);	\
		asm("\nvsr%c0"		: : "i" (hc12ictlr::src)	);	\
		portdlc |= (1 << 5);			/* DEBUG */			\
		inst->run_handler(src);					\
		portdlc &= ~(1 << 5);			/* DEBUG */			\
		asm("rti");

	vsr(is_bdl);
	vsr(is_atd);
	vsr(is_sc0);
	vsr(is_spi);
	vsr(is_pai);
	vsr(is_pao);
	vsr(is_tof);
	vsr(is_tc7);
	vsr(is_tc6);
	vsr(is_tc5);
	vsr(is_tc4);
	vsr(is_tc3);
	vsr(is_tc2);
	vsr(is_tc1);
	vsr(is_tc0);
	vsr(is_rti);
	vsr(is_irq);
};

