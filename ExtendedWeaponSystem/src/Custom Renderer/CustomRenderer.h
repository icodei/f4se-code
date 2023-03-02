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
	ScopeCamera scopeCam{ ScopeCamera() };
	NiPointer<BSShaderAccumulator> spScopeAccumulator{ DrawWorld__spDrawPersonAccum.get() };
	ImageSpaceShaderParam params{ BSImagespaceShader__DefaultParam.get() };
	std::uint32_t type{ 20 };
};

namespace nsScope {

	//functions
	void CreateRenderer();
	void DestroyRenderer();
	ScopeRenderer* InitRenderer();
	void Render();

	//members
	static ScopeRenderer* scopeRenderer;
	static BSSpinLock scopeRendererLock;
}

class AccumulateSceneFunctor {
public:
	AccumulateSceneFunctor() : renderer(nullptr), interior(0){}
	AccumulateSceneFunctor(ScopeRenderer* pRenderer, bool isInterior) {
		renderer = pRenderer;
		interior = isInterior;
	}

	std::uint32_t operator()(TESObjectCELL* a_cell) {
		//TODO
	}

	//members
	ScopeRenderer* renderer{ nullptr };
	bool interior{ 0 };
};

void RenderScopeScene(NiCamera* cam, BSShaderAccumulator* shadeaccum, std::uint32_t a1, std::uint32_t a2, std::uint32_t a3);
