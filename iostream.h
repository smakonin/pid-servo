// $Id: iostream.h,v 1.8 2009-03-21 04:27:34 smakonin Exp $

// iostream.h	 	      Copyright (C) 1996-1997, Real-Time Systems Inc.
//------------------------------------------ All Rights Reserved ------------
//
//	C++ Streams Library
//
//---------------------------------------------------------------------------

#ifndef IOSTREAM_H
#define IOSTREAM_H


//---------------------------------------------------------------------------
//
//	Basic definitions
//

typedef int streampos;		// position in stream
typedef int streamoff;		// delta position in stream

const int EOF = -1;		// end of file sentinel


//---------------------------------------------------------------------------
//
//	Base class for all streams
//

class ios
{
public:

  // special values

  enum open_mode		// stream opening modes
  {
    in		= 0x01,		// open for reading
    out		= 0x02,		// open for writing
    ate		= 0x04,		// seek to eof upon original open
    app		= 0x08,		// append mode: all additions at eof
    trunc	= 0x10,		// truncate file if already exists
    nocreate	= 0x20,		// open fails if file doesn't exist
    noreplace	= 0x40,		// open fails if file already exists
    binary	= 0x80		// binary file    
  };

  enum io_state			// stream state flags
  {
    goodbit	= 0x00,		   // no errors
    eofbit	= 0x01,		   // end of file reached
    failbit	= 0x02,		   // formatting/parsing error
    badbit	= 0x04		   // serious error, data may be lost
  };

  enum seek_dir			// seek starting points
  {
    beg,			   // start from beginning, seek forward
    cur,			   // start from current, seek either way
    end				   // start from end, seek backward
  };

  enum				// formatting flags
  {
    skipws	= 0x0001,	   // skip whitespace
    left	= 0x0002,	   // align left in field
    internal	= 0x0004,	   // pad between sign and number
    right	= 0x0008,	   // align right in field
    oct		= 0x0010,	   // octal base
    dec		= 0x0020,	   // decimal base
    hex		= 0x0040,	   // hexadecimal base
    showbase	= 0x0080,	   // show base indicator for integers
    showpoint	= 0x0100,	   // always show point for floats
    uppercase	= 0x0200,	   // show 'X' for hex, 'E' for floats
    showpos	= 0x0400,	   // show '+' for positive numbers
    scientific	= 0x0800,	   // show n.nnnnEnn for floats
    fixed	= 0x1000,	   // show nnn.nnn for floats
    unitbuf	= 0x2000,	   // flush after each output operation
    stdio	= 0x4000,	   // flush after each character

    basefield	= oct | dec | hex,		// all number base bits
    adjustfield	= left | internal | right,	// all alignment bits
    floatfield	= scientific | fixed		// all float format bits
  };


  // constructors and destructor

  ios				// create stream
  (
    class streambuf* buf	   // buffer for stream
  );

  virtual ~ios();		// destroy stream

  class streambuf* rdbuf() const // return pointer to streambuf
  {
    return _sb;
  }


  // stream state interrogation

  int rdstate() const		// get entire state word
  {
    return _state;
  }

  int good() const		// no errors on stream?
  {
    return _state == 0;
  }

  int eof() const		// at end of file?
  {
    return _state & eofbit;
  }

  int fail() const		// error on stream?
  {
    return _state & (failbit | badbit);
  }

  int bad() const		// serious error on stream?
  {
    return _state & badbit;
  }

  operator const void* () const	// test stream state
  {
    return fail() ? 0 : this;
  }

  int operator ! () const	// test stream state
  {
    return fail();
  }


  // stream state control

  void clear			// set stream state
  (
    int s = 0			   // new stream state
  )
  {
    _state = s;
  }

  void set			// set bits in stream state
  (
    int mask			   // bits to set
  )
  {
    _state |= mask;
  }

  void setstate			// set bits in stream state
  (
    int mask			   // bits to set
  )
  {
    _state |= mask;
  }


  // formatting and parsing flags

  int flags() const		// get current formatting flags
  {
    return _flags;
  }

