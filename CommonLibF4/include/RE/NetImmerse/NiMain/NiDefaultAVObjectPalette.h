#pragma once
#include "RE/NetImmerse/NiMain/NiAVObjectPalette.h"
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"

namespace RE
{
	class NiAVObject;

	class NiDefaultAVObjectPalette : public NiObject
	{
	public:
		static constexpr auto RTTI{ RTTI::NiDefaultAVObjectPalette };
		static constexpr auto VTABLE{ VTABLE::NiDefaultAVObjectPalette };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiDefaultAVObjectPalette };

		//members
		BSTHashMap<BSFixedString, NiAVObject*> m_kHash;
		NiAVObject* m_pkScene;
	};

}
