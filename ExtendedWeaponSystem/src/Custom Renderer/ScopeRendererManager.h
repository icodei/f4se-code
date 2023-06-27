#pragma once
#include "Global.h"

/*
//This will technically do everything that ScopeCustomRenderer and ScopeCamera does but without allocating the custom classes
class ScopeRendererManager {
public:

	//functions
	static void Setup();
	static void Shutdown();
	static void Pause();
	static void RenderHelper(bool save);
	static NiTexture* Render(bool save);

	static BSCullingProcess* pScopeManagerCullingProc;
	static BSShaderAccumulator* pScopeManagerAccumulator;
	static ImageSpaceShaderParam* pScopeManagerShaderParam;
	static NiCamera* pCamera;
	static BSGeometry* pRenderPlane;
};
static_assert(std::is_empty_v<ScopeRendererManager>);
*/
