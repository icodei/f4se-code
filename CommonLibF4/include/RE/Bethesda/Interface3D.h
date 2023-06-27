#pragma once

#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/UIShaderFXInfo.h"
#include "RE/NetImmerse/NiMain/NiColor.h"
#include "RE/NetImmerse/NiMain/NiPoint2.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	enum class UI_DEPTH_PRIORITY;

	class BSGeometry;
	class BSShaderAccumulator;
	class NiAVObject;
	class NiCamera;
	class NiDirectionalLight;
	class ShadowSceneNode;

	namespace Interface3D
	{
		enum class BackgroundMode
		{
			kLive,
			kStatic,
			kSolidColor
		};

		enum class PostEffect
		{
			kNone,
			kPipboy,
			kHUDGlass,
			kHUDGlassWithMod,
			kModMenu,
			kModMenuHighlightAll,
			kModMenuHighlightAllNoPulseOrScanLines
		};

		enum class HighlightEffect
		{
			kNone,
			kVATS
		};

		enum class OffscreenMenuSize
		{
			kPipboy,
			kFullFrame,
			kFullFrameText
		};

		enum class ScreenMode
		{
			kNone,
			kWorldAttached,
			kScreenAttached
		};

		enum class OffscreenMenuBlendMode
		{
			kAdditive,
			kAlpha
		};

		enum class LightType
		{
			kSpot,
			kShadowSpot,
			kPoint
		};

		class OldScreenEffectControl
		{
		public:
			// members
			NiPoint2 uvOffset{ NiPoint2::ZERO };  // 00
			float burstAmount{ 0.0F };            // 08
			float brightness{ 1.0F };             // 0C
			float vScanState{ -1.0F };            // 10
			float vScanRate{ 2.0F };              // 14
			float pulseIntensity{ 0.5F };         // 18
			float pulseRate{ 0.5F };              // 1C
			float flickerMinDelay{ 5.0F };        // 20
			float flickerMaxDelay{ 15.0F };       // 24
			float flickerMinDuration{ 0.1F };     // 28
			float flickerMaxDuration{ 0.6F };     // 2C
			float flickerFrequency{ 22.0F };      // 30
			float flickerBrightness{ -0.1F };     // 34
			float vScanDelayMin{ 1.0F };          // 38
			float vScanDelayMax{ 5.0F };          // 3C
			bool doScanlines{ false };            // 40
			float burstState{ 0.0F };             // 44
			float burstFadeRate{ 0.0F };          // 48
			float shudderState{ -1.0F };          // 4C
			float vScanDelay{ 1.0F };             // 50
			float flickerDelay{ 1.0F };           // 54
			float vHoldState{ -1.0F };            // 58
			float shudderScale{ 0.0F };           // 5C
			float shudderLength{ 0.0F };          // 60
			float vHoldRate{ 0.0F };              // 64
			float time{ 0.0F };                   // 68
			bool flickering{ false };             // 6C
		};
		static_assert(sizeof(OldScreenEffectControl) == 0x70);

		class Renderer
		{
		public:
			struct LightParams
			{
			public:
				// members
				stl::enumeration<LightType, std::int32_t> type;  // 00
				float spotFOV;                                   // 04
				NiPoint3 lookAtPos;                              // 08
				NiPointer<NiAVObject> lookAtObject;              // 18
				NiPointer<NiLight> light;                        // 20
			};
			static_assert(sizeof(LightParams) == 0x28);

			[[nodiscard]] static Renderer* Create(const BSFixedString& a_name, UI_DEPTH_PRIORITY a_depth, float a_fov, bool a_alwaysrender)
			{
				using func_t = decltype(&Renderer::Create);
				REL::Relocation<func_t> func{ REL::ID(88488) };
				return func(a_name, a_depth, a_fov, a_alwaysrender);
			}

			[[nodiscard]] static Renderer* GetByName(const BSFixedString& a_name)
			{
				using func_t = decltype(&Renderer::GetByName);
				REL::Relocation<func_t> func{ REL::ID(140387) };
				return func(a_name);
			}

			void Enable(bool a_unhideGeometries = false)
			{
				using func_t = decltype(&Renderer::Enable);
				REL::Relocation<func_t> func{ REL::ID(326895) };
				return func(this, a_unhideGeometries);
			}

			void Disable()
			{
				using func_t = decltype(&Renderer::Disable);
				REL::Relocation<func_t> func{ REL::ID(938370) };
				return func(this);
			}

			void Release()
			{
				using func_t = decltype(&Renderer::Release);
				REL::Relocation<func_t> func{ REL::ID(74749) };
				return func(this);
			}

			void SetViewport(Scaleform::GFx::Movie& a_movie, NiRect<float> const& a_viewport)
			{
				using func_t = decltype(&Renderer::SetViewport);
				REL::Relocation<func_t> func{ REL::ID(825410) };
				return func(this, a_movie, a_viewport);
			}

			bool QRequiresDefferedOffscreen()
			{
				std::uint32_t fx;
				fx = postfx.underlying();
				return (fx - 4) <= 2 || fx == 3;
			}

			void MainScreen_AddPointLight(NiPoint3 a_position, NiColor a_diffuse, float a_specular, float a_dimmer)
			{
				using func_t = decltype(&Renderer::MainScreen_AddPointLight);
				REL::Relocation<func_t> func{ REL::ID(1335675) };
				return func(this, a_position, a_diffuse, a_specular, a_dimmer);
			}

			void MainScreen_AddSpotLight(NiPoint3 a_position, NiPoint3 a_target, NiAVObject* a_object, float a_FOV, NiColor a_diffuse, float a_specular, float a_dimmer, bool unk)
			{
				using func_t = decltype(&Renderer::MainScreen_AddSpotLight);
				REL::Relocation<func_t> func{ REL::ID(1056093) };
				return func(this, a_position, a_target, a_object, a_FOV, a_diffuse, a_specular, a_dimmer, unk);
			}

			void MainScreen_EnableScreenAttached3DMasking(char const* a_geometry, char const* a_material)
			{
				using func_t = decltype(&Renderer::MainScreen_EnableScreenAttached3DMasking);
				REL::Relocation<func_t> func{ REL::ID(1201550) };
				return func(this, a_geometry, a_material);
			}

			void MainScreen_RegisterGeometryRequiringFullViewport(NiAVObject* a_object)
			{
				using func_t = decltype(&Renderer::MainScreen_RegisterGeometryRequiringFullViewport);
				REL::Relocation<func_t> func{ REL::ID(897225) };
				return func(this, a_object);
			}

			void MainScreen_SetBackgroundMode(BackgroundMode a_mode)
			{
				using func_t = decltype(&Renderer::MainScreen_SetBackgroundMode);
				REL::Relocation<func_t> func{ REL::ID(378876) };
				return func(this, a_mode);
			}

			void MainScreen_SetScreenAttached3D(NiAVObject* a_object)
			{
				using func_t = decltype(&Renderer::MainScreen_SetScreenAttached3D);
				REL::Relocation<func_t> func{ REL::ID(817727) };
				return func(this, a_object);
			}

			void MainScreen_SetWorldAttached3D(NiAVObject* a_object)
			{
				using func_t = decltype(&Renderer::MainScreen_SetWorldAttached3D);
				REL::Relocation<func_t> func{ REL::ID(724778) };
				return func(this, a_object);
			}

			void Offscreen_AddLight(NiPoint3 a_position, NiColor a_diffuse, NiColor a_specular, float a_dimmer)
			{
				using func_t = decltype(&Renderer::Offscreen_AddLight);
				REL::Relocation<func_t> func{ REL::ID(1267198) };
				return func(this, a_position, a_diffuse, a_specular, a_dimmer);
			}

			void Offscreen_Clear3D()
			{
				using func_t = decltype(&Renderer::Offscreen_Clear3D);
				REL::Relocation<func_t> func{ REL::ID(1533262) };
				return func(this);
			}

			void Offscreen_ClearLights()
			{
				using func_t = decltype(&Renderer::Offscreen_ClearLights);
				REL::Relocation<func_t> func{ REL::ID(1039253) };
				return func(this);
			}

			void Offscreen_Enable3D(bool a_enable)
			{
				using func_t = decltype(&Renderer::Offscreen_Enable3D);
				REL::Relocation<func_t> func{ REL::ID(1107859), 0x10 };
				return func(this, a_enable);
			}

			OldScreenEffectControl& Offscreen_QPipboyEffectControl()
			{
				using func_t = decltype(&Renderer::Offscreen_QPipboyEffectControl);
				REL::Relocation<func_t> func{ REL::ID(852814) };
				return func(this);
			}

			void Offscreen_Set3D(NiAVObject* a_object)
			{
				using func_t = decltype(&Renderer::Offscreen_Set3D);
				REL::Relocation<func_t> func{ REL::ID(43983) };
				return func(this, a_object);
			}

			void Offscreen_SetDisplayMode(ScreenMode a_mode, char const* a_geometry, char const* a_material)
			{
				using func_t = decltype(&Renderer::Offscreen_SetDisplayMode);
				REL::Relocation<func_t> func{ REL::ID(576234) };
				return func(this, a_mode, a_geometry, a_material);
			}

			void Offscreen_SetPostEffect(PostEffect a_effect)
			{
				using func_t = decltype(&Renderer::Offscreen_SetPostEffect);
				REL::Relocation<func_t> func{ REL::ID(1187686) };
				return func(this, a_effect);
			}

			void Offscreen_SetRenderTargetSize(OffscreenMenuSize a_size)
			{
				using func_t = decltype(&Renderer::Offscreen_SetRenderTargetSize);
				REL::Relocation<func_t> func{ REL::ID(1547000) };
				return func(this, a_size);
			}

			void Oddscreen_SetUseLongRangeCamera(bool a_enable)
			{
				using func_t = decltype(&Renderer::Oddscreen_SetUseLongRangeCamera);
				REL::Relocation<func_t> func{ REL::ID(1544159), 0x30 };
				return func(this, a_enable);
			}

			void Offscreen_UseCustomRenderTarget(const std::int32_t& a_target, std::int32_t a_swapTarget)
			{
				using func_t = decltype(&Renderer::Offscreen_UseCustomRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(152177), 0x15 };
				return func(this, a_target, a_swapTarget);
			}

			// members
			BSTAlignedArray<UIShaderFXInfo> colorFXInfos;                      // 000
			BSTAlignedArray<UIShaderFXInfo> backgroundFXInfos;                 // 018
			BSReadWriteLock cachedQuadsLock;                                   // 030
			NiColorA clearColor{ NiColorA::BLACK };                            // 038
			float opacityAlpha{ 1.0F };                                        // 048
			bool enabled{ false };                                             // 04C
			bool offscreen3DEnabled{ true };                                   // 04D
			bool hideScreenWhenDisabled{ true };                               // 04E
			bool usePremultAlpha{ true };                                      // 04F
			bool clearRenderTarget{ true };                                    // 050
			bool clearDepthStencilMainScreen{ false };                         // 051
			bool clearDepthStencilOffscreen{ true };                           // 052
			bool postAA;                                                       // 053
			bool useFullPremultAlpha{ false };                                 // 054
			bool alwaysRenderWhenEnabled;                                      // 055
			bool defRenderMainScreen{ true };                                  // 056
			bool enableAO{ false };                                            // 057
			bool useLongRangeCamera{ false };                                  // 058
			bool needsLightSetup{ false };                                     // 059
			bool needsLightSetupOffscreen{ true };                             // 05A
			stl::enumeration<BackgroundMode, std::int32_t> bgmode;             // 05C
			stl::enumeration<PostEffect, std::int32_t> postfx;                 // 060
			stl::enumeration<HighlightEffect, std::int32_t> highlightfx;       // 064
			stl::enumeration<OffscreenMenuSize, std::int32_t> omsize;          // 068
			stl::enumeration<ScreenMode, std::int32_t> screenmode;             // 06C
			stl::enumeration<OffscreenMenuBlendMode, std::int32_t> menuBlend;  // 070
			stl::enumeration<UI_DEPTH_PRIORITY, std::int32_t> depth;           // 074
			NiPointer<NiAVObject> worldAttachedElementRoot{ nullptr };         // 078
			NiPointer<NiAVObject> screenAttachedElementRoot{ nullptr };        // 080
			NiPointer<NiAVObject> offscreenElement{ nullptr };                 // 088
			BSTArray<NiPointer<BSGeometry>> displayGeometry;                   // 090
			NiAVObject* elementRequiringFullVieport{ nullptr };                // 0A8
			NiAVObject* highlightedElement{ nullptr };                         // 0B0
			bool highlightOffscreen{ false };                                  // 0B8
			OldScreenEffectControl pipfx;                                      // 0BC
			OldScreenEffectControl vatsfx;                                     // 12C
			NiPointer<BSShaderAccumulator> accum{ nullptr };                   // 1A0
			NiPointer<NiCamera> pipboyAspect{ nullptr };                       // 1A8
			NiPointer<NiCamera> nativeAspect{ nullptr };                       // 1B0
			NiPointer<NiCamera> nativeAspectLongRange{ nullptr };              // 1B8
			std::int32_t customRenderTarget;                                   // 1C0
			std::int32_t customSwapTarget;                                     // 1C4
			BSTArray<LightParams> mainLights;                                  // 1C8
			BSTArray<LightParams> offscreenLights;                             // 1E0
			float menuDiffuseIntensity{ 1.0F };                                // 1F8
			float menuEmitIntensity{ 1.0F };                                   // 1FC
			float menuDiffuseIntensityWA{ 1.0F };                              // 200
			float menuEmitIntensityWA{ 1.0F };                                 // 204
			BSFixedString name{ "" };                                          // 208
			BSFixedString screenGeomName{ "" };                                // 210
			BSFixedString screenMaterialName{ "" };                            // 218
			BSFixedString maskedGeomName{ "" };                                // 220
			BSFixedString maskedMaterialName{ "" };                            // 228
			NiDirectionalLight* directionalLight{ nullptr };                   // 230
			NiPointer<ShadowSceneNode> screenSSN{ nullptr };                   // 238
			NiPointer<ShadowSceneNode> offscreenSSN{ nullptr };                // 240
		};
		static_assert(sizeof(Renderer) == 0x248);

		namespace
		{
			bool IsHUDGlassEffect(PostEffect a_effect)
			{
				return (stl::to_underlying(a_effect) - 2) <= 1;
			}

			bool IsModMenuEffect(PostEffect a_effect)
			{
				return (stl::to_underlying(a_effect) - 4) <= 2;
			}

			bool IsModMenuHighlightAllEffect(PostEffect a_effect)
			{
				return (stl::to_underlying(a_effect) - 5) <= 1;
			}
		}
	}
}
