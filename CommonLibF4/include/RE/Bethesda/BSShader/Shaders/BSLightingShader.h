#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSLightingShader : public BSShader
	{
		static constexpr auto RTTI{ RTTI::BSLightingShader };
		static constexpr auto VTABLE{ VTABLE::BSLightingShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_LIGHTING };

		std::byte gap[0x158 - 0x118];
	};
	static_assert(sizeof(BSLightingShader) == 0x158);
}
