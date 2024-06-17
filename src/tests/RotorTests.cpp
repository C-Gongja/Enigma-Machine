extern "C"
{
#include "Rotor.h"
#include "common.h"
}
#include <gtest/gtest.h>

namespace
{
	TEST(RotorTests, TestRotor_ROTOR_I_ENIGMA_I_0)
	{
		const char *rotors[] = {ROTOR_I, ROTOR_II, ROTOR_III};
		size_t size = (size_t)3;
		size_t ring[] = {0, 0, 0};
		size_t init[] = {0, 0, 0};
		Rotor *rotor = new_Rotor(size);
		set_Rotor(rotor, rotors, size, ring, init);
		ASSERT_STREQ(rotor->each_rotor[0], "EKMFLGDQVZNTOWYHXUSPAIBRCJ");
		ASSERT_STREQ(rotor->notch[0], "Q");
		ASSERT_STREQ(rotor->each_rotor[1], "AJDKSIRUXBLHWTMCQGZNPYFVOE");
		ASSERT_STREQ(rotor->notch[1], "E");
		ASSERT_STREQ(rotor->each_rotor[2], "BDFHJLCPRTXVZNYEIWGAKMUSQO");
		ASSERT_STREQ(rotor->notch[2], "V");

		free_Rotor(rotor);
	}

	// test ring
	TEST(RotorTests, TestRotor_ROTOR_I_ENIGMA_I_1)
	{
		const char *rotors[] = {ROTOR_I, ROTOR_II, ROTOR_III};
		size_t size = (size_t)3;
		size_t ring[] = {3, 3, 4};
		size_t init[] = {0, 0, 0};
		Rotor *rotor = new_Rotor(size);
		set_Rotor(rotor, rotors, size, ring, init);
		ASSERT_NE(rotor, nullptr);
		ASSERT_STREQ(rotor->each_rotor[0], "UFMHNPIOJGTYCQWRZBKAXVSDLE");
		ASSERT_STREQ(rotor->notch[0], "Q");
		ASSERT_STREQ(rotor->each_rotor[1], "YRHDMGNVLUXAEOKZWPFTJCQSBI");
		ASSERT_STREQ(rotor->notch[1], "E");
		ASSERT_STREQ(rotor->each_rotor[2], "YWUSFHJLNPGTVXBZDRCIMAKEOQ");
		ASSERT_STREQ(rotor->notch[2], "V");

		free_Rotor(rotor);
	}

	// test init
	TEST(RotorTests, TestRotor_ROTOR_I_ENIGMA_I_2)
	{
		const char *rotors[] = {ROTOR_I, ROTOR_II, ROTOR_III};
		size_t size = (size_t)3;
		size_t ring[] = {0, 0, 0};
		size_t init[] = {1, 2, 3};
		Rotor *rotor = new_Rotor(size);
		set_Rotor(rotor, rotors, size, ring, init);
		ASSERT_NE(rotor, nullptr);
		ASSERT_STREQ(rotor->each_rotor[0], "KMFLGDQVZNTOWYHXUSPAIBRCJE");
		ASSERT_STREQ(rotor->notch[0], "P");
		ASSERT_STREQ(rotor->each_rotor[1], "DKSIRUXBLHWTMCQGZNPYFVOEAJ");
		ASSERT_STREQ(rotor->notch[1], "C");
		ASSERT_STREQ(rotor->each_rotor[2], "HJLCPRTXVZNYEIWGAKMUSQOBDF");
		ASSERT_STREQ(rotor->notch[2], "S");

		free_Rotor(rotor);
	}

	// test reset
	TEST(RotorTests, TestRotor_ROTOR_I_ENIGMA_I_3)
	{
		const char *rotors[] = {ROTOR_I, ROTOR_II, ROTOR_III};
		size_t size = (size_t)3;
		size_t ring[] = {0, 0, 0};
		size_t init[] = {1, 2, 3};
		Rotor *rotor = new_Rotor(size);
		set_Rotor(rotor, rotors, size, ring, init);
		ASSERT_NE(rotor, nullptr);
		ASSERT_STREQ(rotor->each_rotor[0], "KMFLGDQVZNTOWYHXUSPAIBRCJE");
		ASSERT_STREQ(rotor->notch[0], "P");
		ASSERT_STREQ(rotor->each_rotor[1], "DKSIRUXBLHWTMCQGZNPYFVOEAJ");
		ASSERT_STREQ(rotor->notch[1], "C");
		ASSERT_STREQ(rotor->each_rotor[2], "HJLCPRTXVZNYEIWGAKMUSQOBDF");
		ASSERT_STREQ(rotor->notch[2], "S");
		size_t new_setting[] = {0, 0, 0};
		reset_Rotor(rotor, new_setting);
		ASSERT_STREQ(rotor->each_rotor[0], "EKMFLGDQVZNTOWYHXUSPAIBRCJ");
		ASSERT_STREQ(rotor->notch[0], "Q");
		ASSERT_STREQ(rotor->each_rotor[1], "AJDKSIRUXBLHWTMCQGZNPYFVOE");
		ASSERT_STREQ(rotor->notch[1], "E");
		ASSERT_STREQ(rotor->each_rotor[2], "BDFHJLCPRTXVZNYEIWGAKMUSQO");
		ASSERT_STREQ(rotor->notch[2], "V");

		free_Rotor(rotor);
	}
}