#include "Matrix.hpp"

#include <cassert>

namespace sr
{
Matrix::Matrix(const int width, const int height)
	:
	width{ width },
	height{ height }
{
	contents.resize(width * height);
}

int Matrix::operator()(const int row, const int column) const
{
	return contents[FindIndex(row, column)];
}

int& Matrix::operator()(const int row, const int column)
{
	return contents[FindIndex(row, column)];
}

Matrix Matrix::operator*(const Matrix& other) const
{
	assert(width == other.height);

	Matrix resultant{ other.width, height };
	
	for (int row = 0; row < resultant.height; ++row)
	{
		for (int column = 0; column < resultant.width; ++column)
		{
			int value = 0;

			for (int index = 0; index < width; ++index)
			{
				value += this->operator()(row, index) * other(index, column);
			}

			resultant(row, column) = value;
		}
	}

	return resultant;
}

int Matrix::Width() const
{
	return width;
}

int Matrix::Height() const
{
	return height;
}

int Matrix::FindIndex(const int row, const int column) const
{
	return ((row * width) + column);
}
}