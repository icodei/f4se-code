#pragma once
#include "f4se/BSGeometry.h"
#include "f4se/ImageSpace.h"
#include "f4se/NiTextures.h"
#include "f4se/NiTypes.h"
#include "f4se_common/Utilities.h"

class ImageSpaceBaseData;
class ImageSpaceEffectParam;
class ImageSpaceLUTData;
class ImageSpaceEffect;

class ImageSpaceManager {
public:

	enum ImageSpaceEffectEnum {
		kRefraction = 5,
		kGetHit = 11,
		kVatsTarget = 12,
		kFullScreenColor = 13,

		kMap = 22,

		kNoise = 62,
		kRainSplash = 63,

		kPipboyScreen = 66,
		kHUDGlass = 67,
		kModMenu = 68,

		kBSCopy = 72,
		kBSCopyScaleBias = 73,
		kBSCopyVisAlpha = 74,
		kBSGreyScale = 75,
		kBSDownsampleDepth = 76,
		kBSCopyStencil = 77,
		kBSCopyWaterMask = 78,

		kBSRefraction = 80,
		kBSDoubleVision = 81,
		kBSTextureMask = 82,
		kBSMap = 83,

		kBSDepthOfFieldFogged = 87,
		kBSDepthOfFieldSplitScreen = 88,

		kBSNoiseScrollAndBlend = 150,
		kBSNoiseNormalmap = 151,
		kBSLocalMap = 152,
		kBSLocalMapCompanion = 153,
		kBSAlphaBlend = 154,
		kBSPipboyScreen = 155,
		kBSHUDGlass = 156,
		kBSHUDGlassDropShadow = 157,
		kBSHUDGlassBlurY = 158,
		kBSHUDGlassBlurX = 159,
		kBSHUDGlassMarkers = 160,
		kBSVatsTargetDebug = 161,
		kBSVatsTarget = 162,
		kBSModMenuEffect = 163,
		kBSModMenuGlowComposite = 164,
		kBSAmbientOcclusion = 165,
		kBSAmbientOcclusionBlur = 166,
		kBSVLSSpotLight = 167,
		kBSVLSApplication = 168,
		kBSVLSComposite = 169,
		kBSVLSSliceCoord = 170,
		kBSVLSSliceInterp = 171,
		kBSVLSSliceStencil = 172,

		kBSTemporalAAPipboy = 191,
		kBSTemporalAAPowerArmorPipboy = 192,

		kBSRainSplash = 200,
		kBSRainSplashUpdate = 201,
		kBSRainSplashDraw = 202,

		kBSFullScreenColor = 205,

		kBSHUDGlassCopy = 207,
	};

	UInt64 field_0;
	UInt64 field_8;
	NiTArray<ImageSpaceEffect> effectArray;
	NiPointer<BSTriShape> ScreenTriShape;
	BSTriShape* ScreenTriShapeColors;
	NiPointer<BSTriShape> DynamicScreenTriShape;
	NiPointer<BSTriShape> PartialScreenTriShape;
	bool field_48;
	UInt32 field_4C;
	UInt64 field_50;
	UInt32 field_58;
	UInt32 field_5C;
	ImageSpaceBaseData* CurrentBaseData;
	ImageSpaceBaseData* OverrideBaseData;
	ImageSpaceBaseData* UnderwaterBaseData;
	ImageSpaceBaseData* ConsoleBaseData;
	ImageSpaceBaseData field_80;
	UInt8 gapD8[88];
	ImageSpaceLUTData field_130;
	UInt8 gap188[24];
	ImageSpaceLUTData* imageSpaceLUT;
	UInt8 gap1A8[8];
	UInt32 field_1B0;
	UInt8 field_1B4;
	UInt8 field_1B5;
	UInt8 field_1B6;

	MEMBER_FN_PREFIX(ImageSpaceManager);

	DEFINE_MEMBER_FN(GetEffect, ImageSpaceEffect*, 0x001E0660, ImageSpaceEffectEnum);

	DEFINE_MEMBER_FN(RenderEffect_1, void, 0x027DA130, ImageSpaceEffectEnum, SInt32, ImageSpaceEffectParam*);
	DEFINE_MEMBER_FN(RenderEffect_2, void, 0x027DA240, ImageSpaceEffect*, SInt32, SInt32, ImageSpaceEffectParam*);
	DEFINE_MEMBER_FN(RenderEffect_3, void, 0x027DA3B0, ImageSpaceEffect*, SInt32, SInt32, SInt32, ImageSpaceEffectParam*);

	DEFINE_MEMBER_FN(RenderEffectHelper_2, void, 0x027DA0D0, ImageSpaceEffectEnum, SInt32, SInt32, ImageSpaceEffectParam*);

	DEFINE_MEMBER_FN(RenderEffect_Tex_1, void, 0x027DA780, ImageSpaceEffect*, NiTexture*, SInt32, ImageSpaceEffectParam*);
	DEFINE_MEMBER_FN(RenderEffect_Tex_2, void, 0x027DA5C0, ImageSpaceEffectEnum, NiTexture*, NiTexture*, SInt32, ImageSpaceEffectParam*);

	DEFINE_MEMBER_FN(RenderEffectHelper_Tex_1, void, 0x027DA560, ImageSpaceEffectEnum, NiTexture*, SInt32, ImageSpaceEffectParam*);

	DEFINE_MEMBER_FN(SelectScreenShape, NiPointer<BSTriShape>&, 0x027E14E0, ImageSpaceEffect*);

	ImageSpaceEffect* GetEffect(ImageSpaceEffectEnum);

	void RenderEffect_1(ImageSpaceEffectEnum, SInt32, ImageSpaceEffectParam*);
	void RenderEffect_2(ImageSpaceEffect*, SInt32, SInt32, ImageSpaceEffectParam*);
	void RenderEffect_3(ImageSpaceEffect*, SInt32, SInt32, SInt32, ImageSpaceEffectParam*);

	void RenderEffectHelper_2(ImageSpaceEffectEnum, SInt32, SInt32, ImageSpaceEffectParam*);

	void RenderEffect_Tex_1(ImageSpaceEffect*, NiTexture*, SInt32, ImageSpaceEffectParam*);
	void RenderEffect_Tex_2(ImageSpaceEffectEnum, NiTexture*, NiTexture*, SInt32, ImageSpaceEffectParam*);

	void RenderEffectHelper_Tex_1(ImageSpaceEffectEnum, NiTexture*, SInt32, ImageSpaceEffectParam*);

	NiPointer<BSTriShape>& SelectScreenShape(ImageSpaceEffect*);
};

extern RelocPtr <ImageSpaceManager*>	ImageSpaceManager_pInstance;