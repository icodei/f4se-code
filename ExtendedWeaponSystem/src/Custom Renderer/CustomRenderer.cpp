#include "Custom Renderer/CustomRenderer.h"

#include "Custom Renderer/ScopeGeometry.h"
#include "Util.h"
#include "WeaponHandlers.h"

#pragma region ScopeCamera

ScopeCamera::ScopeCamera() :
	TESCamera() {
	logInfo("ScopeCamera ctor Starting...");

	DefaultState* camDefaultState;
	ThermalState* camThermalState;
	NightVisionState* camNightVisionState;
	TESCameraState* oldCamState;

	//defaultState init
	camDefaultState = (DefaultState*)RE::malloc(sizeof(DefaultState));
	if (camDefaultState) {
		new (camDefaultState) DefaultState(*this, ScopeCameraStates::kDefault);
		cameraStates[ScopeCameraStates::kDefault].reset(camDefaultState);
		logInfo("ScopeCamera - Created ScopeCamera::DefaultState");
	} else {
		camDefaultState = nullptr;
		auto error = "- ScopeCamera::DefaultState Creation FAILED"sv;
		logError(fmt::format(FMT_STRING(";{0: ^{1}};"), (ASSERT(error)), 80));
	}
	//thermalState init
	camThermalState = (ThermalState*)RE::malloc(sizeof(ThermalState));
	if (camThermalState) {
		new (camThermalState) ThermalState(*this, ScopeCameraStates::kThermal);
		cameraStates[ScopeCameraStates::kThermal].reset(camThermalState);
		logInfo("ScopeCamera - Created ScopeCamera::ThermalState");
	} else {
		camThermalState = nullptr;
		auto error = "- ScopeCamera::ThermalState Creation FAILED"sv;
		logError(fmt::format(FMT_STRING(";{0: ^{1}};"), (ASSERT(error)), 80));
	}
	//nightVisionState init
	camNightVisionState = (NightVisionState*)RE::malloc(sizeof(NightVisionState));
	if (camNightVisionState) {
		new (camNightVisionState) NightVisionState(*this, ScopeCameraStates::kNightVision);
		cameraStates[ScopeCameraStates::kNightVision].reset(camNightVisionState);
		logInfo("ScopeCamera - Created ScopeCamera::NightVisionState");
	} else {
		camNightVisionState = nullptr;
		auto error = "- ScopeCamera::NightVisionState Creation FAILED"sv;
		logError(fmt::format(FMT_STRING(";{0: ^{1}};"), (ASSERT(error)), 80));
	}

	//oldState
	oldCamState = currentState.get();
	if (camDefaultState != oldCamState) {
		if (camDefaultState) {
			InterlockedIncrement(&camDefaultState->refCount);
		}
		currentState.reset(camDefaultState);
		if (oldCamState && !InterlockedDecrement(&oldCamState->refCount)) {
			oldCamState->~TESCameraState();
		}
	}

	//set state to default
	this->SetState(cameraStates[ScopeCameraStates::kDefault].get());
	logInfo("ScopeCamera ctor Completed.");
}

ScopeCamera::ScopeCamera(bool createDefault) :
	ScopeCamera() {
	if (createDefault) {
		CreateDefault3D();
	} else {
		camera = nullptr;
		renderPlane = nullptr;
		geometryDefault = false;
	}
}

ScopeCamera::~ScopeCamera() {
	TESCameraState* current;
	TESCameraState* state;

	NiNode* root;

	current = currentState.get();
	if (current) {
		current->End();
	}

	auto stateA = cameraStates;
	uint32_t total = ScopeCameraState::kTotal;
	do {
		state = stateA->get();
		if (stateA->get()) {
			stateA->~BSTSmartPointer();
			if (!InterlockedDecrement(&state->refCount)) {
				state->~TESCameraState();
			}
		}
		++stateA;
		--total;
	} while (total);

	//Geometry was created by us and needs to be destroyed
	if (geometryDefault) {
		if (!InterlockedDecrement(&camera->refCount)) {
			camera->DeleteThis();
		}
		if (!InterlockedDecrement(&renderPlane->refCount)) {
			renderPlane->DeleteThis();
		}
	}

	camera = nullptr;
	renderPlane = nullptr;

	root = cameraRoot.get();
	if (root) {
		if (!InterlockedDecrement(&root->refCount)) {
			root->DeleteThis();
		}
	}
}

void ScopeCamera::SetCameraRoot(NiNode* newRoot) {
	NiNode* currentRoot;

	currentRoot = cameraRoot.get();
	if (currentRoot != newRoot) {
		if (newRoot) {
			InterlockedIncrement(&newRoot->refCount);
		}
		cameraRoot = newRoot;
		if (currentRoot) {
			if (!InterlockedDecrement(&currentRoot->refCount)) {
				currentRoot->DeleteThis();
			}
		}
	}
}

void ScopeCamera::SetEnabled(bool bEnabled) {  //TODO
	enabled = bEnabled;
}

bool ScopeCamera::QCameraHasRenderPlane() {
	return renderPlane;
}

void ScopeCamera::CreateDefault3D() {
	NiCamera* cam;
	NiCamera* oldCam;
	NiCamera* newCam;
	NiCamera* currentCam;

	//cam = (NiCamera*)RE::malloc(0x1A0);
	cam = NiCamera::Create();
	if (cam) {
		newCam = cam;
		logInfo("ScopeCamera - Created NiCamera");
	} else {
		newCam = nullptr;
		auto error = "- NiCamera Creation FAILED"sv;
		logError(fmt::format(FMT_STRING(";{0: ^{1}};"), (ASSERT(error)), 80));
	}
	currentCam = camera;
	if (camera != newCam) {
		oldCam = camera;
		if (newCam) {
			InterlockedIncrement(&newCam->refCount);
		}
		currentCam = newCam;
		camera = newCam;
		if (oldCam) {
			if (!InterlockedDecrement(&oldCam->refCount)) {
				oldCam->DeleteThis();
			}
			currentCam = camera;
		}
	}

	BSGraphics::State* pGraphicsState = &BSGraphics::State::GetSingleton();
	float widthRatio = pGraphicsState->uiBackBufferWidth / pGraphicsState->uiBackBufferHeight;

	NiFrustum updatedFrustum{ NiFrustum(0) };
	updatedFrustum.nearPlane = 1.0F;
	updatedFrustum.farPlane = 10000.0F;
	updatedFrustum.leftPlane = widthRatio * -0.5F;
	updatedFrustum.rightPlane = widthRatio * 0.5F;
	updatedFrustum.bottomPlane = -0.5F;
	updatedFrustum.topPlane = 0.5F;
	updatedFrustum.ortho = false;
	camera->SetViewFrustum(updatedFrustum);

	//more camera setup needed?

	NiNode* currentNode;
	NiNode* newNode;
	NiNode* node;

	node = (NiNode*)RE::malloc(0x140);
	//node = NiNode::Create();
	if (node) {
		new (node) NiNode(1);
		newNode = node;
		logInfo("ScopeCamera - Created NiNode");
	} else {
		newNode = nullptr;
		auto error = "- NiNode Creation FAILED"sv;
		logError(fmt::format(FMT_STRING(";{0: ^{1}};"), (ASSERT(error)), 80));
	}
	currentNode = cameraRoot.get();
	if (currentNode != newNode) {
		if (newNode) {
			InterlockedIncrement(&newNode->refCount);
		}
		cameraRoot = newNode;
		if (currentNode && !InterlockedDecrement(&currentNode->refCount)) {
			currentNode->DeleteThis();
		}
	}
	cameraRoot->AttachChild(camera, true);

	BSGeometry* geo;
	BSGeometry* newGeo;
	BSGeometry* currentGeo;

	geo = CreateScreenQuadShape(0, 1, 0, 1);
	//geo = (BSGeometry*)RE::malloc(0x160);
	if (geo) {
		//new (geo) BSGeometry();
		newGeo = geo;
		logInfo("ScopeCamera - Created BSTriShape");
	} else {
		newGeo = nullptr;
		auto error = "- BSTriShape Creation FAILED"sv;
		logError(fmt::format(FMT_STRING(";{0: ^{1}};"), (ASSERT(error)), 80));
	}
	currentGeo = renderPlane;
	if (currentGeo != newGeo) {
		if (newGeo) {
			InterlockedIncrement(&newGeo->refCount);
		}
		renderPlane = newGeo;
		if (currentGeo && !InterlockedDecrement(&currentGeo->refCount)) {
			currentGeo->DeleteThis();
		}
	}
	geometryDefault = true;

	//Needs aditional setup for the default render plane
	//lightingshaderproperty or effectshaderproperty needs to be made
	//position of render plane needs to be done
}

