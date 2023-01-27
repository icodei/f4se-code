#pragma once
#include "Global.h"
#include "ScopeCamera.h"

class ScopeRenderer {
public:
	ScopeRenderer();
	~ScopeRenderer();

	//operators
	ScopeRenderer& operator=(const ScopeRenderer& rhs);

	//functions
	NiTexture* Render(bool a1);

	//members
	BSCullingProcess				scopeCullingProc;
	ScopeCamera						scopeCam;
	NiPointer<BSShaderAccumulator>	spScopeAccumulator;
	ImageSpaceShaderParam			params;
	UInt32							type;

};

void nsScope_CreateRenderer();
ScopeRenderer* nsScope_InitRenderer();
void nsScope_Render();

void RenderScopeScene(NiCamera* cam, BSShaderAccumulator* shadeaccum, SInt32 a1, SInt32 a2, SInt32 a3);

extern ScopeRenderer* scopeRenderer;
extern BSReadWriteLock scopeRendererLock;
