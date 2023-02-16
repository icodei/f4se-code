#include "Global.h"

std::unordered_map<const char*, NiCamera*> s_extraCamerasMap;


bool ExtraCameraManager::AttachExtraCamera(const char camName[0x40], bool doAttach, char nodeName) {

	NiCamera* cam;
	NiCamera** pCam;

	if (doAttach) {
		BSFixedString sCamName(camName);
		BSFixedString sNodeName(&nodeName);
		NiNode* targetNode = (NiNode*)GetByNameHelper(sNodeName);
		if (targetNode) {
			if (std::get<bool>(s_extraCamerasMap.insert(std::pair<const char*, NiCamera*>(camName, *pCam)))) {
				*pCam = cam = Create_NiCamera();
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
	}
	else {
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

bool ExtraCameraManager::ProjectExtraCamera(const char camName[0x40], const char nodeName[0x40], float fov, std::uint32_t pixelSize) {
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
