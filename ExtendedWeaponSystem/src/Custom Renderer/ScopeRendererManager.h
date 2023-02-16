#pragma once
#include "Global.h"

extern BSCullingProcess* pScopeManagerCullingProc;
extern BSShaderAccumulator* pScopeManagerAccumulator;
extern ImageSpaceShaderParam* pScopeManagerShaderParam;

//This will technically do everything that ScopeRenderer and ScopeCamera does but without allocating the custom classes
class ScopeRendererManager {
public:

	//functions
	static void Setup();
	static void Shutdown();
	static void Pause();
	static void RenderHelper(bool save);
	static NiTexture* Render(bool save);

};
STATIC_ASSERT(std::is_empty_v<ScopeRendererManager>);