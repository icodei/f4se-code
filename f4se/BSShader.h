#pragma once
#include "f4se_common/Utilities.h"
#include "f4se/BSGraphics.h"
#include "f4se/NiAccumulator.h"
#include "f4se/NiObjects.h"

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
		BSS_AMBIENT = 0x1,
		BSS_DIFFUSE = 0x2,
		BSS_TEXTURE = 0x4,
		BSS_SPECULAR = 0x8,
		BSS_SHADOWS = 0x10,
		BSS_FULLMULTIPASSLIGHTING = 0x0F,
		BSS_FULLMULTIPASSLIGHTING_PROJ = 0x0F
	};

	enum UInt32 {
		BSSM_DISABLED = 0x0FFFFFFFF
	};

	enum eShadowMode {

	};

	enum etRenderMode : UInt16 {
		unk0 = 0,

		unk18 = 18,
	};

	enum usRenderFlags : UInt16 {

	};

	class State {
	public:
		ShadowSceneNode* pShadowSceneNode[4];
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
		BSGeometry* geom_1B8;
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
	BSGraphics::OcclusionQuery* occlusionQuery;
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
	ShadowSceneNode* ShadowSceneNode;
	BSShaderManager::etRenderMode	renderMode;
	BSLight* shadowLight;
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
	typedef void (*_SetSceneFOV)(BSSceneGraph* scene, float FOV, bool a3, NiCamera* cam, bool a4);
	void SetCameraFOV(BSSceneGraph* scene, float FOV, bool a3, NiCamera* cam, bool a4);

	typedef void (*_SetCameraFOV)(NiCamera* cam, float FOV, float f_far, float f_near);
	void SetCameraFOV(NiCamera* cam, float FOV, float f_far, float f_near);

	typedef void (*_AccumulateSceneArray)(NiCamera* cam, BSTArray<NiPointer<NiAVObject>>* objs, BSCullingProcess& cullproc, bool a1);
	void AccumulateSceneArray(NiCamera* cam, BSTArray<NiPointer<NiAVObject>>* objs, BSCullingProcess& cullproc, bool a1);

	typedef void (*_AccumulateScene)(NiCamera* cam, NiAVObject* obj, BSCullingProcess& cullproc, bool a1);
	void AccumulateScene(NiCamera* cam, NiAVObject* obj, BSCullingProcess& cullproc, bool a1);
}

extern RelocPtr <BSShaderAccumulator*>		pCurrentShaderAccumulator;
extern RelocPtr <BSShaderManager::State>	ShaderManager_gState;
extern RelocPtr <BSShaderManager>			gShaderManagerInstance;
extern RelocPtr <NiCamera*>					BSShaderManager_spCamera;
extern RelocPtr <BSShaderMaterial*>			pShaderMaterialDefault;
extern RelocPtr <BSShaderResourceManager>	gShaderResourceManagerInstance;