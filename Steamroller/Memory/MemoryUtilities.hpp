#pragma once

#include "../ApiDeclaration.hpp"
#include "AlignedAllocation.hpp"

namespace sr
{
class EXPORT_API_NO_IMPORT MemoryUtilities final
{
public:
	static constexpr uint8 DefaultAlignment = 16u;
};
}