#pragma once
#include "RE/NetImmerse/NiMain/NiFlags.h"
#include "RE/NetImmerse/NiMain/NiNode.h"
#include "RE/NetImmerse/NiMain/NiTArray.h"

namespace RE
{
	class NiSwitchNode : public NiNode
	{
	public:
		static constexpr auto RTTI{ RTTI::NiSwitchNode };
		static constexpr auto VTABLE{ VTABLE::NiSwitchNode };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiSwitchNode };

		//add

		//members
		NiTFlags<std::uint16_t, NiSwitchNode> m_uFlags;
		std::int32_t m_iIndex;
		float m_fSavedTime;
		std::uint32_t m_uiRevID;
		NiTPrimitiveArray<std::uint32_t> m_kChildRevID;
	};
}
