#pragma once

#include "f4se_common/Relocation.h"
#include "f4se_common/Utilities.h"

#include "f4se/BSGeometry.h"
#include "f4se/NiTextures.h"
#include "f4se/NiMaterials.h"
#include "d3d11.h"

class BSGeometryData;
class BSCullingGroup;

class ImageSpaceManager;
class ImageSpaceEffect;
class BSShaderMaterial;

class NiCamera;

//Other Stuff

class NiAccumulator : public NiObject {
public:
	virtual ~NiAccumulator();
	//NiRefObject::DeleteThis
	//NiAccumulator::GetRTTI
	//NiObject::IsNode
	//NiObject::IsNode
	//NiObject::IsSwitchNode
	//NiObject::IsFadeNode
	//NiObject::IsMultiBoundNode
	//NiObject::IsGeometry
	//NiObject::IsTriStrips
	//NiObject::IsTriShape
	//NiObject::IsDynamicTriShape
	//NiObject::IsSegmentedTriShape
	//NiObject::IsSubIndexTriShape
	//NiObject::IsNiGeometry
	//NiObject::IsNiTriBasedGeom
	//NiObject::IsNiTriShape
	//NiObject::IsParticlesGeom
	//NiObject::IsParticleSystem
	//NiObject::IsLinesGeom
	//NiObject::IsLight
	//NiObject::IsBhkNiCollisionObject
	//NiObject::IsBhkBlendCollisionObject
	//NiObject::IsBhkRigidBody
	//NiObject::IsBhkLimitedHingeConstraint
	//NiObject::IsbhkNPCollisionObject
	//NiObject::CreateClone
	//NiAccumulator::LoadBinary
	//NiAccumulator::LinkObject
	//NiAccumulator::RegisterStreamables
	//NiAccumulator::SaveBinary
	//NiAccumulator::IsEqual
	//NiObject::ProcessClone
	//NiObject::PostLinkObject
	//NiObject::StreamCanSkip
	//NiObject::GetStreamableRTTI
	//NiObject::GetBlockAllocationSize
	//NiObject::GetGroup
	//NiObject::SetGroup
	//NiObject::IsNiControllerManager
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
	virtual ~NiBackToFrontAccumulator();

	char			_pad[24];
	int				m_iNumItems;
	int				m_iMaxItems;
	BSGeometry** m_ppkItems;
	float* m_pfDepths;
	int				m_iCurrItem;
};

class NiAlphaAccumulator : public NiBackToFrontAccumulator {
public:
	virtual ~NiAlphaAccumulator();

	bool m_bObserveNoSortHint;
	bool m_bSortByClosestPoint;
	bool m_bInterfaceSort;
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


		DEFINE_MEMBER_FN(AcquireCubemap, void, 0x01D32BF0, SInt32 target);
		DEFINE_MEMBER_FN(AcquireDepthStencil, void, 0x01D32AE0, SInt32 target);
		DEFINE_MEMBER_FN(AcquireRenderTarget, void, 0x01D329D0, SInt32 target);
		DEFINE_MEMBER_FN(CopyRenderTargetToClipboard, void, 0x01D32990, SInt32 target);
		DEFINE_MEMBER_FN(CopyRenderTargetToRenderTargetCopy, void, 0x01D329B0, SInt32 target, SInt32 target2);
		DEFINE_MEMBER_FN(CopyRenderTargetToTexture, void, 0x01D32960, SInt32 target, Texture * tex, bool a3, bool a4);
		DEFINE_MEMBER_FN(CreateCubeMapRenderTarget, void, 0x01D312D0, SInt32 target, CubeMapRenderTargetProperties & cubeProps, TARGET_PERSISTENCY a3);
		DEFINE_MEMBER_FN(CreateDepthStencilTarget, void, 0x01D310C0, SInt32 target, DepthStencilTargetProperties & depthProps, TARGET_PERSISTENCY a3);
		DEFINE_MEMBER_FN(CreateRenderTarget, void, 0x01D30E90, SInt32 target, RenderTargetProperties & targetProps, TARGET_PERSISTENCY a3);
		DEFINE_MEMBER_FN(ReleaseCubemap, void, 0x01D32C60, SInt32 target);
		DEFINE_MEMBER_FN(ReleaseDepthStencil, void, 0x01D32B50, SInt32 target);
		DEFINE_MEMBER_FN(ReleaseTarget, void, 0x01D32A40, SInt32 target);
	};
};
STATIC_ASSERT(std::is_empty_v<BSGraphics>);

//SHADERS

class BSIStream;

struct BSReloadShaderI {
public:

	// add
	virtual void ReloadShaders(BSIStream* a_stream) = 0;  // 00
};
STATIC_ASSERT(sizeof(BSReloadShaderI) == 0x8);

