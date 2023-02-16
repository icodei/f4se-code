#pragma once
#include "f4se/BSGeometry.h"
#include "f4se/GameTypes.h"
#include "f4se/NiTextures.h"
#include "f4se/NiTypes.h"
#include "f4se_common/Utilities.h"

class ImageSpaceManager;

class ImageSpaceTexture {
public:

	MEMBER_FN_PREFIX(ImageSpaceTexture);

	//ImageSpaceTexture::GetRenderTarget(): This is not a render target.  Use QIsRenderTarget() first.
	//ImageSpaceTexture::GetDepthStencilBuffer(): This is not depth stencil buffer.  Use QIsDepthStencilBuffer() first
};

class ImageSpaceEffectParam {
public:
	virtual ~ImageSpaceEffectParam() {};

	MEMBER_FN_PREFIX(ImageSpaceEffectParam);

};

class ImageSpaceShaderParam : public ImageSpaceEffectParam {
public:
	ImageSpaceShaderParam() { CALL_MEMBER_FN(this, ctor)(); };
	//virtual ~ImageSpaceShaderParam();

	

	void ResizeConstantGroup(SInt32 a1, SInt32 a2);
	void SetPixelConstant(SInt32 a1, float a2, float a3, float a4, float a5);

private:
	MEMBER_FN_PREFIX(ImageSpaceShaderParam);
	DEFINE_MEMBER_FN(ctor, void, 0x0282C200);
	DEFINE_MEMBER_FN(ResizeConstantGroup, void, 0x001E0C80, SInt32, SInt32);
	DEFINE_MEMBER_FN(SetPixelConstant, void, 0x0282C460, SInt32, float, float, float, float);
};

class ImageSpaceEffect {
public:
	class EffectInput {
	public:

	};
	class EffectDesc {
	public:

	};

	virtual ~ImageSpaceEffect() {};
	virtual void Render(BSTriShape*, ImageSpaceEffectParam*) {};
	virtual void Dispatch(ImageSpaceEffectParam*, bool, UInt32, EffectDesc*) {};
	virtual void Setup(ImageSpaceManager*, ImageSpaceEffectParam*) {};
	virtual void Shutdown(void) {};
	virtual void BorrowTextures(ImageSpaceEffectParam*) {};
	virtual void ReturnTextures(void) {};
	virtual void UpdateComputeShaderParam(UInt32) {};
	virtual bool IsActive(void) {};
	virtual bool UpdateParams(ImageSpaceEffectParam*) {};
	virtual bool SetRenderStates(ImageSpaceEffectParam*) {};
	virtual bool RestoreRenderStates(ImageSpaceEffectParam*) {};

	UInt64 unk08;
	NiTArray<ImageSpaceEffect*> pImageSpaceEffectArray;
	NiTArray<ImageSpaceEffectParam*> pImageSpaceEffectParamArray;
	NiTArray<ImageSpaceTexture*> texArray;
	NiTArray<ImageSpaceTexture*> field_58;
	NiTArray<EffectInput*> pEffectInputArray;
	NiTArray<int*> pIntArray;
	bool field_A0;
	UInt8 field_A1;
	UInt32 field_A4;
	bool UseDynamicResolution;
	NiPointer<NiTexture> tex_B0;
	NiPointer<NiTexture> field_B8;
	UInt32 field_C0;
	UInt8 field_C4;
	UInt8 field_C5;
	UInt8 field_C6;
	UInt8 field_C7;
	UInt8 field_C8;
	UInt64 field_D0;
	UInt64 field_D8;
	BSTArray<void*> field_E0;
	BSTArray<void*> field_F8;
	UInt8 gap110[44];
	UInt8 field_13C;

	MEMBER_FN_PREFIX(ImageSpaceEffect);
};



class ImageSpaceBaseData {
public:

	float hdrData[9];
	float cinematicData[3];
	float tintData[4];
	float dofData[6];
};

class ImageSpaceLUTData {
public:

	BSFixedString field_0;
	UInt8 gap8[24];
	BSFixedString field_20;
	NiPointer<NiTexture> field_28;
	NiPointer<NiTexture> field_30;
	UInt64 field_38;
	UInt64 field_40;
	UInt64 field_48;
	UInt64 final1;
};

extern RelocPtr <ImageSpaceShaderParam>		BSImagespaceShader_DefaultParam;
extern RelocPtr <ImageSpaceShaderParam*>	BSImagespaceShader_pCurrentParam;