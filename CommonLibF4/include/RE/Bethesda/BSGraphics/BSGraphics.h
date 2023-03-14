#pragma once
#include "RE/Bethesda/BSGraphics/BSGraphicsTypes.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTList.h"
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
			std::int32_t CurrentRenderTargetIndex;         // 000
			std::int32_t CurrentDepthStencilTargetIndex;   //
			std::int32_t CurrentCubeMapRenderTargetIndex;  //
			D3D11_VIEWPORT ViewPort;                       //
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

		class Context
		{
		public:
			//members
		};
		//static_assert(sizeof(Context) == 0x2FF0);

		enum DepthStencilExtraMode : std::int32_t
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

	};
	//static_assert(std::is_empty_v<BSGraphics>);
}
