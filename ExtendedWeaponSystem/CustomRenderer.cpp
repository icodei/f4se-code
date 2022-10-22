#include "Global.h"

void nsScope_CreateRenderer() {
	//create a spinlock???
	//Lock the rendererlock

	//if renderer is null
	if (0) {
		//renderer is equal to InitRenderer()
		nsScope_InitRenderer(0);
	}

	//if rendererlock._lockcount == 1
	if (1) {
		//rendererlock._owningthread = rendererlock._lockcount -1
		//mm_mfence()
		//interlockedcompareexchange(&rendererlock._lockcount, rendererlock._lockcount - 1, rendererlock._lockcount)
	}
	else {
		//interlockeddecrement(&rendererlock._lockcount)
	}
}

ScopeRenderer* nsScope_InitRenderer(bool a1) {
	//allocate our renderer from MemoryManager

	//if allocated succesful
	if (1) {

	}
}

void nsScope_Render() {

}

ScopeCamera::ScopeCamera() {

	NiCamera* cam;
	NiCamera* newCamera;
	NiCamera* oldCam;

	NiNode* node;
	NiNode* newNode;

	NiNode* camRootNode;

	new(this) TESCamera();

	cam = (NiCamera*)CreateNS_NiCamera_Create();
	if (cam) {
		//CreateNS_NiCamera_Create already constructs using NiCamera::NiCamera() we do not need to do it again
		newCamera = cam;
		//new(cam) NiCamera();
	}
	else {
		newCamera = 0i64;
	}
	oldCam = this->camera.get();
	if (oldCam != newCamera) {
		if (newCamera) {
			InterlockedIncrement(&newCamera->m_uiRefCount);
		}
		this->camera.m_pObject = newCamera;
		if (oldCam && !InterlockedDecrement(&oldCam->m_uiRefCount)) {
			oldCam->DeleteThis();
		}
	}

	node = (NiNode*)CreateNS_NiNode_Create();
	if (node) {
		new(node) NiNode(1);
		newNode = node;
		
	}
	else {
		newNode = 0i64;
	}
	camRootNode = this->cameraNode;
	if (camRootNode != newNode) {
		if (newNode) {
			InterlockedIncrement(&newNode->m_uiRefCount);
		}
		this->cameraNode = newNode;
		if (camRootNode && !InterlockedDecrement(&camRootNode->m_uiRefCount)) {
			camRootNode->DeleteThis();
		}
	}
	this->cameraNode->AttachChild(this->camera.m_pObject, true);

	ScopeCamera::DefaultState* camDefaultState;
	ScopeCamera::DefaultState* oldCamDefaultState;
	camDefaultState = (ScopeCamera::DefaultState*)Heap_Allocate(sizeof(ScopeCamera::DefaultState));
	if (camDefaultState) {
		camDefaultState->m_refCount = 0;
		camDefaultState->camera = this;
		camDefaultState->stateID = 0;
		camDefaultState->initialPosition = NiPoint3_ZERO;
		camDefaultState->translation = NiPoint3_ZERO;
		camDefaultState->zoom = 1.0;
	}
	else {
		camDefaultState = 0i64;
	}
	oldCamDefaultState = this->defaultState;
	if (camDefaultState != oldCamDefaultState) {
		if (camDefaultState) {
			InterlockedIncrement(&camDefaultState->m_refCount);
		}
		this->defaultState = camDefaultState;
		if (oldCamDefaultState && !InterlockedDecrement(&oldCamDefaultState->m_refCount)) {
			//oldCamDefaultState->~TESCameraState();
		}
	}
	this->SetCameraState(this->defaultState);
}

ScopeCamera::DefaultState::DefaultState(TESCamera* cam, UInt32 ID) {
	this->m_refCount = 0;
	this->camera = cam;
	this->stateID = ID;

	this->initialPosition = NiPoint3_ZERO;
	this->translation = NiPoint3_ZERO;
	this->zoom = 1.0;
}

