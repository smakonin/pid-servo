/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#include "ctype.h"
#include "string.h"
#include "iomanip.h"
#include "strstream.h"
#include "shell.h"

command::command(const char *n)
:name(n)
{
}

command::~command()
{
}

bool command::match(istream &sin)
{
	char buf[20];
	return (sin >> setw(sizeof(buf)) >> buf) && (strcmp(buf, name) == 0);
}

bool command::match(const char *n)
{
	return (strcmp(n, name) == 0);
}

const char *command::parse(istream &, ostream &)
{
	return 0;
}

const char *command::help()
{
	return 0;
}

const char *command::getname()
{
	return name;
}

shell::shell(streambuf *sb, const char *p)
:sbuf(sb), prompt(p)
{
}

void shell::present(command **menu)
{
	char last[80];	
				
	while(true)
	{
		ostream sout(sbuf);		
		sout << endl << prompt << flush;
		
		char buf[80];
		getline(buf, sizeof(buf));
		if(buf[0])
		{
			const char *error = "Unknown command.";
			
			if(buf[0] == '\\')
				strcpy(buf, last);

			for(command **c = menu; *c; c++)
			{
				istrstream sin(buf);
			
				if((*c)->match(sin))
				{
					error = (*c)->parse(sin, sout);
										
					if((*c)->match("help"))
					{				
						for(command **c = menu; *c; c++)
						{
							if(!(*c))
								break;
					
							ostream sout2(sbuf);
							sout2.setf(0x0002); //left does causes compile error
							sout2 << endl << "   " << setw(10) << (*c)->getname() << (*c)->help();			
						}
						
						ostream sout2(sbuf);
						sout2.setf(0x0002); //left does causes compile error
						sout2 << endl << "   " << setw(10) << "\\" << "Execute last command";			
						sout2 << endl << "   " << setw(10) << "<tab>" << "Clear the command prompt";			
					}
					
					break;
				}
			}
			
			if(error)
				sout << endl << "Error: " << error;
		
			strcpy(last, buf);
		}		
	}
}

void shell::getline(char *buf, size_t len)
{
	istream sin(sbuf);
	ostream sout(sbuf);

	char *ptr_beg = &buf[0];
	char *ptr_end = &buf[len - 1];

	while(true)
	{
		int c = sin.get();
		switch(c)
		{
			case '\r':
			case '\n':
				*ptr_beg = 0;
				return;
			
			case '\b':
				if(ptr_beg > buf)
				{
					sout << "\b \b" << flush;
					ptr_beg--;
				}
				break;
				
			case '\t':
				for(; ptr_beg > buf; ptr_beg--)
					sout << "\b \b" << flush;
				break;
				
			default:
				if(isprint(c) && ptr_beg < ptr_end)
				{
					sout << char(c) << flush;
					*ptr_beg++ = c;
				}
				break;
		}
	}
}

