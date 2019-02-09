#include "StackAllocator.hpp"

#include <cstdlib>
#include <stdexcept>

namespace sr
{
StackAllocator::StackAllocator()
	:
	size{ 0 },
	memory{ nullptr },
	memoryAddress{ 0 },
	currentAllocation{ nullptr },
	copies{ nullptr }
{
}

StackAllocator::StackAllocator(const Size size)
	:
	size{ size },
	memory{ malloc(size + MemoryGap) },
	memoryAddress{ reinterpret_cast<uintptr_t>(memory) },
	currentAllocation{ reinterpret_cast<Size*>(memory) },
	copies{ reinterpret_cast<uint32*>(reinterpret_cast<Size*>(memory) + 1) }
{
	*currentAllocation = 0;
}

StackAllocator::StackAllocator(const StackAllocator& source)
	:
	size{ source.size },
	memory{ source.memory },
	memoryAddress{ source.memoryAddress },
	currentAllocation{ source.currentAllocation },
	copies{ source.copies }
{
	++(*copies);
}

StackAllocator::StackAllocator(StackAllocator&& source) noexcept
	:
	size{ source.size },
	memory{ source.memory },
	memoryAddress{ source.memoryAddress },
	currentAllocation{ source.currentAllocation },
	copies{ source.copies }
{
	source.size = 0;
	source.memory = nullptr;
	source.memoryAddress = 0;
	source.currentAllocation = nullptr;
	source.copies = nullptr;
}

StackAllocator::~StackAllocator()
{
	--(*copies);

	if (*copies == 0)
	{
		free(memory);	
	}
}

StackAllocator& StackAllocator::operator=(const StackAllocator& source)
{
	if (this != &source)
	{
		size = source.size;
		memory = source.memory;
		memoryAddress = source.memoryAddress;
		currentAllocation = source.currentAllocation;
		copies = source.copies;

		++(*copies);
	}

	return *this;
}

StackAllocator& StackAllocator::operator=(StackAllocator&& source) noexcept
{
	if (this != &source)
	{
		size = source.size;
		memory = source.memory;
		memoryAddress = source.memoryAddress;
		currentAllocation = source.currentAllocation;
		copies = source.copies;

		source.size = 0;
		source.memory = nullptr;
		source.memoryAddress = 0;
		source.currentAllocation = nullptr;
		source.copies = nullptr;
	}

	return *this;
}

StackAllocator::Marker StackAllocator::GetMarker() const
{
	return *currentAllocation;
}

void* StackAllocator::Allocate(const Size size, const uint8 alignment) const
{
	const uintptr_t currentStackTop = memoryAddress + MemoryGap + *currentAllocation;

	const MemoryAlignment memoryAlignment = Align(currentStackTop, alignment);

	*currentAllocation += memoryAlignment.allocationAdjustment + size;

	if ((*currentAllocation) > this->size)
	{
		throw std::overflow_error{ "StackAllocator capacity surpassed" };
	}

	return reinterpret_cast<void*>(memoryAlignment.alignedAddress);
}

void StackAllocator::Deallocate(const Marker marker) const
{
	*currentAllocation = marker;
}

void StackAllocator::Clear() const
{
	*currentAllocation = 0;
}
}