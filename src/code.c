//
//  code.c
//  Code adapted from and written by Professor Stan Eisenstat.
//  ----------------------------------------------------------------------
//  Implementation of putBits() / flushBits() / getBits() described in
//    code.h
//  ----------------------------------------------------------------------
//

#include <stdlib.h>
#include <string.h>
#include "../include/code.h"

// Information shared by putBits() and flushBits()
static int nExtra = 0;                                  // #bits from previous byte(s)
static unsigned long extraBits = 0;                     // Extra bits from previous byte(s)

// Write CODE (NBITS bits) to standard output
void putBits(int nBits, long code) {
    if (nBits <= 0 || NBITS_MAX < nBits) {              // NBITS valid?
        fprintf(stderr, "invalid nBits = %d\n", nBits);
        return;
    }
    
    unsigned long maxCode = 1UL << (nBits - 1);         // Compute maximum code
    maxCode = maxCode + (maxCode - 1);

    if (code < 0 || maxCode < code) {                   // CODE representable?
        fprintf(stderr, "nBits = %d, maxCode = %lu, code = %ld\n", nBits, maxCode, code);
        return;
    }

    // If EXTRABITS << NBITS could overflow, output high-order CHAR_BIT bits
    if (nBits > NBITS_MAX - CHAR_BIT) {
		putBits (CHAR_BIT, code >> (nBits - CHAR_BIT));
		nBits -= CHAR_BIT;
    }

    nExtra += nBits;                                    // Add bits to EXTRABITS
    extraBits = (extraBits << nBits) | code;
    while (nExtra >= CHAR_BIT) {                        // Output whole chars
		nExtra -= CHAR_BIT;                             // Save remaining bits
		unsigned long c = extraBits >> nExtra;
		putchar(c);
		extraBits ^= c << nExtra;
    }
}

// Flush remaining bits to standard output
void flushBits(void) {
    if (nExtra != 0)
        putchar(extraBits << (CHAR_BIT - nExtra));
}

// Return next code (#bits = NBITS) from input stream or EOF on end-of-file
long getBits(int nBits) {
    if (nBits <= 0 || NBITS_MAX < nBits) {              // NBITS valid?
		fprintf(stderr, "invalid nBits = %d\n", nBits);
		return EOF;
    }
    
    unsigned long maxCode = 1 << (nBits - 1);           // Maximum possible code
    maxCode = maxCode + (maxCode - 1);
    static int nExtra = 0;                              // #bits from previous byte(s)
    static unsigned long extraBits = 0;                 // Extra bits from previous byte(s)
    long result = 0;                                    // Value to return

    // If EXTRABITS << NBITS could overflow, read high-order CHAR_BIT bits
    if (nBits > NBITS_MAX - CHAR_BIT) {
		result = getBits (CHAR_BIT);
		if (result < 0)
			return EOF;
		nBits -= CHAR_BIT;
    }

    // Read enough new bytes to have at least NBITS bits to extract code
    long c;
    while (nExtra < nBits) {
		if ((c = getchar()) == EOF)                     // Too few bits?
			return EOF;
		nExtra += CHAR_BIT;
		extraBits = (extraBits << CHAR_BIT) | c;
    }

    // Extract remaining bits and save remainder
    nExtra -= nBits;
    c = extraBits >> nExtra;
    extraBits ^= c << nExtra;
    return (result << nBits) | c;
}
