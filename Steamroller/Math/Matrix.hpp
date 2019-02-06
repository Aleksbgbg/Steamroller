#pragma once

#include <algorithm>
#include <vector>

#include "../Types.hpp"

namespace sr
{
class Matrix
{
public:
	Matrix(const int32 width, const int32 height);
	template<typename TCollection>
	Matrix(const int32 width, const int32 height, const TCollection& collection)
		:
		width{ width },
		height{ height }
	{
		contents.resize(width * height);
		std::copy(std::begin(collection), std::end(collection), contents.begin());
	}

public:
	int32 operator()(const int32 row, const int32 column) const;
	int32& operator()(const int32 row, const int32 column);

	Matrix operator*(const Matrix& other) const;

public:
	int32 Width() const;
	int32 Height() const;

private:
	inline int32 FindIndex(const int32 row, const int32 column) const;

private:
	int32 width;
	int32 height;

	std::vector<int32> contents;
};
}