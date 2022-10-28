#include "f4se/BSGraphics.h"

void BSCullingProcess::SetAccumulator(NiAccumulator* accumulator) {
	CALL_MEMBER_FN(this, SetAccumulator)(accumulator);
}

void BSGraphics::Renderer::ClearColor() {
	CALL_MEMBER_FN(this, ClearColor)();
}

void BSGraphics::Renderer::DoZPrePass(NiCamera* cam1, NiCamera* cam2, float a1, float a2, float a3, float a4) {
	CALL_MEMBER_FN(this, DoZPrePass)(cam1, cam2, a1, a2, a3, a4);
}

void BSGraphics::Renderer::Flush() {
	CALL_MEMBER_FN(this, Flush)();
}

void BSGraphics::Renderer::SetClearColor(float red, float green, float blue, float alpha) {
	CALL_MEMBER_FN(this, SetClearColor)(red, green, blue, alpha);
}

void BSGraphics::Renderer::ResetZPrePass() {
	CALL_MEMBER_FN(this, ResetZPrePass)();
}

void BSGraphics::Renderer::ResetState() {
	CALL_MEMBER_FN(this, ResetState)();
}

void BSGraphics::State::SetCameraData(NiCamera* cam, bool a3, float a4, float a5) {
	CALL_MEMBER_FN(this, SetCameraData)(cam, a3, a4, a5);
}

void BSGraphics::RenderTargetManager::AcquireCubemap(SInt32 target) {
	CALL_MEMBER_FN(this, AcquireCubemap)(target);
}

void BSGraphics::RenderTargetManager::AcquireDepthStencil(SInt32 target) {
	CALL_MEMBER_FN(this, AcquireDepthStencil)(target);
}

void BSGraphics::RenderTargetManager::AcquireRenderTarget(SInt32 target) {
	CALL_MEMBER_FN(this, AcquireRenderTarget)(target);
}

void BSGraphics::RenderTargetManager::CopyRenderTargetToClipboard(SInt32 target) {
	CALL_MEMBER_FN(this, CopyRenderTargetToClipboard)(target);
}

void BSGraphics::RenderTargetManager::CopyRenderTargetToRenderTargetCopy(SInt32 target, SInt32 target2) {
	CALL_MEMBER_FN(this, CopyRenderTargetToRenderTargetCopy)(target, target2);
}

void BSGraphics::RenderTargetManager::CopyRenderTargetToTexture(SInt32 target, Texture* tex, bool a3, bool a4) {
	CALL_MEMBER_FN(this, CopyRenderTargetToTexture)(target, tex, a3, a4);
}

void BSGraphics::RenderTargetManager::CreateCubeMapRenderTarget(SInt32 target, CubeMapRenderTargetProperties& cubeProps, TARGET_PERSISTENCY persist) {
	CALL_MEMBER_FN(this, CreateCubeMapRenderTarget)(target, cubeProps, persist);
}

void BSGraphics::RenderTargetManager::CreateDepthStencilTarget(SInt32 target, DepthStencilTargetProperties& depthProps, TARGET_PERSISTENCY persist) {
	CALL_MEMBER_FN(this, CreateDepthStencilTarget)(target, depthProps, persist);
}

void BSGraphics::RenderTargetManager::CreateRenderTarget(SInt32 target, RenderTargetProperties& targetProps, TARGET_PERSISTENCY persist) {
	CALL_MEMBER_FN(this, CreateRenderTarget)(target, targetProps, persist);
}

void BSGraphics::RenderTargetManager::ReleaseCubemap(SInt32 target) {
	CALL_MEMBER_FN(this, ReleaseCubemap)(target);
}

void BSGraphics::RenderTargetManager::ReleaseDepthStencil(SInt32 target) {
	CALL_MEMBER_FN(this, ReleaseDepthStencil)(target);
}

void BSGraphics::RenderTargetManager::ReleaseRenderTarget(SInt32 target) {
	CALL_MEMBER_FN(this, ReleaseRenderTarget)(target);
}