bool ScopeCamera::IsInDefaultMode() {
	TESCameraState* defaultState;

	defaultState = cameraStates[ScopeCameraState::kDefault].get();
	if (currentState.get() == defaultState) {
		return currentState.get() == defaultState;
	}
	return false;
}

bool ScopeCamera::IsInThermalMode() {
	TESCameraState* thermalState;

	thermalState = cameraStates[ScopeCameraState::kThermal].get();
	if (currentState.get() == thermalState) {
		return currentState.get() == thermalState;
	}
	return false;
}

bool ScopeCamera::IsInNightVisionMode() {
	TESCameraState* nightVisionState;

	nightVisionState = cameraStates[ScopeCameraState::kNightVision].get();
	if (currentState.get() == nightVisionState) {
		return currentState.get() == nightVisionState;
	}
	return false;
}

void ScopeCamera::Reset() {
	currentState->Begin();
}

void ScopeCamera::SetFOV(float FOV) {
	BSGraphics::State* pGraphicsState = &BSGraphics::State::GetSingleton();

	if (camera) {
		NiFrustum newFrustum = new NiFrustum();

		newFrustum.nearPlane = 1.0F;
		newFrustum.farPlane = 10240.0F;
		camera->maxFarNearRatio = newFrustum.farPlane / newFrustum.nearPlane;
		float ratio = pGraphicsState->uiBackBufferHeight / pGraphicsState->uiBackBufferWidth;
		float stuff = tanf((DEG_TO_RAD * FOV) * 0.15F);
		newFrustum.rightPlane = stuff * 0.75F;
		newFrustum.leftPlane = -(stuff * 0.75F);
		newFrustum.topPlane = (stuff * ratio) * 0.75F;
		newFrustum.bottomPlane = -(newFrustum.topPlane);
		newFrustum.ortho = false;

		camera->SetViewFrustum(newFrustum);
	}
}

void ScopeCamera::SetState(TESCameraState* newCameraState) {
	TESCameraState* lastState;
	TESCameraState* oldState;
	TESCameraState* newState;

	lastState = currentState.get();
	if (lastState) {
		lastState->End();
	}
	oldState = currentState.get();
	if (newCameraState != oldState) {
		if (newCameraState) {
			InterlockedIncrement(&newCameraState->refCount);
		}
		currentState.reset(newCameraState);
		if (oldState && !InterlockedDecrement(&oldState->refCount)) {
			oldState->~TESCameraState();
		}
	}
	newState = currentState.get();
	if (newState) {
		newState->Begin();
	}
}

void ScopeCamera::StartCorrectState() {
	if (WeaponHasNoSpecialScopes()) {
		auto error = "was called and could not find the correct state to start"sv;
		logError(fmt::format(FMT_STRING(";{0: ^{1}};"), (ASSERT(error)), 80));
		return;
	}
	if (weaponHasScopeThermal) {
		StartThermalState();
		goto FoundState;
	}
	if (weaponHasScopeNV) {
		StartNightVisionState();
		goto FoundState;
	}
	if (weaponHasScopePIP) {
		StartDefaultState();
		goto FoundState;
	}
FoundState:
	{
		UpdateCamera();
		return;
	}
}

void ScopeCamera::StartDefaultState() {
	TESCameraState* newState = cameraStates[ScopeCameraState::kDefault].get();
	SetState(newState);
}

void ScopeCamera::StartThermalState() {
	TESCameraState* newState = cameraStates[ScopeCameraState::kThermal].get();
	SetState(newState);
}

void ScopeCamera::StartNightVisionState() {
	TESCameraState* newState = cameraStates[ScopeCameraState::kNightVision].get();
	SetState(newState);
}

void ScopeCamera::Update3D() {
	BSGeometry* geom;
	BSGeometry* newGeom;
	BSGeometry* oldGeom;

	const BSFixedString geomName = "TextureLoader:0";

	logInfo("Looking for new camera and geometry...");

	geom = (BSGeometry*)GetByNameFromPlayer3D(geomName);
	if (geom) {
		logInfo("Found the geometry of the scope.");
		newGeom = geom;
	} else {
		logWarn("Could not find the geometry of the scope.");
		newGeom = nullptr;
	}
	oldGeom = renderPlane;
	if (renderPlane != newGeom) {
		if (newGeom) {
			renderPlane = newGeom;
		}

		if (oldGeom) {
		}
	}

	NiCamera* cam;
	NiCamera* newCam;
	NiCamera* oldCam;

	const BSFixedString camName = "ScopePOV";

	cam = (NiCamera*)GetByNameFromPlayer3D(camName);
	if (cam) {
		logInfo("Found the scope camera.");
		newCam = cam;
	} else {
		logWarn("Could not find the camera of the scope.");
		newCam = nullptr;
	}
	oldCam = camera;
	if (camera != newCam) {
		if (newCam) {
			camera = newCam;
			SetCameraRoot(camera->parent);
		}

		if (oldCam) {
		}
	}

	StartCorrectState();

	//TODO: add actor value or something similar to set what the FOV should be on the camera of each scope
	SetFOV(90.0F / 4.0F);
}

void ScopeCamera::UpdateCamera() {
	if (!enabled) {
		return;
	}

	if (!QCameraHasRenderPlane()) {
		Update3D();
	}

	TESCameraState* pCurrentState = currentState.get();
	if (pCurrentState == cameraStates[ScopeCameraState::kDefault].get()) {
		((ScopeCamera::DefaultState*)pCurrentState)->Update(currentState);
	}
	if (pCurrentState == cameraStates[ScopeCameraState::kThermal].get()) {
		((ScopeCamera::ThermalState*)pCurrentState)->Update(currentState);
	}
	if (pCurrentState == cameraStates[ScopeCameraState::kNightVision].get()) {
		((ScopeCamera::NightVisionState*)pCurrentState)->Update(currentState);
	}
}

ScopeCamera::DefaultState::DefaultState(TESCamera& cam, std::uint32_t ID) :
	TESCameraState(cam, ID) {
	logInfo("ScopeCamera::State ctor Starting...");
	refCount = 0;
	camera = &cam;
	id = ID;

	initialRotation.w = 0.0F;
	initialRotation.x = 0.0F;
	initialRotation.y = 0.0F;
	initialRotation.z = 0.0F;
	initialPosition = NiPoint3::ZERO;
	rotation.w = 0.0F;
	rotation.x = 0.0F;
	rotation.y = 0.0F;
	rotation.z = 0.0F;
	translation = NiPoint3::ZERO;
	zoom = 1.0F;
}

ScopeCamera::DefaultState::~DefaultState() {
}

bool ScopeCamera::DefaultState::ShouldHandleEvent(const InputEvent* inputEvent) {  //TODO
	return false;                                                                  //TEMP
}

void ScopeCamera::DefaultState::HandleThumbstickEvent(const ThumbstickEvent* inputEvent) {
}

void ScopeCamera::DefaultState::HandleCursorMoveEvent(const CursorMoveEvent* inputEvent) {
}

void ScopeCamera::DefaultState::HandleMouseMoveEvent(const MouseMoveEvent* inputEvent) {
}

void ScopeCamera::DefaultState::HandleButtonEvent(const ButtonEvent* inputEvent) {  //TODO
}

void ScopeCamera::DefaultState::Begin() {  //TODO: Add new members
	translation = NiPoint3::ZERO;
	zoom = 1.0F;
}

void ScopeCamera::DefaultState::End() {  //TODO
}

