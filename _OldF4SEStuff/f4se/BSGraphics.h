#pragma once

#include "f4se_common/Relocation.h"
#include "f4se_common/Utilities.h"

#include "f4se/BSGeometry.h"

#include "f4se/NiMaterials.h"
#include "f4se/NiNodes.h"
#include "f4se/NiObjects.h"
#include "f4se/NiProperties.h"
#include "f4se/NiTextures.h"
#include "f4se/NiTypes.h"

#include "d3d11.h"

class BSBatchRenderer;
class BSCompoundFrustum;
class BSCullingGroup;
class BSCullingProcess;
class BSGeometryData;
class BSIStream;
class BSLight;
class BSPortalGraphEntry;
class BSSceneGraph;
class BSShader;

class ShadowSceneNode;

class ImageSpaceEffect;
class ImageSpaceEffectParam;
class ImageSpaceManager;
class ImageSpaceTexture;

class NiAccumulator;
class NiCamera;
class NiCullingProcess;
class NiVisibleArray;

//Other Stuff

class BSRenderPass {
public:
	/*BSShader			* unk;
	BSShader			* m_Shader;
	BSShaderProperty	* m_ShaderProperty;
	BSGeometry			* m_Geometry;
	SInt64				unk2;
	BSRenderPass		* m_Next;
	BSLight				** m_SceneLights;
	BSRenderPass		* m_next;
	BSRenderPass		* m_PassGroupNext;
	UInt32				m_PassEnum;
	SInt8				field_4C;
	SInt8				field_4D;
	SInt8				field_4E;
	SInt8				field_4F;
	UInt8				m_NumLights;*/
};

struct PersistentPassList {
public:
	// members
	BSRenderPass* head;  // 00
	BSRenderPass* tail;  // 08
};
STATIC_ASSERT(sizeof(PersistentPassList) == 0x10);

class BSBatchRenderer {
public:

	enum class GEOMETRY_GROUP_ENUM : UInt32 {
		kNone = static_cast<std::underlying_type_t<GEOMETRY_GROUP_ENUM>>(-1),

		kLODLand = 0x0,
		kLODObjects = 0x1,
		kMultiIndexDecal = 0x2,
		kOpaqueDecal = 0x3,
		kBlendedDecal = 0x4,
		kRefrActive = 0x5,
		k1stPersonNonRefractive = 0x6,
		kFading = 0x7,
		kNoShadow = 0x8,
		kLowAniso = 0x9,
		kUnderwaterFog = 0xA,
		kSSLR = 0xB,
		kZOnly = 0xC,
		kPostZOnly = 0xD,
		kSkyClouds = 0xE,
		kSmoothAlphaTest = 0xF,
		kVATSMaskDepthOnly = 0x10,
		kVATSMask = 0x11,
		kSunGlare = 0x12,
		kBloodSpatter = 0x13,
		kZPrepass = 0x14,
		kWaterStencil = 0x15,
		kWaterDepth = 0x16,

		kTotal
	};

	struct CommandBufferPassesMapAccess;
	struct RenderPassMapAccess;

	struct CommandBufferPassesData {
	public:
		// members
		UInt8* buffer[1u << 13];    // 00000
		UInt8** currentBuffer;      // 10000
		CommandBufferPassesData* next;  // 10008
		UInt32 frame;            // 10010
		UInt32 ownerIndex;       // 10014
	};
	STATIC_ASSERT(sizeof(CommandBufferPassesData) == 0x10018);

	struct CommandBufferPassesDataEntry {
	public:
		// members
		CommandBufferPassesData* data;  // 00
		UInt64 groupAndPass;     // 08
	};
	STATIC_ASSERT(sizeof(CommandBufferPassesDataEntry) == 0x10);

	class GeometryGroup {
	public:
		// members
		BSBatchRenderer* batchRenderer;  // 00
		PersistentPassList passList;     // 08
		float depth;                     // 18
		UInt32 count;             // 1C
		UInt8 flags;              // 20
		SInt8 group;               // 21
	};
	STATIC_ASSERT(sizeof(GeometryGroup) == 0x28);

	class PassGroup {
	public:
		// members
		BSRenderPass* passHead;             // 00
		UInt32 passEnum;             // 08
		UInt16 nextPassGroup;        // 0C
		UInt16 commandBufferPasses;  // 0E
	};
	STATIC_ASSERT(sizeof(PassGroup) == 0x10);

