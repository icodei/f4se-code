#include "Global.h"

ScopeRenderer* scopeRenderer;
BSReadWriteLock scopeRendererLock;

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

	shaderAccum = (BSShaderAccumulator*)RE::malloc(0x590);
	if (shaderAccum) {
		new(shaderAccum) BSShaderAccumulator();
		newShaderAccum = shaderAccum;
		logIfNeeded("ScopeRenderer - Created BSShaderAccumulator");
	}
	else {
		newShaderAccum = nullptr;
		logIfNeeded("ScopeRenderer - BSShaderAccumulator Creation FAILED");
	}
	oldShaderAccum = spScopeAccumulator.get();
	if ((oldShaderAccum != newShaderAccum) || (spScopeAccumulator == nullptr)) {
		if (newShaderAccum) {
			InterlockedIncrement(&newShaderAccum->refCount);
		}
		spScopeAccumulator.reset<BSShaderAccumulator>(newShaderAccum);
		if (oldShaderAccum && !InterlockedDecrement(&oldShaderAccum->refCount)) {
			oldShaderAccum->DeleteThis();
		}
	}
	spScopeAccumulator->QZPrePass = 1;
	spScopeAccumulator->ShadowSceneNode = (BSShaderManager__State).get().pShadowSceneNode[0];
	pShaderAccum = spScopeAccumulator.get();
	pShaderAccum->QSilhouetteColor.r = 1.0;
	pShaderAccum->QSilhouetteColor.g = 1.0;
	pShaderAccum->QSilhouetteColor.b = 1.0;
	pShaderAccum->QSilhouetteColor.a = 1.0;
	(&scopeCullingProc)->SetAccumulator(spScopeAccumulator.get());
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
	//if (overlayObjMaybe && !_InterlockedDecrement(&overlayObjMaybe->refCount)) {
	//	overlayObjMaybe->DeleteThis();
	//}
	(&params)->~ImageSpaceShaderParam();
	shaderAccum = spScopeAccumulator.get();
	if (shaderAccum && !InterlockedDecrement(&shaderAccum->refCount)) {
		shaderAccum->DeleteThis();
	}
	cam = scopeCam.camera.get();
	if (cam && !InterlockedDecrement(&cam->refCount)) {
		cam->DeleteThis();
	}
	state = scopeCam.currentState.get();
	if (state && !InterlockedDecrement(&state->refCount)) {
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

	NiCamera* shaderCam = (BSShaderManager__spCamera).get();

	BSCullingProcess scopeCulling{ BSCullingProcess(0) };
	new(&scopeCulling) BSCullingProcess(0); //Is this still needed with the above statement?

	ShadowSceneNode* pShadow = (BSShaderManager__State).get().pShadowSceneNode[0];
	ShadowSceneNode* pShadow2 = (BSShaderManager__State).get().pShadowSceneNode[0];
	NiAVObject* obj = (&BSShaderManager__State.get())->pShadowSceneNode[0]->children[3].get();
	NiAVObject* pObj = obj;
	if (obj) {
		InterlockedIncrement(&obj->refCount);
	}
	bool objCullFlag = obj->flags.flags & 1;
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

	(BSShaderManager__spCamera) = (uintptr_t)scopeCam->camera.get();

	(&BSGraphics__gState.get())->SetCameraData(scopeCam->camera.get(), 0, 0.0, 1.0);
	(&scopeCulling)->SetAccumulator(pScopeRenderer->spScopeAccumulator.get());
	(&scopeCulling)->CullingType = BSCullingProcess::BSCPCullingType::kIgnoreMultiBounds;
	(&scopeCulling)->m_bCameraRelatedUpdates = 0;
	(&scopeCulling)->m_pkCamera = scopeCam->camera.get();

	scopeCam->Update();

	//DisableLightUpdate = pShadow->DisableLightUpdate;
	//pShadow->DisableLightUpdate = 1;
	//bLightUpdate = DisableLightUpdate;
	//fadeEnabled = BSFadeNode::bFadeEnabled;
	//BSFadeNode::bFadeEnabled = 0;
	//BSFadeNode::bDrawFadingEnabled = 0;
	//BSFadeNode::iFadeEnableCounter = 0;
	//bFadeEnabled = fadeEnabled;

	(&BSGraphics__gRenderer.get())->SetClearColor(1.0, 1.0, 1.0, 1.0);

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

	pScopeRenderer->spScopeAccumulator.get()->renderMode = BSShaderManager::etRenderMode::unk18;
	pScopeRenderer->spScopeAccumulator.get()->QEyePosition = scopeCam->camera->world.translate;
	(&BSGraphics__gRenderer.get())->ResetZPrePass();

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

	BSPortalGraphEntry* camPortalEntry = (Main::GetSingleton())->GetCameraPortalGraphEntry();
	NiAVObject* pChildAt9;
	if (camPortalEntry) {
		BSPortalGraph* camPortalGraph = camPortalEntry->QPortalGraph;
		if (camPortalGraph) {
			BSShaderUtil::AccumulateSceneArray(scopeCam->camera.get(), &camPortalGraph->QAlwaysRenderArray, scopeCulling, 0);
		}
	}
	if (pShadow->children.size() > 9) {
		pChildAt9 = pShadow->children[9].get();
	}
	else {
		pChildAt9 = nullptr;
	}
	BSShaderUtil::AccumulateScene(scopeCam->camera.get(), pChildAt9, scopeCulling, 0);
	NiAVObject* pChildAt8;
	if (pShadow->children.size() > 8) {
		pChildAt8 = pShadow->children[8].get();
	}
	else {
		pChildAt8 = nullptr;
	}
	BSShaderUtil::AccumulateScene(scopeCam->camera.get(), pChildAt8, scopeCulling, 0);
	(&BSShaderManager__State.get())->uiCurrentSceneGraph = 0;
	(&BSShaderManager__State.get())->pShadowSceneNode[0]->ProcessQueuedLights(&scopeCulling);
	(&BSGraphics__gRenderer.get())->ResetState();
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
		(BSGraphics__gRenderTargetManager)->AcquireDepthStencil(depthTarget);
		(BSGraphics__gRenderTargetManager)->AcquireRenderTarget(renderTarget);
	}
	(BSGraphics__gRenderTargetManager)->AcquireRenderTarget(newRenderTarget);
	RenderScopeScene(scopeCam->camera.get(), pScopeRenderer->spScopeAccumulator.get(), newRenderTarget, renderTarget, depthTarget);
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(0, 2, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(1, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics__gRenderTargetManager)->SetCurrentDepthStencilTarget(1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, 0);
	//FogOfWar Setup stuff would happen after this in the LocalMapRenderer::Render
	//stuff and things
	//
	(BSGraphics__gRenderTargetManager)->SetCurrentDepthStencilTarget(0, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, 0);
	(&pScopeRenderer->params)->SetPixelConstant(
		0,
		1.0 / (float)(int)(*BSGraphics__gRenderTargetManager).pRenderTargetDataA[pScopeRenderer->type].uiWidth,
		1.0 / (float)(int)(*BSGraphics__gRenderTargetManager).pRenderTargetDataA[pScopeRenderer->type].uiHeight,
		0.0,
		0.0);
	(BSGraphics__gRenderTargetManager)->SetTextureDepth(1, depthTarget);
	(BSGraphics__gRenderTargetManager)->SetTextureRenderTarget(2, renderTarget, 0);
	int effect = ((pScopeRenderer->type == 20) + 152);
	(ImageSpaceManager__pInstance)->effectArray[effect].UseDynamicResolution = 0;
	(ImageSpaceManager__pInstance)->RenderEffectHelper_2((ImageSpaceManager::ImageSpaceEffectEnum)effect, newRenderTarget, pScopeRenderer->type, &pScopeRenderer->params);
	if (pScopeRenderer->type == 20) {
		(BSGraphics__gRenderTargetManager)->ReleaseDepthStencil(depthTarget);
		(BSGraphics__gRenderTargetManager)->ReleaseRenderTarget(renderTarget);
	}
	(BSGraphics__gRenderTargetManager)->ReleaseRenderTarget(newRenderTarget);
	//Threaded stuff would happen here in LocalMapRenderer::Render
	//BSGraphics::Context = threaded stuff
	//if (!context) {
	//		context = BSGraphics::pDefaultContext
	//}
	//shadowState = &context->field_1B70;
	//Texture dirty stuff
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(0, 1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	NiTexture* renderedTexture = nullptr;
	BSGraphics::Texture* graphicsTex = nullptr;
	if (a1) {
		BSFixedString strScope("ScopeTexture");
		renderedTexture = renderedTexture->CreateEmpty(strScope, 0, 0);
		graphicsTex = (BSGraphics__gRenderTargetManager)->SaveRenderTargetToTexture(19, 0, 0, BSGraphics::Usage::USAGE_DEFAULT);
		renderedTexture->rendererTexture = graphicsTex;
	}
	//BSScaleformRenderer::SetCurrentRenderTarget
	(BSShaderManager__spCamera) = (uintptr_t)shaderCam;
	(&BSGraphics__gState.get())->SetCameraData(shaderCam, 0, 0.0, 1.0);
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
	if (!InterlockedDecrement(&obj->refCount)) {
		obj->DeleteThis();
	}
	return renderedTexture;
}

void nsScope_CreateRenderer() {
	logIfNeeded("ScopeRenderer Creation Starting...");
	
	//create a spinlock
	scopeRendererLock = *(new BSReadWriteLock());
	//scopeRendererLock = (*(BSReadWriteLock*)Heap_Allocate(sizeof(BSReadWriteLock)));
	logIfNeeded("ScopeRendererLock Allocated...");
	new(&scopeRendererLock) BSReadWriteLock();
	
	if (scopeRenderer != nullptr) {

	}

	//if renderer is null
	if (!scopeRenderer) {
		scopeRenderer = nsScope_InitRenderer();
		//in nsPipboy_LocalMap::CreateRenderer this is where the localMapCameraUpdateEvent stuff would also be created
	}

	//Unlock?
	//if ((&scopeRendererLock)->lockValue == 1) {
	//	(&scopeRendererLock)->threadID = (&scopeRendererLock)->lockValue -1;
	//	_mm_mfence();
	//	InterlockedCompareExchange(&(&scopeRendererLock)->lockValue, (&scopeRendererLock)->lockValue - 1, (&scopeRendererLock)->lockValue);
	//} else {
	//	InterlockedDecrement(&(&scopeRendererLock)->lockValue);
	//}
	(&scopeRendererLock)->unlock_write();
	(&scopeRendererLock)->unlock_read();

	logIfNeeded("ScopeRenderer Creation Complete.");
}

ScopeRenderer* nsScope_InitRenderer() {
	logIfNeeded("ScopeRenderer Init Starting...");

	ScopeRenderer* renderer;
	ScopeRenderer* newRenderer;

	//allocate our renderer
	renderer = new ScopeRenderer();
	//renderer = (ScopeRenderer*)Heap_Allocate(sizeof(ScopeRenderer)); //LocalMapRenderer allocates 0x2B0 (688)
	logIfNeeded("ScopeRenderer Allocated...");
	//if allocated succesful
	if (renderer) {
		//new(renderer) ScopeRenderer();
		newRenderer = renderer;
	} else {
		newRenderer = nullptr;
	}
	//a2 = g_player->data.location.NiPoint3;
	//if (TESObjectREFR::GetWorldSpace(pPlayer._ptr) && (TESObjectREFR::GetWorldSpace(pc)->flags & 0x40) == 0) {
	//	WorldSpace = TESObjectREFR::GetWorldSpace(pPlayer._ptr);
	//	TESWorldSpace::AdjustMapMarkerCoord(WorldSpace, &a2, 0);
	//}
	//(&newRenderer->scopeCam)->SetInitialPosition(&a2);
	//(&newRenderer->scopeCam)->SetMinFrustum(value, value * 0.5625);
	//nsPipboy_LocalMap::GetLoadedAreaExtents(&a3, &v11, a1);
	//(&newRenderer->scopeCam)->SetExtents(&v12, &v11);
	//parentCell = pPlayer._ptr->parentCell;
	//if (parentCell) {
	//	NorthRotation = TESObjectCELL::GetNorthRotation(parentCell);
	//	(&newRenderer->scopeCam)->SetZRotation(&newLocalMapRenderer->LocalMapCamera, COERCE_FLOAT(LODWORD(NorthRotation) ^ _xmm.v.vector4_i.x));
	//}

	logIfNeeded("ScopeRenderer Init Complete.");
	return newRenderer;
}

void nsScope_Render() {
	
	NiTexture* renderedTexture;

	
	(&scopeRendererLock)->lock_read();
	if (scopeRenderer) {
		renderedTexture = (scopeRenderer)->Render(1);
		if (renderedTexture) {
			//if (texID string init) {
			//	stuff about localMapTextureID
			//	stuff
			//}
			//here there would be stuff for setting the renderedTexture to be the scaleform texture

			NiPointer<BSShaderProperty> shaderProperty;

			BSEffectShaderProperty* effectShaderProperty;
			BSEffectShaderMaterial* effectShaderMaterial;
			shaderProperty.reset((BSShaderProperty*)ScopeTextureLoader->shaderProperty.get());
			effectShaderProperty = (BSEffectShaderProperty*)(shaderProperty.get());
			if (shaderProperty.get()) {
				effectShaderMaterial = static_cast<BSEffectShaderMaterial*>(shaderProperty->material);
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
	//if ((&scopeRendererLock)->lockValue == 1) {
	//	(&scopeRendererLock)->threadID = 0;
	//	_mm_mfence();
	//	InterlockedCompareExchange(&(&scopeRendererLock)->lockValue, 0, (&scopeRendererLock)->lockValue);
	//} else {
	//	InterlockedDecrement(&(&scopeRendererLock)->lockValue);
	//}
	
	
	scopeRendererLock.unlock_read();
	scopeRendererLock.unlock_write();
}

void RenderScopeScene(NiCamera* cam, BSShaderAccumulator* shadeAccum, std::uint32_t a1, std::uint32_t a2, std::uint32_t a3) {
	(BSGraphics__gRenderTargetManager)->SetCurrentDepthStencilTarget(a3, BSGraphics::SetRenderTargetMode::SRTM_FORCE_COPY_RESTORE, 0, 0);
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(0, a1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(1, a2, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(2, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(3, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	if ((BSShaderManager__State).get().unk56) {
		(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(4, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	}
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(5, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics__gRenderTargetManager)->SetCurrentViewportForceToRenderTargetDimensions();
	(BSGraphics__gRenderer).get().SetClearColor(0.0, 0.0, 0.0, 0.0);
	(BSGraphics__gRenderer).get().ClearColor();
	(BSGraphics__gRenderer).get().Flush();
	//Threaded stuff happens here in RenderLocalMapScene
	//stuff
	//more stuff
	(BSGraphics__gState).get().SetCameraData(cam, 0, 0.0, 1.0);
	(BSGraphics__gRenderer).get().DoZPrePass(0, 0, 0.0, 1.0, 0.0, 1.0);
	shadeAccum->RenderOpaqueDecals();
	shadeAccum->RenderBatches(4, 0, -1);
	shadeAccum->RenderBlendedDecals();
	//BSGraphics::pDefaultContext stuff happens here in RenderLocalMapScene
	//stuff
	//more stuff
	(BSGraphics__gRenderer).get().Flush();
	(BSGraphics__gRenderer).get().SetClearColor(1.0, 1.0, 1.0, 1.0);
	//more context stuff
	//more things
	shadeAccum->ClearEffectPasses();
	shadeAccum->ClearActivePasses(0);
}