void ScopeCamera::DefaultState::Update(BSTSmartPointer<TESCameraState>& a_nextState) {
	NiPoint3 updatedTranslation;
	NiQuaternion updatedQuatRotation;
	NiMatrix3 updatedRotation;

	NiPointer<NiNode> spCameraRoot = nullptr;
	NiNode* pCameraRoot = nullptr;

	NiUpdateData updateData{ NiUpdateData(0.0F, 0) };

	GetTranslation(updatedTranslation);
	GetRotation(updatedQuatRotation);

	if (camera->GetCameraRoot(spCameraRoot)) {
		updatedQuatRotation.ToRotation(updatedRotation);

		pCameraRoot->local.rotate.entry[0] = updatedRotation.entry[0];
		pCameraRoot->local.rotate.entry[1] = updatedRotation.entry[1];
		pCameraRoot->local.rotate.entry[2] = updatedRotation.entry[2];
		pCameraRoot->local.translate = updatedTranslation;
		pCameraRoot->Update(updateData);
	}

	float newZoom = camera->zoomInput + zoom;
	if (newZoom <= 1.0F) {
		if (newZoom < 0.0F) {
			newZoom = 0.0F;
		}
	} else {
		newZoom = 1.0F;
	}
	zoom = newZoom;

	//delete the default created node of the nismartpointer???
	NiNode* oldCameraRoot = spCameraRoot.get();
	if (spCameraRoot.get()) {
		if (!InterlockedDecrement(&spCameraRoot->refCount)) {
			oldCameraRoot->DeleteThis();
		}
	}
}

void ScopeCamera::DefaultState::GetRotation(NiQuaternion& a_rotation) const {
	a_rotation = rotation;
}

void ScopeCamera::DefaultState::GetTranslation(NiPoint3& a_translation) const {
	a_translation = translation;
}

void ScopeCamera::DefaultState::SaveGame(BGSSaveFormBuffer* a_saveGameBuffer) {
}

void ScopeCamera::DefaultState::LoadGame(BGSLoadFormBuffer* a_loadGameBuffer) {
}

void ScopeCamera::DefaultState::Revert(BGSLoadFormBuffer* a_loadGameBuffer) {
}

void ScopeCamera::DefaultState::SetInitialRotation(NiQuaternion& newRotation) {
	initialRotation = newRotation;
}

void ScopeCamera::DefaultState::SetInitialPosition(NiPoint3& newPos) {
	initialPosition = newPos;
}

void ScopeCamera::DefaultState::SetRotation(NiQuaternion& newRotation) {
	rotation = newRotation;
}

void ScopeCamera::DefaultState::SetTranslation(NiPoint3& newPos) {
	translation = newPos;
}

void ScopeCamera::DefaultState::SetZoom(float newZoom) {
	zoom = newZoom;
}

ScopeCamera::ThermalState::ThermalState(TESCamera& cam, std::uint32_t ID) :
	DefaultState(cam, ID) {
	logInfo("ScopeCamera::ThermalState ctor Completed.");
}

ScopeCamera::ThermalState::~ThermalState() {
}

bool ScopeCamera::ThermalState::ShouldHandleEvent(const InputEvent* inputEvent) {
	return false;
}

void ScopeCamera::ThermalState::HandleThumbstickEvent(const ThumbstickEvent* inputEvent) {
}

void ScopeCamera::ThermalState::HandleCursorMoveEvent(const CursorMoveEvent* inputEvent) {
}

void ScopeCamera::ThermalState::HandleMouseMoveEvent(const MouseMoveEvent* inputEvent) {
}

void ScopeCamera::ThermalState::HandleButtonEvent(const ButtonEvent* inputEvent) {
}

void ScopeCamera::ThermalState::Begin() {
}

void ScopeCamera::ThermalState::End() {
}

void ScopeCamera::ThermalState::Update(BSTSmartPointer<TESCameraState>& a_nextState) {
}

ScopeCamera::NightVisionState::NightVisionState(TESCamera& cam, std::uint32_t ID) :
	DefaultState(cam, ID) {
	logInfo("ScopeCamera::NightVisionState ctor Completed.");
}

ScopeCamera::NightVisionState::~NightVisionState() {
}

bool ScopeCamera::NightVisionState::ShouldHandleEvent(const InputEvent* inputEvent) {  //TODO
	return false;
}

void ScopeCamera::NightVisionState::HandleThumbstickEvent(const ThumbstickEvent* inputEvent) {
}

void ScopeCamera::NightVisionState::HandleCursorMoveEvent(const CursorMoveEvent* inputEvent) {
}

void ScopeCamera::NightVisionState::HandleMouseMoveEvent(const MouseMoveEvent* inputEvent) {
}

void ScopeCamera::NightVisionState::HandleButtonEvent(const ButtonEvent* inputEvent) {
}

void ScopeCamera::NightVisionState::Begin() {
}

void ScopeCamera::NightVisionState::End() {
}

void ScopeCamera::NightVisionState::Update(BSTSmartPointer<TESCameraState>& a_nextState) {
}

#pragma endregion

#pragma region ScopeCustomRenderer

ScopeCustomRenderer::ScopeCustomRenderer() {
	logInfo("ScopeCustomRenderer ctor Starting...");

	BSShaderAccumulator* shaderAccum;
	BSShaderAccumulator* newShaderAccum;
	BSShaderAccumulator* oldShaderAccum;

	logInfo("ScopeCustomRenderer - Creating BSCullingProcess...");
	pScopeCullingProc = (BSCullingProcess*)RE::malloc(0x1A0);
	if (pScopeCullingProc) {
		new (pScopeCullingProc) BSCullingProcess(0);
	} else {
		pScopeCullingProc = nullptr;
		logError("ScopeCustomRenderer - BSCullingProcess Creation FAILED");
	}

	logInfo("ScopeCustomRenderer - Creating ScopeCamera...");
	pRendererCamera = (ScopeCamera*)RE::malloc(sizeof(ScopeCamera));
	if (pRendererCamera) {
		new (pRendererCamera) ScopeCamera(false);
	} else {
		logError("ScopeCustomRenderer - ScopeCamera Creation FAILED");
	}

	logInfo("ScopeCustomRenderer - Creating ImageSpaceShaderParam...");
	pShaderParams = (ImageSpaceShaderParam*)RE::malloc(0x90);
	if (pShaderParams) {
		new (pShaderParams) ImageSpaceShaderParam();
	} else {
		logError("ScopeCustomRenderer - ImageSpaceShaderParam Creation FAILED");
		pShaderParams = &BSImagespaceShader::GetDefaultParam();
	}

	shaderAccum = (BSShaderAccumulator*)RE::malloc(0x590);
	if (shaderAccum) {
		new (shaderAccum) BSShaderAccumulator();
		newShaderAccum = shaderAccum;
		logInfo("ScopeCustomRenderer - Created BSShaderAccumulator");
	} else {
		newShaderAccum = nullptr;
		logError("ScopeCustomRenderer - BSShaderAccumulator Creation FAILED");
	}
	oldShaderAccum = pScopeAccumulator;
	if ((oldShaderAccum != newShaderAccum) || (!pScopeAccumulator)) {
		if (newShaderAccum) {
			InterlockedIncrement(&newShaderAccum->refCount);
		}
		pScopeAccumulator = newShaderAccum;
		if (oldShaderAccum && !InterlockedDecrement(&oldShaderAccum->refCount)) {
			oldShaderAccum->DeleteThis();
		}
	}
	pScopeAccumulator->ZPrePass = true;
	pScopeAccumulator->activeShadowSceneNode = BSShaderManager::State::GetSingleton().pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD];
	pScopeAccumulator->SilhouetteColor = NiColorA::WHITE;
	pScopeCullingProc->SetAccumulator(pScopeAccumulator);
	pScopeCullingProc->kCullMode = BSCullingProcess::BSCP_CULL_IGNOREMULTIBOUNDS;
	pScopeCullingProc->bCameraRelatedUpdates = true;
	//pShaderParams->ResizeConstantGroup(0, 1); //CTD
	renderTarget = 19;

	logInfo("ScopeCustomRenderer ctor Completed.");
}

ScopeCustomRenderer::~ScopeCustomRenderer() {
	logInfo("ScopeCustomRenderer dtor Starting...");
	BSShaderAccumulator* shaderAccum;
	NiCamera* cam;
	TESCameraState* state;

	pShaderParams->~ImageSpaceShaderParam();
	shaderAccum = pScopeAccumulator;
	if (shaderAccum && !InterlockedDecrement(&shaderAccum->refCount)) {
		shaderAccum->DeleteThis();
	}
	cam = pRendererCamera->camera;
	if (cam && !InterlockedDecrement(&cam->refCount)) {
		cam->DeleteThis();
	}
	state = pRendererCamera->currentState.get();
	if (state && !InterlockedDecrement(&state->refCount)) {
		state->~TESCameraState();
	}
	pRendererCamera->~ScopeCamera();
	pScopeCullingProc->SetAccumulator(nullptr);
	pScopeCullingProc->~BSCullingProcess();
	logInfo("ScopeCustomRenderer dtor Completed.");
}

