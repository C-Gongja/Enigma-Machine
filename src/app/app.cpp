extern "C"
{
#include "Enigma.h"
#include "common.h"
}
#include <iostream>
#include <string>

void clear_terminal() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls"); // Windows command to clear the terminal
#else
    system("clear"); // Unix-like system command to clear the terminal
#endif
}

using namespace std;

unordered_map<string, const char *> macroMap = {
	/// Rotor I ~ V used in Enigma I
{"ROTOR_I", ROTOR_I},
{"ROTOR_II", ROTOR_II},
{"ROTOR_III", ROTOR_III},
{"ROTOR_IV", ROTOR_IV},
{"ROTOR_V", ROTOR_V},

/// Reflectors used in Enigma I
{"I_UKW_A", I_UKW_A},
{"I_UKW_B", I_UKW_B},
{"I_UKW_C", I_UKW_C},

/// Rotors used in Enigma M4
{"ROTOR_VI", ROTOR_VI},
{"ROTOR_VII", ROTOR_VII},
{"ROTOR_VIII", ROTOR_VIII},
{"ROTOR_BETA", ROTOR_BETA},
{"ROTOR_GAMMA", ROTOR_GAMMA},

/// Reflectors in Enigma M4
{"UKW_B", UKW_B},
{"UKW_C", UKW_C}
};

void help() {
	//explain about the Enigma machine
	// Plugboard:
	// Rotors:
	// rings start with 0
	// init 0 = A, 1 = B, 2 = C, ..., 25 = Z
	// Reflector:
}

const char* getMacro(string macro) {
	// Lookup user input in the macro map
    auto it = macroMap.find(macro);
    if (it != macroMap.end()) {
        return it->second;
    } else {
        cout << "Unknown reflector name. Please re-enter:" << endl;
		return NULL;
    }
}

string to_uppercase(const string &input) {
    string result = input;
    transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return toupper(c);
    });
    return result;
}

void print_setting(Enigma* enigma, const char **rotors, size_t rotor_size) {
	cout << "Enigma setting: " << endl;
	cout << "Rotors: " << endl;
	for (int i=0; i < rotor_size; i++) {
		cout << "\t" << rotors[i] << endl;
	}
	cout << endl;
	print_Enigma(enigma);
}

void print_main(){
	cout << "----------------------------------" << endl;
	cout << "*                                *" << endl;
	cout << "* Welcome to the Enigma Machine! *" << endl;
	cout << "*                                *" << endl;
	cout << "*                 by Taeyoon Kim *" << endl;
	cout << "----------------------------------" << endl;
	cout << "e: Encrypt a message" << endl;
	cout << "s: Show the current setting" << endl;
	cout << "c: Change the setting" << endl;
	cout << "q: Quit the program" << endl;
	cout << "h: Show help message" << endl;
	cout << "m: main menu" << endl;
}

Enigma *change_settings(const char **rotors, size_t *rings, size_t *inits, const char *reflector, char *pairs)
{
	size_t rotors_size = 3;
	size_t num_pairs = 0;

	cout << "Enter the number of rotors: ";
	cin >> rotors_size;
	cout << "Enter the Rotors (e.g., ROTOR_I): " << endl;
	for (size_t i = 0; i < rotors_size; i++) {
		cout << "Enter the Rotor " << i + 1 << ": ";
		string rotor;
		cin >> rotor;
		if(getMacro(rotor) == NULL) {
			i--;
		}
		else {
			rotors[i] = getMacro(rotor);
		}
	}
	cout << "Enter the Rings (1~26): " << endl;
	for (size_t i = 0; i < rotors_size; i++) {
		cout << "Enter the Ring " << i + 1 << ": ";
		cin >> rings[i];
	}
	cout << "Enter the Initials (1~26): " << endl;
	for (size_t i = 0; i < rotors_size; i++) {
		cout << "Enter the Initial " << i + 1 << ": ";
		cin >> inits[i];
	}
	cout << "Enter the Reflector (e.g., UKW_A): ";
	string reflector_input;
	cin >> reflector_input;
	if(getMacro(reflector_input) == NULL) {
		return NULL;
	}
	else {
		reflector = getMacro(reflector_input);
	}

	cout << "Enter the number of PlugBoard pairs (e.g., AGCF = A<->G, C<->F): ";
	string pair_string = "";
	cin >> pair_string;
	if (pair_string == "null") {
		pairs = NULL;
	}
	else {
		pair_string = to_uppercase(pair_string);
		strcpy(pairs, pair_string.c_str());
		num_pairs = strlen(pairs) / 2;
	}

	return new_Enigma(rotors_size, rotors, rings, inits, reflector, num_pairs, pairs);
}

Enigma *get_Enigma(const char **rotors, size_t rotors_size, size_t *rings, size_t *inits, const char *reflector, char *pairs)
{
	size_t num_pairs = 0;
	if (pairs != NULL){ 
		num_pairs = strlen(pairs) / 2;
	}
	return new_Enigma(rotors_size, rotors, rings, inits, reflector, num_pairs, pairs);
}

int main()
{
	const char *rotors[] = {ROTOR_III, ROTOR_II, ROTOR_I};
	size_t rings[] = {0, 0, 0};
	size_t inits[] = {1, 1, 1};
	const char *reflector = I_UKW_B;
	char *pairs = NULL;
	string input = "m";
	size_t rotors_size = sizeof(rotors) / sizeof(rotors[0]);
	Enigma *enigma = get_Enigma(rotors, rotors_size, rings, inits, reflector, pairs);

	while(input != "q") {
		if(input == "c") {
			clear_terminal();
			free_Enigma(enigma);
			enigma = change_settings(rotors, rings, inits, reflector, pairs);
			clear_terminal();
		}
		else if(input == "e") {
			clear_terminal();
			reset_rotor_Enigma(enigma, inits);
			cout << "Enter the message: ";
			string message;
			cin.ignore();
			getline(cin, message);
			message = to_uppercase(message);
			char *message_input = new char[message.length() + 1];
			strcpy(message_input, message.c_str());
			char *dst = new char[message.length() + 1];
			cout << "Message: " << message_input << endl;
			encrypt_Enigma(enigma, dst, message_input);
			cout << "Encrypted message: " << dst << endl;
		}
		else if(input == "s") {
			clear_terminal();
			print_setting(enigma, rotors, rotors_size);
		}
		else if(input == "h") {
			clear_terminal();
			help();
		}
		else if(input == "m") {
			clear_terminal();
			print_main();
		}
		else {
			cout << "Invalid input" << endl;
		}

		cout << "user>> :";
		cin >> input;
	}
	free_Enigma(enigma);
	return 0;
}
