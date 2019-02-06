#include "Matrix.hpp"

#include <cassert>

namespace sr
{
Matrix::Matrix(const int32 width, const int32 height)
	:
	width{ width },
	height{ height }
{
	contents.resize(width * height);
}

int32 Matrix::operator()(const int32 row, const int32 column) const
{
	return contents[FindIndex(row, column)];
}

int32& Matrix::operator()(const int32 row, const int32 column)
{
	return contents[FindIndex(row, column)];
}

Matrix Matrix::operator*(const Matrix& other) const
{
	assert(width == other.height);

	Matrix resultant{ other.width, height };
	
	for (int32 row = 0; row < resultant.height; ++row)
	{
		for (int32 column = 0; column < resultant.width; ++column)
		{
			int32 value = 0;

			for (int32 index = 0; index < width; ++index)
			{
				value += this->operator()(row, index) * other(index, column);
			}

			resultant(row, column) = value;
		}
	}

	return resultant;
}

int32 Matrix::Width() const
{
	return width;
}

int32 Matrix::Height() const
{
	return height;
}

int32 Matrix::FindIndex(const int32 row, const int32 column) const
{
	return ((row * width) + column);
}
}