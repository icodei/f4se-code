#pragma once
#include "Global.h"

class ScopeRenderer;
class ScopeCamera;

class ScopeCamera : public TESCamera {
public:
	ScopeCamera();

	virtual ~ScopeCamera();
	
	enum {
		kCameraState_Default = 0,
		kCameraState_IronSights,
		kNumCameraStates
	};

	class DefaultState : public TESCameraState {
	public:
		DefaultState();
		DefaultState(TESCamera & cam, UInt32 ID);

		virtual ~DefaultState();

		virtual bool ShouldHandleEvent(InputEvent* inputEvent = nullptr) override;
		virtual void OnKinectEvent(KinectEvent* inputEvent) override;
		virtual void OnDeviceConnectEvent(DeviceConnectEvent* inputEvent) override;
		virtual void OnThumbstickEvent(ThumbstickEvent* inputEvent) override;
		virtual void OnCursorMoveEvent(CursorMoveEvent* inputEvent) override;
		virtual void OnMouseMoveEvent(MouseMoveEvent* inputEvent) override;
		virtual void OnCharacterEvent(CharacterEvent* inputEvent) override;
		virtual void OnButtonEvent(ButtonEvent* inputEvent) override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Update(TESCameraState* arg) override;
		virtual void GetRotation(NiQuaternion* out) override;
		virtual void GetPosition(NiPoint3* out) override;
		virtual void SaveGame(BGSSaveFormBuffer* save) override { };
		virtual void LoadGame(BGSSaveFormBuffer* save) override { };
		virtual void Revert(BGSSaveFormBuffer* save) override { };

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
	TESCameraState* cameraStates[kNumCameraStates];
	TESCameraState* defaultState;
	NiPointer<NiCamera> camera;
	NiPoint3 maxExtent;
	NiPoint3 minExtent;

	//member access
	NiCamera* QRenderCamera();
	NiPoint3& QMaxExtent();
	NiPoint3& QMinExtent();

	//functions
	void Reset();
	void SetExtents(NiPoint3& min, NiPoint3& max);
	void SetState(TESCameraState* cameraState);
	
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

	//operators
	ScopeRenderer& operator=(const ScopeRenderer& rhs);

	//functions
	NiTexture* Render(bool a1);
};

void nsScope_CreateRenderer();
ScopeRenderer* nsScope_InitRenderer();
void nsScope_Render();

void RenderScopeScene(NiCamera* cam, BSShaderAccumulator* shadeaccum, SInt32 a1, SInt32 a2, SInt32 a3);

extern ScopeRenderer scopeRenderer;
extern BSReadWriteLock scopeRendererLock;
extern std::unordered_map<const char*, NiCamera*> s_extraCamerasMap;

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

extern NiCamera* scopePOV;
extern NiNode* scopePOVRoot;
extern NiCamera* scopePOV_BACKUP;
extern NiNode* scopePOVRoot_BACKUP;
extern BSCullingProcess* pScopeManagerCullingProc;
extern BSShaderAccumulator* pScopeManagerAccumulator;
extern ImageSpaceShaderParam* pScopeManagerShaderParam;

//stuff from JiP for reference
//
//#define DEFINE_COMMAND_PLUGIN(name, refRequired, numParams, paramInfo) \
//DEFINE_CMD_FULL(name, , refRequired, numParams, paramInfo, NULL)
// 
//DEFINE_COMMAND_PLUGIN(AttachExtraCamera, 1, 4, kParams_OneString_OneInt_OneOptionalString_OneOptionalInt);
// 
//DEFINE_COMMAND_PLUGIN(ProjectExtraCamera, 0, 5, kParams_TwoStrings_OneFloat_TwoOptionalInt);

//UInt32 s_texturePixelSize = 0x110;
//UInt32 s_projectPixelSize = 0x100;

//manages extra cameras
class ExtraCameraManager {
public:

	//functions
	static bool AttachExtraCamera(const char camName[0x40], bool doAttach, char nodeName = 0);
	static void GenerateExtraCameraTexture(TESObjectCELL* cell, NiCamera* camera, NiTexture* outTexture);
	static bool ProjectExtraCamera(const char camName[0x40], const char nodeName[0x40], float fov, UInt32 pixelSize = 0x100);

};
STATIC_ASSERT(std::is_empty_v<ExtraCameraManager>);

