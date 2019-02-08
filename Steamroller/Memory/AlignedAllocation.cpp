#include "AlignedAllocation.hpp"

#include <cassert>
#include <cstdlib>

namespace sr
{
void* AllocateAligned(const uint32 size, const uint8 alignment)
{
	assert(0 < alignment);
	assert(alignment <= 128);

	// Alignment must be a power of two (only one bit is set)
	assert((alignment & (alignment - 1)) == 0);

	void* const allocation = malloc(size + alignment);

	const uintptr_t allocationAddress = reinterpret_cast<uintptr_t>(allocation);

	const MemoryAlignment memoryAlignment = AlignInsertVoid(allocationAddress, alignment);

	assert(memoryAlignment.allocationAdjustment < 256);
	// Store alignment in the byte immediately below adjusted address so we can free aligned memory correctly
	reinterpret_cast<uint8*>(memoryAlignment.alignedAddress)[-1] = static_cast<uint8>(memoryAlignment.allocationAdjustment);

	return reinterpret_cast<void*>(memoryAlignment.alignedAddress);
}

void FreeAligned(const void* const alignedMemory)
{
	const uintptr_t alignedAllocationAddress = reinterpret_cast<uintptr_t>(alignedMemory);
	const uint8 allocationAdjustment = reinterpret_cast<const uint8*>(alignedMemory)[-1];
	const uintptr_t initialAllocationAddress = alignedAllocationAddress - allocationAdjustment;

	void* const initialMemory = reinterpret_cast<void*>(initialAllocationAddress);

	free(initialMemory);
}

MemoryAlignment Align(const uintptr_t address, const uint8 alignment)
{
	const uint8 byteWrap = alignment - 1;

	const uintptr_t misalignment = address & byteWrap;

	// & byteWrap ensures that if address is already aligned,
	// the adjustment is zero
	const ptrdiff_t allocationAdjustment = (alignment - misalignment) & byteWrap;

	const uintptr_t alignedAllocationAddress = address + allocationAdjustment;

	return MemoryAlignment{ alignedAllocationAddress, allocationAdjustment };
}

// If memory is already aligned, leave <alignment> empty space at the start of address
// for extra storage
MemoryAlignment AlignInsertVoid(const uintptr_t address, const uint8 alignment)
{
	const uintptr_t misalignment = address & (alignment - 1);

	// Allocation adjustments will be <alignment> if address already aligned
	const ptrdiff_t addressAdjustment = alignment - misalignment;

	const uintptr_t allocationAdjustment = address + addressAdjustment;

	return MemoryAlignment{ allocationAdjustment, addressAdjustment };
}
}