	virtual ~BSBatchRenderer() = default;  // 00

	BSTArray<PassGroup> renderPasses[13];																					// 008
	BSTSmallIndexScatterTable<BSTArray<PassGroup>, RenderPassMapAccess> renderPassMap[13];									// 140
	UInt32 activePassIndexLists[13][2];																						// 2E0
	UInt32 currentFirstPass;																								// 348
	UInt32 currentLastPass;																									// 34C
	bool autoClearPasses;																									// 350
	GeometryGroup* geometryGroups[static_cast<std::underlying_type_t<GEOMETRY_GROUP_ENUM>>(GEOMETRY_GROUP_ENUM::kTotal)];	// 358
	GeometryGroup* alphaGroup;																								// 410
	UInt32 groupingAlphasGroupCount;																						// 418
	GeometryGroup* groupingAlphasGroup;																						// 420
	BSTArray<CommandBufferPassesDataEntry> commandBufferPasses;																// 428
	BSTSmallIndexScatterTable<BSTArray<CommandBufferPassesDataEntry>, CommandBufferPassesMapAccess> commandBufferPassMap;	// 440
	CommandBufferPassesData* bufferPassesCurr;																				// 460
	CommandBufferPassesData* bufferPassesHead;																				// 468
	CommandBufferPassesData** bufferPassesTail;																				// 470
	UInt32 bufferPassesCurrAllocFrame;																						// 478
};
//STATIC_ASSERT(sizeof(BSBatchRenderer) == 0x480);

//GRAPHICS
struct BSGraphics {

	class BSD3DResourceCreator;

	enum RenderTargetMode {
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

	enum RenderTargetCubeMapMode {
		RENDER_TARGET_CUBEMAP_REFLECTIONS,

		RENDER_TARGET_CUBEMAP_COUNT
	};

	enum DepthStencilDepthMode {
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
	
	enum SetRenderTargetMode : UInt32 { //Unconfirmed
		SRTM_CLEAR = 0x0,
		SRTM_CLEAR_DEPTH = 0x1,
		SRTM_CLEAR_STENCIL = 0x2,
		SRTM_RESTORE = 0x3,
		SRTM_NO_CLEAR = 0x4,
		SRTM_FORCE_COPY_RESTORE = 0x5,
		SRTM_INIT = 0x6,
	};

	enum Format {
		
	};
	
	enum Usage { //Uncomfirmed
		USAGE_DEFAULT = 0,
		USAGE_IMMUTABLE = 1,
		USAGE_DYNAMIC = 2,
		USAGE_STAGING = 3 //ScreenShot::GetScreenShotData calls ScreenShot::BufferScreenShot using this
	};

	class RendererShadowState {
	public:

	};

	class TextureHeader {
	public:
		UInt16	height;
		UInt16	width;
		UInt8	mipLevels;
		UInt8	format;
		UInt8	field_6;
		UInt8	field_7;
	};
	STATIC_ASSERT(sizeof(TextureHeader) == 0x8);

	class Texture {
	public:

	};

	class ViewData {
	public:
		NiPoint2 Unk0;
		NiPoint2 Unk8;
		NiPoint2 Unk10;
	};

	class ConstantGroup {
	public:
		// members
		ID3D11Buffer* buffer;		// 00
		float* data;				// 08
		bool dataIsCPUWorkBuffer;	// 10
	};
	STATIC_ASSERT(sizeof(ConstantGroup) == 0x18);

	class ComputeShader {
	public:
		// members
		UInt32 id;										// 00
		ID3D11ComputeShader* shader;					// 08
		UInt32 byteCodeSize;							// 10
		BSGraphics::ConstantGroup constantBuffers[3];	// 18
		UInt64 shaderDesc;								// 60
		SInt8 constantTable[32];						// 68
	};
	STATIC_ASSERT(sizeof(ComputeShader) == 0x88);

	class DomainShader {
	public:
		// members
		UInt32 id;										// 00
		ID3D11DomainShader* shader;						// 08
		UInt32 byteCodeSize;							// 10
		BSGraphics::ConstantGroup constantBuffers[3];	// 18
		UInt64 shaderDesc;								// 60
		SInt8 constantTable[32];						// 68
	};
	STATIC_ASSERT(sizeof(DomainShader) == 0x88);

