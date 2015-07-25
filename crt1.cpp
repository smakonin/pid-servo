/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

typedef void(*fptr)(void);

extern char bss_beg[];
extern char bss_end[];
extern fptr ctor_beg[];
extern fptr ctor_end[];
extern fptr dtor_beg[];
extern fptr dtor_end[];
extern int main();

void crt1()
{
	//init .bss section with 0s	
	for(int i = 0; i < bss_end - bss_beg; i++)
		 bss_beg[i] = 0;
		
	//call static c-tors
	for(int i = 0; i < ctor_end - ctor_beg; i++)
		(*ctor_beg[i])();
	
	//enable interrupts
	asm("cli");
	
	main();	
	
	//disable interrupts
	asm("sei");

	//call static d-tors
	for(int i = 0; i < dtor_end - dtor_beg; i++)
		(*dtor_beg[i])();
}
