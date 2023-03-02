#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSDFPrePassShader : public BSShader
	{
		static constexpr auto RTTI{ RTTI::BSDFPrePassShader };
		static constexpr auto VTABLE{ VTABLE::BSDFPrePassShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_DFPREPASS };

		std::byte gap[0x120 - 0x118];
	};
	static_assert(sizeof(BSDFPrePassShader) == 0x120);
}
