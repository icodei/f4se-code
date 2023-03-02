#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSDFLightShader : public BSShader
	{
		static constexpr auto RTTI{ RTTI::BSDFLightShader };
		static constexpr auto VTABLE{ VTABLE::BSDFLightShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_DFLIGHT };

		std::byte gap[0x140 - 0x118];
	};
	static_assert(sizeof(BSDFLightShader) == 0x140);
}
