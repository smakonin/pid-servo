// $Id: string.h,v 1.9 2009/04/04 19:05:16 smakonin Exp $

// string.h			   Copyright (C) 1997, Real-Time Systems Inc.
//-------------------------------------------- All Rights Reserved ----------
//
//	Character String Manipulation
//
//---------------------------------------------------------------------------

#ifndef STRING_H
#define STRING_H

#include "stddef.h"


size_t strlen		// get length, less terminator
(
  const char* s		   // string to measure
);


char* strcpy		// copy string, including terminator
(
  char* dst,		   // destination buffer
  const char* src	   // source string
);


char* strncpy		// copy string -- truncate or zero-fill to max
(
  char* dst,		   // destination buffer
  const char* src,	   // source string
  size_t max		   // destination size
);

int strlcpy		// copy max chars -- zero terminated
(
  char* dst,		   // destination buffer
  const char* src,	   // source string
  size_t max		   // destination size
);


char* strcat		// concatenate strings
(
  char* dst,		   // destination 
  const char* src	   // source
);


int strcmp		// compare strings
(
  const char* s1,	   // first string
  const char* s2	   // second string
);


int strncmp		// compare strings, length-limited
(
  const char* s1,	   // first string
  const char* s2,	   // second string
  size_t max		   // maximum characters to compare
);


int strcmpi		// compare strings, ignoring case
(
  const char* s1,
  const char* s2
);


extern "C"
{
  void* memcpy		// copy bytes -- overlap not allowed
  (
    void* dest,		   // destination
    const void* src,	   // source
    size_t n		   // count
  );
};


void* memmove		// copy bytes -- overlap allowed
(
  void* dest,		   // destination
  const void* src,	   // source
  size_t n		   // count
);


void* memset		// fill bytes
(
  void* dest,		   // destination
  int c,		   // fill character
  size_t n		   // count
);


int memcmp		// compare byte blocks
(
  const void* s1,	   // operand 1
  const void* s2,	   // operand 2
  size_t n		   // count
);


#endif // STRING_H

