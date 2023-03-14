#pragma once
#include "RE/Bethesda/BSTArray.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/NetImmerse/NiMain/NiColor.h"
#include "RE/NetImmerse/NiMain/NiPoint2.h"
#include "RE/NetImmerse/NiMain/NiPoint3.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"
#include "RE/NetImmerse/NiMain/NiTransform.h"

#include <DirectXMath.h>

namespace RE
{
	class BSGeometry;
	class BSInstanceGroup;
	class BSPerformanceTimer;
	class BSShader;
	class BSShaderAccumulator;
	class BSShaderTextureSet;
	class NiAVObject;
	class NiCamera;
	class NiTexture;
	class ShadowSceneNode;

	class BSShaderManager
	{
	public:
		//custom helper functions start

		static NiCamera* GetCamera()
		{
			REL::Relocation<NiCamera**> singleton{ REL::ID(543218) };
			return *singleton;
		}

		static NiCamera* GetMainCamera()
		{
			REL::Relocation<NiPointer<NiCamera>*> singleton{ REL::ID(175576) };
			return singleton.get()->get();
		}

		static NiPointer<NiCamera>& GetMainCameraPtr()
		{
			REL::Relocation<NiPointer<NiCamera>*> singleton{ REL::ID(175576) };
			return *singleton;
		}

		//custom helper functions end

		enum ShaderEnum : std::int32_t
		{
			BSSM_SHADER_EFFECT = 0x0,
			BSSM_SHADER_UTILITY = 0x1,
			BSSM_SHADER_DISTANTTREE = 0x2,
			BSSM_SHADER_PARTICLE = 0x3,
			BSSM_SHADER_DFPREPASS = 0x4,
			BSSM_SHADER_DFLIGHT = 0x5,
			BSSM_SHADER_DFCOMPOSITE = 0x6,
			BSSM_SHADER_SKY = 0x7,
			BSSM_SHADER_LIGHTING = 0x8,
			BSSM_SHADER_BLOODSPLATTER = 0x9,
			BSSM_SHADER_WATER = 0xA,
			BSSM_SHADER_FACE_CUSTOMIZATION = 0xB,
			BSSM_SHADER_IMAGESPACE = 0xC,

			BSSM_SHADER_COUNT
		};

		//static member DefaultErrorMapID
		//static member DefaultNormalMapID
		//static function GetShader

		using SHADERERRORFUNC = void (*)(char*, NiAVObject*);
		using GARBAGECOLLECTORADDFUNC = void (*)(NiAVObject*);

		//static member pspShader
		//static member pDebugTextureViewer
		//static member pShaderErrorCallback
		//static member actorVegitationCollisionsS
		//static function Free
		//static function Initialize
		//static function Reinitialize
		//static function RegisterStreamables
		//static function CreateTangentSpaceSimple
		//static member pGarbageCollectorCallback
		//static function GetShaderErrorCallback
		//static function SetShaderErrorCallback
		//static function ReportError
		//static function GarbageCollectorAdd
		//static function SetGarbageCollectorAddCallback
		//static function QGarbageCollectorCallbackSet

		using FPTIMERFUNC = float (*)(int, bool);

		enum BSShaderTimerMode : std::int32_t
		{
			TIMER_MODE_DEFAULT = 0x0,
			TIMER_MODE_DELTA = 0x1,
			TIMER_MODE_SYSTEM = 0x2,
			TIMER_MODE_REAL_DELTA = 0x3,
			TIMER_MODE_FRAME_COUNT = 0x4,
			TIMER_MODE_ACCUMULATED_DELTA = 0x5,

			TIMER_MODE_COUNT
		};

		//static function SetTimerFunc
		//static function UpdateTimers
		//static function GetTimer
		//static function GetTimer
		//static function GetFrameCount
		//static function SetStencilRenderTarget
		//static function QStencilRenderTarget

		static constexpr auto BSSM_DISABLED{ 0x0FFFFFFFF };

		enum eSceneGraphEnum : std::int32_t
		{
			BSSM_SSN_WORLD,
			BSSM_SSN_UI_OLD,
			BSSM_SSN_PREVIEW,
			BSSM_SSN_UI_LOADING_MENU,
			BSSM_SSN_UI,

			BSSM_SSN_COUNT
		};

