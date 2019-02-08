#include "CppUnitTest.h"

#include "../../Steamroller/Memory/StackAllocator.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SteamrollerTests
{
TEST_CLASS(AlignedAllocationTests)
{
public:
	TEST_METHOD(TestAllocatesCorrectly)
	{
		const sr::StackAllocator stackAllocator{ 4 };

		const sr::int32* const someInteger = stackAllocator.Create<sr::int32>(50);

		Assert::AreEqual(*someInteger, 50);
	}

	TEST_METHOD(TestCopiesCorrectly)
	{
		const sr::StackAllocator stackAllocator0{ 64 };
		const sr::StackAllocator stackAllocator1{ stackAllocator0 };
		const sr::StackAllocator stackAllocator2{ stackAllocator1 };

		const sr::int32* const someInteger = stackAllocator0.Create<sr::int32>(100);

		Assert::AreEqual(stackAllocator0.GetMarker(), stackAllocator1.GetMarker());
		Assert::AreEqual(stackAllocator1.GetMarker(), stackAllocator2.GetMarker());
	}

	TEST_METHOD(TestThrowsOnOverflow)
	{
		const sr::StackAllocator stackAllocator{ 4 };

		Assert::ExpectException<std::overflow_error>([&stackAllocator]()
		{
			stackAllocator.Create<sr::int64>(50);
		});
	}
};
}