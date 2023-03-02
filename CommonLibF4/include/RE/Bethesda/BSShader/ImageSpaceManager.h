#pragma once
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTArray.h"

namespace RE
{
	class BSTriShape;
	class BSReadWriteLock;
	class ImageSpaceBaseData;
	class ImageSpaceEffect;
	class ImageSpaceEffectParam;
	class ImageSpaceLUTData;
	class NiTexture;

	class ImageSpaceManager
	{
	public:
		enum ImageSpaceEffectEnum
		{
			kRefraction = 5,

			kGetHit = 11,
			kVatsTarget,
			kFullScreenColor = 13,

			kMap = 22,

			kNoise = 62,
			kRainSplash = 63,

			kPipboyScreen = 66,
			kHUDGlass,
			kModMenu = 68,

			kBSCopy = 72,
			kBSCopyScaleBias,
			kBSCopyVisAlpha,
			kBSGreyScale,
			kBSDownsampleDepth,
			kBSCopyStencil,
			kBSCopyWaterMask = 78,

			kBSRefraction = 80,
			kBSDoubleVision,
			kBSTextureMask,
			kBSMap = 83,

			kBSDepthOfFieldFogged = 87,
			kBSDepthOfFieldSplitScreen = 88,

			kBSNoiseScrollAndBlend = 150,
			kBSNoiseNormalmap,
			kBSLocalMap,
			kBSLocalMapCompanion,
			kBSAlphaBlend,
			kBSPipboyScreen,
			kBSHUDGlass,
			kBSHUDGlassDropShadow,
			kBSHUDGlassBlurY,
			kBSHUDGlassBlurX,
			kBSHUDGlassMarkers,
			kBSVatsTargetDebug,
			kBSVatsTarget,
			kBSModMenuEffect,
			kBSModMenuGlowComposite,
			kBSAmbientOcclusion,
			kBSAmbientOcclusionBlur,
			kBSVLSSpotLight,
			kBSVLSApplication,
			kBSVLSComposite,
			kBSVLSSliceCoord,
			kBSVLSSliceInterp,
			kBSVLSSliceStencil = 172,

			kBSTemporalAAPipboy = 191,
			kBSTemporalAAPowerArmorPipboy = 192,

			kBSRainSplash = 200,
			kBSRainSplashUpdate,
			kBSRainSplashDraw = 202,

			kBSFullScreenColor = 205,

			kBSHUDGlassCopy = 207,
		};

		ImageSpaceEffect* GetEffect(ImageSpaceEffectEnum a_effect)
		{
			using func_t = decltype(&ImageSpaceManager::GetEffect);
			REL::Relocation<func_t> func{ REL::ID(697019), 0x30 };
			return func(this, a_effect);
		}

		void RenderEffect_1(ImageSpaceEffectEnum a_effect, std::uint32_t a_target, ImageSpaceEffectParam* a_param)
		{
			using func_t = decltype(&ImageSpaceManager::RenderEffect_1);
			REL::Relocation<func_t> func{ REL::ID(778043) };
			return func(this, a_effect, a_target, a_param);
		}

		void RenderEffect_2(ImageSpaceEffect* a_effect, std::uint32_t a_target1, std::uint32_t a_target2, ImageSpaceEffectParam* a_param)
		{
			using func_t = decltype(&ImageSpaceManager::RenderEffect_2);
			REL::Relocation<func_t> func{ REL::ID(325252) };
			return func(this, a_effect, a_target1, a_target2, a_param);
		}

		void RenderEffect_3(ImageSpaceEffect* a_effect, std::uint32_t a_target1, std::uint32_t a_target2, std::uint32_t a_target3, ImageSpaceEffectParam* a_param)
		{
			using func_t = decltype(&ImageSpaceManager::RenderEffect_3);
			REL::Relocation<func_t> func{ REL::ID(922938) };
			return func(this, a_effect, a_target1, a_target2, a_target3, a_param);
		}

		void RenderEffectHelper_2(ImageSpaceEffectEnum a_effect, std::uint32_t a_target1, std::uint32_t a_target2, ImageSpaceEffectParam* a_param)
		{
			using func_t = decltype(&ImageSpaceManager::RenderEffectHelper_2);
			REL::Relocation<func_t> func{ REL::ID(1309722) };
			return func(this, a_effect, a_target1, a_target2, a_param);
		}

