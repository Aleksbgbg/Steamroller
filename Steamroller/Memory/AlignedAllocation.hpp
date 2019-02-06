#pragma once

#include "../Types.hpp"

namespace sr
{
void* AllocateAligned(const uint32 size, const uint32 alignment);

void FreeAligned(const void* const alignedMemory);
}