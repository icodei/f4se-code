#pragma once
#include "Global.h"

BSEffectShaderData* CreateEffectShaderDataCustom(TESEffectShader* shader, NiTexture* tex1, NiTexture* tex2, NiTexture* tex3);
void SetupGeometryWithEffectShader(BSGeometry* geometryToSetup, TESEffectShader* shaderToUse, BSEffectShaderData& returnData);
void SetupImageSpaceShader(BSGeometry* objGeom, bool active);
