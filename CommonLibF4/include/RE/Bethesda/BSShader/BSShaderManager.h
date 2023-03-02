#pragma once
#include "RE/Bethesda/BSTArray.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiPoint2.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/NetImmerse/NiTransform.h"

#include <DirectXMath.h>

namespace RE
{
	class BSGeometry;
	class BSInstanceGroup;
	class BSShaderAccumulator;
	class BSShaderTextureSet;
	class NiAVObject;
	class NiCamera;
	class NiTexture;
	class ShadowSceneNode;

	class BSShaderManager
	{
	public:
#define NUM_RENDERFLAG_BITS 0x10
		using ShaderErrorCallback_t = void (*)(char*, NiAVObject*);
		using GarbageCollectorCallback_t = void (*)(NiAVObject*);
		using TimerFunction_t = float (*)(int, bool);

		enum
		{
			BSS_AMBIENT = 0x1,
			BSS_DIFFUSE = 0x2,
			BSS_TEXTURE = 0x4,
			BSS_SPECULAR = 0x8,
			BSS_SHADOWS = 0x10,
			BSS_FULLMULTIPASSLIGHTING = 0x0F,
			BSS_FULLMULTIPASSLIGHTING_PROJ = 0x0F
		};

		enum ShaderEnum
		{
			BSSM_SHADER_EFFECT,
			BSSM_SHADER_UTILITY,
			BSSM_SHADER_DISTANTTREE,
			BSSM_SHADER_PARTICLE,
			BSSM_SHADER_DFPREPASS,
			BSSM_SHADER_DFLIGHT,
			BSSM_SHADER_DFCOMPOSITE,
			BSSM_SHADER_SKY,
			BSSM_SHADER_LIGHTING,
			BSSM_SHADER_BLOODSPLATTER,
			BSSM_SHADER_WATER,
			BSSM_SHADER_FACE_CUSTOMIZATION,
			BSSM_SHADER_IMAGESPACE,

			BSSM_SHADER_COUNT
		};

		enum
		{
			BSSM_DISABLED = 0x0FFFFFFFF
		};

		enum eCameraInWaterState
		{
			CAMERA_STATE_ABOVE_WATER,
			CAMERA_STATE_PARTIALLY_ABOVE_WATER,
			CAMERA_STATE_PARTIALLY_UNDER_WATER,
			CAMERA_STATE_UNDER_WATER,
		};

		enum etShadowMode
		{
			BSSM_SHADOW_ISFILTER,
			BSSM_SHADOW_PCF4,
			BSSM_SHADOW_PCF9,
			BSSM_SHADOW_LOOPFILTER,
		};

		enum etRenderFlag
		{
			BSSM_RENDERFLAG_COLORWRITEDISABLE
		};

		enum etRenderMode : std::uint32_t
		{
			BSSM_RENDER_NORMAL,
			BSSM_RENDER_NUMLIGHTS,
			BSSM_RENDER_NUMNONSHADOWLIGHTS,
			BSSM_RENDER_NUMSHADOWLIGHTS,
			BSSM_RENDER_NUMPASSES,
			BSSM_RENDER_SINGLEPASS,
			BSSM_RENDER_TEXUSAGE,
			BSSM_RENDER_DEGRADE,
			BSSM_RENDER_FADE,
			BSSM_RENDER_SHADOWSPLITDEBUG,
			BSSM_RENDER_TEXSIZE,
			BSSM_RENDER_FADENODETRIDEBUG,
			BSSM_RENDER_OVERDRAW,
			BSSM_RENDER_DEPTHPREPASS,
			BSSM_RENDER_OCCLUSION_MAP,
			BSSM_RENDER_SHADOWMAP,
			BSSM_RENDER_SHADOWMAP_DIR,
			BSSM_RENDER_SHADOWMAP_PB,
			BSSM_RENDER_LOCALMAP,
			BSSM_RENDER_FROZEN,
			BSSM_RENDER_SCREEN_SPLATTER,
			BSSM_RENDER_LODONLYNONOISE,
			BSSM_RENDER_SILHOUETTELOD,
			BSSM_RENDER_SILHOUETTE,
			BSSM_RENDER_DEFERRED_GBUFFER,
			BSSM_RENDER_DEFERRED_GB_0,
			BSSM_RENDER_DEFERRED_GB_DEBUGSTART,
			BSSM_RENDER_DEFERRED_GB_1,
			BSSM_RENDER_DEFERRED_GB_2,
			BSSM_RENDER_DEFERRED_GB_3,
			BSSM_RENDER_DEFERRED_GB_4,
			BSSM_RENDER_DEFERRED_GB_5,
			BSSM_RENDER_DEFERRED_GB_DEBUGEND,
			BSSM_RENDER_DEFERRED_GB_ALL,
			BSSM_RENDER_LIGHTVIS,
			BSSM_RENDER_VATS_MASK,
			BSSM_RENDER_VATS_MASK_DEBUG,
			BSSM_RENDER_VATS_MASK_PREPASS,
			BSSM_RENDER_VATS_QUERY,
			BSSM_RENDER_MAP_MAKER,
			BSSM_RENDER_SIMPLE_LIGHTING,

