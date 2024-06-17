#include "Enigma.h"
#include "EnigmaImpl.h"
#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"

/* Your code to implement Enigma here */

Enigma *new_Enigma(size_t num_rotors, const char **rotors, size_t *rings, size_t *inits, const char *reflector, size_t num_pairs, const char *pairs)
{
	Enigma *enigma = (Enigma *)malloc(sizeof(Enigma));
	if (enigma == NULL)
	{
		return NULL;
	}

	// printf("plugboard setting: numspairs: %li, pairs: %s\n", num_pairs, pairs);
	Plugboard *plugboard = new_Plugboard(num_pairs, pairs);
	// printf("reflector setting: %s\n", reflector);
	Reflector *enigma_reflector = new_Reflector(reflector);
	Rotor *enigma_rotors = new_Rotor(num_rotors);
	// printf("rotor setting: ");
	// for(size_t i = 0; i < num_rotors; i++)
	// {
	// 	printf("num_rotors: %li, rotors: %s, rings: %li, inits: %li\n", i, rotors[i], rings[i], inits[i]);
	// }
	set_Rotor(enigma_rotors, rotors, num_rotors, rings, inits);

	enigma->plugboard = plugboard;
	enigma->reflector = enigma_reflector;
	enigma->rotors = enigma_rotors;
	enigma->num_rotors = num_rotors;
	enigma->rings = rings;
	enigma->setting = inits;
	enigma->num_pairs = num_pairs;
	enigma->pairs = pairs;

	return enigma;
}

void *encrypt_Enigma(Enigma *self, char *dst, const char *src)
{
	if (src == NULL)
	{
		dst[0] = '\0';
		return dst;
	}
	for (int i = 0; src[i] != '\0'; i++)
	{
		if (src[i] == ' ')
		{
			dst[i] = ' ';
			continue;
		}
		char letter = src[i];
		int direction = 0;
		if (self->plugboard != NULL)
		{
			letter = plugboard_encrypt(self->plugboard, letter);
		}
		if (self->rotors != NULL)
		{
			tick_Enigma(self);
			letter = rotor_encrypt(self->rotors, letter, direction);
		}
		letter = reflector_encrypt(self->reflector, letter);

		direction = 1;
		if (self->rotors != NULL)
		{
			letter = rotor_encrypt(self->rotors, letter, direction);
		}
		letter = plugboard_encrypt(self->plugboard, letter);
		dst[i] = letter;
	}
	dst[strlen(src)] = '\0'; // Null-terminate the destination string
	return dst;
}

void reset_rotor_Enigma(Enigma *self, size_t *new_setting)
{
	reset_Rotor(self->rotors, new_setting);
}

void free_Enigma(Enigma *self)
{
	if (self != NULL)
	{
		free_Plugboard(self->plugboard);
		free_Reflector(self->reflector);
		free_Rotor(self->rotors);
		free(self);
	}
}

void get_setting_Enigma(Enigma *self, char *ret)
{
	self->setting = get_rotor_setting(self->rotors);
	for (size_t i = 0; i < self->num_rotors; i++)
	{
		ret[i] = self->setting[i] + 'A';
	}
}

void tick_Enigma(Enigma *self)
{
	tick_Rotor(self->rotors, 1);
}

// n번 맨 앞(첫번째) rotor를 돌린다는 뜻
void tick_n_Enigma(Enigma *self, size_t n)
{
	tick_Rotor(self->rotors, (int)n);
}
