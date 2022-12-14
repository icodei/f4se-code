#include "f4se/NiProperties.h"

void BSShaderProperty::SetEffectShaderData(BSEffectShaderData* shaderData) {
	CALL_MEMBER_FN(this, SetEffectShaderData)(shaderData);
}

BSRenderPass* BSShaderProperty::RenderPassArray_Add(BSShader* a_shader, BSShaderProperty* a_prop, BSGeometry* a_geom, UInt32 a1, UInt8 a2, BSLight* a_light, BSLight* a_light2, BSLight* a_light3, BSLight* a_light4) {
	return CALL_MEMBER_FN(this, RenderPassArray_Add)(a_shader, a_prop, a_geom, a1, a2, a_light, a_light2, a_light3, a_light4);
}

BSRenderPass* BSShaderProperty::RenderPassArray_Replace(BSRenderPass* a_pass, BSShader* a_shader, BSShaderProperty* a_prop, BSGeometry* a_geom, UInt32 a1) {
	return CALL_MEMBER_FN(this, RenderPassArray_Replace)(a_pass, a_shader, a_prop, a_geom, a1);
}

BSLightingShaderProperty* BSLightingShaderProperty::Create() {
	BSLightingShaderProperty* prop = (BSLightingShaderProperty*)Heap_Allocate(sizeof(BSLightingShaderProperty));
	CALL_MEMBER_FN(prop, ctor)();
	return prop;
}

BSEffectShaderProperty* BSEffectShaderProperty::Create() {
	BSEffectShaderProperty* prop = (BSEffectShaderProperty*)Heap_Allocate(sizeof(BSEffectShaderProperty));
	CALL_MEMBER_FN(prop, ctor)();
	return prop;
}

BSShaderProperty::RenderPassArray* BSEffectShaderProperty::GetRenderPasses(BSGeometry* a_geom, UInt32 a1, BSShaderAccumulator* a_accumulator) {
	return CALL_MEMBER_FN(this, GetRenderPasses)(a_geom, a1, a_accumulator);
}

NiTexture* BSEffectShaderProperty::QBaseTexture() {
	return CALL_MEMBER_FN(this, QBaseTexture)();
}

BSEffectShaderMaterial* BSEffectShaderProperty::QEffectShaderMaterial() {
	return CALL_MEMBER_FN(this, QEffectShaderMaterial)();
}

NiTexture* BSEffectShaderProperty::QEnvMap() {
	return CALL_MEMBER_FN(this, QEnvMap)();
}

NiTexture* BSEffectShaderProperty::QEnvMapMask() {
	return CALL_MEMBER_FN(this, QEnvMapMask)();
}

NiTexture* BSEffectShaderProperty::QGrayscaleTexture() {
	return CALL_MEMBER_FN(this, QGrayscaleTexture)();
}

NiTexture* BSEffectShaderProperty::QNormalMap() {
	return CALL_MEMBER_FN(this, QNormalMap)();
};

void BSEffectShaderProperty::SetBaseTexture(NiTexture* newTex) {
	BSEffectShaderMaterial* mat = (BSEffectShaderMaterial*)this->shaderMaterial;
	NiTexture* tex = mat->spBaseTexture.get();
	if (tex != newTex) {
		if (newTex) {
			InterlockedIncrement(&newTex->m_uiRefCount);
		}
		mat->spBaseTexture = newTex;
		if (tex) {
			if (!InterlockedDecrement(&tex->m_uiRefCount)) {
				tex->DeleteThis();
			}
		}
	}
}

void BSEffectShaderProperty::SetEnvMap(NiTexture* newTex) {
	CALL_MEMBER_FN(this, SetEnvMap)(newTex);
}

void BSEffectShaderProperty::SetEnvMapMask(NiTexture* newTex) {
	BSEffectShaderMaterial* mat = (BSEffectShaderMaterial*)this->shaderMaterial;
	NiTexture* tex = mat->spEnvironmentMapMaskTexture.get();
	if (tex != newTex) {
		if (newTex) {
			InterlockedIncrement(&newTex->m_uiRefCount);
		}
		mat->spEnvironmentMapMaskTexture = newTex;
		if (tex) {
			if (!InterlockedDecrement(&tex->m_uiRefCount)) {
				tex->DeleteThis();
			}
		}
	}
}

void BSEffectShaderProperty::SetGrayscaleTexture(NiTexture* newTex) {
	BSEffectShaderMaterial* mat = (BSEffectShaderMaterial*)this->shaderMaterial;
	NiTexture* tex = mat->spGrayscaleTexture.get();
	if (tex != newTex) {
		if (newTex) {
			InterlockedIncrement(&newTex->m_uiRefCount);
		}
		mat->spGrayscaleTexture = newTex;
		if (tex) {
			if (!InterlockedDecrement(&tex->m_uiRefCount)) {
				tex->DeleteThis();
			}
		}
	}
}

void BSEffectShaderProperty::SetNormalMap(NiTexture* newTex) {
	return CALL_MEMBER_FN(this, SetNormalMap)(newTex);
}

bool BSEffectShaderProperty::SetupGeometry(BSGeometry* geom) {
	return CALL_MEMBER_FN(this, SetupGeometry)(geom);
}