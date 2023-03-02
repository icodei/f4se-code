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

		// members
		std::byte gap[0x120 - 0x118];
	};
	static_assert(sizeof(BSEffectShader) == 0x120);
}
