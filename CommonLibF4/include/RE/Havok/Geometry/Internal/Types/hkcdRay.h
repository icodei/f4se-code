#pragma once
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"

namespace RE
{
	struct hkcdRay
	{
	public:
		//members
		hkVector4f m_origin;
		hkVector4f m_direction;
		hkVector4f m_invDirection;
	};

	struct hkcdRayQueryFlags
	{
	public:

		enum Enum
		{
			NO_FLAGS,
			DISABLE_BACK_FACING_TRIANGLE_HITS,
			DISABLE_FRONT_FACING_TRIANGLE_HITS,
			ENABLE_INSIDE_HITS,
			ENABLE_EXTRA_TRIANGLE_BEVELPLANES
		};
	};
}