ScopeRenderer::ScopeRenderer(bool a1) {

	BSShaderAccumulator* shaderAccum;
	BSShaderAccumulator* newShaderAccum;
	BSShaderAccumulator* oldShaderAccum;
	BSShaderAccumulator* pShaderAccum;

	new(&this->scopeCullingProc) BSCullingProcess(0i64);
	new(&this->scopeCam) ScopeCamera();
	new(&this->params) ImageSpaceShaderParam();
	this->spScopeAccumulator.m_pObject = 0i64;
	//this->field_2A8 = 0i64; //LocalMapRenderer

	shaderAccum = (BSShaderAccumulator*)Heap_Allocate(0x590ui64);
	if (shaderAccum) {
		new(shaderAccum) BSShaderAccumulator();
		newShaderAccum = shaderAccum;
	}
	else {
		newShaderAccum = 0i64;
	}
	oldShaderAccum = this->spScopeAccumulator.m_pObject;
	if (oldShaderAccum != newShaderAccum) {
		if (newShaderAccum) {
			InterlockedIncrement(&newShaderAccum->m_uiRefCount);
		}
		this->spScopeAccumulator.m_pObject = newShaderAccum;
		if (oldShaderAccum && !InterlockedDecrement(&oldShaderAccum->m_uiRefCount)) {
			oldShaderAccum->DeleteThis();
		}
	}
	this->spScopeAccumulator.m_pObject->QZPrePass = 1;
	this->spScopeAccumulator.m_pObject->ShadowSceneNode = (*ShaderManager_gState).pShadowSceneNode[0];
	pShaderAccum = this->spScopeAccumulator.m_pObject;
	pShaderAccum->QSilhouetteColor.r = 1.0;
	pShaderAccum->QSilhouetteColor.g = 1.0;
	pShaderAccum->QSilhouetteColor.b = 1.0;
	pShaderAccum->QSilhouetteColor.a = 1.0;
	(&this->scopeCullingProc)->SetAccumulator(this->spScopeAccumulator);
	this->scopeCullingProc.CullingType = BSCullingProcess::BSCPCullingType::kIgnoreMultiBounds;
	this->scopeCullingProc.m_bCameraRelatedUpdates = 0;
	(&this->params)->ResizeConstantGroup(0, 1);
	//this->field_2A4 = 18; //LocalMapRenderer
}

NiTexture* ScopeRenderer::Render(bool a1) {
	
	ScopeRenderer* scopeRenderer = (this);
	ScopeCamera* scopeCam = (&scopeRenderer->scopeCam);
	
	NiCamera* shaderCam = (*BSShaderManager_spCamera);
	
	BSCullingProcess scopeCulling;
	new(&scopeCulling) BSCullingProcess(0i64);
	
	//BSCullingProcess* pScopeCulling = (&scopeRenderer->scopeCullingProc);

	
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
	//	InterlockedIncrement(&grassNode->refCount);
	//}
	//grassNodeCullFlag = grassNode->flags & 1;
	//bGrassNodeCullFlag = grassNodeCullFlag;
	//grassNode->SetAppCulled(grassNode, 0);
	//BSDistantObjectInstanceRenderer::QInstance() /*Member at 112*/ = 0;
	
	(*BSShaderManager_spCamera) = scopeCam->camera;

	(BSGraphics_gState)->SetCameraData(scopeCam->camera, 0, 0.0, 1.0);
	(&scopeCulling)->SetAccumulator(scopeRenderer->spScopeAccumulator.m_pObject);
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

	scopeRenderer->spScopeAccumulator.m_pObject->renderMode = BSShaderManager::etRenderMode::unk18;
	scopeRenderer->spScopeAccumulator.m_pObject->QEyePosition = scopeCam->camera->m_worldTransform.pos;
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
	if (scopeRenderer->type == 20) {
		depthTarget = 11;
	}
	newRenderTarget = (scopeRenderer->type == 20) + 22;
	if (scopeRenderer->type == 20) {
		renderTarget = 21;
	}
	if (scopeRenderer->type == 20) {
		(BSGraphics_gRenderTargetManager)->AcquireDepthStencil(depthTarget);
		(BSGraphics_gRenderTargetManager)->AcquireRenderTarget(renderTarget);
	}
	(BSGraphics_gRenderTargetManager)->AcquireRenderTarget(newRenderTarget);
	RenderScopeScene(scopeCam->camera, scopeRenderer->spScopeAccumulator.m_pObject, newRenderTarget, renderTarget, depthTarget);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(0, 2, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	(BSGraphics_gRenderTargetManager)->SetCurrentRenderTarget(1, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics_gRenderTargetManager)->SetCurrentDepthStencilTarget(1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, 0);
	//FogOfWar Setup stuff would happen after this in the LocalMapRenderer
	//stuff and things
	//
	(BSGraphics_gRenderTargetManager)->SetCurrentDepthStencilTarget(0, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, 0);
	(&scopeRenderer->params)->SetPixelConstant(
		0,
		1.0 / (float)(int)(*BSGraphics_gRenderTargetManager).pRenderTargetDataA[scopeRenderer->type].uiWidth,
		1.0 / (float)(int)(*BSGraphics_gRenderTargetManager).pRenderTargetDataA[scopeRenderer->type].uiHeight,
		0.0,
		0.0);
	(BSGraphics_gRenderTargetManager)->SetTextureDepth(1, depthTarget);
	(BSGraphics_gRenderTargetManager)->SetTextureRenderTarget(2, renderTarget, 0);
	int effect = ((scopeRenderer->type == 20) + 152);
	(*ImageSpaceManager_pInstance)->effectArray.m_data[effect].UseDynamicResolution = 0;
	(*ImageSpaceManager_pInstance)->RenderEffectHelper_2((ImageSpaceManager::ImageSpaceEffectEnum)effect, newRenderTarget, scopeRenderer->type, &scopeRenderer->params);
}

void RenderScopeScene(NiCamera* cam, BSShaderAccumulator* shadeaccum, SInt32 a1, SInt32 a2, SInt32 a3) {

}