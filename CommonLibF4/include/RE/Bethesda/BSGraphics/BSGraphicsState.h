#pragma once
#include "RE/Bethesda/BSGraphics/BSGraphics.h"
#include "RE/Bethesda/BSGraphics/BSGraphicsTypes.h"
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/NetImmerse/NiMain/NiColor.h"
#include "RE/NetImmerse/NiMain/NiPoint4.h"
#include "RE/NetImmerse/NiMain/NiRect.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class NiTexture;
	class NiCamera;

	namespace BSGraphics
	{
		struct FogStateType //Line 66
		{
		public:
			//members
			NiPoint4 RangeData;         //00
			NiColor NearLowColor;       //10
			float Power;                //1C
			NiColor NearHighColor;      //20
			float Clamp;                //2C
			NiColor FarLowColor;        //30
			float HighDensityScale;     //3C
			NiColor FarHighColor;       //40
			float fpadding;             //4C
			NiPoint4 HighLowRangeData;  //50
		};
		static_assert(sizeof(FogStateType) == 0x60);

		struct CameraStateData
		{
		public:
			//members
			ViewData CamViewData;
			NiPoint3 PosAdjust;
			NiPoint3 CurrentPosAdjust;
			NiPoint3 PreviousPosAdjust;
			NiCamera* pReferenceCamera;
			bool UseJitter;
		};

		class State
		{
		public:
			[[nodiscard]] static State& GetSingleton()
			{
				REL::Relocation<State*> singleton{ REL::ID(600795) };
				return *singleton;
			}

			//State();
			//State(); //PDB says there are two constructors

			//~State();

			void SetCameraData(NiCamera* cam, bool a3, float a4, float a5)
			{
				using func_t = decltype(&BSGraphics::State::SetCameraData);
				REL::Relocation<func_t> func{ REL::ID(185153) };
				return func(this, cam, a3, a4, a5);
			}

			//void CacheCameraData();                   //TODO
			//void UpdateAllPreviousFrameCameraData();  //TODO
			//void SetFogState();                       //TODO
			//void CalculateCameraViewProj();           //TODO
			//void SetScreenSpaceCameraData();          //TODO
			//void SetCameraViewPort();                 //TODO
			//void GetBackBufferAspectRatio();          //TODO
			//void GetWideScreen();                     //TODO
			//void CreateDefaultTextures();             //TODO
			//void DestroyDefaultTextures();            //TODO
			//void GetIsDefaultTexture();               //TODO
			//void SetCommitTexturesOnCreation();       //TODO
			//void QCommitTexturesOnCreation();         //TODO
			//void SetImmediateTextureLoads();          //TODO
			//void QImmediateTextureLoads();            //TODO
			//void UpdateTemporalData();                //TODO
			//static void Halton();                     //TODO

			//public members
			std::uint32_t iCurrentFrame;                             //000
			float fOffsetX;                                          //
			float fOffsetY;                                          //
			std::uint32_t iCurrentFrameOffset;                       //
			std::uint32_t iPreviousFrameOffset;                      //
			FogStateType FogState;                                   //
			MultiSampleLevel uiMultiSample;                          //
			std::uint32_t uiBackBufferWidth;                         //
			std::uint32_t uiBackBufferHeight;                        //
			std::uint32_t uiScreenWidth;                             //
			std::uint32_t uiScreenHeight;                            //
			NiRect<float> kFrameBufferViewport;                      //
			std::uint32_t uiFrameCount;                              //
			std::uint32_t uiFrameID;                                 //
			bool bInsideFrame;                                       //
			bool bLetterbox;                                         //
			bool bAllowDepthBufferAsTexture;                         //
			bool bShadows;                                           //
			bool bCompiledShaderThisFrame;                           //
			TAA_STATE TaaState;                                      //
			std::uint32_t TaaDisableCounter;                         //
			std::uint32_t TrijuiceState;                             //
			NiPointer<NiTexture> pDefaultTextureBlack;               //
			NiPointer<NiTexture> pDefaultTextureWhite;               //
			NiPointer<NiTexture> pDefaultTextureGrey;                //
			NiPointer<NiTexture> pDefaultHeightMap;                  //
			NiPointer<NiTexture> pDefaultReflectionCubeMap;          //
			NiPointer<NiTexture> pDefaultFaceDetailMap;              //
			NiPointer<NiTexture> pDefaultHighFreqNormalMap;          //
			NiPointer<NiTexture> pDefaultTexEffectMap;               //
			NiPointer<NiTexture> pDefaultTextureWhiteNoiseMap;       //
			NiPointer<NiTexture> pDefaultTextureWhiteNoiseMapSmall;  //
			NiPointer<NiTexture> pDefaultTextureNormalMap;           //
			NiPointer<NiTexture> pDefaultTextureDiffuseMap;          //
			NiPointer<NiTexture> pDefaultSplineMap;                  //
			NiPointer<NiTexture> pDefaultTextureDissolvePattern;     //
			Texture* pDefaultImagespaceLUT;                          //
			NiPointer<NiTexture> pRotatedPoissonDiscLookupMap;       //
			std::uint32_t PresentImmediateThreshold;                 //
			std::uint32_t PresentFlag;                               //
			//In the PDB private starts here
			//private:
			//void BuildCameraStateData();           //TODO
			//void ApplyCameraStateData();           //TODO
			//void UpdatePreviousFrameCameraData();  //TODO
			//void FindCameraStateData();            //TODO

			//private members
			BSTArray<CameraStateData> kCameraDataCacheA;  //
			CameraStateData CameraState;                  //
			bool CommitTexturesOnCreation;                //
			bool ImmediateTextureLoads;                   //
		};
		static_assert(offsetof(State, CameraState) == 0x160);
		static_assert(sizeof(State) == 0x3C0);
	}
}
