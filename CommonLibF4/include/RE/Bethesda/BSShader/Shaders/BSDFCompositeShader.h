#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSTriShape;

	class BSDFCompositeShader : public BSShader
	{
		static constexpr auto RTTI{ RTTI::BSDFCompositeShader };
		static constexpr auto VTABLE{ VTABLE::BSDFCompositeShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_DFCOMPOSITE };

		BSTriShape* UnkGeom;
		void* unk;
	};
	static_assert(sizeof(BSDFCompositeShader) == 0x128);
}