BSGraphics::Texture* BSGraphics::RenderTargetManager::SaveRenderTargetToTexture(SInt32 target, bool a1, bool a2, Usage use) {
	return CALL_MEMBER_FN(this, SaveRenderTargetToTexture)(target, a1, a2, use);
}

void BSGraphics::RenderTargetManager::SetCurrentRenderTarget(SInt32 slot, SInt32 targetIndex, SetRenderTargetMode mode) {
	CALL_MEMBER_FN(this, SetCurrentRenderTarget)(slot, targetIndex, mode);
}

void BSGraphics::RenderTargetManager::SetCurrentDepthStencilTarget(SInt32 a1, SetRenderTargetMode mode, SInt32 a2, bool a3) {
	CALL_MEMBER_FN(this, SetCurrentDepthStencilTarget)(a1, mode, a2, a3);
}

void BSGraphics::RenderTargetManager::SetCurrentViewportForceToRenderTargetDimensions() {
	CALL_MEMBER_FN(this, SetCurrentViewportForceToRenderTargetDimensions)();
}

void BSGraphics::RenderTargetManager::SetTextureRenderTarget(UInt32 a1, SInt32 a2, bool a3) {
	CALL_MEMBER_FN(this, SetTextureRenderTarget)(a1, a2, a3);
}

void BSGraphics::RenderTargetManager::SetTextureDepth(UInt32 a1, SInt32 a2) {
	CALL_MEMBER_FN(this, SetTextureDepth)(a1, a2);
}

RelocAddr<_AccumulateSceneArray> AccumulateSceneArray_Internal(0x0281B0F0);
void BSShaderUtil::AccumulateSceneArray(NiCamera* cam, BSTArray<NiPointer<NiAVObject>>* objs, BSCullingProcess& cullproc, bool a1) {
	AccumulateSceneArray_Internal(cam, objs, cullproc, a1);
}

RelocAddr<_AccumulateScene> AccumulateScene_Internal(0x0281ADE0);
void BSShaderUtil::AccumulateScene(NiCamera* cam, NiAVObject* obj, BSCullingProcess& cullproc, bool a1) {
	AccumulateScene_Internal(cam, obj, cullproc, a1);
}

void BSShaderManager::GetTexture(const char* filePath, bool a2, NiPointer<NiTexture>& returnTex, bool a4, bool a5, bool a6) {
	if (returnTex) {
		CALL_MEMBER_FN(this, GetTexture)(filePath, a2, returnTex, a4, a5, a6);
	}
}

void BSShaderAccumulator::ClearActivePasses(bool a1) {
	CALL_MEMBER_FN(this, ClearActivePasses)(a1);
}

void BSShaderAccumulator::ClearEffectPasses() {
	CALL_MEMBER_FN(this, ClearEffectPasses)();
}

void BSShaderAccumulator::ClearGroupPasses(SInt32 a1, bool a2) {
	CALL_MEMBER_FN(this, ClearGroupPasses)(a1, a2);
}

void BSShaderAccumulator::RenderBatches(SInt32 a1, bool a2, SInt32 a3) {
	CALL_MEMBER_FN(this, RenderBatches)(a1, a2, a3);
}

void BSShaderAccumulator::RenderBlendedDecals() {
	CALL_MEMBER_FN(this, RenderBlendedDecals)();
}

void BSShaderAccumulator::RenderOpaqueDecals() {
	CALL_MEMBER_FN(this, RenderOpaqueDecals)();
}

void ImageSpaceShaderParam::ResizeConstantGroup(SInt32 a1, SInt32 a2) {
	CALL_MEMBER_FN(this, ResizeConstantGroup)(a1, a2);
}

void ImageSpaceShaderParam::SetPixelConstant(SInt32 a1, float a2, float a3, float a4, float a5) {
	CALL_MEMBER_FN(this, SetPixelConstant)(a1, a2, a3, a4, a5);
}

ImageSpaceEffect* ImageSpaceManager::GetEffect(ImageSpaceEffectEnum a_enum) {
	return CALL_MEMBER_FN(this, GetEffect)(a_enum);
}

