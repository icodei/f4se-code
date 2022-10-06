#include "f4se/BSGraphics.h"


RelocPtr <BSGraphics::Context*>						pCurContext(0x06A8CB20);
RelocPtr <BSGraphics::Context*>						pDefaultContext(0x061DDC68);
//RelocPtr <BSGraphics::BSRenderer*>				pRenderer(0x067220E8); //This was originally set to 0x067220E8 which is a pointer to the ImageSpaceManager
RelocPtr <BSGraphics::Renderer>						gRenderer(0x061E0900);
RelocPtr <BSGraphics::RendererData*>				pRendererData(0x0609BF80);
RelocPtr <BSGraphics::RendererWindow*>				pRendererWindow(0x0609BF90);
//RelocPtr <BSGraphics::BSRenderManager>			gRenderManager(0x061E0900);
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
