#pragma once
#include "RE/Havok/Common/Base/Types/Physics/hkRefPtr.h"
#include "RE/Havok/Common/Base/Object/hkReferencedObject.h"
#include "RE/NetImmerse/NiMain/NiObject.h"

namespace RE
{
	class bhkCharacterProxy : public NiObject
	{
	public:
		static constexpr auto RTTI{ RTTI::bhkCharacterProxy };
		static constexpr auto VTABLE{ VTABLE::bhkCharacterProxy };
		static constexpr auto Ni_RTTI{ Ni_RTTI::bhkCharacterProxy };

		//members
		hkRefPtr<hkReferencedObject> spProxyNP;
		//bhkCharacterPointCollector m_ignoredCollisionStartCollector;
	};
}
