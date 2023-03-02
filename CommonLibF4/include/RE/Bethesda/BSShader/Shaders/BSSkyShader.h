#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSSkyShader : public BSShader
	{
	public:
		static constexpr auto RTTI{ RTTI::BSSkyShader };
		static constexpr auto VTABLE{ VTABLE::BSSkyShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_SKY };

		// members
		std::byte gap[0x120 - 0x118];
	};
	static_assert(sizeof(BSSkyShader) == 0x120);
}
