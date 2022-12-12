#pragma once
#include "Global.h"

class ScopeRenderer;
class ScopeCamera;

class ScopeCamera : public TESCamera {
public:
	ScopeCamera();

	virtual ~ScopeCamera();

	virtual void SetCameraNode(NiNode* node) override;
	virtual void SetEnabled(bool enabled) override;
	virtual void Update() override;
	
	enum {
		kCameraState_Default = 0,
		kCameraState_Thermal,
		kCameraState_NightVision,
		kNumCameraStates
	};

	class DefaultState : public TESCameraState {
	public:
		DefaultState() = delete;
		DefaultState(TESCamera & cam, UInt32 ID);

		virtual ~DefaultState();

		virtual bool ShouldHandleEvent(InputEvent* inputEvent = nullptr) override;
		virtual void OnKinectEvent(KinectEvent* inputEvent) override { };
		virtual void OnDeviceConnectEvent(DeviceConnectEvent* inputEvent) override { };
		virtual void OnThumbstickEvent(ThumbstickEvent* inputEvent) override { };
		virtual void OnCursorMoveEvent(CursorMoveEvent* inputEvent) override { };
		virtual void OnMouseMoveEvent(MouseMoveEvent* inputEvent) override { };
		virtual void OnCharacterEvent(CharacterEvent* inputEvent) override { };
		virtual void OnButtonEvent(ButtonEvent* inputEvent) override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Update(TESCameraState* arg) override;
		virtual void GetRotation(NiQuaternion* out) override;
		virtual void GetPosition(NiPoint3* out) override;
		virtual void SaveGame(BGSSaveFormBuffer* save) override { };
		virtual void LoadGame(BGSSaveFormBuffer* save) override { };
		virtual void Revert(BGSSaveFormBuffer* save) override { };

		//functions
		void SetInitialPosition(NiPoint3& newPos);
		void SetMinFrustum(float width, float height);
		void SetTranslation(NiPoint3& newPos);
		void SetZoom(float newZoom);

		//member access
		NiQuaternion& QInitialRotation();
		NiPoint3& QInitialPosition();
		NiQuaternion& QRotation();
		NiPoint3& QTranslation();

		//members
		NiQuaternion initialRotation;
		NiPoint3 initialPosition;
		NiQuaternion rotation;
		NiPoint3 translation;
		float zoom;
		float minFrustumHalfWidth;
		float minFrustumHalfHeight;
	};

	class ThermalState : public DefaultState {
	public:
		ThermalState() = delete;
		ThermalState(TESCamera& cam, UInt32 ID);

		virtual ~ThermalState();

		virtual bool ShouldHandleEvent(InputEvent* inputEvent = nullptr) override;
		virtual void OnKinectEvent(KinectEvent* inputEvent) override { };
		virtual void OnDeviceConnectEvent(DeviceConnectEvent* inputEvent) override { };
		virtual void OnThumbstickEvent(ThumbstickEvent* inputEvent) override { };
		virtual void OnCursorMoveEvent(CursorMoveEvent* inputEvent) override { };
		virtual void OnMouseMoveEvent(MouseMoveEvent* inputEvent) override { };
		virtual void OnCharacterEvent(CharacterEvent* inputEvent) override { };
		virtual void OnButtonEvent(ButtonEvent* inputEvent) override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Update(TESCameraState* arg) override;
		virtual void GetRotation(NiQuaternion* out) override;
		virtual void GetPosition(NiPoint3* out) override;
		virtual void SaveGame(BGSSaveFormBuffer* save) override { };
		virtual void LoadGame(BGSSaveFormBuffer* save) override { };
		virtual void Revert(BGSSaveFormBuffer* save) override { };

		//functions

		//member access

		//members
	};

	class NightVisionState : public DefaultState {
	public:
		NightVisionState() = delete;
		NightVisionState(TESCamera& cam, UInt32 ID);

		virtual ~NightVisionState();

		virtual bool ShouldHandleEvent(InputEvent* inputEvent = nullptr) override;
		virtual void OnKinectEvent(KinectEvent* inputEvent) override { };
		virtual void OnDeviceConnectEvent(DeviceConnectEvent* inputEvent) override { };
		virtual void OnThumbstickEvent(ThumbstickEvent* inputEvent) override { };
		virtual void OnCursorMoveEvent(CursorMoveEvent* inputEvent) override { };
		virtual void OnMouseMoveEvent(MouseMoveEvent* inputEvent) override { };
		virtual void OnCharacterEvent(CharacterEvent* inputEvent) override { };
		virtual void OnButtonEvent(ButtonEvent* inputEvent) override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Update(TESCameraState* arg) override;
		virtual void GetRotation(NiQuaternion* out) override;
		virtual void GetPosition(NiPoint3* out) override;
		virtual void SaveGame(BGSSaveFormBuffer* save) override { };
		virtual void LoadGame(BGSSaveFormBuffer* save) override { };
		virtual void Revert(BGSSaveFormBuffer* save) override { };

		//functions

		//member access

		//members
	};

	//functions
	void Init3D();
	void Reset();
	void SetExtents(NiPoint3& min, NiPoint3& max);
	void SetState(TESCameraState* newCameraState);
	void Update3D();

	//member access
	bool QCameraEquals(UInt32 cameraIndex);
	TESCameraState* QCameraState(UInt32 index);
	NiCamera* QRenderCamera();
	NiPoint3& QMaxExtent();
	NiPoint3& QMinExtent();

	//members
	TESCameraState* cameraStates[kNumCameraStates];
	NiPointer<NiCamera> camera;
	NiAVObject* renderPlane;
	NiPoint3 maxExtent;
	NiPoint3 minExtent;

};

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

//UInt32 s_texturePixelSize = 0x110;
//UInt32 s_projectPixelSize = 0x100;

//uses stuff from JiP for reference
//manages extra cameras
class ExtraCameraManager {
public:

	//functions
	static bool AttachExtraCamera(const char camName[0x40], bool doAttach, char nodeName = 0);
	static void GenerateExtraCameraTexture(TESObjectCELL* cell, NiCamera* camera, NiTexture* outTexture);
	static bool ProjectExtraCamera(const char camName[0x40], const char nodeName[0x40], float fov, UInt32 pixelSize = 0x100);

};
STATIC_ASSERT(std::is_empty_v<ExtraCameraManager>);

