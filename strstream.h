// $Id: strstream.h,v 1.9 2009/04/04 19:05:16 smakonin Exp $

// strstream.h			   Copyright (C) 1999, Real-Time System Inc.
//------------------------------------------- All Rights Reserved ----------
//
//	String Stream Classes
//
//	This is a minimial implementation -- dynamic allocation and sizing
//	of buffers is not supported.
//
//--------------------------------------------------------------------------

#ifndef STRSTREAM_H
#define STRSTREAM_H

#include "iostream.h"


class strstreambuf : public streambuf 
{
public:
  strstreambuf			// use supplied buffer
  ( 
    char* buf, 			   // buffer to use
    int len,			   // length of buffer
    char* put = 0		   // starting 'put' position
  );
  
  ~strstreambuf();		// destroy object

  char* str()			// point to buffer
  {
    return base();
  }

protected:
  virtual int overflow		// flush buffer, put one more character
  (
    int				   // extra character to put
  );

  virtual int underflow();	// fill buffer, return first character

private:
  void init			// initialize object
  (
    char* buf, 			   // buffer to use
    int len, 			   // length of buffer
    char* put			   // starting 'put' position
  );
};


class strstreambase : virtual public ios 
{
public:
  strstreambuf* rdbuf()		// point to buffer
  { 
    return &this->buf; 
  }

protected:
  strstreambase			// use supplied buffer
  (
    char* buf,			  // buffer to use 
    int len, 			  // buffer size
    char* put			  // starting 'put' position
  );

  ~strstreambase();		// destroy object
  
private:
  strstreambuf buf;		// supporting buffer
};


class istrstream : public strstreambase, public istream 
{
public:
  istrstream			// create from buffer
  (
    char* buf, 			   // buffer to use
    int len			   // length of buffer
  );
  
  istrstream			// create from string
  (
    char* str			   // string to use
  );

  ~istrstream();		// destroy object

private:
  istrstream();			// avoid arrays
  istrstream(istrstream&);	// avoid copying
  operator = (istrstream&);	// avoid assignment
};


class ostrstream : public strstreambase, public ostream 
{
public:
  ostrstream			// use supplied buffer
  (
    char* buf, 			   // buffer to use
    int len, 			   // length of buffer
    int mode = ios::out		   // open mode
  );
  
  ~ostrstream();		// destroy object

  char* str()			// point to buffer
  { 
    return strstreambase::rdbuf()->str(); 
  }

  int pcount()			// get amount put so far
  { 
    return strstreambase::rdbuf()->out_waiting(); 
  }

private:
  ostrstream();			// avoid arrays
  ostrstream(ostrstream&);	// avoid copying
  operator = (ostrstream&);	// avoid assignment
};


class strstream : public strstreambase, public iostream 
{
public:
  strstream			// use supplied buffer
  (
    char* buf, 			   // buffer to use
    int len, 			   // length of buffer
    int mode			   // output mode
  );
  
  ~strstream();			// destroy object

  char* str()			// point to buffer
  { 
    return strstreambase::rdbuf()->str(); 
  }

private:
  strstream();			// avoid arrays
  strstream(strstream&);	// avoid copying
  operator = (strstream&);	// avoid assignment
};


#endif // STRSTREAM_H

