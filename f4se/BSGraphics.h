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
class BSCullingGroup;
class BSCullingProcess;
class BSGeometryData;
class BSIStream;
class BSLight;
class BSPortalGraphEntry;
class BSShader;

class ShadowSceneNode;

class ImageSpaceEffect;
class ImageSpaceEffectParam;
class ImageSpaceManager;
class ImageSpaceTexture;

class NiCamera;
class NiCullingProcess;
class NiVisibleArray;

//Other Stuff

class BSCompoundFrustum {
public:
	UInt8 _pad0[208];
};

class NiAccumulator : public NiObject {
public:
	//virtual ~NiAccumulator();
	//NiAccumulator::StartAccumulating
	//NiAccumulator::FinishAccumulating
	//_purecall_0
	//NiAccumulator::StartGroupingAlphas
	//NiAccumulator::StopGroupingAlphas
	//NiAccumulator::RegisterObject

	NiCamera* m_pkCamera;
};

class NiBackToFrontAccumulator : public NiAccumulator {
public:
	//virtual ~NiBackToFrontAccumulator();

	SInt8			_pad[24];
	SInt32			m_iNumItems;
	SInt32			m_iMaxItems;
	BSGeometry**	m_ppkItems;
	float*			m_pfDepths;
	SInt32			m_iCurrItem;
};

class NiAlphaAccumulator : public NiBackToFrontAccumulator {
public:
	//virtual ~NiAlphaAccumulator();

	bool m_bObserveNoSortHint;
	bool m_bSortByClosestPoint;
	bool m_bInterfaceSort;
};

class NiCullingProcess {
public:
	NiCullingProcess() : m_bUseVirtualAppend(0), m_pkVisibleSet(nullptr), m_pkCamera(nullptr), m_kFrustum(), m_kPlanes(), kCustomCullPlanes(), m_bCameraRelatedUpdates(0), bUpdateAccumulateFlag(0), bIgnorePreprocess(0), bCustomCullPlanes(0), bUnknownBool1(0), bUnknownBool2(0) { CALL_MEMBER_FN(this, ctor)(m_pkVisibleSet); };
	NiCullingProcess(NiVisibleArray* a1) : m_bUseVirtualAppend(0), m_pkVisibleSet(nullptr) { CALL_MEMBER_FN(this, ctor)(a1); };
	virtual void GetRTTI() {};
	virtual void IsNode() {};
	virtual void IsNode2() {};
	virtual void IsSwitchNode() {};
	virtual void IsFadeNode() {};
	virtual void IsMultiBoundNode() {};
	virtual void IsGeometry() {};
	virtual void IsTriStrips() {};
	virtual void IsTriShape() {};
	virtual void IsDynamicTriShape() {};
	virtual void IsSegmentedTriShape() {};
	virtual void IsSubIndexTriShape() {};
	virtual void IsNiGeometry() {};
	virtual void IsNiTriBasedGeom() {};
	virtual void IsNiTriShape() {};
	virtual void IsParticlesGeom() {};
	virtual void IsParticleSystem() {};
	virtual void IsLinesGeom() {};
	virtual void IsLight() {};
	virtual void IsBhkNiCollisionObject() {};
	virtual void IsBhkBlendCollisionObject() {};
	virtual void IsBhkRigidBody() {};
	virtual void IsBhkLimitedHingeConstraint() {};
	virtual void IsbhkNPCollisionObject() {};
	virtual ~NiCullingProcess() {};
	virtual void Process() {};
	virtual void Process2() {};
	virtual void AppendVirtual() {};

	const bool m_bUseVirtualAppend;
	NiVisibleArray* m_pkVisibleSet;
	NiCamera* m_pkCamera;
	NiFrustum m_kFrustum;
	NiFrustumPlanes m_kPlanes;
	NiFrustumPlanes kCustomCullPlanes;
	bool m_bCameraRelatedUpdates;
	bool bUpdateAccumulateFlag;
	bool bIgnorePreprocess;
	bool bCustomCullPlanes;
	bool bUnknownBool1;
	bool bUnknownBool2;

