// $Id: chipio.h,v 1.9 2009/04/04 19:05:16 smakonin Exp $

// chipio.h		   	   Copyright (C) 1996, Real-Time Systems Inc.
//-------------------------------------------- All Rights Reserved ----------
//
// 	HC12 I/O Port and Bit Definitions
//
//	This file gives explicit names to the i/o ports and bits for
//	the 68HC12 processors, according to the following scheme:
//
// 	  - expanded modes only
//	  - port addresses given as offsets from iobase
// 	  - port names from data book, some bit names modified for clarity
// 	  - bit groups encoded as one mask for each useful combination
// 	  - bit mask format:
// 		IoMask symbol = xxxx   // meaning of '1' (meaning of '0')
//
//	Some port definitions vary between processors.  The A4 is the
//	default.  To use another processor, ensure the symbol __HCxxxxx__
//	is defined, where 'xx' is, for example, '812A4'.
//
//---------------------------------------------------------------------------

#ifndef CHIPIO_H
#define CHIPIO_H


// i/o port and mask type definitions for memory-mapped devices

#if defined(CHIPIO_CC)
  #define IoPort(type, name) volatile type name		 		\
			     __attribute__ ((section (".io")))
#else
  #define IoPort(type, name) extern volatile type name
#endif

#define IoByte(name) IoPort(char, name)
#define IoWord(name) IoPort(unsigned int, name)
typedef const int IoMask;


// parallel ports

IoByte(porta);			// parallel port a data
IoByte(portb);			// parallel port b data
IoByte(ddra);			// parallel port a direction
IoByte(ddrb);			// parallel port b direction
#if defined(__HC812A4__)
 IoByte(portc);			// parallel port c data
 IoByte(portd);			// parallel port d data
 IoByte(ddrc);			// parallel port c direction
 IoByte(ddrd);			// parallel port d direction
#endif
#if defined(__HC912B32__)
 IoByte(rsvd04[4]);
#endif
IoByte(porte);			// parallel port e data
IoByte(ddre);			// parallel port e direction

IoByte(pear);			// port e pin assignment register
 #if defined(__HC812A4__)
  IoMask arsie	= 0x80;         //   auxilliary reset input 	(parallel i/o)
  IoMask cdlte	= 0x40;         //   CDL testing	    	(parallel i/o)
 #endif
 #if defined(__HC912B32__)
  IoMask ndbe	= 0x80;		//   parallel i/o	     (data bus enable)
 #endif
 IoMask pipoe	= 0x20;         //   pipe status signal output	(parallel i/o)
 IoMask neclk	= 0x10;         //   parallel i/o 	      (E clock output)
 IoMask lstre	= 0x08;         //   low strobe* 		(parallel i/o)
 IoMask rdwe	= 0x04;         //   read/write*		(parallel i/o)


// system mode

IoByte(moder);			// mode register
 IoMask smodn	= 0x80;		//   special modes
 IoMask modb	= 0x40;		//   mode b
 IoMask moda	= 0x20;		//   mode a
 IoMask estr	= 0x10;		//   E-clock stretch enable
 IoMask ivis	= 0x08;		//   internal bus visible
 #if defined(__HC912B32__)
  IoMask ebswai	= 0x04;		//   external bus stop in wait
 #endif
 #if defined(__HC812A4__)
  IoMask emd	= 0x02;		//   emulate port d
 #endif
 IoMask eme	= 0x01;		//   emulate port e


// pin driver configuration

IoByte(pucr);			// pullup control register
 #if defined(__HC812A4__)
  IoMask puph	= 0x80;		//   port h pullups enable
  IoMask pupg	= 0x40;		//   port g pullups enable
  IoMask pupf	= 0x20;		//   port f pullups enable
 #endif
 IoMask pupe	= 0x10;		//   port e pullups enable
 #if defined(__HC812A4__)
  IoMask pupd	= 0x08;		//   port d pullups enable
  IoMask pupc	= 0x04;		//   port c pullups enable
 #endif
 IoMask pupb	= 0x02;		//   port b pullups enable
 IoMask pupa	= 0x01;		//   port a pullups enable

IoByte(rdriv);			// reduced drive control register
 #if defined(__HC812A4__)
  IoMask rdpj	= 0x80;		//   port j reduced drive
  IoMask rdph	= 0x40;		//   port h reduced drive
  IoMask rdpg	= 0x20;		//   port g reduced drive
  IoMask rdpf	= 0x10;		//   port f reduced drive
  IoMask rdpe	= 0x08;		//   port e reduced drive
  IoMask rdpd	= 0x04;		//   port d reduced drive
  IoMask rdpc	= 0x02;		//   port c reduced drive
  IoMask rdpba	= 0x01;		//   port ba reduced drive
 #endif
 #if defined(__HC912B32__)
  IoMask rdpe	= 0x08;		//   port e reduced drive
  IoMask rdpb	= 0x02;		//   port b reduced drive
  IoMask rdpa	= 0x01;		//   port a reduced drive
 #endif

