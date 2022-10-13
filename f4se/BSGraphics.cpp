#include "f4se/BSGraphics.h"


void BSShaderManager::GetTexture(const char* filePath, bool a2, NiPointer<NiTexture>& returnTex, bool a4, bool a5, bool a6) {
	if (returnTex) {
		CALL_MEMBER_FN(this, GetTexture)(filePath, a2, returnTex, a4, a5, a6);
	}
};

ImageSpaceEffect* ImageSpaceManager::GetEffect(ImageSpaceEffectEnum a_enum) {
	return CALL_MEMBER_FN(this, GetEffect)(a_enum);
};

void ImageSpaceManager::RenderEffect_1(ImageSpaceEffectEnum a_enum, SInt32 a2, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_1)(a_enum, a2, a_param);
};
void ImageSpaceManager::RenderEffect_2(ImageSpaceEffect* a_effect, SInt32 a2, SInt32 a3, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_2)(a_effect, a2, a3, a_param);
};

void ImageSpaceManager::RenderEffect_3(ImageSpaceEffect* a_effect, SInt32 a2, SInt32 a3, SInt32 a4, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_3)(a_effect, a2, a3, a4, a_param);
};

void ImageSpaceManager::RenderEffectHelper_2(ImageSpaceEffectEnum a_enum, SInt32 a2, SInt32 a3, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffectHelper_2)(a_enum, a2, a3, a_param);
};

void ImageSpaceManager::RenderEffect_Tex_1(ImageSpaceEffect* a_effect, NiTexture* a_tex, SInt32 a3, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_Tex_1)(a_effect, a_tex, a3, a_param);
};
void ImageSpaceManager::RenderEffect_Tex_2(ImageSpaceEffectEnum a_enum, NiTexture* a_tex, NiTexture* a_tex2, SInt32 a4, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_Tex_2)(a_enum, a_tex, a_tex2, a4, a_param);
};

void ImageSpaceManager::RenderEffectHelper_Tex_1(ImageSpaceEffectEnum a_enum, NiTexture* a_tex, SInt32 a3, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffectHelper_Tex_1)(a_enum, a_tex, a3, a_param);
};

NiPointer<BSTriShape>& ImageSpaceManager::SelectScreenShape(ImageSpaceEffect* a_effect) {
	return CALL_MEMBER_FN(this, SelectScreenShape)(a_effect);
};


RelocPtr <BSGraphics::Context*>						pCurContext(0x06A8CB20);
RelocPtr <BSGraphics::Context*>						pDefaultContext(0x061DDC68);
RelocPtr <BSGraphics::Renderer>						gRenderer(0x061E0900);
RelocPtr <BSGraphics::RendererData*>				pRendererData(0x0609BF80);
RelocPtr <BSGraphics::RendererWindow*>				pRendererWindow(0x0609BF90);
RelocPtr <BSGraphics::State>						gRenderState(0x06541EF0);
RelocPtr <BSGraphics::RenderTargetManager>			gRenderTargetManager(0x0384FD30);
RelocPtr <BSShaderAccumulator*>						pCurrentShaderAccumulator(0x06721AB0);
RelocPtr <BSShaderManager::State>					gShaderManagerState(0x06721B70);
RelocPtr <BSShaderManager>							gShaderManagerInstance(0x06721B39);
RelocPtr <BSShaderMaterial*>						pShaderMaterialDefault(0x06723120);
RelocPtr <BSShaderResourceManager>					gShaderResourceManagerInstance(0x038CBDC0); //This was originally set to 0x05C08F08 which is a pointer to the IRendererResourceManager
RelocPtr <ID3D11Device*>							pDevice(0x0609BF88);
RelocPtr <ID3D11DeviceContext*>						pImmediateContext(0x061DDC60);
RelocPtr <ID3D11DeviceContext*>						pMainContext(0x0609BF98);
RelocPtr <ID3D11DeviceContext*>						pContext(0x06A8CB18);
RelocPtr <ImageSpaceManager*>						pImageSpaceManagerInstance(0x067220E8);
RelocPtr <ImageSpaceShaderParam>					BSImagespaceShader_DefaultParam(0x06733340);
RelocPtr <ImageSpaceShaderParam*>					BSImagespaceShader_pCurrentParam(0x06733330);
