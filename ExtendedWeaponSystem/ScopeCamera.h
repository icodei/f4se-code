#pragma once
#include "Global.h"

extern NiCamera* scopePOV;
extern NiNode* scopePOVRoot;
extern NiCamera* scopePOV_BACKUP;
extern NiNode* scopePOVRoot_BACKUP;


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
		DefaultState(TESCamera& cam, UInt32 ID);

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