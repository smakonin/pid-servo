# $Id: Makefile,v 1.11 2009-03-21 04:27:34 smakonin Exp $

# Makefile for ELEX8030 term project

PROG	= project.o

OBJS    = $(addsuffix .o, $(basename $(wildcard *.cpp) $(wildcard *.s)))

CC		=  hc12-coff-gcc

LIBS	+= iostream.a

CFLAGS	+= -O2
CFLAGS	+= -g
CFLAGS	+= -fno-exceptions -fno-rtti -fpcc-struct-return -fvtable-thunks
CFLAGS 	+= -W -Wall -Wtraditional -Wundef -Wbad-function-cast -Wcast-qual
CFLAGS	+= -Wwrite-strings -Wconversion -Wstrict-prototypes
CFLAGS	+= -Wmissing-prototypes -Wmissing-declarations -Wold-style-cast
CFLAGS	+= -Woverloaded-virtual -Werror -Wunused 
CFLAGS	+= -D__HC912B32__
CFLAGS	+= -Wa,-ahlnd=$*.lst

LFLAGS	+= -Wl,--defsym,_stack_top=0x8000
LFLAGS	+= -Wl,--defsym,_heap_lim=0x7C00
LFLAGS	+= -Wl,-Map,$*.map
LFLAGS	+= --verbose
LFLAGS	+= -Wl,-T,$*.ld

all : $(PROG)

$(PROG) : $(OBJS) $(LIBS)
	$(CC) $(LFLAGS) -o $@ $^

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

%.o : %.s
	$(CC) -c $<

clean :
	rm -f $(PROG) $(OBJS) *.lst *.map

