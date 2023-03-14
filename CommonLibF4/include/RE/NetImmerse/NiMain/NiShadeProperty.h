#pragma once

#include "RE/NetImmerse/NiMain/NiProperty.h"

namespace RE
{
	class __declspec(novtable) NiShadeProperty :
		public NiProperty  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::NiShadeProperty };
		static constexpr auto VTABLE{ VTABLE::NiShadeProperty };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiShadeProperty };
		static constexpr auto TYPE{ SHADE };

		// add
		virtual bool SetupGeometry([[maybe_unused]] BSGeometry* a_geometry) { return true; }  // 2A
	};
	static_assert(sizeof(NiShadeProperty) == 0x28);
}
