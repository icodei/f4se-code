#pragma once
#include "RE/Havok/Common/Base/Math/Vector/hkVector4f.h"

namespace RE
{
	class hkContactPoint
	{
	public:
		//members
		hkVector4f m_position;
		hkVector4f m_separatingNormal;
	};
}