IoByte(rsvd0E[2]);


// internal resource mapping

IoByte(initrm);			// internal ram address, high byte
IoByte(initrg);			// internal i/o address, high byte
 #if defined(__HC912B32__)
  IoMask mmswai	= 0x01;		//   memory mapping interface off in wait
 #endif
IoByte(initee);			// internal eeprom address, high byte
 IoMask eeon	= 0x01;		//   eeprom visible

IoByte(misc);			// miscellaneous configuration
 #if defined(__HC812A4__)
  IoMask ewdir	= 0x80;		//   extra window in direct space
  IoMask ndrc   = 0x40;		//   narrow data bus for register cs space
 #endif
 #if defined(__HC912B32__)
  IoMask ndrf	= 0x40;		//   narrow data bus for register-foll. map
  IoMask rfstr	= 0x10;		//   register-following stretch (2 bits)
  IoMask exstr	= 0x04;		//   external access stretch (2 bits)
  IoMask maprom	= 0x02;		//   flash rom at 8000h (0000h)
  IoMask romon	= 0x01;		//   enable flash rom
 #endif

#ifdef __HC812A4__
  const unsigned eesize = 0x1000;	// eeprom size
#endif
#ifdef __HC912B32__
  const unsigned eesize = 0x0300;	// eeprom size
#endif


// real-time clock interrupt

IoByte(rtictl);			// real-time interrupt control
IoByte(rtiflg);			// real-time interrupt flag
 IoMask rti	= 0x80;		//   rti interrupt mask/flag
 IoMask rswai	= 0x40;		//   rti/cop disabled in wait
 IoMask rsbck	= 0x20;		//   rti/cop disabled in background
 IoMask rtbyp	= 0x08;		//   bypass divider chain
 IoMask rtr	= 0x07;		//   real time rate field
 IoMask rtr65	= 0x07;		//   real time rate:  65.536 msec
 IoMask rtr32	= 0x06;		//   real time rate:  32.768 msec
 IoMask rtr16	= 0x05;		//   real time rate:  16.384 msec
 IoMask rtr8	= 0x04;		//   real time rate:   8.192 msec
 IoMask rtr4	= 0x03;		//   real time rate:   4.096 msec
 IoMask rtr2	= 0x02;		//   real time rate:   2.048 msec
 IoMask rtr1	= 0x01;		//   real time rate:   1.024 msec
 IoMask rtroff	= 0x00;		//   real time interrupt disabled


// system protection

IoByte(copctl);			// system protection control
 IoMask cme	= 0x80;		//   clock monitor enable
 IoMask fcme	= 0x40;		//   force clock monitor enable
 IoMask fcm	= 0x20;		//   force clock monitor reset
 IoMask fcop	= 0x20;		//   force watchdog timer reset
 IoMask disr	= 0x10;		//   disable watchdog/clockmon resets
 IoMask cr	= 0x07;		//   cop rate field
 IoMask cr1049	= 0x07;		//   cop rate:  1049 msec
 IoMask cr524	= 0x06;		//   cop rate:   524 msec
 IoMask cr262	= 0x05;		//   cop rate:   262 msec
 IoMask cr65	= 0x04;		//   cop rate:    65 msec
 IoMask cr16	= 0x03;		//   cop rate:    16 msec
 IoMask cr4	= 0x02;		//   cop rate:     4 msec
 IoMask cr1	= 0x01;		//   cop rate:     1 msec
 IoMask croff	= 0x00;		//   watchdog timer disabled

IoByte(coprst);			// watchdog timer reset

inline void resetWatchdog()	// tickle watchdog timer
{
  coprst = 0x55;
  coprst = 0xAA;
}


// test registers

IoByte(itst0);			// test register 0
IoByte(itst1);			// test register 1
IoByte(itst2);			// test register 2
IoByte(itst3);			// test register 3

IoByte(rsvd1C[2]);


// interrupt control

IoByte(intcr);			// external irq control
 IoMask irqe	= 0x80;		//   edge sensitive (level sensitive)
 IoMask irqen	= 0x40;		//   irq (and kwd on A4) enable
 IoMask dly	= 0x20;		//   delay 4096 cycles on exit from stop

