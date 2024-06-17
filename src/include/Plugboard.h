#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include "common.h"
#include <stdlib.h>
// included
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LETTER_SIZE 26

/* Your definition of Plugboard */
// array of plugboard?
// Or make map of plugboard?
typedef struct Plugboard
{
	char encrypted[LETTER_SIZE];

} Plugboard;

Plugboard *new_Plugboard(size_t num_pairs, const char *pairs);
char plugboard_encrypt(Plugboard *plugboard, char input);

void free_Plugboard(Plugboard *self);

#endif