void ScopeCustomRenderer::RenderScopeScene(NiCamera* a_camera, BSShaderAccumulator* a_shaderAccumulator, uint32_t a_renderTarget, uint32_t a_depthTarget) {
	BSGraphics::State* pGraphicsState = &BSGraphics::State::GetSingleton();
	BSGraphics::RenderTargetManager* pTargetManager = &BSGraphics::RenderTargetManager::GetSingleton();
	BSGraphics::Renderer* pRenderData = &BSGraphics::Renderer::GetSingleton();
	BSShaderManager::State* pShaderState = &BSShaderManager::State::GetSingleton();

	pTargetManager->SetCurrentDepthStencilTarget(a_depthTarget, BSGraphics::SetRenderTargetMode::SRTM_FORCE_COPY_RESTORE, 0, false);
	pTargetManager->SetCurrentRenderTarget(0, a_renderTarget, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);                                                                   //ALBEDO
	pTargetManager->SetCurrentRenderTarget(1, stl::to_underlying<RenderTargetMode>(RenderTargetMode::RENDER_TARGET_GB_NORMAL), BSGraphics::SetRenderTargetMode::SRTM_CLEAR);  //NORMAL
	pTargetManager->SetCurrentRenderTarget(2, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);                                                                               //ENVMAP
	pTargetManager->SetCurrentRenderTarget(3, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);                                                                               //AMBIENT
	if (pShaderState->bDeferredRGBEmit) {
		pTargetManager->SetCurrentRenderTarget(4, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);  //EMIT
	}
	pTargetManager->SetCurrentRenderTarget(5, -1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);  //MOTION_VECTORS
	pTargetManager->SetCurrentViewportForceToRenderTargetDimensions();
	pRenderData->SetClearColor(0.0F, 0.0F, 0.0F, 0.0F);
	pRenderData->ClearColor();
	pRenderData->Flush();
	pGraphicsState->SetCameraData(a_camera, false, 0.0F, 1.0F);
	pRenderData->DoZPrePass(nullptr, nullptr, 0.0F, 1.0F, 0.0F, 1.0F);
	a_shaderAccumulator->RenderOpaqueDecals();
	a_shaderAccumulator->RenderBatches(4, false, -1);
	a_shaderAccumulator->RenderBlendedDecals();
	pRenderData->Flush();
	pRenderData->SetClearColor(0.2F, 0.2F, 0.2F, 1.0F);
	a_shaderAccumulator->ClearEffectPasses();
	a_shaderAccumulator->ClearActivePasses(false);
}

NiTexture* ScopeCustomRenderer::Render() {
	logInfo("ScopeCustomRenderer::Render() Starting...");
	BSGraphics::State* pGraphicsState = &BSGraphics::State::GetSingleton();
	BSGraphics::RenderTargetManager* pTargetManager = &BSGraphics::RenderTargetManager::GetSingleton();
	BSGraphics::Renderer* pRenderData = &BSGraphics::Renderer::GetSingleton();
	ImageSpaceManager* pImageSpaceManager = ImageSpaceManager::GetSingleton();
	BSShaderManager::State* pShaderState = &BSShaderManager::State::GetSingleton();
	NiCamera* shaderCam = BSShaderManager::GetCamera();

	ShadowSceneNode* pWorldSSN = pShaderState->pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD];
	NiAVObject* objectLODRoot = pShaderState->pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD]->children[3].get();
	NiAVObject* pObjectLODRoot = objectLODRoot;
	if (objectLODRoot) {
		InterlockedIncrement(&objectLODRoot->refCount);
	}
	bool objectLODRootCull = objectLODRoot->flags.GetBit(NiAVObject::APP_CULLED_MASK);
	objectLODRoot->SetAppCulled(true);
	NiNode* grassNode = BGSGrassManager::GetSingleton()->grassNode;
	NiNode* pGrassNode = grassNode;
	bool grassCull = grassNode->flags.GetBit(NiAVObject::APP_CULLED_MASK);
	bool grassCullFlag = grassCull;
	grassNode->SetAppCulled(true);
	BSDistantObjectInstanceRenderer::QInstance().enabled = false;

	BSShaderManager::SetCamera(pRendererCamera->camera);

	pGraphicsState->SetCameraData(pRendererCamera->camera, false, 0.0F, 1.0F);
	pScopeCullingProc->SetAccumulator(pScopeAccumulator);
	pScopeCullingProc->kCullMode = BSCullingProcess::BSCP_CULL_IGNOREMULTIBOUNDS;
	pScopeCullingProc->bCameraRelatedUpdates = false;
	pScopeCullingProc->pkCamera = pRendererCamera->camera;
	pRendererCamera->Update();

	bool lightUpdateLast = pWorldSSN->DisableLightUpdate;
	pWorldSSN->DisableLightUpdate = true;
	bool lightUpdate = lightUpdateLast;

	REL::Relocation<bool*> BSFadeNode_bFadeEnabled{ REL::ID(1220201) };
	REL::Relocation<bool*> BSFadeNode_bDrawFadingEnabled{ REL::ID(1445134) };
	REL::Relocation<int*> BSFadeNode_iFadeEnableCounter{ REL::ID(580186) };

	bool fadeEnabledFlag = *BSFadeNode_bFadeEnabled;
	REL::safe_write(BSFadeNode_bFadeEnabled.address(), false);
	REL::safe_write(BSFadeNode_bDrawFadingEnabled.address(), false);
	REL::safe_write(BSFadeNode_iFadeEnableCounter.address(), 0);
	bool fadeEnabled = fadeEnabledFlag;

	pRenderData->SetClearColor(0.2F, 0.2F, 0.2F, 1.0F);

	//water here

	pScopeAccumulator->renderMode = BSShaderManager::etRenderMode::BSSM_RENDER_SCREEN_SPLATTER;
	pScopeAccumulator->eyePosition = pRendererCamera->camera->world.translate;
	pRenderData->ResetZPrePass();

	//here is where we would go through the array of cells for a top down render like Local Map Renderer

	BSPortalGraphEntry* camPortalEntry = Main::GetSingleton()->GetCameraPortalGraphEntry();
	if (camPortalEntry) {
		BSPortalGraph* camPortalGraph = camPortalEntry->PortalGraph;
		if (camPortalGraph) {
			BSShaderUtil::AccumulateSceneArray(pRendererCamera->camera, &camPortalGraph->AlwaysRenderArray, *pScopeCullingProc, false);
		}
	}

	NiAVObject* portalSharedNode;
	if (pWorldSSN->children.size() > 9) {
		portalSharedNode = pWorldSSN->children[9].get();
	} else {
		portalSharedNode = nullptr;
	}
	BSShaderUtil::AccumulateScene(pRendererCamera->camera, portalSharedNode, *pScopeCullingProc, false);

	NiAVObject* multiBoundNode;
	if (pWorldSSN->children.size() > 8) {
		multiBoundNode = pWorldSSN->children[8].get();
	} else {
		multiBoundNode = nullptr;
	}
	BSShaderUtil::AccumulateScene(pRendererCamera->camera, multiBoundNode, *pScopeCullingProc, false);
	pShaderState->cSceneGraph = BSShaderManager::BSSM_SSN_WORLD;
	pShaderState->pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD]->ProcessQueuedLights(pScopeCullingProc);
	pRenderData->ResetState();

	uint32_t renderTargetID = stl::to_underlying<RenderTargetMode>(RenderTargetMode::RENDER_TARGET_LOCAL_MAP);
	uint32_t depthTargetID = stl::to_underlying<DepthStencilTargetMode>(DepthStencilTargetMode::DEPTH_STENCIL_TARGET_MAIN);
	uint32_t effectID = stl::to_underlying<ImageSpaceManager::ImageSpaceEffectEnum>(ImageSpaceManager::ImageSpaceEffectEnum::kBSLocalMap);

	logInfo("Acquiring Targets...");  //Need to do more research for if we need to acquire targets or not
	bool shouldRelease = false;
	if (!pTargetManager->QIsAcquiredRenderTarget(renderTargetID)) {
		pTargetManager->AcquireRenderTarget(renderTargetID);
		shouldRelease = true;
	}
	logInfo("Render Scene...");
	RenderScopeScene(pRendererCamera->camera, pScopeAccumulator, renderTargetID, depthTargetID);

	pTargetManager->SetCurrentRenderTarget(0, 2, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);  //RENDER_TARGET_MAIN_COPY
	pTargetManager->SetCurrentRenderTarget(1, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);   //RENDER_TARGET_NONE
	pTargetManager->SetCurrentDepthStencilTarget(depthTargetID, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, false);

	//FOG OF WAR

	pTargetManager->SetCurrentDepthStencilTarget(0, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, false);

	pShaderParams->SetPixelConstant(0,
		1.0F / pTargetManager->pRenderTargetDataA[renderTargetID].uiWidth,
		1.0F / pTargetManager->pRenderTargetDataA[renderTargetID].uiHeight,
		0.0F,
		0.0F);

	pTargetManager->SetTextureDepth(1, depthTargetID);
	pTargetManager->SetTextureRenderTarget(2, renderTargetID, false);
	pImageSpaceManager->effectArray[effectID].UseDynamicResolution = false;
	pImageSpaceManager->RenderEffectHelper_2((ImageSpaceManager::ImageSpaceEffectEnum)effectID, renderTargetID, renderTargetID, pShaderParams);
	pTargetManager->SetCurrentRenderTarget(0, 1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);  //RENDER_TARGET_MAIN

	const BSFixedString strScope("ScopeTexture");
	NiTexture* renderedTexture = renderedTexture->CreateEmpty(strScope, false, false);
	renderedTexture->SetRendererTexture(pTargetManager->SaveRenderTargetToTexture(renderTargetID, false, false, BSGraphics::Usage::USAGE_DEFAULT));

	logInfo("Releasing Targets...");
	if (shouldRelease) {
		pTargetManager->ReleaseRenderTarget(renderTargetID);
	}

	BSShaderManager::SetCamera(shaderCam);
	pGraphicsState->SetCameraData(shaderCam, false, 0.0F, 1.0F);
	pWorldSSN->DisableLightUpdate = lightUpdate;

	REL::safe_write(BSFadeNode_bFadeEnabled.address(), fadeEnabled);
	REL::safe_write(BSFadeNode_bDrawFadingEnabled.address(), fadeEnabled);
	REL::safe_write(BSFadeNode_iFadeEnableCounter.address(), 0);

	//water here

	pScopeAccumulator->ClearActivePasses(false);
	pScopeAccumulator->ClearGroupPasses(5, false);
	BSDistantObjectInstanceRenderer::QInstance().enabled = true;

	NiAVObject* pOldGrassNode = pGrassNode;
	pGrassNode->SetAppCulled(grassCull);
	if (!InterlockedDecrement(&pOldGrassNode->refCount)) {
		pOldGrassNode->DeleteThis();
	}

	objectLODRoot->SetAppCulled(objectLODRootCull);
	if (!InterlockedDecrement(&objectLODRoot->refCount)) {
		objectLODRoot->DeleteThis();
	}
	return renderedTexture;
}