		enum class etRenderMode : std::int32_t
		{
			BSSM_RENDER_NORMAL = 0x0,
			BSSM_RENDER_NUMLIGHTS = 0x1,
			BSSM_RENDER_NUMNONSHADOWLIGHTS = 0x2,
			BSSM_RENDER_NUMSHADOWLIGHTS = 0x3,
			BSSM_RENDER_NUMPASSES = 0x4,
			BSSM_RENDER_SINGLEPASS = 0x5,
			BSSM_RENDER_TEXUSAGE = 0x6,
			BSSM_RENDER_DEGRADE = 0x7,
			BSSM_RENDER_FADE = 0x8,
			BSSM_RENDER_SHADOWSPLITDEBUG = 0x9,
			BSSM_RENDER_TEXSIZE = 0xA,
			BSSM_RENDER_FADENODETRIDEBUG = 0xB,
			BSSM_RENDER_OVERDRAW = 0xC,
			BSSM_RENDER_DEPTHPREPASS = 0xD,
			BSSM_RENDER_OCCLUSION_MAP = 0xE,
			BSSM_RENDER_SHADOWMAP = 0xF,
			BSSM_RENDER_SHADOWMAP_DIR = 0x10,
			BSSM_RENDER_SHADOWMAP_PB = 0x11,
			BSSM_RENDER_LOCALMAP = 0x12,
			BSSM_RENDER_FROZEN = 0x13,
			BSSM_RENDER_SCREEN_SPLATTER = 0x14,
			BSSM_RENDER_LODONLYNONOISE = 0x15,
			BSSM_RENDER_SILHOUETTELOD = 0x16,
			BSSM_RENDER_SILHOUETTE = 0x17,
			BSSM_RENDER_DEFERRED_GBUFFER = 0x18,
			BSSM_RENDER_DEFERRED_GB_0 = 0x19,
			BSSM_RENDER_DEFERRED_GB_DEBUGSTART = 0x19,
			BSSM_RENDER_DEFERRED_GB_1 = 0x1A,
			BSSM_RENDER_DEFERRED_GB_2 = 0x1B,
			BSSM_RENDER_DEFERRED_GB_3 = 0x1C,
			BSSM_RENDER_DEFERRED_GB_4 = 0x1D,
			BSSM_RENDER_DEFERRED_GB_5 = 0x1E,
			BSSM_RENDER_DEFERRED_GB_DEBUGEND = 0x1E,
			BSSM_RENDER_DEFERRED_GB_ALL = 0x1F,
			BSSM_RENDER_LIGHTVIS = 0x20,
			BSSM_RENDER_VATS_MASK = 0x21,
			BSSM_RENDER_VATS_MASK_DEBUG = 0x22,
			BSSM_RENDER_VATS_MASK_PREPASS = 0x23,
			BSSM_RENDER_VATS_QUERY = 0x24,
			BSSM_RENDER_MAP_MAKER = 0x25,
			BSSM_RENDER_SIMPLE_LIGHTING = 0x26,

			BSSM_RENDER_COUNT
		};

		enum eCameraInWaterState : std::int32_t
		{
			CAMERA_STATE_ABOVE_WATER,
			CAMERA_STATE_PARTIALLY_ABOVE_WATER,
			CAMERA_STATE_PARTIALLY_UNDER_WATER,
			CAMERA_STATE_UNDER_WATER,
		};

