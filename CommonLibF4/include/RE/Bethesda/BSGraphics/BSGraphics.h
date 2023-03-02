#pragma once
#include "RE/Bethesda/BSGraphics/BSGraphicsTypes.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiPoint2.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiPoint4.h"
#include "RE/NetImmerse/NiRect.h"

#include <DirectXMath.h>
#include <d3d11.h>

struct ID3D11Buffer;
struct ID3D11ComputeShader;
struct ID3D11DepthStencilView;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11DomainShader;
struct ID3D11HullShader;
struct ID3D11PixelShader;
struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;
struct ID3D11Texture2D;
struct ID3D11UnorderedAccessView;
struct ID3D11VertexShader;
struct IDXGISwapChain;

enum DXGI_FORMAT;

namespace RE
{
	enum class DXGI_MODE_SCALING;
	enum class DXGI_MODE_SCANLINE_ORDER;

	class BSD3DResourceCreator;

	class NiCamera;
	class NiTexture;

	struct DXGI_RATIONAL
	{
	public:
		// members
		std::uint32_t numerator;    // 00
		std::uint32_t denominator;  // 04
	};
	static_assert(sizeof(DXGI_RATIONAL) == 0x08);

	namespace BSGraphics
	{
		struct ApplicationWindowProperties
		{
		public:
			//members
			std::uint32_t uiWidth;
			std::uint32_t uiHeight;
			std::int32_t iX;
			std::int32_t iY;
			std::uint32_t uiRefreshRate;
			bool bFullScreen;
			bool bBorderlessWindow;
			bool bVSync;
			std::uint32_t uiPresentInterval;
		};

		struct AutoDebugMarker
		{
		public:
			//members
		};

		struct Buffer
		{
		public:
			//members
			std::uint64_t unk00;
			std::uint64_t rawVertexData;
		};

		struct LineShape
		{
		public:
			//members
			ID3D11Buffer* m_VertexBuffer;
			ID3D11Buffer* m_IndexBuffer;
			std::uint64_t m_VertexDesc;
			std::uint32_t m_RefCount;
		};

		struct TriShape
		{
		public:
			//members
			char* __ptr32 pData;
			std::uint64_t uiVertexDesc;
			std::uint32_t uiRefCount;
			std::uint16_t* __ptr32 pIndices;
		};

		enum Usage
		{
			USAGE_DEFAULT,
			USAGE_IMMUTABLE,
			USAGE_DYNAMIC,
			USAGE_STAGING,
		};

		enum MultiSampleLevel : std::int32_t
		{
			MULTISAMPLE_NONE = 0x0,
			MULTISAMPLE_2 = 0x1,
			MULTISAMPLE_4 = 0x2,
			MULTISAMPLE_8 = 0x3,
		};

		enum TAA_STATE : std::int32_t
		{
			TAA_DISABLED = 0x0,
			TAA_ENABLED = 0x1,
		};

		struct ShaderMacro
		{
		public:
			//members
			const char* Name;
			const char* Definition;
		};

		struct FogStateType
		{
		public:
			//members
			NiPoint4 RangeData;
			NiColor NearLowColor;
			float Power;
			NiColor NearHighColor;
			float Clamp;
			NiColor FarLowColor;
			float HighDensityScale;
			NiColor FarHighColor;
			float fpadding;
			NiPoint4 HighLowRangeData;
		};

		class OcclusionQuery
		{
		public:
			//members
		};

		class TextureHeader
		{
		public:
			//members
			std::uint16_t height;
			std::uint16_t width;
			std::uint8_t mipLevels;
			std::uint8_t format;
			std::uint8_t field_6;
			std::uint8_t field_7;
		};
		static_assert(sizeof(TextureHeader) == 0x8);

		class Texture
		{
		public:
			//members
		};

		class ConstantGroup
		{
		public:
			// members
			ID3D11Buffer* buffer{ nullptr };    // 00
			float* data{ nullptr };             // 08
			bool dataIsCPUWorkBuffer{ false };  // 10
		};
		static_assert(sizeof(ConstantGroup) == 0x18);

		class ComputeShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                   // 00
			ID3D11ComputeShader* shader{ nullptr };  // 08
			std::uint32_t byteCodeSize{ 0 };         // 10
			ConstantGroup constantBuffers[3];        // 18
			std::uint64_t shaderDesc{ 0 };           // 60
			std::int8_t constantTable[32]{ 0 };      // 68
		};
		static_assert(sizeof(ComputeShader) == 0x88);

