#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/ImageSpace.h"
#include "RE/Bethesda/BSCore/BSTArray.h"

namespace RE
{
	class BSImagespaceShader : public BSShader, public ImageSpaceEffect
	{
	public:
		static constexpr auto RTTI{ RTTI::BSImagespaceShader };
		static constexpr auto VTABLE{ VTABLE::BSImagespaceShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_IMAGESPACE };

		BSImagespaceShader() = delete;
		BSImagespaceShader(const char* fxpName)
		{
			typedef BSImagespaceShader* func_t(BSImagespaceShader*, const char*);
			REL::Relocation<func_t> func{ REL::ID(103011) };
			func(this, fxpName);
		}

		virtual ~BSImagespaceShader();	// 00

		static ImageSpaceShaderParam& GetDefaultParam()
		{
			REL::Relocation<ImageSpaceShaderParam*> singleton{ REL::ID(455011) };
			return *singleton;
		}

		static ImageSpaceShaderParam* GetCurrentParam()
		{
			REL::Relocation<ImageSpaceShaderParam**> singleton{ REL::ID(16045) };
			return *singleton;
		}

		//members
		const char* name;
		std::uint64_t field_1D0;
		std::uint32_t field_1D8;
		std::uint32_t field_1DC;
		BSTArray<void*> vertexConstantGroup;
		BSTArray<void*> pixelConstantGroup;
		BSTArray<void*> array_210;
		BSTArray<void*> array_228;
	};
}
