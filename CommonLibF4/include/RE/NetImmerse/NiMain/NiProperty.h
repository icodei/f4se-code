#pragma once

#include "RE/NetImmerse/NiObjectNET.h"

namespace RE
{
	class NiUpdateData;

	class __declspec(novtable) NiProperty :
		public NiObjectNET  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::NiProperty };
		static constexpr auto VTABLE{ VTABLE::NiProperty };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiProperty };

		enum
		{
			ALPHA = 0x0,
			SHADE = 0x1,
			MAX_TYPES = 0x2,
			STENCIL = 0x3,
			FOG = 0x4,
		};

		// add
		virtual std::int32_t Type() const = 0;            // 28
		virtual void Update(NiUpdateData& a_updateData);  // 29
	};
	static_assert(sizeof(NiProperty) == 0x28);
}
