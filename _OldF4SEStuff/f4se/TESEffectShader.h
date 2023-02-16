#pragma once
#include "f4se_common/Utilities.h"
#include "f4se/GameFormComponents.h"
#include "f4se/GameForms.h"
#include "f4se/BSGeometry.h"
#include "f4se/NiObjects.h"
#include "f4se/NiTextures.h"
#include "f4se/NiMaterials.h"

enum class _D3DBLEND;    // NOLINT(bugprone-reserved-identifier)
enum class _D3DBLENDOP;  // NOLINT(bugprone-reserved-identifier)
enum class _D3DCMPFUNC;  // NOLINT(bugprone-reserved-identifier)

struct EffectShaderData {
public:
	// members
	_D3DBLEND textureBlendModeSource;									// 00
	_D3DBLENDOP textureBlendOperation;									// 04
	_D3DCMPFUNC textureZTestFunction;									// 08
	UInt32 fillColor1;													// 0C
	float fillAlphaFadeInTime;                                          // 10
	float fillAlphaFullTime;                                            // 14
	float fillAlphaFadeOutTime;                                         // 18
	float fillAlphaPersistentPercent;                                   // 1C
	float fillAlphaPulseAmplitude;                                      // 20
	float fillAlphaPulseFrequency;                                      // 24
	float fillTextureUAnimSpeed;                                        // 28
	float fillTextureVAnimSpeed;                                        // 2C
	float edgeExponentValue;                                            // 30
	UInt32 edgeColor;													// 34
	float edgeAlphaFadeInTime;                                          // 38
	float edgeAlphaFullTime;                                            // 3C
	float edgeAlphaFadeOutTime;                                         // 40
	float edgeAlphaPersistentPercent;                                   // 44
	float edgeAlphaPulseAmplitude;                                      // 48
	float edgeAlphaPulseFrequency;                                      // 4C
	float fillAlphaFullPercent;                                         // 50
	float edgeAlphaFullPercent;                                         // 54
	_D3DBLEND textureBlendModeDest;										// 58
	float alphaTestStartTime;                                           // 5C
	float alphaTestEndTime;                                             // 60
	float alphaTestStartValue;                                          // 64
	float alphaTestEndValue;                                            // 68
	BGSSoundDescriptorForm* ambientSound;                               // 70
	UInt32 fillColor2;													// 78
	UInt32 fillColor3;													// 7C
	float fillColorScaleA[3];                                           // 80
	float fillColorTimeA[3];                                            // 8C
	UInt32 flags;														// 98
	float fillTextureUScale;                                            // 9C
	float fillTextureVScale;                                            // A0
	SInt8 boneDepth;													// A4
};
STATIC_ASSERT(sizeof(EffectShaderData) == 0xA8);

class TESEffectShader : public TESForm, public TESModel {
public:

	// members
	EffectShaderData data;                    // 050
	TESTexture textureShaderTexture;          // 0F8
	TESTexture blockOutTexture;               // 108
	TESTexture paletteTexture;                // 118
	NiPointer<BSGeometry> shareableGeometry;  // 128

	MEMBER_FN_PREFIX(TESEffectShader);

	DEFINE_MEMBER_FN(StartEffectShader, unsigned int, 0x00311AF0, TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData, bool a4);
	DEFINE_MEMBER_FN(StopEffectShader, void, 0x00311CC0, TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData);

	DEFINE_MEMBER_FN(CreateEffectShaderData, BSEffectShaderData*, 0x00311570, NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex);
	DEFINE_MEMBER_FN(ResetEffectShaderData, void, 0x003116D0, BSEffectShaderData* effectShaderData, NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex);

	unsigned int StartEffectShader(TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData, bool a4);
	void StopEffectShader(TESEffectShader* shader, NiAVObject* object, BSEffectShaderData* shaderData);

	BSEffectShaderData* CreateEffectShaderData(NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex);
	void ResetEffectShaderData(BSEffectShaderData* shadeData, NiAVObject* object, NiTexture* baseTex, NiTexture* blockoutTex, NiTexture* specialTex);
};
STATIC_ASSERT(sizeof(TESEffectShader) == 0x130);