	class HullShader {
	public:
		// members
		UInt32 id;										// 00
		ID3D11HullShader* shader;						// 08
		UInt32 byteCodeSize;							// 10
		BSGraphics::ConstantGroup constantBuffers[3];	// 18
		UInt64 shaderDesc;								// 60
		SInt8 constantTable[32];						// 68
	};
	STATIC_ASSERT(sizeof(HullShader) == 0x88);

	class PixelShader {
	public:
		// members
		UInt32 id;										// 00
		ID3D11PixelShader* shader;						// 08
		BSGraphics::ConstantGroup constantBuffers[3];	// 10
		SInt8 constantTable[32];						// 58
	};
	STATIC_ASSERT(sizeof(PixelShader) == 0x78);

	class VertexShader {
	public:
		// members
		UInt32 id;										// 00
		ID3D11VertexShader* shader;						// 08
		UInt32 byteCodeSize;							// 10
		BSGraphics::ConstantGroup constantBuffers[3];	// 18
		UInt64 shaderDesc;								// 60
		SInt8 constantTable[32];						// 68
	};
	STATIC_ASSERT(sizeof(VertexShader) == 0x88);

	class CubeMapRenderTarget {
	public:
		// members
		ID3D11Texture2D* texture;           // 00
		ID3D11RenderTargetView* rtView[6];  // 08
		ID3D11ShaderResourceView* srView;   // 38
	};
	STATIC_ASSERT(sizeof(CubeMapRenderTarget) == 0x40);

	class DepthStencilTarget {
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
	STATIC_ASSERT(sizeof(DepthStencilTarget) == 0x98);

	class RenderTarget {
	public:
		// members
		ID3D11Texture2D* texture;              // 00
		ID3D11Texture2D* copyTexture;          // 08
		ID3D11RenderTargetView* rtView;        // 10
		ID3D11ShaderResourceView* srView;      // 18
		ID3D11ShaderResourceView* copySRView;  // 20
		ID3D11UnorderedAccessView* uaView;     // 28
	};
	//STATIC_ASSERT(sizeof(RenderTarget) == 0x30);

	struct RenderTargetProperties {
		UInt32 uiWidth;
		UInt32 uiHeight;
		DXGI_FORMAT eFormat;
		bool bCopyable;
		bool bSupportUnorderedAccess;
		bool bAllowMipGeneration;
		int iMipLevel;
		UInt32 uiTextureTarget;
		UInt32 uiUnknown;
	};
	STATIC_ASSERT(sizeof(RenderTargetProperties) == 0x1C);

	struct DepthStencilTargetProperties {
		UInt32 uiWidth;
		UInt32 uiHeight;
		UInt32 uiArraySize;
		bool Unknown1;
		bool Stencil;
		bool Use16BitsDepth;
	};
	STATIC_ASSERT(sizeof(DepthStencilTargetProperties) == 0x10);

	struct CubeMapRenderTargetProperties {
		UInt32 uiWidth;
		UInt32 uiHeight;
		DXGI_FORMAT eFormat;
	};
	STATIC_ASSERT(sizeof(CubeMapRenderTargetProperties) == 0xC);

	class RendererWindow {
	public:
		void* hwnd;
		SInt32 windowX;
		SInt32 windowY;
		SInt32 windowWidth;
		SInt32 windowHeight;
		IDXGISwapChain* swapChain;
		RenderTarget swapChainRenderTarget;
	};
	STATIC_ASSERT(sizeof(RendererWindow) == 0x50);

	class RendererData {
	public:
		// members
		RendererShadowState* shadowState;				// 0000
		BSD3DResourceCreator* resourceCreator;			// 0008
		UInt32 adapter;									// 0010
		DXGI_RATIONAL desiredRefreshRate;				// 0014
		DXGI_RATIONAL actualRefreshRate;				// 001C
		DXGI_MODE_SCALING scaleMode;					// 0024
		DXGI_MODE_SCANLINE_ORDER scanlineMode;			// 0028
		SInt32 fullScreen;								// 002C
		bool appFullScreen;								// 0030
		bool borderlessWindow;							// 0031
		bool vsync;										// 0032
		bool initialized;								// 0033
		bool requestWindowSizeChange;					// 0034
		UInt32 newWidth;								// 0038
		UInt32 newHeight;								// 003C
		UInt32 presentInterval;							// 0040
		ID3D11Device* device;							// 0048
		ID3D11DeviceContext* context;					// 0050
		RendererWindow renderWindow[32];				// 0058
		RenderTarget renderTargets[101];				// 0A58
		DepthStencilTarget depthStencilTargets[13];		// 1D48
		CubeMapRenderTarget cubeMapRenderTargets[2];	// 2500
		unsigned char rendererLock[0x25A8 - 0x2580];    // 2580 - TODO
		const char* className;							// 25A8
		void* instance;									// 25B0
		bool nvapiEnabled;								// 25B8
	};

