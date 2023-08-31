#pragma once
#include "RE/Shared/TempEffects/BSTempEffect.h"

namespace RE
{
	class __declspec(novtable) BSTempEffectGeometryDecal :
		public BSTempEffect  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSTempEffectGeometryDecal };
		static constexpr auto VTABLE{ VTABLE::BSTempEffectGeometryDecal };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSTempEffectGeometryDecal };
		static constexpr auto TYPE{ TEMP_EFFECT_TYPE::kGeometryDecal };

		// add

		// members
	};
	//static_assert(sizeof(BSTempEffectGeometryDecal) == 0x40);
}
