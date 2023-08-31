#pragma once
#include "RE/Shared/TempEffects/BSTempEffect.h"

namespace RE
{
	class __declspec(novtable) BSTempEffectSPG :
		public BSTempEffect  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSTempEffectSPG };
		static constexpr auto VTABLE{ VTABLE::BSTempEffectSPG };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSTempEffectSPG };
		static constexpr auto TYPE{ TEMP_EFFECT_TYPE::kSPG };

		// add

		// members
	};
	//static_assert(sizeof(BSTempEffectSPG) == 0x40);
}
