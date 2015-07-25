/*
    ELEX 8030 - PID Servo Project
    Copyright (C) 2009 Stephen Makonin
*/

#ifndef NO_COPY_H
#define NO_COPY_H

class no_copy
{
	private:
		no_copy(const no_copy &);
		const no_copy & operator = (const no_copy &);

	protected:
		no_copy()
		{
		}
		
		~no_copy()
		{
		}
};

#endif
