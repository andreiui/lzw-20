//
//  table.h
//  Copyright © 2020-2021 Andrei Pascu. All rights reserved.
//  ----------------------------------------------------------------------
//  Interface to StringTable data structure for LZW20 encoding / decoding
//  ----------------------------------------------------------------------
//

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

// Definitions of custom types for bits_t, code_t, char_t 
#define bits_t char
#define code_t unsigned int
#define char_t unsigned
#define EMPTY 0

typedef struct StringTable StringTable;
typedef struct Node Node;
typedef struct Pair Pair;

StringTable *createStringTable(bits_t maxBits);

unsigned long maxStringCode(StringTable *st);

void deleteStringTable(StringTable *st);

void insertStringTable(StringTable *st, code_t PREF, char_t CHAR);

code_t lookupStringTable(StringTable *st, code_t PREF, char_t CHAR);

void fillStringTable(StringTable *st);

void pruneStringTable(StringTable *st1);

char putStringTable(StringTable *st, code_t CODE);
