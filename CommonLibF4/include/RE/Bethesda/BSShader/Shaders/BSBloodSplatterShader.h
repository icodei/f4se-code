#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSBloodSplatterShader : public BSShader
	{
		static constexpr auto RTTI{ RTTI::BSBloodSplatterShader };
		static constexpr auto VTABLE{ VTABLE::BSBloodSplatterShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_BLOODSPLATTER };

		void* unk;
	};
	static_assert(sizeof(BSBloodSplatterShader) == 0x120);
}
