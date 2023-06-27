#pragma once
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSGraphics/BSGraphicsTypes.h"
#include "RE/NetImmerse/NiMain/NiColor.h"
#include "RE/NetImmerse/NiMain/NiPoint2.h"
#include "RE/NetImmerse/NiMain/NiPoint3.h"
#include "RE/NetImmerse/NiMain/NiPoint4.h"
#include "RE/NetImmerse/NiMain/NiRect.h"

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

	static constexpr auto MAX_VS_CONSTANTS{ 32 };
	static constexpr auto MAX_HS_CONSTANTS{ 32 };
	static constexpr auto MAX_DS_CONSTANTS{ 32 };
	static constexpr auto MAX_PS_CONSTANTS{ 32 };
	static constexpr auto MAX_CS_CONSTANTS{ 32 };

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
		enum class DepthStencilExtraMode;

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
			char* pData;
			std::uint64_t uiVertexDesc;
			std::uint32_t uiRefCount;
			std::uint16_t* pIndices;
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

		class OcclusionQuery
		{
		public:
			//members
		};

		enum class Map
		{
			MAP_READ = 1,
			MAP_WRITE,
			MAP_READ_WRITE,
			MAP_WRITE_DISCARD,
			MAP_WRITE_NO_OVERWRITE
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
			ID3D11Texture2D* m_Texture;  //UNK
			ID3D11Texture2D* tex2D;
			ID3D11ShaderResourceView* m_ResourceView;
			std::uint64_t field_18;
			HANDLE* handle;
			TextureHeader header;
			std::uint32_t field_30;
			std::uint32_t field_34;
			std::uint32_t currentAllocFrame;
			std::uint8_t minLOD;
			std::uint8_t degradeLevel;
			std::byte field_3E;
			std::byte field_3F;
		};

		class TextureAccess
		{
		public:
			D3D11_MAPPED_SUBRESOURCE resource;
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
			void* GetByteCodeBuffer() const
			{
				uintptr_t addr = *(uintptr_t*)this;
				addr += 0x88;
				return (void*)addr;
			}

			// members
			std::uint32_t id{ 0 };                             // 00
			ID3D11ComputeShader* shader{ nullptr };            // 08
			std::uint32_t byteCodeSize{ 0 };                   // 10
			ConstantGroup constantBuffers[3];                  // 18
			std::uint64_t shaderDesc{ 0 };                     // 60
			std::int8_t constantTable[MAX_CS_CONSTANTS]{ 0 };  // 68
		};
		static_assert(sizeof(ComputeShader) == 0x88);

		class DomainShader
		{
		public:
			void* GetByteCodeBuffer() const
			{
				uintptr_t addr = *(uintptr_t*)this;
				addr += 0x88;
				return (void*)addr;
			}

			// members
			std::uint32_t id{ 0 };                             // 00
			ID3D11DomainShader* shader{ nullptr };             // 08
			std::uint32_t byteCodeSize{ 0 };                   // 10
			ConstantGroup constantBuffers[3]{ 0 };             // 18
			std::uint64_t shaderDesc{ 0 };                     // 60
			std::int8_t constantTable[MAX_DS_CONSTANTS]{ 0 };  // 68
		};
		static_assert(sizeof(DomainShader) == 0x88);

		class HullShader
		{
		public:
			void* GetByteCodeBuffer() const
			{
				uintptr_t addr = *(uintptr_t*)this;
				addr += 0x88;
				return (void*)addr;
			}

			// members
			std::uint32_t id{ 0 };                             // 00
			ID3D11HullShader* shader{ nullptr };               // 08
			std::uint32_t byteCodeSize{ 0 };                   // 10
			ConstantGroup constantBuffers[3];                  // 18
			std::uint64_t shaderDesc{ 0 };                     // 60
			std::int8_t constantTable[MAX_HS_CONSTANTS]{ 0 };  // 68
		};
		static_assert(sizeof(HullShader) == 0x88);

		class PixelShader
		{
		public:
			void* GetByteCodeBuffer() const
			{
				uintptr_t addr = *(uintptr_t*)this;
				addr += 0x88;
				return (void*)addr;
			}

			// members
			std::uint32_t id{ 0 };                             // 00
			ID3D11PixelShader* shader{ nullptr };              // 08
			ConstantGroup constantBuffers[3];                  // 10
			std::int8_t constantTable[MAX_PS_CONSTANTS]{ 0 };  // 58
		};
		static_assert(sizeof(PixelShader) == 0x78);

		class VertexShader
		{
		public:
			void* GetByteCodeBuffer() const
			{
				uintptr_t addr = *(uintptr_t*)this;
				addr += 0x88;
				return (void*)addr;
			}

			// members
			std::uint32_t id{ 0 };                             // 00
			ID3D11VertexShader* shader{ nullptr };             // 08
			std::uint32_t byteCodeSize{ 0 };                   // 10
			ConstantGroup constantBuffers[3];                  // 18
			std::uint64_t shaderDesc{ 0 };                     // 60
			std::int8_t constantTable[MAX_VS_CONSTANTS]{ 0 };  // 68
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

		class RendererShadowState
		{
		public:
			//members
			std::uint32_t m_StateUpdateFlags;
			std::uint32_t m_ModifiedBits0x4;
			std::uint32_t m_ModifiedBits0x8;
			std::uint32_t m_ModifiedBits0xC;
			std::uint32_t m_ModifiedBits0x10;
			std::uint32_t m_ModifiedBits0x14;
			std::uint32_t m_ModifiedBits0x18;
			std::uint32_t m_ModifiedBits0x1C;
			std::uint32_t m_ModifiedBits0x20;
			std::uint32_t m_CSUAVModifiedBits;
			bool m_TextureDepthSomethingBool;
			bool m_TextureSomethingBool;
			bool field_2A;
			bool field_2B;
			std::uint32_t m_RenderTargets[8];
			std::uint32_t m_CurrentDepthStencilIndex;
			std::uint32_t m_CurrentDepthStencilSliceIndex;
			std::uint32_t m_CurrentCubeMapRenderTargetIndex;
			std::uint32_t m_CurrentCubeMapRenderTargetViewIndex;
			SetRenderTargetMode m_SetRenderTargetMode[8];
			SetRenderTargetMode m_SetDepthStencilMode;
			SetRenderTargetMode m_SetCubeMapRenderTargetMode;
			std::uint32_t rendertarget;
			std::uint32_t depthstenciltargetindex;
			std::uint32_t cubemaprendertargetindex;
			D3D11_VIEWPORT m_ViewPort;
			DepthStencilDepthMode m_DepthStencilDepthMode;
			DepthStencilStencilMode m_DepthStencilStencilMode;
			DepthStencilExtraMode m_DepthStencilExtraMode;
			std::uint32_t m_StencilRef;
			RasterStateCullMode m_RasterStateFillMode;
			RasterStateCullMode m_RasterStateCullMode;
			RasterStateDepthBiasMode m_RasterStateDepthBiasMode;
			RasterStateScissorMode m_RasterStateScissorMode;
			AlphaBlendMode m_AlphaBlendMode;
			AlphaBlendAlphaToCoverage m_AlphaBlendAlphaToCoverage;
			AlphaBlendWriteMode m_AlphaBlendWriteMode;
			bool m_AlphaTestEnabled;
			float m_AlphaTestRef;
			TextureAddressMode m_VSTextureAddressMode[16];
			TextureFilterMode m_VSTextureFilterMode[16];
			ID3D11ShaderResourceView* m_VSTexture[16];
			std::uint32_t m_VSTextureSomething[16];
			std::uint32_t m_DSTextureAddressMode[16];
			std::uint32_t m_DSTextureFilterMode[16];
			ID3D11ShaderResourceView* m_DSTexture[16];
			std::uint32_t m_DSTextureFilter[16];
			TextureAddressMode textureAddressMode[16];
			std::uint32_t field_3A0;
			std::uint32_t field_3A4;
			std::byte gap3A8[56];
			ID3D11ShaderResourceView* m_Texture[16];
			std::uint32_t m_TextureSomething[16];
			std::uint32_t m_CSTextureAddressMode[16];
			std::uint32_t m_CSTextureFilterMode[16];
			ID3D11ShaderResourceView* SRViewArray[16];
			std::uint32_t m_CSTextureSomething[8];
			void* field_5C0;
			std::uint64_t field_5C8;
			std::uint64_t field_5D0;
			std::uint64_t field_5D8;
			ID3D11UnorderedAccessView* field_5E0;
			std::uint64_t field_5E8;
			std::uint64_t field_5F0;
			std::uint64_t field_5F8;
			std::uint64_t field_600;
			std::uint64_t field_608;
			std::uint64_t field_610;
			std::uint64_t field_618;
			std::uint64_t field_620;
			std::uint64_t field_628;
			ID3D11Buffer* m_ZPrePassConstantBuffer;
			std::uint64_t field_638;
			std::uint64_t field_640;
			ID3D11Buffer* m_AlphaTestZPrePassConstantBufferPS;
			std::uint64_t field_650;
			std::uint64_t field_658;
			std::uint64_t field_660;
			std::uint64_t field_668;
			std::uint64_t field_670;
			std::uint64_t field_678;
			std::uint64_t field_680;
			VertexShader* m_CurrentVertexShader;
			DomainShader* m_CurrentDomainShader;
			HullShader* m_CurrentHullShader;
			PixelShader* m_CurrentPixelShader;
			std::uint32_t field_6A8;
			std::uint32_t field_6AC;
			NiPoint3 actorCollision;
			std::uint32_t field_6BC;
			NiPoint3 field_6C0;
			std::uint32_t field_6CC;
			ViewData m_ViewData;
			float m_PreviousClearColor[4];
			float field_8F0;
			float clearcolor6;
			float clearcolor7;
			float clearcolor8;
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

		class Context
		{
		public:
			//members
		};
		//static_assert(sizeof(Context) == 0x2FF0);

		enum class DepthStencilExtraMode : std::int32_t
		{
			DEPTH_STENCIL_EX_DISABLED = 0x0,
			DEPTH_STENCIL_EX_DFLIGHT_STEP0 = 0x1,
			DEPTH_STENCIL_EX_DFLIGHT_STEP1 = 0x2,
			DEPTH_STENCIL_EX_DFLIGHT_EXCLUSIVE0 = 0x3,
			DEPTH_STENCIL_EX_DFLIGHT_EXCLUSIVE1 = 0x4,
			DEPTH_STENCIL_EX_DFLIGHT_EXCLUSIVECLEAR = 0x5,
			DEPTH_STENCIL_EX_DFDIRLIGHT_SINGLE = 0x6,
			DEPTH_STENCIL_EX_DFDIRLIGHT_STEPS = 0x7,
			DEPTH_STENCIL_EX_DFDIRLIGHT_STEPS_BLEND0 = 0x8,
			DEPTH_STENCIL_EX_DFDIRLIGHT_STEPS_BLEND1 = 0x9,
			DEPTH_STENCIL_EX_DFDIRLIGHT_FINAL = 0xA,
			DEPTH_STENCIL_EX_CHARACTER_LIGHT_TEST = 0xB,
			DEPTH_STENCIL_EX_CHARACTER_LIGHT_MASK = 0xC,
			DEPTH_STENCIL_EX_CHARACTER_LIGHT_MASK_DEPTH_TEST_ONLY = 0xD,
			DEPTH_STENCIL_EX_CLEAR_01111111 = 0xE,

			DEPTH_STENCIL_EX_COUNT
		};

		RendererWindow* GetCurrentRenderWindow();
		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetMainContext();
		ID3D11DeviceContext* GetImmediateContext();
		Context* GetDefaultContext();
		RendererShadowState& GetRendererShadowState();
		RendererShadowState& GetLastDrawCallRendererShadowState();
	};
}
