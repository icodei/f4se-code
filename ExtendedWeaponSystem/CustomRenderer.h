#pragma once

class ScopeRenderer;
class ScopeCamera;

#define NiPoint3_ZERO NiPoint3(0, 0, 0);

class ScopeCamera : public TESCamera {
public:
	ScopeCamera();

	class DefaultState : public TESCameraState {
	public:
		DefaultState(TESCamera * cam, UInt32 ID);
		virtual ~DefaultState();
		virtual void Begin() override;
		virtual void End() override { };
		//virtual void Update(TESCameraState* arg) override;
		//virtual void GetRotation(NiQuaternion* out) override;
		//virtual void GetPosition(NiPoint3* out) override;
		//virtual void SaveGame() override;
		//virtual void LoadGame() override;
		//virtual void Revert() override;

		//members
		NiPoint3 initialPosition;
		NiPoint3 translation;
		float zoom;
		float minFrustumHalfWidth;
		float minFrustumHalfHeight;

		//member access
		NiPoint3& QInitialPosition();

		//functions
		void SetInitialPosition(NiPoint3& newPos);
		void SetMinFrustum(float width, float height);
		void SetTranslation(NiPoint3& newPos);
		void SetZoom(float newZoom);
	};

	//members
	NiPoint3 maxExtent;
	NiPoint3 minExtent;
	DefaultState* defaultState;
	NiPointer<NiCamera> camera;
	float zRotation;

	//member access
	NiPoint3& QMaxExtent();
	NiPoint3& QMinExtent();
	NiCamera* QRenderCamera();
	float QZRotation();

	//functions
	void FocusOnPosition(NiPoint3 position);
	void Reset();
	void SetExtents(NiPoint3& min, NiPoint3& max);
	void SetInitialPosition(const NiPoint3& newPos);
	void SetMinFrustum(float width, float height);
	void SetState(DefaultState* cameraState);
	void SetZRotation(float rotation);
	void SetZoom(float newZoom);
	
};

class ScopeRenderer {
public:
	ScopeRenderer();
	~ScopeRenderer();

	//members
	BSCullingProcess				scopeCullingProc;
	ScopeCamera						scopeCam;
	NiPointer<BSShaderAccumulator>	spScopeAccumulator;
	ImageSpaceShaderParam			params;
	UInt32							type;

	//functions
	NiTexture* Render(bool a1);
};

void nsScope_CreateRenderer();
ScopeRenderer* nsScope_InitRenderer();
void nsScope_Render();

void RenderScopeScene(NiCamera* cam, BSShaderAccumulator* shadeaccum, SInt32 a1, SInt32 a2, SInt32 a3);

//This will technically do everything that ScopeRenderer and ScopeCamera does but without allocating the custom classes
class ScopeRendererManager {
public:

	//functions
	static void Setup();
	static void RenderHelper(bool save);
	static NiTexture* Render(bool save);
};
STATIC_ASSERT(std::is_empty_v<ScopeRendererManager>);