IoByte(hprio);			// highest priority interrupt
 IoMask hpirq	= 0xF2;		//   external irq
 #if defined(__HC812A4__)
  IoMask hpkwd	= 0xF2;		//   key wakeup, port d
 #endif
 IoMask hprti	= 0xF0;		//   real-time interrupt
 IoMask hptc0	= 0xEE;		//   timer channel 0
 IoMask hptc1	= 0xEC;		//   timer channel 1
 IoMask hptc2	= 0xEA;		//   timer channel 2
 IoMask hptc3	= 0xE8;		//   timer channel 3
 IoMask hptc4	= 0xE6;		//   timer channel 4
 IoMask hptc5	= 0xE4;		//   timer channel 5
 IoMask hptc6	= 0xE2;		//   timer channel 6
 IoMask hptc7	= 0xE0;		//   timer channel 7
 IoMask hptof	= 0xDE;		//   timer overflow
 IoMask hppao	= 0xDC;		//   pulse accumulator overflow
 IoMask hppai	= 0xDA;		//   pulse accumulator edge
 IoMask hpspi	= 0xD8;		//   spi transfer complete
 IoMask hpsc0	= 0xD6;		//   sci channel 0
 #if defined(__HC812A4__)
  IoMask hpsc1	= 0xD4;		//   sci channel 1
 #endif
 IoMask hpatd	= 0xD2;		//   a/d converter
 #if defined(__HC812A4__)
  IoMask hpkwj	= 0xD0;		//   key wakeup, port j
  IoMask hpkwh	= 0xCE;		//   key wakeup, port h
 #endif
 #if defined(__HC912B32__)
  IoMask hpbdl	= 0xD0;		//   byte data link communications port
 #endif


// key wakeup system

#if defined(__HC812A4__)
 IoByte(kwied);			// key wakeup interrupt masks, port d
 IoByte(kwifd);			// key wakeup interrupt flags, port d

 IoByte(rsvd22[2]);

 IoByte(porth);			// parallel port h data
 IoByte(ddrh);			// parallel port h direction
 IoByte(kwieh);			// key wakeup interrupt masks, port h
 IoByte(kwifh);			// key wakeup interrupt flags, port h

 IoByte(portj);			// parallel port j data
 IoByte(ddrj);			// parallel port j direction
 IoByte(kwiej);			// key wakeup interrupt masks, port j
 IoByte(kwifj);			// key wakeup interrupt flags, port j

 IoByte(kpolj);			// key wakeup polarity, port j
 IoByte(pupsj);			// pullup select, port j -- up (down)
 IoByte(pulej);			// pullup enable, port j -- ena (dis)

 IoByte(rsvd2F[1]);
#endif


// memory banking and chip select

#if defined(__HC812A4__)
 IoByte(portf);			// parallel port f data
 IoByte(portg);			// parallel port g data
 IoByte(ddrf);			// parallel port f direction
 IoByte(ddrg);			// parallel port g direction

 IoByte(dpage);			// data page (A19 to A12)
 IoByte(ppage);			// program page (A21 to A14)
 IoByte(epage);			// extra page (A17 to A10)

 IoByte(windef);		// window definition
  IoMask dwen	= 0x80;		//   enable data window (7000 to 7FFF)
  IoMask pwen	= 0x40;		//   enable program window (8000 to BFFF)
  IoMask ewen	= 0x20;		//   enable extra window

 IoByte(mxar);			// memory expansion pin assignment (port g)

 IoByte(rsvd39[3]);

 IoByte(csctl0);		// chip select control 0
  IoMask csp1e	= 0x40;		//   csp1 enable
  IoMask csp0e	= 0x20;		//   csp0 enable
  IoMask csde	= 0x10;		//   csd enable
  IoMask cs3e	= 0x08;		//   cs3 enable
  IoMask cs2e	= 0x04;		//   cs2 enable
  IoMask cs1e	= 0x02;		//   cs1 enable
  IoMask cs0e	= 0x01;		//   cs0 enable

 IoByte(csctl1);		// chip select control 1
  IoMask csp1fl	= 0x40;		//   csp1 covers full map
  IoMask cspa21	= 0x20;		//   A21 chooses csp1 or csp0
  IoMask csdhf	= 0x10;		//   csd covers half map
  IoMask cs3ep	= 0x08;		//   cse follows extra page (io page)

 IoWord(csstr);			// chip select stretch
  IoMask strp1	= 0x1000;	//   csp1 offset
  IoMask strp0	= 0x0400;	//   csp0 offset
  IoMask strd	= 0x0100;	//   csd offset
  IoMask str3	= 0x0040;	//   cs3 offset
  IoMask str2	= 0x0010;	//   cs2 offset
  IoMask str1	= 0x0004;	//   cs1 offset
  IoMask str0	= 0x0001;	//   cs0 offset
