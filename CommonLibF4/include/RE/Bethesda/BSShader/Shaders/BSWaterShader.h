#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSWaterShader : public BSShader
	{
		static constexpr auto RTTI{ RTTI::BSWaterShader };
		static constexpr auto VTABLE{ VTABLE::BSWaterShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_WATER };

		std::byte gap[0x120 - 0x118];
	};
	static_assert(sizeof(BSWaterShader) == 0x120);
}
