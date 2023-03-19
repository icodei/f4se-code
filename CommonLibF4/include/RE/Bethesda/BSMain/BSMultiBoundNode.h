#pragma once
#include "RE/Bethesda/BSMain/BSCullingProcess.h"
#include "RE/Bethesda/BSMain/BSNiNode.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class BSMultiBound;

	class BSMultiBoundNode : public BSNiNode
	{
		static constexpr auto RTTI{ RTTI::BSMultiBoundNode };
		static constexpr auto VTABLE{ VTABLE::BSMultiBoundNode };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSMultiBoundNode };

		//members
		NiPointer<BSMultiBound> spMultiBound;
		BSCullingProcess::BSCPCullingType CullingMode;
		float fLastAccumTime;
	};
	static_assert(sizeof(BSMultiBoundNode) == 0x150);
}
