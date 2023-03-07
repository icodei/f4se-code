#include "Global.h"

//ScopeRenderer* scopeRenderer;
//BSSpinLock scopeRendererLock;

ScopeRenderer::ScopeRenderer() {
	logIfNeeded("ScopeRenderer ctor Starting...");

	BSShaderAccumulator* shaderAccum;
	BSShaderAccumulator* newShaderAccum;
	BSShaderAccumulator* oldShaderAccum;
	BSShaderAccumulator* pShaderAccum;

	logIfNeeded("ScopeRenderer - Creating BSCullingProcess...");
	new (&pScopeCullingProc) BSCullingProcess(0);
	logIfNeeded("ScopeRenderer - Creating ScopeCamera...");
	new (&scopeCam) ScopeCamera();
	logIfNeeded("ScopeRenderer - Creating ImageSpaceShaderParam...");
	new (&shaderParams) ImageSpaceShaderParam();
	//spScopeAccumulator = nullptr;

	shaderAccum = (BSShaderAccumulator*)RE::malloc(0x590);
	if (shaderAccum) {
		new (shaderAccum) BSShaderAccumulator();
		newShaderAccum = shaderAccum;
		logIfNeeded("ScopeRenderer - Created BSShaderAccumulator");
	} else {
		newShaderAccum = nullptr;
		logIfNeeded("ScopeRenderer - BSShaderAccumulator Creation FAILED");
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
	pScopeAccumulator->QZPrePass = 1;
	pScopeAccumulator->ShadowSceneNode = (BSShaderManager__State).get().pShadowSceneNode[0];
	pShaderAccum = pScopeAccumulator;
	pShaderAccum->QSilhouetteColor.r = 1.0;
	pShaderAccum->QSilhouetteColor.g = 1.0;
	pShaderAccum->QSilhouetteColor.b = 1.0;
	pShaderAccum->QSilhouetteColor.a = 1.0;
	pScopeCullingProc->SetAccumulator(pScopeAccumulator);
	pScopeCullingProc->CullingType = BSCullingProcess::BSCP_CULL_IGNOREMULTIBOUNDS;
	pScopeCullingProc->m_bCameraRelatedUpdates = 0;
	(&shaderParams)->ResizeConstantGroup(0, 1);
	renderTarget = 19;

	logIfNeeded("ScopeRenderer ctor Completed.");
}

ScopeRenderer::ScopeRenderer(BSCullingProcess* cullingProcess, ScopeCamera* camera, BSShaderAccumulator* accumulator, ImageSpaceShaderParam* params) {
	pScopeCullingProc = cullingProcess;
	scopeCam = *camera;
	pScopeAccumulator = accumulator;
	shaderParams = *params;
}

ScopeRenderer::~ScopeRenderer() {
	BSShaderAccumulator* shaderAccum;
	NiCamera* cam;
	TESCameraState* state;

	(&shaderParams)->~ImageSpaceShaderParam();
	shaderAccum = pScopeAccumulator;
	if (shaderAccum && !InterlockedDecrement(&shaderAccum->refCount)) {
		shaderAccum->DeleteThis();
	}
	cam = scopeCam.camera;
	if (cam && !InterlockedDecrement(&cam->refCount)) {
		cam->DeleteThis();
	}
	state = scopeCam.currentState.get();
	if (state && !InterlockedDecrement(&state->refCount)) {
		state->~TESCameraState();
	}
	(&scopeCam)->~ScopeCamera();
	pScopeCullingProc->~BSCullingProcess();
}

ScopeRenderer& ScopeRenderer::operator=(const ScopeRenderer& rhs) {
	memcpy(pScopeCullingProc, rhs.pScopeCullingProc, 0x1A0);
	//pScopeCullingProc = rhs.pScopeCullingProc;
	scopeCam = rhs.scopeCam;
	pScopeAccumulator = rhs.pScopeAccumulator;
	shaderParams = rhs.shaderParams;
	renderTarget = rhs.renderTarget;
}

NiTexture* ScopeRenderer::Render(bool a1) {
	ScopeRenderer* pScopeRenderer = (this);
	ScopeCamera* scopeCam = (&pScopeRenderer->scopeCam);

	NiCamera* shaderCam = (BSShaderManager__spCamera).get();

	BSCullingProcess scopeCulling{ BSCullingProcess(0) };
	new (&scopeCulling) BSCullingProcess(0);  //Is this still needed with the above statement?

	ShadowSceneNode* pWorldSSN = (BSShaderManager__State).get().pShadowSceneNode[0];
	ShadowSceneNode* pWorldSSN2 = (BSShaderManager__State).get().pShadowSceneNode[0];
	NiAVObject* objectLODRoot = (&BSShaderManager__State.get())->pShadowSceneNode[0]->children[3].get();
	NiAVObject* pObj = objectLODRoot;
	if (objectLODRoot) {
		InterlockedIncrement(&objectLODRoot->refCount);
	}
	bool objCullFlag = objectLODRoot->flags.flags & 1;
	objectLODRoot->SetAppCulled(1);

	(BSShaderManager__spCamera) = (uintptr_t)scopeCam->camera;

	(&BSGraphics__gState.get())->SetCameraData(scopeCam->camera, 0, 0.0, 1.0);
	(&scopeCulling)->SetAccumulator(pScopeRenderer->pScopeAccumulator);
	(&scopeCulling)->CullingType = BSCullingProcess::BSCP_CULL_IGNOREMULTIBOUNDS;
	(&scopeCulling)->m_bCameraRelatedUpdates = 0;
	(&scopeCulling)->m_pkCamera = scopeCam->camera;

	scopeCam->Update();

	(&BSGraphics__gRenderer.get())->SetClearColor(1.0, 1.0, 1.0, 1.0);

	pScopeRenderer->pScopeAccumulator->renderMode = BSShaderManager::etRenderMode::BSSM_RENDER_VATS_MASK;
	pScopeRenderer->pScopeAccumulator->QEyePosition = scopeCam->camera->world.translate;
	(&BSGraphics__gRenderer.get())->ResetZPrePass();
	AccumulateSceneFunctor acummulateFunctor;
	acummulateFunctor.renderer = pScopeRenderer;
	if (TES::GetSingleton()->GetWorldSpace() || (acummulateFunctor.interior = 0, TES::GetSingleton()->GetWorldSpace()->flags & 0x40) == 0) {
		acummulateFunctor.interior = 1;
	}

	BSPortalGraphEntry* camPortalEntry = (Main::GetSingleton())->GetCameraPortalGraphEntry();
	if (camPortalEntry) {
		BSPortalGraph* camPortalGraph = camPortalEntry->QPortalGraph;
		if (camPortalGraph) {
			BSShaderUtil::AccumulateSceneArray(scopeCam->camera, &camPortalGraph->QAlwaysRenderArray, scopeCulling, 0);
		}
	}

	NiAVObject* portalSharedNode;
	if (pWorldSSN->children.size() > 9) {
		portalSharedNode = pWorldSSN->children[9].get();
		BSShaderUtil::AccumulateScene(scopeCam->camera, portalSharedNode, scopeCulling, 0);
	} else {
		portalSharedNode = nullptr;
	}
	
	NiAVObject* multiBoundNode;
	if (pWorldSSN->children.size() > 8) {
		multiBoundNode = pWorldSSN->children[8].get();
		BSShaderUtil::AccumulateScene(scopeCam->camera, multiBoundNode, scopeCulling, 0);
	} else {
		multiBoundNode = nullptr;
	}

	(&BSShaderManager__State.get())->cSceneGraph = BSShaderManager::BSSM_SSN_WORLD;
	(&BSShaderManager__State.get())->pShadowSceneNode[0]->ProcessQueuedLights(&scopeCulling);
	(&BSGraphics__gRenderer.get())->ResetState();
	int depthTarget = 1;
	int renderTarget = 27;
	int fogOfWarTarget = 22;
	(BSGraphics__gRenderTargetManager)->AcquireDepthStencil(depthTarget);
	(BSGraphics__gRenderTargetManager)->AcquireRenderTarget(renderTarget);
	RenderScopeScene(scopeCam->camera, pScopeRenderer->pScopeAccumulator, renderTarget, depthTarget);
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(0, 2, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(1, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics__gRenderTargetManager)->SetCurrentDepthStencilTarget(1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, 0);
	//FogOfWar Setup stuff would happen after this in the LocalMapRenderer::Render
	//stuff and things
	//
	(BSGraphics__gRenderTargetManager)->SetCurrentDepthStencilTarget(0, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, 0);
	pScopeRenderer->shaderParams.SetPixelConstant(0, 1.0 / (float)(int)(*BSGraphics__gRenderTargetManager).pRenderTargetDataA[pScopeRenderer->renderTarget].uiWidth, 1.0 / (float)(int)(*BSGraphics__gRenderTargetManager).pRenderTargetDataA[pScopeRenderer->renderTarget].uiHeight, 0.0, 0.0);
	(BSGraphics__gRenderTargetManager)->SetTextureDepth(1, depthTarget);
	(BSGraphics__gRenderTargetManager)->SetTextureRenderTarget(2, renderTarget, 0);
	int effect = 152;
	(ImageSpaceManager__pInstance)->effectArray[effect].UseDynamicResolution = 0;
	(ImageSpaceManager__pInstance)->RenderEffect_1((ImageSpaceManager::ImageSpaceEffectEnum)effect, pScopeRenderer->renderTarget, &pScopeRenderer->shaderParams);
	(BSGraphics__gRenderTargetManager)->ReleaseDepthStencil(depthTarget);
	(BSGraphics__gRenderTargetManager)->ReleaseRenderTarget(renderTarget);
	
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
	
	pScopeRenderer->pScopeAccumulator->ClearActivePasses(0);
	pScopeRenderer->pScopeAccumulator->ClearGroupPasses(5, 0);
	(&scopeCulling)->~BSCullingProcess();
	
	objectLODRoot->SetAppCulled(objCullFlag);
	if (!InterlockedDecrement(&objectLODRoot->refCount)) {
		objectLODRoot->DeleteThis();
	}
	return renderedTexture;
}

void nsScope::CreateRenderer() {
	logIfNeeded("ScopeRenderer Creation Starting...");

	//create a spinlock
	scopeRendererLock = *(new BSSpinLock());
	logIfNeeded("ScopeRendererLock Allocated...");
	new (&scopeRendererLock) BSSpinLock();

	if (&scopeRenderer != nullptr) {
		return;
	}

	//if renderer is null
	if (!&scopeRenderer) {
		scopeRenderer = InitRenderer();
		//in nsPipboy_LocalMap::CreateRenderer this is where the localMapCameraUpdateEvent stuff would also be created
	}
	(&scopeRendererLock)->unlock();

	logIfNeeded("ScopeRenderer Creation Complete.");
}

void nsScope::DestroyRenderer() {

}

ScopeRenderer* nsScope::InitRenderer() {
	logIfNeeded("ScopeRenderer Init Starting...");

	ScopeRenderer* renderer;
	ScopeRenderer* newRenderer;

	//allocate our renderer
	renderer = new ScopeRenderer();
	logIfNeeded("ScopeRenderer Allocated...");
	//if allocated succesful
	if (renderer) {
		newRenderer = renderer;
	} else {
		newRenderer = nullptr;
	}
	/*
	a2 = g_player->data.location.NiPoint3;
	if (TESObjectREFR::GetWorldSpace(pPlayer._ptr) && (TESObjectREFR::GetWorldSpace(pc)->flags & 0x40) == 0) {
		WorldSpace = TESObjectREFR::GetWorldSpace(pPlayer._ptr);
		TESWorldSpace::AdjustMapMarkerCoord(WorldSpace, &a2, 0);
	}
	(&newRenderer->scopeCam)->SetInitialPosition(&a2);
	(&newRenderer->scopeCam)->SetMinFrustum(value, value * 0.5625);
	nsPipboy_LocalMap::GetLoadedAreaExtents(&a3, &v11, a1);
	(&newRenderer->scopeCam)->SetExtents(&v12, &v11);
	parentCell = pPlayer._ptr->parentCell;
	if (parentCell) {
		NorthRotation = TESObjectCELL::GetNorthRotation(parentCell);
		(&newRenderer->scopeCam)->SetZRotation(&newLocalMapRenderer->LocalMapCamera, COERCE_FLOAT(LODWORD(NorthRotation) ^ _xmm.v.vector4_i.x));
	}
	*/

	logIfNeeded("ScopeRenderer Init Complete.");
	return newRenderer;
}

void nsScope::Render() {
	NiTexture* renderedTexture;

	(&scopeRendererLock)->lock();
	if (&scopeRenderer) {
		renderedTexture = (scopeRenderer)->Render(1);
		if (renderedTexture) {
			/*
			if (texID string init) {
				//stuff about localMapTextureID
				//stuff
			}
			//here there would be stuff for setting the renderedTexture to be the scaleform texture
			*/

			NiPointer<BSShaderProperty> shaderProperty;

			BSEffectShaderProperty* effectShaderProperty;
			BSEffectShaderMaterial* effectShaderMaterial;
			shaderProperty.reset((BSShaderProperty*)(ScopeTextureLoader->shaderProperty.get()));
			effectShaderProperty = (BSEffectShaderProperty*)(shaderProperty.get());
			if (shaderProperty.get()) {
				effectShaderMaterial = static_cast<BSEffectShaderMaterial*>(shaderProperty->material);
				effectShaderMaterial->spBaseTexture.reset(renderedTexture);
				effectShaderMaterial->fBaseColorScale = 1.0;
				effectShaderMaterial->kBaseColor = NiColorA(1.0, 1.0, 1.0, 1.0);
			}

			/*
			BSLightingShaderProperty* lightingShaderProperty;
			BSLightingShaderMaterial* lightingShaderMaterial;
			shaderProperty.reset((BSShaderProperty*)ScopeTextureLoader->shaderProperty.get());
			lightingShaderProperty = (BSLightingShaderProperty*)(shaderProperty.get());
			if (shaderProperty.get()) {
				lightingShaderMaterial = static_cast<BSLightingShaderMaterial*>(shaderProperty->material);
			}
			*/
		}
	}
	scopeRendererLock.unlock();
}

void RenderScopeScene(NiCamera* cam, BSShaderAccumulator* shadeAccum, std::uint32_t target, std::uint32_t depthTarget) {
	(BSGraphics__gRenderTargetManager)->SetCurrentDepthStencilTarget(depthTarget, BSGraphics::SetRenderTargetMode::SRTM_FORCE_COPY_RESTORE, 0, 0);
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(1, target, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(2, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(3, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	if ((BSShaderManager__State).get().bDeferredRGBEmit) {
		(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(4, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	}
	(BSGraphics__gRenderTargetManager)->SetCurrentRenderTarget(5, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	(BSGraphics__gRenderTargetManager)->SetCurrentViewportForceToRenderTargetDimensions();
	(&BSGraphics__gRenderer.get())->SetClearColor(0.0, 0.0, 0.0, 0.0);
	(&BSGraphics__gRenderer.get())->ClearColor();
	(&BSGraphics__gRenderer.get())->Flush();
	//Threaded stuff happens here in RenderLocalMapScene
	//stuff
	//more stuff
	(&BSGraphics__gState.get())->SetCameraData(cam, 0, 0.0, 1.0);
	(&BSGraphics__gRenderer.get())->DoZPrePass(0, 0, 0.0, 1.0, 0.0, 1.0);
	shadeAccum->RenderOpaqueDecals();
	shadeAccum->RenderBatches(4, 0, -1);
	shadeAccum->RenderBlendedDecals();
	//BSGraphics::pDefaultContext stuff happens here in RenderLocalMapScene
	//stuff
	//more stuff
	(&BSGraphics__gRenderer.get())->Flush();
	(&BSGraphics__gRenderer.get())->SetClearColor(1.0, 1.0, 1.0, 1.0);
	//more context stuff
	//more things
	shadeAccum->ClearEffectPasses();
	shadeAccum->ClearActivePasses(0);
}