		//================================================= NOTES ABOUT pShadowSceneNode ===================================================//
		// Found with REClass while character was in a mostly empty test world.																//
		// Character was standing around and did not interact with any workshops or workbenches.											//
		// Could be why UI_LOADING_MENU and PREVIEW were empty/nullptr.																		//
		// Another potential for UI_LOADING_MENU being empty is my use of high fps fix mod and removing loading screen models.				//
		//==================================================================================================================================//
		//											//											//											//
		// pShadowSceneNode[0] <- WORLD				// pShadowSceneNode[1] <- UI_OLD			// pShadowSceneNode[2] <- PREVIEW			//
		//	Name									//	Name									//	Name									//
		//	 shadow scene node						//	 shadow scene node						//											//
		//	Parent									//	Parent									//	Parent									//
		//	 WorldRootNode? (SceneGraph)			//	 NULL 									//		 									//
		//	Children								//	Children								//	Children								//
		//	 0 - Sky (BSMultiBoundNode)				//	 0 - NoName (NiNode)					//	 0 - 									//
		//	 1 - Weather (NiNode)					//	 1 - NoName (NiNode)					//	 1 - 									//
		//	 2 - LODRoot (BSClearZNode)				//	 2 - NoName (NiNode)					//											//
		//	 3 - ObjectLODRoot? (NiNode)			//	 3 - NoName (NiNode)					//											//
		//	 4 - NULL								//	 4 - NoName (NiNode)					//											//
		//	 5 - NoName (BSParticleSystemManager)	//	 5 - NoName (NiNode)					//											//
		//	 6 - GrassManager? (NiNode)				//	 6 - NoName (NiNode)					//											//
		//	 7 - NULL								//	 7 - NoName (NiNode)					//											//
		//	 8 - MultiBoundNode Node (NiNode)		//											//											//
		//	 9 - Portal-shared Node	(NiNode)		//											//											//
		//	10 - NoName (NiNode)					//											//											//
		//											//											//											//
		//==================================================================================================================================//
		//											//											//											//
		//	pShadowSceneNode[3] <- UI_LOADING_MENU	// pShadowSceneNode[4] <- UI				//											//
		//	Name									//  Name									//											//
		//											//	 Interface3D Root						//											//
		//	Parent									//	Parent									//											//
		//											//	 NULL									//											//
		//	Children								//	Children								//											//
		//											//	 0 -									//											//
		//											//	 1 -									//											//
		//											//	 2 -									//											//
		//											//	 3 -									//											//
		//											//	 4 -									//											//
		//											//	 5 -									//											//
		//											//	 6 -									//											//
		//											//	 7 -									//											//
		//											//	 8 -									//											//
		//											//	 9 -									//											//
		//											//	10 -									//											//
		//											//	11 -									//											//
		//											//											//											//
		//==================================================================================================================================//

		class State
		{
		public:
			[[nodiscard]] static State& GetSingleton()
			{
				REL::Relocation<State*> singleton{ REL::ID(1327069) };
				return *singleton;
			}

			//members
			ShadowSceneNode* pShadowSceneNode[BSSM_SSN_COUNT];                          // 000
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
			std::byte field_AA;                                                         //
			stl::enumeration<etRenderMode, std::uint16_t> usDebugMode;                  //
			std::byte gapAE[18];                                                        //
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
			float field_16C;                                                            //
			std::byte gap170[12];                                                       //
			std::byte field_17C;                                                        //
			std::byte gap17D[7];                                                        //
			std::byte field_184;                                                        //
			std::byte gap185[7];                                                        //
			float fBoneTintingTiming;                                                   //
			NiPoint3 ForwardLightOffset;                                                //
			NiPoint3 ClipVolume[2];                                                     //
			NiPointer<BSGeometry> spClipVolumeGeom;                                     //
			NiColorA MaskRectParams;                                                    //
			NiColorA pUIMaskRectsA[16];                                                 //
			NiColorA pUIMaskRectColorsA[16];                                            //
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
		static_assert(offsetof(State, cSceneGraph) == 0xA9);
		static_assert(offsetof(State, usDebugMode) == 0xAC);
		static_assert(sizeof(State) == 0x3F0);

		//static function QState
		//static function GetInterior
		//static function SetInterior
		//static function GetWindMagnitude
		//static function SetWindMagnitude
		//static function GetWindAngle
		//static function SetWindAngle
		//static function GetWindMinSpeed
		//static function SetWindMinSpeed
		//static function GetWindMaxSpeed
		//static function SetWindMaxSpeed
		//static function GetWindFrequency
		//static function SetWindFrequency
		//static function GetWindShaderMultiplier
		//static function QPipboyScreenTarget
		//static function SetPipboyScreenTarget
		//static function QPipboyFXTexture
		//static function SetPipboyFXTexture

		static constexpr auto BSS_AMBIENT{ 0x1 };
		static constexpr auto BSS_DIFFUSE{ 0x2 };
		static constexpr auto BSS_TEXTURE{ 0x4 };
		static constexpr auto BSS_SPECULAR{ 0x8 };
		static constexpr auto BSS_SHADOWS{ 0x10 };
		static constexpr auto BSS_FULLMULTIPASSLIGHTING{ 0xF };
		static constexpr auto BSS_FULLMULTIPASSLIGHTING_PROJ{ 0xF };

