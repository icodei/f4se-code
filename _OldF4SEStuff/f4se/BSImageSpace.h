#pragma once
#include "f4se_common/Utilities.h"
#include "f4se/BSShader.h"
#include "f4se/ImageSpace.h"

class BSImagespaceShader : public BSShader, public ImageSpaceEffect {
public:
	BSImagespaceShader() = delete;
	BSImagespaceShader(const char* fxpName) { };

	//virtual ~BSImagespaceShader();
	//virtual void Render(BSTriShape*, ImageSpaceEffectParam*) override;
	//virtual void Dispatch(ImageSpaceEffectParam*, bool, UInt32, EffectDesc*) override;
	//virtual void Setup(ImageSpaceManager*, ImageSpaceEffectParam*);
	//virtual void Shutdown(void) override;
	//virtual void BorrowTextures(ImageSpaceEffectParam*);
	//virtual void ReturnTextures(void);
	//virtual void UpdateComputeShaderParam(UInt32);
	//virtual bool IsActive(void);
	//virtual bool UpdateParams(ImageSpaceEffectParam*);
	//virtual bool SetRenderStates(ImageSpaceEffectParam*);
	//virtual bool RestoreRenderStates(ImageSpaceEffectParam*);

	MEMBER_FN_PREFIX(BSImagespaceShader);
};