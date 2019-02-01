#pragma once

#include <vector>

namespace sr
{
class Matrix
{
public:
	Matrix(const int width, const int height);
	template<typename TIterator>
	Matrix(const int width, const int height, TIterator begin, TIterator end)
		:
		width{ width },
		height{ height }
	{
		contents.resize(width * height);
		std::copy(begin, end, contents.begin());
	}

public:
	int Width() const;
	int Height() const;

private:
	int width;
	int height;

	std::vector<int> contents;
};
}