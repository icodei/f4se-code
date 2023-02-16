#pragma once
#include "RE/Bethesda/BSTArray.h"
#include "RE/NetImmerse/NiColor.h"
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

		enum
		{
			BSSM_DISABLED = 0x0FFFFFFFF
		};

		enum etShadowMode
		{

		};

		enum etRenderMode : std::uint16_t
		{
			unk0 = 0,

			unk18 = 18,
		};

		enum usRenderFlags : std::uint16_t
		{

		};

		class State
		{
		public:

			//members
			ShadowSceneNode* pShadowSceneNode[4];
			std::uint8_t gap20[8];
			float timerMode[5];
			float field_3C;
			std::uint32_t uiFrameCount;
			NiColorA loadedRange;
			bool isInterior;
			bool bLightBrite;
			std::uint8_t unk56;
			bool rgbspecMAYBE;
			bool usePremultAlpha;
			bool field_59;
			float opacityAlpha;
			bool useCharacterLighting;
			std::int8_t bScreenSpaceReflections;
			bool bScreenSpaceSubsurfaceScattering;
			std::uint32_t uiPipboyScreenTarget;
			NiPointer<NiTexture> pipboyFXTexture;
			float fPipboyScreenEmitIntensityPA;
			float menuDiffuseIntensity;
			float menuEmitIntensityWA;
			float menuDiffuseIntensityWA;
			std::int64_t field_80;
			float field_88;
			float fLeafAnimDampenDistStart;
			float fLeafAnimDampenDistEnd;
			NiPoint2 field_94;
			NiPoint2 field_9C;
			float field_A4;
			std::uint8_t field_A8;
			std::int8_t uiCurrentSceneGraph;
			BSShaderManager::etRenderMode etRenderMode;
			std::uint8_t gapB0[16];
			NiTransform QDirectionalAmbientTransform;
			NiTransform QLocalDirectionalAmbientTransform;
			NiColorA QAmbientSpecular;
			std::int8_t field_150;
			std::uint32_t QTextureTransformBufferIndex;
			std::uint32_t QTextureTransformFlipMode;
			std::uint32_t uiCameraInWaterState;
			float camFrustrumFar;
			float camFrustrumNear;
			float fWaterIntersect;
			std::int32_t field_16C;
			std::int32_t field_170;
			std::int32_t field_174;
			std::int64_t field_178;
			std::int64_t field_180;
			float field_188;
			float field_18C;
			NiPoint3 field_190;
			NiPoint3 field_19C;
			NiPoint3 field_1A8;
			BSGeometry* geom_1B8;
			std::uint8_t gap1C0[4];
			float fUIMaskRectEdgeSharpness;
			float field_1C8;
			float opacity;
			std::uint8_t gap1D0[8];
			std::int64_t field_1D8;
			std::uint8_t gap1E0[248];
			std::int64_t field_2D8;
			std::uint8_t gap2E0[240];
			float characterLightRimStrength;
			float characterLightFillStrength;
			std::int32_t field_3D8;
			std::int32_t field_3DC;
			std::int32_t field_3E0;
			bool vatsEffectOff;
			std::int8_t field_3E5;
			std::int8_t field_3E6;
			std::int8_t field_3E7;
			std::int8_t field_3E8;
			bool field_3E9;
			bool field_3EA;
			bool field_3EB;
		};
		static_assert(sizeof(State) == 0x3F0);
	};
	static_assert(std::is_empty_v<BSShaderManager>);

	REL::Relocation<BSShaderManager::ShaderErrorCallback_t*> BSShaderManager__pShaderErrorCallback{ REL::ID(197682) };            //146721A60
	REL::Relocation<BSShaderManager::GarbageCollectorCallback_t*> BSShaderManager__pGarbageCollectorCallback{ REL::ID(416649) };  //146721A68
	REL::Relocation<float[4][4]> BSShaderManager__actorVegetationCollisionsS{ REL::ID(636411) };                                  //146721A70
	REL::Relocation<BSShaderAccumulator*> BSShaderManager__pCurrentShaderAccumulator{ REL::ID(809145) };                          //146721AB0
	REL::Relocation<BSShaderManager::etRenderMode> BSShaderManager__usRenderMode{ REL::ID(1028217) };                             //146721AB8
	REL::Relocation<bool> BSShaderManager__bInitialized{ REL::ID(346773) };                                                       //146721ABC
	REL::Relocation<bool> BSShaderManager__bImageSpaceEffects{ REL::ID(572286) };                                                 //146721ABD
	//REL::Relocation<bool> BSShaderManager__bTransparencyMultisampling{ REL::ID() };                                               //146721ABE
	//REL::Relocation<bool> BSShaderManager__bAnisoMinFiltering{ REL::ID() };                                                       //146721ABF
	REL::Relocation<BSShaderManager::TimerFunction_t> BSShaderManager__pTimerFunction{ REL::ID(1247963) };  //146721AC0
	//REL::Relocation<unsigned short> BSShaderManager__usRenderFlags{ REL::ID() };                                                  //146721AC8
	//REL::Relocation<bool> BSShaderManager__bOcclusionQuery{ REL::ID() };                                                          //146721ACA
	//REL::Relocation<bool> BSShaderManager__bSLIMode{ REL::ID() };                                                                 //146721ACB
	//REL::Relocation<int> BSShaderManager__iSelfIllumCount{ REL::ID() };                                                           //146721ACC
	//REL::Relocation<unsigned int> BSShaderManager__uiStencilRenderTarget{ REL::ID() };                                            //146721AD0
	//REL::Relocation<float> BSShaderManager__fWindAngle{ REL::ID() };                                                              //146721AD4
	//REL::Relocation<float> BSShaderManager__fWindMinSpeed{ REL::ID() };                                                           //146721AD8
	//REL::Relocation<BSShaderManager::etShadowMode> BSShaderManager__eShadowMode{ REL::ID() };                                     //146721ADC
	REL::Relocation<NiCamera*> BSShaderManager__spCamera{ REL::ID(543218) };  //146721AE0
	//REL::Relocation<float> BSShaderManager__fShadowLODStartFadeSquared{ REL::ID() };                                              //146721AE8
	//REL::Relocation<float> BSShaderManager__fShadowLODEndSquared{ REL::ID() };                                                    //146721AEC
	//REL::Relocation<bool> BSShaderManager__bUseHardDriveCache{ REL::ID() };                                                       //146721AF0
	//REL::Relocation<bool> BSShaderManager__bDisplayLODLand{ REL::ID() };                                                          //146721AF1
	//REL::Relocation<bool> BSShaderManager__bWireframeDecals{ REL::ID() };                                                         //146721AF2
	//REL::Relocation<bool> BSShaderManager__bDynamicWindowReflections{ REL::ID() };                                                //146721AF3
	//REL::Relocation<float> BSShaderManager__fEnvMapLODStartFade{ REL::ID() };                                                     //146721AF4
	//REL::Relocation<float[4]> BSShaderManager__CloudParameters{ REL::ID() };                                                      //146721AF8
	//REL::Relocation<float> BSShaderManager__fEnvMapLODEnd{ REL::ID() };                                                           //146721B08
	//REL::Relocation<float> BSShaderManager__fEyeEnvMapLODStartFade{ REL::ID() };                                                  //146721B0C
	//REL::Relocation<float> BSShaderManager__fEyeEnvMapLODEnd{ REL::ID() };                                                        //146721B10
	//REL::Relocation<float> BSShaderManager__fDecalLODStartFade{ REL::ID() };                                                      //146721B14
	//REL::Relocation<float> BSShaderManager__fDecalLODEnd{ REL::ID() };                                                            //146721B18
	//REL::Relocation<float> BSShaderManager__fSkinnedDecalLODStartFade{ REL::ID() };                                               //146721B1C
	//REL::Relocation<float> BSShaderManager__fSkinnedDecalLODEnd{ REL::ID() };                                                     //146721B20
	//REL::Relocation<bool> BSShaderManager__bInLODWorld{ REL::ID() };                                                              //146721B24
	//REL::Relocation<bool> BSShaderManager__bFreezeGeometryBatch{ REL::ID() };                                                     //146721B25
	//REL::Relocation<bool> BSShaderManager__bFrozenBatchAcquired{ REL::ID() };                                                     //146721B26
	//REL::Relocation<bool> BSShaderManager__bFreezeCamera{ REL::ID() };                                                            //146721B27
	//REL::Relocation<bool> BSShaderManager__bMTRendering{ REL::ID() };                                                             //146721B28
	//REL::Relocation<bool> BSShaderManager__bLODNoiseAniso{ REL::ID() };                                                           //146721B29
	//REL::Relocation<bool> BSShaderManager__bTintMipMaps{ REL::ID() };                                                             //146721B2A
	//REL::Relocation<bool> BSShaderManager__bFullScreenMotionBlurVATS{ REL::ID() };                                                //146721B2B
	//REL::Relocation<float> BSShaderManager__fLODNoiseMipBias{ REL::ID() };                                                        //146721B2C
	//REL::Relocation<int> BSShaderManager__iObjectMotionBlurCount{ REL::ID() };                                                    //146721B30
	//REL::Relocation<float> BSShaderManager__fMinAmbient{ REL::ID() };                                                             //146721B34
	//REL::Relocation<bool> BSShaderManager__bFakeFullScreenMotionBlur{ REL::ID() };                                                //146721B38
	REL::Relocation<BSShaderManager> BSShaderManager__Instance{ REL::ID(16321) };  //146721B39
	//REL::Relocation<BSPerformanceTimer> TimerImageSpace{ REL::ID() };                                                             //146721B3A
	REL::Relocation<BSTArray<NiPointer<BSInstanceGroup>>> BSShaderManager__InstanceGroups{ REL::ID(10442) };  //146721B40
	REL::Relocation<BSTArray<BSShaderTextureSet*>> BSShaderManager__DismembermentTextureArray{ REL::ID() };   //146721B58
	REL::Relocation<BSShaderManager::State> BSShaderManager__State{ REL::ID(1327069) };                       //146721B70
	REL::Relocation<NiPointer<BSShader>> BSShaderManager__pspShader{ REL::ID(487858) };                       //146721F60
	REL::Relocation<NiPointer<NiCamera>> BSShaderManager__spMainCamera{ REL::ID(175576) };                    //146721FC8
	REL::Relocation<DirectX::XMMATRIX> BSShaderManager__xmPipBoyWorldView{ REL::ID(394640) };                 //146721FD0
	REL::Relocation<NiColor> BSShaderManager__kBackgroundColor{ REL::ID(567603) };                            //146722010
	REL::Relocation<NiColorA> BSShaderManager__fpInterfaceTint{ REL::ID(1006044) };                           //146722020
	REL::Relocation<NiColor[2][3]> BSShaderManager__DirectionalAmbientColorsA{ REL::ID(1444949) };            //146722030
	REL::Relocation<NiColor[2][3]> BSShaderManager__LocalDirectionalAmbientColorsA{ REL::ID(474137) };        //146722080
	//REL::Relocation<NiColorA> BSShaderManager__pHairTint{ REL::ID() };                                                            //1467220C8
	REL::Relocation<bool> BSShaderManager__binstancing{ REL::ID(1304977) };  //1467220D8
}
