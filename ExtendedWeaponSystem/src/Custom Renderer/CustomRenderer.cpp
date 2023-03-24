#include "Custom Renderer/CustomRenderer.h"

#pragma region ScopeCamera


ScopeCamera::ScopeCamera() :
	TESCamera() {
	logInfoConditional("ScopeCamera ctor Starting...");

	DefaultState* camDefaultState;
	ThermalState* camThermalState;
	NightVisionState* camNightVisionState;
	TESCameraState* oldCamState;

	//defaultState init
	camDefaultState = new DefaultState(*this, ScopeCameraStates::kDefault);
	if (camDefaultState) {
		cameraStates[ScopeCameraStates::kDefault].reset(camDefaultState);
		logInfoConditional("ScopeCamera - Created ScopeCamera::DefaultState");
	} else {
		camDefaultState = nullptr;
		logInfoConditional("ScopeCamera - ScopeCamera::DefaultState Creation FAILED");
	}
	//thermalState init
	camThermalState = new ThermalState(*this, ScopeCameraStates::kThermal);
	if (camThermalState) {
		cameraStates[ScopeCameraStates::kThermal].reset(camThermalState);
		logInfoConditional("ScopeCamera - Created ScopeCamera::ThermalState");
	} else {
		camThermalState = nullptr;
		logInfoConditional("ScopeCamera - ScopeCamera::ThermalState Creation FAILED");
	}
	//nightVisionState init
	camNightVisionState = new NightVisionState(*this, ScopeCameraStates::kNightVision);
	if (camNightVisionState) {
		cameraStates[ScopeCameraStates::kNightVision].reset(camNightVisionState);
		logInfoConditional("ScopeCamera - Created ScopeCamera::NightVisionState");
	} else {
		camNightVisionState = nullptr;
		logInfoConditional("ScopeCamera - ScopeCamera::NightVisionState Creation FAILED");
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
	logInfoConditional("ScopeCamera ctor Completed.");
}

ScopeCamera::~ScopeCamera() {  //TODO
}

void ScopeCamera::SetCameraRoot(NiNode* node) {  //TODO
}

void ScopeCamera::SetEnabled(bool bEnabled) {  //TODO
	enabled = bEnabled;
}

void ScopeCamera::Update() {  //TODO
}

bool ScopeCamera::QCameraEquals(std::uint32_t cameraIndex) {
	return false;
}

TESCameraState* ScopeCamera::QCameraState(std::uint32_t index) {
	if (!index) {
		return nullptr;
	}
	if (index > ScopeCameraStates::kTotal) {
		return nullptr;
	}
	return cameraStates[index].get();
}

NiCamera* ScopeCamera::QRenderCamera() {
	return camera;
}

NiPoint3& ScopeCamera::QMaxExtent() {
	return maxExtent;
}

NiPoint3& ScopeCamera::QMinExtent() {
	return minExtent;
}

void ScopeCamera::CreateDefault3D() {
	NiCamera* cam;
	NiCamera* oldCam;
	NiCamera* newCam;
	NiCamera* currentCam;

	cam = NiCamera::Create();
	if (cam) {
		newCam = cam;
		logInfoConditional("ScopeCamera - Created NiCamera");
	} else {
		newCam = nullptr;
		logInfoConditional("ScopeCamera - NiCamera Creation FAILED");
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
	camera->SetViewFrustrum(updatedFrustum);

	NiNode* currentNode;
	NiNode* newNode;
	NiNode* node;

	node = new NiNode(1);
	if (node) {
		newNode = node;
		logInfoConditional("ScopeCamera - Created NiNode");
	} else {
		newNode = nullptr;
		logInfoConditional("ScopeCamera - NiNode Creation FAILED");
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

	geo = new BSTriShape();
	if (geo) {
		newGeo = geo;
		logInfoConditional("ScopeCamera - Created BSTriShape");
	} else {
		newGeo = nullptr;
		logInfoConditional("ScopeCamera - BSTriShape Creation FAILED");
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
}

void ScopeCamera::Reset() {
	currentState->Begin();
}

void ScopeCamera::SetExtents(NiPoint3& min, NiPoint3& max) {
	maxExtent = max;
	minExtent = min;
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

void ScopeCamera::Update3D() {
	BSGeometry* currentGeom;
	BSGeometry* geom;
	BSGeometry* newGeom;
	BSGeometry* oldGeom;

	const BSFixedString geomName = "TextureLoader:0";

	logInfoConditional("Looking for new camera and geometry...");

	geom = (BSGeometry*)GetByNameFromPlayer3D(geomName);
	if (geom) {
		newGeom = geom;
	} else {
		newGeom = nullptr;
	}
	currentGeom = renderPlane;
	if (renderPlane != newGeom) {
		oldGeom = renderPlane;
		if (newGeom) {
			//Do we need to increment the refCount?
			logInfoConditional("Found the geometry of the scope.");
		}
		currentGeom = newGeom;
		renderPlane = newGeom;
		if (oldGeom) {
			//Do we need to delete the old one?
			currentGeom = renderPlane;
		}
	}

	NiCamera* currentCam;
	NiCamera* cam;
	NiCamera* newCam;
	NiCamera* oldCam;

	const BSFixedString camName = "ScopePOV";

	cam = (NiCamera*)GetByNameFromPlayer3D(camName);
	if (cam) {
		newCam = cam;
	} else {
		newCam = nullptr;
	}
	currentCam = camera;
	if (camera != newCam) {
		oldCam = camera;
		if (newCam) {
			//Do we need to increment the refCount?
			logInfoConditional("Found the scope camera.");
		}
		currentCam = newCam;
		camera = newCam;
		cameraRoot = camera->parent;
		if (oldCam) {
			//Do we need to delete the old one?
			currentCam = camera;
		}
	}
	//TODO: add actor value or something similar to set what the FOV should be on the camera of each scope
	BSShaderUtil::SetSceneGraphCameraFOV(Main::GetWorldSceneGraph(), (90.0 / 4.0), 0, camera, 1);  //TEMP. Right now I just have it as 4x zoom

	if (!geom) {
		logInfoConditional("Could not find the geometry of the scope.");
		processCurrentScope = false;
	}
}

ScopeCamera::DefaultState::DefaultState(TESCamera& cam, std::uint32_t ID) :
	TESCameraState(cam, ID) {  //TODO: Add new members and add each new state
	logInfoConditional("ScopeCamera::DefaultState ctor Starting...");
	refCount = 0;
	camera = &cam;
	id = ID;

	initialPosition = NiPoint3::ZERO;
	translation = NiPoint3::ZERO;
	zoom = 1.0F;
	minFrustumHalfWidth = 0.0F;
	minFrustumHalfHeight = 0.0F;
	logInfoConditional("ScopeCamera::DefaultState ctor Completed.");
}

ScopeCamera::DefaultState::~DefaultState() {
	logInfoConditional("ScopeCamera::DefaultState dtor Starting...");
	RE::free(this);
	logInfoConditional("ScopeCamera::DefaultState dtor Completed.");
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

void ScopeCamera::DefaultState::Update(BSTSmartPointer<TESCameraState>& a_nextState) {  //TODO
}

void ScopeCamera::DefaultState::GetRotation(NiQuaternion& a_rotation) const {  //TODO
}

void ScopeCamera::DefaultState::GetTranslation(NiPoint3& a_translation) const {  //TODO
}

NiQuaternion& ScopeCamera::DefaultState::QInitialRotation() {
	return initialRotation;
}

NiPoint3& ScopeCamera::DefaultState::QInitialPosition() {
	return initialPosition;
}

NiQuaternion& ScopeCamera::DefaultState::QRotation() {
	return rotation;
}

NiPoint3& ScopeCamera::DefaultState::QTranslation() {
	return translation;
}

void ScopeCamera::DefaultState::SetInitialPosition(NiPoint3& newPos) {
	initialPosition = newPos;
}

void ScopeCamera::DefaultState::SetMinFrustum(float width, float height) {
	minFrustumHalfWidth = width * 0.5F;
	minFrustumHalfHeight = height * 0.5F;
}

void ScopeCamera::DefaultState::SetTranslation(NiPoint3& newPos) {
	translation = newPos;
}

void ScopeCamera::DefaultState::SetZoom(float newZoom) {
	zoom = newZoom;
}

ScopeCamera::ThermalState::ThermalState(TESCamera& cam, std::uint32_t ID) :
	DefaultState(cam, ID) {
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

void ScopeCamera::ThermalState::GetRotation(NiQuaternion& a_rotation) const {
}

void ScopeCamera::ThermalState::GetTranslation(NiPoint3& a_translation) const {
}

ScopeCamera::NightVisionState::NightVisionState(TESCamera& cam, std::uint32_t ID) :
	DefaultState(cam, ID) {
}

ScopeCamera::NightVisionState::~NightVisionState() {
}

bool ScopeCamera::NightVisionState::ShouldHandleEvent(const InputEvent* inputEvent) {
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

void ScopeCamera::NightVisionState::GetRotation(NiQuaternion& a_rotation) const {
}

void ScopeCamera::NightVisionState::GetTranslation(NiPoint3& a_translation) const {
}


#pragma endregion

#pragma region ScopeRenderer

ScopeRenderer::ScopeRenderer() {
	logInfoConditional("ScopeRenderer ctor Starting...");

	BSShaderAccumulator* shaderAccum;
	BSShaderAccumulator* newShaderAccum;
	BSShaderAccumulator* oldShaderAccum;
	BSShaderAccumulator* pShaderAccum;

	logInfoConditional("ScopeRenderer - Creating BSCullingProcess...");
	pScopeCullingProc = (BSCullingProcess*)RE::malloc(0x1A0);
	if (&pScopeCullingProc) {
		new (pScopeCullingProc) BSCullingProcess(0);
	} else {
		pScopeCullingProc = nullptr;
		logInfoConditional("ScopeRenderer - BSCullingProcess Creation FAILED");
	}

	logInfoConditional("ScopeRenderer - Creating ScopeCamera...");
	rendererCamera = *new ScopeCamera();
	if (&rendererCamera) {
		new (&rendererCamera) ScopeCamera();
	} else {
		logInfoConditional("ScopeRenderer - ScopeCamera Creation FAILED");
	}

	logInfoConditional("ScopeRenderer - Creating ImageSpaceShaderParam...");
	shaderParams = *(ImageSpaceShaderParam*)RE::malloc(0x90);
	if (&shaderParams) {
		new (&shaderParams) ImageSpaceShaderParam();
	} else {
		logInfoConditional("ScopeRenderer - ImageSpaceShaderParam Creation FAILED");
		shaderParams = BSImagespaceShader::GetDefaultParam();
	}

	shaderAccum = (BSShaderAccumulator*)RE::malloc(0x590);
	if (shaderAccum) {
		new (shaderAccum) BSShaderAccumulator();
		newShaderAccum = shaderAccum;
		logInfoConditional("ScopeRenderer - Created BSShaderAccumulator");
	} else {
		newShaderAccum = nullptr;
		logInfoConditional("ScopeRenderer - BSShaderAccumulator Creation FAILED");
	}
	oldShaderAccum = pScopeAccumulator;
	if ((oldShaderAccum != newShaderAccum) || (pScopeAccumulator == nullptr)) {
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
	pShaderAccum = pScopeAccumulator;
	pShaderAccum->QSilhouetteColor = NiColorA::WHITE;
	pScopeCullingProc->SetAccumulator(pScopeAccumulator);
	pScopeCullingProc->kCullMode = BSCullingProcess::BSCP_CULL_IGNOREMULTIBOUNDS;
	pScopeCullingProc->m_bCameraRelatedUpdates = false;
	(&shaderParams)->ResizeConstantGroup(0, 1);
	renderTarget = 19;

	logInfoConditional("ScopeRenderer ctor Completed.");
}

ScopeRenderer::~ScopeRenderer() {
	BSShaderAccumulator* shaderAccum;
	NiCamera* cam;
	TESCameraState* state;

	shaderParams.~ImageSpaceShaderParam();
	shaderAccum = pScopeAccumulator;
	if (shaderAccum && !InterlockedDecrement(&shaderAccum->refCount)) {
		shaderAccum->DeleteThis();
	}
	cam = rendererCamera.camera;
	if (cam && !InterlockedDecrement(&cam->refCount)) {
		cam->DeleteThis();
	}
	state = rendererCamera.currentState.get();
	if (state && !InterlockedDecrement(&state->refCount)) {
		state->~TESCameraState();
	}
	rendererCamera.~ScopeCamera();
	pScopeCullingProc->~BSCullingProcess();
}

ScopeRenderer& ScopeRenderer::operator=(const ScopeRenderer& rhs) {
	memcpy(pScopeCullingProc, rhs.pScopeCullingProc, 0x1A0);
	rendererCamera = rhs.rendererCamera;
	pScopeAccumulator = rhs.pScopeAccumulator;
	shaderParams = rhs.shaderParams;
	renderTarget = rhs.renderTarget;
	return *this;
}

NiTexture* ScopeRenderer::Render(bool saveTexture) {
	ScopeRenderer* pScopeRenderer = (this);
	ScopeCamera* pScopeCam = (&pScopeRenderer->rendererCamera);

	BSGraphics::State* pGraphicsState = &BSGraphics::State::GetSingleton();
	BSGraphics::RenderTargetManager* pTargetManager = &BSGraphics::RenderTargetManager::GetSingleton();
	BSGraphics::Renderer* pRenderData = &BSGraphics::Renderer::GetSingleton();
	ImageSpaceManager* pImageSpaceManager = ImageSpaceManager::GetSingleton();
	BSShaderManager::State* pShaderState = &BSShaderManager::State::GetSingleton();
	NiCamera* shaderCam = BSShaderManager::GetCamera();

	BSCullingProcess scopeCulling = *(BSCullingProcess*)RE::malloc(0x1A0);
	new (&scopeCulling) BSCullingProcess(0);  //Is this still needed with the above statement?

	ShadowSceneNode* pWorldSSN = pShaderState->pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD];
	NiAVObject* objectLODRoot = pShaderState->pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD]->children[3].get();
	if (objectLODRoot) {
		InterlockedIncrement(&objectLODRoot->refCount);
	}
	bool objCullFlag = objectLODRoot->flags.flags & 1;
	objectLODRoot->SetAppCulled(true);

	memcpy(BSShaderManager::GetCamera(), pScopeCam->camera, 0x1A0);

	pGraphicsState->SetCameraData(pScopeCam->camera, false, 0.0F, 1.0F);
	(&scopeCulling)->SetAccumulator(pScopeRenderer->pScopeAccumulator);
	(&scopeCulling)->kCullMode = BSCullingProcess::BSCP_CULL_IGNOREMULTIBOUNDS;
	(&scopeCulling)->m_bCameraRelatedUpdates = false;
	(&scopeCulling)->m_pkCamera = pScopeCam->camera;

	pScopeCam->Update();

	pRenderData->SetClearColor(1.0F, 1.0F, 1.0F, 1.0F);

	pScopeRenderer->pScopeAccumulator->renderMode = BSShaderManager::etRenderMode::BSSM_RENDER_VATS_MASK;
	pScopeRenderer->pScopeAccumulator->QEyePosition = pScopeCam->camera->world.translate;
	pRenderData->ResetZPrePass();
	AccumulateSceneFunctor acummulateFunctor;
	acummulateFunctor.renderer = pScopeRenderer;
	if (TES::GetSingleton()->GetWorldSpace() || (acummulateFunctor.interior = false, TES::GetSingleton()->GetWorldSpace()->flags & 0x40) == 0) {
		acummulateFunctor.interior = true;
	}

	BSPortalGraphEntry* camPortalEntry = (Main::GetSingleton())->GetCameraPortalGraphEntry();
	if (camPortalEntry) {
		BSPortalGraph* camPortalGraph = camPortalEntry->PortalGraph;
		if (camPortalGraph) {
			BSShaderUtil::AccumulateSceneArray(pScopeCam->camera, &camPortalGraph->AlwaysRenderArray, scopeCulling, false);
		}
	}

	NiAVObject* portalSharedNode;
	if (pWorldSSN->children.size() > 9) {
		portalSharedNode = pWorldSSN->children[9].get();
		BSShaderUtil::AccumulateScene(pScopeCam->camera, portalSharedNode, scopeCulling, false);
	} else {
		portalSharedNode = nullptr;
	}

	NiAVObject* multiBoundNode;
	if (pWorldSSN->children.size() > 8) {
		multiBoundNode = pWorldSSN->children[8].get();
		BSShaderUtil::AccumulateScene(pScopeCam->camera, multiBoundNode, scopeCulling, false);
	} else {
		multiBoundNode = nullptr;
	}

	uint32_t depthTargetID = 1;
	uint32_t renderTargetID = 27;
	uint32_t effectID = 152;

	pShaderState->cSceneGraph = BSShaderManager::BSSM_SSN_WORLD;
	pShaderState->pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD]->ProcessQueuedLights(&scopeCulling);
	pRenderData->ResetState();

	pTargetManager->AcquireDepthStencil(depthTargetID);
	pTargetManager->AcquireRenderTarget(renderTargetID);
	RenderScopeScene(pScopeCam->camera, pScopeRenderer->pScopeAccumulator, renderTargetID, depthTargetID);
	pTargetManager->SetCurrentRenderTarget(0, 2, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	pTargetManager->SetCurrentRenderTarget(1, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	pTargetManager->SetCurrentDepthStencilTarget(1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, false);
	//FogOfWar Setup stuff would happen after this in the LocalMapRenderer::Render
	//stuff and things
	//
	pTargetManager->SetCurrentDepthStencilTarget(0, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, false);
	pScopeRenderer->shaderParams.SetPixelConstant(0, 1.0F / pTargetManager->pRenderTargetDataA[pScopeRenderer->renderTarget].uiWidth, 1.0F / pTargetManager->pRenderTargetDataA[pScopeRenderer->renderTarget].uiHeight, 0.0F, 0.0F);
	pTargetManager->SetTextureDepth(1, depthTargetID);
	pTargetManager->SetTextureRenderTarget(2, renderTargetID, false);
	pImageSpaceManager->effectArray[effectID].UseDynamicResolution = false;
	pImageSpaceManager->RenderEffect_1((ImageSpaceManager::ImageSpaceEffectEnum)effectID, pScopeRenderer->renderTarget, &pScopeRenderer->shaderParams);
	pTargetManager->ReleaseDepthStencil(depthTargetID);
	pTargetManager->ReleaseRenderTarget(renderTargetID);

	pTargetManager->SetCurrentRenderTarget(0, 1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	NiTexture* renderedTexture = nullptr;
	BSGraphics::Texture* graphicsTex = nullptr;
	if (saveTexture) {
		const BSFixedString strScope("ScopeTexture");
		renderedTexture = renderedTexture->CreateEmpty(strScope, false, false);
		graphicsTex = pTargetManager->SaveRenderTargetToTexture(19, false, false, BSGraphics::Usage::USAGE_DEFAULT);
		renderedTexture->rendererTexture = graphicsTex;
	}
	//BSScaleformRenderer::SetCurrentRenderTarget
	memcpy(BSShaderManager::GetCamera(), shaderCam, 0x1A0);
	pGraphicsState->SetCameraData(shaderCam, false, 0.0F, 1.0F);

	pScopeRenderer->pScopeAccumulator->ClearActivePasses(false);
	pScopeRenderer->pScopeAccumulator->ClearGroupPasses(5, false);
	(&scopeCulling)->~BSCullingProcess();

	objectLODRoot->SetAppCulled(objCullFlag);
	if (!InterlockedDecrement(&objectLODRoot->refCount)) {
		objectLODRoot->DeleteThis();
	}
	return renderedTexture;
}

#pragma endregion

void RenderScopeScene(NiCamera* cam, BSShaderAccumulator* shadeAccum, uint32_t target, uint32_t depthTarget) {
	BSGraphics::State* pGraphicsState = &BSGraphics::State::GetSingleton();
	BSGraphics::RenderTargetManager* pTargetManager = &BSGraphics::RenderTargetManager::GetSingleton();
	BSGraphics::Renderer* pRenderData = &BSGraphics::Renderer::GetSingleton();
	BSShaderManager::State* pShaderState = &BSShaderManager::State::GetSingleton();

	pTargetManager->SetCurrentDepthStencilTarget(depthTarget, BSGraphics::SetRenderTargetMode::SRTM_FORCE_COPY_RESTORE, 0, false);
	pTargetManager->SetCurrentRenderTarget(1, target, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	pTargetManager->SetCurrentRenderTarget(2, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	pTargetManager->SetCurrentRenderTarget(3, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	if (pShaderState->bDeferredRGBEmit) {
		pTargetManager->SetCurrentRenderTarget(4, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	}
	pTargetManager->SetCurrentRenderTarget(5, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	pTargetManager->SetCurrentViewportForceToRenderTargetDimensions();
	pRenderData->SetClearColor(0.0F, 0.0F, 0.0F, 0.0F);
	pRenderData->ClearColor();
	pRenderData->Flush();
	//Threaded stuff happens here in RenderLocalMapScene
	//stuff
	//more stuff
	pGraphicsState->SetCameraData(cam, false, 0.0F, 1.0F);
	pRenderData->DoZPrePass(nullptr, nullptr, 0.0F, 1.0F, 0.0F, 1.0F);
	shadeAccum->RenderOpaqueDecals();
	shadeAccum->RenderBatches(4, false, -1);
	shadeAccum->RenderBlendedDecals();
	//BSGraphics::pDefaultContext stuff happens here in RenderLocalMapScene
	//stuff
	//more stuff
	pRenderData->Flush();
	pRenderData->SetClearColor(1.0F, 1.0F, 1.0F, 1.0F);
	//more context stuff
	//more things
	shadeAccum->ClearEffectPasses();
	shadeAccum->ClearActivePasses(false);
}


#pragma region nsScope

void nsScope::CreateRenderer() {
	logInfoConditional("ScopeRenderer Creation Starting...");

	//create a spinlock
	scopeRendererLock = *(new BSSpinLock());
	logInfoConditional("ScopeRendererLock Allocated...");
	new (&scopeRendererLock) BSSpinLock();

	//there is already an exsisting renderer
	if (scopeRenderer != nullptr) {
		logInfoConditional("nsScope::CreateRenderer() was called but there was already a renderer in place");
		return;
	}

	//if renderer is null
	if (!scopeRenderer) {
		scopeRenderer = InitRenderer();
		//in nsPipboy_LocalMap::CreateRenderer this is where the localMapCameraUpdateEvent stuff would also be created
	}
	scopeRendererLock.unlock();
	readyForRender = true;
	logInfoConditional("ScopeRenderer Creation Complete.");
	logger::info(FMT_STRING("ScopeRenderer created at {:p}"), fmt::ptr(scopeRenderer));
}

void nsScope::DestroyRenderer() {
	logInfoConditional("ScopeRenderer Destroy Starting...");
	scopeRendererLock.lock();

	ScopeRenderer* pRenderer = scopeRenderer;
	if (scopeRenderer) {
		scopeRenderer->~ScopeRenderer();
		RE::free(pRenderer);
	}
	scopeRenderer = nullptr;
	readyForRender = false;
	logInfoConditional("ScopeRenderer Destroy Complete.");
}

ScopeRenderer* nsScope::InitRenderer() {
	logInfoConditional("ScopeRenderer Init Starting...");

	ScopeRenderer* renderer;
	ScopeRenderer* newRenderer;

	//allocate our renderer
	renderer = new ScopeRenderer();
	logInfoConditional("ScopeRenderer Allocated...");
	//if allocated succesful
	if (renderer) {
		newRenderer = renderer;
	} else {
		newRenderer = nullptr;
	}

	logInfoConditional("ScopeRenderer Init Complete.");
	return newRenderer;
}

void nsScope::Render() {
	NiTexture* renderedTexture;

	scopeRendererLock.lock();
	if (scopeRenderer) {
		renderedTexture = scopeRenderer->Render(true);
		if (renderedTexture) {
			/*
			if (texID string init) {
				//stuff about localMapTextureID
				//stuff
			}
			//here there would be stuff for setting the renderedTexture to be the scaleform texture
			*/
			if (scopeRenderer->rendererCamera.renderPlane->shaderProperty.get()->Type() != NiProperty::SHADE) {
				//TODO: Add a creation of a shader property to the geometry for if the shaderProperty of the current geometry is nullptr or invalid

			}
			BSShaderProperty* shaderProperty = scopeRenderer->rendererCamera.renderPlane->QShaderProperty();
			if (shaderProperty->GetMaterialType() == BSShaderMaterial::BSMATERIAL_TYPE_EFFECT) {
				BSEffectShaderProperty* effectShaderProperty;
				BSEffectShaderMaterial* effectShaderMaterial;
				effectShaderProperty = (BSEffectShaderProperty*)shaderProperty;
				if (shaderProperty) {
					effectShaderMaterial = effectShaderProperty->GetEffectShaderMaterial();
					effectShaderMaterial->SetBaseTexture(renderedTexture);
					effectShaderMaterial->fBaseColorScale = 1.0F;
					effectShaderMaterial->kBaseColor = NiColorA::WHITE;
				}
			}
			if (shaderProperty->GetMaterialType() == BSShaderMaterial::BSMATERIAL_TYPE_LIGHTING) {
				BSLightingShaderProperty* lightingShaderProperty;
				BSLightingShaderMaterialBase* lightingShaderMaterial;
				lightingShaderProperty = (BSLightingShaderProperty*)(shaderProperty);
				if (shaderProperty) {
					lightingShaderMaterial = lightingShaderProperty->GetLightingShaderMaterial();
					lightingShaderMaterial->spDiffuseTexture.reset(renderedTexture);
				}
			}
		}
	}
	scopeRendererLock.unlock();
}

#pragma endregion
