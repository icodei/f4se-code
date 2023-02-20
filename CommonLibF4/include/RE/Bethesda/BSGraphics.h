#pragma once
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSTList.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiPoint2.h"
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
		enum AlphaBlendAlphaToCoverage : std::int32_t
		{
			ALPHA_BLEND_ALPHA_TO_COVERAGE_DISABLED = 0x0,
			ALPHA_BLEND_ALPHA_TO_COVERAGE_ENABLED = 0x1,
			ALPHA_BLEND_ALPHA_TO_COVERAGE_COUNT = 0x2,
			ALPHA_BLEND_ALPHA_TO_COVERAGE_DEFAULT = 0x0,
		};

		enum AlphaBlendMode : std::int32_t
		{
			ALPHA_BLEND_MODE_DISABLED = 0x0,
			ALPHA_BLEND_MODE_SRCALPHA_INVSRCALPHA = 0x1,
			ALPHA_BLEND_MODE_SRCALPHA_ONE = 0x2,
			ALPHA_BLEND_MODE_DEST_ZERO = 0x3,
			ALPHA_BLEND_MODE_ONE_INVSRCALPHA = 0x4,
			ALPHA_BLEND_MODE_ONE_ONE = 0x5,
			ALPHA_BLEND_MODE_WEAPON_BLOOD = 0x6,
			ALPHA_BLEND_MODE_COUNT = 0x7,
			ALPHA_BLEND_MODE_DEFAULT = 0x0,
		};

		enum AlphaBlendWriteMode : std::int32_t
		{
			ALPHA_BLEND_WRITE_MODE_DISABLED = 0x0,
			ALPHA_BLEND_WRITE_MODE_RGB = 0x1,
			ALPHA_BLEND_WRITE_MODE_RGBA = 0x2,
			ALPHA_BLEND_WRITE_MODE_RG = 0x3,
			ALPHA_BLEND_WRITE_MODE_BA = 0x4,
			ALPHA_BLEND_WRITE_MODE_R = 0x5,
			ALPHA_BLEND_WRITE_MODE_G = 0x6,
			ALPHA_BLEND_WRITE_MODE_B = 0x7,
			ALPHA_BLEND_WRITE_MODE_A = 0x8,
			ALPHA_BLEND_WRITE_MODE_A_TARGET0 = 0x9,
			ALPHA_BLEND_WRITE_MODE_A_TARGET1 = 0xA,
			ALPHA_BLEND_WRITE_MODE_A_TARGET2 = 0xB,
			ALPHA_BLEND_WRITE_MODE_A_TARGET3 = 0xC,
			ALPHA_BLEND_WRITE_MODE_COUNT = 0xD,
			ALPHA_BLEND_WRITE_MODE_DEFAULT = 0x1,
		};

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

		enum TextureAddressMode
		{
			TEXTURE_ADDRESS_MODE_CLAMP_S_CLAMP_T,
			TEXTURE_ADDRESS_MODE_CLAMP_S_WRAP_T,
			TEXTURE_ADDRESS_MODE_WRAP_S_CLAMP_T,
			TEXTURE_ADDRESS_MODE_WRAP_S_WRAP_T,

			TEXTURE_ADDRESS_MODE_COUNT,
		};

		enum TextureFilterMode
		{
			TEXTURE_FILTER_MODE_NEAREST,
			TEXTURE_FILTER_MODE_BILERP,
			TEXTURE_FILTER_MODE_TRILERP,
			TEXTURE_FILTER_MODE_ANISO,
			TEXTURE_FILTER_MODE_COMP_BILERP,

			TEXTURE_FILTER_MODE_COUNT,
		};

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

			RENDER_TARGET_COUNT,
		};

		enum RenderTargetCubeMapMode : std::uint32_t
		{
			RENDER_TARGET_CUBEMAP_NONE = 0xFFFFFFFF,
			RENDER_TARGET_CUBEMAP_REFLECTIONS = 0x0,
			RENDER_TARGET_CUBEMAP_COUNT = 0x1,
		};

		enum DepthStencilStencilMode : std::int32_t
		{
			DEPTH_STENCIL_STENCIL_MODE_DEFAULT = 0x0,

			DEPTH_STENCIL_STENCIL_MODE_DISABLED = 0x0,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_ALWAYS_REPLACE = 0x1,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_ALWAYS_REPLACE_WM00000001 = 0x2,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_ALWAYS_REPLACE_WM00000010 = 0x3,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_ALWAYS_REPLACE_WM00000100 = 0x4,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_ALWAYS_REPLACE_WM00001000 = 0x5,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_ALWAYS_REPLACE_WM00010000 = 0x6,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_ALWAYS_REPLACE_WM00100000 = 0x7,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_ALWAYS_REPLACE_WM01000000 = 0x8,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_ALWAYS_REPLACE_WM10000000 = 0x9,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_ALWAYS_INCREMENT = 0xA,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_GREATER_KEEP = 0xB,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_KEEP = 0xC,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_KEEP_RM00000001 = 0xD,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_KEEP_RM00000010 = 0xE,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_KEEP_RM00000100 = 0xF,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_KEEP_RM00001000 = 0x10,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_KEEP_RM00010000 = 0x11,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_KEEP_RM00100000 = 0x12,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_KEEP_RM01000000 = 0x13,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_KEEP_RM10000000 = 0x14,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_REPLACE = 0x15,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_REPLACE_RM00000010 = 0x16,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_REPLACE_RM00000100 = 0x17,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_REPLACE_RM00001000 = 0x18,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_REPLACE_RM00010000 = 0x19,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_REPLACE_RM00100000 = 0x1A,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_REPLACE_RM01000000 = 0x1B,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_REPLACE_RM10000000 = 0x1C,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_NOT_EQUAL_REPLACE_RM00000001 = 0x1D,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_INCREMENT = 0x1E,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_INCREMENT_RM00000010 = 0x1F,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_INCREMENT_RM00000100 = 0x20,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_INCREMENT_RM00001000 = 0x21,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_INCREMENT_RM00010000 = 0x22,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_INCREMENT_RM00100000 = 0x23,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_INCREMENT_RM01000000 = 0x24,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_INCREMENT_RM10000000 = 0x25,
			DEPTH_STENCIL_STENCIL_MODE_ENABLED_EQUAL_REPLACE_WM00000000 = 0x26,

			DEPTH_STENCIL_STENCIL_MODE_COUNT
		};

		enum DepthStencilDepthMode : std::int32_t
		{
			DEPTH_STENCIL_DEPTH_MODE_DEFAULT = 0x3,

			DEPTH_STENCIL_DEPTH_MODE_DISABLED = 0x0,
			DEPTH_STENCIL_DEPTH_MODE_TEST = 0x1,
			DEPTH_STENCIL_DEPTH_MODE_WRITE = 0x2,
			DEPTH_STENCIL_DEPTH_MODE_TEST_WRITE = 0x3,
			DEPTH_STENCIL_DEPTH_MODE_TESTEQUAL = 0x4,
			DEPTH_STENCIL_DEPTH_MODE_TESTGREATEREQUAL = 0x5,
			DEPTH_STENCIL_DEPTH_MODE_TESTGREATER = 0x6,

			DEPTH_STENCIL_DEPTH_MODE_COUNT,
		};

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

		enum ClearDepthStencilTarget : std::int32_t
		{
			CLEAR_DEPTH_STENCIL_TARGET_DEPTH = 0x1,
			CLEAR_DEPTH_STENCIL_TARGET_STENCIL = 0x2,
			CLEAR_DEPTH_STENCIL_TARGET_ALL = 0x3,
		};

		enum SetRenderTargetMode : std::uint32_t
		{
			SRTM_CLEAR,
			SRTM_CLEAR_DEPTH,
			SRTM_CLEAR_STENCIL,
			SRTM_NO_CLEAR,
			SRTM_RESTORE,
			SRTM_FORCE_COPY_RESTORE,
			SRTM_INIT,
		};

		enum Format
		{
			FORMAT_NONE,
			FORMAT_R32G32B32A32_TYPELESS,
			FORMAT_R32G32B32A32_FLOAT,
			FORMAT_R32G32B32A32_UINT,
			FORMAT_R32G32B32A32_SINT,
			FORMAT_R32G32B32_TYPELESS,
			FORMAT_R32G32B32_FLOAT,
			FORMAT_R32G32B32_UINT,
			FORMAT_R32G32B32_SINT,
			FORMAT_R16G16B16A16_TYPELESS,
			FORMAT_R16G16B16A16_FLOAT,
			FORMAT_R16G16B16A16_UNORM,
			FORMAT_R16G16B16A16_UINT,
			FORMAT_R16G16B16A16_SNORM,
			FORMAT_R16G16B16A16_SINT,
			FORMAT_R32G32_TYPELESS,
			FORMAT_R32G32_FLOAT,
			FORMAT_R32G32_UINT,
			FORMAT_R32G32_SINT,
			FORMAT_R32G8X24_TYPELESS,
			FORMAT_D32_FLOAT_S8X24_UINT,
			FORMAT_R32_FLOAT_X8X24_TYPELESS,
			FORMAT_X32_TYPELESS_G8X24_UINT,
			FORMAT_R10G10B10A2_TYPELESS,
			FORMAT_R10G10B10A2_UNORM,
			FORMAT_R10G10B10A2_UINT,
			FORMAT_R11G11B10_FLOAT,
			FORMAT_R8G8B8A8_TYPELESS,
			FORMAT_R8G8B8A8_UNORM,
			FORMAT_R8G8B8A8_UNORM_SRGB,
			FORMAT_R8G8B8A8_UINT,
			FORMAT_R8G8B8A8_SNORM,
			FORMAT_R8G8B8A8_SINT,
			FORMAT_R16G16_TYPELESS,
			FORMAT_R16G16_FLOAT,
			FORMAT_R16G16_UNORM,
			FORMAT_R16G16_UINT,
			FORMAT_R16G16_SNORM,
			FORMAT_R16G16_SINT,
			FORMAT_R32_TYPELESS,
			FORMAT_D32_FLOAT,
			FORMAT_R32_FLOAT,
			FORMAT_R32_UINT,
			FORMAT_R32_SINT,
			FORMAT_R24G8_TYPELESS,
			FORMAT_D24_UNORM_S8_UINT,
			FORMAT_R24_UNORM_X8_TYPELESS,
			FORMAT_X24_TYPELESS_G8_UINT,
			FORMAT_R8G8_TYPELESS,
			FORMAT_R8G8_UNORM,
			FORMAT_R8G8_UINT,
			FORMAT_R8G8_SNORM,
			FORMAT_R8G8_SINT,
			FORMAT_R16_TYPELESS,
			FORMAT_R16_FLOAT,
			FORMAT_D16_UNORM,
			FORMAT_R16_UNORM,
			FORMAT_R16_UINT,
			FORMAT_R16_SNORM,
			FORMAT_R16_SINT,
			FORMAT_R8_TYPELESS,
			FORMAT_R8_UNORM,
			FORMAT_R8_UINT,
			FORMAT_R8_SNORM,
			FORMAT_R8_SINT,
			FORMAT_A8_UNORM,
			FORMAT_R1_UNORM,
			FORMAT_R9G9B9E5_SHAREDEXP,
			FORMAT_R8G8_B8G8_UNORM,
			FORMAT_G8R8_G8B8_UNORM,
			FORMAT_BC1_TYPELESS,
			FORMAT_BC1_UNORM,
			FORMAT_BC1_UNORM_SRGB,
			FORMAT_BC2_TYPELESS,
			FORMAT_BC2_UNORM,
			FORMAT_BC2_UNORM_SRGB,
			FORMAT_BC3_TYPELESS,
			FORMAT_BC3_UNORM,
			FORMAT_BC3_UNORM_SRGB,
			FORMAT_BC4_TYPELESS,
			FORMAT_BC4_UNORM,
			FORMAT_BC4_SNORM,
			FORMAT_BC5_TYPELESS,
			FORMAT_BC5_UNORM,
			FORMAT_BC5_SNORM,
			FORMAT_B5G6R5_UNORM,
			FORMAT_B5G5R5A1_UNORM,
			FORMAT_B8G8R8A8_UNORM,
			FORMAT_B8G8R8X8_UNORM,
			FORMAT_R10G10B10_XR_BIAS_A2_UNORM,
			FORMAT_B8G8R8A8_TYPELESS,
			FORMAT_B8G8R8A8_UNORM_SRGB,
			FORMAT_B8G8R8X8_TYPELESS,
			FORMAT_B8G8R8X8_UNORM_SRGB,
			FORMAT_BC6H_TYPELESS,
			FORMAT_BC6H_UF16,
			FORMAT_BC6H_SF16,
			FORMAT_BC7_TYPELESS,
			FORMAT_BC7_UNORM,
			FORMAT_BC7_UNORM_SRGB,

			FORMAT_COUNT
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
			const char* __ptr32 Name;
			const char* __ptr32 Definition;
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
			Format eFormat;
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
			std::int32_t CurrentRenderTargetIndex;
			std::int32_t CurrentDepthStencilTargetIndex;
			std::int32_t CurrentCubeMapRenderTargetIndex;
			D3D11_VIEWPORT ViewPort;
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

		struct __declspec(align(8)) CameraStateData
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
			using ResetRenderTargets = void (*)();

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
			ResetRenderTargets resetRenderTargets;  // 08
			RendererData data;                        // 10
		};
		static_assert(sizeof(Renderer) == 0x25D0);

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

			void CacheCameraData();	//TODO
			void UpdateAllPreviousFrameCameraData();	//TODO
			void SetFogState();	//TODO
			void CalculateCameraViewProj();	//TODO
			void SetScreenSpaceCameraData();	//TODO
			void SetCameraViewPort();	//TODO
			void GetBackBufferAspectRatio();	//TODO
			void GetWideScreen();	//TODO
			void CreateDefaultTextures();	//TODO
			void DestroyDefaultTextures();	//TODO
			void GetIsDefaultTexture();	//TODO
			void SetCommitTexturesOnCreation();	//TODO
			void QCommitTexturesOnCreation();	//TODO
			void SetImmediateTextureLoads();	//TODO
			void QImmediateTextureLoads();	//TODO
			void UpdateTemporalData();	//TODO
			static void Halton();	//TODO

			//public members
			std::uint32_t iCurrentFrame;								//000
			float fOffsetX;												//
			float fOffsetY;												//
			std::uint32_t iCurrentFrameOffset;							//
			std::uint32_t iPreviousFrameOffset;							//
			FogStateType FogState;										//
			MultiSampleLevel uiMultiSample;								//
			std::uint32_t uiBackBufferWidth;							//
			std::uint32_t uiBackBufferHeight;							//
			std::uint32_t uiScreenWidth;								//
			std::uint32_t uiScreenHeight;								//
			NiRect<float> kFrameBufferViewport;							//
			std::uint32_t uiFrameCount;									//
			std::uint32_t uiFrameID;									//
			bool bInsideFrame;											//
			bool bLetterbox;											//
			bool bAllowDepthBufferAsTexture;							//
			bool bShadows;												//
			bool bCompiledShaderThisFrame;								//
			TAA_STATE TaaState;											//
			std::uint32_t TaaDisableCounter;							//
			std::uint32_t TrijuiceState;								//
			NiPointer<NiTexture> pDefaultTextureBlack;					//
			NiPointer<NiTexture> pDefaultTextureWhite;					//
			NiPointer<NiTexture> pDefaultTextureGrey;					//
			NiPointer<NiTexture> pDefaultHeightMap;						//
			NiPointer<NiTexture> pDefaultReflectionCubeMap;				//
			NiPointer<NiTexture> pDefaultFaceDetailMap;					//
			NiPointer<NiTexture> pDefaultHighFreqNormalMap;				//
			NiPointer<NiTexture> pDefaultTexEffectMap;					//
			NiPointer<NiTexture> pDefaultTextureWhiteNoiseMap;			//
			NiPointer<NiTexture> pDefaultTextureWhiteNoiseMapSmall;		//
			NiPointer<NiTexture> pDefaultTextureNormalMap;				//
			NiPointer<NiTexture> pDefaultTextureDiffuseMap;				//
			NiPointer<NiTexture> pDefaultSplineMap;						//
			NiPointer<NiTexture> pDefaultTextureDissolvePattern;		//
			Texture* pDefaultImagespaceLUT;								//
			NiPointer<NiTexture> pRotatedPoissonDiscLookupMap;			//
			std::uint32_t PresentImmediateThreshold;					//
			std::uint32_t PresentFlag;									//
			//In the PDB private starts here
			//private:
			void BuildCameraStateData();	//TODO
			void ApplyCameraStateData();	//TODO
			void UpdatePreviousFrameCameraData();	//TODO
			void FindCameraStateData();		//TODO

			//private members
			BSTArray<CameraStateData> kCameraDataCacheA;				//
			CameraStateData CameraState;								//
			bool CommitTexturesOnCreation;								//
			bool ImmediateTextureLoads;									//
		};
		static_assert(offsetof(State, CameraState) == 0x160);
		static_assert(sizeof(State) == 0x3C0);

		class Context
		{
		public:
			//members
		};
		//static_assert(sizeof(Context) == 0x2FF0);

		class RenderTargetManager
		{
		public:
			enum TARGET_PERSISTENCY
			{
				TARGET_PERSISTENCY_SHARED,
				TARGET_PERSISTENCY_ALWAYS,
				TARGET_PERSISTENCY_NEVER
			};

			struct TargetHandle
			{
			public:
				//members
				std::uint32_t TargetId;
				BSTAtomicValue<std::int32_t> AcquireCount;
				BSTAtomicValue<std::int32_t> Reserved;
			};

			using TargetHandleList = BSSimpleList<BSGraphics::RenderTargetManager::TargetHandle*>;

			struct Persistency
			{
			public:
				//members
				TARGET_PERSISTENCY m_Persistency;
				bool m_KeepTarget;
			};

			RenderTargetManager();
			~RenderTargetManager();

			void SetFrameBufferProperties();  //TODO

			void CreateRenderTarget(std::uint32_t target, RenderTargetProperties& targetProps, TARGET_PERSISTENCY persist)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CreateRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(43433) };
				return func(this, target, targetProps, persist);
			}

			void CreateDepthStencilTarget(std::uint32_t target, DepthStencilTargetProperties& depthProps, TARGET_PERSISTENCY persist)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CreateDepthStencilTarget);
				REL::Relocation<func_t> func{ REL::ID(1159619) };
				return func(this, target, depthProps, persist);
			}

			void CreateCubeMapRenderTarget(std::uint32_t target, CubeMapRenderTargetProperties& cubeProps, TARGET_PERSISTENCY persist)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CreateCubeMapRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(1397856) };
				return func(this, target, cubeProps, persist);
			}

			void SetRenderTargetPersistency();           //TODO
			void QRenderTargetTextureWidth();            //TODO
			void QRenderTargetTextureHeight();           //TODO
			void QRenderTargetRenderingWidth();          //TODO
			void QRenderTargetRenderingHeight();         //TODO
			void QCurrentRenderTargetWidth();            //TODO
			void QCurrentRenderTargetHeight();           //TODO
			void QRenderTargetProperties();              //TODO
			void QCurrentRenderTarget();                 //TODO
			void QCurrentPlatformRenderTarget();         //TODO
			void QDepthStencilTargetWidth();             //TODO
			void QDepthStencilTargetHeight();            //TODO
			void QCurrentDepthStencilTarget();           //TODO
			void QCurrentPlatformDepthStencilTarget();   //TODO
			void QCubeMapRenderTargetWidth();            //TODO
			void QCubeMapRenderTargetHeight();           //TODO
			void QCurrentCubeMapRenderTargetWidth();     //TODO
			void QCurrentCubeMapRenderTargetHeight();    //TODO
			void QCurrentCubeMapRenderTarget();          //TODO
			void QCurrentPlatformCubeMapRenderTarget();  //TODO

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

			void SetCurrentCubeMapRenderTarget(); //TODO
			void SetCurrentViewportCustomDimensions(); //TODO
			void SetCurrentViewportDefault(); //TODO

			void SetCurrentViewportForceToRenderTargetDimensions()
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetCurrentViewportForceToRenderTargetDimensions);
				REL::Relocation<func_t> func{ REL::ID(1208720) };
				return func(this);
			}

			void SetUseDynamicResolutionViewportAsDefaultViewport();	//TODO
			void GetUseDynamicResolutionViewportAsDefaultViewport();	//TODO
			void UpdateDynamicResolution();								//TODO
			void QGetDynamicWidthRatio();								//TODO
			void SetDynamicWidthRatio();								//TODO
			void QGetDynamicHeightRatio();								//TODO
			void SetDynamicHeightRatio();								//TODO
			void QIsDynamicResolutionCurrentlyActivated();				//TODO
			void SetLowestWidthRatio();									//TODO
			void SetLowestHeightRatio(); //TODO
			void SetFreezeDynamicResolution(); //TODO
			void QGetFreezeDynamicResolution(); //TODO
			void QGetEnableDynamicResolution(); //TODO
			void SetEnableDynamicResolution(); //TODO
			void QIncreaseSpeed();			//TODO
			void QDecreaseSpeed(); //TODO
			void SetIncreaseSpeedRatio(); //TODO
			void SetDecreaseSpeedRatio(); //TODO
			void SetIncreaseResolution(); //TODO
			void SetMovementDelta(); //TODO
			void SetOnlyIncreaseWhenMoving(); //TODO
			void QOnlyIncreaseWhenMoving(); //TODO
			void SetNbFramePause(); //TODO

			void SetTextureRenderTarget(std::uint32_t a1, std::uint32_t a2, bool a3)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetTextureRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(1433009) };
				return func(this, a1, a2, a3);
			}

			void SetTextureRenderTarget_2();	//TODO

			void SetTextureDepth(std::uint32_t a1, std::uint32_t a2)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SetTextureDepth);
				REL::Relocation<func_t> func{ REL::ID(182949) };
				return func(this, a1, a2);
			}

			void SetTextureDepth_2();	//TODO
			void SetTextureStencil();	//TODO
			void SetTextureStencil_2();	//TODO
			void SetTextureCubeMap();	//TODO
			void SetVSTextureRenderTarget();	//TODO
			void SetVSTextureRenderTarget_2();	//TODO
			void SetVSTextureDepthStencil();	//TODO
			void SetVSTextureDepthStencil_2();	//TODO
			void SetCSTextureRenderTarget();	//TODO
			void SetCSTextureDepthStencil();	//TODO
			void SetCSTextureDepthStencilHTILE();	//TODO
			void SetCSUnorderedAccessTarget();	//TODO

			void CopyRenderTargetToRenderTargetCopy(std::uint32_t target, std::uint32_t target2)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CopyRenderTargetToRenderTargetCopy);
				REL::Relocation<func_t> func{ REL::ID(591200) };
				return func(this, target, target2);
			}

			void AcquireRenderTarget(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::AcquireDepthStencil);
				REL::Relocation<func_t> func{ REL::ID(1468639) };
				return func(this, target);
			}

			void ReleaseRenderTarget(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::ReleaseRenderTarget);
				REL::Relocation<func_t> func{ REL::ID(1374956) };
				return func(this, target);
			}

			void AcquireDepthStencil(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::AcquireDepthStencil);
				REL::Relocation<func_t> func{ REL::ID(1015879) };
				return func(this, target);
			}

			void ReleaseDepthStencil(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::ReleaseDepthStencil);
				REL::Relocation<func_t> func{ REL::ID(922599) };
				return func(this, target);
			}

			void AcquireCubemap(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::AcquireCubemap);
				REL::Relocation<func_t> func{ REL::ID(563587) };
				return func(this, target);
			}

			void ReleaseCubemap(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::ReleaseCubemap);
				REL::Relocation<func_t> func{ REL::ID(469959) };
				return func(this, target);
			}

			void QIsAcquiredRenderTarget();	//TODO
			void QIsAcquiredDepthStencil();	//TODO
			void QIsAcquiredCubemap();	//TODO
			void SyncRenderTarget();	//TODO
			void SyncDepthTarget();	//TODO
			void DestroyRenderTargets();	//TODO
			void GetPlatformTargetFromRenderTarget();	//TODO
			void GetPlatformTargetFromDepthStencilTarget();	//TODO

			using CreateFunc = void (*)();
			
			void SetRecreateRenderTargetsCallback();	//TODO
			void RecreateRenderTargets();	//TODO


			void CopyRenderTargetToClipboard(std::uint32_t target)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CopyRenderTargetToClipboard);
				REL::Relocation<func_t> func{ REL::ID(1295596) };
				return func(this, target);
			}

			void CopyRenderTargetToTexture(std::uint32_t target, Texture* tex, bool a3, bool a4)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::CopyRenderTargetToTexture);
				REL::Relocation<func_t> func{ REL::ID(1561984) };
				return func(this, target, tex, a3, a4);
			}

			Texture* SaveRenderTargetToTexture(std::uint32_t target, bool a1, bool a2, Usage use)
			{
				using func_t = decltype(&BSGraphics::RenderTargetManager::SaveRenderTargetToTexture);
				REL::Relocation<func_t> func{ REL::ID(950217) };
				return func(this, target, a1, a2, use);
			}

			#define MAX_RENDER_TARGETS 0x64			//static
			#define MAX_DEPTH_STENCIL_TARGETS 0xC	//static
			#define MAX_CUBEMAP_RENDER_TARGETS 0x1	//static
			
			//Here is where private would start
			//private:
			
			void MustBeKept();
			void InitializeTargets();
			void CreateTarget();
			void DestroyTarget();

			//members
			BSGraphics::RenderTargetProperties pRenderTargetDataA[MAX_RENDER_TARGETS];
			BSGraphics::DepthStencilTargetProperties pDepthStencilTargetDataA[MAX_DEPTH_STENCIL_TARGETS];
			BSGraphics::CubeMapRenderTargetProperties pCubeMapRenderTargetDataA[MAX_CUBEMAP_RENDER_TARGETS];
			std::uint32_t RenderTargetIdA[MAX_RENDER_TARGETS];
			std::uint32_t DepthStencilTargetIdA[MAX_DEPTH_STENCIL_TARGETS];
			std::uint32_t CubeMapRenderTargetIdA[MAX_CUBEMAP_RENDER_TARGETS];
			//bool Creating;	//<- listed in the pdb but seems to mess up alignment
			float fDynamicWidthRatio;
			float fDynamicHeightRatio;
			float fLowestWidthRatio;
			float fLowestHeightRatio;
			float fRatioIncreasePerSeconds;
			float fRatioDecreasePerSeconds;
			float fMovementDelta;
			bool bIncreaseResolution;
			bool bFreezeResolution;
			bool bUpdateResolutionOnlyWhenMoving;
			bool bUseDynamicResolutionViewportAsDefaultViewport;
			bool bIsDynamicResolutionCurrentlyActivated;
			std::uint32_t iNbFramePause;
			std::uint32_t iNbFramesSinceLastIncrease;
			BSTAtomicValue<std::uint32_t> uiDynamicResolutionDisabled;
			CreateFunc createRenderTargets;
		};
		static_assert(sizeof(RenderTargetManager) == 0xFC0);
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
