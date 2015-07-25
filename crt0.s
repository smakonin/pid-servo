		public _start
_start 
		lds		#_stack_top		; set initial stack pointer
		movw	#0,2,-s			; terminate return chain
		movw	#0,2,-s			; terminate frame chain
		tfr		s,x				; set initial frame pointer
		jsr _crt1__Fv			; run crt1()
		stop
