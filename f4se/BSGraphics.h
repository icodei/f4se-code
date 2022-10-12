#pragma once

#include "f4se_common/Relocation.h"
#include "f4se_common/Utilities.h"

#include "f4se/BSGeometry.h"
#include "f4se/NiTextures.h"
#include "f4se/NiMaterials.h"
#include "d3d11.h"

class BSGeometryData;
class BSCullingGroup;

//struct ID3D11Buffer;
//struct ID3D11ComputeShader;
//struct ID3D11DepthStencilView;
//struct ID3D11Device;
//struct ID3D11DeviceContext;
//struct ID3D11DomainShader;
//struct ID3D11HullShader;
//struct ID3D11PixelShader;
//struct ID3D11RenderTargetView;
//struct ID3D11ShaderResourceView;
//struct ID3D11Texture2D;
//struct ID3D11UnorderedAccessView;
//struct ID3D11VertexShader;
//struct IDXGISwapChain;
//struct D3D11_VIEWPORT;
//struct D3D11_PRIMITIVE_TOPOLOGY;

//GRAPHICS
struct BSGraphics {

	class BSD3DResourceCreator;

	//class BSRenderManager {
	//public:
	//	UInt64				unk2588[0x2590 >> 3];	// 2588
	//	CRITICAL_SECTION	m_textureLock;			// 2590
	//
	//	MEMBER_FN_PREFIX(BSRenderManager);
	//	DEFINE_MEMBER_FN(CreateBSGeometryData, BSGeometryData*, 0x01D0BD60, UInt32 * blockSize, UInt8 * vertexData, UInt64 vertexDesc, BSGeometryData::TriangleData * triData); // Creates a block with a vertex copy in the resource pool with a reference to the supplied triblock (partial deep copy)
	//};
	//STATIC_ASSERT(offsetof(BSRenderManager, m_textureLock) == 0x2590);

	enum SetRenderTargetMode {};
	enum DepthStencilDepthMode {};

	class RendererShadowState {
	public:

	};

	class Texture {
	public:
	};

	class ConstantGroup {
	public:
		// members
		ID3D11Buffer* buffer;    // 00
		float* data;             // 08
		bool dataIsCPUWorkBuffer;  // 10
	};
	STATIC_ASSERT(sizeof(ConstantGroup) == 0x18);

	class ComputeShader {
	public:
		// members
		UInt32 id;                         // 00
		ID3D11ComputeShader* shader;        // 08
		UInt32 byteCodeSize;               // 10
		BSGraphics::ConstantGroup constantBuffers[3];  // 18
		UInt64 shaderDesc;                 // 60
		SInt8 constantTable[32];            // 68
	};
	STATIC_ASSERT(sizeof(ComputeShader) == 0x88);

	class DomainShader
	{
	public:
		// members
		UInt32 id;                              // 00
		ID3D11DomainShader* shader;              // 08
		UInt32 byteCodeSize;                    // 10
		BSGraphics::ConstantGroup constantBuffers[3];  // 18
		UInt64 shaderDesc;                      // 60
		SInt8 constantTable[32];                 // 68
	};
	STATIC_ASSERT(sizeof(DomainShader) == 0x88);

	class HullShader
	{
	public:
		// members
		UInt32 id;                         // 00
		ID3D11HullShader* shader;           // 08
		UInt32 byteCodeSize;               // 10
		BSGraphics::ConstantGroup constantBuffers[3];  // 18
		UInt64 shaderDesc;                 // 60
		SInt8 constantTable[32];            // 68
	};
	STATIC_ASSERT(sizeof(HullShader) == 0x88);

	class PixelShader
	{
	public:
		// members
		UInt32 id;                         // 00
		ID3D11PixelShader* shader;          // 08
		BSGraphics::ConstantGroup constantBuffers[3];  // 10
		SInt8 constantTable[32];            // 58
	};
	STATIC_ASSERT(sizeof(PixelShader) == 0x78);

	class VertexShader
	{
	public:
		// members
		UInt32 id;                         // 00
		ID3D11VertexShader* shader;         // 08
		UInt32 byteCodeSize;               // 10
		BSGraphics::ConstantGroup constantBuffers[3];  // 18
		UInt64 shaderDesc;                 // 60
		SInt8 constantTable[32];            // 68
	};
	STATIC_ASSERT(sizeof(VertexShader) == 0x88);