#endif


// pll clock synthesizer

#if defined(__HC812A4__)
 IoWord(ldv);			// loop divisor
 IoWord(rdv);			// reference divisor

 IoByte(rsvd44[3]);

 IoByte(clkctl);		// clock control
  IoMask lckf	= 0x80;		//   lock flag
  IoMask pllon	= 0x40;		//   pll enable
  IoMask plls	= 0x20;		//   select pll (crystal) for muxclk
  IoMask bcs128	= 0x1C;		//   sysclk = muxclk / 128
  IoMask bcs64	= 0x18;		//   sysclk = muxclk / 64
  IoMask bcs32	= 0x14;		//   sysclk = muxclk / 32
  IoMask bcs16	= 0x10;		//   sysclk = muxclk / 16
  IoMask bcs8	= 0x0C;		//   sysclk = muxclk / 8
  IoMask bcs4	= 0x08;		//   sysclk = muxclk / 4
  IoMask bcs2	= 0x04;		//   sysclk = muxclk / 2
  IoMask bcs1	= 0x00;		//   sysclk = muxclk / 1
  IoMask mcs8	= 0x03;		//   mclk = pclk / 8
  IoMask mcs4	= 0x02;		//   mclk = pclk / 4
  IoMask mcs2	= 0x01;		//   mclk = pclk / 2
  IoMask mcs1	= 0x00;		//   mclk = pclk / 1

 IoByte(rsvd48[0x60-0x48]);
#endif


// breakpoint control

#if defined(__HC912B32__)
 IoByte(brkct0);		// breakpoint control 0
  IoMask bkoff	= 0x00;		//   breakpoints off
  IoMask bkswid	= 0x40;		//   swi dual address mode
  IoMask bkbdmf	= 0x80;		//   bdm full breakpoint mode
  IoMask bkbdmd = 0xC0;		//   bdm dual address mode
  IoMask bkpm	= 0x20;		//   break on program addresses
  IoMask bk1ale = 0x08;		//   brkdl will compare to address bus
  IoMask bk0ale	= 0x04;		//   brkal will compare to address bus

 IoByte(brkct1);		// breakpoint control 1
  IoMask bkdbe	= 0x40;		//   enable data bus
  IoMask bkmbh	= 0x20;		//   breakpoint mask high
  IoMask bkmbl	= 0x10;		//   breakpoint mask low
  IoMask bk1rwe	= 0x08;		//   r/w compare enable
  IoMask bk1rw	= 0x04;		//   r/w compare value
  IoMask bk0rwe	= 0x02;		//   r/w compare enable
  IoMask bk0rw	= 0x01;		//   r/w compare value

 IoWord(brka);			// breakpoint address register
 IoWord(brkd);			// breakpoint data register

 IoByte(rsvd26[0x40-0x26]);
#endif


// pulse-width modulator

