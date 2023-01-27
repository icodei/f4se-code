#include "f4se/BSShader.h"

void BSShaderManager::GetTexture(const char* filePath, bool a2, NiPointer<NiTexture>& returnTex, bool a4, bool a5, bool a6) {
	if (returnTex) {
		CALL_MEMBER_FN(this, GetTexture)(filePath, a2, returnTex, a4, a5, a6);
	}
}

void BSShaderAccumulator::ClearActivePasses(bool a1) {
	CALL_MEMBER_FN(this, ClearActivePasses)(a1);
}

void BSShaderAccumulator::ClearEffectPasses() {
	CALL_MEMBER_FN(this, ClearEffectPasses)();
}

void BSShaderAccumulator::ClearGroupPasses(SInt32 a1, bool a2) {
	CALL_MEMBER_FN(this, ClearGroupPasses)(a1, a2);
}

void BSShaderAccumulator::RenderBatches(SInt32 a1, bool a2, SInt32 a3) {
	CALL_MEMBER_FN(this, RenderBatches)(a1, a2, a3);
}

void BSShaderAccumulator::RenderBlendedDecals() {
	CALL_MEMBER_FN(this, RenderBlendedDecals)();
}

void BSShaderAccumulator::RenderOpaqueDecals() {
	CALL_MEMBER_FN(this, RenderOpaqueDecals)();
}

namespace BSShaderUtil {
	RelocAddr<_SetSceneFOV> SetSceneFOV_Internal(0x028201F0);
	void SetCameraFOV(BSSceneGraph* scene, float FOV, bool a3, NiCamera* cam, bool a4) {
		SetSceneFOV_Internal(scene, FOV, a3, cam, a4);
	}

	RelocAddr<_SetCameraFOV> SetCameraFOV_Internal(0x02820430);
	void SetCameraFOV(NiCamera* cam, float FOV, float f_far, float f_near) {
		SetCameraFOV_Internal(cam, FOV, f_far, f_near);
	}

	RelocAddr<_AccumulateSceneArray> AccumulateSceneArray_Internal(0x0281B0F0);
	void AccumulateSceneArray(NiCamera* cam, BSTArray<NiPointer<NiAVObject>>* objs, BSCullingProcess& cullproc, bool a1) {
		AccumulateSceneArray_Internal(cam, objs, cullproc, a1);
	}

	RelocAddr<_AccumulateScene> AccumulateScene_Internal(0x0281ADE0);
	void AccumulateScene(NiCamera* cam, NiAVObject* obj, BSCullingProcess& cullproc, bool a1) {
		AccumulateScene_Internal(cam, obj, cullproc, a1);
	}
}

RelocPtr <BSShaderAccumulator*>		pCurrentShaderAccumulator(0x06721AB0);
RelocPtr <BSShaderManager::State>	ShaderManager_gState(0x06721B70);
RelocPtr <BSShaderManager>			gShaderManagerInstance(0x06721B39);
RelocPtr <NiCamera*>				BSShaderManager_spCamera(0x06721AE0);
RelocPtr <BSShaderMaterial*>		pShaderMaterialDefault(0x06723120);
RelocPtr <BSShaderResourceManager>	gShaderResourceManagerInstance(0x038CBDC0);