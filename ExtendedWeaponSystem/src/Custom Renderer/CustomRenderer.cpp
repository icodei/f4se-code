#include "Global.h"

#pragma region ScopeRenderer

ScopeRenderer::ScopeRenderer() {
	logIfNeeded("ScopeRenderer ctor Starting...");

	BSShaderAccumulator* shaderAccum;
	BSShaderAccumulator* newShaderAccum;
	BSShaderAccumulator* oldShaderAccum;
	BSShaderAccumulator* pShaderAccum;

	logIfNeeded("ScopeRenderer - Creating BSCullingProcess...");
	pScopeCullingProc = (BSCullingProcess*)RE::malloc(0x1A0);
	if (&pScopeCullingProc) {
		new (pScopeCullingProc) BSCullingProcess(0);
	} else {
		pScopeCullingProc = nullptr;
		logIfNeeded("ScopeRenderer - BSCullingProcess Creation FAILED");
	}

	logIfNeeded("ScopeRenderer - Creating ScopeCamera...");
	scopeCam = *new ScopeCamera();
	if (&scopeCam) {
		new (&scopeCam) ScopeCamera();
	} else {
		logIfNeeded("ScopeRenderer - ScopeCamera Creation FAILED");
	}

	logIfNeeded("ScopeRenderer - Creating ImageSpaceShaderParam...");
	shaderParams = *(ImageSpaceShaderParam*)RE::malloc(0x90);
	if (&shaderParams) {
		new (&shaderParams) ImageSpaceShaderParam();
	} else {
		logIfNeeded("ScopeRenderer - ImageSpaceShaderParam Creation FAILED");
		shaderParams = BSImagespaceShader::GetDefaultParam();
	}

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
	pScopeAccumulator->ZPrePass = true;
	pScopeAccumulator->activeShadowSceneNode = BSShaderManager::State::GetSingleton().pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD];
	pShaderAccum = pScopeAccumulator;
	pShaderAccum->QSilhouetteColor = NiColorA::WHITE;
	pScopeCullingProc->SetAccumulator(pScopeAccumulator);
	pScopeCullingProc->CullingType = BSCullingProcess::BSCP_CULL_IGNOREMULTIBOUNDS;
	pScopeCullingProc->m_bCameraRelatedUpdates = false;
	(&shaderParams)->ResizeConstantGroup(0, 1);
	renderTarget = 19;

	logIfNeeded("ScopeRenderer ctor Completed.");
}

ScopeRenderer::ScopeRenderer(BSCullingProcess* cullingProcess, ScopeCamera* camera, BSShaderAccumulator* accumulator, ImageSpaceShaderParam* params, uint32_t target) {
	pScopeCullingProc = cullingProcess;
	scopeCam = *camera;
	pScopeAccumulator = accumulator;
	shaderParams = *params;
	renderTarget = target;
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
	cam = scopeCam.camera;
	if (cam && !InterlockedDecrement(&cam->refCount)) {
		cam->DeleteThis();
	}
	state = scopeCam.currentState.get();
	if (state && !InterlockedDecrement(&state->refCount)) {
		state->~TESCameraState();
	}
	scopeCam.~ScopeCamera();
	pScopeCullingProc->~BSCullingProcess();
}

ScopeRenderer& ScopeRenderer::operator=(const ScopeRenderer& rhs) {
	memcpy(pScopeCullingProc, rhs.pScopeCullingProc, 0x1A0);
	scopeCam = rhs.scopeCam;
	pScopeAccumulator = rhs.pScopeAccumulator;
	shaderParams = rhs.shaderParams;
	renderTarget = rhs.renderTarget;
	return *this;
}

NiTexture* ScopeRenderer::Render(bool saveTexture) {
	ScopeRenderer* pScopeRenderer = (this);
	ScopeCamera* pScopeCam = (&pScopeRenderer->scopeCam);

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
	(&scopeCulling)->CullingType = BSCullingProcess::BSCP_CULL_IGNOREMULTIBOUNDS;
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
	logIfNeeded("ScopeRenderer Creation Starting...");

	//create a spinlock
	scopeRendererLock = *(new BSSpinLock());
	logIfNeeded("ScopeRendererLock Allocated...");
	new (&scopeRendererLock) BSSpinLock();

	//there is already an exsisting renderer
	if (scopeRenderer != nullptr) {
		logIfNeeded("nsScope::CreateRenderer() was called but there was already a renderer in place");
		return;
	}

	//if renderer is null
	if (!scopeRenderer) {
		scopeRenderer = InitRenderer();
		//in nsPipboy_LocalMap::CreateRenderer this is where the localMapCameraUpdateEvent stuff would also be created
	}
	scopeRendererLock.unlock();
	readyForRender = true;
	logIfNeeded("ScopeRenderer Creation Complete.");
}

void nsScope::DestroyRenderer() {
	logIfNeeded("ScopeRenderer Destroy Starting...");
	scopeRendererLock.lock();

	ScopeRenderer* pRenderer = scopeRenderer;
	if (scopeRenderer) {
		scopeRenderer->~ScopeRenderer();
		RE::free(pRenderer);
	}
	scopeRenderer = nullptr;
	readyForRender = false;
	logIfNeeded("ScopeRenderer Destroy Complete.");
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

	logIfNeeded("ScopeRenderer Init Complete.");
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
			if (scopeRenderer->scopeCam.renderPlane->shaderProperty.get()->Type() != NiProperty::SHADE) {
				//TODO: Add a creation of a shader property to the geometry for if the shaderProperty of the current geometry is nullptr or invalid

			}
			BSShaderProperty* shaderProperty = scopeRenderer->scopeCam.renderPlane->QShaderProperty();
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