	MEMBER_FN_PREFIX(NiCullingProcess);
	DEFINE_MEMBER_FN(ctor, void, 0x01BC4A60, NiVisibleArray*);
	DEFINE_MEMBER_FN(dtor, void, 0x01BC4A40);
};

class BSCullingProcess : public NiCullingProcess {
public:

	enum BSCPCullingType {
		kNormal = 0,
		kAllPass = 1,
		kAllFail = 2,
		kIgnoreMultiBounds = 3,
		kForceMultiBoundsNoUpdate = 4
	};

	BSCullingProcess() {};
	BSCullingProcess(NiVisibleArray* a1) { CALL_MEMBER_FN(this, ctor)(a1); };
	~BSCullingProcess() { CALL_MEMBER_FN(this, dtor)(); };
	//virtual void GetRTTI();
	//virtual void IsNode();
	//virtual void IsNode2();
	//virtual void IsSwitchNode();
	//virtual void IsFadeNode();
	//virtual void IsMultiBoundNode();
	//virtual void IsGeometry();
	//virtual void IsTriStrips();
	//virtual void IsTriShape();
	//virtual void IsDynamicTriShape();
	//virtual void IsSegmentedTriShape();
	//virtual void IsSubIndexTriShape();
	//virtual void IsNiGeometry();
	//virtual void IsNiTriBasedGeom();
	//virtual void IsNiTriShape();
	//virtual void IsParticlesGeom();
	//virtual void IsParticleSystem();
	//virtual void IsLinesGeom();
	//virtual void IsLight();
	//virtual void IsBhkNiCollisionObject();
	//virtual void IsBhkBlendCollisionObject();
	//virtual void IsBhkRigidBody();
	//virtual void IsBhkLimitedHingeConstraint();
	//virtual void IsbhkNPCollisionObject();
	//virtual ~BSCullingProcess();
	//virtual void Process();
	//virtual void Process2();
	//virtual void AppendVirtual();

	//add
	virtual void AppendNonAccum() {};
	virtual void TestBaseVisibility_BSMultiBound() {};
	virtual void TestBaseVisibility_BSOcclusionPlane() {};
	virtual void TestBaseVisibility_NiBound() {};

	SInt32 field_128;
	SInt32 field_12C;
	SInt32 field_130;
	SInt32 field_134;
	void* field_138;
	SInt64 gap140;
	SInt64 field_148;
	BSPortalGraphEntry* QPortalGraphEntry;
	BSCPCullingType CullingType;
	UInt8 gap15C[40];
	SInt32 field_184;
	BSCompoundFrustum* field_188;
	NiPointer<NiAccumulator> Accumulator;
	bool QRecurseToGeometry;

	MEMBER_FN_PREFIX(BSCullingProcess);
	DEFINE_MEMBER_FN(ctor, void, 0x01CCDE90, NiVisibleArray*);
	DEFINE_MEMBER_FN(dtor, void, 0x01CCDF10);
	DEFINE_MEMBER_FN(SetAccumulator, void, 0x01CCDF70, NiAccumulator*);

	void SetAccumulator(NiAccumulator* accumulator);
};
//STATIC_ASSERT(sizeof(BSCullingProcess) == 0x1A0);


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

class BSBatchRenderer {
public:

