#include "Plugboard.h"
#include "common.h"

/* Your code to implement Plugboard here */

Plugboard *new_Plugboard(size_t num_pairs, const char *pairs)
{
	// we need to parse the pairs. with num_pairs
	Plugboard *plugboard = (Plugboard *)malloc(sizeof(Plugboard));
	if (plugboard == NULL)
	{
		return NULL;
	}
	for (int i = 0; i < LETTER_SIZE; i++)
	{
		plugboard->encrypted[i] = i + 'A';
	}
	if (num_pairs == 0)
	{
		return plugboard;
	}
	if ((int)strlen(pairs) % 2 != 0 || num_pairs > 13)
	{
		free(plugboard);
		printf("Invalid number of pairs\n");
		return NULL;
	}
	for (int i = 0; i < (int)num_pairs; i++)
	{
		char a = toupper(pairs[i * 2]);
		char b = toupper(pairs[i * 2 + 1]);
		plugboard->encrypted[a - 'A'] = b;
		plugboard->encrypted[b - 'A'] = a;
	}
	return plugboard;
}

char plugboard_encrypt(Plugboard *plugboard, char input)
{
	return plugboard->encrypted[input - 'A'];
}

void free_Plugboard(Plugboard *self)
{
	free(self);
}