#if defined(__HC912B32__)
 IoByte(pwmclk);		// pwm clocks and concatenate
  IoMask con23	= 0x80;		//   concatenate channels 2 and 3
  IoMask con01	= 0x40;		//   concatenate channels 0 and 1
  IoMask pcka	= 0x08;		//   offset of clock a prescaler
  IoMask pckb	= 0x01;		//   offset of clock b prescaler
  IoMask pck128	= 0x07;		//   clock = P / 128
  IoMask pck64	= 0x06;		//   clock = P / 64
  IoMask pck32	= 0x05;		//   clock = P / 32
  IoMask pck16	= 0x04;		//   clock = P / 16
  IoMask pck8	= 0x03;		//   clock = P / 8
  IoMask pck4	= 0x02;		//   clock = P / 4
  IoMask pck2	= 0x01;		//   clock = P / 2
  IoMask pck1	= 0x00;		//   clock = P / 1

 IoByte(pwpol);			// pwm clock select and polarity
  IoMask pclk3	= 0x80;		//   channel 3 uses S1 (B)
  IoMask pclk2	= 0x40;		//   channel 2 uses S1 (B)
  IoMask pclk1	= 0x20;		//   channel 1 uses S1 (B)
  IoMask pclk0	= 0x10;		//   channel 0 uses S1 (B)
  IoMask ppol3	= 0x08;		//   channel 3 active high (low)
  IoMask ppol2	= 0x04;		//   channel 2 active high (low)
  IoMask ppol1	= 0x02;		//   channel 1 active high (low)
  IoMask ppol0	= 0x01;		//   channel 0 active high (low)

 IoByte(pwen);			// pwm enable
  IoMask pwen3	= 0x08;		//   enable channel 3
  IoMask pwen2	= 0x04;		//   enable channel 2
  IoMask pwen1	= 0x02;		//   enable channel 1
  IoMask pwen0	= 0x01;		//   enable channel 0

 IoByte(pwpres);		// pwm prescaler

 IoByte(pwscal0);		// pwm scale register 0
 IoByte(pwscnt0);		// pwm scale counter 0 value

 IoByte(pwscal1);		// pwm scale register 1
 IoByte(pwscnt1);		// pwm scale counter 1 value

 union pwmreg
 {
   char byte[2];		// dual 8-bit pulse-width modulators
   unsigned int word;		// single 16-bit pulse-width modulator
 };

 IoPort(pwmreg, pwcnt01);	// pwm channel 0/1 counters
 IoPort(pwmreg, pwcnt23);	// pwm channel 2/3 counters
 
 IoPort(pwmreg, pwper01);	// pwm channel 0/1 period
 IoPort(pwmreg, pwper23);	// pwm channel 2/3 period
 
 IoPort(pwmreg, pwdty01);	// pwm channel 0/1 duty cycle
 IoPort(pwmreg, pwdty23);	// pwm channel 2/3 duty cycle
 
 IoByte(pwctl);			// pwm control
  IoMask pswai	= 0x10;		//   pwm halts in wait
  IoMask centr	= 0x08;		//   center-aligned output mode
  IoMask rdpp	= 0x04;		//   reduced drive, port p
  IoMask pupp	= 0x02;		//   pullup enable, port p
  IoMask psbck	= 0x01;		//   pwm stops in background

 IoByte(pwtst);			// pwm test

 IoByte(portp);			// parallel port p data
 IoByte(ddrp);			// parallel port p direction

 IoByte(rsvd58[0x60-0x58]);
#endif


// analog to digital converter

IoByte(atdctl0);		// a/d control 0
IoByte(atdctl1);		// a/d control 1

IoByte(atdctl2);		// a/d control 2
 IoMask adpu	= 0x80;		//   power up a/d converter
 IoMask affc	= 0x40;		//   fast flag clear all
 IoMask awai	= 0x20;		//   a/d stops in wait
 IoMask ascie	= 0x02;		//   sequence complete interrupt mask
 IoMask ascif	= 0x02;		//   sequence complete interrupt flag

IoByte(atdctl3);		// a/d control 3
 IoMask frz1	= 0x02;		//   freeze control 1
 IoMask frz0	= 0x01;		//   freeze control 0

IoByte(atdctl4);		// a/d control 4
 IoMask smp16	= 0x60;		//   sample time = 16 a/d clocks
 IoMask smp8	= 0x40;		//   sample time =  8 a/d clocks
 IoMask smp4	= 0x20;		//   sample time =  4 a/d clocks
 IoMask smp2	= 0x00;		//   sample time =  2 a/d clocks
 IoMask prs16	= 0x07;		//   prescale by 16
 IoMask prs14	= 0x06;		//   prescale by 14
 IoMask prs12	= 0x05;		//   prescale by 12
 IoMask prs10	= 0x04;		//   prescale by 10
 IoMask prs8	= 0x03;		//   prescale by 8
 IoMask prs6	= 0x02;		//   prescale by 6
 IoMask prs4	= 0x01;		//   prescale by 4
 IoMask prs2	= 0x00;		//   prescale by 2

IoByte(atdctl5);		// a/d control 5
 IoMask s8cm	= 0x40;		//   select 8 channel mode (4 channel mode)
 IoMask scan	= 0x20;		//   continuous conversions (single)
 IoMask mult	= 0x10;		//   multiple sequential channels (single)

IoByte(atdstat0);		// a/d status 1
 IoMask scf	= 0x80;		//   sequence complete
 IoMask cc	= 0x07;		//   conversion counter mask

IoByte(atdstat1);		// a/d status 1 (conversion complete flags)

IoWord(atdtst);			// a/d test register

IoByte(rsvd6A[0x6F-0x6A]);

IoByte(portad);			// parallel port ad data

IoWord(adr0);			// a/d result register 0
IoWord(adr1);			// a/d result register 1
IoWord(adr2);			// a/d result register 2
IoWord(adr3);			// a/d result register 3
IoWord(adr4);			// a/d result register 4
IoWord(adr5);			// a/d result register 5
IoWord(adr6);			// a/d result register 6
IoWord(adr7);			// a/d result register 7


