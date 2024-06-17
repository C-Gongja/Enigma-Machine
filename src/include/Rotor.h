#ifndef ROTOR_H
#define ROTOR_H

#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LETTER_SIZE 26
#define MAX_NOTCHES 10

/* Your definition of Rotor */
/// @param num_rotors The number of rotors used in this machine
/// @param rotors An array of strings describing the rotor. The first 26
/// charactors is the mapping, or wiring. The 27th charactor must be a comma,
/// followed by the notch(s). The 0th rotor is the fastest one, the last rotor
/// is the closest to the reflector.
/// @param rings The ring setting for each rotor.
/// 	-	how to set each rotor and notch, it change the sequence of letter but not notch position.
/// @param inits The initial setting for each rotor.
/// 	-	how to set each rotor in the beginning of a machine, this change the notch position.
/*
 * Rotor struct
 * each_rotor: 2D array of rotor mappings
 * notch_size: number of notches in the rotor
 * position: current position of each rotor
 */
typedef struct Rotor
{
	char **each_rotor;
	char **rotor_setting;
	char **notch;
	size_t rotor_size;
	size_t *ring_setting;
	size_t *position;

} Rotor;

/// @brief Creates a new Rotor
/// @param rotor A string describing the rotor. The first 26
/// charactors is the mapping, or wiring. The 27th charactor must be a comma,
/// followed by the notch(s).
/// @param ring The ring setting for the rotor.
/// @param init The initial setting for the rotor.
/// @return An initialized rotor.
Rotor *new_Rotor(size_t size);

void set_Rotor(Rotor *self, const char **rotors, size_t size, size_t *ring, size_t *init);

void tick_Rotor(Rotor *self, int numTicks);

/// @brief Get the mapping of the rotor.
/// @param self A high level representation of the rotor.
/// @param dst Destination buffer. Store the result in the buffer.
/// @param src A null terminated string to be encrypted.
/// @return dst
char rotor_encrypt(Rotor *self, char src, int direction);

/// @brief Get the setting of rotors.
/// @param self A high level representation of the rotor.
size_t *get_rotor_setting(Rotor *self);

/// @brief Reset the rotor to the new setting
/// @param self A high level representation of the rotor.
/// @param new_setting The new setting for the rotor.
void reset_Rotor(Rotor *self, size_t *new_setting);

/// @brief Deallocates the rotor.
/// @param self A high level representation of the rotor.
void free_Rotor(Rotor *self);

#endif
