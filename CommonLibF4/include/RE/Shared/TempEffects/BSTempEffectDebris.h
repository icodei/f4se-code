#pragma once
#include "RE/Shared/TempEffects/BSTempEffect.h"

namespace RE
{
	class __declspec(novtable) BSTempEffectDebris :
		public BSTempEffect  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSTempEffectDebris };
		static constexpr auto VTABLE{ VTABLE::BSTempEffectDebris };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSTempEffectDebris };
		static constexpr auto TYPE{ TEMP_EFFECT_TYPE::kDebris };

		// add

		// members
	};
	//static_assert(sizeof(BSTempEffectDebris) == 0x40);
}