void ImageSpaceManager::RenderEffect_1(ImageSpaceEffectEnum a_enum, SInt32 a2, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_1)(a_enum, a2, a_param);
}

void ImageSpaceManager::RenderEffect_2(ImageSpaceEffect* a_effect, SInt32 a2, SInt32 a3, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_2)(a_effect, a2, a3, a_param);
}

void ImageSpaceManager::RenderEffect_3(ImageSpaceEffect* a_effect, SInt32 a2, SInt32 a3, SInt32 a4, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_3)(a_effect, a2, a3, a4, a_param);
}

void ImageSpaceManager::RenderEffectHelper_2(ImageSpaceEffectEnum a_enum, SInt32 a2, SInt32 a3, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffectHelper_2)(a_enum, a2, a3, a_param);
}

void ImageSpaceManager::RenderEffect_Tex_1(ImageSpaceEffect* a_effect, NiTexture* a_tex, SInt32 a3, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_Tex_1)(a_effect, a_tex, a3, a_param);
}

void ImageSpaceManager::RenderEffect_Tex_2(ImageSpaceEffectEnum a_enum, NiTexture* a_tex, NiTexture* a_tex2, SInt32 a4, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffect_Tex_2)(a_enum, a_tex, a_tex2, a4, a_param);
}

void ImageSpaceManager::RenderEffectHelper_Tex_1(ImageSpaceEffectEnum a_enum, NiTexture* a_tex, SInt32 a3, ImageSpaceEffectParam* a_param) {
	CALL_MEMBER_FN(this, RenderEffectHelper_Tex_1)(a_enum, a_tex, a3, a_param);
}

NiPointer<BSTriShape>& ImageSpaceManager::SelectScreenShape(ImageSpaceEffect* a_effect) {
	return CALL_MEMBER_FN(this, SelectScreenShape)(a_effect);
}


RelocPtr <BSGraphics::Context*>						pCurContext(0x06A8CB20);
RelocPtr <BSGraphics::Context*>						pDefaultContext(0x061DDC68);
RelocPtr <BSGraphics::Renderer>						BSGraphics_gRenderer(0x061E0900);
RelocPtr <BSGraphics::RendererData*>				pRendererData(0x0609BF80);
RelocPtr <BSGraphics::RendererWindow*>				pRendererWindow(0x0609BF90);
RelocPtr <BSGraphics::State>						BSGraphics_gState(0x06541EF0);
RelocPtr <BSGraphics::RenderTargetManager>			BSGraphics_gRenderTargetManager(0x0384FD30);
RelocPtr <BSShaderAccumulator*>						pCurrentShaderAccumulator(0x06721AB0);
RelocPtr <BSShaderManager::State>					ShaderManager_gState(0x06721B70);
RelocPtr <BSShaderManager>							gShaderManagerInstance(0x06721B39);
RelocPtr <NiCamera*>								BSShaderManager_spCamera(0x06721AE0);
RelocPtr <BSShaderMaterial*>						pShaderMaterialDefault(0x06723120);
RelocPtr <BSShaderResourceManager>					gShaderResourceManagerInstance(0x038CBDC0); //This was originally set to 0x05C08F08 which is a pointer to the IRendererResourceManager
RelocPtr <ID3D11Device*>							pDevice(0x0609BF88);
RelocPtr <ID3D11DeviceContext*>						pImmediateContext(0x061DDC60);
RelocPtr <ID3D11DeviceContext*>						pMainContext(0x0609BF98);
RelocPtr <ID3D11DeviceContext*>						pContext(0x06A8CB18);
RelocPtr <ImageSpaceManager*>						ImageSpaceManager_pInstance(0x067220E8);
RelocPtr <ImageSpaceShaderParam>					BSImagespaceShader_DefaultParam(0x06733340);
RelocPtr <ImageSpaceShaderParam*>					BSImagespaceShader_pCurrentParam(0x06733330);


