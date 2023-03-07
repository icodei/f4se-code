#pragma once
#include "Global.h"
#include "ScopeCamera.h"

class ScopeRenderer {
public:
	ScopeRenderer();
	ScopeRenderer(BSCullingProcess *cullingProcess, ScopeCamera *camera, BSShaderAccumulator* accumulator, ImageSpaceShaderParam* params);
	~ScopeRenderer();

	//operators
	ScopeRenderer& operator=(const ScopeRenderer& rhs);

	//functions
	NiTexture* Render(bool a1);

	//members
	BSCullingProcess* pScopeCullingProc{ nullptr };
	ScopeCamera scopeCam{ ScopeCamera() };
	BSShaderAccumulator* pScopeAccumulator{ nullptr };
	ImageSpaceShaderParam shaderParams;
	std::uint32_t renderTarget{ 19 };
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

void RenderScopeScene(NiCamera* cam, BSShaderAccumulator* shadeAccum, std::uint32_t target, std::uint32_t depthTarget);
