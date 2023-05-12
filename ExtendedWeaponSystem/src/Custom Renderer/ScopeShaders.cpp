#include "Custom Renderer/ScopeShaders.h"
#include "Util.h"

//TESEffectShader::CreateEffectShaderData but without the reset part breaking it
BSEffectShaderData* CreateEffectShaderDataCustom(TESEffectShader* shader, NiTexture* tex1, NiTexture* tex2, NiTexture* tex3) {
	BSEffectShaderData* newEffectShaderData = (BSEffectShaderData*)RE::malloc(0x88);
	if (newEffectShaderData) {
		newEffectShaderData->refCount = 0;
		newEffectShaderData->pNodeFilterFunction = 0i64;
		newEffectShaderData->spBaseTexture = nullptr;
		newEffectShaderData->spPaletteTexture = nullptr;
		newEffectShaderData->spBlockOutTexture = nullptr;
		newEffectShaderData->eTextureClampMode = BSGraphics::TextureAddressMode::TEXTURE_ADDRESS_MODE_WRAP_S_WRAP_T;
		newEffectShaderData->FillColor.g = 0.0F;
		newEffectShaderData->FillColor.a = 0.0F;
		newEffectShaderData->RimColor.g = 0.0F;
		newEffectShaderData->RimColor.a = 0.0F;
		newEffectShaderData->fBaseFillScale = 1.0F;
		newEffectShaderData->fBaseFillAlpha = 1.0F;
		newEffectShaderData->fBaseRimAlpha = 1.0F;
		newEffectShaderData->fVOffset = 0.0F;
		newEffectShaderData->fUScale = 1.0F;
		newEffectShaderData->fVScale = 1.0F;
		newEffectShaderData->fEdgeExponent = 1.0F;
		newEffectShaderData->eSrcBlend = NiAlphaProperty::AlphaFunction::kSrcAlpha;
		newEffectShaderData->eDestBlend = NiAlphaProperty::AlphaFunction::kInvSrcAlpha;
		newEffectShaderData->eZTestFunc = BSGraphics::DepthStencilDepthMode::DEPTH_STENCIL_DEPTH_MODE_TEST;
		newEffectShaderData->bBaseTextureProjectedUVs = 0;
	} else {
		newEffectShaderData = nullptr;
	}
	InterlockedIncrement(&newEffectShaderData->refCount);

	NiPointer<NiTexture> textureShaderTexture;
	NiPointer<NiTexture> blockOutTexture;
	NiPointer<NiTexture> paletteTexture;

	BSShaderManager::GetTexture(shader->textureShaderTexture.textureName.c_str(), false, textureShaderTexture, true, true, true);
	BSShaderManager::GetTexture(shader->blockOutTexture.textureName.c_str(), false, blockOutTexture, true, true, true);
	BSShaderManager::GetTexture(shader->paletteTexture.textureName.c_str(), false, paletteTexture, true, true, true);

	newEffectShaderData->spBaseTexture = textureShaderTexture;
	newEffectShaderData->spBlockOutTexture = blockOutTexture;
	newEffectShaderData->spPaletteTexture = paletteTexture;

	newEffectShaderData->FillColor.r = (float)BYTE0(shader->data.fillColor1) * FToRGB;
	newEffectShaderData->FillColor.g = (float)BYTE1(shader->data.fillColor1) * FToRGB;
	newEffectShaderData->FillColor.b = (float)BYTE2(shader->data.fillColor1) * FToRGB;
	newEffectShaderData->FillColor.a = 0.0F * FToRGB;

	float rimColorR = BYTE0(shader->data.edgeColor);
	float rimColorG = BYTE1(shader->data.edgeColor);
	float rimColorB = BYTE2(shader->data.edgeColor);

	newEffectShaderData->RimColor.r = (float)rimColorR * FToRGB;
	newEffectShaderData->RimColor.g = (float)rimColorG * FToRGB;
	newEffectShaderData->RimColor.b = (float)rimColorB * FToRGB;
	newEffectShaderData->RimColor.a = 0.0 * FToRGB;

	float fillAlpha;
	if (shader->data.fillAlphaFadeInTime == 0.0F && shader->data.fillAlphaFullTime == 0.0F) {
		fillAlpha = shader->data.fillAlphaFullPercent;
	} else {
		fillAlpha = 0.0F;
	}
	newEffectShaderData->fBaseFillAlpha = fillAlpha;
	float edgeAlpha = 1.0F;
	if (shader->data.edgeAlphaFadeInTime == 0.0F && shader->data.edgeAlphaFullTime == 0.0F) {
		edgeAlpha = shader->data.edgeAlphaFullPercent;
	}
	newEffectShaderData->fBaseRimAlpha = edgeAlpha;
	newEffectShaderData->fUOffset = 0;
	newEffectShaderData->fUScale = shader->data.fillTextureUScale;
	newEffectShaderData->fVScale = shader->data.fillTextureVScale;
	newEffectShaderData->fEdgeExponent = shader->data.edgeExponentValue;

	newEffectShaderData->eSrcBlend = NiAlphaProperty::AlphaFunction::kSrcAlpha;
	newEffectShaderData->eDestBlend = NiAlphaProperty::AlphaFunction::kInvSrcAlpha;
	newEffectShaderData->eZTestFunc = BSGraphics::DepthStencilDepthMode::DEPTH_STENCIL_DEPTH_MODE_TEST;
	newEffectShaderData->ucAlphaTestRef = shader->data.alphaTestStartValue;
	newEffectShaderData->bGrayscaleToColor = (shader->data.flags & 2) != 0;
	newEffectShaderData->bGrayscaleToAlpha = (shader->data.flags & 4) != 0;
	newEffectShaderData->bIgnoreTextureAlpha = (shader->data.flags & 64) != 0;
	newEffectShaderData->bBaseTextureProjectedUVs = (shader->data.flags & 128) != 0;
	newEffectShaderData->bIgnoreBaseGeomTexAlpha = BYTE1(shader->data.flags) & 1;
	newEffectShaderData->bLighting = (shader->data.flags & 512) != 0;
	newEffectShaderData->bAlpha = (shader->data.flags & 2048) != 0;

	if ((shader->data.flags & 16) != 0) {
		rimColorG = rimColorG - 255.0F;
		rimColorB = rimColorB - 255.0F;
		newEffectShaderData->RimColor.r = (float)(rimColorR - 255.0F) * FToRGB;
	} else {
		newEffectShaderData->RimColor.r = rimColorR * FToRGB;
	}
	newEffectShaderData->RimColor.g = rimColorG * FToRGB;
	newEffectShaderData->RimColor.b = rimColorB * FToRGB;
	newEffectShaderData->RimColor.a = 0.0F * FToRGB;

	return newEffectShaderData;
}

