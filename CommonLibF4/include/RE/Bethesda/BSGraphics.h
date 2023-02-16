#pragma once

#include "RE/Bethesda/BSTHashMap.h"

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

	struct DXGI_RATIONAL
	{
	public:
		// members
		std::uint32_t numerator;    // 00
		std::uint32_t denominator;  // 04
	};
	static_assert(sizeof(DXGI_RATIONAL) == 0x08);

	struct BSGraphics
	{
		enum class TextureAddressMode;

		struct Vertex
		{
			enum Attribute : std::uint8_t
			{
				VA_POSITION = 0x0,
				VA_TEXCOORD0 = 0x1,
				VA_TEXCOORD1 = 0x2,
				VA_NORMAL = 0x3,
				VA_BINORMAL = 0x4,
				VA_COLOR = 0x5,
				VA_SKINNING = 0x6,
				VA_LANDDATA = 0x7,
				VA_EYEDATA = 0x8,

				VA_COUNT = 9
			};

			enum Flags : std::uint16_t
			{
				VF_VERTEX = 1 << VA_POSITION,
				VF_UV = 1 << VA_TEXCOORD0,
				VF_UV_2 = 1 << VA_TEXCOORD1,
				VF_NORMAL = 1 << VA_NORMAL,
				VF_TANGENT = 1 << VA_BINORMAL,
				VF_COLORS = 1 << VA_COLOR,
				VF_SKINNED = 1 << VA_SKINNING,
				VF_LANDDATA = 1 << VA_LANDDATA,
				VF_EYEDATA = 1 << VA_EYEDATA,
				VF_FULLPREC = 0x400
			};

			enum Masks : std::uint64_t
			{
				DESC_MASK_VERT = 0xFFFFFFFFFFFFFFF0,
				DESC_MASK_UVS = 0xFFFFFFFFFFFFFF0F,
				DESC_MASK_NBT = 0xFFFFFFFFFFFFF0FF,
				DESC_MASK_SKCOL = 0xFFFFFFFFFFFF0FFF,
				DESC_MASK_DATA = 0xFFFFFFFFFFF0FFFF,
				DESC_MASK_OFFSET = 0xFFFFFF0000000000,
				DESC_MASK_FLAGS = ~(DESC_MASK_OFFSET)
			};
		};

		class VertexDesc
		{
		public:
			[[nodiscard]] bool HasFlag(Vertex::Flags a_flag) const
			{
				return ((desc >> 44) & a_flag) != 0;
			}
			void SetFlag(Vertex::Flags a_flag)
			{
				desc |= (static_cast<uint64_t>(a_flag) << 44);
			}
			void ClearFlag(Vertex::Flags a_flag)
			{
				desc &= ~(static_cast<uint64_t>(a_flag) << 44);
			}

			[[nodiscard]] std::uint32_t GetAttributeOffset(Vertex::Attribute a_attribute) const
			{
				return (desc >> (4 * static_cast<uint8_t>(a_attribute) + 2)) & 0x3C;
			}
			void SetAttributeOffset(Vertex::Attribute a_attribute, std::uint32_t a_offset)
			{
				if (a_attribute != Vertex::Attribute::VA_POSITION) {
					const uint64_t lhs = static_cast<uint64_t>(a_offset) << (4 * static_cast<uint8_t>(a_attribute) + 2);
					const uint64_t rhs = desc & ~static_cast<uint64_t>(15 << (4 * static_cast<uint8_t>(a_attribute) + 4));

					desc = lhs | rhs;
				}
			}
			void ClearAttributeOffsets()
			{
				desc &= Vertex::Masks::DESC_MASK_OFFSET;
			}

			[[nodiscard]] Vertex::Flags GetFlags() const
			{
				return static_cast<Vertex::Flags>((desc & Vertex::Masks::DESC_MASK_OFFSET) >> 44);
			}
			void SetFlags(Vertex::Flags a_flags)
			{
				desc |= (static_cast<uint64_t>(a_flags) << 44) | (desc & Vertex::Masks::DESC_MASK_FLAGS);
			}

			[[nodiscard]] std::uint32_t GetSize()
			{
				/*std::uint32_t vertexSize = 0;
				auto          flags = GetFlags();
				if (flags & Vertex::VF_VERTEX) {
					vertexSize += sizeof(std::uint16_t) * 4; //Fallout 4 uses half precision for vertex coordinates
				}
				if (flags & Vertex::VF_UV) {
					vertexSize += sizeof(std::uint16_t) * 2;
				}
				if (flags & Vertex::VF_UV_2) {
					vertexSize += sizeof(std::uint16_t) * 2;
				}
				if (flags & Vertex::VF_NORMAL) {
					vertexSize += sizeof(std::uint16_t) * 2;
					if (flags & Vertex::VF_TANGENT) {
						vertexSize += sizeof(std::uint16_t) * 2;
					}
				}
				if (flags & Vertex::VF_COLORS) {
					vertexSize += sizeof(std::uint8_t) * 4;
				}
				if (flags & Vertex::VF_SKINNED) {
					vertexSize += sizeof(std::uint16_t) * 4 + sizeof(std::uint8_t) * 4;
				}
				if (flags & Vertex::VF_EYEDATA) {
					vertexSize += sizeof(std::uint16_t);
				}
				return vertexSize;*/
				return (desc & 0xF) * 4;
			}

		private:
			// members
			std::uint64_t desc;  // 00
		};
		static_assert(sizeof(VertexDesc) == 0x8);

		enum RenderTargetMode
		{
			RENDER_TARGET_FRAMEBUFFER = 0x0,
			RENDER_TARGET_FRAMEBUFFER_COUNT = 0x1,
			RENDER_TARGET_MAIN = 0x1,
			RENDER_TARGET_MAIN_COPY = 0x2,
			RENDER_TARGET_MAIN_SAVE_RES = 0x3,
			RENDER_TARGET_SSR_PREPASS = 0x4,
			RENDER_TARGET_SSR = 0x5,
			RENDER_TARGET_SSR_BLURRED0 = 0x6,
			RENDER_TARGET_SSR_BLURRED1 = 0x7,
			RENDER_TARGET_SSR_DEPTH = 0x8,
			RENDER_TARGET_SSR_BLEND = 0x9,
			RENDER_TARGET_WATER_DISPLACEMENT = 0xA,
			RENDER_TARGET_WATER_DISPLACEMENT_SWAP = 0xB,
			RENDER_TARGET_WATER_REFLECTIONS = 0xC,
			RENDER_TARGET_WATER_REFRACTION = 0xD,
			RENDER_TARGET_REFRACTION_NORMALS = 0xE,
			RENDER_TARGET_MENUBG = 0xF,
			RENDER_TARGET_VATS_MASK = 0xF,
			RENDER_TARGET_FACE_CUSTOMIZATION_DIFFUSE = 0x10,
			RENDER_TARGET_FACE_CUSTOMIZATION_NORMALS = 0x11,
			RENDER_TARGET_FACE_CUSTOMIZATION_SMOOTHSPEC = 0x12,
			RENDER_TARGET_LOCAL_MAP = 0x13,
			RENDER_TARGET_COMPANION_LOCAL_MAP = 0x14,
			RENDER_TARGET_COMPANION_LOCAL_MAP_NORM = 0x15,
			RENDER_TARGET_FOG_OF_WAR = 0x16,
			RENDER_TARGET_COMPANION_FOG_OF_WAR = 0x17,
			RENDER_TARGET_HUDGLASS = 0x18,
			RENDER_TARGET_HUDGLASS_SWAP = 0x19,
			RENDER_TARGET_GB_ALBEDO_SPEC = 0x1A,
			RENDER_TARGET_GB_NORMAL = 0x1B,
			RENDER_TARGET_GB_NORMAL_COPY = 0x1C,
			RENDER_TARGET_GB_ENVMAP = 0x1D,
			RENDER_TARGET_GB_AMBIENT_MAT = 0x1E,
			RENDER_TARGET_GB_EMIT = 0x1F,
			RENDER_TARGET_GB_MOTION_VECTORS = 0x20,
			RENDER_TARGET_DFLIGHT = 0x21,
			RENDER_TARGET_DFSPECULAR = 0x22,
			RENDER_TARGET_DFLIGHT_TILED = 0x23,
			RENDER_TARGET_DFSPECULAR_TILED = 0x24,
			RENDER_TARGET_AO = 0x25,
			RENDER_TARGET_AO_SWAP_0 = 0x26,
			RENDER_TARGET_AO_2X = 0x27,
			RENDER_TARGET_SAO_CAMERAZ = 0x28,
			RENDER_TARGET_SAO_CAMERAZ_MIP_LEVEL_0 = 0x29,
			RENDER_TARGET_SAO_CAMERAZ_MIP_LEVEL_1 = 0x2A,
			RENDER_TARGET_SAO_CAMERAZ_MIP_LEVEL_2 = 0x2B,
			RENDER_TARGET_SAO_CAMERAZ_MIP_LEVEL_3 = 0x2C,
			RENDER_TARGET_SAO_CAMERAZ_MIP_LEVEL_4 = 0x2D,
			RENDER_TARGET_SAO_CAMERAZ_MIP_LEVEL_5 = 0x2E,
			RENDER_TARGET_SAO_CAMERAZ_MIP_LEVEL_6 = 0x2F,
			RENDER_TARGET_SAO_CAMERAZ_MIP_LEVEL_7 = 0x30,
			RENDER_TARGET_SAO_CAMERAZ_MIP_LEVEL_8 = 0x31,
			RENDER_TARGET_SAO_CAMERAZ_MIP_LEVEL_9 = 0x32,
			RENDER_TARGET_SAO_CAMERAZ_MIP_LEVEL_10 = 0x33,
			RENDER_TARGET_SAO_RAW_AO = 0x34,
			RENDER_TARGET_SAO_RAW_AO_2 = 0x35,
			RENDER_TARGET_SAO_TEMP_BLUR = 0x36,
			RENDER_TARGET_SAO_RAW_AO_2X = 0x37,
			RENDER_TARGET_SAO_RAW_AO_2_2X = 0x38,
			RENDER_TARGET_SAO_TEMP_BLUR_2X = 0x39,
			RENDER_TARGET_TEMPORAL_AA_ACCUMULATION_1 = 0x3A,
			RENDER_TARGET_TEMPORAL_AA_ACCUMULATION_2 = 0x3B,
			RENDER_TARGET_PIPBOY = 0x3C,
			RENDER_TARGET_PIPBOY_SWAP = 0x3D,
			RENDER_TARGET_MENU_SCREEN_FULLSIZE = 0x3E,
			RENDER_TARGET_MENU_SCREEN_FULLSIZE_SWAP = 0x3F,
			RENDER_TARGET_MENU_TEXT = 0x40,
			RENDER_TARGET_LENSFLAREVIS = 0x41,
			RENDER_TARGET_GETHIT_BUFFER = 0x42,
			RENDER_TARGET_BLURFULL_BUFFER = 0x43,
			RENDER_TARGET_HDR_BLURSWAP = 0x44,
			RENDER_TARGET_HDR_BLOOM = 0x45,
			RENDER_TARGET_HDR_DOWNSAMPLE0 = 0x46,
			RENDER_TARGET_HDR_DOWNSAMPLE1 = 0x47,
			RENDER_TARGET_HDR_DOWNSAMPLE2 = 0x48,
			RENDER_TARGET_HDR_DOWNSAMPLE3 = 0x49,
			RENDER_TARGET_HDR_DOWNSAMPLE4 = 0x4A,
			RENDER_TARGET_HDR_DOWNSAMPLE5 = 0x4B,
			RENDER_TARGET_HDR_DOWNSAMPLE6 = 0x4C,
			RENDER_TARGET_HDR_DOWNSAMPLE7 = 0x4D,
			RENDER_TARGET_HDR_DOWNSAMPLE8 = 0x4E,
			RENDER_TARGET_HDR_DOWNSAMPLE9 = 0x4F,
			RENDER_TARGET_HDR_DOWNSAMPLE10 = 0x50,
			RENDER_TARGET_HDR_DOWNSAMPLE11 = 0x51,
			RENDER_TARGET_HDR_DOWNSAMPLE12 = 0x52,
			RENDER_TARGET_HDR_DOWNSAMPLE13 = 0x53,
			RENDER_TARGET_DOF_1 = 0x54,
			RENDER_TARGET_DOF_2 = 0x55,
			RENDER_TARGET_RAIN_OCCLUSIONMAP = 0x56,
			RENDER_TARGET_EDITOR_TERRAIN_TEXTURE_GENERATION = 0x57,
			RENDER_TARGET_EDITOR_TERRAIN_TEXTURE_GENERATION_FINAL = 0x58,
			RENDER_TARGET_EDITOR_MAP_MAKER = 0x59,
			RENDER_TARGET_EDITOR_MAP_MAKER_SWAP = 0x5A,
			RENDER_TARGET_GODRAYS_PHASE_LUT = 0x5B,
			RENDER_TARGET_GODRAYS_ACCUMULATION = 0x5C,
			RENDER_TARGET_GODRAYS_RESOLVED = 0x5D,
			RENDER_TARGET_GODRAYS_RESOLVED_DEPTH = 0x5E,
			RENDER_TARGET_GODRAYS_FILTERED_0 = 0x5F,
			RENDER_TARGET_GODRAYS_FILTERED_1 = 0x60,
			RENDER_TARGET_GODRAYS_FILTERED_DEPTH_0 = 0x61,
			RENDER_TARGET_GODRAYS_FILTERED_DEPTH_1 = 0x62,
			RENDER_TARGET_MONITOR_SCREENSHOT = 0x63,

			RENDER_TARGET_COUNT
		};

		enum RenderTargetCubeMapMode
		{
			RENDER_TARGET_CUBEMAP_REFLECTIONS,

			RENDER_TARGET_CUBEMAP_COUNT
		};

		enum DepthStencilDepthMode
		{
			DEPTH_STENCIL_NONE,
			DEPTH_STENCIL_MAIN_DEPTH,
			DEPTH_STENCIL_MAIN_DEPTH_HALF,
			DEPTH_STENCIL_PIPBOY,
			DEPTH_STENCIL_VATS,
			DEPTH_STENCIL_SHADOW_MAP,
			DEPTH_STENCIL_SHADOW_MAP_ARRAY,
			DEPTH_STENCIL_CUBEMAP_REFLECTIONS,
			DEPTH_STENCIL_RAIN_OCCLUSION_MAP,
			DEPTH_STENCIL_VLS_SLICE_STENCIL,
			DEPTH_STENCIL_GODRAYS_DEPTH,
			DEPTH_STENCIL_COMPANION_LOCAL_MAP_DEPTH,

			DEPTH_STENCIL_COUNT
		};

		enum SetRenderTargetMode : std::uint32_t
		{  //Unconfirmed
			SRTM_CLEAR = 0x0,
			SRTM_CLEAR_DEPTH = 0x1,
			SRTM_CLEAR_STENCIL = 0x2,
			SRTM_RESTORE = 0x3,
			SRTM_NO_CLEAR = 0x4,
			SRTM_FORCE_COPY_RESTORE = 0x5,
			SRTM_INIT = 0x6,
		};

		enum Format
		{

		};

		enum Usage
		{  //Uncomfirmed
			USAGE_DEFAULT = 0,
			USAGE_IMMUTABLE = 1,
			USAGE_DYNAMIC = 2,
			USAGE_STAGING = 3  //ScreenShot::GetScreenShotData calls ScreenShot::BufferScreenShot using this
		};

		class RendererShadowState
		{
		public:
		};

		class TextureHeader
		{
		public:
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
		};

		class ViewData
		{
		public:
			NiPoint2 Unk0;
			NiPoint2 Unk8;
			NiPoint2 Unk10;
		};

		struct Buffer
		{
			uint64_t unk00;
			uint64_t rawVertexData;
		};

		struct TriShape
		{
			VertexDesc vertexDesc;
			Buffer* buffer08;
			Buffer* buffer10;
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
			std::uint32_t id{ 0 };                         // 00
			ID3D11ComputeShader* shader{ nullptr };        // 08
			std::uint32_t byteCodeSize{ 0 };               // 10
			BSGraphics::ConstantGroup constantBuffers[3];  // 18
			std::uint64_t shaderDesc{ 0 };                 // 60
			std::int8_t constantTable[32]{ 0 };            // 68
		};
		static_assert(sizeof(ComputeShader) == 0x88);

		class DomainShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                              // 00
			ID3D11DomainShader* shader{ nullptr };              // 08
			std::uint32_t byteCodeSize{ 0 };                    // 10
			BSGraphics::ConstantGroup constantBuffers[3]{ 0 };  // 18
			std::uint64_t shaderDesc{ 0 };                      // 60
			std::int8_t constantTable[32]{ 0 };                 // 68
		};
		static_assert(sizeof(DomainShader) == 0x88);

		class HullShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                         // 00
			ID3D11HullShader* shader{ nullptr };           // 08
			std::uint32_t byteCodeSize{ 0 };               // 10
			BSGraphics::ConstantGroup constantBuffers[3];  // 18
			std::uint64_t shaderDesc{ 0 };                 // 60
			std::int8_t constantTable[32]{ 0 };            // 68
		};
		static_assert(sizeof(HullShader) == 0x88);

		class PixelShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                         // 00
			ID3D11PixelShader* shader{ nullptr };          // 08
			BSGraphics::ConstantGroup constantBuffers[3];  // 10
			std::int8_t constantTable[32]{ 0 };            // 58
		};
		static_assert(sizeof(PixelShader) == 0x78);

		class VertexShader
		{
		public:
			// members
			std::uint32_t id{ 0 };                         // 00
			ID3D11VertexShader* shader{ nullptr };         // 08
			std::uint32_t byteCodeSize{ 0 };               // 10
			BSGraphics::ConstantGroup constantBuffers[3];  // 18
			std::uint64_t shaderDesc{ 0 };                 // 60
			std::int8_t constantTable[32]{ 0 };            // 68
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

		struct RenderTargetProperties
		{
			std::uint32_t uiWidth;
			std::uint32_t uiHeight;
			DXGI_FORMAT eFormat;
			bool bCopyable;
			bool bSupportUnorderedAccess;
			bool bAllowMipGeneration;
			std::int32_t iMipLevel;
			std::uint32_t uiTextureTarget;
			std::uint32_t uiUnknown;
		};
		static_assert(sizeof(RenderTargetProperties) == 0x1C);

		struct DepthStencilTargetProperties
		{
			std::uint32_t uiWidth;
			std::uint32_t uiHeight;
			std::uint32_t uiArraySize;
			bool Unknown1;
			bool Stencil;
			bool Use16BitsDepth;
		};
		static_assert(sizeof(DepthStencilTargetProperties) == 0x10);

		struct CubeMapRenderTargetProperties
		{
			std::uint32_t uiWidth;
			std::uint32_t uiHeight;
			DXGI_FORMAT eFormat;
		};
		static_assert(sizeof(CubeMapRenderTargetProperties) == 0xC);

		class RendererWindow
		{
		public:
			void* hwnd;
			std::int32_t windowX;
			std::int32_t windowY;
			std::int32_t windowWidth;
			std::int32_t windowHeight;
			IDXGISwapChain* swapChain;
			RenderTarget swapChainRenderTarget;
		};
		static_assert(sizeof(RendererWindow) == 0x50);

		class RendererData
		{
		public:
			[[nodiscard]] static RendererData* GetSingleton()
			{
				REL::Relocation<RendererData**> singleton{ REL::ID(1235449) };
				return *singleton;
			}

			// members
			RendererShadowState* shadowState;             // 0000
			BSD3DResourceCreator* resourceCreator;        // 0008
			std::uint32_t adapter;                        // 0010
			DXGI_RATIONAL desiredRefreshRate;             // 0014
			DXGI_RATIONAL actualRefreshRate;              // 001C
			DXGI_MODE_SCALING scaleMode;                  // 0024
			DXGI_MODE_SCANLINE_ORDER scanlineMode;        // 0028
			std::int32_t fullScreen;                      // 002C
			bool appFullScreen;                           // 0030
			bool borderlessWindow;                        // 0031
			bool vsync;                                   // 0032
			bool initialized;                             // 0033
			bool requestWindowSizeChange;                 // 0034
			std::uint32_t newWidth;                       // 0038
			std::uint32_t newHeight;                      // 003C
			std::uint32_t presentInterval;                // 0040
			ID3D11Device* device;                         // 0048
			ID3D11DeviceContext* context;                 // 0050
			RendererWindow renderWindow[32];              // 0058
			RenderTarget renderTargets[101];              // 0A58
			DepthStencilTarget depthStencilTargets[13];   // 1D48
			CubeMapRenderTarget cubeMapRenderTargets[2];  // 2500
			std::byte rendererLock[0x25A8 - 0x2580];      // 2580 - TODO
			const char* className;                        // 25A8
			void* instance;                               // 25B0
			bool nvapiEnabled;                            // 25B8
		};
		static_assert(sizeof(RendererData) == 0x25C0);

		class Renderer
		{
		private:
			using ResetRenderTargets_t = void (*)();

		public:
			void IncRef(Buffer* vertexBuffer)
			{
				using func_t = decltype(&BSGraphics::Renderer::IncRef);
				REL::Relocation<func_t> func{ REL::ID(1337764) };
				return func(this, vertexBuffer);
			}

			void DecRef(Buffer* vertexBuffer)
			{
				using func_t = decltype(&BSGraphics::Renderer::DecRef);
				REL::Relocation<func_t> func{ REL::ID(194808) };
				return func(this, vertexBuffer);
			}

			void ClearColor()
			{
				using func_t = decltype(&BSGraphics::Renderer::ClearColor);
				REL::Relocation<func_t> func{ REL::ID(673185) };
				return func(this);
			}

			Texture* CreateEmptyTexture(std::uint32_t width, std::uint32_t height)
			{
				using func_t = decltype(&BSGraphics::Renderer::CreateEmptyTexture);
				REL::Relocation<func_t> func{ REL::ID(1024513) };
				return func(this, width, height);
			}

			void DoZPrePass(NiCamera* cam1, NiCamera* cam2, float a1, float a2, float a3, float a4)
			{
				using func_t = decltype(&BSGraphics::Renderer::DoZPrePass);
				REL::Relocation<func_t> func{ REL::ID(1491502) };
				return func(this, cam1, cam2, a1, a2, a3, a4);
			}

			void Flush()
			{
				using func_t = decltype(&BSGraphics::Renderer::Flush);
				REL::Relocation<func_t> func{ REL::ID(952687) };
				return func(this);
			}

			void SetClearColor(float red, float green, float blue, float alpha)
			{
				using func_t = decltype(&BSGraphics::Renderer::SetClearColor);
				REL::Relocation<func_t> func{ REL::ID(1391151) };
				return func(this, red, green, blue, alpha);
			}

			void ResetZPrePass()
			{
				using func_t = decltype(&BSGraphics::Renderer::ResetZPrePass);
				REL::Relocation<func_t> func{ REL::ID(1359409) };
				return func(this);
			}

			void ResetState()
			{
				using func_t = decltype(&BSGraphics::Renderer::ResetState);
				REL::Relocation<func_t> func{ REL::ID(405603) };
				return func(this);
			}

			// members
			bool skipNextPresent;                     // 00
			ResetRenderTargets_t resetRenderTargets;  // 08
			RendererData data;                        // 10
		};
		static_assert(sizeof(Renderer) == 0x25D0);

		class State
		{
		public:
			void SetCameraData(NiCamera* cam, bool a3, float a4, float a5)
			{
				using func_t = decltype(&BSGraphics::State::SetCameraData);
				REL::Relocation<func_t> func{ REL::ID(185153) };
				return func(this, cam, a3, a4, a5);
			}
		};

		class Context
		{
		public:
		};
		//static_assert(sizeof(Context) == 0x2FF0);

		class OcclusionQuery
		{
		public:
		};

		class RenderTargetManager
		{
		private:
			using CreateRenderTargets_t = void (*)();

		public:
#define MAX_RENDER_TARGETS 0x64
#define MAX_DEPTH_STENCIL_TARGETS 0xC
#define MAX_CUBEMAP_RENDER_TARGETS 0x1

			enum TARGET_PERSISTENCY
			{
				TARGET_PERSISTENCY_ALWAYS,
			};

			void AcquireCubemap(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::AcquireCubemap);
				REL::Relocation<func_t> func{ REL::ID(563587) };
				return func(this, target);
			}

			void AcquireDepthStencil(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::AcquireDepthStencil);
				REL::Relocation<func_t> func{ REL::ID(1015879) };
				return func(this, target);
			}

			void AcquireRenderTarget(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::AcquireDepthStencil);
				REL::Relocation<func_t> func{ REL::ID(1468639) };
				return func(this, target);
			}

			void CopyRenderTargetToClipboard(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CopyRenderTargetToClipboard);
				REL::Relocation<func_t> func{ REL::ID(1295596) };
				return func(this, target);
			}

			void CopyRenderTargetToRenderTargetCopy(std::uint32_t target, std::uint32_t target2)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CopyRenderTargetToRenderTargetCopy);
				REL::Relocation<func_t> func{ REL::ID(591200) };
				return func(this, target, target2);
			}

			void CopyRenderTargetToTexture(std::uint32_t target, Texture* tex, bool a3, bool a4)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CopyRenderTargetToTexture);
				REL::Relocation<func_t> func{ REL::ID(1561984) };
				return func(this, target, tex, a3, a4);
			}

			void CreateCubeMapRenderTarget(std::uint32_t target, CubeMapRenderTargetProperties& cubeProps, TARGET_PERSISTENCY persist)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CreateCubeMapRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(1397856) };
				return func(this, target, cubeProps, persist);
			}

			void CreateDepthStencilTarget(std::uint32_t target, DepthStencilTargetProperties& depthProps, TARGET_PERSISTENCY persist)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CreateDepthStencilTarget);
				REL::Relocation<func_t> func{ REL::ID(1159619) };
				return func(this, target, depthProps, persist);
			}

			void CreateRenderTarget(std::uint32_t target, RenderTargetProperties& targetProps, TARGET_PERSISTENCY persist)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CreateRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(43433) };
				return func(this, target, targetProps, persist);
			}

			void ReleaseCubemap(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::ReleaseCubemap);
				REL::Relocation<func_t> func{ REL::ID(469959) };
				return func(this, target);
			}

			void ReleaseDepthStencil(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::ReleaseDepthStencil);
				REL::Relocation<func_t> func{ REL::ID(922599) };
				return func(this, target);
			}

			void ReleaseRenderTarget(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::ReleaseRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(1374956) };
				return func(this, target);
			}

			Texture* SaveRenderTargetToTexture(std::uint32_t target, bool a1, bool a2, Usage use)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SaveRenderTargetToTexture);
				REL::Relocation<func_t> func{ REL::ID(950217) };
				return func(this, target, a1, a2, use);
			}

			void SetCurrentRenderTarget(std::uint32_t target, std::uint32_t targetIndex, SetRenderTargetMode mode)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetCurrentRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(1502425) };
				return func(this, target, targetIndex, mode);
			}

			void SetCurrentDepthStencilTarget(std::uint32_t a1, SetRenderTargetMode mode, std::uint32_t a2, bool a3)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetCurrentDepthStencilTarget);
				REL::Relocation<func_t> func{ REL::ID(704517) };
				return func(this, a1, mode, a2, a3);
			}

			void SetCurrentViewportForceToRenderTargetDimensions()
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetCurrentViewportForceToRenderTargetDimensions);
				REL::Relocation<func_t> func{ REL::ID(1208720) };
				return func(this);
			}

			void SetTextureRenderTarget(std::uint32_t a1, std::uint32_t a2, bool a3)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetTextureRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(1433009) };
				return func(this, a1, a2, a3);
			}

			void SetTextureDepth(std::uint32_t a1, std::uint32_t a2)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetTextureDepth);
				REL::Relocation<func_t> func{ REL::ID(182949) };
				return func(this, a1, a2);
			}

			//members
			RenderTargetProperties pRenderTargetDataA[100];
			DepthStencilTargetProperties pDepthStencilTargetDataA[12];
			CubeMapRenderTargetProperties pCubeMapRenderTargetDataA[1];
			std::uint8_t gapD50[568];
			float Width;
			float Height;
			float dynamicWidth;
			float dynamicHeight;
			float IncreaseSpeed;
			float DecreaseSpeed;
			float deltaMovement;
			bool increaseResolution;
			bool bDynamicResolution;
			bool bResolutionDontGrowOnPlayerMove;
			std::uint8_t field_FA7;
			std::uint32_t field_FA8;
			std::uint32_t uiResolutionGrowEveryFrame;
			std::uint8_t gapFB0[8];
			CreateRenderTargets_t createRenderTargets;
		};
	};
	static_assert(std::is_empty_v<BSGraphics>);

	REL::Relocation<BSGraphics::RenderTargetManager*> BSGraphics__gRenderTargetManager{ REL::ID(1508457) };
	REL::Relocation<BSGraphics::Context*> BSGraphics__pDefaultContext{ REL::ID(33539) };
	REL::Relocation<BSGraphics::Renderer> BSGraphics__gRenderer{ REL::ID(1378294) };
	REL::Relocation<BSGraphics::RendererData*> BSGraphics__pRendererData{ REL::ID(1235449) };
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
