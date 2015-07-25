/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef MYSHELL_H
#define MYSHELL_H

#include "stddef.h"
#include "no_copy.h"
#include "ctype.h"
#include "iomanip.h"
#include "string.h"
#include "shell.h"
#include "sys_objects.h"
#include "task.h"
#include "timer.h"

class cmd_hello : public command
{
	private:
		sys_objects &so;
		
	public:
		cmd_hello(const char *name, sys_objects &o) : command(name), so(o)
		{
		}

		virtual const char *parse(istream &, ostream &sout)
		{
			sout << endl << "Hello World!";
			return 0;
		}
		
		virtual const char *help()
		{
			return "Prints hello message";
		}
};

class cmd_help : public command
{
	private:
		sys_objects &so;
		
	public:
		cmd_help(const char *name, sys_objects &o) : command(name), so(o)
		{
		}

		virtual const char *parse(istream &, ostream &)
		{
			return 0;
		}
		
		virtual const char *help()
		{
			return "Diplay a list of shell commands";
		}
};

class cmd_pwm : public command
{	
	private:
		sys_objects &so;
		
	public:
		cmd_pwm(const char *name, sys_objects &o) : command(name), so(o)
		{
		}

		virtual const char *parse(istream &sin, ostream &sout)
		{
			float dc = 0.0;
			char ch[4];
			
			if(!(sin >> setw(4) >> dec >> ch))
			{
				sout << endl << "No device specified: res or tec";
				return 0;
			}

			if(!(sin >> dec >> dc))
			{
				if(strcmp(ch, "res") == 0)
					sout << endl << "Resistor PWM duty cycle is " << so.res.getduty();
				else if(strcmp(ch, "tec") == 0)
					sout << endl << "TEC PWM duty cycle is " << so.tec.getduty();
				else
					sout << endl << "No supported device named: " << ch;
				return 0;
			}
			
			if(strcmp(ch, "res") == 0)
				so.res.setduty(dc);
			else if(strcmp(ch, "tec") == 0)
				so.tec.setduty(dc);
			else
				sout << endl << "No supported device named: " << ch;

			return 0;
		}

		virtual const char *help()
		{
			return "Displays or sets the PWM duty cycle for [res or tec]";
		}
};

class cmd_temp : public command
{	
	private:
		sys_objects &so;
		
	public:
		cmd_temp(const char *name, sys_objects &o) : command(name), so(o)
		{
		}

		virtual const char *parse(istream &, ostream &sout)
		{
			sout.setf(ios::fixed, ios::floatfield);
            sout.precision(2);
            sout << "\r"
            	 << "  Temp = "  << setw(6) << (so.temp.read() * 100) << " (Celsius)"		
				 << "  Raw = "  << setw(6) << so.temp.read_raw()
				 << "  Filtered = "  << setw(6) << so.temp.read_filtered();
			return 0;
		}



		virtual const char *help()
		{
			return "Displays the temperature from the LM35DT sensor";
		}
};


class cmd_servo : public command
{	
	private:
		sys_objects &so;
		
	public:
		cmd_servo(const char *name, sys_objects &o) : command(name), so(o)
		{
		}

		virtual const char *parse(istream &sin, ostream &sout)
		{
			char var[16];
			char eq[5];
			float val = 0.0;
			bool set = true;
			
			if(!(sin >> setw(16) >> var))
			{
				sout << endl << "No variable given: show, pgain, igain, dgain, setpoint, ilimit, deadband, oplimit, safeval, mode, raw, temp, curerr, preverr, accumerr, response, pwm.";
				return 0;
			}
			
			if(!(sin >> setw(5) >> eq))
			    set = false;
			    
			if(!(sin >> dec >> val) && set && eq[0] == '=')
			{
			    sout << endl << "No value specified";
				return 0;
			}
			               			    
			if(strcmp(var, "show") == 0)
			{
			    if(!set)
			    {
		            sout << endl << "Must be: show [all or line]";
				    return 0;
			    }
			    
			    if(strcmp(eq, "line") == 0)
			        so.servo.print_line(sout);
			    else if(strcmp(eq, "all") == 0)
			        so.servo.print_values(sout);
			    else if(strcmp(eq, "loop") == 0)
			    {
			        while(true)
			        {
			            so.servo.print_line(sout);
			            sout << endl << "Press <enter> to exit..." << flush;
			            timer::delay(1000);
			            
			            int c = sin.get();
			            if(c == '\r' || c == '\n')
                            break;		            
			        }
			    }
			    else
			        sout << endl << "Must be: show [all or line or loop] (not " << eq << ")";
			        
			    return 0;
			}
			else
			{
			    if(set)
			    {
			        return so.servo.set(var, val);
			    }
			    else
			    {
			        val = so.servo.get(var);
			        
			        if(val == ~0)			           
			            sout << endl << "No such var: " << var;
			        else
			            sout << endl << var << " = " << val; 
			            
			        return 0; 
			    }
			}
			    
			return 0;
		}

		virtual const char *help()
		{
			return "Displays or sets the PID Servo paramerters";
		}
};

class cmd_memdump : public command
{
	private:
		sys_objects &so;
		
	public:
		cmd_memdump(const char *name, sys_objects &o) : command(name), so(o)
		{
		}

		virtual const char *parse(istream &sin, ostream &sout)
		{
			size_t beg_addr;
			size_t end_addr;

			if(!(sin >> hex >> beg_addr))
				return "Need start address in hex.";

			if(!(sin >> hex >> end_addr))
				end_addr = beg_addr + 0x80;

			int flags = sout.flags();
			sout << setfill('0') << hex;
			for(size_t addr = beg_addr & ~0xF; addr < end_addr; addr += 0x10)
			{
				sout << endl << setw(4) << addr << " : ";
				for(int i = 0; i < 0x10; i++)
				{
					char *cp = reinterpret_cast<char *>(addr + i);
					sout << setw(2) << int(*cp) << " ";
				}

				sout << " ";

				for(int i = 0; i < 0x10; i++)
				{
					char *cp = reinterpret_cast<char *>(addr + i);
					if(isprint(*cp))
						sout << *cp;
					else
						sout << ".";		
				}
			}

			sout.flags(flags);
			sout << setfill(' ');
			return 0;
		}

		virtual const char *help()
		{
			return "Dumps memory from a given address";
		}
};

class myshell : public task, public shell
{
	private:
		sys_objects &so;
		
		
	protected:
		virtual void main()
		{
			command *menu[] = 
			{
				new cmd_hello("hello", so),
				new cmd_help("help", so),
				new cmd_memdump("memdump", so),
				new cmd_pwm("pwm", so),
				new cmd_servo("servo", so),
				new cmd_temp("temp", so),
				0
			};

			present(menu);

			for(command **c = menu; *c; c++)
				delete *c;
		}
		
	public:
		myshell(size_t size, int p, sys_objects &o) : 
		task(size, p),
		shell(&o.com, "sh$ "), 
		so(o)
		{
			fork();
		}
};

#endif

