#include "Matrix.hpp"

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