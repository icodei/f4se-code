#pragma once
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/NetImmerse/NiMain/NiNode.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"
#include "RE/NetImmerse/NiMain/NiTransform.h"

namespace RE
{
	class BSFlattenedBoneTree : public NiNode
	{
	public:
		static constexpr auto RTTI{ RTTI::BSFlattenedBoneTree };
		static constexpr auto VTABLE{ VTABLE::BSFlattenedBoneTree };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSFlattenedBoneTree };

		struct FlattenedBone
		{
		public:
			NiTransform Local;
			NiTransform World;
			std::int16_t iParent;
			std::int16_t iFirstChild;
			std::uint16_t uiChildCount;
			std::int16_t iNextSibling;
			NiPointer<NiNode> spGBNode;
			BSFixedString Name;
			bool bDeferredAttach;
		};

		//members
		std::int32_t iBoneCount;
		std::int32_t iExpandedBoneCount;
		FlattenedBone* pBoneA;
		BSTHashMap<BSFixedString, std::int32_t> BoneMap;
	};

}