NiTexture* ScopeCustomRenderer::RenderSimple() {
	logInfo("ScopeCustomRenderer::RenderSimple() Starting...");
	BSGraphics::State* pGraphicsState = &BSGraphics::State::GetSingleton();
	BSGraphics::RenderTargetManager* pTargetManager = &BSGraphics::RenderTargetManager::GetSingleton();
	BSGraphics::Renderer* pRenderData = &BSGraphics::Renderer::GetSingleton();
	ImageSpaceManager* pImageSpaceManager = ImageSpaceManager::GetSingleton();
	BSShaderManager::State* pShaderState = &BSShaderManager::State::GetSingleton();
	NiCamera* pShaderCam = BSShaderManager::GetCamera();

	uint32_t renderTargetID = stl::to_underlying<RenderTargetMode>(RenderTargetMode::RENDER_TARGET_GB_ALBEDO_SPEC);
	uint32_t depthTargetID = stl::to_underlying<DepthStencilTargetMode>(DepthStencilTargetMode::DEPTH_STENCIL_TARGET_MAIN);
	uint32_t effectID = stl::to_underlying<ImageSpaceManager::ImageSpaceEffectEnum>(ImageSpaceManager::ImageSpaceEffectEnum::kHUDGlass);

	pScopeCullingProc->SetAccumulator(pScopeAccumulator);
	pScopeCullingProc->kCullMode = BSCullingProcess::BSCP_CULL_NORMAL;
	pScopeCullingProc->bCameraRelatedUpdates = true;
	pScopeCullingProc->pkCamera = pRendererCamera->camera;
	pRendererCamera->Update();

	pScopeAccumulator->activeShadowSceneNode = pShaderState->pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD];
	pScopeAccumulator->renderMode = BSShaderManager::etRenderMode::BSSM_RENDER_NORMAL;
	pScopeAccumulator->eyePosition = pRendererCamera->camera->world.translate;
	pScopeAccumulator->firstPerson = true;

	bool shouldRelease = false;
	if (!pTargetManager->QIsAcquiredRenderTarget(renderTargetID)) {
		pTargetManager->AcquireRenderTarget(renderTargetID);
		shouldRelease = true;
	}

	bool locked = false;
	if (pRenderData->TryLock()) {
		locked = true;
		pRenderData->Begin(0);
	}

	BSShaderAccumulator* lastAccumulator = std::move(BSShaderManager::GetCurrentAccumulator());
	NiCamera* lastCamera = std::move(BSShaderManager::GetCamera());

	ShadowSceneNode* pWorldSSN = pShaderState->pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD];
	NiAVObject* multiBoundNode;
	if (pWorldSSN->children.size() > 8) {
		multiBoundNode = pWorldSSN->children[8].get();
	} else {
		multiBoundNode = nullptr;
	}
	BSShaderUtil::AccumulateScene(pRendererCamera->camera, multiBoundNode, *pScopeCullingProc, false);
	BSShaderUtil::AccumulateScene(pRendererCamera->camera, pRendererCamera->cameraRoot.get(), *pScopeCullingProc, false);

	//pImageSpaceManager->RenderEffect_1((ImageSpaceManager::ImageSpaceEffectEnum)effectID, renderTargetID, nullptr);
	pImageSpaceManager->RenderEffectHelper_2((ImageSpaceManager::ImageSpaceEffectEnum)effectID, renderTargetID, renderTargetID, nullptr);

	pRenderData->SetClearColor(0.2F, 0.2F, 0.2F, 1.0F);

	pTargetManager->SetCurrentDepthStencilTarget(depthTargetID, BSGraphics::SetRenderTargetMode::SRTM_CLEAR, 0, false);
	pTargetManager->SetCurrentRenderTarget(0, renderTargetID, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);

	pTargetManager->SetTextureDepth(0, depthTargetID);
	pTargetManager->SetTextureRenderTarget(0, renderTargetID, false);

	pRenderData->ClearColor();

	//TODO: Check if there is already a texture made before making a new texture
	// If one is already made then we should destroy it
	//TODO: Destroy this texture when we are done with it
	const BSFixedString strScope("ScopeTexture");
	NiTexture* emptyTexture = emptyTexture->CreateEmpty(strScope, false, false);
	NiTexture* texture = nullptr;
	NiTexture* currentTexture = nullptr;
	NiTexture* renderedTexture = nullptr;

	if (pRendererCamera->renderPlane->shaderProperty.get()->Type() != NiProperty::SHADE) {
		//TODO: Add a creation of a shader property to the geometry for if the shaderProperty of the current geometry is nullptr or invalid
	}
	BSShaderProperty* shaderProperty = pRendererCamera->renderPlane->QShaderProperty();
	NiAlphaProperty* alphaProperty = (NiAlphaProperty*)pRendererCamera->renderPlane->effectState.get();
	bool alpha = false;
	if (alphaProperty) {
		alpha = alphaProperty->flags.flags & 1;
	} else {
		alpha = false;
	}
	if (shaderProperty) {
		if (shaderProperty->GetMaterialType() == BSShaderMaterial::BSMATERIAL_TYPE_EFFECT) {
			BSEffectShaderProperty* effectShaderProperty;
			BSEffectShaderMaterial* effectShaderMaterial;
			effectShaderProperty = (BSEffectShaderProperty*)shaderProperty;
			effectShaderMaterial = effectShaderProperty->GetEffectShaderMaterial();
			if (effectShaderMaterial) {
				texture = effectShaderMaterial->spBaseTexture.get();
			} else {
				texture = effectShaderProperty->GetBaseTexture();
			}
		}
		if (shaderProperty->GetMaterialType() == BSShaderMaterial::BSMATERIAL_TYPE_LIGHTING) {
			BSLightingShaderProperty* lightingShaderProperty;
			BSLightingShaderMaterialBase* lightingShaderMaterial;
			lightingShaderProperty = (BSLightingShaderProperty*)(shaderProperty);
			lightingShaderMaterial = lightingShaderProperty->GetLightingShaderMaterial();
			if (lightingShaderMaterial) {
				texture = lightingShaderMaterial->spDiffuseTexture.get();
			} else {
				texture = lightingShaderProperty->GetBaseTexture();
			}
		}
	}
	currentTexture = texture;
	if (texture != emptyTexture) {
		if (emptyTexture) {
			InterlockedIncrement(&emptyTexture->refCount);
		}
		texture = emptyTexture;
		if (currentTexture && !InterlockedDecrement(&currentTexture->refCount)) {
			currentTexture->DeleteThis();
		}
	}
	strScope.~BSFixedString();
	renderedTexture = emptyTexture;

	BSShaderAccumulator::RegisterObject_Standard(pScopeAccumulator, pRendererCamera->renderPlane, shaderProperty);
	//BSShaderUtil::RenderScene(pRendererCamera->camera, pScopeAccumulator, false);
	pGraphicsState->SetCameraData(pRendererCamera->camera, false, 0.0F, 1.0F);
	pScopeAccumulator->StartAccumulating(pRendererCamera->camera);
	pScopeAccumulator->FinishAccumulating();

	renderedTexture->SetRendererTexture(pTargetManager->SaveRenderTargetToTexture(renderTargetID, true, true, BSGraphics::Usage::USAGE_DYNAMIC));

	/*
	BSRenderPass* pass = shaderProperty->GetRenderPasses(pRendererCamera->renderPlane, (uint32_t)pScopeAccumulator->renderMode, pScopeAccumulator)->passList;
	if (pass) {
		pRendererCamera->renderPlane->flags.SetBit(true, NiAVObject::NEEDS_CUSTOM_RENDER);
		BSBatchRenderer::RenderPassImmediately(pass, pass->m_PassEnum, alpha);
		BSBatchRenderer::EndPass();
	}
	*/

	BSShaderManager::SetCurrentAccumulator(std::move(lastAccumulator));
	BSShaderManager::SetCamera(std::move(lastCamera));

	pRenderData->RestorePreviousClearColor();
	pTargetManager->SetCurrentRenderTarget(0, -1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	pGraphicsState->SetCameraData(pShaderCam, false, 0.0F, 1.0F);

	if (locked) {
		pRenderData->End();
		pRenderData->Unlock();
	}
	//pass->~BSRenderPass();

	if (shouldRelease) {
		pTargetManager->ReleaseRenderTarget(renderTargetID);
	}

	BSGraphics::TextureAccess mappedResource;
	ZeroMemory(&mappedResource, sizeof(BSGraphics::TextureAccess));

	D3D11_SHADER_RESOURCE_VIEW_DESC* pSRVDesc = nullptr;
	ID3D11Device* pSRVDevice = nullptr;
	D3D11_TEXTURE2D_DESC* pT2DDesc = nullptr;
	ID3D11Device* pT2DDevice = nullptr;

	renderedTexture->rendererTexture->m_ResourceView->GetDesc(pSRVDesc);
	renderedTexture->rendererTexture->m_ResourceView->GetDevice(&pSRVDevice);
	renderedTexture->rendererTexture->tex2D->GetDesc(pT2DDesc);
	renderedTexture->rendererTexture->tex2D->GetDevice(&pT2DDevice);

	pRenderData->MapTexture(renderedTexture->rendererTexture, BSGraphics::Map::MAP_WRITE_DISCARD, mappedResource);
	//DO TEXTURE STUFF HERE
	//MEMCPY mappedResource.pData
	pRenderData->UnmapTexture(renderedTexture->rendererTexture);
	return renderedTexture;
}
#pragma endregion

