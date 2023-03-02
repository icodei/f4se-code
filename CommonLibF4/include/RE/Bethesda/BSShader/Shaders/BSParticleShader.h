#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSParticleShader : public BSShader
	{
	public:
		static constexpr auto RTTI{ RTTI::BSParticleShader };
		static constexpr auto VTABLE{ VTABLE::BSParticleShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_PARTICLE };

		// members
		std::byte gap[0x120 - 0x118];
	};
	static_assert(sizeof(BSParticleShader) == 0x120);
}
