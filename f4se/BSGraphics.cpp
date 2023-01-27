#include "f4se/BSGraphics.h"

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


RelocPtr <BSGraphics::Context*>				pCurContext(0x06A8CB20);
RelocPtr <BSGraphics::Context*>				pDefaultContext(0x061DDC68);
RelocPtr <BSGraphics::Renderer>				BSGraphics_gRenderer(0x061E0900);
RelocPtr <BSGraphics::RendererData*>		pRendererData(0x0609BF80);
RelocPtr <BSGraphics::RendererWindow*>		pRendererWindow(0x0609BF90);
RelocPtr <BSGraphics::State>				BSGraphics_gState(0x06541EF0);
RelocPtr <BSGraphics::RenderTargetManager>	BSGraphics_gRenderTargetManager(0x0384FD30);
RelocPtr <ID3D11Device*>					pDevice(0x0609BF88);
RelocPtr <ID3D11DeviceContext*>				pImmediateContext(0x061DDC60);
RelocPtr <ID3D11DeviceContext*>				pMainContext(0x0609BF98);
RelocPtr <ID3D11DeviceContext*>				pContext(0x06A8CB18);