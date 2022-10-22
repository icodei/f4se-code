#pragma once

class ScopeRenderer;
class ScopeCamera;

#define NiPoint3_ZERO NiPoint3(0, 0, 0);

class ScopeCamera : public TESCamera {
public:
	ScopeCamera();
	ScopeCamera(ScopeCamera* scopeCam);

	class DefaultState : public TESCameraState {
	public:
		DefaultState(TESCamera * cam, UInt32 ID);
		
		NiPoint3 initialPosition;
		NiPoint3 translation;
		float zoom;
		float minFrustrumHalfWidth;
		float minFrustrumHalfHeight;
	};

	//members
	NiPoint3 maxExtent;
	NiPoint3 minExtent;
	DefaultState* defaultState;
	NiPointer<NiCamera> camera;
	float zRotation;

	void SetInitialPosition(const NiPoint3& newPos);
	void SetZoom(float newZoom);
	void Reset();
};

class ScopeRenderer {
public:
	ScopeRenderer();
	ScopeRenderer(bool a1);

	BSCullingProcess				scopeCullingProc;
	ScopeCamera						scopeCam;
	NiPointer<BSShaderAccumulator>	spScopeAccumulator;
	ImageSpaceShaderParam			params;
	UInt32							type;

	NiTexture* Render(bool a1);
};

void nsScope_CreateRenderer();
ScopeRenderer* nsScope_InitRenderer(bool a1);
void nsScope_Render();

void RenderScopeScene(NiCamera* cam, BSShaderAccumulator* shadeaccum, SInt32 a1, SInt32 a2, SInt32 a3);