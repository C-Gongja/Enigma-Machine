#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "common.h"

#define LETTER_BUFF_SIZE 27

/* Your definition of Reflector */
typedef struct Reflector
{
	char mapping[LETTER_BUFF_SIZE];
} Reflector;

Reflector *new_Reflector(const char *mapping);
char reflector_encrypt(Reflector *self, char c);
void free_Reflector(Reflector *self);

#endif
