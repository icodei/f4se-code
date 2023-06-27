#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSEffectShader : public BSShader
	{
	public:
		static constexpr auto RTTI{ RTTI::BSEffectShader };
		static constexpr auto VTABLE{ VTABLE::BSEffectShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_EFFECT };

		static constexpr auto X{ 0 };
		static constexpr auto Y{ 1 };
		static constexpr auto Z{ 2 };
		static constexpr auto W{ 3 };

		// members
		std::byte gap[0x120 - 0x118];
	};
	static_assert(sizeof(BSEffectShader) == 0x120);
}
