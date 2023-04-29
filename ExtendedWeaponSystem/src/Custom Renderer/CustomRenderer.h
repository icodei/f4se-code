#pragma once
#include "Global.h"

#pragma region ScopeCamera

struct ScopeCameraStates {
	enum CameraState : unsigned {
		kDefault = 0,
		kThermal,
		kNightVision,

		kTotal
	};
};
using ScopeCameraState = ScopeCameraStates::CameraState;

class ScopeCamera : public TESCamera {	//TODO Add BSTEventSink as a baseclass???
public:
	class DefaultState : public TESCameraState {
	public:
		static constexpr auto STATE{ ScopeCameraState::kDefault };

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
		virtual void SaveGame([[maybe_unused]] BGSSaveFormBuffer* a_saveGameBuffer) override;
		virtual void LoadGame([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) override;
		virtual void Revert([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) override;

		//functions
		void SetInitialRotation(NiQuaternion& newRotation);
		void SetInitialPosition(NiPoint3& newPos);
		void SetRotation(NiQuaternion& newRotation);
		void SetTranslation(NiPoint3& newPos);
		void SetZoom(float newZoom);

		//members
		NiQuaternion initialRotation;
		NiPoint3 initialPosition;
		NiQuaternion rotation;
		NiPoint3 translation;
		float zoom;

		F4_HEAP_REDEFINE_NEW(ScopeCamera::DefaultState);
	};

	class ThermalState : public DefaultState {
	public:
		static constexpr auto STATE{ ScopeCameraState::kThermal };

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

		//functions

		//members

		F4_HEAP_REDEFINE_NEW(ScopeCamera::ThermalState);
	};

	class NightVisionState : public DefaultState {
	public:
		static constexpr auto STATE{ ScopeCameraState::kNightVision };

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

		//functions

		//members

		F4_HEAP_REDEFINE_NEW(ScopeCamera::NightVisionState);
	};

	ScopeCamera();
	ScopeCamera(bool createDefault);

	virtual ~ScopeCamera();

	virtual void SetCameraRoot(NiNode* node) override;
	virtual void SetEnabled(bool bEnabled) override;

	//functions
	void CreateDefault3D();
	bool IsInDefaultMode();
	bool IsInThermalMode();
	bool IsInNightVisionMode();
	void Reset();
	void SetState(TESCameraState* newCameraState);
	void StartCorrectState();
	void StartDefaultState();
	void StartThermalState();
	void StartNightVisionState();
	void Update3D();
	void UpdateCamera();
	
	//member access
	bool QCameraHasRenderPlane();

	//members
	BSTSmartPointer<TESCameraState> cameraStates[ScopeCameraState::kTotal];
	NiCamera* camera;
	BSGeometry* renderPlane;
	bool geometryDefault;

	F4_HEAP_REDEFINE_NEW(ScopeCamera);
};
#pragma endregion

class ScopeRenderer {
public:
	ScopeRenderer();
	~ScopeRenderer();

	//static functions
	static void RenderScopeScene(NiCamera* a_camera, BSShaderAccumulator* a_shaderAccumulator, uint32_t a_renderTarget, uint32_t a_depthTarget);

	//functions
	NiTexture* Render();
	NiTexture* RenderSimple();

	//members
	BSCullingProcess* pScopeCullingProc{ nullptr };
	ScopeCamera* pRendererCamera{ nullptr };
	BSShaderAccumulator* pScopeAccumulator{ nullptr };
	ImageSpaceShaderParam* pShaderParams;
	uint32_t renderTarget{ 19 };

	F4_HEAP_REDEFINE_NEW(ScopeRenderer);
};

class ScopeGeometry {
public:

	//functions
	void InitModels();

	//members
	BSFixedString rendererName;
};

namespace nsScope {

	//functions
	void CreateRenderer();
	void DestroyRenderer();
	ScopeRenderer* InitRenderer();
	void Render();

	//members
	extern ScopeRenderer* scopeRenderer;
	extern bool initialized;
}
