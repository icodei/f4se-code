#pragma once
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/Bethesda/BSShader/BSLeafAnimNode.h"

namespace RE
{
	class NiAVObject;

	class BSTreeNode : public BSLeafAnimNode
	{
		static constexpr auto RTTI{ RTTI::BSTreeNode };
		static constexpr auto VTABLE{ VTABLE::BSTreeNode };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSTreeNode };

		//members
		float fDistanceBetweenLODTrees;
		std::uint32_t uiBranchAnimationRangeStart;
		std::uint32_t uiNumBranchesToAnimate;
		BSTArray<NiAVObject*> kTrunkBones;
		BSTArray<NiAVObject*> kBranchBones;
	};

}