  int flags			// get/set all formatting flags at once
  (
    int word			   // entire flags word
  )
  {
    int old = _flags;
    _flags = word;
    return old;
  }

  int setf			// set some formatting flags unconditionally
  (
    int bits			   // flag bits to set
  )
  {
    int old = _flags;
    _flags |= bits;
    return old;
  }

  int setf			// set some flags in given field
  (
    int bits,			   // flag bits to set
    int field			   // flag bits to clear first
  )
  {
    int old = _flags;
    _flags = (_flags & ~field) | (bits & field);
    return old;
  }

  int unsetf			// clear some formatting flags
  (
    int bits			   // flag bits to clear
  )
  {
    int old = _flags;
    _flags &= ~bits;
    return old;
  }


  // field width control

  int width() const		// get current field width
  {
    return _width;
  }

  int width			// get/set field width
  (
    int w			   // new width to set
  )
  {
    int old = _width;
    _width = w;
    return old;
  }


  // output padding character control

  char fill() const		// get current fill character
  {
    return _fill;
  }

  char fill			// get/set fill character
  (
    char f			   // new fill character
  )
  {
    char old = _fill;
    _fill = f;
    return old;
  }


  // float output precision control

  int precision() const		// get float output precision
  {
    return _precision;
  }

  int precision			// get/set output precision
  (
    int p			   // new float precision
  )
  {
    int old = _precision;
    _precision = p;
    return old;
  }


  // tied stream control

  class ostream* tie() const	// return pointer to tied ostream
  {
    return _tie;
  }

  class ostream* ios::tie	// set/get pointer to tied stream
  (
    ostream* os      		   // new tied output stream
  )
  {
    ostream* old = _tie;
    _tie = os;
    return old;
  }


protected:
  ios();			// create uninitialized ios

  void init			// initialize stream
  (
    class streambuf* s,		   // buffer for stream
    class ostream* t = 0	   // ostream to tie to
  );
  
private:
  ios(ios&);			// protect from copying
  operator = (ios&);		// protect from assignment

  class streambuf* _sb;		// the associated streambuf
  class ostream* _tie;		// tied ostream, if any

  int _state;			// stream state

  int _flags;			// formatting flags
  int _width;			// field width for next operation
  int _precision;		// float output precision
  int _fill;			// output fill character
};


//---------------------------------------------------------------------------
//
//	Base class for all stream buffers
//

class streambuf
{
public:

  // destructor

  virtual ~streambuf();		// destroy streambuf


  // inserting characters

  int out_waiting();		// get number of characters waiting

  int sputc			// put character to streambuf
  (
    int c			   // character to put
  );

  int sputn			// put block to streambuf
  (
    const char* buf, int len	   // buffer and length
  )
  {
    return xsputn(buf, len);
  }


  // extracting characters

  virtual int in_avail();	// get number of characters available

  int sgetc();			// get character, leave in buffer

  int snextc();			// advance to and get next character

  int sbumpc();			// get character, advance to next character

  void stossc();		// advance to next character

  int sgetn			// get block from streambuf
  (
    char* buf, int len		   // buffer and length
  )
  {
    return xsgetn(buf, len);
  }

  int sputbackc			// push character back on stream
  (
    char c
  );


  // positioning stream

  virtual streampos seekoff	// seek from given point
  (
    streamoff off,		     // desired offset
    ios::seek_dir dir,		     // point to seek from
    int mode = (ios::in | ios::out)  // stream mode to seek
  );

  virtual streampos seekpos	// seek to absolute position
  (
    streampos pos,		     // desired offset
    int mode = (ios::in | ios::out)  // stream mode to seek
  );


  // buffer maintenance

  virtual int sync();		// flush output buffer


protected:

  // constructors

  streambuf();			// create without buffer

  streambuf			// create from supplied buffer
  (
    char* buf, int len		   // buffer and length
  );


  // pointer manipulation

  void setb			// set up physical buffer
  (
    char* base,			   // base pointer
    char* ebuf,			   // end pointer
    int del			   // non-zero if destructor should delete
  );

  void setp			// set up put area pointers
  (
    char* base_cur,		   // base and current pointer
    char* end			   // end pointer
  );

