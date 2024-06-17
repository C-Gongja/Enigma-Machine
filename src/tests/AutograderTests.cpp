extern "C"
{
#include "Enigma.h"
#include "common.h"
}
#include <gtest/gtest.h>

#define ECS153 "I REALLY LIKE ECS ONE FIVE THREE"
#define INTG_0 "ICH HEISE PETER ICH LERNE DEUTSCH ICH MAG ECS ONE FIVE THREE"
#define M4_1 "THE HOMEWORK IS FUN I REALLY LIKE IT AND WANT MORE"
// #define M4_1 "FKL EDVKZLXE XR HGK F CNFDOR MJWL QC TUK FZLA TQVQ"
#define Unknown "SNC BFXLB FBAKA QXY YUSIM ENCAUIV UWW AXV JUZ TCQ DSHH NLUDT"

/*
When does rotor move
0 : always, everytime press the key
1: when 0 hit the notch, or when 1 is in the notch
2: when 1 hit the notch, or when 2 is in the notch
last: when 2 hit the notch

Integral0
plugboard setting: numspairs: 3, pairs: PETRON
reflector setting: YRUHQSLDPXNGOKMIEBFZCWVJAT
rotor setting: num_rotors: 0, rotors: BDFHJLCPRTXVZNYEIWGAKMUSQO,V, rings: 6, inits: 20
num_rotors: 1, rotors: AJDKSIRUXBLHWTMCQGZNPYFVOE,E, rings: 6, inits: 3
num_rotors: 2, rotors: EKMFLGDQVZNTOWYHXUSPAIBRCJ,Q, rings: 6, inits: 16

Integral1
plugboard setting: numspairs: 3, pairs: PETRON
reflector setting: YRUHQSLDPXNGOKMIEBFZCWVJAT
rotor setting: num_rotors: 0, rotors: AJDKSIRUXBLHWTMCQGZNPYFVOE,E, rings: 14, inits: 17
num_rotors: 1, rotors: BDFHJLCPRTXVZNYEIWGAKMUSQO,V, rings: 15, inits: 18
num_rotors: 2, rotors: EKMFLGDQVZNTOWYHXUSPAIBRCJ,Q, rings: 16, inits: 19

M4_1
plugboard setting: numspairs: 8, pairs: GLOMHAVEZKBTXQSU
reflector setting: ENKQAUYWJICOPBLMDXZVFTHRGS
rotor setting: num_rotors: 0, rotors: JPGVOUMFYQBENHZRDKASXLICTW,MZ, rings: 3, inits: 16
num_rotors: 1, rotors: NZJHGRCXMYSWBOUFAIVLPEKQDT,MZ, rings: 3, inits: 24
num_rotors: 2, rotors: FKQHTLXOCBJSPDZRAMEWNIUYGV,MZ, rings: 5, inits: 12
num_rotors: 3, rotors: LEYJVCNIXWPBQMDRTAKZGFUHOS,, rings: 5, inits: 14

	Which is: "FKL EDVKZLXF VG VPC P QKEMCQ EPVP QU RWE INPV SCFR"
  "FKL EDVKZLXE XR HGK F CNFDOR MJWL QC TUK FZLA TQVQ"

Plugboard: K -> Z
Rotor: Z -> E : notch LY
Rotor: E -> R : notch NA
Rotor: R -> Z : notch AN
Rotor: Z -> O : notch (null)
Reflector: O -> L
Rotor: L -> N : notch (null)
Rotor: N -> P : notch AN
Rotor: P -> X : notch NA
Rotor: X -> F : notch LY
back Plugboard: F -> F


Unknown1
plugboard setting: numspairs: 8, pairs: GLOMHAVEZKBTXQSU
reflector setting: YRUHQSLDPXNGOKMIEBFZCWVJAT
rotor setting: num_rotors: 0, rotors: BDFHJLCPRTXVZNYEIWGAKMUSQO,V, rings: 23, inits: 20
num_rotors: 1, rotors: AJDKSIRUXBLHWTMCQGZNPYFVOE,E, rings: 22, inits: 3
num_rotors: 2, rotors: EKMFLGDQVZNTOWYHXUSPAIBRCJ,Q, rings: 21, inits: 16
num_rotors: 3, rotors: EKMFLGDQVZNTOWYHXUSPAIBRCJ,Q, rings: 11, inits: 7
num_rotors: 4, rotors: AJDKSIRUXBLHWTMCQGZNPYFVOE,E, rings: 12, inits: 3
num_rotors: 5, rotors: BDFHJLCPRTXVZNYEIWGAKMUSQO,V, rings: 13, inits: 1
 encrypt
	Which is: "PYL FPWTH HKGOP EQG IOGPL UUQZQXW ZLI YWM VGV LTF NKTV KLUDQ"
  "SNC BFXLB FBAKA QXY YUSIM ENCAUIV UWW AXV JUZ TCQ DSHH NLUDT"
Plugboard: P -> P

Unknown3
plugboard setting: numspairs: 0, pairs: (null)
reflector setting: ENKQAUYWJICOPBLMDXZVFTHRGS
rotor setting: num_rotors: 0, rotors: JPGVOUMFYQBENHZRDKASXLICTW,MZ, rings: 16, inits: 20
num_rotors: 1, rotors: NZJHGRCXMYSWBOUFAIVLPEKQDT,MZ, rings: 12, inits: 21
num_rotors: 2, rotors: FKQHTLXOCBJSPDZRAMEWNIUYGV,MZ, rings: 15, inits: 22
num_rotors: 3, rotors: LEYJVCNIXWPBQMDRTAKZGFUHOS,, rings: 11, inits: 23
  encrypt[0]
	Which is: 'F' (70, 0x46)
  '\0

Unknown4
plugboard setting: numspairs: 8, pairs: GLOMHAVEZKBTXQSU
reflector setting: RDOBJNTKVEHMLFCWZAXGYIPSUQ
rotor setting: num_rotors: 0, rotors: FSOKANUERHMBTIYCWLQPZXVGJD,DKGLAICT, rings: 2, inits: 20
num_rotors: 1, rotors: YRUHQSLDPXNGOKMIEBFZCWVJAT,ABCDEFGHIJKLMNOPQRSTUVWXYZ, rings: 22, inits: 3
num_rotors: 2, rotors: RDOBJNTKVEHMLFCWZAXGYIPSUQ,PETRONG, rings: 11, inits: 1
num_rotors: 3, rotors: NZJHGRCXMYSWBOUFAIVLPEKQDT,MZ, rings: 12, inits: 13
num_rotors: 4, rotors: JPGVOUMFYQBENHZRDKASXLICTW,MZ, rings: 5, inits: 21
num_rotors: 5, rotors: FKQHTLXOCBJSPDZRAMEWNIUYGV,MZ, rings: 8, inits: 8
*/

