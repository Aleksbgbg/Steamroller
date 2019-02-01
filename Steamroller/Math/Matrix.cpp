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

int Matrix::Width() const
{
	return width;
}

int Matrix::Height() const
{
	return height;
}
}