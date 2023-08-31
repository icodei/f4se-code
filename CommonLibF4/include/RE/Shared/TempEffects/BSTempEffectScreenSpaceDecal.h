#pragma once
#include "RE/Shared/TempEffects/BSTempEffect.h"

namespace RE
{
	class __declspec(novtable) BSTempEffectScreenSpaceDecal :
		public BSTempEffect  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::__BSTempEffectScreenSpaceDecal };
		static constexpr auto VTABLE{ VTABLE::__BSTempEffectScreenSpaceDecal };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSTempEffectScreenSpaceDecal };
		static constexpr auto TYPE{ TEMP_EFFECT_TYPE::kScreenSpaceDecal };

		// add

		// members
	};
	//static_assert(sizeof(BSTempEffectScreenSpaceDecal) == 0x40);
}
