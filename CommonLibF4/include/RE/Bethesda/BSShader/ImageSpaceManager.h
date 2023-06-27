#pragma once
#include "RE/NetImmerse/NiMain/NiColor.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"
#include "RE/NetImmerse/NiMain/NiTArray.h"
#include "RE/Bethesda/BSShader/ImageSpace.h"

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

		static ImageSpaceManager* GetSingleton()
		{
			REL::Relocation<ImageSpaceManager**> singleton{ REL::ID(161743) };
			return *singleton;
		}

		enum ImageSpaceEffectEnum
		{
			kNONE = -1,
			kUNK0 = 0,
			kUNK1,
			kSunbeams,
			kHDR,
			kHDRCS,
			kRefraction,
			kDOF,
			kDOFSplitScreen,
			kRadialBlur,
			kFullScreenBlur,
			kMotionBlur,
			kGetHit,
			kVatsTarget,
			kFullScreenColor,
			kBSGammaCorrect,
			kBSGammaCorrectLUT,
			kBSGammaCorrectResize,
			kBSFXAA,
			kTemporalAA,
			kUNK19,
			kBokehDOF,
			kUpsampleDynamicResolution,
			kMap,

			kBlurStart = 23,
			
			kBlurEnd = 60,

			kWaterDisplacement,
			kNoise,
			kRainSplash,
			kVLSLight,
			kVLS,
			kPipboyScreen,
			kHUDGlass,
			kModMenu,
			kAO,
			kScalableAO,
			kScalableAOCS,
			kBSCopy,
			kBSCopyScaleBias,
			kBSCopyVisAlpha,
			kBSGreyScale,
			kBSDownsampleDepth,
			kBSCopyStencil,
			kBSCopyWaterMask,
			kBSCopyShadowMapToArray,
			kBSRefraction,
			kBSDoubleVision,
			kBSTextureMask,
			kBSMap,
			kUNK84,
			kUNK85,
			kBSDOF,
			kBSDOFFogged,
			kBSDOFSplitScreen,
			kBSBokehDOFPass1,
			kBSBokehDOFPass2,
			kBSBokehDOFPass3,
			kBSBokehDOFPass4,
			kBSBokehDOFPass4Fogged,
			kBSDistantBlurFogged = 94,
			kUNK95,
			kBSRadialBlur,
			kBSRadialBlurMedium,
			kBSRadialBlurHigh,
			kBSHDRTonemapBlendCinematic,
			kBSHDRTonemapBlendCinematicFade,
			kBSHDRDownSample16,
			kBSHDRDownSample4,
			kBSHDRDownSample16Lum,
			kBSHDRDownSample4RGB2Lum,
			kBSHDRDownSample4LumClamp,
			kBSHDRDownSample4LightAdapt,
			kBSHDRDownSample16LumClamp,
			kBSHDRDownSample16LightAdapt,
			kBSHDRDownSample4CS,
			kBSHDRDownSample64RGB2LumCS,
			kBSHDRDownSample4LumCS,
			kBSHDRDownSample16LumCS,
			kBSHDRDownSample2LightAdaptCS,
			kBSBlur3,
			kBSBlur5,
			kBSBlur7,
			kBSBlur9,
			kBSBlur11,
			kBSBlur13,
			kBSBlur15,

			kBSHDRBlurX15_320CS = 121,
			kBSHDRBlurX15_480CS,
			kBSHDRBlurX15_1024CS,
			kBSNonHDRBlur3,
			kBSNonHDRBlur5,
			kBSNonHDRBlur7,
			kBSNonHDRBlur9,
			kBSNonHDRBlur11,
			kBSNonHDRBlur13,
			kBSNonHDRBlur15,
			kBSBrightPassBlur3,
			kBSBrightPassBlur5,
			kBSBrightPassBlur7,
			kBSBrightPassBlur9,
			kBSBrightPassBlur11,
			kBSBrightPassBlur13,
			kBSBrightPassBlur15,
			kBSBrightPassHDRBlurY15_180CS,
			kBSBrightPassHDRBlurY15_270CS,
			kBSBrightPassHDRBlurY15_1024CS,
			kBSWaterDisplacementClearSimulation,
			kBSWaterDisplacementTexOffset,
			kBSWaterDisplacementWadingRipple,
			kBSWaterDisplacementRainRipple,
			kBSWaterWadingHeightmap,
			kBSWaterRainHeightmap,
			kBSWaterBlendHeightmaps,
			kBSWaterSmoothHeightmap,
			kBSWaterDisplacementNormals,
			kBSNoiseScrollAndBlend,
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
			kBSVLSSliceStencil,
			kBSVLSSliceScatterRay,
			kBSVLSSliceScatterInterp,
			kBSVLSScatterAccum,
			kBSSAOCameraZ,
			kBSSAOMinify,
			kBSSAORawAO,
			kBSSAOBlurH,
			kBSSAOBlurV,
			kBSSAORawAOEditor,
			kBSSAOCameraZCS,
			kBSSAOMinifyCS,
			kBSSAOCameraAndMipsZCS,
			kBSSAOMipsZCS,
			kBSSAORawAOCS,
			kBSSAOBlurHCS,
			kBSSAOBlurVCS,
			kBSMotionBlur,
			kBSTemporalAA,
			kBSTemporalAAPipboy,
			kBSTemporalAAPowerArmorPipboy,
			kBSGammaLinearize,
			kBSSunbeams,
			kBSSSLRPrepass,
			kBSSSLRRaytracing,
			kBSSSLRBlurH,
			kBSSSLRBlurV,
			kBSLensFlare,
			kBSRainSplash,
			kBSRainSplashUpdate,
			kBSRainSplashDraw,
			kBSLensFlareVisibility,
			kBSUpsampleDynamicResolution,
			kBSFullScreenColor,
			kBSHUDGlassClear,
			kBSHUDGlassCopy,
			kBSBlurY3_270CS,
			kBSBlurY5_270CS,
			kBSBlurY7_270CS,
			kBSBlurY9_270CS,
			kBSBlurY11_270CS,
			kBSBlurY13_270CS,
			kBSBlurY15_270CS,
			kUNK215,
			kBSBlurX3_480CS,
			kBSBlurX5_480CS,
			kBSBlurX7_480CS,
			kBSBlurX9_480CS,
			kBSBlurX11_480CS = 220,
			kBSBlurX13_480CS,
			kBSBlurX15_480CS,
			kUNK223,
			kBSBrightPassBlurY3_270CS,
			kBSBrightPassBlurY5_270CS,
			kBSBrightPassBlurY7_270CS,
			kBSBrightPassBlurY9_270CS,
			kBSBrightPassBlurY11_270CS,
			kBSBrightPassBlurY13_270CS,
			kBSBrightPassBlurY15_270CS = 230,
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

		BSTriShape* CreatePartialScreenGeometry(std::uint32_t width, std::uint32_t height)
		{
			using func_t = decltype(&ImageSpaceManager::CreatePartialScreenGeometry);
			REL::Relocation<func_t> func{ REL::ID(1103472) };
			return func(this, width, height);
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
}