	// 1B8
	class Renderer {
	public:
		using ResetRenderTargets_t = void (*)();

		// members
		bool skipNextPresent;                     // 00
		ResetRenderTargets_t resetRenderTargets;  // 08
		RendererData data;                        // 10

		MEMBER_FN_PREFIX(Renderer);
		DEFINE_MEMBER_FN(ClearColor, void, 0x01D0B8B0);
		DEFINE_MEMBER_FN(CreateEmptyTexture, Texture*, 0x01D0EB00, UInt32, UInt32);
		DEFINE_MEMBER_FN(DoZPrePass, void, 0x01D12980, NiCamera*, NiCamera*, float, float, float, float);
		DEFINE_MEMBER_FN(Flush, void, 0x01D0B760);
		DEFINE_MEMBER_FN(SetClearColor, void, 0x01D0B770, float, float, float, float);
		DEFINE_MEMBER_FN(ResetZPrePass, void, 0x01D125E0);
		DEFINE_MEMBER_FN(ResetState, void, 0x01D11DA0);

		void ClearColor();
		Texture* CreateEmptyTexture(UInt32 width, UInt32 height);
		void DoZPrePass(NiCamera* cam1, NiCamera* cam2, float a1, float a2, float a3, float a4);
		void Flush();
		void SetClearColor(float red, float green, float blue, float alpha);
		void ResetZPrePass();
		void ResetState();
	};

	class State {
	public:

		MEMBER_FN_PREFIX(State);
		DEFINE_MEMBER_FN(SetCameraData, void, 0x01D215C0, NiCamera*, bool, float, float);

		void SetCameraData(NiCamera* cam, bool a3, float a4, float a5);
	};

	// 0x2FF0
	class Context {
	public:

	};
	//STATIC_ASSERT(sizeof(Context) == 0x2FF0);

	class OcclusionQuery {
	public:

	};

	class RenderTargetManager {
	public:

#define MAX_RENDER_TARGETS			0x64
#define MAX_DEPTH_STENCIL_TARGETS	0xC
#define MAX_CUBEMAP_RENDER_TARGETS	0x1

		enum TARGET_PERSISTENCY {
			TARGET_PERSISTENCY_ALWAYS,
		};

		struct SharedTargetInfo {
			UInt32	width;		// 00 - 400
			UInt32	height;		// 04 - 400
			UInt32	unk08;		// 08 - 1C
			UInt32	unk0C;		// 0C - 10000
			UInt32	unk10;		// 10 - FFFFFFFF
			UInt32	unk14;		// 14 - r13d
			UInt32	unk18;		// 18 - r12b
		};

		RenderTargetProperties			pRenderTargetDataA[100];
		DepthStencilTargetProperties	pDepthStencilTargetDataA[12];
		CubeMapRenderTargetProperties	pCubeMapRenderTargetDataA[1];
		UInt8							gapD50[568];
		float							Width;
		float							Height;
		float							dynamicWidth;
		float							dynamicHeight;
		float							IncreaseSpeed;
		float							DecreaseSpeed;
		float							deltaMovement;
		bool							increaseResolution;
		bool							bDynamicResolution;
		bool							bResolutionDontGrowOnPlayerMove;
		UInt8							field_FA7;
		UInt32							field_FA8;
		UInt32							uiResolutionGrowEveryFrame;
		UInt8							gapFB0[8];
		void(__fastcall* Create)();

