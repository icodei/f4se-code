#include "Global.h"

unsigned int TESEffectShader::StartEffectShader(TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData, bool a4) {
	if (object) {
		return CALL_MEMBER_FN(this, StartEffectShader)(shader, object, shaderData, a4);
	}
	else {
		return 0;
	}
};
void TESEffectShader::StopEffectShader(TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData) {
	if (object) {
		CALL_MEMBER_FN(this, StopEffectShader)(shader, object, shaderData);
	}
	else {
		logIfNeeded("Could not stop Effect Shader");
	}
};

BSEffectShaderData* TESEffectShader::CreateEffectShaderData(NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex) {
	if (object) {
		return CALL_MEMBER_FN(this, CreateEffectShaderData)(object, baseTex, blockoutTex, specialTex);
	}
	else {
		logIfNeeded("Could not create new BSEffectShaderData.");
		return NULL;
	}
};
void TESEffectShader::ResetEffectShaderData(BSEffectShaderData* shadeData, NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex) {
	if (shadeData) {
		CALL_MEMBER_FN(this, ResetEffectShaderData)(shadeData, object, baseTex, blockoutTex, specialTex);
	}
	else {
		logIfNeeded("Could not reset the BSEffectShaderData");
	}
};

RelocAddr<_GetObjectByName> GetObjectByName_Internal(0x01C93980);
//_GetObjectByName GetObjectByName_Original = nullptr;

namespace BSUtilities {
	NiAVObject* GetObjectByName(NiAVObject* target, BSFixedString& name, bool a3, bool a4) {
		
		NiAVObject* obj = GetObjectByName_Internal(target, name, a3, a4);
		return obj;
	}
}

void InstallExtraFunc() {
	//GetObjectByName_Original = *(_GetObjectByName*)(GetObjectByName_Internal.GetUIntPtr());
	//SafeWrite64(GetObjectByName_Internal, (uintptr_t)BSUtilities::GetObjectByName);
}


RelocPtr <NiPointer<SceneGraph>>	spWorldSceneGraph(0x05AA4358);
RelocPtr <NiPointer<SceneGraph>>	spMenuRoot(0x05AA4360);
RelocPtr <NiPointer<SceneGraph>>	sp3DMenuRoot(0x05AA4368);

RelocPtr <NiPointer<NiCamera>>		spCustomCamera(0x058DF5B0);
RelocPtr <NiPointer<NiCamera>>		spCamera(0x058DEF88);