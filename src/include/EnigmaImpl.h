#ifndef ENIGMA_IMPL_H
#define ENIGMA_IMPL_H

#include "Enigma.h"
#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"

struct Enigma
{
	/* Your implementation of Enigma */
	Plugboard *plugboard;
	Reflector *reflector;
	Rotor *rotors;
	size_t num_rotors;
	size_t *rings;
	size_t *setting;
	size_t num_pairs;
	const char *pairs;
};

#endif