  void setg			// set up get area pointers
  (
    char* base,			   // base pointer
    char* cur,			   // current pointer
    char* end			   // end pointer
  );

  int blen() const		// get length of physical buffer
  {
    return _ebuf - _base;
  }   

  char* base() const		// get start of physical buffer
  {
    return _base;
  }

  char* ebuf() const		// get end of physical buffer
  {
    return _ebuf;
  }

  char* pbase()	const		// get start of put area
  {
    return _pbase;
  }

  char* pptr() const		// get current position in put area
  {
    return _pptr;
  }

  char* epptr()	const		// get end of put area
  {
    return _epptr;
  }

  char* eback()	const		// get start of get area
  {
    return _eback;
  }

  char* gptr() const		// get current position in get area
  {
    return _gptr;
  }

  char* egptr()	const		// get end of get area
  {
    return _egptr;
  }

  void pbump			// update the put pointer (no checking)
  (
    int change			   // change amount
  )
  {
    _pptr += change;
  }

  void gbump			// update the get pointer (no checking)
  (
    int change			   // change amount
  )
  {
    _gptr += change;
  }


  // inserting characters
  
  virtual int overflow		// flush buffer, put one more character
  (
    int c = EOF			   // character to send after flush
  );

  virtual int xsputn		// implementation of sputn
  (
    const char* buf, int len	   // buffer and length
  );


  // extracting characters

  virtual int underflow();	// fill empty buffer, get one more character

  virtual int xsgetn		// implementation of sgetn
  (
    char* buf, int len		   // buffer and length
  );

  virtual int pbackfail		// implementation of sputbackc
  (
    int c			   // character to put back
  );


private:
  streambuf(streambuf&);	// protect from copying
  operator = (streambuf&);	// protect from assignment

  int _del;			// destructor should delete buffer

  char* _base;			// start of physical buffer
  char* _ebuf;			// end of physical buffer

  char* _pbase;			// start of put area
  char* _pptr;			// current position in put area
  char* _epptr;			// end of put area

  char* _eback;			// start of get area
  char* _gptr;			// current position in get area
  char* _egptr;			// end of get area
};


//---------------------------------------------------------------------------
//
//	Base class for all input streams
//

class istream : virtual public ios
{
public:

  // constructor and destructor

  istream                       // create stream
  (
    streambuf* s		   // buffer to use
  );

  virtual ~istream();		// destroy stream


  // buffer maintenance

  int ipfx			// called before extraction operation
  (
    int unformatted = 0		   // zero to skip whitespace
  );

  void isfx()			// called after extraction operation
  {
  }


  // stream positioning

  streampos tellg();		// get stream position

  istream& seekg		// set stream to absolute position
  (
    streampos p			   // desired position
  );

  istream& seekg		// set stream position relative to point
  (
    streamoff o,		   // offset from given point
    ios::seek_dir d		   // point to seek from
  );

  int sync()			// flush associated output stream
  {
    return rdbuf()->sync();
  }


  // unformatted extraction

  int get();			// get one character from stream

  int peek();			// get one character, leave in stream

  istream& get			// get one character from stream
  (
    char& c			   // target character
  );

  istream& get  		// get block into streambuf
  (
    streambuf& s,		   // buffer
    int term = '\n'		   // terminator (not copied, left in source)
  );

  istream& get 			// get block into character string
  (
    char* buf, int len,		   // buffer and length
    int term = '\n'		   // terminator (not copied, left in source)
  );

  istream& getline		// get block into character string
  (
    char* buf, int len,		   // buffer and length
    int term = '\n'		   // terminator (extract and discarded)
  );

  istream& read			// get block of characters into buffer
  (
    char* buf, int len		   // buffer and length
  );

  istream& putback		// push character back on stream
  (
    char c			   // character to push
  );

  istream& ignore		// ignore characters
  (
    int count = 1,		   // number to ignore
    int term = EOF		   // terminator (extract and discard)
  );

  int gcount()			// extraction count from last unformatted op.
  {
    return _gcount;
  }


  // formatted extraction

  istream& operator >> (char&);		 // extract character

