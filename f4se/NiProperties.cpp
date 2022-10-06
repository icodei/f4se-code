#include "f4se/NiProperties.h"


void BSShaderProperty::SetEffectShaderData(BSEffectShaderData* shaderData) {
	CALL_MEMBER_FN(this, SetEffectShaderData)(shaderData);
};

BSLightingShaderProperty* BSLightingShaderProperty::Create()
{
	BSLightingShaderProperty* prop = (BSLightingShaderProperty*)Heap_Allocate(sizeof(BSLightingShaderProperty));
	CALL_MEMBER_FN(prop, ctor)();
	return prop;
}

BSEffectShaderProperty* BSEffectShaderProperty::Create()
{
	BSEffectShaderProperty* prop = (BSEffectShaderProperty*)Heap_Allocate(sizeof(BSEffectShaderProperty));
	CALL_MEMBER_FN(prop, ctor)();
	return prop;
}

BSEffectShaderMaterial* BSEffectShaderProperty::QEffectShaderMaterial() {
	return CALL_MEMBER_FN(this, QEffectShaderMaterial)();
};

bool BSEffectShaderProperty::SetupGeometry(BSGeometry* geom) {
	return CALL_MEMBER_FN(this, SetupGeometry)(geom);
};