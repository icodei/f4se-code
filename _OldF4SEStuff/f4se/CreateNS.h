#pragma once
#include "f4se_common/Utilities.h"

class NiObject;
class BSEffectShaderProperty;
class BSLightingShaderProperty;
class BSTriShape;
class NiCamera;
class NiNode;

typedef NiObject* (*_Create_BSEffectShaderProperty)();
BSEffectShaderProperty* Create_BSEffectShaderProperty();

typedef NiObject* (*_Create_BSLightingShaderProperty)();
BSLightingShaderProperty* Create_BSLightingShaderProperty();

typedef NiObject* (*_Create_BSTriShape)();
BSTriShape* Create_BSTriShape();

typedef NiObject* (*_Create_NiCamera)();
NiCamera* Create_NiCamera();

typedef NiObject* (*_Create_NiNode)();
NiNode* Create_NiNode();

