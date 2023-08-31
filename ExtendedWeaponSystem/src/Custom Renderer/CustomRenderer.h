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

class ScopeCamera : public TESCamera {  //TODO Add BSTEventSink as a baseclass???
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
		NiPoint3 initialPosition{ NiPoint3::ZERO };
		NiQuaternion rotation;
		NiPoint3 translation{ NiPoint3::ZERO };
		float zoom{ 1.0F };

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
	void SetFOV(float FOV);
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
	NiCamera* camera{ nullptr };
	BSGeometry* renderPlane{ nullptr };
	bool geometryDefault{ false };

	F4_HEAP_REDEFINE_NEW(ScopeCamera);
};
#pragma endregion

class ScopeCustomRenderer {
public:
	ScopeCustomRenderer();
	~ScopeCustomRenderer();

	//static functions
	static void RenderScopeScene(NiCamera* a_camera, BSShaderAccumulator* a_shaderAccumulator, uint32_t a_renderTarget, uint32_t a_depthTarget);

	//functions
	NiTexture* Render();
	NiTexture* RenderSimple();

	//members
	BSCullingProcess* pScopeCullingProc{ nullptr };
	ScopeCamera* pRendererCamera{ nullptr };
	BSShaderAccumulator* pScopeAccumulator{ nullptr };
	ImageSpaceShaderParam* pShaderParams{ nullptr };
	int32_t renderTarget{ stl::to_underlying<RenderTargetMode>(RenderTargetMode::RENDER_TARGET_GB_ALBEDO_SPEC) };
	int32_t depthTarget{ stl::to_underlying<DepthStencilTargetMode>(DepthStencilTargetMode::DEPTH_STENCIL_TARGET_MAIN) };
	int32_t effect{ stl::to_underlying<ImageSpaceManager::ImageSpaceEffectEnum>(ImageSpaceManager::ImageSpaceEffectEnum::kModMenu) };

	F4_HEAP_REDEFINE_NEW(ScopeCustomRenderer);
};

class ScopeLensModel {
public:
	ScopeLensModel();
	ScopeLensModel(int32_t a_target, int32_t a_swap);
	~ScopeLensModel();

	//functions
	void InitModels();
	void InitRenderer();
	void InitTargets();
	Interface3D::Renderer* GetRenderer();
	const BSFixedString GetRendererName() const;
	void Show(bool forceShow);
	void Hide();

	//FX functions
	void ChangeFOV(float FOV);
	void ClearFX();
	void DoNightVisionFX();
	void DoThermalFX();

	//members
	NiNode* renderRoot{ nullptr };       //TextureLoader
	BSGeometry* renderPlane{ nullptr };  //TextureLoader:0
	NiNode* scopeRoot{ nullptr };        //ScopeViewParts
	NiNode* rootNode{ nullptr };         //ScopeAiming
	int32_t renderTarget{ stl::to_underlying<RenderTargetMode>(RenderTargetMode::RENDER_TARGET_HUDGLASS) };
	int32_t swapTarget{ stl::to_underlying<RenderTargetMode>(RenderTargetMode::RENDER_TARGET_HUDGLASS_SWAP) };
	bool FXNoneActive{ true };
	bool FXNightVisionActive{ false };
	bool FXThermalActive{ false };
	bool visible{ false };

	F4_HEAP_REDEFINE_NEW(ScopeLensModel);
};

class ScopeReticleModel {
public:
	ScopeReticleModel();
	ScopeReticleModel(int32_t a_target, int32_t a_swap);
	~ScopeReticleModel();

	//functions
	void InitModels();
	void InitRenderer();
	void InitTargets();
	Interface3D::Renderer* GetRenderer();
	const BSFixedString GetRendererName() const;
	void Show(bool forceShow);
	void Hide();

	//members
	NiNode* reticleRoot{ nullptr };       //reticle_ui_stencil
	BSGeometry* reticlePlane{ nullptr };  //reticle_ui_stencil:0
	NiNode* scopeRoot{ nullptr };         //ScopeViewParts
	NiNode* rootNode{ nullptr };          //ScopeAiming
	int32_t renderTarget{ stl::to_underlying<RenderTargetMode>(RenderTargetMode::RENDER_TARGET_AO) };
	int32_t swapTarget{ stl::to_underlying<RenderTargetMode>(RenderTargetMode::RENDER_TARGET_AO_SWAP_0) };
	bool visible{ false };

	F4_HEAP_REDEFINE_NEW(ScopeReticleModel);
};

namespace ScopeRenderer {

	//Custom Renderer
	//The custom renderer will draw the world with FX inside the scope

	//custom renderer functions
	void CreateCustomRenderer();
	void DestroyCustomRenderer();
	ScopeCustomRenderer* InitCustomRenderer();
	void Render();

	//custom renderer members
	extern ScopeCustomRenderer* scopeCustomRenderer;
	extern bool customRendererInitialized;

	//interface3D renderer functions
	void CreateAllInterfaceRenderers();
	void DestroyAllInterfaceRenderers();
	void HideAllInterfaceRenderers();

	//Lens Renderer
	//The lens renderer will have the black circle depth effect that magnified scopes have

	//lens renderer functions
	void CreateLensRenderer();
	void DestroyLensRenderer();
	ScopeLensModel* InitLensRenderer();

	//lens renderer members
	extern ScopeLensModel* scopeLensRenderer;
	extern bool lensRendererInitialized;

	//Reticle Renderer
	//The reticle renderer will have the red dot sight effect

	//reticle renderer functions
	void CreateReticleRenderer();
	void DestroyReticleRenderer();
	ScopeReticleModel* InitReticleRenderer();

	//reticle renderer members
	extern ScopeReticleModel* scopeReticleRenderer;
	extern bool reticleRendererInitialized;

}
