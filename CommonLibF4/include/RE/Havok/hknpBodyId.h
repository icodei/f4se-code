#pragma once

#include "RE/Havok/Common/Base/Types/hkHandle.h"

namespace RE
{
	struct hknpBodyIdBaseDiscriminant;

	struct hknpBodyId :
		public hkHandle<std::uint32_t, 0x7FFF'FFFF, hknpBodyIdBaseDiscriminant>
	{
	public:
	};
	static_assert(sizeof(hknpBodyId) == 0x4);
}