			BSSM_RENDER_COUNT
		};

		enum eSceneGraphEnum
		{
			BSSM_SSN_WORLD,
			BSSM_SSN_UI_OLD,
			BSSM_SSN_PREVIEW,
			BSSM_SSN_UI_LOADING_MENU,
			BSSM_SSN_UI,

			BSSM_SSN_COUNT
		};

		enum usRenderFlags : std::uint16_t
		{

		};

		enum BSShaderTimerMode
		{
			TIMER_MODE_DEFAULT,
			TIMER_MODE_DELTA,
			TIMER_MODE_SYSTEM,
			TIMER_MODE_REAL_DELTA,
			TIMER_MODE_FRAME_COUNT,
			TIMER_MODE_ACCUMULATED_DELTA,

			TIMER_MODE_COUNT
		};

		class State
		{
		public:
			//members
			ShadowSceneNode* pShadowSceneNode[5];                                       // 000
			float fTimerValues[TIMER_MODE_COUNT];                                       //
			std::uint32_t uiFrameCount;                                                 //
			NiColorA LoadedRange;                                                       //
			bool bInterior;                                                             //
			bool bLiteBrite;                                                            //
			bool bDeferredRGBEmit;                                                      //
			bool bDeferredRGBSpec;                                                      //
			bool bMenuScreenPremultAlpha;                                               //
			bool bMenuScreenPostAA;                                                     //
			float fMenuScreenAlpha;                                                     //
			bool CharacterLightEnabled;                                                 //
			bool ScreenSpaceReflectionsEnabled;                                         //
			bool ScreenSpaceSubsurfaceScatteringEnabled;                                //
			std::uint32_t uiPipboyScreenTarget;                                         //
			NiPointer<NiTexture> spPipboyFXTexture;                                     //
			float fPipboyScreenEmitIntensity;                                           //
			float fPipboyScreenDiffuseIntensity;                                        //
			float fPipboyScreenEmitIntensityWA;                                         //
			float fPipboyScreenDiffuseIntensityWA;                                      //
			float fSpecularLODStartFadeSquared;                                         //
			float fSpecularLODEndSquared;                                               //
			float fLandLOFadeSeconds;                                                   //
			float fLeafAnimDampenDistStartSPU;                                          //
			float fLeafAnimDampenDistEndSPU;                                            //
			NiPoint2 kOldGridArrayCenter;                                               //
			NiPoint2 kGridArrayCenter;                                                  //
			float kfGriddArrayLerpStart;                                                //
			bool bLODFadeInProgress;                                                    //
			stl::enumeration<eSceneGraphEnum, std::uint8_t> cSceneGraph;                //
			stl::enumeration<etRenderMode, std::uint16_t> usDebugMode;                  //
			std::uint32_t uiDebugColorWrite;                                            //
			NiTransform DirectionalAmbientTransform;                                    //
			NiTransform LocalDirectionalAmbientTransform;                               //
			NiColorA AmbientSpecular;                                                   //
			bool bAmbientSpecularEnabled;                                               //
			std::uint32_t uiTextureTransformCurrentBuffer;                              //
			std::uint32_t uiTextureTransformFlipMode;                                   //
			stl::enumeration<eCameraInWaterState, std::uint32_t> uiCameraInWaterState;  //
			float fCameraNear;                                                          //
			float fCameraFar;                                                           //
			float fWaterIntersect;                                                      //
			NiColorA MenuScreenBlendParams;                                             //
			NiColorA DebugTintColor;                                                    //
			float fBoneTintingTiming;                                                   //
			NiPoint3 ForwardLightOffset;                                                //
			NiPoint3 ClipVolume[2];                                                     //
			NiPointer<BSGeometry> spClipVolumeGeom;                                     //
			NiColorA MaskRectParams;                                                    //
			NiColorA pUIMaskRectsA[16];                                                 //
			NiColorA pUIMaskRectColorsA[16];                                            //
			std::byte gap3C0[16];                                                       //
			NiColorA CharacterLightParams;                                              //
			std::uint32_t uiForceDisableFrame;                                          //
			bool bEffectShaderVATSHighlight;                                            //
			bool ForceEffectShaderPremultAlpha;                                         //
			bool ForceDisableSSR;                                                       //
			bool ForceDisableGodrays;                                                   //
			bool ForceDisableDirLights;                                                 //
			bool PendingForceDisableSSR;                                                //
			bool PendingForceDisableGodrays;                                            //
			bool PendingForceDisableDirLights;                                          //
		};
		static_assert(sizeof(State) == 0x3F0);
	};
	static_assert(std::is_empty_v<BSShaderManager>);