namespace
{
	/* Changes to this file will be ignored. */
	Enigma *get_EnigmaA()
	{
		const char *rotors[] = {ROTOR_III, ROTOR_II, ROTOR_I};
		size_t rings[] = {6, 6, 6};
		size_t inits[] = {20, 3, 16};
		return new_Enigma(3, rotors, rings, inits, I_UKW_B, 3, "PETRON");
	}

	Enigma *get_Enigma_Unknown1()
	{
		const char *rotors[] = {ROTOR_III, ROTOR_II, ROTOR_I, ROTOR_II, ROTOR_III};
		size_t rings[] = {23, 22, 21, 11, 12, 13};
		size_t inits[] = {20, 3, 16, 7, 3, 1};
		return new_Enigma(3, rotors, rings, inits, I_UKW_B, 8, "GLOMHAVEZKBTXQSU");
	}

	Enigma *get_Enigma_M4_1()
	{
		const char *rotors[] = {ROTOR_VI, ROTOR_VII, ROTOR_VIII, ROTOR_BETA};
		size_t rings[] = {3, 3, 5, 5};
		size_t inits[] = {16, 24, 12, 14};
		return new_Enigma(4, rotors, rings, inits, UKW_B, 8, "GLOMHAVEZKBTXQSU");
	}

	TEST(ExampleTests, test_IntegralTest_0)
	{
		Enigma *enigma = get_EnigmaA();
		char encrypt[64];
		memset(encrypt, 0, 64);
		encrypt_Enigma(enigma, encrypt, INTG_0);
		ASSERT_STREQ(encrypt, "LLP UHVWM BJOVZ YXF PGNOR PDAJUQY KZS XRH FJG NWV UENG QRGWT");
		size_t inits[] = {20, 3, 16};
		reset_rotor_Enigma(enigma, inits);
		char decrypt[64];
		memset(decrypt, 0, 64);
		encrypt_Enigma(enigma, decrypt, encrypt);
		EXPECT_STREQ(INTG_0, decrypt);
		free_Enigma(enigma);
	}

	TEST(ExampleTests, test_IntegralTest_M4_1)
	{
		Enigma *enigma = get_Enigma_M4_1();
		char encrypt[64];
		memset(encrypt, 0, 64);
		encrypt_Enigma(enigma, encrypt, M4_1);
		ASSERT_STREQ(encrypt, "FKL EDVKZLXE XR HGK F CNFDOR MJWL QC TUK FZLA TQVQ");
		size_t inits[] = {16, 24, 12, 14};
		reset_rotor_Enigma(enigma, inits);
		char decrypt[64];
		memset(decrypt, 0, 64);
		encrypt_Enigma(enigma, decrypt, encrypt);
		EXPECT_STREQ(M4_1, decrypt);
		free_Enigma(enigma);
	}

	TEST(ExampleTests, test_IntegralTest_Unknown)
	{
		Enigma *enigma = get_Enigma_Unknown1();
		char decrypt[64];
		memset(decrypt, 0, 64);
		encrypt_Enigma(enigma, decrypt, Unknown);
		size_t inits[] = {20, 3, 16, 7, 3, 1};
		reset_rotor_Enigma(enigma, inits);
		char encrypt[64];
		memset(encrypt, 0, 64);
		encrypt_Enigma(enigma, encrypt, decrypt);
		EXPECT_STREQ(Unknown, encrypt);
		free_Enigma(enigma);
	}

	TEST(ExampleTests, test_IntegralTest_Unknown3)
	{
		Enigma *enigma = get_Enigma_Unknown1();
		char decrypt[64];
		memset(decrypt, 0, 64);
		encrypt_Enigma(enigma, decrypt, NULL);
		EXPECT_EQ(decrypt[0], '\0');
	}
}