#pragma region ScopeLensModel
ScopeLensModel::ScopeLensModel() {
	renderRoot = nullptr;
	renderPlane = nullptr;
	reticleRoot = nullptr;
	reticlePlane = nullptr;
	scopeRoot = nullptr;
	rootNode = nullptr;
	renderTarget = -1;
	swapTarget = -1;
	visible = false;

	Interface3D::Renderer::Create(GetRendererName(), UI_DEPTH_PRIORITY::k3DUnderHUD, 50.0F, true)->hideScreenWhenDisabled = false;

	if (GetByNameFromPlayer3D("ScopeAiming")) {
		rootNode = const_cast<NiAVObject*>(GetByNameFromPlayer3D("ScopeAiming"))->IsNode();
		logInfo("Found Model Root.");
	}
	if (GetByNameFromPlayer3D("ScopeViewParts")) {
		scopeRoot = const_cast<NiAVObject*>(GetByNameFromPlayer3D("ScopeViewParts"))->IsNode();
		logInfo("Found Scope Root.");
	}
	if (GetByNameFromPlayer3D("TextureLoader:0")) {
		renderPlane = const_cast<NiAVObject*>(GetByNameFromPlayer3D("TextureLoader:0"))->IsTriShape();
		logInfo("Found Scope Render Plane.");
		BSShaderUtil::SetTexturesCanDegrade(renderPlane, false);
		if (renderPlane && renderPlane->parent) {
			renderRoot = renderPlane->parent;
		}
	}
	if (GetByNameFromPlayer3D("reticle_ui_stencil:0")) {
		reticlePlane = const_cast<NiAVObject*>(GetByNameFromPlayer3D("reticle_ui_stencil:0"))->IsTriShape();
		logInfo("Found Scope Reticle Plane.");
		BSShaderUtil::SetTexturesCanDegrade(reticlePlane, false);
		if (reticlePlane && reticlePlane->parent) {
			reticleRoot = reticlePlane->parent;
		}
	}

	InitModels();
	InitRenderer();
	InitTargets();
}

ScopeLensModel::ScopeLensModel(int32_t a_target, int32_t a_swap) :
	ScopeLensModel() {
	renderTarget = a_target;
	swapTarget = a_swap;
}

ScopeLensModel::~ScopeLensModel() {
	Interface3D::Renderer* renderer = GetRenderer();
	if (renderer) {
		renderer->Release();
	}
	NiNode* root = rootNode;
	if (root && !InterlockedDecrement(&root->refCount)) {
		root->DeleteThis();
	}
	//Do we need to destroy the geometry?
}

