// $Id: iomanip.h,v 1.8 2009-03-21 04:27:34 smakonin Exp $

// iostream.h		      Copyright (C) 1996-2002, Real-Time Systems Inc.
//------------------------------------------ All Rights Reserved ------------
//
//	C++ Streams Manipulators
//
//---------------------------------------------------------------------------

#ifndef IOMANIP_H
#define IOMANIP_H

#include "iostream.h"


// stream manipulator with integer parameter

class Smanip_int
{
  ios& (*_f)(ios&, int);		// function to call
  int _i;				// argument for function

public:
  Smanip_int
  (
    ios& (*f)(ios&, int),		// function to call
    int i				// argument for function
  )
  : _f(f),
    _i(i)
  {
  }

  friend istream& operator >> (istream& is, const Smanip_int& m)
  {
    m._f(is, m._i);
    return is;
  }

  friend ostream& operator << (ostream& os, const Smanip_int& m)
  {
    m._f(os, m._i);
    return os;
  }
};


// standard manipulators

Smanip_int setw(int i);			// set width for next operation

Smanip_int setfill(int i);		// set fill character

Smanip_int setbase(int i);		// set conversion base

Smanip_int setprecision(int i);		// set precision


#endif // IOMANIP_H

