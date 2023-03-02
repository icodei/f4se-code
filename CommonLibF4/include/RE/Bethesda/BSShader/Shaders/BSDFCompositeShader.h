#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSDFCompositeShader : public BSShader
	{
		static constexpr auto RTTI{ RTTI::BSDFCompositeShader };
		static constexpr auto VTABLE{ VTABLE::BSDFCompositeShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_DFCOMPOSITE };

		std::byte gap[0x128 - 0x118];
	};
	static_assert(sizeof(BSDFCompositeShader) == 0x128);
}