// standard timer module

IoByte(tios);			// capture/compare select
IoByte(cforc);			// force output compare
IoByte(oc7m);			// output compare 7 mask
IoByte(oc7d);			// output compare 7 data

IoWord(tcnt);			// free-running counter

IoByte(tscr);			// timer system control
 IoMask ten	= 0x80;		//   enable timer
 IoMask tswai	= 0x40;		//   timer stops in wait
 IoMask tsbck	= 0x20;		//   timer stops in background
 IoMask tffca	= 0x10;		//   timer fast flag clear all

IoByte(tqcr);			// timer test register

IoWord(tctl1);			// output compare control
 IoMask om	= 0x02;		//   output mode steady (other)
 IoMask ol	= 0x01;		//   output level high/toggle (low/off)

IoWord(tctl3);			// input capture control
 IoMask fall	= 0x02;		//   capture falling edges
 IoMask rise	= 0x01;		//   capture rising edges

IoByte(tmsk1);			// timer interrupt mask 1

IoByte(tmsk2);			// timer interrupt mask 2
 IoMask toi	= 0x80;		//   timer overflow enable
 IoMask pupt	= 0x20;		//   pullup enable, port t
 IoMask rdpt	= 0x10;		//   reduced drive, port t
 IoMask tdrb	= 0x10;		//   reduced drive, port t
 IoMask tcre	= 0x08;		//   reset counter on compare 7
 IoMask pr32	= 0x05;		//   prescale by 32
 IoMask pr16	= 0x04;		//   prescale by 16
 IoMask pr8	= 0x03;		//   prescale by  8
 IoMask pr4	= 0x02;		//   prescale by  4
 IoMask pr2	= 0x01;		//   prescale by  2
 IoMask pr1	= 0x00;		//   prescale by  1

IoByte(tflg1);			// timer interrupt flag 1

IoByte(tflg2);			// timer interrupt flag 1
 IoMask tof	= 0x80;		//   timer overflow flag

IoWord(tc0);			// timer channel 0
IoWord(tc1);			// timer channel 1
IoWord(tc2);			// timer channel 2
IoWord(tc3);			// timer channel 3
IoWord(tc4);			// timer channel 4
IoWord(tc5);			// timer channel 5
IoWord(tc6);			// timer channel 6
IoWord(tc7);			// timer channel 7

IoByte(pactl);			// pulse accumulator control
 IoMask paen	= 0x40;		//   enable pulse accumulator
 IoMask pamod	= 0x20;		//   gated mode (event count mode)
 IoMask pedge	= 0x10;		//   rising edge
 IoMask clk65k	= 0x0C;		//   clock = paclk / 65536
 IoMask clk256	= 0x08;		//   clock = paclk / 256
 IoMask clk1	= 0x04;		//   clock = paclk / 1
 IoMask clkt	= 0x00;		//   clock = timer prescaler clock
 IoMask paovi	= 0x02;		//   enable overflow interrupt
 IoMask pai	= 0x01;		//   enable input edge interrupt

IoByte(paflg);			// pulse accumulator flag
 IoMask paovf	= 0x02;		//   overflow interrupt
 IoMask paif	= 0x01;		//   input edge interrupt

IoWord(pacnt);			// pulse accumulator count

IoByte(rsvdA4[0xAD-0xA4]);
IoByte(timtst);			// timer test

IoByte(portt);			// parallel port t data
IoByte(ddrt);			// parallel port t direction

IoByte(rsvdB0[0xC0-0xB0]);


// asynchronous serial system

struct sciport
{
  int scbd;			// sci baud rate

  char sccr1;			// sci control 1
   IoMask loops	= 0x80;		//   loop mode (normal)
   IoMask woms	= 0x40;		//   wire-or mode
   IoMask rsrc	= 0x20;		//   receiver input is tx at pin (internally)
   IoMask m	= 0x10;		//   9-bit mode
   IoMask wake	= 0x08;		//   wake up on bit8 = 1 (idle line)
   IoMask ilt	= 0x04;		//   idle line mode long (short)
   IoMask pe	= 0x02;		//   enable parity
   IoMask pt	= 0x01;		//   odd parity (even parity)

