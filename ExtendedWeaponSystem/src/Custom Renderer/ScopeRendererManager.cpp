#include "Global.h"

BSCullingProcess* pScopeManagerCullingProc;
BSShaderAccumulator* pScopeManagerAccumulator;
ImageSpaceShaderParam* pScopeManagerShaderParam;


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
	}
	else {
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

	cam = Create_NiCamera();
	if (cam) {
		//CreateNS_NiCamera_Create already constructs using NiCamera::NiCamera() we do not need to do it again
		//new(cam) NiCamera();
		newCam = cam;
		logIfNeeded("ScopeRendererManager - Created NiCamera");
	}
	else {
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

	node = Create_NiNode();
	if (node) {
		new(node) NiNode(1);
		if ((*g_playerCamera)) {
			node->m_localTransform.pos.x = (*g_playerCamera)->translationInput.x;
			node->m_localTransform.pos.y = (*g_playerCamera)->translationInput.y + 5.0;
			node->m_localTransform.pos.z = (*g_playerCamera)->translationInput.z;
		}
		newNode = node;
		logIfNeeded("ScopeRendererManager - Created NiNode");

	}
	else {
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
		BSShaderUtil::SetCameraFOV((*Main__spWorldSceneGraph), (float)(90.0 / 4.0), 0, scopePOV, 1); //TEMP. Right now I just have it as 4x zoom
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
	}
	else {
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
	}
	else {
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
	}
	else {
		pChildAt9 = nullptr;
	}
	BSShaderUtil::AccumulateScene(scopePOV, pChildAt9, (*scopeCulling), 0);
	NiAVObject* pChildAt8;
	if (pShadow->m_children.m_emptyRunStart > 8) {
		pChildAt8 = pShadow->m_children.m_data[8];
	}
	else {
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
