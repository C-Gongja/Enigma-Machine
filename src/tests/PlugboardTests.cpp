extern "C"
{
#include "Plugboard.h"
#include "common.h"
}
#include <gtest/gtest.h>

namespace
{
	TEST(PlugboardTests, TestNewPlugboard0)
	{
		Plugboard *plugboard = new_Plugboard(2, "ABCD");
		ASSERT_NE(plugboard, nullptr);

		// Expected output: "BACD...Z" with remaining letters in default positions
		char expected[LETTER_SIZE + 1] = "BADCEFGHIJKLMNOPQRSTUVWXYZ";
		expected[LETTER_SIZE] = '\0';

		char output[LETTER_SIZE + 1] = {0};
		for (int i = 0; i < LETTER_SIZE; ++i)
		{
			output[i] = plugboard->encrypted[i];
		}
		output[LETTER_SIZE] = '\0';

		ASSERT_STREQ(output, expected);
		char input = 'B';
		char output1 = plugboard_encrypt(plugboard, input);
		ASSERT_EQ(output1, 'A');

		free_Plugboard(plugboard);
	}

	TEST(PlugboardTests, TestNewPlugboard1)
	{
		Plugboard *plugboard = new_Plugboard(3, "AECFGH");
		// Expected output: "BACD...Z" with remaining letters in default positions
		char expected[LETTER_SIZE + 1] = "EBFDACHGIJKLMNOPQRSTUVWXYZ";
		expected[LETTER_SIZE] = '\0';

		char output[LETTER_SIZE + 1] = {0};
		for (int i = 0; i < LETTER_SIZE; ++i)
		{
			output[i] = plugboard->encrypted[i];
		}
		output[LETTER_SIZE] = '\0';

		ASSERT_STREQ(output, expected);
		char input = 'F';
		char output1 = plugboard_encrypt(plugboard, input);
		ASSERT_EQ(output1, 'C');

		free_Plugboard(plugboard);
	}

	TEST(PlugboardTests, TestNewPlugboard3)
	{
		Plugboard *plugboard = new_Plugboard(10, "bqcrdiejkwmtospxuzgh");
		// Expected output: "BACD...Z" with remaining letters in default positions
		char expected[LETTER_SIZE + 1] = "AQRIJFHGDEWLTNSXBCOMZVKPYU";
		expected[LETTER_SIZE] = '\0';

		char output[LETTER_SIZE + 1] = {0};
		for (int i = 0; i < LETTER_SIZE; ++i)
		{
			output[i] = plugboard->encrypted[i];
		}
		output[LETTER_SIZE] = '\0';

		ASSERT_STREQ(output, expected);
		char input = 'B';
		char output1 = plugboard_encrypt(plugboard, input);
		ASSERT_EQ(output1, 'Q');

		free_Plugboard(plugboard);
	}
}