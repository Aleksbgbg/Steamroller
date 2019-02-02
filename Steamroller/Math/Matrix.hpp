#pragma once

#include <algorithm>
#include <vector>

namespace sr
{
class Matrix
{
public:
	Matrix(const int width, const int height);
	template<typename TCollection>
	Matrix(const int width, const int height, const TCollection& collection)
		:
		width{ width },
		height{ height }
	{
		contents.resize(width * height);
		std::copy(std::begin(collection), std::end(collection), contents.begin());
	}

public:
	int operator()(const int row, const int column) const;
	int& operator()(const int row, const int column);

	Matrix operator*(const Matrix& other) const;

public:
	int Width() const;
	int Height() const;

private:
	inline int FindIndex(const int row, const int column) const;

private:
	int width;
	int height;

	std::vector<int> contents;
};
}