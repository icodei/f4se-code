#include "Global.h"

NiCamera* scopePOV;
NiNode* scopePOVRoot;
NiCamera* scopePOV_BACKUP;
NiNode* scopePOVRoot_BACKUP;
BSCullingProcess* pScopeManagerCullingProc;
BSShaderAccumulator* pScopeManagerAccumulator;
ImageSpaceShaderParam* pScopeManagerShaderParam;

ScopeRenderer scopeRenderer;
BSReadWriteLock scopeRendererLock;
std::unordered_map<const char*, NiCamera*> s_extraCamerasMap;

void nsScope_CreateRenderer() {
	logIfNeeded("ScopeRenderer Creation Starting...");
	
	//create a spinlock
	scopeRendererLock = (*(BSReadWriteLock*)Heap_Allocate(sizeof(BSReadWriteLock)));
	logIfNeeded("ScopeRendererLock Allocated...");
	new(&scopeRendererLock) BSReadWriteLock();
	

	//if renderer is null
	if (!(&scopeRenderer)) {
		scopeRenderer = *nsScope_InitRenderer();
		//in nsPipboy_LocalMap::CreateRenderer this is where the localMapCameraUpdateEvent stuff would also be created
	}

	//Unlock
	if ((&scopeRendererLock)->lockValue == 1) {
		(&scopeRendererLock)->threadID = (&scopeRendererLock)->lockValue -1;
		_mm_mfence();
		InterlockedCompareExchange(&(&scopeRendererLock)->lockValue, (&scopeRendererLock)->lockValue - 1, (&scopeRendererLock)->lockValue);
	} else {
		InterlockedDecrement(&(&scopeRendererLock)->lockValue);
	}

	logIfNeeded("ScopeRenderer Creation Complete.");
}

ScopeRenderer* nsScope_InitRenderer() {
	logIfNeeded("ScopeRenderer Init Starting...");

	ScopeRenderer* renderer;
	ScopeRenderer* newRenderer;

	//allocate our renderer from MemoryManager
	renderer = (ScopeRenderer*)Heap_Allocate(sizeof(ScopeRenderer)); //LocalMapRenderer allocates 0x2B0 (688)
	logIfNeeded("ScopeRenderer Allocated...");
	//if allocated succesful
	if (renderer) {
		new(renderer) ScopeRenderer();
		newRenderer = renderer;
	} else {
		newRenderer = nullptr;
	}
	//if (TESObjectREFR::GetInterior(pPlayer._ptr)) {
	//	value = fLocalMapMinFrustumWidth_Interior_G._value;
	//}
	//} else {
	//	value = fLocalMapMinFrustumWidth_G._value;
	//}
	//a2 = pPlayer._ptr->data.location.NiPoint3;
	//if (TESObjectREFR::GetWorldSpace(pPlayer._ptr) && (TESObjectREFR::GetWorldSpace(pPlayer._ptr)->flags & 0x40) == 0) {
	//	WorldSpace = TESObjectREFR::GetWorldSpace(pPlayer._ptr);
	//	TESWorldSpace::AdjustMapMarkerCoord(WorldSpace, &a2, 0);
	//}
	//(&newRenderer->scopeCam)->SetInitialPosition(&a2);
	//(&newRenderer->scopeCam)->SetMinFrustum(value, value * 0.5625);
	//nsPipboy_LocalMap::GetLoadedAreaExtents(&a3, &v11, a1);
	//(&newRenderer->scopeCam)->SetExtents(&v12, &v11);
	//parentCell = pPlayer._ptr->parentCell;
	//if (parentCell) {
	//	NorthRotation = TESObjectCELL::GetNorthRotation((TESObjectCELL*)parentCell);
	//	(&newRenderer->scopeCam)->SetZRotation(&newLocalMapRenderer->LocalMapCamera, COERCE_FLOAT(LODWORD(NorthRotation) ^ _xmm.v.vector4_i.x));
	//}

	logIfNeeded("ScopeRenderer Init Complete.");
	return newRenderer;
}

void nsScope_Render() {
	
	NiTexture* renderedTexture;

	(&scopeRendererLock)->LockForReadAndWrite();
	if (&scopeRenderer) {
		renderedTexture = (&scopeRenderer)->Render(1);
		if (renderedTexture) {
			//if (texID string init) {
			//	stuff about localMapTextureID
			//	stuff
			//}
			//here there would be stuff for setting the renderedTexture to be the scaleform texture

			NiPointer<BSShaderProperty> shaderProperty;

			BSEffectShaderProperty* effectShaderProperty;
			BSEffectShaderMaterial* effectShaderMaterial;
			shaderProperty = ni_cast(ScopeTextureLoader->shaderProperty, BSShaderProperty);
			effectShaderProperty = ni_cast(shaderProperty, BSEffectShaderProperty);
			if (shaderProperty.get()) {
				effectShaderMaterial = static_cast<BSEffectShaderMaterial*>(shaderProperty->shaderMaterial);
				effectShaderMaterial->spBaseTexture = renderedTexture;
				effectShaderMaterial->fBaseColorScale = 1.0;
				effectShaderMaterial->kBaseColor = NiColorA(1.0, 1.0, 1.0, 1.0);
			}

			//BSLightingShaderProperty* lightingShaderProperty;
			//BSLightingShaderMaterial* lightingShaderMaterial;
			//shaderProperty = ni_cast(ScopeTextureLoader->shaderProperty, BSShaderProperty);
			//lightingShaderProperty = ni_cast(shaderProperty, BSLightingShaderProperty);
			//if (shaderProperty.get()) {
			//	lightingShaderMaterial = static_cast<BSLightingShaderMaterial*>(shaderProperty->shaderMaterial);
			//}
		}
	}

	//This seems to be unlocking the spinlock of the renderer after it's finished creating the renderer
	if ((&scopeRendererLock)->lockValue == 1) {
		(&scopeRendererLock)->threadID = 0;
		_mm_mfence();
		InterlockedCompareExchange(&(&scopeRendererLock)->lockValue, 0, (&scopeRendererLock)->lockValue);
	} else {
		InterlockedDecrement(&(&scopeRendererLock)->lockValue);
	}
	
	//scopeRendererLock->Unlock();
}

ScopeCamera::ScopeCamera() : TESCamera() {
	logIfNeeded("ScopeCamera ctor Starting...");

	NiCamera* cam;
	NiCamera* newCamera;
	NiCamera* oldCam;

	NiNode* node;
	NiNode* newNode;

	NiNode* camRootNode;

	cam = (NiCamera*)CreateNS_NiCamera_Create();
	if (cam) {
		new(cam) NiCamera();
		newCamera = cam;
		logIfNeeded("ScopeCamera - Created NiCamera");
	} else {
		newCamera = nullptr;
		logIfNeeded("ScopeCamera - NiCamera Creation FAILED");
	}
	oldCam = camera;
	if (oldCam != newCamera) {
		if (newCamera) {
			InterlockedIncrement(&newCamera->m_uiRefCount);
		}
		camera = newCamera;
		if (oldCam && !InterlockedDecrement(&oldCam->m_uiRefCount)) {
			oldCam->DeleteThis();
		}
	}

	node = (NiNode*)CreateNS_NiNode_Create();
	if (node) {
		new(node) NiNode(1);
		newNode = node;
		logIfNeeded("ScopeCamera - Created NiNode");
		
	} else {
		newNode = nullptr;
		logIfNeeded("ScopeCamera - NiNode Creation FAILED");
	}
	camRootNode = cameraNode;
	if (camRootNode != newNode) {
		if (newNode) {
			InterlockedIncrement(&newNode->m_uiRefCount);
		}
		cameraNode = newNode;
		if (camRootNode && !InterlockedDecrement(&camRootNode->m_uiRefCount)) {
			camRootNode->DeleteThis();
		}
	}
	cameraNode->AttachChild(camera, true);

	ScopeCamera::DefaultState* camDefaultState;
	TESCameraState* oldCamState;
	camDefaultState = (ScopeCamera::DefaultState*)Heap_Allocate(sizeof(ScopeCamera::DefaultState));
	if (camDefaultState) { //TODO: Add new members
		camDefaultState->m_refCount = 0;
		camDefaultState->camera = this;
		camDefaultState->stateID = 0;
		camDefaultState->initialPosition = NiPoint3_ZERO;
		camDefaultState->translation = NiPoint3_ZERO;
		camDefaultState->zoom = 1.0;
		camDefaultState->minFrustumHalfWidth = 0.0;
		camDefaultState->minFrustumHalfHeight = 0.0;
		logIfNeeded("ScopeCamera - Created ScopeCamera::DefaultState");
	} else {
		camDefaultState = nullptr;
		logIfNeeded("ScopeCamera - ScopeCamera::DefaultState Creation FAILED");
	}
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
	//this->SetState(this->defaultState); //This is crashing. Idk why
	logIfNeeded("ScopeCamera ctor Completed.");
}

