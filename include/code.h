//
//  code.h
//  Code adapted from and written by Professor Stan Eisenstat.
//  ----------------------------------------------------------------------
//  Interface to putBits() / getBits() / flushBits()
//  ----------------------------------------------------------------------
//

#include <stdio.h>
#include <limits.h>

#define NBITS_MAX (sizeof(long) * CHAR_BIT)

// Write the low-order NBITS bits of CODE to a bit stream on the standard
// output. If NBITS <= 0, NBITS_MAX < NBITS, CODE < 0, or
// 1<<NBITS <= CODE, write an error message to the standard error
// instead.
//
// The bit stream is padded with up to CHAR_BIT-1 zero bits so that its
// length is a multiple of CHAR_BIT, and then is broken into a sequence
// of CHAR_BIT-bit characters that are written to the standard output.
// To do so some low-order bits in CODE may have to be saved until the
// next call to putBits(), and the final call must be followed by a
// call to flushBits().
void putBits(int nBits, long code);

// If there are any bits in the bit stream being saved for the next call to
// putBits(), write to the standard output a character containing those bits
// padded with up to CHAR_BIT-1 zero bits.
void flushBits(void);

// Return an integer whose low-order bits are the next NBITS bits from a
// bit stream on the standard input and whose high-order bits are zero.
// Return EOF if there are fewer than NBITS remaining.  If NBITS <= 0,
// NBITS_MAX < NBITS or CODE < 0, write an error message to the standard
// error and return EOF instead.
//
// The bit stream is assumed to be padded with up to CHAR_BIT-1 zero bits
// so that its length is a multiple of CHAR_BIT and to be broken into
// CHAR_BIT-bit characters.
long getBits(int nBits);