		void RenderEffect_Tex_1(ImageSpaceEffect* a_effect, NiTexture* a_texture, std::uint32_t a_target, ImageSpaceEffectParam* a_param)
		{
			using func_t = decltype(&ImageSpaceManager::RenderEffect_Tex_1);
			REL::Relocation<func_t> func{ REL::ID(788799) };
			return func(this, a_effect, a_texture, a_target, a_param);
		}

		void RenderEffect_Tex_2(ImageSpaceEffectEnum a_effect, NiTexture* a_texture1, NiTexture* a_texture2, std::uint32_t a_target, ImageSpaceEffectParam* a_param)
		{
			using func_t = decltype(&ImageSpaceManager::RenderEffect_Tex_2);
			REL::Relocation<func_t> func{ REL::ID(1161595) };
			return func(this, a_effect, a_texture1, a_texture2, a_target, a_param);
		}

		void RenderEffectHelper_Tex_1(ImageSpaceEffectEnum a_effect, NiTexture* a_texture, std::uint32_t a_target, ImageSpaceEffectParam* a_param)
		{
			using func_t = decltype(&ImageSpaceManager::RenderEffectHelper_Tex_1);
			REL::Relocation<func_t> func{ REL::ID(111275) };
			return func(this, a_effect, a_texture, a_target, a_param);
		}

		NiPointer<BSTriShape>& SelectScreenShape(ImageSpaceEffect* a_effect)
		{
			using func_t = decltype(&ImageSpaceManager::SelectScreenShape);
			REL::Relocation<func_t> func{ REL::ID(522068), -0xB };
			return func(this, a_effect);
		}

		//members
		std::uint64_t field_0;                            // 000
		std::uint64_t field_8;                            // 008
		NiTPrimitiveArray<ImageSpaceEffect> effectArray;  // 010 - allocates 0x740 on ctor
		NiPointer<BSTriShape> ScreenTriShape;             // 028
		BSTriShape* ScreenTriShapeColors;                 // 030
		NiPointer<BSTriShape> DynamicScreenTriShape;      // 038
		NiPointer<BSTriShape> PartialScreenTriShape;      // 040
		bool isPartialScreen;                             // 048
		std::uint32_t field_4C;                           // 04C
		NiColorA refractionTint;                          // 050
		ImageSpaceBaseData* CurrentBaseData;              // 060
		ImageSpaceBaseData* OverrideBaseData;             // 068
		ImageSpaceBaseData* UnderwaterBaseData;           // 070
		ImageSpaceBaseData* ConsoleBaseData;              // 078
		ImageSpaceBaseData field_80;                      // 080
		std::uint8_t gapD8[88];                           // 0D8
		ImageSpaceLUTData field_130;                      // 130
		std::uint8_t gap188[24];                          // 188
		ImageSpaceLUTData* imageSpaceLUT;                 // 1A0
		float motionBlurMin;                              // 1A8
		float motionBlurMax;                              // 1AC
		std::uint32_t field_1B0;                          // 1B0
		std::uint8_t field_1B4;                           // 1B4
		std::uint8_t field_1B5;                           // 1B5
		std::uint8_t field_1B6;                           // 1B6
	};
	static_assert(sizeof(ImageSpaceManager) == 0x1B8);

	REL::Relocation<ImageSpaceManager*> ImageSpaceManager__pInstance{ REL::ID(161743) };
	REL::Relocation<int> ImageSpaceManager__iActiveEffectsCount{ REL::ID(1524657) };
	REL::Relocation<ImageSpaceBaseData> ImageSpaceManager__kInitBaseData{ REL::ID(380891) };
	REL::Relocation<BSReadWriteLock> ImageSpaceManager__kBaseDataLock{ REL::ID(1212084) };
	REL::Relocation<ImageSpaceManager::ImageSpaceEffectEnum> ImageSpaceManager__iLastEffect{ REL::ID(646887) };
	REL::Relocation<int> ImageSpaceManager__iSwapTarget{ REL::ID(1547604) };
	REL::Relocation<int> ImageSpaceManager__iSaveTarget{ REL::ID(865881) };
}
