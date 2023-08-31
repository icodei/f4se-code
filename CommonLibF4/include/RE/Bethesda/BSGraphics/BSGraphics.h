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
			// members
			std::uint16_t height = 0;   // 0
			std::uint16_t width = 0;    // 2
			std::uint8_t mipCount = 0;  // 3
			std::uint8_t format = 0;    // 5
			std::uint8_t flags = 0;     // 6
			std::uint8_t tilemode = 0;  // 7
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
			std::uint32_t stateUpdateFlags;
			std::uint32_t VSTextureFlags;
			std::uint32_t VSTextureState;
			std::uint32_t DSTextureFlags;
			std::uint32_t DSTextureState;
			std::uint32_t textureFlags;
			std::uint32_t textureState;
			std::uint32_t CSTextureFlags;
			std::uint32_t CSTextureState;
			std::uint32_t CSUAVState;
			std::uint8_t clearTextureDepth;
			std::uint8_t clearTextureStencil;
			std::byte gap2A[2];
			std::uint32_t renderTarget[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
			std::byte gap4C[16];
			stl::enumeration<BSGraphics::SetRenderTargetMode, std::uint32_t> setRenderTargetMode[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT];
			stl::enumeration<BSGraphics::SetRenderTargetMode, std::uint32_t> setDepthStencilMode;
			stl::enumeration<BSGraphics::SetRenderTargetMode, std::uint32_t> setCubeMapRenderTargetMode;
			std::byte field_84[4];
			std::byte field_88[8];
			D3D11_VIEWPORT viewport;
			stl::enumeration<BSGraphics::DepthStencilDepthMode, std::uint32_t> depthStencilDepthMode;
			stl::enumeration<BSGraphics::DepthStencilStencilMode, std::uint32_t> depthStencilStencilMode;
			stl::enumeration<BSGraphics::DepthStencilExtraMode, std::uint32_t> depthStencilExtraMode;
			std::byte gapB4[4];
			stl::enumeration<BSGraphics::RasterStateFillMode, std::uint32_t> rasterStateFillMode;
			stl::enumeration<BSGraphics::RasterStateCullMode, std::uint32_t> rasterStateCullMode;
			stl::enumeration<BSGraphics::RasterStateDepthBiasMode, std::uint32_t> rasterStateDepthBiasMode;
			stl::enumeration<BSGraphics::RasterStateScissorMode, std::uint32_t> rasterStateScissorMode;
			stl::enumeration<BSGraphics::AlphaBlendMode, std::uint32_t> alphaBlendMode;
			stl::enumeration<BSGraphics::AlphaBlendAlphaToCoverage, std::uint32_t> alphaBlendAlphaToCoverage;
			stl::enumeration<BSGraphics::AlphaBlendWriteMode, std::uint32_t> alphaBlendWriteMode;
			std::byte gapD4[8];
			stl::enumeration<BSGraphics::TextureAddressMode, std::uint32_t> VSTextureAddressMode[16];
			stl::enumeration<BSGraphics::TextureFilterMode, std::uint32_t> VSTextureFilterMode[16];
			std::byte gap15C[4];
			ID3D11ShaderResourceView* VSTexture[16];
			std::uint32_t VSTextureMinLodMode[16];
			stl::enumeration<BSGraphics::TextureAddressMode, std::uint32_t> DSTextureAddressMode[16];
			stl::enumeration<BSGraphics::TextureFilterMode, std::uint32_t> DSTextureFilterMode[16];
			ID3D11ShaderResourceView* DSTexture[16];
			std::uint32_t DSTextureMinLodMode[16];
			stl::enumeration<BSGraphics::TextureAddressMode, std::uint32_t> textureAddressMode[16];
			stl::enumeration<BSGraphics::TextureFilterMode, std::uint32_t> textureFilterMode[16];
			ID3D11ShaderResourceView* texture[16];
			std::uint32_t textureMinLodMode[16];
			stl::enumeration<BSGraphics::TextureAddressMode, std::uint32_t> CSTextureAddressMode[16];
			stl::enumeration<BSGraphics::TextureFilterMode, std::uint32_t> CSTextureFilterMode[16];
			ID3D11ShaderResourceView* CSTexture[16];
			std::uint32_t CSTextureMinLodMode[16];
			ID3D11UnorderedAccessView* CSUAV[8];
			std::byte gap620[104];
			BSGraphics::VertexShader* currentVertexShader;
			BSGraphics::DomainShader* currentDomainShader;
			BSGraphics::HullShader* currentHullShader;
			BSGraphics::PixelShader* currentPixelShader;
			std::uint32_t field_6A8;
			std::uint32_t field_6AC;
			NiPoint3 posAdjust;
			std::byte gap6BC[4];
			NiPoint3 lastPosAdjust;
			std::byte gap6CC[532];
			float clearColor[4];
			float lastClearColor[4];
			std::byte gap900[16];
		};
		static_assert(sizeof(RendererShadowState) == 0x910);  // Unconfirmed

		class RendererWindow
		{
		public:
			//members
			void* hwnd;                          // 00
			std::int32_t windowX;                // 08
			std::int32_t windowY;                // 0C
			std::int32_t windowWidth;            // 10
			std::int32_t windowHeight;           // 14
			IDXGISwapChain* swapChain;           // 18
			RenderTarget swapChainRenderTarget;  // 20
		};
		static_assert(sizeof(RendererWindow) == 0x50);

		class Context
		{
		public:
			//members
			ID3D11DeviceContext* deviceContext;                  // 0000
			ID3D11Buffer* shaderConstantBuffer;                  // 0008
			ID3D11Buffer* ConstantBuffer1[541];                  // 0010	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer2[20];                   // 10F8	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer3[10];                   // 1198	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer4[28];                   // 11E8	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer5[20];                   // 12C8	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer6[10];                   // 1368	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer7[20];                   // 13B8	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer8[20];                   // 1458	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer9[10];                   // 14F8	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer10[20];                  // 1548	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer11[36];                  // 15E8	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer12[20];                  // 1708	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer13[40];                  // 17A8	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer14[20];                  // 18E8	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer15[20];                  // 1988	-	ByteWidth: 16
			ID3D11Buffer* ConstantBuffer16[34];                  // 1A28	-	ByteWidth: 16
			ID3D11Buffer* perFrameConstantBuffer;                // 1B38	-	ByteWidth: 752
			ID3D11Buffer* computeConstantBuffer;                 // 1B40	-	ByteWidth: 576
			ID3D11Buffer* instanceTransformConstantBuffer;       // 1B48	-	ByteWidth: 65520
			BSGraphics::ConstantGroup miscConstantGroup;         // 1B50
			std::uint64_t gap1B68;                               // 1B68
			BSGraphics::RendererShadowState currentShadowState;  // 1B70
			BSGraphics::RendererShadowState lastShadowState;     // 2480
			ID3D11Buffer* dynamicVertexBuffer[8];
			std::byte gap2DD0[96];
			std::uint32_t currentDynamicVertexBuffer;
			std::uint32_t currentDynamicVertexBufferOffset;
			ID3D11Buffer* sharedParticleIndexBuffer;
			ID3D11Buffer* sharedParticleStaticBuffer;
			std::byte gap2E48[360];
			BSTHashMap<std::uint64_t, ID3D11InputLayout*> inputLayoutMap;
			ID3D11InputLayout* particleShaderInputLayout;
			std::byte gap2FE8[8];
		};
		static_assert(offsetof(Context, currentShadowState) == 0x1B70);
		static_assert(offsetof(Context, lastShadowState) == 0x2480);
		static_assert(sizeof(Context) == 0x2FF0);

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