  char sccr2;			// sci control 2
   IoMask tie	= 0x80;		//   enable transmit interrupt
   IoMask tcie	= 0x40;		//   enable transmit complete interrupt
   IoMask rie	= 0x20;		//   enable receive interrupt
   IoMask ilie	= 0x10;		//   enable idle line interrupt
   IoMask te	= 0x08;		//   enable transmitter
   IoMask re	= 0x04;		//   enable receiver
   IoMask rwu	= 0x02;		//   wait for wake-up
   IoMask sbk	= 0x01;		//   send break

  char scsr1;			// sci status 1
   IoMask tdre	= 0x80;		//   transmit data register empty
   IoMask tc	= 0x40;		//   transmit complete
   IoMask rdrf	= 0x20;		//   receive data register full
   IoMask idle	= 0x10;		//   receiver idle
   IoMask or	= 0x08;		//   over-run
   IoMask nf	= 0x04;		//   noise flag
   IoMask fe	= 0x02;		//   framing error
   IoMask pf	= 0x01;		//   parity error

  char scsr2;			// sci status 1
   IoMask raf	= 0x01;		//   receiver active

  char scdrh;			// data register high
   IoMask r8	= 0x80;		//   receive bit 8
   IoMask t8	= 0x40;		//   transmit bit 8

  char scdrl;			// data register low
};

IoPort(sciport, sci0);		// sci port 0
#if defined(__HC812A4__)
 IoPort(sciport, sci1);		// sci port 1
#endif
#if defined(__HC912B32__)
 IoByte(rsvdC8[8]);
#endif


// syncronous serial system

struct spiport
{
  char spcr1;			// spi control 1
   IoMask spie	= 0x80;		//   enable spi interrupt
   IoMask spe	= 0x40;		//   enable spi
   IoMask swom	= 0x20;		//   port d wire-or mode
   IoMask mstr	= 0x10;		//   master select
   IoMask cpol	= 0x08;		//   clock polarity = idle high
   IoMask cpha	= 0x04;		//   clock phase = sample center
   IoMask ssoe	= 0x02;		//   slave select output enable
   IoMask lsbf	= 0x01;		//   least significant byte first (most)

  char spcr2;			// spi control 2
   #if defined(__HC812A4__)
    IoMask pups	= 0x08;		//   pullup enable, port s
    IoMask rds	= 0x04;		//   reduced drive, port s
   #endif
   #if defined(__HC912B32__)
    IoMask sswai = 0x02;	//   spi clock halts in wait
   #endif
    IoMask spc0	= 0x01;		//   serial pin control 0

   char spbr;			// spi baud rate
    IoMask spr31   = 0x07;	//   spi rate:    31 kbaud
    IoMask spr62   = 0x06;	//   spi rate:    62 kbaud
    IoMask spr125  = 0x05;	//   spi rate:   125 kbaud
    IoMask spr250  = 0x04;	//   spi rate:   500 kbaud
    IoMask spr500  = 0x03;	//   spi rate:   500 kbaud
    IoMask spr1000 = 0x02;	//   spi rate:  1000 kbaud
    IoMask spr2000 = 0x01;	//   spi rate:  2000 kbaud
    IoMask spr4000 = 0x00;	//   spi rate:  4000 kbaud

   char spsr;			// spi status
    IoMask spif	= 0x80;		//   transfer complete
    IoMask wcol	= 0x40;		//   write collision
    IoMask modf	= 0x10;		//   mode fault

   char rsvd4;

   char spdr;			// spi data
};

IoPort(spiport, spi0);		// spi port 0

IoByte(ports);			// parallel port s data
IoByte(ddrs);			// parallel port s direction

#if defined(__HC812A4__)
 IoByte(rsvdD8[0xE0-0xD8]);
#endif
#if defined(__HC912B32__)
 IoByte(rsvdD8[0xDB-0xD8]);

 IoByte(purds);			// pullup enable and reduced drive, port s
  IoMask rdps2	= 0x40;		//   reduced drive, ps2
  IoMask rdps1	= 0x20;		//   reduced drive, ps1
  IoMask rdps0	= 0x10;		//   reduced drive, ps0
  IoMask pups2	= 0x04;		//   pullup enable, ps2
  IoMask pups1	= 0x02;		//   pullup enable, ps1
  IoMask pups0	= 0x01;		//   pullup enable, ps0

 IoByte(rsvdDC[0xE0-0xDC]);
#endif

IoByte(rsvdE0[0xF0-0xE0]);


// eeprom control

IoByte(eemcr);			// eeprom module control
 #if defined(__HC912B32__)
  IoMask eeswai	= 0x04;		//   eeprom clock stops during wait
 #endif
 IoMask protlck	= 0x02;		//   block protect bits locked
 IoMask eerc	= 0x01;		//   use internal RC oscillator

