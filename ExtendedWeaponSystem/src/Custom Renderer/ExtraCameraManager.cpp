#include "Custom Renderer/ExtraCameraManager.h"

/*
bool ExtraCameraManager::AttachExtraCamera(const char camName[0x40], bool doAttach, char nodeName) {
	NiCamera* cam = nullptr;
	NiCamera** pCam = nullptr;

	if (doAttach) {
		BSFixedString sCamName(camName);
		BSFixedString sNodeName(&nodeName);
		NiNode* targetNode = (NiNode*)GetByNameFromPlayer3D(sNodeName);
		if (targetNode) {
			if (std::get<bool>(s_extraCamerasMap.insert(std::pair<const char*, NiCamera*>(camName, *pCam)))) {
				*pCam = cam = NiCamera::Create();
				InterlockedIncrement(&cam->refCount);
				cam->name = sCamName;
				cam->viewFrustum.nearPlane = 5.0F;
				cam->viewFrustum.farPlane = 353840.0F;
				cam->minNearPlaneDist = 1.0F;
				cam->maxFarNearRatio = 70768.0F;
				cam->lodAdjust = 0.001F;
			} else {
				cam = *pCam;
			}
			if (cam->parent != targetNode) {
				targetNode->AttachChild(cam, 1);
				NiUpdateData camUpdateParams;
				cam->UpdateDownwardPass(camUpdateParams, 0);
			}
		}
	} else {
		auto findCam = s_extraCamerasMap.find(camName);
		if (findCam != s_extraCamerasMap.end()) {
			cam = findCam->second;
			s_extraCamerasMap.erase(camName);
			if (cam->parent) {
				cam->parent->DetachChild(cam);
			}
			cam->DeleteThis();
		}
	}
	return true;
}

void ExtraCameraManager::GenerateExtraCameraTexture(TESObjectCELL* cell, NiCamera* camera, NiTexture* outTexture) {
}

bool ExtraCameraManager::ProjectExtraCamera(const char camName[0x40], const char nodeName[0x40], float fov, std::uint32_t pixelSize) {
	NiCamera* cam = (*s_extraCamerasMap.find(camName)).second;
	if (cam && cam->parent) {
		NiTexture** pTex = NULL;
		if (nodeName) {
			BSFixedString sNodeName(nodeName);
			const BSGeometry* targetGeom = (BSGeometry*)GetByNameFromPlayer3D(sNodeName);
			if (targetGeom) {
				NiPointer<BSShaderProperty> shaderProperty;

				BSEffectShaderProperty* effectShaderProperty;
				shaderProperty.reset((BSShaderProperty*)(targetGeom->shaderProperty.get()));
				effectShaderProperty = (BSEffectShaderProperty*)shaderProperty.get();
				if (shaderProperty.get()) {
					NiTexture* baseTex = effectShaderProperty->GetBaseTexture();
					pTex = &baseTex;
				}
			}
		}
		if (pTex) {
			float w = tan(fov * FltPId180) * (1 / 1.5);
			cam->viewFrustum.leftPlane = -w;
			cam->viewFrustum.rightPlane = w;
			cam->viewFrustum.topPlane = w;
			cam->viewFrustum.bottomPlane = -w;
		}
	}
	return true;
}

unordered_map<const char*, NiCamera*> ExtraCameraManager::s_extraCamerasMap;
*/
