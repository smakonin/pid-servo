// $Id: ctype.h,v 1.8 2009-03-21 04:27:34 smakonin Exp $

// ctype.h			   Copyright (C) 1997, Real-Time Systems Inc.
//-------------------------------------------- All Rights Reserved ----------
//
//	Character Classification and Conversion
//
//---------------------------------------------------------------------------

#ifndef CTYPE_H
#define CTYPE_H


// character classification

int isascii(int c);		// is character in 0x00...0x7F?
int isspace(int c);		// is character in 0x09...0x0D, 0x20
int isprint(int c);		// is character in 0x20...0x7E?
int isgraph(int c);		// is character in 0x21...0x7E?
int isdigit(int c);		// is character a decimal digit?
int isxdigit(int c);		// is character a hexadecimal digit?
int islower(int c);		// is character an lower-case letter?
int isupper(int c);		// is character an upper-case letter?


// character conversion

int tolower(int c);		// convert character to lower case
int toupper(int c);		// convert character to upper case


#endif // CTYPE_H