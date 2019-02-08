#pragma once

#include "../ApiDeclaration.hpp"
#include "AlignedAllocation.hpp"

namespace sr
{
class EXPORT_API_NO_IMPORT MemoryUtilities
{
public:
	static constexpr uint8 DefaultAlignment = 16u;
};
}