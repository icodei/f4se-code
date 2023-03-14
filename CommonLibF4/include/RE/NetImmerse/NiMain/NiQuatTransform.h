#pragma once
#include "RE/NetImmerse/NiMain/NiPoint3.h"
#include "RE/NetImmerse/NiMain/NiQuaternion.h"

namespace RE
{
	class NiQuatTransform
	{
	public:
		//members
		NiPoint3 m_kTranslate;
		NiQuaternion m_kRotate;
		float m_fScale;
	};

}
