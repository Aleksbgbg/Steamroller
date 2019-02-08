#include "CppUnitTest.h"

#include "../../Steamroller/Memory/AlignedAllocation.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SteamrollerTests
{
TEST_CLASS(AlignedAllocationTests)
{
public:
	TEST_METHOD(TestAlign16B)
	{
		const sr::MemoryAlignment alignment = sr::Align(50, 16);

		Assert::AreEqual(alignment.alignedAddress, static_cast<uintptr_t>(64));
	}

	TEST_METHOD(TestAlign2B)
	{
		const sr::MemoryAlignment alignment = sr::Align(50, 2);

		Assert::AreEqual(alignment.alignedAddress, static_cast<uintptr_t>(50));
	}

public:
	TEST_METHOD(TestAlignInsertVoid16B)
	{
		const sr::MemoryAlignment alignment = sr::AlignInsertVoid(50, 16);

		Assert::AreEqual(alignment.alignedAddress, static_cast<uintptr_t>(64));
	}

	TEST_METHOD(TestAlignInsertVoid2B)
	{
		const sr::MemoryAlignment alignment = sr::AlignInsertVoid(50, 2);

		Assert::AreEqual(alignment.alignedAddress, static_cast<uintptr_t>(52));
	}
};
}