		class DomainShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                  // 00
			ID3D11DomainShader* shader{ nullptr };  // 08
			std::uint32_t byteCodeSize{ 0 };        // 10
			ConstantGroup constantBuffers[3]{ 0 };  // 18
			std::uint64_t shaderDesc{ 0 };          // 60
			std::int8_t constantTable[32]{ 0 };     // 68
		};
		static_assert(sizeof(DomainShader) == 0x88);

		class HullShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                // 00
			ID3D11HullShader* shader{ nullptr };  // 08
			std::uint32_t byteCodeSize{ 0 };      // 10
			ConstantGroup constantBuffers[3];     // 18
			std::uint64_t shaderDesc{ 0 };        // 60
			std::int8_t constantTable[32]{ 0 };   // 68
		};
		static_assert(sizeof(HullShader) == 0x88);

		class PixelShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                 // 00
			ID3D11PixelShader* shader{ nullptr };  // 08
			ConstantGroup constantBuffers[3];      // 10
			std::int8_t constantTable[32]{ 0 };    // 58
		};
		static_assert(sizeof(PixelShader) == 0x78);

		class VertexShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                  // 00
			ID3D11VertexShader* shader{ nullptr };  // 08
			std::uint32_t byteCodeSize{ 0 };        // 10
			ConstantGroup constantBuffers[3];       // 18
			std::uint64_t shaderDesc{ 0 };          // 60
			std::int8_t constantTable[32]{ 0 };     // 68
		};
		static_assert(sizeof(VertexShader) == 0x88);

		class CubeMapRenderTarget
		{
		public:
			// members
			ID3D11Texture2D* texture;           // 00
			ID3D11RenderTargetView* rtView[6];  // 08
			ID3D11ShaderResourceView* srView;   // 38
		};
		static_assert(sizeof(CubeMapRenderTarget) == 0x40);

		struct CubeMapRenderTargetProperties
		{
		public:
			//members
			std::uint32_t uiWidth;
			std::uint32_t uiHeight;
			BSGraphics::Format eFormat;
			std::uint32_t uiMultiSample;
			bool bSampleable;
			std::int32_t iAlias;
			std::int32_t i360Alias;
			std::int32_t i360Group;
			std::int32_t i360TileHeight;
		};
		static_assert(sizeof(CubeMapRenderTargetProperties) == 0x24);

		class DepthStencilTarget
		{
		public:
			// members
			ID3D11Texture2D* texture;                               // 00
			ID3D11DepthStencilView* dsView[4];                      // 08
			ID3D11DepthStencilView* dsViewReadOnlyDepth[4];         // 28
			ID3D11DepthStencilView* dsViewReadOnlyStencil[4];       // 48
			ID3D11DepthStencilView* dsViewReadOnlyDepthStencil[4];  // 68
			ID3D11ShaderResourceView* srViewDepth;                  // 88
			ID3D11ShaderResourceView* srViewStencil;                // 90
		};
		static_assert(sizeof(DepthStencilTarget) == 0x98);

		struct DepthStencilTargetProperties
		{
		public:
			//members
			std::uint32_t uiWidth;
			std::uint32_t uiHeight;
			std::uint32_t uiArraySize;
			std::uint32_t uiMultiSample;
			std::int32_t iAlias;
			bool bSampleable;
			bool bHTILE;
			bool Stencil;
			bool Use16BitsDepth;
		};
		static_assert(sizeof(DepthStencilTargetProperties) == 0x18);

		class RenderTarget
		{
		public:
			// members
			ID3D11Texture2D* texture;              // 00
			ID3D11Texture2D* copyTexture;          // 08
			ID3D11RenderTargetView* rtView;        // 10
			ID3D11ShaderResourceView* srView;      // 18
			ID3D11ShaderResourceView* copySRView;  // 20
			ID3D11UnorderedAccessView* uaView;     // 28
		};
		static_assert(sizeof(RenderTarget) == 0x30);

		struct RenderTargetProperties
		{
		public:
			//members
			std::uint32_t uiWidth;
			std::uint32_t uiHeight;
			Format eFormat;
			std::uint32_t uiMultiSample;
			bool bCopyable;
			bool bSupportUnorderedAccess;
			bool bAllowMipGeneration;
			bool bForceLinear;
			std::int32_t iMipLevel;
			std::uint32_t uiTextureTarget;
			bool bEnableFastClear;
		};
		static_assert(sizeof(RenderTargetProperties) == 0x20);

		class RendererShadowState
		{
		public:
			//members
			std::int32_t CurrentRenderTargetIndex;			// 000
			std::int32_t CurrentDepthStencilTargetIndex;	//
			std::int32_t CurrentCubeMapRenderTargetIndex;	//
			D3D11_VIEWPORT ViewPort;						//
															// ...
		};

		class RendererWindow
		{
		public:
			//members
			void* hwnd;
			std::int32_t windowX;
			std::int32_t windowY;
			std::int32_t windowWidth;
			std::int32_t windowHeight;
			IDXGISwapChain* swapChain;
			RenderTarget swapChainRenderTarget;
		};
		static_assert(sizeof(RendererWindow) == 0x50);

		struct ViewData
		{
		public:
			//members
			NiRect<float> kViewPort;
			NiPoint2 kViewDepthRange;
			__m128 kViewUp;
			__m128 kViewRight;
			__m128 kViewDir;
			DirectX::XMMATRIX kViewMat;
			DirectX::XMMATRIX kProjMat;
			DirectX::XMMATRIX kViewProjMat;
			DirectX::XMMATRIX kViewProjUnjittered;
			DirectX::XMMATRIX kCurrentViewProjUnjittered;
			DirectX::XMMATRIX kPreviousViewProjUnjittered;
			DirectX::XMMATRIX kInv1stPersonProjMat;
		};

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
			State();
			//State2(); //PDB says there are two constructors

			~State();

			void SetCameraData(NiCamera* cam, bool a3, float a4, float a5)
			{
				using func_t = decltype(&BSGraphics::State::SetCameraData);
				REL::Relocation<func_t> func{ REL::ID(185153) };
				return func(this, cam, a3, a4, a5);
			}

			void CacheCameraData();                   //TODO
			void UpdateAllPreviousFrameCameraData();  //TODO
			void SetFogState();                       //TODO
			void CalculateCameraViewProj();           //TODO
			void SetScreenSpaceCameraData();          //TODO
			void SetCameraViewPort();                 //TODO
			void GetBackBufferAspectRatio();          //TODO
			void GetWideScreen();                     //TODO
			void CreateDefaultTextures();             //TODO
			void DestroyDefaultTextures();            //TODO
			void GetIsDefaultTexture();               //TODO
			void SetCommitTexturesOnCreation();       //TODO
			void QCommitTexturesOnCreation();         //TODO
			void SetImmediateTextureLoads();          //TODO
			void QImmediateTextureLoads();            //TODO
			void UpdateTemporalData();                //TODO
			static void Halton();                     //TODO

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
			void BuildCameraStateData();           //TODO
			void ApplyCameraStateData();           //TODO
			void UpdatePreviousFrameCameraData();  //TODO
			void FindCameraStateData();            //TODO

			//private members
			BSTArray<CameraStateData> kCameraDataCacheA;  //
			CameraStateData CameraState;                  //
			bool CommitTexturesOnCreation;                //
			bool ImmediateTextureLoads;                   //
		};
		static_assert(offsetof(State, CameraState) == 0x160);
		static_assert(sizeof(State) == 0x3C0);

		class Context
		{
		public:
			//members
		};
		//static_assert(sizeof(Context) == 0x2FF0);

	};
	//static_assert(std::is_empty_v<BSGraphics>);

	REL::Relocation<BSGraphics::Context*> BSGraphics__pDefaultContext{ REL::ID(33539) };
	REL::Relocation<BSGraphics::RendererWindow*> BSGraphics__pRendererWindow{ REL::ID(91810) };
	REL::Relocation<BSGraphics::State> BSGraphics__gState{ REL::ID(600795) };
	REL::Relocation<ID3D11Device*> BSGraphics__pDevice{ REL::ID(1454788) };
	REL::Relocation<ID3D11DeviceContext*> BSGraphics__pImmediateContext{ REL::ID(1396536) };
	REL::Relocation<ID3D11DeviceContext*> BSGraphics__pContext{ REL::ID(557671), 0xB18 };          //146A8CB18 - TLS
	REL::Relocation<BSGraphics::Context*> BSGraphics__pCurContext{ REL::ID(557671), 0xB20 };       //146A8CB20 - TLS
	REL::Relocation<std::uint32_t> BSGraphics__uiStreamingDynamicFlags{ REL::ID(557671), 0xB28 };  //146A8CB28 - TLS
	REL::Relocation<std::uint32_t> BSGraphics__uiLODLevel{ REL::ID(557671), 0x1530 };              //146A8D530 - TLS

	namespace BSShaderTechniqueIDMap
	{
		template <class T>
		struct HashPolicy
		{
			[[nodiscard]] std::uint32_t operator()(const T a_shader) const noexcept
			{
				assert(a_shader != nullptr);
				return a_shader->id;
			}
		};

		template <class T>
		struct ComparePolicy
		{
			[[nodiscard]] bool operator()(const T a_lhs, const T a_rhs) const noexcept
			{
				assert(a_lhs != nullptr);
				assert(a_rhs != nullptr);
				return a_lhs->id == a_rhs->id;
			}
		};

		template <class T>
		using MapType = BSTSet<T, HashPolicy<T>, ComparePolicy<T>>;
	}
}
