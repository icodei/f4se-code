#include "Global.h"

NiCamera* scopePOV;
NiNode* scopePOVRoot;
NiCamera* scopePOV_BACKUP;
NiNode* scopePOVRoot_BACKUP;


ScopeCamera::ScopeCamera() : TESCamera() {
	logIfNeeded("ScopeCamera ctor Starting...");

	Init3D();

	DefaultState* camDefaultState;
	TESCameraState* oldCamState;

	//defaultState init
	camDefaultState = new DefaultState(*this, 0);
	if (camDefaultState) { //TODO: Add each state to the cameraStates array
		cameraStates[0] = camDefaultState;
		logIfNeeded("ScopeCamera - Created ScopeCamera::DefaultState");
	}
	else {
		camDefaultState = nullptr;
		logIfNeeded("ScopeCamera - ScopeCamera::DefaultState Creation FAILED");
	}
	//thermalState init

	//nightVisionState init

	//oldState
	oldCamState = currentState;
	if (camDefaultState != oldCamState) {
		if (camDefaultState) {
			InterlockedIncrement(&camDefaultState->m_refCount);
		}
		currentState = camDefaultState;
		if (oldCamState && !InterlockedDecrement(&oldCamState->m_refCount)) {
			oldCamState->~TESCameraState();
		}
	}
	//set state to default
	this->SetState(cameraStates[0]);
	logIfNeeded("ScopeCamera ctor Completed.");
}

ScopeCamera::~ScopeCamera() { //TODO

}

void ScopeCamera::SetCameraRoot(NiNode* node) {  //TODO

}

void ScopeCamera::SetEnabled(bool enabled) { //TODO

}

void ScopeCamera::Update() { //TODO

}

bool ScopeCamera::QCameraEquals(std::uint32_t cameraIndex)
{
	return false;
}

