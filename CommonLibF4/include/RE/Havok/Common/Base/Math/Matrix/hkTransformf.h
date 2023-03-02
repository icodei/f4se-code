#pragma once
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"
#include "RE/Havok/Common/Base/Math/Matrix/hkRotationf.h"

namespace RE
{
	class hkTransformf
	{
	public:
		//members
		hkRotationf m_rotation;
		hkVector4f m_translation;
	};
}
