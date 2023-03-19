#pragma once
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/NetImmerse/NiMain/NiExtraData.h"

namespace RE
{
	class BSBoneMap : public NiExtraData
	{
	public:
		static constexpr auto RTTI{ RTTI::BSBoneMap };
		static constexpr auto VTABLE{ VTABLE::BSBoneMap };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSBoneMap };

		//members
		BSTHashMap<BSFixedString, NiAVObject*> mBoneNames;
	};

}
