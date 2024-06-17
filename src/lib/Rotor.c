#include "Rotor.h"
#include "common.h"

/* Your code to implement Rotor here */
char get_alphabet(char a)
{
	char result = a;
	if (a < 'A')
	{
		result = a + 26;
	}
	else if (a > 'Z')
	{
		result = a - 26;
	}
	return result;
}

size_t update_setting(size_t setting, size_t move)
{
	setting += move;
	if (setting > 25)
	{
		setting -= 26;
	}
	return setting;
}

/*
ring setting: 	how to set each rotor and notch, it change the sequence of letter but not notch position.
if(i - ring[i] > 26)
	index = abs(i - ring[i] - 26)
else
	index = abs(i - ring[i])
rotor->each_rotor[i] = rotor->each_rotor[index] + ring[i]
initial setting: 	how to set each rotor in the beginning of a machine. position of the rotor in the beginning.
shift the rotor to the left or right.
*/
Rotor *new_Rotor(size_t size)
{
	if (size == 0)
	{
		return NULL;
	}
	Rotor *rotor = (Rotor *)malloc(sizeof(Rotor));
	rotor->each_rotor = malloc(size * sizeof(char *));
	rotor->rotor_setting = malloc(size * sizeof(char *));
	rotor->position = (size_t *)malloc(size * sizeof(size_t));
	rotor->notch = malloc((size * (MAX_NOTCHES + 1)) * sizeof(char *));
	rotor->ring_setting = (size_t *)malloc(size * sizeof(size_t));
	rotor->rotor_size = size;

	if (rotor->each_rotor == NULL || rotor->rotor_setting == NULL || rotor->notch == NULL ||
		rotor->position == NULL || rotor->ring_setting == NULL)
	{
		// Handle memory allocation failure
		free_Rotor(rotor);
		fprintf(stderr, "Memory allocation failed\n");
		return NULL;
	}

	return rotor;
}

void update_notch(char *notch, size_t numShifts)
{
	if (notch == NULL)
	{
		return;
	}
	for (size_t i = 0; i < strlen(notch); i++)
	{
		char result = notch[i] - numShifts;
		if (result < 'A')
		{
			result += 26;
		}
		notch[i] = result;
	}
}

void set_setting(char *str, size_t numShifts, char *notch)
{
	int len = strlen(str);
	if (len > 1)
	{
		// Ensure the number of shifts is within the length of the string
		numShifts = numShifts % len;

		// Temporary array to hold the shifted string
		char temp[len + 1];

		// Copy the part of the string that will be moved to the front
		strncpy(temp, str + numShifts, len - numShifts);
		// Copy the part of the string that will be moved to the back
		strncpy(temp + len - numShifts, str, numShifts);
		// Null terminate the temporary string
		temp[len] = '\0';

		// Copy the shifted string back to the original string
		strcpy(str, temp);
		update_notch(notch, numShifts);
	}
}

void set_ring(Rotor *rotor, size_t size, size_t *ring, size_t *init)
{
	// set the rotors
	for (size_t i = 0; i < size; i++)
	{
		// initial setting
		rotor->position[i] = init[i];
		rotor->ring_setting[i] = ring[i];
	
		// ring setting
		// make copy of each_rotor[i] to each_rotor[i]
		char *temp_rotor = strdup(rotor->each_rotor[i]);
		int ring_num = (int)ring[i];
		for (int j = 0; j < 26; j++)
		{
			int index = j + ring_num;
			if (index > 25)
			{
				index -= 26;
			}
			rotor->each_rotor[i][index] = get_alphabet(temp_rotor[j] + ring_num);
		}
		free(temp_rotor);
		set_setting(rotor->each_rotor[i], rotor->position[i], rotor->notch[i]);
	}
}

void parse_Rotor(Rotor *self, size_t index)
{
	// Split the rotor string into the rotor mapping and notches
	char *temp_copy = strdup(self->each_rotor[index]); // Make a copy of the string
	char *token = strtok(temp_copy, ",");
	strcpy(self->each_rotor[index], token);
	self->each_rotor[index][LETTER_SIZE] = '\0'; // Ensure null termination

	// Save notches
	token = strtok(NULL, ",");
	if (token == NULL)
	{
		self->notch[index] = NULL;
	}
	else
		self->notch[index] = strdup(token);

	free(temp_copy);
}

