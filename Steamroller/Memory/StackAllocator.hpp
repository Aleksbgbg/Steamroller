#pragma once

#include "../ApiDeclaration.hpp"
#include "AlignedAllocation.hpp"
#include "MemoryUtilities.hpp"

namespace sr
{
class EXPORT_API_NO_IMPORT StackAllocator
{
public:
	typedef Size Marker;

public:
	StackAllocator();
	explicit StackAllocator(const Size size);

	StackAllocator(const StackAllocator& source);
	StackAllocator(StackAllocator&& source) noexcept;

	~StackAllocator();

public:
	StackAllocator& operator=(const StackAllocator& source);
	StackAllocator& operator=(StackAllocator&& source) noexcept;

public:
	Marker GetMarker() const;

	void* Allocate(const Size size, const uint8 alignment = MemoryUtilities::DefaultAlignment) const;

	template<typename T, typename... TArgs>
	T* Create(TArgs... arguments) const;

	template<typename T>
	T* CreateArray(const Size length);

	void Deallocate(const Marker marker) const;
	void Clear() const;

private:
	Size size;
	void* memory;
	uintptr_t memoryAddress;
	Marker* currentAllocation;
	uint32* copies;

private:
	static constexpr Size MemoryGap = sizeof(*currentAllocation) + sizeof(*copies);
};

template<typename T, typename ... TArgs>
T* StackAllocator::Create(TArgs... arguments) const
{
	void* memory = Allocate(sizeof(T), alignof(T));
	return new (memory) T(arguments...);
}

template<typename T>
T* StackAllocator::CreateArray(const Size length)
{
	// new T[] not used as it allocates a random block before the array

	void* memory = Allocate(sizeof(T) * length, alignof(T));
	uint8* bytePointer = reinterpret_cast<uint8*>(memory);

	for (Size index = 0; index < length; ++index)
	{
		new (bytePointer + (index * sizeof(T))) T();
	}

	return reinterpret_cast<T*>(memory);
}
}