void ScopeLensModel::InitModels() {
	bool createRoot = false;
	bool createRenderPlane = false;
	bool createReticlePlane = false;

	NiUpdateData update(0.0F, 0);

	BSTriShape* renderPlaneCurrent = nullptr;
	BSTriShape* renderPlaneNew = nullptr;
	BSTriShape* render = nullptr;
	BSTriShape* reticlePlaneCurrent = nullptr;
	BSTriShape* reticlePlaneNew = nullptr;
	BSTriShape* reticle = nullptr;

	if (!rootNode) {
		createRoot = true;
	}
	if (!renderPlane) {
		createRenderPlane = true;
	}
	if (!reticlePlane) {
		createReticlePlane = true;
	}

	if (createRoot) {
		NiNode* rootCurrent = nullptr;
		NiNode* rootNew = nullptr;
		NiNode* root = nullptr;

		//There was no rootNode found. We need to make it ourself
		root = (NiNode*)RE::aligned_alloc(0x140, 0x10);
		if (root) {
			new (rootNew) NiNode(0);
		} else {
			rootNew = nullptr;
		}
		rootCurrent = rootNode;
		if (rootCurrent != rootNew) {
			if (rootNew) {
				InterlockedIncrement(&rootNew->refCount);
			}
			rootNode = rootNew;
			if (rootCurrent && !InterlockedDecrement(&rootCurrent->refCount)) {
				rootCurrent->DeleteThis();
			}
		}
		rootNode->name = "ScopeViewParts"sv;
		//TODO: Position this new root node to the proper spot (WeaponBone?)
		//Do we need to attach this to the weapon bone?
		rootNode->Update(update);
	}
	if (createRenderPlane) {
		//There was no renderPlane found. We need to make it ourself
		//TODO: At a later point this should be able to be positioned via MCM
		NiNode* rootCurrent = nullptr;
		NiNode* rootNew = nullptr;
		NiNode* root = nullptr;

		root = (NiNode*)RE::aligned_alloc(0x140, 0x10);
		if (root) {
			new (rootNew) NiNode(0);
		} else {
			rootNew = nullptr;
		}
		rootCurrent = renderRoot;
		if (rootCurrent != rootNew) {
			if (rootNew) {
				InterlockedIncrement(&rootNew->refCount);
			}
			renderRoot = rootNew;
			if (rootCurrent && !InterlockedDecrement(&rootCurrent->refCount)) {
				rootCurrent->DeleteThis();
			}
		}
		renderRoot->name = "TextureLoader"sv;
		rootNode->AttachChild(renderRoot, true);
		renderRoot->Update(update);

		render = ImageSpaceManager::GetSingleton()->CreatePartialScreenGeometry(1, 1);
		if (render) {
		} else {
			renderPlaneNew = nullptr;
		}
		if (renderPlane) {
			renderPlaneCurrent = renderPlane->IsTriShape();
		} else {
			renderPlaneCurrent = nullptr;
		}
		if (renderPlaneCurrent != renderPlaneNew) {
			if (renderPlaneNew) {
				InterlockedIncrement(&renderPlaneNew->refCount);
			}
			renderPlane = renderPlaneNew;
			if (renderPlaneCurrent && !InterlockedDecrement(&renderPlaneCurrent->refCount)) {
				renderPlaneCurrent->DeleteThis();
			}
		}
		renderPlane->name = "TextureLoader:0"sv;

		BSEffectShaderProperty* prop = nullptr;
		BSEffectShaderProperty* propNew = nullptr;
		BSEffectShaderProperty* propCurrent = nullptr;

		propNew = BSEffectShaderProperty::Create();
		if (propNew) {
		} else {
			propNew = nullptr;
		}
		propNew->SetMaterial(propNew->material, true);
		((BSEffectShaderMaterial*)(propNew->material))->kBaseColor = NiColorA::BLACK;
		propNew->SetupGeometry(renderPlane);
		propCurrent = (BSEffectShaderProperty*)renderPlane->QShaderProperty();
		if (propCurrent != propNew) {
			InterlockedIncrement(&propNew->refCount);
			renderPlane->SetProperty(propNew);
			if (propCurrent) {
				if (!InterlockedDecrement(&propCurrent->refCount)) {
					propCurrent->DeleteThis();
				}
			}
		}

		//Alpha property???

		renderPlane->flags.SetBit(true, NiAVObject::ALWAYS_DRAW);
		renderPlane->worldBound.fRadius = 1.0F;

		renderPlane->local.translate.x = 0.0;  //TODO
		renderPlane->local.translate.y = 0.0;  //TODO
		renderPlane->local.translate.z = 0.0;  //TODO
		renderRoot->AttachChild(renderPlane, true);
		renderPlane->Update(update);
	}
	if (createReticlePlane) {
		//There was no reticlePlane found. We need to make it ourself
		NiNode* rootCurrent = nullptr;
		NiNode* rootNew = nullptr;
		NiNode* root = nullptr;

		//There was no rootNode found. We need to make it ourself
		root = (NiNode*)RE::aligned_alloc(0x140, 0x10);
		if (root) {
			new (rootNew) NiNode(0);
		} else {
			rootNew = nullptr;
		}
		rootCurrent = reticleRoot;
		if (rootCurrent != rootNew) {
			if (rootNew) {
				InterlockedIncrement(&rootNew->refCount);
			}
			reticleRoot = rootNew;
			if (rootCurrent && !InterlockedDecrement(&rootCurrent->refCount)) {
				rootCurrent->DeleteThis();
			}
		}
		reticleRoot->name = "reticle_ui_stencil"sv;
		rootNode->AttachChild(reticleRoot, true);
		reticleRoot->Update(update);

		reticle = ImageSpaceManager::GetSingleton()->CreatePartialScreenGeometry(1, 1);
		if (reticle) {
		} else {
			reticlePlaneNew = nullptr;
		}
		if (reticlePlane) {
			reticlePlaneCurrent = reticlePlane->IsTriShape();
		} else {
			reticlePlaneCurrent = nullptr;
		}
		if (reticlePlaneCurrent != reticlePlaneNew) {
			if (reticlePlaneNew) {
				InterlockedIncrement(&reticlePlaneNew->refCount);
			}
			reticlePlane = reticlePlaneNew;
			if (reticlePlaneCurrent && !InterlockedDecrement(&reticlePlaneCurrent->refCount)) {
				reticlePlaneCurrent->DeleteThis();
			}
		}
		reticlePlane->name = "reticle_ui_stencil:0"sv;

		BSEffectShaderProperty* prop = nullptr;
		BSEffectShaderProperty* propNew = nullptr;
		BSEffectShaderProperty* propCurrent = nullptr;

		propNew = BSEffectShaderProperty::Create();
		if (propNew) {
		} else {
			propNew = nullptr;
		}
		propNew->SetMaterial(propNew->material, true);
		((BSEffectShaderMaterial*)(propNew->material))->kBaseColor = NiColorA::BLACK;
		propNew->SetupGeometry(reticlePlane);
		propCurrent = (BSEffectShaderProperty*)reticlePlane->QShaderProperty();
		if (propCurrent != propNew) {
			InterlockedIncrement(&propNew->refCount);
			reticlePlane->SetProperty(propNew);
			if (propCurrent) {
				if (!InterlockedDecrement(&propCurrent->refCount)) {
					propCurrent->DeleteThis();
				}
			}
		}

		NiAlphaProperty* alphaProp = nullptr;
		NiAlphaProperty* alphaPropNew = nullptr;

		alphaProp = (NiAlphaProperty*)RE::malloc(0x30);
		alphaPropNew = alphaProp;
		if (alphaProp) {
		} else {
			alphaPropNew = nullptr;
		}
		alphaPropNew->flags.flags |= 1;
		reticlePlane->AttachProperty(alphaPropNew);
		reticlePlane->flags.SetBit(true, NiAVObject::ALWAYS_DRAW);
		reticlePlane->worldBound.fRadius = 1.0F;

		reticlePlane->local.translate.x = 0.0;  //TODO
		reticlePlane->local.translate.y = 0.0;  //TODO
		reticlePlane->local.translate.z = 0.0;  //TODO
		reticleRoot->AttachChild(reticlePlane, true);
		reticlePlane->Update(update);
	}
}

void ScopeLensModel::InitRenderer() {
	Interface3D::Renderer* renderer = GetRenderer();
	SceneGraph* world = Main::GetWorldSceneGraph();

	renderer->Offscreen_SetDisplayMode(Interface3D::ScreenMode::kScreenAttached, "TextureLoader:0", "Materials\\Interface\\ScopeLens.BGEM");
	renderer->Offscreen_SetRenderTargetSize(Interface3D::OffscreenMenuSize::kFullFrame);
	renderer->MainScreen_SetBackgroundMode(Interface3D::BackgroundMode::kLive);
	//renderer->MainScreen_EnableScreenAttached3DMasking("TextureLoaderShadow:0", "Materials\\Interface\\ScopeLensShadow.BGEM");
	renderer->Offscreen_SetPostEffect(Interface3D::PostEffect::kNone);
	renderer->clearColor = NiColorA(0.0F);
	renderer->postAA = true;
	renderer->useFullPremultAlpha = true;
	renderer->useLongRangeCamera = true;
	renderer->customRenderTarget = renderTarget;
	renderer->customSwapTarget = swapTarget;
	renderer->Offscreen_Set3D(reticleRoot);
	//renderer->Offscreen_Set3D(world);
	renderer->MainScreen_SetScreenAttached3D(renderRoot);
	renderer->MainScreen_RegisterGeometryRequiringFullViewport(renderRoot);
}