class BSRenderPass {
public:
	//BSShader* unk;
	//BSShader* m_Shader;
	//BSShaderProperty* m_ShaderProperty;
	//BSGeometry* m_Geometry;
	//__int64 unk2;
	//BSRenderPass* m_Next;
	//BSLight** m_SceneLights;
	//BSRenderPass* m_next;
	//BSRenderPass* m_PassGroupNext;
	//unsigned int m_PassEnum;
	//__int8 field_4C;
	//char field_4D;
	//__int8 field_4E;
	//char field_4F;
	//unsigned __int8 m_NumLights;
};

class BSShader : public NiRefObject, public BSReloadShaderI
{
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

class BSUtilityShader : public BSShader
{
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

	enum eShadowMode {
	};

	enum etRenderMode : UInt16 {
	};

	enum usRenderFlags : UInt16 {
	};

	class State {
	public:

	};
	MEMBER_FN_PREFIX(BSShaderManager);
	DEFINE_MEMBER_FN(GetTexture, void, 0x027D61F0, const char* filePath, bool a2, NiPointer<NiTexture>& returnTex, bool a4, bool a5, bool a6);


	void GetTexture(const char* filePath, bool a2, NiPointer<NiTexture>& returnTex, bool a4, bool a5, bool a6);
};

class BSShaderAccumulator : public NiAlphaAccumulator {
public:
	virtual ~BSShaderAccumulator();
	//NiRefObject::DeleteThis
	//BSShaderAccumulator::GetRTTI
	//NiObject::IsNode
	//NiObject::IsNode
	//NiObject::IsSwitchNode
	//NiObject::IsFadeNode
	//NiObject::IsMultiBoundNode
	//NiObject::IsGeometry
	//NiObject::IsTriStrips
	//NiObject::IsTriShape
	//NiObject::IsDynamicTriShape
	//NiObject::IsSegmentedTriShape
	//NiObject::IsSubIndexTriShape
	//NiObject::IsNiGeometry
	//NiObject::IsNiTriBasedGeom
	//NiObject::IsNiTriShape
	//NiObject::IsParticlesGeom
	//NiObject::IsParticleSystem
	//NiObject::IsLinesGeom
	//NiObject::IsLight
	//NiObject::IsBhkNiCollisionObject
	//NiObject::IsBhkBlendCollisionObject
	//NiObject::IsBhkRigidBody
	//NiObject::IsBhkLimitedHingeConstraint
	//NiObject::IsbhkNPCollisionObject
	//NiObject::CreateClone
	//NiAlphaAccumulator::LoadBinary
	//NiAlphaAccumulator::LinkObject
	//NiAlphaAccumulator::RegisterStreamables
	//NiAlphaAccumulator::SaveBinary
	//NiAlphaAccumulator::IsEqual
	//NiObject::ProcessClone
	//NiObject::PostLinkObject
	//NiObject::StreamCanSkip
	//NiObject::GetStreamableRTTI
	//NiObject::GetBlockAllocationSize
	//NiObject::GetGroup
	//NiObject::SetGroup
	//NiObject::IsNiControllerManager
	//BSShaderAccumulator::StartAccumulating
	//BSShaderAccumulator::FinishAccumulating
	//NiAlphaAccumulator::RegisterObjectArray
	//BSShaderAccumulator::StartGroupingAlphas
	//BSShaderAccumulator::StopGroupingAlphas
	//BSShaderAccumulator::RegisterObject
	//BSShaderAccumulator::FinishAccumulatingPreResolveDepth
	//BSShaderAccumulator::FinishAccumulatingPostResolveDepth
};

//IMAGESPACE

class ImageSpaceEffectParam {
public:
	virtual ~ImageSpaceEffectParam();

	MEMBER_FN_PREFIX(ImageSpaceEffectParam);
};

class ImageSpaceShaderParam : public ImageSpaceEffectParam {
public:
	virtual ~ImageSpaceShaderParam();
};

class ImageSpaceEffect {
public:

	class EffectDesc {
	public:

	};

	virtual ~ImageSpaceEffect();
	virtual void Render(BSTriShape*, ImageSpaceEffectParam*);
	virtual void Dispatch(ImageSpaceEffectParam*, bool, UInt32, EffectDesc*);
	virtual void Setup(ImageSpaceManager*, ImageSpaceEffectParam*);
	virtual void Shutdown(void);
	virtual void BorrowTextures(ImageSpaceEffectParam*);
	virtual void ReturnTextures(void);
	virtual void UpdateComputeShaderParam(UInt32);
	virtual bool IsActive(void);
	virtual bool UpdateParams(ImageSpaceEffectParam*);
	virtual bool SetRenderStates(ImageSpaceEffectParam*);
	virtual bool RestoreRenderStates(ImageSpaceEffectParam*);

	MEMBER_FN_PREFIX(ImageSpaceEffect);
};

class ImageSpaceTexture {
public:

	MEMBER_FN_PREFIX(ImageSpaceTexture);
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
	virtual ~BSImagespaceShader();
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
extern RelocPtr <ImageSpaceShaderParam>					BSImagespaceShader_DefaultParam;
extern RelocPtr <ImageSpaceShaderParam*>				BSImagespaceShader_pCurrentParam;
