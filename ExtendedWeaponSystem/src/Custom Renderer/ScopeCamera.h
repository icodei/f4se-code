#pragma once
#include "Global.h"

struct ScopeCameraStates {
	enum CameraState : unsigned {
		kDefault = 0,
		kThermal,
		kNightVision,

		kTotal
	};
};
using ScopeCameraState = ScopeCameraStates::CameraState;

class ScopeCamera : public TESCamera {
public:
	

	class DefaultState : public TESCameraState {
	public:
		static constexpr auto STATE{ ScopeCameraStates::kDefault };

		DefaultState() = delete;
		DefaultState(TESCamera& cam, uint32_t ID);

		virtual ~DefaultState();

		virtual bool ShouldHandleEvent(const InputEvent* inputEvent = nullptr) override;
		virtual void HandleThumbstickEvent(const ThumbstickEvent* inputEvent) override;
		virtual void HandleCursorMoveEvent(const CursorMoveEvent* inputEvent) override;
		virtual void HandleMouseMoveEvent(const MouseMoveEvent* inputEvent) override;
		virtual void HandleButtonEvent(const ButtonEvent* inputEvent) override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;
		virtual void GetRotation(NiQuaternion& a_rotation) const override;
		virtual void GetTranslation(NiPoint3& a_translation) const override;

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

		F4_HEAP_REDEFINE_NEW(ScopeCamera::DefaultState);
	};

	class ThermalState : public DefaultState {
	public:
		static constexpr auto STATE{ ScopeCameraStates::kThermal };

		ThermalState() = delete;
		ThermalState(TESCamera& cam, uint32_t ID);

		virtual ~ThermalState();

		virtual bool ShouldHandleEvent(const InputEvent* inputEvent = nullptr) override;
		virtual void HandleThumbstickEvent(const ThumbstickEvent* inputEvent) override;
		virtual void HandleCursorMoveEvent(const CursorMoveEvent* inputEvent) override;
		virtual void HandleMouseMoveEvent(const MouseMoveEvent* inputEvent) override;
		virtual void HandleButtonEvent(const ButtonEvent* inputEvent) override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;
		virtual void GetRotation(NiQuaternion& a_rotation) const override;
		virtual void GetTranslation(NiPoint3& a_translation) const override;

		//functions

		//member access

		//members

		F4_HEAP_REDEFINE_NEW(ScopeCamera::ThermalState);
	};

	class NightVisionState : public DefaultState {
	public:
		static constexpr auto STATE{ ScopeCameraStates::kNightVision };

		NightVisionState() = delete;
		NightVisionState(TESCamera& cam, uint32_t ID);

		virtual ~NightVisionState();

		virtual bool ShouldHandleEvent(const InputEvent* inputEvent = nullptr) override;
		virtual void HandleThumbstickEvent(const ThumbstickEvent* inputEvent) override;
		virtual void HandleCursorMoveEvent(const CursorMoveEvent* inputEvent) override;
		virtual void HandleMouseMoveEvent(const MouseMoveEvent* inputEvent) override;
		virtual void HandleButtonEvent(const ButtonEvent* inputEvent) override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;
		virtual void GetRotation(NiQuaternion& a_rotation) const override;
		virtual void GetTranslation(NiPoint3& a_translation) const override;

		//functions

		//member access

		//members

		F4_HEAP_REDEFINE_NEW(ScopeCamera::NightVisionState);
	};

	ScopeCamera();

	virtual ~ScopeCamera();

	virtual void SetCameraRoot(NiNode* node) override;
	virtual void SetEnabled(bool bEnabled) override;
	virtual void Update() override;

	//functions
	void CreateDefault3D();
	void Reset();
	void SetExtents(NiPoint3& min, NiPoint3& max);
	void SetState(TESCameraState* newCameraState);
	void Update3D();

	//member access
	bool QCameraEquals(uint32_t cameraIndex);
	TESCameraState* QCameraState(uint32_t index);
	NiCamera* QRenderCamera();
	NiPoint3& QMaxExtent();
	NiPoint3& QMinExtent();

	//members
	BSTSmartPointer<TESCameraState> cameraStates[ScopeCameraStates::kTotal];
	NiCamera* camera;
	BSGeometry* renderPlane;
	NiPoint3 maxExtent;
	NiPoint3 minExtent;

	F4_HEAP_REDEFINE_NEW(ScopeCamera);
};
