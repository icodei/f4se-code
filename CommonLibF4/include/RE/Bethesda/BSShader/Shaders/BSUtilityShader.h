#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSUtilityShader : public BSShader
	{
	public:
		static constexpr auto RTTI{ RTTI::BSUtilityShader };
		static constexpr auto VTABLE{ VTABLE::BSUtilityShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_UTILITY };

		// members
		std::uint32_t currentTechniqueID;  // 118
		std::uint32_t currentDecl;         // 11C
	};
	static_assert(sizeof(BSUtilityShader) == 0x120);
}