	class CubeMapRenderTarget
	{
	public:
		// members
		ID3D11Texture2D* texture;           // 00
		ID3D11RenderTargetView* rtView[6];  // 08
		ID3D11ShaderResourceView* srView;   // 38
	};
	STATIC_ASSERT(sizeof(CubeMapRenderTarget) == 0x40);

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
	STATIC_ASSERT(sizeof(DepthStencilTarget) == 0x98);

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
	STATIC_ASSERT(sizeof(RenderTarget) == 0x30);

	struct RenderTargetProperties {
		uint32_t uiWidth;
		uint32_t uiHeight;
		DXGI_FORMAT eFormat;
		bool bCopyable;
		bool bSupportUnorderedAccess;
		bool bAllowMipGeneration;
		int iMipLevel;
		uint32_t uiTextureTarget;
		uint32_t uiUnknown;
	};
	STATIC_ASSERT(sizeof(RenderTargetProperties) == 0x1C);


	struct DepthStencilTargetProperties {
		uint32_t uiWidth;
		uint32_t uiHeight;
		uint32_t uiArraySize;
		bool Unknown1;
		bool Stencil;
		bool Use16BitsDepth;
	};
	STATIC_ASSERT(sizeof(DepthStencilTargetProperties) == 0x10);

	struct CubeMapRenderTargetProperties {
		uint32_t uiWidth;
		uint32_t uiHeight;
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
		RendererShadowState* shadowState;             // 0000
		BSD3DResourceCreator* resourceCreator;        // 0008
		UInt32 adapter;                        // 0010
		DXGI_RATIONAL desiredRefreshRate;             // 0014
		DXGI_RATIONAL actualRefreshRate;              // 001C
		DXGI_MODE_SCALING scaleMode;                  // 0024
		DXGI_MODE_SCANLINE_ORDER scanlineMode;        // 0028
		SInt32 fullScreen;                      // 002C
		bool appFullScreen;                           // 0030
		bool borderlessWindow;                        // 0031
		bool vsync;                                   // 0032
		bool initialized;                             // 0033
		bool requestWindowSizeChange;                 // 0034
		UInt32 newWidth;                       // 0038
		UInt32 newHeight;                      // 003C
		UInt32 presentInterval;                // 0040
		ID3D11Device* device;                         // 0048
		ID3D11DeviceContext* context;                 // 0050
		RendererWindow renderWindow[32];              // 0058
		RenderTarget renderTargets[101];              // 0A58
		DepthStencilTarget depthStencilTargets[13];   // 1D48
		CubeMapRenderTarget cubeMapRenderTargets[2];  // 2500
		unsigned char rendererLock[0x25A8 - 0x2580];      // 2580 - TODO
		const char* className;                        // 25A8
		void* instance;                               // 25B0
		bool nvapiEnabled;                            // 25B8
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
	};

	class State {
	public:

	};

	class Context {
	public:

	};

	class RenderTargetManager {
	public:

#define MAX_RENDER_TARGETS			0x64
#define MAX_DEPTH_STENCIL_TARGETS	0xC
#define MAX_CUBEMAP_RENDER_TARGETS	0x1

		enum TARGET_PERSISTENCY {
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

		MEMBER_FN_PREFIX(RenderTargetManager);