		MEMBER_FN_PREFIX(RenderTargetManager);
		DEFINE_MEMBER_FN(AcquireCubemap, void, 0x01D32BF0, SInt32);
		DEFINE_MEMBER_FN(AcquireDepthStencil, void, 0x01D32AE0, SInt32);
		DEFINE_MEMBER_FN(AcquireRenderTarget, void, 0x01D329D0, SInt32);
		DEFINE_MEMBER_FN(CopyRenderTargetToClipboard, void, 0x01D32990, SInt32);
		DEFINE_MEMBER_FN(CopyRenderTargetToRenderTargetCopy, void, 0x01D329B0, SInt32, SInt32);
		DEFINE_MEMBER_FN(CopyRenderTargetToTexture, void, 0x01D32960, SInt32, Texture*, bool, bool);
		DEFINE_MEMBER_FN(CreateCubeMapRenderTarget, void, 0x01D312D0, SInt32, CubeMapRenderTargetProperties&, TARGET_PERSISTENCY);
		DEFINE_MEMBER_FN(CreateDepthStencilTarget, void, 0x01D310C0, SInt32, DepthStencilTargetProperties&, TARGET_PERSISTENCY);
		DEFINE_MEMBER_FN(CreateRenderTarget, void, 0x01D30E90, SInt32, RenderTargetProperties&, TARGET_PERSISTENCY);
		DEFINE_MEMBER_FN(ReleaseCubemap, void, 0x01D32C60, SInt32);
		DEFINE_MEMBER_FN(ReleaseDepthStencil, void, 0x01D32B50, SInt32);
		DEFINE_MEMBER_FN(ReleaseRenderTarget, void, 0x01D32A40, SInt32);
		DEFINE_MEMBER_FN(SaveRenderTargetToTexture, Texture*, 0x01D32910, SInt32, bool, bool, Usage);
		DEFINE_MEMBER_FN(SetCurrentRenderTarget, void, 0x01D318B0, SInt32, SInt32, SetRenderTargetMode);
		DEFINE_MEMBER_FN(SetCurrentDepthStencilTarget, void, 0x01D31940, SInt32, SetRenderTargetMode, SInt32, bool);
		DEFINE_MEMBER_FN(SetCurrentViewportForceToRenderTargetDimensions, void, 0x01D31B20);
		DEFINE_MEMBER_FN(SetTextureRenderTarget, void, 0x01D31E50, UInt32, SInt32, bool);
		DEFINE_MEMBER_FN(SetTextureDepth, void, 0x01D31FF0, UInt32, SInt32);

		void AcquireCubemap(SInt32 target);
		void AcquireDepthStencil(SInt32 target);
		void AcquireRenderTarget(SInt32 target);
		void CopyRenderTargetToClipboard(SInt32 target);
		void CopyRenderTargetToRenderTargetCopy(SInt32 target, SInt32 target2);
		void CopyRenderTargetToTexture(SInt32 target, Texture* tex, bool a3, bool a4);
		void CreateCubeMapRenderTarget(SInt32 target, CubeMapRenderTargetProperties& cubeProps, TARGET_PERSISTENCY persist);
		void CreateDepthStencilTarget(SInt32 target, DepthStencilTargetProperties& depthProps, TARGET_PERSISTENCY persist);
		void CreateRenderTarget(SInt32 target, RenderTargetProperties& targetProps, TARGET_PERSISTENCY persist);
		void ReleaseCubemap(SInt32 target);
		void ReleaseDepthStencil(SInt32 target);
		void ReleaseRenderTarget(SInt32 target);
		Texture* SaveRenderTargetToTexture(SInt32 target, bool a1, bool a2, Usage use);
		void SetCurrentRenderTarget(SInt32 slot, SInt32 targetIndex, SetRenderTargetMode mode);
		void SetCurrentDepthStencilTarget(SInt32 a1, SetRenderTargetMode mode, SInt32 a2, bool a3);
		void SetCurrentViewportForceToRenderTargetDimensions();
		void SetTextureRenderTarget(UInt32 a1, SInt32 a2, bool a3);
		void SetTextureDepth(UInt32 a1, SInt32 a2);
	};
};
STATIC_ASSERT(std::is_empty_v<BSGraphics>);

//EXTERN

extern RelocPtr <BSGraphics::Context*>				pCurContext;
extern RelocPtr <BSGraphics::Context*>				pDefaultContext;
extern RelocPtr <BSGraphics::Renderer>				BSGraphics_gRenderer;
extern RelocPtr <BSGraphics::RendererData*>			pRendererData;
extern RelocPtr <BSGraphics::RendererWindow*>		pRendererWindow;
extern RelocPtr <BSGraphics::State>					BSGraphics_gState;
extern RelocPtr <BSGraphics::RenderTargetManager>	BSGraphics_gRenderTargetManager;
extern RelocPtr <ID3D11Device*>						pDevice;
extern RelocPtr <ID3D11DeviceContext*>				pImmediateContext;
extern RelocPtr <ID3D11DeviceContext*>				pMainContext;
extern RelocPtr <ID3D11DeviceContext*>				pContext;