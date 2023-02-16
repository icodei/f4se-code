#include "f4se/TESEffectShader.h"

unsigned int TESEffectShader::StartEffectShader(TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData, bool a4) {
	if (object) {
		return CALL_MEMBER_FN(this, StartEffectShader)(shader, object, shaderData, a4);
	}
	else {
		return 0;
	}
}

void TESEffectShader::StopEffectShader(TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData) {
	if (object) {
		CALL_MEMBER_FN(this, StopEffectShader)(shader, object, shaderData);
	}
	else {
		return;
	}
}

BSEffectShaderData* TESEffectShader::CreateEffectShaderData(NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex) {
	if (!object) {
		return NULL;
	}
	BSEffectShaderData* data = CALL_MEMBER_FN(this, CreateEffectShaderData)(object, baseTex, blockoutTex, specialTex);
	if (data) {
		return data;
	}
	else {
		return NULL;
	}
}

void TESEffectShader::ResetEffectShaderData(BSEffectShaderData* shadeData, NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex) {
	if (shadeData) {
		CALL_MEMBER_FN(this, ResetEffectShaderData)(shadeData, object, baseTex, blockoutTex, specialTex);
	} else {
		return;
	}
}