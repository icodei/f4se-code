#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/ImageSpace.h"
#include "RE/Bethesda/BSTArray.h"

namespace RE
{
	class BSImagespaceShader : public BSShader, public ImageSpaceEffect
	{
	public:
		static constexpr auto RTTI{ RTTI::BSImagespaceShader };
		static constexpr auto VTABLE{ VTABLE::BSImagespaceShader };

		BSImagespaceShader() = delete;
		BSImagespaceShader(const char* fxpName) { ctor(fxpName); }

		//virtual ~BSImagespaceShader();
		//virtual void Render(BSTriShape*, ImageSpaceEffectParam*) override;
		//virtual void Dispatch(ImageSpaceEffectParam*, bool, std::uint32_t, EffectDesc*) override;
		//virtual void Setup(ImageSpaceManager*, ImageSpaceEffectParam*);
		//virtual void Shutdown(void) override;
		//virtual void BorrowTextures(ImageSpaceEffectParam*);
		//virtual void ReturnTextures(void);
		//virtual void UpdateComputeShaderParam(std::uint32_t);
		//virtual bool IsActive(void);
		//virtual bool UpdateParams(ImageSpaceEffectParam*);
		//virtual bool SetRenderStates(ImageSpaceEffectParam*);
		//virtual bool RestoreRenderStates(ImageSpaceEffectParam*);

		//members
		const char* name;
		std::uint64_t field_1D0;
		std::uint32_t field_1D8;
		std::uint32_t field_1DC;
		BSTArray<void*> vertexConstantGroup;
		BSTArray<void*> pixelConstantGroup;
		BSTArray<void*> array_210;
		BSTArray<void*> array_228;
	private:
		BSImagespaceShader* ctor(const char* fxpName)
		{
			using func_t = decltype(&BSImagespaceShader::ctor);
			REL::Relocation<func_t> func{ REL::ID(103011) };
			return func(this, fxpName);
		}
	};
	REL::Relocation<ImageSpaceShaderParam> BSImagespaceShader__DefaultParam{ REL::ID(455011) };
	REL::Relocation<ImageSpaceShaderParam*> BSImagespaceShader__pCurrentParam{ REL::ID(16045) };
}