ScopeCamera::~ScopeCamera() { //TODO

}

void ScopeCamera::SetCameraNode(NiNode* node) { //TODO

}

void ScopeCamera::SetEnabled(bool enabled) { //TODO

}

void ScopeCamera::Update() { //TODO

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

ScopeCamera::DefaultState::DefaultState(TESCamera& cam, UInt32 ID) : TESCameraState(cam, ID) { //TODO: Add new members
	logIfNeeded("ScopeCamera::DefaultState ctor Starting...");
	m_refCount = 0;
	camera = &cam;
	stateID = ID;

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

bool ScopeCamera::DefaultState::ShouldHandleEvent(InputEvent* inputEvent) { //TODO
	return false; //TEMP
}

void ScopeCamera::DefaultState::OnKinectEvent(KinectEvent* inputEvent) { //TODO

}

void ScopeCamera::DefaultState::OnDeviceConnectEvent(DeviceConnectEvent* inputEvent) { //TODO

}

void ScopeCamera::DefaultState::OnThumbstickEvent(ThumbstickEvent* inputEvent) { //TODO

}

void ScopeCamera::DefaultState::OnCursorMoveEvent(CursorMoveEvent* inputEvent) { //TODO

}

void ScopeCamera::DefaultState::OnMouseMoveEvent(MouseMoveEvent* inputEvent) { //TODO

}

void ScopeCamera::DefaultState::OnCharacterEvent(CharacterEvent* inputEvent) { //TODO

}

void ScopeCamera::DefaultState::OnButtonEvent(ButtonEvent* inputEvent) { //TODO

}

void ScopeCamera::DefaultState::Begin() { //TODO: Add new members
	translation = NiPoint3_ZERO;
	zoom = 1.0;
}

void ScopeCamera::DefaultState::End() { //TODO

}

void ScopeCamera::DefaultState::Update(TESCameraState* arg) { //TODO

}

void ScopeCamera::DefaultState::GetRotation(NiQuaternion* out) { //TODO

}

void ScopeCamera::DefaultState::GetPosition(NiPoint3* out) { //TODO

}

NiPoint3& ScopeCamera::DefaultState::QInitialPosition() {
	return initialPosition;
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

ScopeRenderer::ScopeRenderer() {
	logIfNeeded("ScopeRenderer ctor Starting...");

	BSShaderAccumulator* shaderAccum;
	BSShaderAccumulator* newShaderAccum;
	BSShaderAccumulator* oldShaderAccum;
	BSShaderAccumulator* pShaderAccum;

	logIfNeeded("ScopeRenderer - Creating BSCullingProcess...");
	new(&scopeCullingProc) BSCullingProcess(0);
	logIfNeeded("ScopeRenderer - Creating ScopeCamera...");
	new(&scopeCam) ScopeCamera();
	logIfNeeded("ScopeRenderer - Creating ImageSpaceShaderParam...");
	new(&params) ImageSpaceShaderParam();
	//spScopeAccumulator = nullptr;

	shaderAccum = (BSShaderAccumulator*)Heap_Allocate(0x590);
	if (shaderAccum) {
		new(shaderAccum) BSShaderAccumulator();
		newShaderAccum = shaderAccum;
		logIfNeeded("ScopeRenderer - Created BSShaderAccumulator");
	} else {
		newShaderAccum = nullptr;
		logIfNeeded("ScopeRenderer - BSShaderAccumulator Creation FAILED");
	}
	oldShaderAccum = spScopeAccumulator;
	if ((oldShaderAccum != newShaderAccum) || (spScopeAccumulator == nullptr)) {
		if (newShaderAccum) {
			InterlockedIncrement(&newShaderAccum->m_uiRefCount);
		}
		spScopeAccumulator = newShaderAccum;
		if (oldShaderAccum && !InterlockedDecrement(&oldShaderAccum->m_uiRefCount)) {
			oldShaderAccum->DeleteThis();
		}
	}
	spScopeAccumulator->QZPrePass = 1;
	spScopeAccumulator->ShadowSceneNode = (*ShaderManager_gState).pShadowSceneNode[0];
	pShaderAccum = spScopeAccumulator;
	pShaderAccum->QSilhouetteColor.r = 1.0;
	pShaderAccum->QSilhouetteColor.g = 1.0;
	pShaderAccum->QSilhouetteColor.b = 1.0;
	pShaderAccum->QSilhouetteColor.a = 1.0;
	(&scopeCullingProc)->SetAccumulator(this->spScopeAccumulator);
	scopeCullingProc.CullingType = BSCullingProcess::BSCPCullingType::kIgnoreMultiBounds;
	scopeCullingProc.m_bCameraRelatedUpdates = 0;
	(&params)->ResizeConstantGroup(0, 1);
	//field_2A4 = 18; //LocalMapRenderer
	type = 19;

	logIfNeeded("ScopeRenderer ctor Completed.");
}

ScopeRenderer::~ScopeRenderer() {
	//NiAVObject* overlayObjMaybe;
	BSShaderAccumulator* shaderAccum;
	NiCamera* cam;
	TESCameraState* state;

	//overlayObjMaybe = this->overlayObjMaybe;
	//if (overlayObjMaybe && !_InterlockedDecrement(&overlayObjMaybe->m_uiRefCount)) {
	//	overlayObjMaybe->DeleteThis();
	//}
	(&params)->~ImageSpaceShaderParam();
	shaderAccum = spScopeAccumulator;
	if (shaderAccum && !InterlockedDecrement(&shaderAccum->m_uiRefCount)) {
		shaderAccum->DeleteThis();
	}
	cam = scopeCam.camera;
	if (cam && !InterlockedDecrement(&cam->m_uiRefCount)) {
		cam->DeleteThis();
	}
	state = scopeCam.currentState;
	if (state && !InterlockedDecrement(&state->m_refCount)) {
		state->~TESCameraState();
	}
	(&scopeCam)->~ScopeCamera();
	(&scopeCullingProc)->~BSCullingProcess();
}

ScopeRenderer& ScopeRenderer::operator=(const ScopeRenderer& rhs) {
	memcpy(&scopeCullingProc, &rhs.scopeCullingProc, 0x1A0);
	//scopeCullingProc = rhs.scopeCullingProc;
	scopeCam = rhs.scopeCam;
	spScopeAccumulator = rhs.spScopeAccumulator;
	params = rhs.params;
	type = rhs.type;
}

NiTexture* ScopeRenderer::Render(bool a1) {
	
	ScopeRenderer* pScopeRenderer = (this);
	ScopeCamera* scopeCam = (&pScopeRenderer->scopeCam);
	
	NiCamera* shaderCam = (*BSShaderManager_spCamera);
	
	BSCullingProcess scopeCulling;
	new(&scopeCulling) BSCullingProcess(0);
	
	ShadowSceneNode* pShadow = (*ShaderManager_gState).pShadowSceneNode[0];
	ShadowSceneNode* pShadow2 = (*ShaderManager_gState).pShadowSceneNode[0];
	NiAVObject* obj = (*ShaderManager_gState).pShadowSceneNode[0]->m_children.m_data[3];
	NiAVObject* pObj = obj;
	if ( obj ) {
		InterlockedIncrement(&obj->m_uiRefCount);
	}
	bool objCullFlag = obj->flags & 1;
	obj->SetAppCulled(1);
	
	//grassNode = BSTSingletonSDMBase<BGSGrassManager>::QInstancePtr::pinstanceS->QGrassNode;
	//pGrassNode = grassNode;
	//if ( grassNode ) {
	//	InterlockedIncrement(&grassNode->m_uiRefCount);
	//}
	//grassNodeCullFlag = grassNode->flags & 1;
	//bGrassNodeCullFlag = grassNodeCullFlag;
	//grassNode->SetAppCulled(grassNode, 0);
	//BSDistantObjectInstanceRenderer::QInstance() /*Member at 112*/ = 0;
	
	(*BSShaderManager_spCamera) = scopeCam->camera;

	(BSGraphics_gState)->SetCameraData(scopeCam->camera, 0, 0.0, 1.0);
	(&scopeCulling)->SetAccumulator(pScopeRenderer->spScopeAccumulator.m_pObject);
	(&scopeCulling)->CullingType = BSCullingProcess::BSCPCullingType::kIgnoreMultiBounds;
	(&scopeCulling)->m_bCameraRelatedUpdates = 0;
	(&scopeCulling)->m_pkCamera = scopeCam->camera;

	scopeCam->Update();

	//DisableLightUpdate = pShadow->DisableLightUpdate;
	//pShadow->DisableLightUpdate = 1;
	//bLightUpdate = DisableLightUpdate;
	//fadeEnabled = BSFadeNode::bFadeEnabled;
	//BSFadeNode::bFadeEnabled = 0;
	//BSFadeNode::bDrawFadingEnabled = 0;
	//BSFadeNode::iFadeEnableCounter = 0;
	//bFadeEnabled = fadeEnabled;

	(BSGraphics_gRenderer)->SetClearColor(1.0, 1.0, 1.0, 1.0);

	//waterEnabled = localRenderer->field_2A4 == 37;
	//r = BSWaterShaderProperty::WaterColorMult.r;
	//g = BSWaterShaderProperty::WaterColorMult.g;
	//b = BSWaterShaderProperty::WaterColorMult.b;
	//waterPropertyEnabled = BSWaterShaderProperty::bEnabled;
	//BSWaterShaderProperty::WaterColorMult.r = 10.0;
	//BSWaterShaderProperty::WaterColorMult.g = 10.0;
	//a = BSWaterShaderProperty::WaterColorMult.a;
	//BSWaterShaderProperty::WaterColorMult.b = FLOAT_60;
	//BSWaterShaderProperty::bEnabled = waterEnabled;
	//bWaterEnabled = waterPropertyEnabled;
	//waterSimpleEnabled = BSShaderAccumulator::bSimpleWaterMode;
	//BSShaderAccumulator::bSimpleWaterMode = 1;
	//bWaterSimple = waterSimpleEnabled;

	pScopeRenderer->spScopeAccumulator.m_pObject->renderMode = BSShaderManager::etRenderMode::unk18;
	pScopeRenderer->spScopeAccumulator.m_pObject->QEyePosition = scopeCam->camera->m_worldTransform.pos;
	(BSGraphics_gRenderer)->ResetZPrePass();

	//In LocalMapRenderer::Render this is where the going through arrays of TESObjectCells starts
	//if (!bCullLocalMap._value) {
	//	unk = TES->unk[88];
	//	if (unk) {
	//		goto LABEL_10;
	//	}
	//	//while loop stuff of GridCellArrays and then AccumulateSceneFunctor on those GridCell Arrays
	//	if (cells) {	
	//		while(thing == 1) {
	//			stuff
	//			more stuff
	//			if (thing != 1) {
	//				break;
	//			}
	//			goto LABEL_50;
	//		}
	//	} else {
	//	LABEL_50:
	//		SkyCell = TES::GetSkyCell(pTes);
	//		if (SkyCell && SkyCell->cellState._impl == 8) {
	//			AccumulateSceneFunctor::operator()(&pCull, SkyCell);
	//		}
	//	}
	//	LABEL_53:
	//	pShadow = pShadow2;
	//	localRenderer = this;
	//	goto LABEL_54;
	//}
	//v17 = *(TESObjectCELL**)&tes->unk[88];
	//if (!v17) {
	//	BSTObjectArenaScrapAllocBase::BSTObjectArenaScrapAllocBase((BSTObjectArenaScrapAllocBase*)&objArenaCell);
	//	objArenaCell._tail = (BSTObjectArena::Page::TESObjectCELL*)&objArenaCell._next;
	//	objArenaCell._next = 0i64;
	//	memset(&objArenaCell._free, 0, 32);
	//	a2_120 = 0;
	//	TESObjectCELL::GetOverlappedCells(&localRenderer->LocalMapCamera.minExtent, &localRenderer->LocalMapCamera.maxExtent, &objArenaCell);
	//	arraySizeMaybe = a2_120;
	//	if (localRenderer->type == 20 && a2_120 > uiCompanionLocalMapMaxCells._value) {
	//		BSTArrayHeapAllocator::BSTArrayHeapAllocator(&array);
	//		BSTArrayBase::BSTArrayBase(&array.BSTArrayBase);
	//		a2_128[0].__vftable = (BSTArrayBase::IAllocatorFunctor_vtbl*)&BSTArrayAllocatorFunctor<BSTArrayHeapAllocator>::`vftable';
	//			a2_128[1].__vftable = (BSTArrayBase::IAllocatorFunctor_vtbl*)&array;
	//		BSTArrayBase::InitialReserve(&array.BSTArrayBase, a2_128, arraySizeMaybe, 8u);
	//		a2_48 = &array;
	//		BSTObjectArena<TESObjectCELL*, BSTObjectArenaScrapAlloc, 32>::ForEach<_lambda_74ce9d00abd68d954279d61887a28760_>(&objArenaCell, &a2_48);
	//		sorter = NearestCellSort;
	//			if (array.QSize > 1) {
	//				v19 = array.QSize - 1;
	//				v20 = (TESObjectCELL**)array.QBuffer[0];
	//				v21 = 0i64;
	//				for (i = array.QSize - 1; ; v27[i] = v28) {
	//					do {
	//						if (sorter(*((TESObjectCELL**)array.QBuffer[0] + i), *v20) <= 0) {
	//							break;
	//						}
	//						--i;
	//					} while ((unsigned int)v21 < i);
	//					if ((unsigned int)v21 >= i) {
	//						break;
	//					}
	//					v23 = 8 * v21;
	//					while (sorter(*(TESObjectCELL**)((char*)array.QBuffer[0] + v23), *v20) <= 0) {
	//						v21 = (unsigned int)(v21 + 1);
	//						v23 += 8i64;
	//						if ((unsigned int)v21 >= i) {
	//							goto LABEL_22;
	//						}
	//					}
	//					v27 = array.QBuffer[0];
	//					v28 = *((_QWORD*)array.QBuffer[0] + v21);
	//					*((_QWORD*)array.QBuffer[0] + v21) = *((_QWORD*)array.QBuffer[0] + i);
	//				}
	//			LABEL_22:
	//				v24 = array.QBuffer[0];
	//				v25 = *(_QWORD*)array.QBuffer[0];
	//				*(_QWORD*)array.QBuffer[0] = *((_QWORD*)array.QBuffer[0] + i);
	//				v24[i] = v25;
	//				if (i) {
	//					ArrayQuickSortRecursive<TESObjectCELL*, int (*)(TESObjectCELL*, TESObjectCELL*), BSTArrayHeapAllocator>(&array, &sorter, 0i64, i - 1);
	//				}
	//				if (i < array.QSize - 1) {
	//					ArrayQuickSortRecursive<TESObjectCELL*, int (*)(TESObjectCELL*, TESObjectCELL*), BSTArrayHeapAllocator>(&array, &sorter, i + 1, v19);
	//				}
	//			}
	//		for (j = 0i64; (unsigned int)j < uiCompanionLocalMapMaxCells._value; j = (unsigned int)(j + 1)) {
	//			AccumulateSceneFunctor::operator()(&pCull, *((TESObjectCELL **)array.QBuffer[0] + j));
	//		}
	//		if (array.QBuffer[0]) {
	//			BSTArrayHeapAllocator::Deallocate(&array);
	//			array.QSize = 0;
	//		}
	//		BSTArrayBase::~BSTArrayBase(&array.BSTArrayBase);
	//		BSTArrayHeapAllocator::~BSTArrayHeapAllocator(&array);
	//		BSTObjectArena<TESObjectCELL*, BSTObjectArenaScrapAlloc, 32>::~BSTObjectArena<TESObjectCELL*, BSTObjectArenaScrapAlloc, 32>(&objArenaCell);
	//	} else {
	//		next = objArenaCell._next;
	//		ppCell = *(TESObjectCELL***)&objArenaCell._size;
	//		v31 = 1;
	//		v32 = objArenaCell._next + 32;
	//		*(_OWORD*)&pCull2 = *(_OWORD*)&pCull;
	//		if (a2_120) {
	//			do {
	//				--arraySizeMaybe;
	//				if (v31 != 1) {
	//					break;
	//				}
	//				v31 = AccumulateSceneFunctor::operator()(&pCull2, *ppCell++);
	//					if (ppCell >= (TESObjectCELL**)v32) {
	//						next = (BSTObjectArena::Page::TESObjectCELL**)next[32];
	//						if (next) {
	//							ppCell = (TESObjectCELL**)next;
	//							v32 = next + 32;
	//						}
	//					}
	//			} while (arraySizeMaybe);
	//		}
	//		BSTObjectArena<TESObjectCELL*, BSTObjectArenaScrapAlloc, 32>::~BSTObjectArena<TESObjectCELL*, BSTObjectArenaScrapAlloc, 32>(&objArenaCell);
	//	}
	//	goto LABEL_53;
	//}
	//LABEL_10:
	//AccumulateSceneFunctor::operator()(&pCull, v17);
	//LABEL_54:
	//
	
	BSPortalGraphEntry* camPortalEntry = (*appMain)->GetCameraPortalGraphEntry();
	NiAVObject* pChildAt9;
	if (camPortalEntry) {
		BSPortalGraph* camPortalGraph = camPortalEntry->QPortalGraph;
		if (camPortalGraph) {
			BSShaderUtil::AccumulateSceneArray(scopeCam->camera, &camPortalGraph->QAlwaysRenderArray, scopeCulling, 0);
		}
	}
	if (pShadow->m_children.m_emptyRunStart > 9) {
		pChildAt9 = pShadow->m_children.m_data[9];
	} else {
		pChildAt9 = nullptr;
	}
	BSShaderUtil::AccumulateScene(scopeCam->camera, pChildAt9, scopeCulling, 0);
	NiAVObject* pChildAt8;
	if (pShadow->m_children.m_emptyRunStart > 8) {
		pChildAt8 = pShadow->m_children.m_data[8];
	} else {
		pChildAt8 = nullptr;
	}
	BSShaderUtil::AccumulateScene(scopeCam->camera, pChildAt8, scopeCulling, 0);
	(*ShaderManager_gState).uiCurrentSceneGraph = 0;
	(*ShaderManager_gState).pShadowSceneNode[0]->ProcessQueuedLights(&scopeCulling);
	(BSGraphics_gRenderer)->ResetState();
	int depthTarget = 1;
	int renderTarget = 27;
	int newRenderTarget = 22;
	if (pScopeRenderer->type == 20) {
		depthTarget = 11;
	}
	newRenderTarget = (pScopeRenderer->type == 20) + 22;
	if (pScopeRenderer->type == 20) {
		renderTarget = 21;
	}
	if (pScopeRenderer->type == 20) {
		(BSGraphics_gRenderTargetManager)->AcquireDepthStencil(depthTarget);
		(BSGraphics_gRenderTargetManager)->AcquireRenderTarget(renderTarget);
	}
	(BSGraphics_gRenderTargetManager)->AcquireRenderTarget(newRenderTarget);
	RenderScopeScene(scopeCam->camera, pScopeRenderer->spScopeAccumulator.m_pObject, newRenderTarget, renderTarget, depthTarget);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(0, 2, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(1, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics_gRenderTargetManager)->SetCurrentDepthStencilTarget(1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, 0);
	//FogOfWar Setup stuff would happen after this in the LocalMapRenderer::Render
	//stuff and things
	//
	(BSGraphics_gRenderTargetManager)->SetCurrentDepthStencilTarget(0, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, 0);
	(&pScopeRenderer->params)->SetPixelConstant(
		0,
		1.0 / (float)(int)(*BSGraphics_gRenderTargetManager).pRenderTargetDataA[pScopeRenderer->type].uiWidth,
		1.0 / (float)(int)(*BSGraphics_gRenderTargetManager).pRenderTargetDataA[pScopeRenderer->type].uiHeight,
		0.0,
		0.0);
	(BSGraphics_gRenderTargetManager)->SetTextureDepth(1, depthTarget);
	(BSGraphics_gRenderTargetManager)->SetTextureRenderTarget(2, renderTarget, 0);
	int effect = ((pScopeRenderer->type == 20) + 152);
	(*ImageSpaceManager_pInstance)->effectArray.m_data[effect].UseDynamicResolution = 0;
	(*ImageSpaceManager_pInstance)->RenderEffectHelper_2((ImageSpaceManager::ImageSpaceEffectEnum)effect, newRenderTarget, pScopeRenderer->type, &pScopeRenderer->params);
	if (pScopeRenderer->type == 20) {
		(BSGraphics_gRenderTargetManager)->ReleaseDepthStencil(depthTarget);
		(BSGraphics_gRenderTargetManager)->ReleaseRenderTarget(renderTarget);
	}
	(BSGraphics_gRenderTargetManager)->ReleaseRenderTarget(newRenderTarget);
	//Threaded stuff would happen here in LocalMapRenderer::Render
	//BSGraphics::Context = threaded stuff
	//if (!context) {
	//		context = BSGraphics::pDefaultContext
	//}
	//shadowState = &context->field_1B70;
	//Texture dirty stuff
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(0, 1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	NiTexture* renderedTexture = nullptr;
	BSGraphics::Texture* graphicsTex = nullptr;
	if (a1) {
		BSFixedString strScope("ScopeTexture");
		renderedTexture = renderedTexture->CreateEmpty(strScope, 0, 0);
		graphicsTex = (BSGraphics_gRenderTargetManager)->SaveRenderTargetToTexture(19, 0, 0, BSGraphics::Usage::USAGE_DEFAULT);
		renderedTexture->rendererData = reinterpret_cast<BSRenderData*>(graphicsTex);
	}
	//BSScaleformRenderer::SetCurrentRenderTarget
	(*BSShaderManager_spCamera) = shaderCam;
	(BSGraphics_gState)->SetCameraData(shaderCam, 0, 0.0, 1.0);
	//pShadow2->DisableLightUpdate = bLightUpdate;
	//BSFadeNode::iFadeEnableCounter = 0;
	//BSWaterShaderProperty::WaterColorMult.r = r;
	//BSWaterShaderProperty::WaterColorMult.g = g;
	//BSWaterShaderProperty::WaterColorMult.b = b;
	//BSShaderAccumulator::bSimpleWaterMode = bWaterSimple;
	//BSWaterShaderProperty::WaterColorMult.a = a;
	//BSFadeNode::bFadeEnabled = bFadeEnabled;
	//BSFadeNode::bDrawFadingEnabled = bFadeEnabled;
	//BSWaterShaderProperty::bEnabled = bWaterEnabled;
	pScopeRenderer->spScopeAccumulator->ClearActivePasses(0);
	pScopeRenderer->spScopeAccumulator->ClearGroupPasses(5, 0);
	(&scopeCulling)->~BSCullingProcess();
	//pOldGrassNode = pGrassNode;
	//pGrassNode->SetAppCulled(pGrassNode, grassNodeCullFlag);
	//if (!_InterlockedDecrement(&pOldGrassNode->refCount)) {
	//	pOldGrassNode->DeleteThis(pOldGrassNode);
	//}
	obj->SetAppCulled(objCullFlag);
	if (!InterlockedDecrement(&obj->m_uiRefCount)) {
		obj->DeleteThis();
	}
	return renderedTexture;
}

void RenderScopeScene(NiCamera* cam, BSShaderAccumulator* shadeAccum, SInt32 a1, SInt32 a2, SInt32 a3) {
	(BSGraphics_gRenderTargetManager)->SetCurrentDepthStencilTarget(a3, BSGraphics::SetRenderTargetMode::SRTM_FORCE_COPY_RESTORE, 0, 0);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(0, a1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(1, a2, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(2, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(3, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	if ((*ShaderManager_gState).unk56) {
		(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(4, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	}
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(5, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics_gRenderTargetManager)->SetCurrentViewportForceToRenderTargetDimensions();
	(BSGraphics_gRenderer)->SetClearColor(0.0, 0.0, 0.0, 0.0);
	(BSGraphics_gRenderer)->ClearColor();
	(BSGraphics_gRenderer)->Flush();
	//Threaded stuff happens here in RenderLocalMapScene
	//stuff
	//more stuff
	(BSGraphics_gState)->SetCameraData(cam, 0, 0.0, 1.0);
	(BSGraphics_gRenderer)->DoZPrePass(0, 0, 0.0, 1.0, 0.0, 1.0);
	shadeAccum->RenderOpaqueDecals();
	shadeAccum->RenderBatches(4, 0, -1);
	shadeAccum->RenderBlendedDecals();
	//BSGraphics::pDefaultContext stuff happens here in RenderLocalMapScene
	//stuff
	//more stuff
	(BSGraphics_gRenderer)->Flush();
	(BSGraphics_gRenderer)->SetClearColor(1.0, 1.0, 1.0, 1.0);
	//more context stuff
	//more things
	shadeAccum->ClearEffectPasses();
	shadeAccum->ClearActivePasses(0);
}

//ScopeRendererManager

void ScopeRendererManager::Setup() {
	logIfNeeded("ScopeRendererManager Setup Starting...");

	logIfNeeded("ScopeRendererManager - Creating BSCullingProcess...");
	BSCullingProcess* currentCullingProcess;
	BSCullingProcess* cullingProcess;
	BSCullingProcess* newCullingProcess;

	cullingProcess = (BSCullingProcess*)Heap_Allocate(0x1A0);
	if (cullingProcess) {
		new(cullingProcess) BSCullingProcess(0);
		newCullingProcess = cullingProcess;
		logIfNeeded("ScopeRendererManager - Created BSCullingProcess");
	} else {
		newCullingProcess = nullptr;
		logIfNeeded("ScopeRendererManager - BSCullingProcess Creation FAILED");
	}
	currentCullingProcess = pScopeManagerCullingProc;
	if (currentCullingProcess != newCullingProcess) {
		pScopeManagerCullingProc = newCullingProcess;
		if (currentCullingProcess) {
			currentCullingProcess->~BSCullingProcess();
		}
	}

	logIfNeeded("ScopeRendererManager - Creating Cameras...");

	logIfNeeded("ScopeRendererManager - Creating NiCamera...");
	NiCamera* currentCam;
	NiCamera* cam;
	NiCamera* newCam;

	cam = (NiCamera*)CreateNS_NiCamera_Create();
	if (cam) {
		//CreateNS_NiCamera_Create already constructs using NiCamera::NiCamera() we do not need to do it again
		//new(cam) NiCamera();
		newCam = cam;
		logIfNeeded("ScopeRendererManager - Created NiCamera");
	} else {
		newCam = nullptr;
		logIfNeeded("ScopeRendererManager - NiCamera Creation FAILED");
	}
	currentCam = scopePOV;
	if (currentCam != newCam) {
		if (newCam) {
			InterlockedIncrement(&newCam->m_uiRefCount);
		}
		scopePOV = newCam;
		scopePOV_BACKUP = newCam;
		if (currentCam && !InterlockedDecrement(&currentCam->m_uiRefCount)) {
			currentCam->DeleteThis();
		}
	}

	logIfNeeded("ScopeRendererManager - Creating NiCameraRootNode...");
	NiNode* currentNode;
	NiNode* node;
	NiNode* newNode;

	node = (NiNode*)CreateNS_NiNode_Create();
	if (node) {
		new(node) NiNode(1);
		if ((*g_playerCamera)) {
			node->m_localTransform.pos.x = (*g_playerCamera)->translationInput.x;
			node->m_localTransform.pos.y = (*g_playerCamera)->translationInput.y + 5.0;
			node->m_localTransform.pos.z = (*g_playerCamera)->translationInput.z;
		}
		newNode = node;
		logIfNeeded("ScopeRendererManager - Created NiNode");

	} else {
		newNode = nullptr;
		logIfNeeded("ScopeRendererManager - NiNode Creation FAILED");
	}
	currentNode = scopePOVRoot;
	if (currentNode != newNode) {
		if (newNode) {
			InterlockedIncrement(&newNode->m_uiRefCount);
		}
		scopePOVRoot = newNode;
		scopePOVRoot_BACKUP = newNode;
		//float FOV = (*g_playerCamera)->fDefault1stPersonFOV;
		BSShaderUtil_SetCameraFOV((*Main__spWorldSceneGraph), (float)(90.0 / 4.0), 0, scopePOV, 1); //TEMP. Right now I just have it as 4x zoom
		if (currentNode && !InterlockedDecrement(&currentNode->m_uiRefCount)) {
			currentNode->DeleteThis();
		}
	}
	scopePOVRoot->AttachChild(scopePOV, true);
	logIfNeeded("ScopeRendererManager Cameras Completed.");

	logIfNeeded("ScopeRendererManager - Creating ImageSpaceShaderParam...");
	ImageSpaceShaderParam* currentShaderParam;
	ImageSpaceShaderParam* shaderParam;
	ImageSpaceShaderParam* newShaderParam;

	shaderParam = (ImageSpaceShaderParam*)Heap_Allocate(0x90);
	if (shaderParam) {
		new(shaderParam) ImageSpaceShaderParam();
		newShaderParam = shaderParam;
		logIfNeeded("ScopeRendererManager - Created ImageSpaceShaderParam");
	} else {
		newShaderParam = nullptr;
		logIfNeeded("ScopeRendererManager - ImageSpaceShaderParam Creation FAILED");
	}
	currentShaderParam = pScopeManagerShaderParam;
	if (currentShaderParam != newShaderParam) {
		pScopeManagerShaderParam = newShaderParam;
		if (currentShaderParam) {
			currentShaderParam->~ImageSpaceShaderParam();
		}
	}
	
	logIfNeeded("ScopeRendererManager - Creating BSShaderAccumulator...");
	BSShaderAccumulator* currentShaderAccumulator;
	BSShaderAccumulator* shaderAccumulator;
	BSShaderAccumulator* newShaderAccumulator;

	shaderAccumulator = (BSShaderAccumulator*)Heap_Allocate(0x590);
	if (shaderAccumulator) {
		new(shaderAccumulator) BSShaderAccumulator();
		newShaderAccumulator = shaderAccumulator;
		logIfNeeded("ScopeRendererManager - Created BSShaderAccumulator");
	} else {
		newShaderAccumulator = nullptr;
		logIfNeeded("ScopeRendererManager - BSShaderAccumulator Creation FAILED");
	}
	currentShaderAccumulator = pScopeManagerAccumulator;
	if (currentShaderAccumulator != newShaderAccumulator) {
		if (newShaderAccumulator) {
			InterlockedIncrement(&newShaderAccumulator->m_uiRefCount);
		}
		pScopeManagerAccumulator = newShaderAccumulator;
		if (currentShaderAccumulator && !InterlockedDecrement(&currentShaderAccumulator->m_uiRefCount)) {
			currentShaderAccumulator->DeleteThis();
		}
	}
	pScopeManagerAccumulator->QZPrePass = 1;
	pScopeManagerAccumulator->ShadowSceneNode = (*ShaderManager_gState).pShadowSceneNode[0];
	pScopeManagerAccumulator->QSilhouetteColor.r = 1.0;
	pScopeManagerAccumulator->QSilhouetteColor.g = 1.0;
	pScopeManagerAccumulator->QSilhouetteColor.b = 1.0;
	pScopeManagerAccumulator->QSilhouetteColor.a = 1.0;
	pScopeManagerCullingProc->SetAccumulator(pScopeManagerAccumulator);
	pScopeManagerCullingProc->CullingType = BSCullingProcess::BSCPCullingType::kIgnoreMultiBounds;
	pScopeManagerCullingProc->m_bCameraRelatedUpdates = 0;
	pScopeManagerShaderParam->ResizeConstantGroup(0, 1);
	readyForRender = true;
	logIfNeeded("ScopeRendererManager Setup Completed.");
}

//Delete the current stored values and objects we have created so far. I don't think DestroyRenderTarget is needed but idk. I'm still not sure how rendertargets work
void ScopeRendererManager::Shutdown() {

}

//I'm not too sure about this one. Mostly a test to see if ReleaseRenderTarget is a thing I need to do or not
void ScopeRendererManager::Pause() {

}

void ScopeRendererManager::RenderHelper(bool save) {
	//logIfNeeded("ScopeRendererManager Rendering...");
	NiTexture* renderedTexture;
	renderedTexture = ScopeRendererManager::Render(save);
	if (renderedTexture) {
		//if (texID string init) {
		//	stuff about localMapTextureID
		//	stuff
		//}
		//here there would be stuff for setting the renderedTexture to be the scaleform texture

		NiPointer<BSShaderProperty> shaderProperty;

		BSEffectShaderProperty* effectShaderProperty;
		BSEffectShaderMaterial* effectShaderMaterial;
		shaderProperty = ni_cast(ScopeTextureLoader->shaderProperty, BSShaderProperty);
		effectShaderProperty = ni_cast(shaderProperty, BSEffectShaderProperty);
		if (shaderProperty.get()) {
			effectShaderMaterial = static_cast<BSEffectShaderMaterial*>(shaderProperty->shaderMaterial);
			effectShaderMaterial->spBaseTexture = renderedTexture;
			//effectShaderMaterial->fBaseColorScale = 1.0;
			//effectShaderMaterial->kBaseColor = NiColorA(1.0, 1.0, 1.0, 1.0);
		}

		//BSLightingShaderProperty* lightingShaderProperty;
		//BSLightingShaderMaterial* lightingShaderMaterial;
		//shaderProperty = ni_cast(ScopeTextureLoader->shaderProperty, BSShaderProperty);
		//lightingShaderProperty = ni_cast(shaderProperty, BSLightingShaderProperty);
		//if (shaderProperty.get()) {
		//	lightingShaderMaterial = static_cast<BSLightingShaderMaterial*>(shaderProperty->shaderMaterial);
		//}
	}
}

NiTexture* ScopeRendererManager::Render(bool save) {
	NiCamera* shaderCam = (*BSShaderManager_spCamera);

	BSCullingProcess* scopeCulling = pScopeManagerCullingProc;

	ShadowSceneNode* pShadow = (*ShaderManager_gState).pShadowSceneNode[0];
	ShadowSceneNode* pShadow2 = (*ShaderManager_gState).pShadowSceneNode[0];
	NiAVObject* obj = (*ShaderManager_gState).pShadowSceneNode[0]->m_children.m_data[3];
	NiAVObject* pObj = obj;
	if (obj) {
		InterlockedIncrement(&obj->m_uiRefCount);
	}
	bool objCullFlag = obj->flags & 1;
	obj->SetAppCulled(1);

	//grassNode = BSTSingletonSDMBase<BGSGrassManager>::QInstancePtr::pinstanceS->QGrassNode;
	//pGrassNode = grassNode;
	//if ( grassNode ) {
	//	InterlockedIncrement(&grassNode->m_uiRefCount);
	//}
	//grassNodeCullFlag = grassNode->flags & 1;
	//bGrassNodeCullFlag = grassNodeCullFlag;
	//grassNode->SetAppCulled(grassNode, 0);
	//BSDistantObjectInstanceRenderer::QInstance() /*Member at 112*/ = 0;

	(*BSShaderManager_spCamera) = scopePOV;

	(BSGraphics_gState)->SetCameraData(scopePOV, 0, 0.0, 1.0);
	scopeCulling->SetAccumulator(pScopeManagerAccumulator);
	scopeCulling->CullingType = BSCullingProcess::BSCPCullingType::kIgnoreMultiBounds;
	scopeCulling->m_bCameraRelatedUpdates = 0;
	scopeCulling->m_pkCamera = scopePOV;

	//scopeCam->Update();

	//DisableLightUpdate = pShadow->DisableLightUpdate;
	//pShadow->DisableLightUpdate = 1;
	//bLightUpdate = DisableLightUpdate;
	//fadeEnabled = BSFadeNode::bFadeEnabled;
	//BSFadeNode::bFadeEnabled = 0;
	//BSFadeNode::bDrawFadingEnabled = 0;
	//BSFadeNode::iFadeEnableCounter = 0;
	//bFadeEnabled = fadeEnabled;

	(BSGraphics_gRenderer)->SetClearColor(1.0, 1.0, 1.0, 1.0);

	//waterEnabled = localRenderer->field_2A4 == 37;
	//float r = BSWaterShaderProperty::WaterColorMult.r;
	//float g = BSWaterShaderProperty::WaterColorMult.g;
	//float b = BSWaterShaderProperty::WaterColorMult.b;
	//float a = BSWaterShaderProperty::WaterColorMult.a;
	//waterPropertyEnabled = BSWaterShaderProperty::bEnabled;
	//BSWaterShaderProperty::WaterColorMult.r = 10.0;
	//BSWaterShaderProperty::WaterColorMult.g = 10.0;
	//BSWaterShaderProperty::WaterColorMult.b = 60.0;
	//BSWaterShaderProperty::bEnabled = waterEnabled;
	//bWaterEnabled = waterPropertyEnabled;
	//waterSimpleEnabled = BSShaderAccumulator::bSimpleWaterMode;
	//BSShaderAccumulator::bSimpleWaterMode = 1;
	//bWaterSimple = waterSimpleEnabled;

	pScopeManagerAccumulator->renderMode = BSShaderManager::etRenderMode::unk18;
	pScopeManagerAccumulator->QEyePosition = scopePOV->m_worldTransform.pos;
	(BSGraphics_gRenderer)->ResetZPrePass();

	//In LocalMapRenderer::Render this is where the going through arrays of TESObjectCells starts
	//if (!bCullLocalMap._value) {
	//	unk = TES->unk[88];
	//	if (unk) {
	//		goto LABEL_10;
	//	}
	//	//while loop stuff of GridCellArrays and then AccumulateSceneFunctor on those GridCell Arrays
	//	if (cells) {	
	//		while(thing == 1) {
	//			stuff
	//			more stuff
	//			if (thing != 1) {
	//				break;
	//			}
	//			goto LABEL_50;
	//		}
	//	} else {
	//	LABEL_50:
	//		SkyCell = TES::GetSkyCell(pTes);
	//		if (SkyCell && SkyCell->cellState._impl == 8) {
	//			AccumulateSceneFunctor::operator()(&pCull, SkyCell);
	//		}
	//	}
	//	LABEL_53:
	//	pShadow = pShadow2;
	//	localRenderer = this;
	//	goto LABEL_54;
	//}
	//v17 = *(TESObjectCELL**)&tes->unk[88];
	//if (!v17) {
	//	BSTObjectArenaScrapAllocBase::BSTObjectArenaScrapAllocBase((BSTObjectArenaScrapAllocBase*)&objArenaCell);
	//	objArenaCell._tail = (BSTObjectArena::Page::TESObjectCELL*)&objArenaCell._next;
	//	objArenaCell._next = 0i64;
	//	memset(&objArenaCell._free, 0, 32);
	//	a2_120 = 0;
	//	TESObjectCELL::GetOverlappedCells(&localRenderer->LocalMapCamera.minExtent, &localRenderer->LocalMapCamera.maxExtent, &objArenaCell);
	//	arraySizeMaybe = a2_120;
	//	if (localRenderer->type == 20 && a2_120 > uiCompanionLocalMapMaxCells._value) {
	//		BSTArrayHeapAllocator::BSTArrayHeapAllocator(&array);
	//		BSTArrayBase::BSTArrayBase(&array.BSTArrayBase);
	//		a2_128[0].__vftable = (BSTArrayBase::IAllocatorFunctor_vtbl*)&BSTArrayAllocatorFunctor<BSTArrayHeapAllocator>::`vftable';
	//			a2_128[1].__vftable = (BSTArrayBase::IAllocatorFunctor_vtbl*)&array;
	//		BSTArrayBase::InitialReserve(&array.BSTArrayBase, a2_128, arraySizeMaybe, 8u);
	//		a2_48 = &array;
	//		BSTObjectArena<TESObjectCELL*, BSTObjectArenaScrapAlloc, 32>::ForEach<_lambda_74ce9d00abd68d954279d61887a28760_>(&objArenaCell, &a2_48);
	//		sorter = NearestCellSort;
	//			if (array.QSize > 1) {
	//				v19 = array.QSize - 1;
	//				v20 = (TESObjectCELL**)array.QBuffer[0];
	//				v21 = 0i64;
	//				for (i = array.QSize - 1; ; v27[i] = v28) {
	//					do {
	//						if (sorter(*((TESObjectCELL**)array.QBuffer[0] + i), *v20) <= 0) {
	//							break;
	//						}
	//						--i;
	//					} while ((unsigned int)v21 < i);
	//					if ((unsigned int)v21 >= i) {
	//						break;
	//					}
	//					v23 = 8 * v21;
	//					while (sorter(*(TESObjectCELL**)((char*)array.QBuffer[0] + v23), *v20) <= 0) {
	//						v21 = (unsigned int)(v21 + 1);
	//						v23 += 8i64;
	//						if ((unsigned int)v21 >= i) {
	//							goto LABEL_22;
	//						}
	//					}
	//					v27 = array.QBuffer[0];
	//					v28 = *((_QWORD*)array.QBuffer[0] + v21);
	//					*((_QWORD*)array.QBuffer[0] + v21) = *((_QWORD*)array.QBuffer[0] + i);
	//				}
	//			LABEL_22:
	//				v24 = array.QBuffer[0];
	//				v25 = *(_QWORD*)array.QBuffer[0];
	//				*(_QWORD*)array.QBuffer[0] = *((_QWORD*)array.QBuffer[0] + i);
	//				v24[i] = v25;
	//				if (i) {
	//					ArrayQuickSortRecursive<TESObjectCELL*, int (*)(TESObjectCELL*, TESObjectCELL*), BSTArrayHeapAllocator>(&array, &sorter, 0i64, i - 1);
	//				}
	//				if (i < array.QSize - 1) {
	//					ArrayQuickSortRecursive<TESObjectCELL*, int (*)(TESObjectCELL*, TESObjectCELL*), BSTArrayHeapAllocator>(&array, &sorter, i + 1, v19);
	//				}
	//			}
	//		for (j = 0i64; (unsigned int)j < uiCompanionLocalMapMaxCells._value; j = (unsigned int)(j + 1)) {
	//			AccumulateSceneFunctor::operator()(&pCull, *((TESObjectCELL **)array.QBuffer[0] + j));
	//		}
	//		if (array.QBuffer[0]) {
	//			BSTArrayHeapAllocator::Deallocate(&array);
	//			array.QSize = 0;
	//		}
	//		BSTArrayBase::~BSTArrayBase(&array.BSTArrayBase);
	//		BSTArrayHeapAllocator::~BSTArrayHeapAllocator(&array);
	//		BSTObjectArena<TESObjectCELL*, BSTObjectArenaScrapAlloc, 32>::~BSTObjectArena<TESObjectCELL*, BSTObjectArenaScrapAlloc, 32>(&objArenaCell);
	//	} else {
	//		next = objArenaCell._next;
	//		ppCell = *(TESObjectCELL***)&objArenaCell._size;
	//		v31 = 1;
	//		v32 = objArenaCell._next + 32;
	//		*(_OWORD*)&pCull2 = *(_OWORD*)&pCull;
	//		if (a2_120) {
	//			do {
	//				--arraySizeMaybe;
	//				if (v31 != 1) {
	//					break;
	//				}
	//				v31 = AccumulateSceneFunctor::operator()(&pCull2, *ppCell++);
	//					if (ppCell >= (TESObjectCELL**)v32) {
	//						next = (BSTObjectArena::Page::TESObjectCELL**)next[32];
	//						if (next) {
	//							ppCell = (TESObjectCELL**)next;
	//							v32 = next + 32;
	//						}
	//					}
	//			} while (arraySizeMaybe);
	//		}
	//		BSTObjectArena<TESObjectCELL*, BSTObjectArenaScrapAlloc, 32>::~BSTObjectArena<TESObjectCELL*, BSTObjectArenaScrapAlloc, 32>(&objArenaCell);
	//	}
	//	goto LABEL_53;
	//}
	//LABEL_10:
	//AccumulateSceneFunctor::operator()(&pCull, v17);
	//LABEL_54:
	//

	BSPortalGraphEntry* camPortalEntry = (*appMain)->GetCameraPortalGraphEntry();
	NiAVObject* pChildAt9;
	if (camPortalEntry) {
		BSPortalGraph* camPortalGraph = camPortalEntry->QPortalGraph;
		if (camPortalGraph) {
			BSShaderUtil::AccumulateSceneArray(scopePOV, &camPortalGraph->QAlwaysRenderArray, (*scopeCulling), 0);
		}
	}
	if (pShadow->m_children.m_emptyRunStart > 9) {
		pChildAt9 = pShadow->m_children.m_data[9];
	} else {
		pChildAt9 = nullptr;
	}
	BSShaderUtil::AccumulateScene(scopePOV, pChildAt9, (*scopeCulling), 0);
	NiAVObject* pChildAt8;
	if (pShadow->m_children.m_emptyRunStart > 8) {
		pChildAt8 = pShadow->m_children.m_data[8];
	} else {
		pChildAt8 = nullptr;
	}
	BSShaderUtil::AccumulateScene(scopePOV, pChildAt8, (*scopeCulling), 0);
	(*ShaderManager_gState).uiCurrentSceneGraph = 0;
	(*ShaderManager_gState).pShadowSceneNode[0]->ProcessQueuedLights(scopeCulling);
	(BSGraphics_gRenderer)->ResetState();
	int type = 19;
	int depthTarget = 1;
	int renderTarget = 27;
	int newRenderTarget = 22;
	if (type == 20) {
		depthTarget = 11;
	}
	newRenderTarget = (type == 20) + 22;
	if (type == 20) {
		renderTarget = 21;
	}
	if (type == 20) {
		(BSGraphics_gRenderTargetManager)->AcquireDepthStencil(depthTarget);
		(BSGraphics_gRenderTargetManager)->AcquireRenderTarget(renderTarget);
	}
	(BSGraphics_gRenderTargetManager)->AcquireRenderTarget(newRenderTarget);

	//RenderScene
	(BSGraphics_gRenderTargetManager)->SetCurrentDepthStencilTarget(depthTarget, BSGraphics::SetRenderTargetMode::SRTM_FORCE_COPY_RESTORE, 0, 0);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(0, newRenderTarget, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(1, renderTarget, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(2, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(3, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	if ((*ShaderManager_gState).unk56) {
		(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(4, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	}
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(5, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics_gRenderTargetManager)->SetCurrentViewportForceToRenderTargetDimensions();
	(BSGraphics_gRenderer)->SetClearColor(0.0, 0.0, 0.0, 0.0);
	(BSGraphics_gRenderer)->ClearColor();
	(BSGraphics_gRenderer)->Flush();
	//Threaded stuff happens here in RenderLocalMapScene
	//stuff
	//more stuff
	(BSGraphics_gState)->SetCameraData(scopePOV, 0, 0.0, 1.0);
	(BSGraphics_gRenderer)->DoZPrePass(0, 0, 0.0, 1.0, 0.0, 1.0);
	pScopeManagerAccumulator->RenderOpaqueDecals();
	pScopeManagerAccumulator->RenderBatches(4, 0, -1);
	pScopeManagerAccumulator->RenderBlendedDecals();
	//BSGraphics::pDefaultContext stuff happens here in RenderLocalMapScene
	//stuff
	//more stuff
	(BSGraphics_gRenderer)->Flush();
	(BSGraphics_gRenderer)->SetClearColor(1.0, 1.0, 1.0, 1.0);
	//more context stuff
	//more things
	//pScopeManagerAccumulator->ClearEffectPasses();
	//pScopeManagerAccumulator->ClearActivePasses(0);
	//RenderSceneEnd

	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(0, 2, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(1, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics_gRenderTargetManager)->SetCurrentDepthStencilTarget(1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, 0);
	//FogOfWar Setup stuff would happen after this in the LocalMapRenderer::Render
	//stuff and things
	//
	(BSGraphics_gRenderTargetManager)->SetCurrentDepthStencilTarget(0, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, 0);
	pScopeManagerShaderParam->SetPixelConstant(
		0,
		1.0 / (float)(int)(*BSGraphics_gRenderTargetManager).pRenderTargetDataA[type].uiWidth,
		1.0 / (float)(int)(*BSGraphics_gRenderTargetManager).pRenderTargetDataA[type].uiHeight,
		0.0,
		0.0);
	(BSGraphics_gRenderTargetManager)->SetTextureDepth(1, depthTarget);
	(BSGraphics_gRenderTargetManager)->SetTextureRenderTarget(2, renderTarget, 0);
	int effect = ((type == 20) + 152);
	(*ImageSpaceManager_pInstance)->effectArray.m_data[effect].UseDynamicResolution = 0;
	(*ImageSpaceManager_pInstance)->RenderEffectHelper_2((ImageSpaceManager::ImageSpaceEffectEnum)effect, newRenderTarget, type, pScopeManagerShaderParam);
	if (type == 20) {
		(BSGraphics_gRenderTargetManager)->ReleaseDepthStencil(depthTarget);
		(BSGraphics_gRenderTargetManager)->ReleaseRenderTarget(renderTarget);
	}
	(BSGraphics_gRenderTargetManager)->ReleaseRenderTarget(newRenderTarget);
	//Threaded stuff would happen here in LocalMapRenderer::Render
	//BSGraphics::Context = threaded stuff
	//if (!context) {
	//		context = BSGraphics::pDefaultContext
	//}
	//shadowState = &context->field_1B70;
	//Texture dirty stuff
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(0, 1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	NiTexture* renderedTexture = nullptr;
	BSGraphics::Texture* graphicsTex = nullptr;
	if (save) {
		const BSFixedString strScope("ScopeTexture");
		//renderedTexture = renderedTexture->CreateEmpty((strScope), 0, 0);
		renderedTexture = CreateTexture(strScope, 0);
		graphicsTex = (BSGraphics_gRenderTargetManager)->SaveRenderTargetToTexture(19, 0, 0, BSGraphics::Usage::USAGE_DEFAULT);
		renderedTexture->rendererData = reinterpret_cast<BSRenderData*>(graphicsTex);
	}
	//BSScaleformRenderer::SetCurrentRenderTarget
	(*BSShaderManager_spCamera) = shaderCam;
	(BSGraphics_gState)->SetCameraData(shaderCam, 0, 0.0, 1.0);
	//pShadow2->DisableLightUpdate = bLightUpdate;
	//BSFadeNode::iFadeEnableCounter = 0;
	//BSWaterShaderProperty::WaterColorMult.r = r;
	//BSWaterShaderProperty::WaterColorMult.g = g;
	//BSWaterShaderProperty::WaterColorMult.b = b;
	//BSWaterShaderProperty::WaterColorMult.a = a;
	//BSShaderAccumulator::bSimpleWaterMode = bWaterSimple;
	//BSFadeNode::bFadeEnabled = bFadeEnabled;
	//BSFadeNode::bDrawFadingEnabled = bFadeEnabled;
	//BSWaterShaderProperty::bEnabled = bWaterEnabled;
	pScopeManagerAccumulator->ClearActivePasses(0);
	pScopeManagerAccumulator->ClearGroupPasses(5, 0);
	//scopeCulling->~BSCullingProcess();
	//pOldGrassNode = pGrassNode;
	//pGrassNode->SetAppCulled(pGrassNode, grassNodeCullFlag);
	//if (!InterlockedDecrement(&pOldGrassNode->m_uiRefCount)) {
	//	pOldGrassNode->DeleteThis(pOldGrassNode);
	//}
	obj->SetAppCulled(objCullFlag);
	if (!InterlockedDecrement(&obj->m_uiRefCount)) {
		obj->DeleteThis();
	}
	return renderedTexture;
}

//ExtraCameraManager

bool ExtraCameraManager::AttachExtraCamera(const char camName[0x40], bool doAttach, char nodeName) {
	
	NiCamera* cam;
	NiCamera** pCam;

	if (doAttach) {
		BSFixedString sCamName(camName);
		BSFixedString sNodeName(&nodeName);
		NiNode* targetNode = (NiNode*)GetByNameHelper(sNodeName);
		if (targetNode) {
			if (std::get<bool>(s_extraCamerasMap.insert(std::pair<const char*, NiCamera*>(camName, *pCam)))) {
				*pCam = cam = (NiCamera*)CreateNS_NiCamera_Create();
				InterlockedIncrement(&cam->m_uiRefCount);
				cam->m_name = sCamName;
				cam->viewFrustum.m_fNear = 5.0;
				cam->viewFrustum.m_fFar = 353840.0;
				cam->minNearPlaneDist = 1.0;
				cam->maxFarNearRatio = 70768.0;
				cam->lodAdjust = 0.001;

				scopePOV = cam;
				scopePOV_BACKUP = cam;
			}
			else { cam = *pCam; }
			if (cam->m_parent != targetNode) {
				targetNode->AttachChild(cam, 1);
				NiAVObject::NiUpdateData camUpdateParams;
				new(&camUpdateParams) NiAVObject::NiUpdateData();
				camUpdateParams.unk00 = 0; //time = 0.0
				memset(camUpdateParams.pCamera, 0, 20);
				cam->Update(camUpdateParams);
			}
		}
	} else {
		auto findCam = s_extraCamerasMap.find(camName);
		if (findCam != s_extraCamerasMap.end()) {
			cam = findCam->second;
			s_extraCamerasMap.erase(camName);
			if (cam->m_parent) {
				cam->m_parent->RemoveChild(cam);
			}
			cam->DeleteThis();
		}
	}
	return true;
}

void ExtraCameraManager::GenerateExtraCameraTexture(TESObjectCELL* cell, NiCamera* camera, NiTexture* outTexture) {

}

bool ExtraCameraManager::ProjectExtraCamera(const char camName[0x40], const char nodeName[0x40], float fov, UInt32 pixelSize) {
	NiCamera* cam = (*s_extraCamerasMap.find(camName)).second;
	if (cam && cam->m_parent) {
		NiTexture** pTex = NULL;
		if (nodeName) {
			BSFixedString sNodeName(nodeName);
			NiAVObject* targetGeom = GetByNameHelper(sNodeName);
			if (targetGeom && targetGeom->GetAsBSGeometry()) {
				NiPointer<BSShaderProperty> shaderProperty;

				BSEffectShaderProperty* effectShaderProperty;
				shaderProperty = ni_cast(targetGeom->GetAsBSGeometry()->shaderProperty, BSShaderProperty);
				effectShaderProperty = ni_cast(shaderProperty, BSEffectShaderProperty);
				if (shaderProperty.get()) {
					NiTexture* baseTex = effectShaderProperty->QBaseTexture();
					pTex = &baseTex;
				}
			}
		}
		if (pTex) {
			float w = tan(fov * FltPId180) * (1 / 1.5);
			cam->viewFrustum.m_fLeft = -w;
			cam->viewFrustum.m_fRight = w;
			cam->viewFrustum.m_fTop = w;
			cam->viewFrustum.m_fBottom = -w;

		}
	}
	return true;
}
