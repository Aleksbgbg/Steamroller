#include "AlignedAllocation.hpp"

#include <cassert>
#include <cstdlib>

namespace sr
{
void* AllocateAligned(const uint32 size, const uint32 alignment)
{
	assert(0 < alignment);
	assert(alignment <= 128);

	// Alignment must be a power of two (only one bit is set)
	assert((alignment & (alignment - 1)) == 0);

	void* const allocation = malloc(size + alignment);

	const uintptr_t allocationAddress = reinterpret_cast<uintptr_t>(allocation);

	const uintptr_t misalignment = allocationAddress & (alignment - 1);
	const ptrdiff_t allocationAdjustment = alignment - misalignment;

	const uintptr_t alignedAllocationAddress = allocationAddress + allocationAdjustment;

	// Store alignment in the byte immediately below adjusted address so we can free aligned memory correctly
	assert(allocationAdjustment < 256);
	reinterpret_cast<uint8*>(alignedAllocationAddress)[-1] = static_cast<uint8>(allocationAdjustment);

	return reinterpret_cast<void*>(alignedAllocationAddress);
}

void FreeAligned(const void* const alignedMemory)
{
	const uintptr_t alignedAllocationAddress = reinterpret_cast<uintptr_t>(alignedMemory);
	const uint8 allocationAdjustment = reinterpret_cast<const uint8*>(alignedMemory)[-1];
	const uintptr_t initialAllocationAddress = alignedAllocationAddress - allocationAdjustment;

	void* const initialMemory = reinterpret_cast<void*>(initialAllocationAddress);

	free(initialMemory);
}
}