#include "Global.h"

void SetupImageSpaceShader(BSGeometry* objGeom, bool active) {
	BSImagespaceShader* BSImageShader = (BSImagespaceShader*)(*ImageSpaceManager_pInstance)->GetEffect(ImageSpaceManager::ImageSpaceEffectEnum::kBSHUDGlassCopy);
	NiPointer<BSShaderProperty> shaderProperty;
	BSEffectShaderProperty* effectShaderProperty;
	BSEffectShaderMaterial* effectShaderMaterial;
	shaderProperty = ni_cast(objGeom->shaderProperty, BSShaderProperty);
	effectShaderProperty = ni_cast(shaderProperty, BSEffectShaderProperty);
	if (shaderProperty.get()) {
		effectShaderMaterial = static_cast<BSEffectShaderMaterial*>(shaderProperty->shaderMaterial);
		BSImageShader->Render((BSTriShape*)objGeom, BSImagespaceShader_DefaultParam);
		logIfNeeded("Scope materials setup complete.");
	}
}

void SetupTextureLoaderWithEffectShader() {
	NiPointer<BSShaderProperty> shaderProperty;
	BSEffectShaderProperty* effectShaderProperty;
	BSEffectShaderMaterial* effectShaderMaterial;
	shaderProperty = ni_cast(ScopeTextureLoader->shaderProperty, BSShaderProperty);
	effectShaderProperty = ni_cast(shaderProperty, BSEffectShaderProperty);
	if (shaderProperty.get()) {
		logIfNeeded("Got the EffectShaderProperty");
		effectShaderMaterial = static_cast<BSEffectShaderMaterial*>(shaderProperty->shaderMaterial);
		//effectShaderData = ThermalFXS->CreateEffectShaderData(ScopeTextureLoader, effectShaderMaterial->spBaseTexture.get(), effectShaderMaterial->spBaseTexture.get(), effectShaderMaterial->spBaseTexture.get());
		effectShaderData = CreateEffectShaderDataCustom(ThermalFXS, effectShaderMaterial->spBaseTexture.get(), effectShaderMaterial->spBaseTexture.get(), effectShaderMaterial->spBaseTexture.get());
		effectShaderProperty->SetEffectShaderData(effectShaderData);
		if (effectShaderProperty->SetupGeometry(ScopeTextureLoader)) {
			logIfNeeded("Geometry was setup with the shaders.");
		} else {
			logIfNeeded("Geometry was unable to be setup.");
		}
		logIfNeeded("Scope materials setup complete.");
	}
}

