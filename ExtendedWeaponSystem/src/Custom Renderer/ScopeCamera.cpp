#include "Global.h"

ScopeCamera::ScopeCamera() : TESCamera() {
	logIfNeeded("ScopeCamera ctor Starting...");

	DefaultState* camDefaultState;
	ThermalState* camThermalState;
	NightVisionState* camNightVisionState;
	TESCameraState* oldCamState;

	//defaultState init
	camDefaultState = new DefaultState(*this, ScopeCameraStates::kDefault);
	if (camDefaultState) {
		cameraStates[ScopeCameraStates::kDefault].reset(camDefaultState);
		logIfNeeded("ScopeCamera - Created ScopeCamera::DefaultState");
	} else {
		camDefaultState = nullptr;
		logIfNeeded("ScopeCamera - ScopeCamera::DefaultState Creation FAILED");
	}
	//thermalState init
	camThermalState = new ThermalState(*this, ScopeCameraStates::kThermal);
	if (camThermalState) {
		cameraStates[ScopeCameraStates::kThermal].reset(camThermalState);
		logIfNeeded("ScopeCamera - Created ScopeCamera::ThermalState");
	} else {
		camThermalState = nullptr;
		logIfNeeded("ScopeCamera - ScopeCamera::ThermalState Creation FAILED");
	}
	//nightVisionState init
	camNightVisionState = new NightVisionState(*this, ScopeCameraStates::kNightVision);
	if (camNightVisionState) {
		cameraStates[ScopeCameraStates::kNightVision].reset(camNightVisionState);
		logIfNeeded("ScopeCamera - Created ScopeCamera::NightVisionState");
	} else {
		camNightVisionState = nullptr;
		logIfNeeded("ScopeCamera - ScopeCamera::NightVisionState Creation FAILED");
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
	logIfNeeded("ScopeCamera ctor Completed.");
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
		logIfNeeded("ScopeCamera - Created NiCamera");
	} else {
		newCam = nullptr;
		logIfNeeded("ScopeCamera - NiCamera Creation FAILED");
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
		logIfNeeded("ScopeCamera - Created NiNode");
	} else {
		newNode = nullptr;
		logIfNeeded("ScopeCamera - NiNode Creation FAILED");
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
		logIfNeeded("ScopeCamera - Created BSTriShape");
	} else {
		newGeo = nullptr;
		logIfNeeded("ScopeCamera - BSTriShape Creation FAILED");
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
	
	logIfNeeded("Looking for new camera and geometry...");

	geom = (BSGeometry*)GetByNameHelper(geomName);
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
			logIfNeeded("Found the geometry of the scope.");
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

	cam = (NiCamera*)GetByNameHelper(camName);
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
			logIfNeeded("Found the scope camera.");
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
		logIfNeeded("Could not find the geometry of the scope.");
		processCurrentScope = false;
	}
}

ScopeCamera::DefaultState::DefaultState(TESCamera& cam, std::uint32_t ID) : TESCameraState(cam, ID) {  //TODO: Add new members and add each new state
	logIfNeeded("ScopeCamera::DefaultState ctor Starting...");
	refCount = 0;
	camera = &cam;
	id = ID;

	initialPosition = NiPoint3::ZERO;
	translation = NiPoint3::ZERO;
	zoom = 1.0F;
	minFrustumHalfWidth = 0.0F;
	minFrustumHalfHeight = 0.0F;
	logIfNeeded("ScopeCamera::DefaultState ctor Completed.");
}

ScopeCamera::DefaultState::~DefaultState() {
	logIfNeeded("ScopeCamera::DefaultState dtor Starting...");
	RE::free(this);
	logIfNeeded("ScopeCamera::DefaultState dtor Completed.");
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