		//static function EnableShadows
		//static function GetShadows
		//static function SetEmittanceRecurse
		//static function SetExternalEmittanceRecurse
		//static function SetEnabledPasses
		//static function GetEnabledPasses
		//static function GetLiteBrite
		//static function QTextureTransformBufferIndex
		//static function QTextureTransformFlipMode
		//static function FlipTextureTransformBufferIndex
		//static function SetLiteBrite
		//static member fGamma
		//static function SetCurrentSceneGraph
		//static function GetCurrentSceneGraph
		//static function SetShadowSceneNode
		//static function GetShadowSceneNode
		//static function SetFogProperty
		//static function GetFogProperty
		//static function QLoadWarningFile
		//static function SetLoadWarningFile

		static void GetTexture(const char* filepath, bool demandTex, NiPointer<NiTexture>& returnTex, bool environmentMap, bool normalMap, bool a6)
		{
			using func_t = decltype(&BSShaderManager::GetTexture);
			REL::Relocation<func_t> func{ REL::ID(1375091) };
			return func(filepath, demandTex, returnTex, environmentMap, normalMap, a6);
		}

		//static function ReloadTexture
		//static function SetRenderMode
		//static function IsDepthRenderMode
		//static function IsSilhouetteRenderMode
		//static function GetRenderMode
		//static function SetDebugMode
		//static function SetDebugChannels
		//static function GetDebugMode
		//static function GetDebugChannels
		//static function IsDebugColorMode
		//static function SetFlatAmbientColor
		//static function SetDirectionalAmbientColors
		//static function GetDirectionalAmbientColors
		//static function SetLocalDirectionalAmbientColors
		//static function GetLocalDirectionalAmbientColors
		//static function QDirectionalAmbientTransform
		//static function QLocalDirectionalAmbientTransform
		//static function QAmbientSpecular
		//static function QAmbientSpecularEnabled

		enum class etRenderFlag : std::int32_t
		{
			BSSM_RENDERFLAG_COLORWRITEDISABLE
		};

		//static function GetRenderFlag
		//static function SetRenderFlag
		//static function EnableImageSpaceEffects
		//static function GetImageSpaceEffects
		//static function SetTintMipMaps
		//static function GetTintMipMaps
		//static function SetUseDirectionalMaterials
		//static function QUseDirectionalMaterials
		//static function UpdateSLIMode

		enum class etShadowMode : std::int32_t
		{
			BSSM_SHADOW_ISFILTER,
			BSSM_SHADOW_PCF4,
			BSSM_SHADOW_PCF9,
			BSSM_SHADOW_LOOPFILTER,
		};

		//static member eShadowMode
		//static function GetRenderDebugTexture
		//static function RenderDebugTexture
		//static function SetDebugRenderTexture
		//static function GetSelfIllumCount
		//static function SetSelfIllumCount
		//...

		static BSShaderAccumulator* GetCurrentAccumulator()
		{
			using func_t = decltype(&BSShaderManager::GetCurrentAccumulator);
			REL::Relocation<func_t> func{ REL::ID(1555929) };
			return func();
		}

		static void SetCurrentAccumulator(BSShaderAccumulator* a_accumulator)
		{
			using func_t = decltype(&BSShaderManager::SetCurrentAccumulator);
			REL::Relocation<func_t> func{ REL::ID(412086) };
			return func(a_accumulator);
		}
		//...
		//static function SetFOV
		//...
		using InstanceMap = BSTHashMap<std::uint64_t, BSTArray<BSGeometry*>>;
		//static function StartMapForInstancing
		//static function AddToMapForInstancing
		//static function FinishInstancing
		//static member InstanceGroups
		//static member IMap
		//static member pTimerFunction
		//static member iENabledPasses
		//static member bInitialized
		static constexpr auto NUM_RENDERFLAG_BITS{ 0x10 };
		//static member usRenderFlags
		//...
		//static member St
		//static member pCurrentShaderAccumulator
		//static member usRenderMode
		//static function BSShaderManager
		//static member Instance
	};
	static_assert(std::is_empty_v<BSShaderManager>);
}
