#include "Global.h"
/*
void ScopeRendererManager::Setup() {
	logIfNeeded("ScopeRendererManager Setup Starting...");

	logIfNeeded("ScopeRendererManager - Creating BSCullingProcess...");
	BSCullingProcess* currentCullingProcess;
	BSCullingProcess* cullingProcess;
	BSCullingProcess* newCullingProcess;

	cullingProcess = (BSCullingProcess*)RE::malloc(0x1A0);
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
	NiCamera* cam;
	NiCamera* oldCam;
	NiCamera* newCam;
	NiCamera* currentCam;

	cam = NiCamera::Create();
	if (cam) {
		newCam = cam;
		logIfNeeded("ScopeRendererManager - Created NiCamera");
	} else {
		newCam = nullptr;
		logIfNeeded("ScopeRendererManager - NiCamera Creation FAILED");
	}
	currentCam = pCamera;
	if (pCamera != newCam) {
		oldCam = pCamera;
		if (newCam) {
			InterlockedIncrement(&newCam->refCount);
		}
		currentCam = newCam;
		pCamera = newCam;
		if (oldCam) {
			if (!InterlockedDecrement(&oldCam->refCount)) {
				oldCam->DeleteThis();
			}
			currentCam = pCamera;
		}
	}

	logIfNeeded("ScopeRendererManager - Creating NiCameraRootNode...");
	NiNode* currentNode;
	NiNode* newNode;
	NiNode* node;

	node = new NiNode(1);
	if (node) {
		newNode = node;
		logIfNeeded("ScopeRendererManager - Created NiNode");
	} else {
		newNode = nullptr;
		logIfNeeded("ScopeRendererManager - NiNode Creation FAILED");
	}
	currentNode = pCamera->parent;
	if (currentNode != newNode) {
		if (newNode) {
			InterlockedIncrement(&newNode->refCount);
		}
		pCamera->parent = newNode;
		if (currentNode && !InterlockedDecrement(&currentNode->refCount)) {
			currentNode->DeleteThis();
		}
	}
	pCamera->parent->AttachChild(pCamera, true);
	logIfNeeded("ScopeRendererManager Cameras Completed.");

	logIfNeeded("ScopeRendererManager - Creating ImageSpaceShaderParam...");
	ImageSpaceShaderParam* currentShaderParam;
	ImageSpaceShaderParam* shaderParam;
	ImageSpaceShaderParam* newShaderParam;

	shaderParam = (ImageSpaceShaderParam*)RE::malloc(0x90);
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

	shaderAccumulator = (BSShaderAccumulator*)RE::malloc(0x590);
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
			InterlockedIncrement(&newShaderAccumulator->refCount);
		}
		pScopeManagerAccumulator = newShaderAccumulator;
		if (currentShaderAccumulator && !InterlockedDecrement(&currentShaderAccumulator->refCount)) {
			currentShaderAccumulator->DeleteThis();
		}
	}
	pScopeManagerAccumulator->ZPrePass = 1;
	pScopeManagerAccumulator->activeShadowSceneNode = BSShaderManager::State::GetSingleton().pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD];
	pScopeManagerAccumulator->QSilhouetteColor.r = 1.0F;
	pScopeManagerAccumulator->QSilhouetteColor.g = 1.0F;
	pScopeManagerAccumulator->QSilhouetteColor.b = 1.0F;
	pScopeManagerAccumulator->QSilhouetteColor.a = 1.0F;
	pScopeManagerCullingProc->SetAccumulator(pScopeManagerAccumulator);
	pScopeManagerCullingProc->CullingType = BSCullingProcess::BSCP_CULL_IGNOREMULTIBOUNDS;
	pScopeManagerCullingProc->m_bCameraRelatedUpdates = 0;
	pScopeManagerShaderParam->ResizeConstantGroup(0, 1);
	readyForRender = 1;
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

		BSShaderProperty* shaderProperty;

		BSEffectShaderProperty* effectShaderProperty;
		BSEffectShaderMaterial* effectShaderMaterial;
		shaderProperty = (BSShaderProperty*)pRenderPlane->shaderProperty.get();
		effectShaderProperty = (BSEffectShaderProperty*)shaderProperty;
		if (shaderProperty) {
			effectShaderMaterial = static_cast<BSEffectShaderMaterial*>(shaderProperty->material);
			effectShaderMaterial->spBaseTexture = renderedTexture;
			effectShaderMaterial->fBaseColorScale = 1.0F;
			effectShaderMaterial->kBaseColor = NiColorA::WHITE;
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
	BSGraphics::State* pGraphicsState = &BSGraphics::State::GetSingleton();
	BSGraphics::RenderTargetManager* pTargetManager = &BSGraphics::RenderTargetManager::GetSingleton();
	BSGraphics::Renderer* pRenderData = &BSGraphics::Renderer::GetSingleton();
	ImageSpaceManager* pImageSpaceManager = ImageSpaceManager::GetSingleton();
	BSShaderManager::State* pShaderState = &BSShaderManager::State::GetSingleton();
	NiCamera* shaderCam = BSShaderManager::GetCamera();

	BSCullingProcess* scopeCulling = pScopeManagerCullingProc;

	ShadowSceneNode* pShadow = pShaderState->pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD];

	memcpy(BSShaderManager::GetCamera(), pCamera, 0x1A0);

	pGraphicsState->SetCameraData(pCamera, 0, 0.0F, 1.0F);
	scopeCulling->SetAccumulator(pScopeManagerAccumulator);
	scopeCulling->CullingType = BSCullingProcess::BSCP_CULL_IGNOREMULTIBOUNDS;
	scopeCulling->m_bCameraRelatedUpdates = 0;
	scopeCulling->m_pkCamera = pCamera;

	//scopeCam->Update();

	pRenderData->SetClearColor(1.0F, 1.0F, 1.0F, 1.0F);

	pScopeManagerAccumulator->renderMode = BSShaderManager::etRenderMode::BSSM_RENDER_LOCALMAP;
	pScopeManagerAccumulator->QEyePosition = pCamera->world.translate;
	pRenderData->ResetZPrePass();

	BSPortalGraphEntry* camPortalEntry = Main::GetSingleton()->GetCameraPortalGraphEntry();
	NiAVObject* pChildAt9;
	if (camPortalEntry) {
		BSPortalGraph* camPortalGraph = camPortalEntry->QPortalGraph;
		if (camPortalGraph) {
			BSShaderUtil::AccumulateSceneArray(pCamera, &camPortalGraph->QAlwaysRenderArray, (*scopeCulling), 0);
		}
	}
	if (pShadow->children.size() > 9) {
		pChildAt9 = pShadow->children[9].get();
	}
	else {
		pChildAt9 = nullptr;
	}
	BSShaderUtil::AccumulateScene(pCamera, pChildAt9, *scopeCulling, 0);
	NiAVObject* pChildAt8;
	if (pShadow->children.size() > 8) {
		pChildAt8 = pShadow->children[8].get();
	}
	else {
		pChildAt8 = nullptr;
	}
	BSShaderUtil::AccumulateScene(pCamera, pChildAt8, *scopeCulling, 0);
	pShaderState->cSceneGraph = BSShaderManager::BSSM_SSN_WORLD;
	pShaderState->pShadowSceneNode[BSShaderManager::BSSM_SSN_WORLD]->ProcessQueuedLights(scopeCulling);
	pRenderData->ResetState();
	int type = 19;
	int depthTarget = 1;
	int renderTarget = 27;
	int newRenderTarget = 22;
	pTargetManager->AcquireDepthStencil(depthTarget);
	pTargetManager->AcquireRenderTarget(newRenderTarget);

	//RenderScene
	pTargetManager->SetCurrentDepthStencilTarget(depthTarget, BSGraphics::SetRenderTargetMode::SRTM_FORCE_COPY_RESTORE, 0, 0);
	pTargetManager->SetCurrentRenderTarget(0, newRenderTarget, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	pTargetManager->SetCurrentRenderTarget(1, renderTarget, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	pTargetManager->SetCurrentRenderTarget(2, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	pTargetManager->SetCurrentRenderTarget(3, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	pTargetManager->SetCurrentRenderTarget(5, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	pTargetManager->SetCurrentViewportForceToRenderTargetDimensions();
	pRenderData->SetClearColor(0.0F, 0.0F, 0.0F, 0.0F);
	pRenderData->ClearColor();
	pRenderData->Flush();
	//Threaded stuff happens here in RenderLocalMapScene
	//stuff
	//more stuff
	pGraphicsState->SetCameraData(pCamera, 0, 0.0F, 1.0F);
	pRenderData->DoZPrePass(0, 0, 0.0F, 1.0F, 0.0F, 1.0F);
	pScopeManagerAccumulator->RenderOpaqueDecals();
	pScopeManagerAccumulator->RenderBatches(4, 0, -1);
	pScopeManagerAccumulator->RenderBlendedDecals();
	//BSGraphics::pDefaultContext stuff happens here in RenderLocalMapScene
	//stuff
	//more stuff
	pRenderData->Flush();
	pRenderData->SetClearColor(1.0F, 1.0F, 1.0F, 1.0F);
	//more context stuff
	//more things
	//pScopeManagerAccumulator->ClearEffectPasses();
	//pScopeManagerAccumulator->ClearActivePasses(0);
	//RenderSceneEnd

	pTargetManager->SetCurrentRenderTarget(0, 2, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	pTargetManager->SetCurrentRenderTarget(1, -1, BSGraphics::SetRenderTargetMode::SRTM_CLEAR);
	pTargetManager->SetCurrentDepthStencilTarget(1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, 0);
	//FogOfWar Setup stuff would happen after this in the LocalMapRenderer::Render
	//stuff and things
	//
	pTargetManager->SetCurrentDepthStencilTarget(0, BSGraphics::SetRenderTargetMode::SRTM_RESTORE, 0, 0);
	pScopeManagerShaderParam->SetPixelConstant(
		0,
		1.0F / pTargetManager->pRenderTargetDataA[type].uiWidth,
		1.0F / pTargetManager->pRenderTargetDataA[type].uiHeight,
		0.0F,
		0.0F);
	pTargetManager->SetTextureDepth(1, depthTarget);
	pTargetManager->SetTextureRenderTarget(2, renderTarget, 0);
	int effect = ((type == 20) + 152);
	pImageSpaceManager->effectArray[effect].UseDynamicResolution = 0;
	pImageSpaceManager->RenderEffectHelper_2((ImageSpaceManager::ImageSpaceEffectEnum)effect, newRenderTarget, type, pScopeManagerShaderParam);
	if (type == 20) {
		pTargetManager->ReleaseDepthStencil(depthTarget);
		pTargetManager->ReleaseRenderTarget(renderTarget);
	}
	pTargetManager->ReleaseRenderTarget(newRenderTarget);
	//Threaded stuff would happen here in LocalMapRenderer::Render
	//BSGraphics::Context = threaded stuff
	//if (!context) {
	//		context = BSGraphics::pDefaultContext
	//}
	//shadowState = &context->field_1B70;
	//Texture dirty stuff
	pTargetManager->SetCurrentRenderTarget(0, 1, BSGraphics::SetRenderTargetMode::SRTM_RESTORE);
	NiTexture* renderedTexture = nullptr;
	BSGraphics::Texture* graphicsTex = nullptr;
	if (save) {
		BSFixedString strScope("ScopeTexture");
		renderedTexture = NiTexture::CreateEmpty(strScope, 0, 0);
		graphicsTex = pTargetManager->SaveRenderTargetToTexture(19, 0, 0, BSGraphics::Usage::USAGE_DEFAULT);
		renderedTexture->rendererTexture = graphicsTex;
	}
	//BSScaleformRenderer::SetCurrentRenderTarget
	memcpy(BSShaderManager::GetCamera(), shaderCam, 0x1A0);
	pGraphicsState->SetCameraData(shaderCam, 0, 0.0F, 1.0F);
	pScopeManagerAccumulator->ClearActivePasses(0);
	pScopeManagerAccumulator->ClearGroupPasses(5, 0);
	
	return renderedTexture;
}

BSCullingProcess* ScopeRendererManager::pScopeManagerCullingProc;
BSShaderAccumulator* ScopeRendererManager::pScopeManagerAccumulator;
ImageSpaceShaderParam* ScopeRendererManager::pScopeManagerShaderParam;
NiCamera* ScopeRendererManager::pCamera;
BSGeometry* ScopeRendererManager::pRenderPlane;
*/
