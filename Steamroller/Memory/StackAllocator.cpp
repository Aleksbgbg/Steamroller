#include "StackAllocator.hpp"

#include <cstdlib>
#include <stdexcept>

sr::StackAllocator::StackAllocator()
	:
	size{ 0 },
	memory{ nullptr },
	memoryAddress{ 0 },
	currentAllocation{ nullptr },
	copies{ nullptr }
{
}

sr::StackAllocator::StackAllocator(const Size size)
	:
	size{ size },
	memory{ malloc(size + MemoryGap) },
	memoryAddress{ reinterpret_cast<uintptr_t>(memory) },
	currentAllocation{ reinterpret_cast<Size*>(memory) },
	copies{ reinterpret_cast<uint32*>(reinterpret_cast<Size*>(memory) + 1) }
{
	*currentAllocation = 0;
}

sr::StackAllocator::StackAllocator(const StackAllocator& source)
	:
	size{ source.size },
	memory{ source.memory },
	memoryAddress{ source.memoryAddress },
	currentAllocation{ source.currentAllocation },
	copies{ source.copies }
{
	++(*copies);
}

sr::StackAllocator::StackAllocator(StackAllocator&& source) noexcept
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

sr::StackAllocator::~StackAllocator()
{
	--(*copies);

	if (*copies == 0)
	{
		free(memory);	
	}
}

sr::StackAllocator& sr::StackAllocator::operator=(const StackAllocator& source)
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

sr::StackAllocator& sr::StackAllocator::operator=(StackAllocator&& source) noexcept
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

sr::StackAllocator::Marker sr::StackAllocator::GetMarker() const
{
	return *currentAllocation;
}

void* sr::StackAllocator::Allocate(const Size size, const uint8 alignment) const
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

void sr::StackAllocator::Deallocate(const Marker marker) const
{
	*currentAllocation = marker;
}

void sr::StackAllocator::Clear() const
{
	*currentAllocation = 0;
}