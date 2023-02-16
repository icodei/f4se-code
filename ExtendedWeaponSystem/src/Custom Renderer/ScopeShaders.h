#pragma once
#include "Global.h"

void SetupTextureLoaderWithEffectShader();
void SetupImageSpaceShader(BSGeometry* objGeom, bool active);
BSEffectShaderData* CreateEffectShaderDataCustom(TESEffectShader* shader, NiTexture* tex1, NiTexture* tex2, NiTexture* tex3);