	REL::Relocation<BSShaderManager::ShaderErrorCallback_t*> BSShaderManager__pShaderErrorCallback{ REL::ID(197682) };            //146721A60
	REL::Relocation<BSShaderManager::GarbageCollectorCallback_t*> BSShaderManager__pGarbageCollectorCallback{ REL::ID(416649) };  //146721A68
	//REL::Relocation<float[4][4]> BSShaderManager__actorVegetationCollisionsS{ REL::ID(636411) };                                  //146721A70
	REL::Relocation<BSShaderAccumulator*> BSShaderManager__pCurrentShaderAccumulator{ REL::ID(809145) };    //146721AB0
	REL::Relocation<BSShaderManager::etRenderMode> BSShaderManager__usRenderMode{ REL::ID(1028217) };       //146721AB8
	REL::Relocation<bool> BSShaderManager__bInitialized{ REL::ID(346773) };                                 //146721ABC
	REL::Relocation<bool> BSShaderManager__bImageSpaceEffects{ REL::ID(572286) };                           //146721ABD
	REL::Relocation<bool> BSShaderManager__bTransparencyMultisampling{ (0x6721ABE) };                       //146721ABE
	REL::Relocation<bool> BSShaderManager__bAnisoMinFiltering{ (0x6721ABF) };                               //146721ABF
	REL::Relocation<BSShaderManager::TimerFunction_t> BSShaderManager__pTimerFunction{ REL::ID(1247963) };  //146721AC0
	REL::Relocation<unsigned short> BSShaderManager__usRenderFlags{ (0x6721AC8) };                          //146721AC8
	REL::Relocation<bool> BSShaderManager__bOcclusionQuery{ (0x6721ACA) };                                  //146721ACA
	REL::Relocation<bool> BSShaderManager__bSLIMode{ (0x6721ACB) };                                         //146721ACB
	REL::Relocation<int> BSShaderManager__iSelfIllumCount{ (0x6721ACC) };                                   //146721ACC
	REL::Relocation<std::uint32_t> BSShaderManager__uiStencilRenderTarget{ (0x6721AD0) };                   //146721AD0
	REL::Relocation<float> BSShaderManager__fWindAngle{ (0x6721AD4) };                                      //146721AD4
	REL::Relocation<float> BSShaderManager__fWindMinSpeed{ (0x6721AD8) };                                   //146721AD8
	REL::Relocation<BSShaderManager::etShadowMode> BSShaderManager__eShadowMode{ (0x6721ADC) };             //146721ADC
	REL::Relocation<NiCamera*> BSShaderManager__spCamera{ REL::ID(543218) };                                //146721AE0
	REL::Relocation<float> BSShaderManager__fShadowLODStartFadeSquared{ (0x6721AE8) };                      //146721AE8
	REL::Relocation<float> BSShaderManager__fShadowLODEndSquared{ (0x6721AEC) };                            //146721AEC
	REL::Relocation<bool> BSShaderManager__bUseHardDriveCache{ (0x6721AF0) };                               //146721AF0
	REL::Relocation<bool> BSShaderManager__bDisplayLODLand{ (0x6721AF1) };                                  //146721AF1
	REL::Relocation<bool> BSShaderManager__bWireframeDecals{ (0x6721AF2) };                                 //146721AF2
	REL::Relocation<bool> BSShaderManager__bDynamicWindowReflections{ (0x6721AF3) };                        //146721AF3
	REL::Relocation<float> BSShaderManager__fEnvMapLODStartFade{ (0x6721AF4) };                             //146721AF4
	//REL::Relocation<float[4]> BSShaderManager__CloudParameters{ (0x6721AF8) };                                                    //146721AF8
	REL::Relocation<float> BSShaderManager__fEnvMapLODEnd{ (0x6721B08) };                                     //146721B08
	REL::Relocation<float> BSShaderManager__fEyeEnvMapLODStartFade{ (0x6721B0C) };                            //146721B0C
	REL::Relocation<float> BSShaderManager__fEyeEnvMapLODEnd{ (0x6721B10) };                                  //146721B10
	REL::Relocation<float> BSShaderManager__fDecalLODStartFade{ (0x6721B14) };                                //146721B14
	REL::Relocation<float> BSShaderManager__fDecalLODEnd{ (0x6721B18) };                                      //146721B18
	REL::Relocation<float> BSShaderManager__fSkinnedDecalLODStartFade{ (0x6721B1C) };                         //146721B1C
	REL::Relocation<float> BSShaderManager__fSkinnedDecalLODEnd{ (0x6721B20) };                               //146721B20
	REL::Relocation<bool> BSShaderManager__bInLODWorld{ (0x6721B24) };                                        //146721B24
	REL::Relocation<bool> BSShaderManager__bFreezeGeometryBatch{ (0x6721B25) };                               //146721B25
	REL::Relocation<bool> BSShaderManager__bFrozenBatchAcquired{ (0x6721B26) };                               //146721B26
	REL::Relocation<bool> BSShaderManager__bFreezeCamera{ (0x6721B27) };                                      //146721B27
	REL::Relocation<bool> BSShaderManager__bMTRendering{ (0x6721B28) };                                       //146721B28
	REL::Relocation<bool> BSShaderManager__bLODNoiseAniso{ (0x6721B29) };                                     //146721B29
	REL::Relocation<bool> BSShaderManager__bTintMipMaps{ (0x6721B2A) };                                       //146721B2A
	REL::Relocation<bool> BSShaderManager__bFullScreenMotionBlurVATS{ (0x6721B2B) };                          //146721B2B
	REL::Relocation<float> BSShaderManager__fLODNoiseMipBias{ (0x6721B2C) };                                  //146721B2C
	REL::Relocation<int> BSShaderManager__iObjectMotionBlurCount{ (0x6721B30) };                              //146721B30
	REL::Relocation<float> BSShaderManager__fMinAmbient{ (0x6721B34) };                                       //146721B34
	REL::Relocation<bool> BSShaderManager__bFakeFullScreenMotionBlur{ (0x6721B38) };                          //146721B38
	REL::Relocation<BSShaderManager> BSShaderManager__Instance{ REL::ID(16321) };                             //146721B39
	REL::Relocation<BSPerformanceTimer> TimerImageSpace{ (0x6721B3A) };                                       //146721B3A
	REL::Relocation<BSTArray<NiPointer<BSInstanceGroup>>> BSShaderManager__InstanceGroups{ REL::ID(10442) };  //146721B40
	REL::Relocation<BSTArray<BSShaderTextureSet*>> BSShaderManager__DismembermentTextureArray{ REL::ID() };   //146721B58
	REL::Relocation<BSShaderManager::State> BSShaderManager__State{ REL::ID(1327069) };                       //146721B70
	REL::Relocation<NiPointer<BSShader>> BSShaderManager__pspShader{ REL::ID(487858) };                       //146721F60
	REL::Relocation<NiPointer<NiCamera>> BSShaderManager__spMainCamera{ REL::ID(175576) };                    //146721FC8
	REL::Relocation<DirectX::XMMATRIX> BSShaderManager__xmPipBoyWorldView{ REL::ID(394640) };                 //146721FD0
	REL::Relocation<NiColor> BSShaderManager__kBackgroundColor{ REL::ID(567603) };                            //146722010
	REL::Relocation<NiColorA> BSShaderManager__fpInterfaceTint{ REL::ID(1006044) };                           //146722020
	//REL::Relocation<NiColor[2][3]> BSShaderManager__DirectionalAmbientColorsA{ REL::ID(1444949) };            //146722030
	//REL::Relocation<NiColor[2][3]> BSShaderManager__LocalDirectionalAmbientColorsA{ REL::ID(474137) };        //146722080
	REL::Relocation<NiColorA> BSShaderManager__pHairTint{ (0x67220C8) };     //1467220C8
	REL::Relocation<bool> BSShaderManager__binstancing{ REL::ID(1304977) };  //1467220D8
}
