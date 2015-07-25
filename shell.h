/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef SHELL_H
#define SHELL_H

#include "stddef.h"
#include "no_copy.h"
#include "iostream.h"

class command : private no_copy
{
	private:
		const char *name;

	public:
		command(const char *);
		virtual ~command();
		bool match(istream &);
		bool match(const char *);
		virtual const char *parse(istream &, ostream &);
		virtual const char *help();
		const char *getname();
};

class shell : private no_copy
{
	private:
		streambuf *sbuf;
		const char *prompt;

		void getline(char *, size_t);
	
	protected:
		void present(command **);

	public:
		shell(streambuf *, const char *);
};

#endif
