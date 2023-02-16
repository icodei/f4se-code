#pragma once
#include "RE/Bethesda/BSShader.h"
#include "RE/Bethesda/ImageSpace.h"

namespace RE
{
	class BSImagespaceShader : public BSShader, public ImageSpaceEffect
	{
	public:

		static constexpr auto RTTI{ RTTI::BSImagespaceShader };
		static constexpr auto VTABLE{ VTABLE::BSImagespaceShader };

		BSImagespaceShader() = delete;
		BSImagespaceShader(const char* fxpName){};

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

		
	};
	REL::Relocation<ImageSpaceShaderParam> BSImagespaceShader__DefaultParam{ REL::ID(455011) };
	REL::Relocation<ImageSpaceShaderParam*> BSImagespaceShader__pCurrentParam{ REL::ID(16045) };
}
