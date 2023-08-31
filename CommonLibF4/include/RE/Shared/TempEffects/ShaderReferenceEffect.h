#pragma once
#include "RE/Shared/TempEffects/BSTempEffect.h"
#include "RE/Shared/TempEffects/ReferenceEffect.h"

namespace RE
{
	class __declspec(novtable) ShaderReferenceEffect :
		public ReferenceEffect  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ShaderReferenceEffect };
		static constexpr auto VTABLE{ VTABLE::ShaderReferenceEffect };
		static constexpr auto Ni_RTTI{ Ni_RTTI::ShaderReferenceEffect };
		static constexpr auto TYPE{ TEMP_EFFECT_TYPE::kShaderReference };

		enum Flag
		{
		};

		// add

		// members
	};
	//static_assert(sizeof(ShaderReferenceEffect) == 0x40);
}