  istream& operator >> (int&);		 // extract integer

  istream& operator >> (unsigned int&);	 // extract unsigned integer

  istream& operator >> (long&);		 // extract long integer

  istream& operator >> (unsigned long&); // extract unsigned long integer

  istream& operator >> (float&);	 // extract single float

  istream& operator >> (double&);	 // extract double float

  istream& operator >> (char*);		 // extract token to string

  istream& operator >> (streambuf*);	 // extract into streambuf

  istream& operator >> (istream& (*f)(istream&))	// manipulator
  {
    return (*f)(*this);
  }

  istream& operator >> (ios& (*f)(ios&))		// manipulator
  {
    (*f)(*this);
    return *this;
  }


protected:
  istream();			// create without initializing

private:
  istream(istream&);		// protect from copying
  operator = (istream&);	// protect from assignment

  int _gcount;			// count from last unformatted extraction
};


//---------------------------------------------------------------------------
//
//	Base class for all output streams
//

class ostream : virtual public ios
{
public:

  // constructor and destructor

  ostream       		// create stream
  (
    streambuf* s		   // buffer to use
  );

  virtual ~ostream();		// destroy stream


  // buffer maintenance

  int opfx();			// called before insertion

  void osfx();			// called after insertion

  ostream& flush();		// flush output buffer


  // stream positioning

  streampos tellp();		// get stream position

  ostream& seekp		// set stream to absolute position
  (
    streampos p			   // desired position
  );

  ostream& seekp		// set stream position relative to point
  (
    streamoff o,		   // offset from given point
    ios::seek_dir d		   // point to seek from
  );


  // unformatted insertion

  ostream& put			// put character onto stream
  (
    char c			   // character to put
  );

  ostream& write		// put buffer onto stream
  (
    const char* buf, int len	   // buffer and length
  );


  // formatted insertion

  ostream& operator << (char);		// insert character

  ostream& operator << (int);		// insert integer

  ostream& operator << (unsigned int);	// insert unsigned integer

  ostream& operator << (long);		// insert long integer

  ostream& operator << (unsigned long);	// insert unsigned long integer

  ostream& operator << (float);		// insert single float

  ostream& operator << (double d);	// insert double float

  ostream& operator << (const char*);	// insert zero-terminated string

  ostream& operator << (void*);		// insert pointer value

  ostream& operator << (streambuf*);	// insert contents of streambuf

  ostream& operator << (ostream& (*f)(ostream&))	// manipulator
  {
    return (*f)(*this);
  }

  ostream& operator << (ios& (*f)(ios&))		// manipulator
  {
    (*f)(*this);
    return *this;
  }

protected:
  ostream();			// create without initializing

private:
  ostream(ostream&);		// protect from copying
  operator = (ostream&);	// protect from assignment

  void puts			// put string with justification, fill, etc
  (
    const char* str,		   // string to put
    const char* pfx = 0		   // prefix string
  );

  void puti			// put integer with formatting options
  (
    unsigned val,		   // number to put
    int sign			   // -1 = signed, negative
  );

  void putl			// put long integer with formatting options
  (
    unsigned long val,		   // number to put
    int sign			   // -1 = signed, negative
  );
};


//---------------------------------------------------------------------------
//
//	Base class for input/output streams
//

class iostream : public istream, public ostream
{
public:
  iostream			// create iostream
  (
    streambuf* s		   // buffer to use
  );

  virtual ~iostream();		// destroy stream

protected:
  iostream();
};


//---------------------------------------------------------------------------
//
//	Manipulators
//

ios& oct(ios&);				// set octal for i/o

ios& dec(ios&);				// set decimal for i/o

ios& hex(ios&);				// set hexadecimal for i/o

istream& ws(istream&);			// eat whitespace from stream

ostream& endl(ostream&);		// insert newline and flush stream

ostream& ends(ostream&);		// insert terminating zero

ostream& flush(ostream&);		// flush stream


//---------------------------------------------------------------------------
//
//	Standard streams
//

extern istream cin;
extern ostream cout;
extern ostream cerr;
extern ostream clog;


#endif // IOSTREAM_H

