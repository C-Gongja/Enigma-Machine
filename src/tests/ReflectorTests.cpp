extern "C"
{
#include "Reflector.h"
#include "common.h"
}
#include <gtest/gtest.h>

namespace
{
	TEST(ReflectorTests, TestReflectorI_UKW_A)
	{
		Reflector *reflector = new_Reflector(I_UKW_A);
		ASSERT_NE(reflector, nullptr);
		ASSERT_EQ(reflector_encrypt(reflector, 'A'), 'E');
		ASSERT_EQ(reflector_encrypt(reflector, 'B'), 'J');
		ASSERT_EQ(reflector_encrypt(reflector, 'C'), 'M');
		ASSERT_EQ(reflector_encrypt(reflector, 'D'), 'Z');
		free_Reflector(reflector);
	}
	TEST(ReflectorTests, TestReflectorI_UKW_B)
	{
		Reflector *reflector = new_Reflector(I_UKW_B);
		ASSERT_NE(reflector, nullptr);
		ASSERT_EQ(reflector_encrypt(reflector, 'A'), 'Y');
		ASSERT_EQ(reflector_encrypt(reflector, 'B'), 'R');
		ASSERT_EQ(reflector_encrypt(reflector, 'C'), 'U');
		ASSERT_EQ(reflector_encrypt(reflector, 'D'), 'H');
		free_Reflector(reflector);
	}
	TEST(ReflectorTests, TestReflectorI_UKW_C)
	{
		Reflector *reflector = new_Reflector(I_UKW_C);
		ASSERT_NE(reflector, nullptr);
		ASSERT_EQ(reflector_encrypt(reflector, 'A'), 'F');
		ASSERT_EQ(reflector_encrypt(reflector, 'B'), 'V');
		ASSERT_EQ(reflector_encrypt(reflector, 'C'), 'P');
		ASSERT_EQ(reflector_encrypt(reflector, 'D'), 'J');
		free_Reflector(reflector);
	}
}