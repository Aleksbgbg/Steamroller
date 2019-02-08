#pragma once

#include "../ApiDeclaration.hpp"
#include "../Types.hpp"

namespace sr
{
struct MemoryAlignment
{
	uintptr_t alignedAddress;
	ptrdiff_t allocationAdjustment;
};

EXPORT_API void* AllocateAligned(const Size size, const uint8 alignment);

EXPORT_API void FreeAligned(const void* const alignedMemory);

MemoryAlignment Align(const uintptr_t address, const uint8 alignment);

// If memory is already aligned, leave <alignment> empty space at the start of address
// for extra storage
MemoryAlignment AlignInsertVoid(const uintptr_t address, const uint8 alignment);
}