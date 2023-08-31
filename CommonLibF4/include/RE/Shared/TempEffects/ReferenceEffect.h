#pragma once
#include "RE/Shared/TempEffects/BSTempEffect.h"

namespace RE
{
	class __declspec(novtable) ReferenceEffect :
		public BSTempEffect  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ReferenceEffect };
		static constexpr auto VTABLE{ VTABLE::ReferenceEffect };
		static constexpr auto Ni_RTTI{ Ni_RTTI::ReferenceEffect };
		static constexpr auto TYPE{ TEMP_EFFECT_TYPE::kReference };

		// add

		// members
	};
	//static_assert(sizeof(ReferenceEffect) == 0x40);
}