void ScopeLensModel::InitTargets() {
	BSGraphics::RenderTargetManager* pTargetManager = &BSGraphics::RenderTargetManager::GetSingleton();
	if (renderTarget != -1 && !pTargetManager->QIsAcquiredRenderTarget(renderTarget)) {
		pTargetManager->AcquireRenderTarget(renderTarget);
	}
	if (swapTarget != -1 && !pTargetManager->QIsAcquiredRenderTarget(swapTarget)) {
		pTargetManager->AcquireRenderTarget(swapTarget);
	}
}

Interface3D::Renderer* ScopeLensModel::GetRenderer() {
	return Interface3D::Renderer::GetByName(GetRendererName());
}

const BSFixedString ScopeLensModel::GetRendererName() const {
	static BSFixedString ScopeGeometryStr("ScopeLensModel");
	return ScopeGeometryStr;
}

void ScopeLensModel::Show(bool forceShow) {
	if (!visible || forceShow) {
		GetRenderer()->Enable(true);
		visible = true;
	}
}

void ScopeLensModel::Hide() {
	if (visible) {
		GetRenderer()->Disable();
		visible = false;
	}
}

void ScopeLensModel::ChangeFOV(float FOV) {
	Interface3D::Renderer* renderer = GetRenderer();

	renderer->nativeAspectLongRange.get()->SetFOV(FOV);
	renderer->nativeAspect.get()->SetFOV(FOV);
	renderer->pipboyAspect.get()->SetFOV(FOV);
}

void ScopeLensModel::ClearFX() {
	Interface3D::Renderer* renderer = GetRenderer();
	bool show = visible;
	if (visible) {
		Hide();
	}
	renderer->Offscreen_QPipboyEffectControl().doScanlines = false;
	renderer->Offscreen_SetRenderTargetSize(Interface3D::OffscreenMenuSize::kFullFrame);
	renderer->Offscreen_SetPostEffect(Interface3D::PostEffect::kNone);
	FXNightVisionActive = false;
	FXThermalActive = false;
	FXNoneActive = true;

	if (show) {
		Show(true);
	}
}

void ScopeLensModel::DoNightVisionFX() {
	Interface3D::Renderer* renderer = GetRenderer();
	bool show = visible;
	if (visible) {
		Hide();
	}
	if (FXThermalActive) {
		ClearFX();
	}
	
	renderer->Offscreen_QPipboyEffectControl().doScanlines = true;
	renderer->Offscreen_SetRenderTargetSize(Interface3D::OffscreenMenuSize::kPipboy);
	renderer->Offscreen_SetPostEffect(Interface3D::PostEffect::kPipboy);
	FXNightVisionActive = true;
	FXNoneActive = false;

	if (show) {
		Show(true);
	}
}

void ScopeLensModel::DoThermalFX() {
	Interface3D::Renderer* renderer = GetRenderer();
	bool show = visible;
	if (visible) {
		Hide();
	}
	if (FXNightVisionActive) {
		ClearFX();
	}
	renderer->Offscreen_QPipboyEffectControl().doScanlines = true;
	renderer->Offscreen_SetRenderTargetSize(Interface3D::OffscreenMenuSize::kPipboy);
	renderer->Offscreen_SetPostEffect(Interface3D::PostEffect::kPipboy);
	FXThermalActive = true;
	FXNoneActive = false;

	if (show) {
		Show(true);
	}
}
#pragma endregion ScopeLensModel

#pragma region ScopeRenderer
namespace ScopeRenderer {
#pragma region ScopeCustomRenderer
	void CreateCustomRenderer() {
		logInfo("ScopeCustomRenderer Creation Starting...");

		//there is already an exsisting renderer
		if (scopeCustomRenderer) {
			logInfo("ScopeRenderer::CreateCustomRenderer() was called but there was already a renderer in place");
			return;
		}

		//if renderer is null
		if (!scopeCustomRenderer) {
			scopeCustomRenderer = InitCustomRenderer();
		}
		customRendererInitialized = true;

		logInfo("ScopeCustomRenderer Creation Complete.");
		logger::info(FMT_STRING("ScopeCustomRenderer created at {:p}"), fmt::ptr(scopeCustomRenderer));
	}

	void DestroyCustomRenderer() {
		if (!scopeCustomRenderer) {
			//logWarn("ScopeRenderer::DestroyCustomRenderer() Was called but renderer is already nullptr");
			return;
		}
		logInfo("ScopeCustomRenderer Destroy Starting...");
		scopeCustomRenderer->~ScopeCustomRenderer();
		scopeCustomRenderer = nullptr;
		customRendererInitialized = false;
		logInfo("ScopeCustomRenderer Destroy Complete.");
	}

	ScopeCustomRenderer* InitCustomRenderer() {
		logInfo("ScopeCustomRenderer Init Starting...");

		ScopeCustomRenderer* renderer;
		ScopeCustomRenderer* newRenderer;

		//allocate our renderer
		renderer = (ScopeCustomRenderer*)RE::malloc(sizeof(ScopeCustomRenderer));
		logInfo("ScopeCustomRenderer Allocated...");
		//if allocated succesful
		if (renderer) {
			new (renderer) ScopeCustomRenderer();
			newRenderer = renderer;
		} else {
			newRenderer = nullptr;
		}

		logInfo("ScopeCustomRenderer Init Complete.");
		return newRenderer;
	}

	void Render() {
		if (!scopeCustomRenderer) {
			logWarn("ScopeRenderer::Render() was called while scopeCustomRenderer was nullptr");
			return;
		}
		NiTexture* renderedTexture;

		//renderedTexture = scopeCustomRenderer->Render();
		renderedTexture = scopeCustomRenderer->RenderSimple();
		if (renderedTexture) {
			if (scopeCustomRenderer->pRendererCamera->renderPlane->shaderProperty.get()->Type() != NiProperty::SHADE) {
				//TODO: Add a creation of a shader property to the geometry for if the shaderProperty of the current geometry is nullptr or invalid
			}
			BSShaderProperty* shaderProperty = scopeCustomRenderer->pRendererCamera->renderPlane->QShaderProperty();
			if (shaderProperty) {
				if (shaderProperty->GetMaterialType() == BSShaderMaterial::BSMATERIAL_TYPE_EFFECT) {
					BSEffectShaderProperty* effectShaderProperty;
					BSEffectShaderMaterial* effectShaderMaterial;
					effectShaderProperty = (BSEffectShaderProperty*)shaderProperty;
					effectShaderMaterial = effectShaderProperty->GetEffectShaderMaterial();
					if (effectShaderMaterial) {
						effectShaderMaterial->SetBaseTexture(renderedTexture);
						effectShaderMaterial->fBaseColorScale = 1.0F;
						effectShaderMaterial->kBaseColor = NiColorA::WHITE;
					} else {
						effectShaderProperty->SetBaseTexture(renderedTexture);
					}
				}
				if (shaderProperty->GetMaterialType() == BSShaderMaterial::BSMATERIAL_TYPE_LIGHTING) {
					BSLightingShaderProperty* lightingShaderProperty;
					BSLightingShaderMaterialBase* lightingShaderMaterial;
					lightingShaderProperty = (BSLightingShaderProperty*)(shaderProperty);
					lightingShaderMaterial = lightingShaderProperty->GetLightingShaderMaterial();
					if (lightingShaderMaterial) {
						lightingShaderMaterial->spDiffuseTexture = renderedTexture;
					} else {
						lightingShaderProperty->SetDiffuseTexture(renderedTexture);
					}
				}
			}
		}
	}

	ScopeCustomRenderer* scopeCustomRenderer = nullptr;
	bool customRendererInitialized = false;
#pragma endregion ScopeCustomRenderer

#pragma region ScopeLensRenderer
	void CreateLensRenderer() {
		if (!scopeLensRenderer) {
			scopeLensRenderer = InitLensRenderer();
		}
	}

	void DestroyLensRenderer() {
		lensRendererInitialized = false;
		if (scopeLensRenderer) {
			scopeLensRenderer->~ScopeLensModel();
			scopeLensRenderer = nullptr;
		}
	}

	ScopeLensModel* InitLensRenderer() {
		lensRendererInitialized = true;
		return new ScopeLensModel();
	}

	ScopeLensModel* scopeLensRenderer = nullptr;
	bool lensRendererInitialized = false;
#pragma endregion ScopeLensRenderer
}

#pragma endregion ScopeRenderer
