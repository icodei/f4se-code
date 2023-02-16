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
	BSCullingProcess scopeCullingProc{ BSCullingProcess(0) };
	ScopeCamera scopeCam;
	NiPointer<BSShaderAccumulator> spScopeAccumulator;
	ImageSpaceShaderParam params;
	std::uint32_t type;

	F4_HEAP_REDEFINE_NEW(ScopeRenderer);
};

void nsScope_CreateRenderer();
ScopeRenderer* nsScope_InitRenderer();
void nsScope_Render();

void RenderScopeScene(NiCamera* cam, BSShaderAccumulator* shadeaccum, std::uint32_t a1, std::uint32_t a2, std::uint32_t a3);

extern ScopeRenderer* scopeRenderer;
extern BSReadWriteLock scopeRendererLock;
