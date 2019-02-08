#include "CppUnitTest.h"

#include "../Steamroller/Math/Matrix.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SteamrollerTests
{
TEST_CLASS(MatrixTests)
{
public:
	TEST_METHOD(TestCreateBySize)
	{
		constexpr sr::int32 width = 2;
		constexpr sr::int32 height = 4;

		const sr::Matrix matrix{ width, height };

		Assert::AreEqual(matrix.Width(), width);
		Assert::AreEqual(matrix.Height(), height);
	}

	TEST_METHOD(TestCreateFromCollection)
	{
		constexpr sr::int32 width = 4;
		constexpr sr::int32 height = 2;

		const sr::int32 collection[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		const sr::Matrix matrix{ width, height, collection };

		Assert::AreEqual(matrix(0, 0), 0);
		Assert::AreEqual(matrix(0, 1), 1);
		Assert::AreEqual(matrix(0, 2), 2);
		Assert::AreEqual(matrix(0, 3), 3);
		Assert::AreEqual(matrix(1, 0), 4);
		Assert::AreEqual(matrix(1, 1), 5);
		Assert::AreEqual(matrix(1, 2), 6);
		Assert::AreEqual(matrix(1, 3), 7);
	}

	TEST_METHOD(TestMultiply0)
	{
		const sr::int32 matrix0Contents[] = { 3, 4, 2 };
		const sr::Matrix matrix0{ 3, 1, matrix0Contents };

		const sr::int32 matrix1Contents[] = { 13, 9, 7, 15, 8, 7, 4, 6, 6, 4, 0, 3 };
		const sr::Matrix matrix1{ 4, 3, matrix1Contents };

		const sr::Matrix multiplicationResult = matrix0 * matrix1;

		Assert::AreEqual(multiplicationResult(0, 0), 83);
		Assert::AreEqual(multiplicationResult(0, 1), 63);
		Assert::AreEqual(multiplicationResult(0, 2), 37);
		Assert::AreEqual(multiplicationResult(0, 3), 75);
	}

	TEST_METHOD(TestMultiply1)
	{
		const sr::int32 matrix0Contents[] = { 1, 2, 3, 4, 5, 6 };
		const sr::Matrix matrix0{ 3, 2, matrix0Contents };

		const sr::int32 matrix1Contents[] = { 7, 8, 9, 10, 11, 12 };
		const sr::Matrix matrix1{ 2, 3, matrix1Contents };

		const sr::Matrix multiplicationResult = matrix0 * matrix1;

		Assert::AreEqual(multiplicationResult(0, 0), 58);
		Assert::AreEqual(multiplicationResult(0, 1), 64);
		Assert::AreEqual(multiplicationResult(1, 0), 139);
		Assert::AreEqual(multiplicationResult(1, 1), 154);
	}
};
}