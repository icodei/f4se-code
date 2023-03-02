#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSDistantTreeShader : public BSShader
	{
		static constexpr auto RTTI{ RTTI::BSDistantTreeShader };
		static constexpr auto VTABLE{ VTABLE::BSDistantTreeShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_DISTANTTREE };

		void* unk;
	};
	static_assert(sizeof(BSDistantTreeShader) == 0x120);
}