TESCameraState* ScopeCamera::QCameraState(std::uint32_t index)
{
	return nullptr;
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

void ScopeCamera::Init3D() {
	NiCamera* cam;
	NiCamera* newCam;
	NiCamera* currentCam;

	NiNode* node;
	NiNode* newNode;
	NiNode* currentNode;

	NiAVObject* geo;
	NiAVObject* newGeo;
	NiAVObject* currentGeo;

	cam = Create_NiCamera();
	if (cam) {
		new(cam) NiCamera();
		newCam = cam;
		logIfNeeded("ScopeCamera - Created NiCamera");
	}
	else {
		newCam = nullptr;
		logIfNeeded("ScopeCamera - NiCamera Creation FAILED");
	}
	currentCam = camera;
	if (currentCam != newCam) {
		if (newCam) {
			InterlockedIncrement(&newCam->m_uiRefCount);
		}
		camera = newCam;
		if (currentCam && !InterlockedDecrement(&currentCam->m_uiRefCount)) {
			currentCam->DeleteThis();
		}
	}

	node = Create_NiNode();
	if (node) {
		new(node) NiNode(1);
		newNode = node;
		logIfNeeded("ScopeCamera - Created NiNode");
	}
	else {
		newNode = nullptr;
		logIfNeeded("ScopeCamera - NiNode Creation FAILED");
	}
	currentNode = cameraNode;
	if (currentNode != newNode) {
		if (newNode) {
			InterlockedIncrement(&newNode->m_uiRefCount);
		}
		cameraNode = newNode;
		if (currentNode && !InterlockedDecrement(&currentNode->m_uiRefCount)) {
			currentNode->DeleteThis();
		}
	}
	cameraNode->AttachChild(camera, true);

	geo = Create_BSTriShape();
	if (geo) {
		new(geo) BSTriShape();
		newGeo = geo;
		logIfNeeded("ScopeCamera - Created BSTriShape");
	}
	else {
		newGeo = nullptr;
		logIfNeeded("ScopeCamera - BSTriShape Creation FAILED");
	}
	currentGeo = renderPlane;
	if (currentGeo != newGeo) {
		if (newGeo) {
			InterlockedIncrement(&newGeo->m_uiRefCount);
		}
		renderPlane = newGeo;
		if (currentGeo && !InterlockedDecrement(&currentGeo->m_uiRefCount)) {
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
	TESCameraState* pOldState;
	TESCameraState* oldState;
	TESCameraState* newState;

	pOldState = currentState;
	if (pOldState) {
		pOldState->End();
	}
	oldState = currentState;
	if (newCameraState != oldState) {
		if (newCameraState) {
			InterlockedIncrement(&newCameraState->m_refCount);
		}
		currentState = newCameraState;
		if (oldState && !InterlockedDecrement(&oldState->m_refCount)) {
			oldState->~TESCameraState();
		}
	}
	newState = currentState;
	if (newState) {
		newState->Begin();
	}
}

void ScopeCamera::Update3D() {
	BSGeometry* objGeom;
	NiCamera* currentCam;
	NiCamera* cam;
	NiCamera* newCam;

	const BSFixedString geomName = "TextureLoader:0";
	const BSFixedString camName = "ScopePOV";

	logIfNeeded("The 3D should be loaded now. We should be able to interact with geometry now.");
	objGeom = (BSGeometry*)GetByNameHelper(geomName);
	if (objGeom != ScopeTextureLoader) {
		if (objGeom) {
			ScopeTextureLoader = objGeom;
			logIfNeeded("Found the geometry of the scope.");
		}
	}
	cam = (NiCamera*)GetByNameHelper(camName);
	if (cam) {
		newCam = cam;
	}
	else {
		newCam = nullptr;
		scopePOV = scopePOV_BACKUP;
		scopePOVRoot = scopePOVRoot_BACKUP;
	}
	currentCam = scopePOV;
	if (currentCam != newCam) {
		if (newCam) {
			scopePOV = newCam;
			if (scopePOV->m_parent) {
				scopePOVRoot = scopePOV->m_parent;
			}
			logIfNeeded("Found the scope camera.");
		}
		if (currentCam && !InterlockedDecrement(&currentCam->refCount)) {
			currentCam->DeleteThis();
		}
	}
	//TODO: add actor value or something similar to set what the FOV should be on the camera of each scope
	if (scopePOV) {
		//float FOV = (*g_playerCamera)->fDefault1stPersonFOV;
		BSShaderUtil::SetSceneGraphCameraFOV(Main::GetWorldSceneGraph(), (float)(90.0 / 4.0), 0, scopePOV, 1);  //TEMP. Right now I just have it as 4x zoom
	}

	//if (scopePOV && scopeRenderer) {
	//	scopeRenderer->scopeCam.camera = scopePOV;
	//}
	//SetupTextureLoaderWithEffectShader();
	//SetupImageSpaceShader(ScopeTextureLoader, true);
	if (!objGeom) {
		logIfNeeded("Could not find the geometry of the scope.");
		//(ThermalFXS)->StopEffectShader(ThermalFXS, ScopeTextureLoader, effectShaderData);
		processCurrentScope = false;
	}
}

ScopeCamera::DefaultState::DefaultState(TESCamera& cam, std::uint32_t ID) : TESCameraState(cam, ID) { //TODO: Add new members and add each new state
	logIfNeeded("ScopeCamera::DefaultState ctor Starting...");
	refCount = 0;
	camera = &cam;
	id.set(CameraState, ID);

	initialPosition = NiPoint3_ZERO;
	translation = NiPoint3_ZERO;
	zoom = 1.0;
	minFrustumHalfWidth = 0.0;
	minFrustumHalfHeight = 0.0;
	logIfNeeded("ScopeCamera::DefaultState ctor Completed.");
}

ScopeCamera::DefaultState::~DefaultState() {
	logIfNeeded("ScopeCamera::DefaultState dtor Starting...");
	Heap_Free(this);
	logIfNeeded("ScopeCamera::DefaultState dtor Completed.");
}

bool ScopeCamera::DefaultState::ShouldHandleEvent(const InputEvent* inputEvent) { //TODO
	return false; //TEMP
}

void ScopeCamera::DefaultState::HandleEvent(const ButtonEvent* inputEvent) {  //TODO

}

void ScopeCamera::DefaultState::Begin() { //TODO: Add new members
	translation = NiPoint3_ZERO;
	zoom = 1.0;
}

void ScopeCamera::DefaultState::End() { //TODO

}

void ScopeCamera::DefaultState::Update(BSTSmartPointer<TESCameraState>& a_nextState) {  //TODO

}

void ScopeCamera::DefaultState::GetRotation(NiQuaternion& a_rotation) const {  //TODO

}

void ScopeCamera::DefaultState::GetTranslation(NiPoint3& a_translation) const {  //TODO

}

NiQuaternion& ScopeCamera::DefaultState::QInitialRotation()
{
	// TODO: insert return statement here
}

NiPoint3& ScopeCamera::DefaultState::QInitialPosition() {
	return initialPosition;
}

NiQuaternion& ScopeCamera::DefaultState::QRotation()
{
	// TODO: insert return statement here
}

NiPoint3& ScopeCamera::DefaultState::QTranslation()
{
	// TODO: insert return statement here
}

void ScopeCamera::DefaultState::SetInitialPosition(NiPoint3& newPos) {
	initialPosition = newPos;
}

void ScopeCamera::DefaultState::SetMinFrustum(float width, float height) {
	minFrustumHalfWidth = width * 0.5;
	minFrustumHalfHeight = height * 0.5;
}

void ScopeCamera::DefaultState::SetTranslation(NiPoint3& newPos) {
	translation = newPos;
}

void ScopeCamera::DefaultState::SetZoom(float newZoom) {
	zoom = newZoom;
}

ScopeCamera::ThermalState::ThermalState(TESCamera& cam, std::uint32_t ID) : DefaultState(cam, ID) {

}

ScopeCamera::ThermalState::~ThermalState()
{
}

bool ScopeCamera::ThermalState::ShouldHandleEvent(InputEvent* inputEvent)
{
	return false;
}

void ScopeCamera::ThermalState::OnButtonEvent(ButtonEvent* inputEvent)
{
}

void ScopeCamera::ThermalState::Begin()
{
}

void ScopeCamera::ThermalState::End()
{
}

void ScopeCamera::ThermalState::Update(TESCameraState* arg)
{
}

void ScopeCamera::ThermalState::GetRotation(NiQuaternion* out)
{
}

void ScopeCamera::ThermalState::GetPosition(NiPoint3* out)
{
}

ScopeCamera::NightVisionState::NightVisionState(TESCamera& cam, std::uint32_t ID) : DefaultState(cam, ID) {

}

ScopeCamera::NightVisionState::~NightVisionState()
{
}

bool ScopeCamera::NightVisionState::ShouldHandleEvent(InputEvent* inputEvent)
{
	return false;
}

void ScopeCamera::NightVisionState::OnButtonEvent(ButtonEvent* inputEvent)
{
}

void ScopeCamera::NightVisionState::Begin()
{
}

void ScopeCamera::NightVisionState::End()
{
}

void ScopeCamera::NightVisionState::Update(TESCameraState* arg)
{
}

void ScopeCamera::NightVisionState::GetRotation(NiQuaternion* out)
{
}

void ScopeCamera::NightVisionState::GetPosition(NiPoint3* out)
{
}