void SetupGeometryWithEffectShader(BSGeometry* geometryToSetup, TESEffectShader* shaderToUse, BSEffectShaderData& returnData) {
	BSShaderProperty* shaderProperty;
	BSEffectShaderProperty* effectShaderProperty;
	BSEffectShaderMaterial* effectShaderMaterial;
	shaderProperty = (BSShaderProperty*)geometryToSetup->shaderProperty.get();
	effectShaderProperty = (BSEffectShaderProperty*)shaderProperty;
	if (shaderProperty) {
		logInfo("Got the EffectShaderProperty");
		effectShaderMaterial = static_cast<BSEffectShaderMaterial*>(shaderProperty->material);
		//effectShaderData = ThermalFXS->CreateEffectShaderData(ScopeTextureLoader, effectShaderMaterial->spBaseTexture.get(), effectShaderMaterial->spBaseTexture.get(), effectShaderMaterial->spBaseTexture.get());
		returnData = *CreateEffectShaderDataCustom(shaderToUse, effectShaderMaterial->spBaseTexture.get(), effectShaderMaterial->spBaseTexture.get(), effectShaderMaterial->spBaseTexture.get());
		effectShaderProperty->SetEffectShaderData(&returnData);
		if (effectShaderProperty->SetupGeometry(geometryToSetup)) {
			logInfo("Geometry was setup with the shaders.");
		} else {
			logInfo("Geometry was unable to be setup.");
		}
		logInfo("Scope materials setup complete.");
	}
}

void SetupImageSpaceShader(BSGeometry* objGeom, bool active) {
	ImageSpaceShaderParam* defaultParams = &BSImagespaceShader::GetDefaultParam();
	ImageSpaceManager* pImageSpaceManager = ImageSpaceManager::GetSingleton();

	BSImagespaceShader* BSImageShader = (BSImagespaceShader*)pImageSpaceManager->GetEffect(ImageSpaceManager::kBSHUDGlassCopy);
	BSShaderProperty* shaderProperty;
	BSEffectShaderProperty* effectShaderProperty;
	BSEffectShaderMaterial* effectShaderMaterial;
	shaderProperty = (BSShaderProperty*)objGeom->shaderProperty.get();
	effectShaderProperty = (BSEffectShaderProperty*)shaderProperty;
	if (shaderProperty) {
		effectShaderMaterial = static_cast<BSEffectShaderMaterial*>(shaderProperty->material);
		BSImageShader->Render((BSTriShape*)objGeom, defaultParams);
		logInfo("Scope materials setup complete.");
	}
}
