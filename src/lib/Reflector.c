#include "Reflector.h"
#include "common.h"
#include "stdlib.h"
#include "string.h"

/* Your code to implement Reflector here */

Reflector *new_Reflector(const char *mapping)
{
	Reflector *reflector = (Reflector *)malloc(sizeof(Reflector));
	if (reflector == NULL)
	{
		return NULL;
	}
	// i = 0 -> A, i = 1 -> B, ...
	// if i = 0 -> F means A -> F, F -> A
	// so if A is input, then it returns mapping[A - 'A'] = mapping[0] = F
	for (int i = 0; i < LETTER_BUFF_SIZE; i++)
	{
		reflector->mapping[i] = mapping[i];
	}
	return reflector;
}

char reflector_encrypt(Reflector *self, char c)
{
	return self->mapping[c - 'A'];
}

void free_Reflector(Reflector *self)
{
	free(self);
}
