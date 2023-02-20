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

	virtual void SetCameraRoot(NiNode* node) override;
	virtual void SetEnabled(bool enabled) override;
	virtual void Update() override;

	struct CameraStates {
		enum CameraState : unsigned {
			kDefault = 0,
			kThermal,
			kNightVision,

			kTotal
		};
	};
	using ScopeCameraState = CameraStates::CameraState;

	class DefaultState : public TESCameraState {
	public:
		static constexpr auto STATE{ ScopeCameraState::kDefault };

		DefaultState() = delete;
		DefaultState(TESCamera& cam, std::uint32_t ID);

		virtual ~DefaultState();

		virtual bool ShouldHandleEvent(const InputEvent* inputEvent = nullptr) override;
		virtual void HandleEvent(const KinectEvent* inputEvent) override;
		virtual void HandleEvent(const DeviceConnectEvent* inputEvent) override;
		virtual void HandleEvent(const ThumbstickEvent* inputEvent) override;
		virtual void HandleEvent(const CursorMoveEvent* inputEvent) override;
		virtual void HandleEvent(const MouseMoveEvent* inputEvent) override;
		virtual void HandleEvent(const CharacterEvent* inputEvent) override;
		virtual void HandleEvent(const ButtonEvent* inputEvent) override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;
		virtual void GetRotation(NiQuaternion& a_rotation) const override;
		virtual void GetTranslation(NiPoint3& a_translation) const override;
		virtual void SaveGame([[maybe_unused]] BGSSaveFormBuffer* a_saveGameBuffer) override;
		virtual void LoadGame([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) override;
		virtual void Revert([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) override;

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
		ThermalState(TESCamera& cam, std::uint32_t ID);

		virtual ~ThermalState();

		virtual bool ShouldHandleEvent(const InputEvent* inputEvent = nullptr) override;
		virtual void HandleEvent(const KinectEvent* inputEvent) override;
		virtual void HandleEvent(const DeviceConnectEvent* inputEvent) override;
		virtual void HandleEvent(const ThumbstickEvent* inputEvent) override;
		virtual void HandleEvent(const CursorMoveEvent* inputEvent) override;
		virtual void HandleEvent(const MouseMoveEvent* inputEvent) override;
		virtual void HandleEvent(const CharacterEvent* inputEvent) override;
		virtual void HandleEvent(const ButtonEvent* inputEvent) override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;
		virtual void GetRotation(NiQuaternion& a_rotation) const override;
		virtual void GetTranslation(NiPoint3& a_translation) const override;
		virtual void SaveGame([[maybe_unused]] BGSSaveFormBuffer* a_saveGameBuffer) override;
		virtual void LoadGame([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) override;
		virtual void Revert([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) override;

		//functions

		//member access

		//members
	};

	class NightVisionState : public DefaultState {
	public:
		NightVisionState() = delete;
		NightVisionState(TESCamera& cam, std::uint32_t ID);

		virtual ~NightVisionState();

		virtual bool ShouldHandleEvent(const InputEvent* inputEvent = nullptr) override;
		virtual void HandleEvent(const KinectEvent* inputEvent) override;
		virtual void HandleEvent(const DeviceConnectEvent* inputEvent) override;
		virtual void HandleEvent(const ThumbstickEvent* inputEvent) override;
		virtual void HandleEvent(const CursorMoveEvent* inputEvent) override;
		virtual void HandleEvent(const MouseMoveEvent* inputEvent) override;
		virtual void HandleEvent(const CharacterEvent* inputEvent) override;
		virtual void HandleEvent(const ButtonEvent* inputEvent) override;
		virtual void Begin() override;
		virtual void End() override;
		virtual void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;
		virtual void GetRotation(NiQuaternion& a_rotation) const override;
		virtual void GetTranslation(NiPoint3& a_translation) const override;
		virtual void SaveGame([[maybe_unused]] BGSSaveFormBuffer* a_saveGameBuffer) override;
		virtual void LoadGame([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) override;
		virtual void Revert([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) override;

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
	bool QCameraEquals(std::uint32_t cameraIndex);
	TESCameraState* QCameraState(std::uint32_t index);
	NiCamera* QRenderCamera();
	NiPoint3& QMaxExtent();
	NiPoint3& QMinExtent();

	//members
	BSTSmartPointer<TESCameraState> cameraStates[CameraStates::kTotal];
	NiPointer<NiCamera> camera;
	NiAVObject* renderPlane;
	NiPoint3 maxExtent;
	NiPoint3 minExtent;
};
