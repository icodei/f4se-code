#include "Global.h"

RelocAddr <_Create_BSEffectShaderProperty> Create_BSEffectShaderProperty_Internal(0x027CBBE0);
BSEffectShaderProperty* Create_BSEffectShaderProperty() {
	return (BSEffectShaderProperty*)Create_BSEffectShaderProperty_Internal();
}

RelocAddr <_Create_BSLightingShaderProperty> Create_BSLightingShaderProperty_Internal(0x027CFBB0);
BSLightingShaderProperty* Create_BSLightingShaderProperty() {
	return (BSLightingShaderProperty*)Create_BSLightingShaderProperty_Internal();
}

RelocAddr <_Create_BSTriShape> Create_BSTriShape_Internal(0x01BB66D0);
BSTriShape* Create_BSTriShape() {
	return (BSTriShape*)Create_BSTriShape_Internal();
}

RelocAddr <_Create_NiCamera> Create_NiCamera_Internal(0x01BAE180);
NiCamera* Create_NiCamera() {
	return (NiCamera*)Create_NiCamera_Internal();
}

RelocAddr <_Create_NiNode> Create_NiNode_Internal(0x01B99E60);
NiNode* Create_NiNode() {
	return (NiNode*)Create_NiNode_Internal();
}