	// 28
	class GeometryGroup {
	public:

	};
	//STATIC_ASSERT(sizeof(GeometryGroup) == 0x28);
};

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

	enum RenderTargetType : UInt32 {
		unkN1 = 0xFFFFFFFF, //None??
		unk00 = 0, //Buffer??
		unk01 = 1, //Main??
		unk02 = 2, //MainCopy??
		unk03 = 3,

		unk14 = 14, //RefractionNormals??
		unk15 = 15, //ClearMask?? MenuBG??
		unk16 = 16, //FaceCustomizationDiffuse
		unk17 = 17, //FaceCustomizationNormals
		unk18 = 18, //FaceCustomizationSmoothSpec

		unk21 = 21, //LocalMapCompanion??

		unk26 = 26, //part of DrawWorld::MainRenderSetup
		unk27 = 27, //LocalMap?? part of DrawWorld::MainRenderSetup
		
		unk29 = 29, //part of DrawWorld::MainRenderSetup
		unk30 = 30, //part of DrawWorld::MainRenderSetup
		unk31 = 31, //part of DrawWorld::MainRenderSetup
		unk32 = 32, //LoadingMenu?? part of DrawWorld::MainRenderSetup

		unk63 = 63, //ScreenShot??
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

	enum Format {};
	enum DepthStencilDepthMode {};
	
	enum Usage { //Uncomfirmed
		USAGE_DEFAULT = 0,
		USAGE_IMMUTABLE = 1,
		USAGE_DYNAMIC = 2,
		USAGE_STAGING = 3
	};

	class RendererShadowState {
	public:

	};

	class TextureHeader {
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

	class DomainShader {
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

	class HullShader {
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

	class PixelShader {
	public:
		// members
		UInt32 id;                         // 00
		ID3D11PixelShader* shader;          // 08
		BSGraphics::ConstantGroup constantBuffers[3];  // 10
		SInt8 constantTable[32];            // 58
	};
	STATIC_ASSERT(sizeof(PixelShader) == 0x78);

	class VertexShader {
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
	//STATIC_ASSERT(sizeof(RendererWindow) == 0x50);

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
		DEFINE_MEMBER_FN(DoZPrePass, void, 0x01D12980, NiCamera*, NiCamera*, float, float, float, float);
		DEFINE_MEMBER_FN(Flush, void, 0x01D0B760);
		DEFINE_MEMBER_FN(SetClearColor, void, 0x01D0B770, float, float, float, float);
		DEFINE_MEMBER_FN(ResetZPrePass, void, 0x01D125E0);
		DEFINE_MEMBER_FN(ResetState, void, 0x01D11DA0);

		void ClearColor();
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

	// 12272
	class Context {
	public:

	};
	//STATIC_ASSERT(sizeof(Context) == 0x12272);

	class OcclusionQuery {
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

		BSGraphics::RenderTargetProperties pRenderTargetDataA[100];
		BSGraphics::DepthStencilTargetProperties pDepthStencilTargetDataA[12];
		BSGraphics::CubeMapRenderTargetProperties pCubeMapRenderTargetDataA[1];
		UInt8 gapD50[568];
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
		char field_FA7;
		int field_FA8;
		unsigned int uiResolutionGrowEveryFrame;
		UInt8 gapFB0[8];
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

//SHADERS

struct BSReloadShaderI {
public:

	// add
	virtual void ReloadShaders(BSIStream* a_stream) = 0;  // 00
};
STATIC_ASSERT(sizeof(BSReloadShaderI) == 0x8);

class BSShader : public NiRefObject, public BSReloadShaderI {
public:

	// add
	virtual bool SetupTechnique(UInt32 a_currentPass) = 0;													// 02
	virtual void RestoreTechnique(UInt32 a_currentPass) = 0;												// 03
	virtual void SetupMaterial(const BSShaderMaterial* a_material) { return; }								// 04
	virtual void RestoreMaterial(const BSShaderMaterial* a_material) { return; }							// 05
	virtual void SetupMaterialSecondary(const BSShaderMaterial* a_material) { return; }						// 06
	virtual void SetupGeometry(BSRenderPass* a_currentPass) = 0;                                            // 07
	virtual void RestoreGeometry(BSRenderPass* a_currentPass) = 0;                                          // 08
	virtual void GetTechniqueName(UInt32 a_techniqueID, char* a_buffer, UInt32 a_bufferSize);				// 09
	virtual void RecreateRendererData() { return; }                                                         // 0A
	virtual void ReloadShaders(bool a_clear);                                                               // 0B
	virtual SInt32 GetBonesVertexConstant() const { return 0; }												// 0C

	// members
	SInt32 shaderType;																// 018
	//BSShaderTechniqueIDMap::MapType<BSGraphics::VertexShader*> vertexShaders;     // 020
	//BSShaderTechniqueIDMap::MapType<BSGraphics::HullShader*> hullShaders;         // 050
	//BSShaderTechniqueIDMap::MapType<BSGraphics::DomainShader*> domainShaders;     // 080
	//BSShaderTechniqueIDMap::MapType<BSGraphics::PixelShader*> pixelShaders;       // 0B0
	//BSShaderTechniqueIDMap::MapType<BSGraphics::ComputeShader*> computeShaders;   // 0E0
	const char* fxpFilename;														// 110
};
//STATIC_ASSERT(sizeof(BSShader) == 0x118);

namespace BSShaderUtil {
	void AccumulateSceneArray(NiCamera* cam, BSTArray<NiPointer<NiAVObject>>* objs, BSCullingProcess& cullproc, bool a1);
	void AccumulateScene(NiCamera* cam, NiAVObject* obj, BSCullingProcess& cullproc, bool a1);
}
typedef void (*_AccumulateSceneArray)(NiCamera* cam, BSTArray<NiPointer<NiAVObject>>* objs, BSCullingProcess& cullproc, bool a1);
extern RelocAddr<_AccumulateSceneArray> AccumulateSceneArray_Internal;
typedef void (*_AccumulateScene)(NiCamera* cam, NiAVObject* obj, BSCullingProcess& cullproc, bool a1);
extern RelocAddr<_AccumulateScene> AccumulateScene_Internal;

class BSUtilityShader : public BSShader {
public:

	// members
	UInt32 currentTechniqueID;  // 118
	UInt32 currentDecl;         // 11C
};
//STATIC_ASSERT(sizeof(BSUtilityShader) == 0x120);

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

	enum eShadowMode {};

	enum etRenderMode : UInt16 {
		unk0 = 0,

		unk18 = 18,
	};

	enum usRenderFlags : UInt16 {};

	class State {
	public:
		ShadowSceneNode					* pShadowSceneNode[4];
		UInt8							gap20[8];
		float							timerMode[5];
		float							field_3C;
		UInt32							uiFrameCount;
		NiColorA						loadedRange;
		bool							isInterior;
		bool							bLightBrite;
		UInt8							unk56;
		bool							rgbspecMAYBE;
		bool							usePremultAlpha;
		bool							field_59;
		float							opacityAlpha;
		bool							useCharacterLighting;
		SInt8							bScreenSpaceReflections;
		bool							bScreenSpaceSubsurfaceScattering;
		UInt32							uiPipboyScreenTarget;
		NiPointer<NiTexture>			pipboyFXTexture;
		float							fPipboyScreenEmitIntensityPA;
		float							menuDiffuseIntensity;
		float							menuEmitIntensityWA;
		float							menuDiffuseIntensityWA;
		SInt64							field_80;
		float							field_88;
		float							fLeafAnimDampenDistStart;
		float							fLeafAnimDampenDistEnd;
		NiPoint2						field_94;
		NiPoint2						field_9C;
		float							field_A4;
		UInt8							field_A8;
		SInt8							uiCurrentSceneGraph;
		BSShaderManager::etRenderMode	etRenderMode;
		UInt8							gapB0[16];
		NiTransform						QDirectionalAmbientTransform;
		NiTransform						QLocalDirectionalAmbientTransform;
		NiColorA						QAmbientSpecular;
		SInt8							field_150;
		UInt32							QTextureTransformBufferIndex;
		UInt32							QTextureTransformFlipMode;
		UInt32							uiCameraInWaterState;
		float							camFrustrumFar;
		float							camFrustrumNear;
		float							fWaterIntersect;
		SInt32							field_16C;
		SInt32							field_170;
		SInt32							field_174;
		SInt64							field_178;
		SInt64							field_180;
		float							field_188;
		float							field_18C;
		NiPoint3						field_190;
		NiPoint3						field_19C;
		NiPoint3						field_1A8;
		BSGeometry						* geom_1B8;
		UInt8							gap1C0[4];
		float							fUIMaskRectEdgeSharpness;
		float							field_1C8;
		float							opacity;
		UInt8							gap1D0[8];
		SInt64							field_1D8;
		UInt8							gap1E0[248];
		SInt64							field_2D8;
		UInt8							gap2E0[240];
		float							characterLightRimStrength;
		float							characterLightFillStrength;
		SInt32							field_3D8;
		SInt32							field_3DC;
		SInt32							field_3E0;
		bool							vatsEffectOff;
		SInt8							field_3E5;
		SInt8							field_3E6;
		SInt8							field_3E7;
		SInt8							field_3E8;
		bool							field_3E9;
		bool							field_3EA;
		bool							field_3EB;
	};
	MEMBER_FN_PREFIX(BSShaderManager);
	DEFINE_MEMBER_FN(GetTexture, void, 0x027D61F0, const char* filePath, bool a2, NiPointer<NiTexture>& returnTex, bool a4, bool a5, bool a6);


	void GetTexture(const char* filePath, bool a2, NiPointer<NiTexture>& returnTex, bool a4, bool a5, bool a6);
};

class BSShaderAccumulator : public NiAlphaAccumulator {
public:
	
	enum BATCHRENDERER_CREATION_MODE {};
	
	BSShaderAccumulator() { CALL_MEMBER_FN(this, ctor)(); };
	//virtual ~BSShaderAccumulator();
	
	//BSShaderAccumulator::StartAccumulating
	//BSShaderAccumulator::FinishAccumulating
	//NiAlphaAccumulator::RegisterObjectArray
	//BSShaderAccumulator::StartGroupingAlphas
	//BSShaderAccumulator::StopGroupingAlphas
	//BSShaderAccumulator::RegisterObject
	//BSShaderAccumulator::FinishAccumulatingPreResolveDepth
	//BSShaderAccumulator::FinishAccumulatingPostResolveDepth

	SInt32							field_58;
	SInt8							field_5C;
	float							StoredSunOcclustionPercent;
	BSGraphics::OcclusionQuery		* occlusionQuery;
	SInt64							field_70;
	SInt32							field_78;
	SInt8							field_7C;
	SInt64							field_80;
	SInt64							field_88;
	SInt32							field_90;
	SInt8							field_94;
	SInt64							field_98;
	SInt64							field_A0;
	SInt32							field_A8;
	SInt32							field_AC;
	bool							m_firstPerson;
	bool							QZPrePass;
	NiColorA						QSilhouetteColor;
	SInt8							QRenderDecals;
	SInt8							field_C5;
	BSBatchRenderer					BatchRenderer;
	SInt64							field_548;
	SInt8							field_550;
	ShadowSceneNode					* ShadowSceneNode;
	BSShaderManager::etRenderMode	renderMode;
	BSLight							* shadowLight;
	NiPoint3						QEyePosition;
	UInt32							QDepthPassIndex;

	MEMBER_FN_PREFIX(BSShaderAccumulator);
	DEFINE_MEMBER_FN(ctor, void, 0x0282CC00);
	DEFINE_MEMBER_FN(ClearActivePasses, void, 0x0282F080, bool);
	DEFINE_MEMBER_FN(ClearEffectPasses, void, 0x0282EED0);
	DEFINE_MEMBER_FN(ClearGroupPasses, void, 0x0282EAD0, SInt32, bool);
	DEFINE_MEMBER_FN(RenderBatches, void, 0x0282EF70, SInt32, bool, SInt32);
	DEFINE_MEMBER_FN(RenderBlendedDecals, void, 0x0282E300);
	DEFINE_MEMBER_FN(RenderOpaqueDecals, void, 0x0282E190);

	void ClearActivePasses(bool a1);
	void ClearEffectPasses();
	void ClearGroupPasses(SInt32 a1, bool a2);
	void RenderBatches(SInt32 a1, bool a2, SInt32 a3);
	void RenderBlendedDecals();
	void RenderOpaqueDecals();
};

namespace BSShaderUtil {
	typedef void (*_SetCameraFOV)(BSSceneGraph* scene, float FOV, bool a3, NiCamera* cam, bool a4);
	void SetCameraFOV(BSSceneGraph* scene, float FOV, bool a3, NiCamera* cam, bool a4);
	extern RelocAddr<_SetCameraFOV> SetCameraFOV_Internal;
}

//IMAGESPACE

class ImageSpaceEffectParam {
public:
	virtual ~ImageSpaceEffectParam() {};

	MEMBER_FN_PREFIX(ImageSpaceEffectParam);

};

class ImageSpaceShaderParam : public ImageSpaceEffectParam {
public:
	ImageSpaceShaderParam() { CALL_MEMBER_FN(this, ctor)(); };
	//virtual ~ImageSpaceShaderParam();

	MEMBER_FN_PREFIX(ImageSpaceShaderParam);
	DEFINE_MEMBER_FN(ctor, void, 0x0282C200);
	DEFINE_MEMBER_FN(ResizeConstantGroup, void, 0x001E0C80, SInt32, SInt32);
	DEFINE_MEMBER_FN(SetPixelConstant, void, 0x0282C460, SInt32, float, float, float, float);

	void ResizeConstantGroup(SInt32 a1, SInt32 a2);
	void SetPixelConstant(SInt32 a1, float a2, float a3, float a4, float a5);
};

class ImageSpaceEffect {
public:
	class EffectInput {
	public:

	};
	class EffectDesc {
	public:

	};

	virtual ~ImageSpaceEffect() {};
	virtual void Render(BSTriShape*, ImageSpaceEffectParam*) {};
	virtual void Dispatch(ImageSpaceEffectParam*, bool, UInt32, EffectDesc*) {};
	virtual void Setup(ImageSpaceManager*, ImageSpaceEffectParam*) {};
	virtual void Shutdown(void) {};
	virtual void BorrowTextures(ImageSpaceEffectParam*) {};
	virtual void ReturnTextures(void) {};
	virtual void UpdateComputeShaderParam(UInt32) {};
	virtual bool IsActive(void) {};
	virtual bool UpdateParams(ImageSpaceEffectParam*) {};
	virtual bool SetRenderStates(ImageSpaceEffectParam*) {};
	virtual bool RestoreRenderStates(ImageSpaceEffectParam*) {};

	UInt64 unk08;
	NiTArray<ImageSpaceEffect*> pImageSpaceEffectArray;
	NiTArray<ImageSpaceEffectParam*> pImageSpaceEffectParamArray;
	NiTArray<ImageSpaceTexture*> texArray;
	NiTArray<ImageSpaceTexture*> field_58;
	NiTArray<EffectInput*> pEffectInputArray;
	NiTArray<int*> pIntArray;
	bool field_A0;
	UInt8 field_A1;
	UInt32 field_A4;
	bool UseDynamicResolution;
	NiPointer<NiTexture> tex_B0;
	NiPointer<NiTexture> field_B8;
	UInt32 field_C0;
	UInt8 field_C4;
	UInt8 field_C5;
	UInt8 field_C6;
	UInt8 field_C7;
	UInt8 field_C8;
	UInt64 field_D0;
	UInt64 field_D8;
	BSTArray<void*> field_E0;
	BSTArray<void*> field_F8;
	UInt8 gap110[44];
	UInt8 field_13C;

	MEMBER_FN_PREFIX(ImageSpaceEffect);
};

class ImageSpaceTexture {
public:

	MEMBER_FN_PREFIX(ImageSpaceTexture);
};

class ImageSpaceBaseData {
	float hdrData[9];
	float cinematicData[3];
	float tintData[4];
	float dofData[6];
};

class ImageSpaceLUTData {
	BSFixedString field_0;
	UInt8 gap8[24];
	BSFixedString field_20;
	NiPointer<NiTexture> field_28;
	NiPointer<NiTexture> field_30;
	UInt64 field_38;
	UInt64 field_40;
	UInt64 field_48;
	UInt64 final1;
};

class ImageSpaceManager {
public:

	enum ImageSpaceEffectEnum {
		kRefraction = 5,
		kGetHit = 11,
		kVatsTarget = 12,
		kFullScreenColor = 13,
		
		kMap = 22,

		kNoise = 62,
		kRainSplash = 63,
		
		kPipboyScreen = 66,
		kHUDGlass = 67,
		kModMenu = 68,

		kBSCopy = 72,
		kBSCopyScaleBias = 73,
		kBSCopyVisAlpha = 74,
		kBSGreyScale = 75,
		kBSDownsampleDepth = 76,
		kBSCopyStencil = 77,
		kBSCopyWaterMask = 78,
		
		kBSRefraction = 80,
		kBSDoubleVision = 81,
		kBSTextureMask = 82,
		kBSMap = 83,

		kBSDepthOfFieldFogged = 87,
		kBSDepthOfFieldSplitScreen = 88,
		
		kBSNoiseScrollAndBlend = 150,
		kBSNoiseNormalmap = 151,
		kBSLocalMap = 152,
		kBSLocalMapCompanion = 153,
		kBSAlphaBlend = 154,
		kBSPipboyScreen = 155,
		kBSHUDGlass = 156,
		kBSHUDGlassDropShadow = 157,
		kBSHUDGlassBlurY = 158,
		kBSHUDGlassBlurX = 159,
		kBSHUDGlassMarkers = 160,
		kBSVatsTargetDebug = 161,
		kBSVatsTarget = 162,
		kBSModMenuEffect = 163,
		kBSModMenuGlowComposite = 164,
		kBSAmbientOcclusion = 165,
		kBSAmbientOcclusionBlur = 166,
		kBSVLSSpotLight = 167,
		kBSVLSApplication = 168,
		kBSVLSComposite = 169,
		kBSVLSSliceCoord = 170,
		kBSVLSSliceInterp = 171,
		kBSVLSSliceStencil = 172,

		kBSTemporalAAPipboy = 191,
		kBSTemporalAAPowerArmorPipboy = 192,

		kBSRainSplash = 200,
		kBSRainSplashUpdate = 201,
		kBSRainSplashDraw = 202,

		kBSFullScreenColor = 205,

		kBSHUDGlassCopy = 207,
	};

	UInt64 field_0;
	UInt64 field_8;
	NiTArray<ImageSpaceEffect> effectArray;
	NiPointer<BSTriShape> ScreenTriShape;
	BSTriShape* ScreenTriShapeColors;
	NiPointer<BSTriShape> DynamicScreenTriShape;
	NiPointer<BSTriShape> PartialScreenTriShape;
	bool field_48;
	UInt32 field_4C;
	UInt64 field_50;
	UInt32 field_58;
	UInt32 field_5C;
	ImageSpaceBaseData* CurrentBaseData;
	ImageSpaceBaseData* OverrideBaseData;
	ImageSpaceBaseData* UnderwaterBaseData;
	ImageSpaceBaseData* ConsoleBaseData;
	ImageSpaceBaseData field_80;
	UInt8 gapD8[88];
	ImageSpaceLUTData field_130;
	UInt8 gap188[24];
	ImageSpaceLUTData* imageSpaceLUT;
	UInt8 gap1A8[8];
	UInt32 field_1B0;
	UInt8 field_1B4;
	UInt8 field_1B5;
	UInt8 field_1B6;

	MEMBER_FN_PREFIX(ImageSpaceManager);

	DEFINE_MEMBER_FN(GetEffect, ImageSpaceEffect*, 0x001E0660, ImageSpaceEffectEnum);

	DEFINE_MEMBER_FN(RenderEffect_1, void, 0x027DA130, ImageSpaceEffectEnum, SInt32, ImageSpaceEffectParam*);
	DEFINE_MEMBER_FN(RenderEffect_2, void, 0x027DA240, ImageSpaceEffect*, SInt32, SInt32, ImageSpaceEffectParam*);
	DEFINE_MEMBER_FN(RenderEffect_3, void, 0x027DA3B0, ImageSpaceEffect*, SInt32, SInt32, SInt32, ImageSpaceEffectParam*);

	DEFINE_MEMBER_FN(RenderEffectHelper_2, void, 0x027DA0D0, ImageSpaceEffectEnum, SInt32, SInt32, ImageSpaceEffectParam*);

	DEFINE_MEMBER_FN(RenderEffect_Tex_1, void, 0x027DA780, ImageSpaceEffect*, NiTexture*, SInt32, ImageSpaceEffectParam*);
	DEFINE_MEMBER_FN(RenderEffect_Tex_2, void, 0x027DA5C0, ImageSpaceEffectEnum, NiTexture*, NiTexture*, SInt32, ImageSpaceEffectParam*);

	DEFINE_MEMBER_FN(RenderEffectHelper_Tex_1, void, 0x027DA560, ImageSpaceEffectEnum, NiTexture*, SInt32, ImageSpaceEffectParam*);

	DEFINE_MEMBER_FN(SelectScreenShape, NiPointer<BSTriShape>&, 0x027E14E0, ImageSpaceEffect*);

	ImageSpaceEffect* GetEffect(ImageSpaceEffectEnum);

	void RenderEffect_1(ImageSpaceEffectEnum, SInt32, ImageSpaceEffectParam*);
	void RenderEffect_2(ImageSpaceEffect*, SInt32, SInt32, ImageSpaceEffectParam*);
	void RenderEffect_3(ImageSpaceEffect*, SInt32, SInt32, SInt32, ImageSpaceEffectParam*);

	void RenderEffectHelper_2(ImageSpaceEffectEnum, SInt32, SInt32, ImageSpaceEffectParam*);

	void RenderEffect_Tex_1(ImageSpaceEffect*, NiTexture*, SInt32, ImageSpaceEffectParam*);
	void RenderEffect_Tex_2(ImageSpaceEffectEnum, NiTexture*, NiTexture*, SInt32, ImageSpaceEffectParam*);

	void RenderEffectHelper_Tex_1(ImageSpaceEffectEnum, NiTexture*, SInt32, ImageSpaceEffectParam*);

	NiPointer<BSTriShape>& SelectScreenShape(ImageSpaceEffect*);
};

class BSImagespaceShader : public ImageSpaceEffect {
public:
	//virtual ~BSImagespaceShader();
	//virtual void Render(BSTriShape*, ImageSpaceEffectParam*) override;
	//virtual void Dispatch(ImageSpaceEffectParam*, bool, UInt32, EffectDesc*) override;
	//virtual void Setup(ImageSpaceManager*, ImageSpaceEffectParam*);
	//virtual void Shutdown(void) override;
	//virtual void BorrowTextures(ImageSpaceEffectParam*);
	//virtual void ReturnTextures(void);
	//virtual void UpdateComputeShaderParam(UInt32);
	//virtual bool IsActive(void);
	//virtual bool UpdateParams(ImageSpaceEffectParam*);
	//virtual bool SetRenderStates(ImageSpaceEffectParam*);
	//virtual bool RestoreRenderStates(ImageSpaceEffectParam*);

	MEMBER_FN_PREFIX(BSImagespaceShader);
};

//EXTERN

extern RelocPtr <BSGraphics::Context*>					pCurContext;
extern RelocPtr <BSGraphics::Context*>					pDefaultContext;
extern RelocPtr <BSGraphics::Renderer>					BSGraphics_gRenderer;
extern RelocPtr <BSGraphics::RendererData*>				pRendererData;
extern RelocPtr <BSGraphics::RendererWindow*>			pRendererWindow;
extern RelocPtr <BSGraphics::State>						BSGraphics_gState;
extern RelocPtr <BSGraphics::RenderTargetManager>		BSGraphics_gRenderTargetManager;
extern RelocPtr <BSShaderAccumulator*>					pCurrentShaderAccumulator;
extern RelocPtr <BSShaderManager::State>				ShaderManager_gState;
extern RelocPtr <BSShaderManager>						gShaderManagerInstance;
extern RelocPtr <NiCamera*>								BSShaderManager_spCamera;
extern RelocPtr <BSShaderMaterial*>						pShaderMaterialDefault;
extern RelocPtr <BSShaderResourceManager>				gShaderResourceManagerInstance;
extern RelocPtr <ID3D11Device*>							pDevice;
extern RelocPtr <ID3D11DeviceContext*>					pImmediateContext;
extern RelocPtr <ID3D11DeviceContext*>					pMainContext;
extern RelocPtr <ID3D11DeviceContext*>					pContext;
extern RelocPtr <ImageSpaceManager*>					ImageSpaceManager_pInstance;
extern RelocPtr <ImageSpaceShaderParam>					BSImagespaceShader_DefaultParam;
extern RelocPtr <ImageSpaceShaderParam*>				BSImagespaceShader_pCurrentParam;
