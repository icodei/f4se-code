#pragma once
#include "RE/Havok/hknpMaterialId.h"
#include "RE/Havok/Common/Base/Types/hkBaseTypes.h"

namespace RE
{
	struct hknpQueryFilterData
	{
	public:
		//members
		hknpMaterialId materialId;
		hkPadSpu<std::uint32_t> collisionFilterInfo;
		hkPadSpu<std::uint64_t> userData;
	};
}