//TESEffectShader::CreateEffectShaderData but without the reset part breaking it
BSEffectShaderData* CreateEffectShaderDataCustom(TESEffectShader* shader, NiTexture* tex1, NiTexture* tex2, NiTexture* tex3) {
	BSEffectShaderData* newEffectShaderData = (BSEffectShaderData*)Heap_Allocate(0x88);
	if (newEffectShaderData) {
		newEffectShaderData->m_refCount = 0;
		newEffectShaderData->pNodeFilterFunction = 0i64;
		newEffectShaderData->spBaseTexture.m_pObject = nullptr;
		newEffectShaderData->spPaletteTexture.m_pObject = nullptr;
		newEffectShaderData->spBlockOutTexture.m_pObject = nullptr;
		newEffectShaderData->eTextureClampMode = 3;
		newEffectShaderData->FillColor.g = 0.0;
		newEffectShaderData->FillColor.a = 0.0;
		newEffectShaderData->RimColor.g = 0.0;
		newEffectShaderData->RimColor.a = 0.0;
		newEffectShaderData->fBaseFillScale = 1.0;
		newEffectShaderData->fBaseFillAlpha = 1.0;
		newEffectShaderData->fBaseRimAlpha = 1.0;
		newEffectShaderData->fVOffset = 0.0;
		newEffectShaderData->fUScale = 1.0;
		newEffectShaderData->fVScale = 1.0;
		newEffectShaderData->fEdgeExponent = 1.0;
		newEffectShaderData->eSrcBlend = NiAlphaProperty::AlphaFunction::kAlpha_SrcAlpha;
		newEffectShaderData->eDestBlend = NiAlphaProperty::AlphaFunction::kAlpha_InvSrcAlpha;
		newEffectShaderData->eZTestFunc = 1;
		newEffectShaderData->bBaseTextureProjectedUVs = 0;
	} else {
		newEffectShaderData = nullptr;
	}
	InterlockedIncrement(&newEffectShaderData->m_refCount);

	NiPointer<NiTexture> textureShaderTexture;
	NiPointer<NiTexture> blockOutTexture;
	NiPointer<NiTexture> paletteTexture;

	gShaderManagerInstance->GetTexture(shader->textureShaderTexture.str.c_str(), false, textureShaderTexture, true, true, true);
	gShaderManagerInstance->GetTexture(shader->blockOutTexture.str.c_str(), false, blockOutTexture, true, true, true);
	gShaderManagerInstance->GetTexture(shader->paletteTexture.str.c_str(), false, paletteTexture, true, true, true);

	newEffectShaderData->spBaseTexture = textureShaderTexture;
	newEffectShaderData->spBlockOutTexture = blockOutTexture;
	newEffectShaderData->spPaletteTexture = paletteTexture;


	newEffectShaderData->FillColor.r = (float)BYTE0(shader->data.fillColor1) * FToRGB;
	newEffectShaderData->FillColor.g = (float)BYTE1(shader->data.fillColor1) * FToRGB;
	newEffectShaderData->FillColor.b = (float)BYTE2(shader->data.fillColor1) * FToRGB;
	newEffectShaderData->FillColor.a = 0.0 * FToRGB;

	float rimColorR = BYTE0(shader->data.edgeColor);
	float rimColorG = BYTE1(shader->data.edgeColor);
	float rimColorB = BYTE2(shader->data.edgeColor);

	newEffectShaderData->RimColor.r = (float)rimColorR * FToRGB;
	newEffectShaderData->RimColor.g = (float)rimColorG * FToRGB;
	newEffectShaderData->RimColor.b = (float)rimColorB * FToRGB;
	newEffectShaderData->RimColor.a = 0.0 * FToRGB;

	float fillAlpha;
	if (shader->data.fillAlphaFadeInTime == 0.0 && shader->data.fillAlphaFullTime == 0.0) {
		fillAlpha = shader->data.fillAlphaFullPercent;
	} else {
		fillAlpha = 0.0;
	}
	newEffectShaderData->fBaseFillAlpha = fillAlpha;
	float edgeAlpha;
	if (shader->data.edgeAlphaFadeInTime == 0.0 && shader->data.edgeAlphaFullTime == 0.0) {
		edgeAlpha = shader->data.edgeAlphaFullPercent;
	}
	newEffectShaderData->fBaseRimAlpha = edgeAlpha;
	newEffectShaderData->fUOffset = 0;
	newEffectShaderData->fUScale = shader->data.fillTextureUScale;
	newEffectShaderData->fVScale = shader->data.fillTextureVScale;
	newEffectShaderData->fEdgeExponent = shader->data.edgeExponentValue;

	newEffectShaderData->eSrcBlend = NiAlphaProperty::AlphaFunction::kAlpha_SrcAlpha;
	newEffectShaderData->eDestBlend = NiAlphaProperty::AlphaFunction::kAlpha_InvSrcAlpha;
	newEffectShaderData->eZTestFunc = 1;
	newEffectShaderData->ucAlphaTestRef = shader->data.alphaTestStartValue;
	newEffectShaderData->bGrayscaleToColor = (shader->data.flags & 2) != 0;
	newEffectShaderData->bGrayscaleToAlpha = (shader->data.flags & 4) != 0;
	newEffectShaderData->bIgnoreTextureAlpha = (shader->data.flags & 64) != 0;
	newEffectShaderData->bBaseTextureProjectedUVs = (shader->data.flags & 128) != 0;
	newEffectShaderData->bIgnoreBaseGeomTexAlpha = BYTE1(shader->data.flags) & 1;
	newEffectShaderData->bLighting = (shader->data.flags & 512) != 0;
	newEffectShaderData->bAlpha = (shader->data.flags & 2048) != 0;

	if ((shader->data.flags & 16) != 0) {
		rimColorG = rimColorG - 255.0;
		rimColorB = rimColorB - 255.0;
		newEffectShaderData->RimColor.r = (float)(rimColorR - 255.0) * FToRGB;
	} else {
		newEffectShaderData->RimColor.r = rimColorR * FToRGB;
	}
	newEffectShaderData->RimColor.g = rimColorG * FToRGB;
	newEffectShaderData->RimColor.b = rimColorB * FToRGB;
	newEffectShaderData->RimColor.a = 0.0 * FToRGB;

	if (effectShaderData == newEffectShaderData) {
		newEffectShaderData->~BSEffectShaderData();
		logIfNeeded("The BSEffectShaderData has already been made. We can delete the one just now created");
		return effectShaderData;

	} else {
		return newEffectShaderData;
	}
}