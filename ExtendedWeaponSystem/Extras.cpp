#include "Global.h"

//void* MemoryManager::Allocate(unsigned __int64 a_size, unsigned int a_alignment, bool a_alignmentRequired) {
//	return CALL_MEMBER_FN(this, Allocate)(a_size, a_alignment, a_alignmentRequired);
//}
//RelocPtr<MemoryManager>	MemoryManager_Instance(0x038CC980);

BSPortalGraphEntry* Main::GetCameraPortalGraphEntry() {
	return CALL_MEMBER_FN(this, GetCameraPortalGraphEntry)();
}
RelocPtr<Main*>						appMain(0x05AA4278);
RelocPtr<NiPointer<SceneGraph>>		Main__spWorldSceneGraph(0x05AA4358);
RelocPtr<NiPointer<SceneGraph>>		Main__spMenuRoot(0x05AA4360);
RelocPtr<NiPointer<SceneGraph>>		Main__sp3DMenuRoot(0x05AA4368);

RelocPtr<TES*>			tes(0x05AA4288);

NiFrustum& NiCamera::GetViewFrustrum() {
	return CALL_MEMBER_FN(this, GetViewFrustrum)();
}
NiRect<float>& NiCamera::GetViewPort() {
	return CALL_MEMBER_FN(this, GetViewPort)();
}

void NiCamera::SetViewFrustrum(NiFrustum& a1) {
	CALL_MEMBER_FN(this, SetViewFrustrum)(a1);
}

void NiCamera::SetViewPort(NiRect<float>& port) {
	CALL_MEMBER_FN(this, SetViewPort)(port);
}

unsigned int TESEffectShader::StartEffectShader(TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData, bool a4) {
	if (object) {
		return CALL_MEMBER_FN(this, StartEffectShader)(shader, object, shaderData, a4);
	} else {
		return 0;
	}
}

void TESEffectShader::StopEffectShader(TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData) {
	if (object) {
		CALL_MEMBER_FN(this, StopEffectShader)(shader, object, shaderData);
	} else {
		logIfNeeded("Could not stop Effect Shader");
	}
}

BSEffectShaderData* TESEffectShader::CreateEffectShaderData(NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex) {
	if (object) {
		BSEffectShaderData* data = CALL_MEMBER_FN(this, CreateEffectShaderData)(object, baseTex, blockoutTex, specialTex);
		if (data) {
			logIfNeeded("Successfully created a new BSEffectShaderData from the TESEffectShader.");
			return data;
		} else {
			logIfNeeded("Could not create new BSEffectShaderData.");
			return NULL;
		}
	} else {
		logIfNeeded("Could not create new BSEffectShaderData.");
		return NULL;
	}
}

void TESEffectShader::ResetEffectShaderData(BSEffectShaderData* shadeData, NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex) {
	if (shadeData) {
		CALL_MEMBER_FN(this, ResetEffectShaderData)(shadeData, object, baseTex, blockoutTex, specialTex);
	} else {
		logIfNeeded("Could not reset the BSEffectShaderData");
	}
}

//DrawWorld Static Stuff
RelocPtr<NiAVObject*>				DrawWorld_p1stPerson(0x06723200);
RelocPtr<NiAVObject*>				DrawWorld_pScreenSplatterRoot(0x06723230);
RelocPtr<NiCamera*>					DrawWorld_pCamera(0x06723238);
RelocPtr<NiCamera*>					DrawWorld_pVisCamera(0x06723240);
RelocPtr<NiCamera*>					DrawWorld_pScreenSplatterCamera(0x06723248);

RelocPtr<_VATSEffectRenderFunc*>	DrawWorld_VATSEffectRenderFunc(0x06723290);
RelocPtr<_Interface3DRenderFN*>		DrawWorld_Interface3DRenderFN(0x06723298);
RelocPtr<_Additional1stPersonFunc*>	DrawWorld_Additional1stPersonFunc(0x067232B0);

RelocPtr<NiPointer<BSGeometry>>		DrawWorld_spUnitBox(0x067232F0);
RelocPtr<NiPointer<NiCamera>>		DrawWorld_sp1stPersonCamera(0x067232F8);

RelocPtr<NiPointer<BSShaderAccumulator>>	DrawWorld_spDraw1stPersonAccum(0x06723358);

RelocAddr<BSCullingGroup>			DrawWorld_k1stPersonCullingGroup(0x067236A0);
RelocAddr<BSTArray<NiPointer<NiAVObject>>>	DrawWorld_Additional1stPersonGeom(0x067239C8);
//DrawWorld Static Stuff End

RelocAddr<_GetObjectByName>			GetObjectByName_Internal(0x01C93980);
namespace BSUtilities {
	NiAVObject* GetObjectByName(NiAVObject* target, const BSFixedString& name, bool a3, bool a4) {
		NiAVObject* obj = GetObjectByName_Internal(target, name, a3, a4);
		return obj;
	}
}

void InstallExtraFunc() {

}

RelocPtr <NiPointer<NiCamera>>		spCustomCamera(0x058DF5B0);
RelocPtr <NiPointer<NiCamera>>		spCamera(0x058DEF88);