IoByte(eeprot);			// block protect map
 #if defined(__HC812A4__)
  IoMask bprot6	= 0x40;		//   protect 2048 bytes
  IoMask bprot5	= 0x20;		//   protect 1024 bytes
 #endif
 IoMask bprot4	= 0x10;		//   protect  512 bytes
 IoMask bprot3	= 0x08;		//   protect  256 bytes
 IoMask bprot2	= 0x04;		//   protect  128 bytes
 IoMask bprot1	= 0x02;		//   protect   64 bytes
 IoMask bprot0	= 0x01;		//   protect   64 bytes

IoByte(eetst);			// eeprom test

IoByte(eeprog);			// eeprom programming control
 IoMask bulkp	= 0x80;		//   bulk erase protect
 IoMask byt	= 0x10;		//   byte...
 IoMask row	= 0x08;		//   row...
 IoMask bulk	= 0x00;		//   bulk...
 IoMask erase	= 0x04;		//   ...erase
 IoMask eelat	= 0x02;		//   latch address
 IoMask eepgm	= 0x01;		//   program!


// flash rom control

#if defined(__HC912B32__)
 IoByte(feelck);		// flash lock control
  IoMask lock	= 0x01;		//   lock out module control register

 IoByte(feemcr);		// flash module control
  IoMask bootp	= 0x01;		//   protect boot block

 IoByte(feetst);		// flast test

 IoByte(feectl);		// flash programming control
  IoMask feeswai = 0x10;	//   halt flash clock in wait
  IoMask svfp	= 0x08;		//   Vfp pin above normal level (below)
  IoMask eras	= 0x04;		//   erase (program)
  IoMask lat	= 0x02;		//   programming latches enabled
  IoMask enpe	= 0x01;		//   enable program/erase
#endif


// byte data link communications (SAE J1850)

#if defined(__HC912B32__)
 IoByte(bcr1);			// bdlc control 1
  IoMask imsg	= 0x80;		//   disable receiver (enable)
  IoMask clcks	= 0x40;		//   binary frequency: 1.048 MHz (1.000 MHz)
  IoMask r8m	= 0x30;		//   bdlc rate:  8 MHz
  IoMask r4m	= 0x20;		//   bdlc rate:  4 MHz
  IoMask r2m	= 0x10;		//   bdlc rate:  2 MHz
  IoMask r1m	= 0x00;		//   bdlc rate:  1 MHz
  IoMask ie	= 0x02;		//   interrupt enable
  IoMask wcm	= 0x01;		//   stop clock during wait

 IoByte(bcr2);			// bdlc control 2
  IoMask aloop	= 0x80;		//   analog loopback
  IoMask dloop	= 0x40;		//   digital loopback
  IoMask rx4xe	= 0x20;		//   4x receive-only (tx/rx at 104 kbps)
  IoMask nbfs	= 0x10;		//   normalization bit
  IoMask teod	= 0x08;		//   transmit end-of-data
  IoMask tsifr	= 0x04;		//   transmit in-frame response control
  IoMask tmifr1	= 0x02;		//   transmit in-frame response control
  IoMask tmifr0	= 0x01;		//   transmit in-frame response control

 IoByte(bsvr);			// bdlc state vector
  IoMask bwake	= 0x20;		//   wakeup
  IoMask binv	= 0x1C;		//   symbol invalid or out of range
  IoMask bcrc	= 0x18;		//   crc error
  IoMask barb	= 0x14;		//   loss of arbitration
  IoMask btdre	= 0x10;		//   transmit data register empty
  IoMask brdrf	= 0x0C;		//   receive data register full
  IoMask brxifr	= 0x08;		//   received ifr byte
  IoMask beov	= 0x04;		//   received eof
  IoMask bnone	= 0x00;		//   no interrupts pending

 IoByte(bdr);			// bdlc data

 IoByte(bard);			// bdlc analog roundtrip delay
  IoMask ate	= 0x80;		//   analog transceiver enable
  IoMask rxpol	= 0x40;		//   receive pin polarity
  IoMask bo	= 0x0F;		//   bard offset mask

 IoByte(dlcscr);		// bdlc port control
  IoMask bdlcen	= 0x04;		//   bdlc enable (parallel i/o)
  IoMask pupdlc	= 0x02;		//   pullup enable, port dlc
  IoMask rdpdlc	= 0x01;		//   reduced drive, port dlc

 IoByte(portdlc);		// parallel port dlc data
 IoByte(ddrdlc);		// parallel port dlc direction
#endif


#endif // CHIPIO_H

