; $Id: vectors.s,v 1.12 2009/04/04 19:05:17 smakonin Exp $

; vectors.s			   Copyright (C) 2002, Real-Time Systems Inc.
;-------------------------------------------- All Rights Reserved -----------
;
;	System Vector Table
;
;----------------------------------------------------------------------------

	section	.vectors

	dc.w	0
	dc.w	0
	dc.w	0
	dc.w	0
	dc.w	0
	dc.w	0
	dc.w	0
	dc.w	0

	dc.w	vsr0
	dc.w	vsr1
	dc.w	0
	dc.w	vsr2
	dc.w	vsr3
	dc.w	vsr4
	dc.w	vsr5
	dc.w	vsr6

	dc.w	vsr7
	dc.w	vsr8
	dc.w	vsr9
	dc.w	vsr10
	dc.w	vsr11
	dc.w	vsr12
	dc.w	vsr13
	dc.w	vsr14

	dc.w	vsr15
	dc.w	vsr16
	dc.w	0
	dc.w	0
	dc.w	0
	dc.w	0
	dc.w	0
	dc.w	_start