void set_Rotor(Rotor *self, const char **rotors, size_t size, size_t *ring, size_t *init)
{
	// Get rotors and notches
	for (size_t i = 0; i < size; i++)
	{
		self->each_rotor[i] = strdup(rotors[i]);
		if (self->each_rotor[i] == NULL)
		{
			// Handle strdup failure
			for (size_t j = 0; j < i; j++)
			{
				free(self->each_rotor[j]);
			}
			free(self->each_rotor);
			free(self->position);
			free(self->notch);
			free(self->ring_setting);
			free(self);
			return;
		}
		// store the init rotor setting
		self->rotor_setting[i] = strdup(rotors[i]);
		if (self->rotor_setting[i] == NULL)
		{
			// Handle strdup failure
			free_Rotor(self);
			fprintf(stderr, "Memory allocation failed\n");
			return;
		}
		parse_Rotor(self, i);
	}
	set_ring(self, size, ring, init);
}

int findCharA(const char *str)
{
	int length = strlen(str);
	for (int i = 0; i < length; i++)
	{
		if (str[i] == 'A')
		{
			return 1;
		}
	}
	return 0;
}

void tick_Rotor(Rotor *self, int numTicks)
{
	int notch_move = numTicks % 26;
	char *check_notch = NULL;

	for (size_t i = 0; i < self->rotor_size; i++)
	{
		if (self->notch[i] != NULL)
		{
			check_notch = strdup(self->notch[i]);
			int notch_pos = findCharA(self->notch[i]);
			// when the middle rotor in notch position, move the rotor
			if (notch_pos == 1 && self->notch[i + 1] != NULL)
			{
				if (i == self->rotor_size - 1 && notch_move == 0)
				{
					notch_move = 0;
				}
				else
					notch_move = 1;
			}
			// printf("notch before tick: %s\n", self->notch[i]);
			set_setting(self->each_rotor[i], notch_move, self->notch[i]);
			self->position[i] = update_setting(self->position[i], notch_move);
			// printf("notch after tick: %s\n", self->notch[i]);
			notch_move = 0;
			for (size_t j = 0; j < strlen(self->notch[i]); j++)
			{
				if (check_notch[j] < (char)self->notch[i][j])
				{
					notch_move += 1;
					if (numTicks / 26 > 0)
					{
						notch_move += numTicks / 26;
					}
				}
			}
			if (self->notch[i] != NULL)
			{
				free(check_notch);
			}
		}
	}
}

int rotor_getIndex(char *str, char c)
{
	int index = 0;

	// Loop through the string to find the character
	while (str[index] != '\0')
	{
		if (str[index] == c)
		{
			return index;
		}
		index++;
	}

	// If the character is not found, return -1
	return -1;
}

char rotor_encrypt(Rotor *rotor, char src, int direction)
{
	char letter = src;
	if (direction == 0)
	{
		for (size_t i = 0; i < rotor->rotor_size; i++)
		{
			letter = get_alphabet(rotor->each_rotor[i][letter - 'A']);
			letter = get_alphabet(letter - rotor->position[i]);
		}
	}
	// backward rotor
	else if (direction == 1)
	{
		for (int i = (int)rotor->rotor_size - 1; i >= 0; i--)
		{
			letter = get_alphabet(letter + rotor->position[i]);
			int back_index = rotor_getIndex(rotor->each_rotor[i], letter);
			letter = back_index + 'A';
		}
	}

	return letter;
}

size_t *get_rotor_setting(Rotor *self)
{
	return self->position;
}

void reset_Rotor(Rotor *self, size_t *new_setting)
{
	for (size_t i = 0; i < self->rotor_size; i++)
	{
		self->position[i] = new_setting[i];
		free(self->each_rotor[i]);
		free(self->notch[i]);
		self->each_rotor[i] = strdup(self->rotor_setting[i]);
		parse_Rotor(self, i);
	}
	set_ring(self, self->rotor_size, self->ring_setting, self->position);
}

void free_Rotor(Rotor *rotor)
{
	if (rotor == NULL)
	{
		return;
	}
	for (size_t i = 0; i < rotor->rotor_size; i++)
	{
		free(rotor->each_rotor[i]);
		free(rotor->rotor_setting[i]);
		free(rotor->notch[i]);
	}
	free(rotor->each_rotor);
	free(rotor->rotor_setting);
	free(rotor->notch);
	free(rotor->position);
	free(rotor->ring_setting);
	free(rotor);
}