		DEFINE_MEMBER_FN(AcquireCubemap, void, 0x01D32BF0, int target);
		DEFINE_MEMBER_FN(AcquireDepthStencil, void, 0x01D32AE0, int target);
		DEFINE_MEMBER_FN(AcquireRenderTarget, void, 0x01D329D0, int target);
		DEFINE_MEMBER_FN(CopyRenderTargetToClipboard, void, 0x01D32990, int target);
		DEFINE_MEMBER_FN(CopyRenderTargetToRenderTargetCopy, void, 0x01D329B0, int target, int target2);
		DEFINE_MEMBER_FN(CopyRenderTargetToTexture, void, 0x01D32960, int target, Texture * tex, bool a3, bool a4);
		DEFINE_MEMBER_FN(CreateCubeMapRenderTarget, void, 0x01D312D0, int target, CubeMapRenderTargetProperties & cubeProps, TARGET_PERSISTENCY a3);
		DEFINE_MEMBER_FN(CreateDepthStencilTarget, void, 0x01D310C0, int target, DepthStencilTargetProperties & depthProps, TARGET_PERSISTENCY a3);
		DEFINE_MEMBER_FN(CreateRenderTarget, void, 0x01D30E90, int target, RenderTargetProperties & targetProps, TARGET_PERSISTENCY a3);
		DEFINE_MEMBER_FN(ReleaseCubemap, void, 0x01D32C60, int target);
		DEFINE_MEMBER_FN(ReleaseDepthStencil, void, 0x01D32B50, int target);
		DEFINE_MEMBER_FN(ReleaseTarget, void, 0x01D32A40, int target);
	};
};
STATIC_ASSERT(std::is_empty_v<BSGraphics>);

//SHADERS

class BSShaderResourceManager {
public:
	virtual ~BSShaderResourceManager();

	virtual void CreateTriShape1();
	virtual void CreateTriShape2();
	virtual void CreateTriShape3();
	virtual void CreateTriShapeRendererData();
	virtual void CreateSubIndexTriShape();
	virtual void IncGeometryRef(BSGeometryData* geomData);
	virtual void DefGeometryRef(BSGeometryData* geomData); // Will auto-destroy the block when it reaches zero
	//... 

};

class BSShaderManager {
public:

#define NUM_RENDERFLAG_BITS 0x10

	enum Int32 {
		BSS_AMBIENT						= 0x1,
		BSS_DIFFUSE						= 0x2,
		BSS_TEXTURE						= 0x4,
		BSS_SPECULAR					= 0x8,
		BSS_SHADOWS						= 0x10,
		BSS_FULLMULTIPASSLIGHTING		= 0x0F,
		BSS_FULLMULTIPASSLIGHTING_PROJ	= 0x0F
	};

	enum UInt32 {
		BSSM_DISABLED = 0x0FFFFFFFF
	};

	enum eShadowMode {
	};

	enum etRenderMode : unsigned short {
	};

	enum usRenderFlags : unsigned short {
	};

	class State {
	public:

	};
	MEMBER_FN_PREFIX(BSShaderManager);
	DEFINE_MEMBER_FN(GetTexture, void, 0x027D61F0, const char* filePath, bool a2, NiPointer<NiTexture>& returnTex, bool a4, bool a5, bool a6);


	void GetTexture(const char* filePath, bool a2, NiPointer<NiTexture>& returnTex, bool a4, bool a5, bool a6);
};

class BSShaderAccumulator {
public:

};


//IMAGESPACE

class ImageSpaceManager {
public:

};

//EXTERN

extern RelocPtr <BSGraphics::Context*>					pCurContext;
extern RelocPtr <BSGraphics::Context*>					pDefaultContext;
extern RelocPtr <BSGraphics::Renderer>					gRenderer;
extern RelocPtr <BSGraphics::RendererData*>				pRendererData;
extern RelocPtr <BSGraphics::RendererWindow*>			pRendererWindow;
extern RelocPtr <BSGraphics::State>						gRenderState;
extern RelocPtr <BSGraphics::RenderTargetManager>		gRenderTargetManager;
extern RelocPtr <BSShaderAccumulator*>					pCurrentShaderAccumulator;
extern RelocPtr <BSShaderManager::State>				gShaderManagerState;
extern RelocPtr <BSShaderManager>						gShaderManagerInstance;
extern RelocPtr <BSShaderMaterial*>						pShaderMaterialDefault;
extern RelocPtr <BSShaderResourceManager>				gShaderResourceManagerInstance;
extern RelocPtr <ID3D11Device*>							pDevice;
extern RelocPtr <ID3D11DeviceContext*>					pImmediateContext;
extern RelocPtr <ID3D11DeviceContext*>					pMainContext;
extern RelocPtr <ID3D11DeviceContext*>					pContext;
extern RelocPtr <ImageSpaceManager*>					pImageSpaceManagerInstance;
