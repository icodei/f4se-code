#pragma once
#include "RE/Shared/TempEffects/BSTempEffect.h"

namespace RE
{
	class __declspec(novtable) BSTempEffectParticle :
		public BSTempEffect  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSTempEffectParticle };
		static constexpr auto VTABLE{ VTABLE::BSTempEffectParticle };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSTempEffectParticle };
		static constexpr auto TYPE{ TEMP_EFFECT_TYPE::kParticle };

		// add

		// members
	};
	//static_assert(sizeof(BSTempEffectParticle) == 0x40);
}
