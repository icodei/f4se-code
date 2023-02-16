#pragma once

#include "f4se/BSLight.h"
#include "f4se/NiMaterials.h"
#include "f4se/NiObjects.h"

class BSFadeNode;
class BSGeometry;
class BSParticleShaderCubeEmitter;
class BSRenderPass;
class BSShader;
class BSShaderAccumulator;
class BSEffectShaderMaterial;
class BSShaderMaterial;
class NiTexture;

class NiProperty : public NiObjectNET {
public:
	virtual ~NiProperty();
	//add
	virtual SInt32	GetType(void);
	//virtual void	Update(NiAVObject::NiUpdateData&);

	enum {
		kTypeAlpha = 0,
		kTypeShade = 1
	};

};

// 30
class NiAlphaProperty : public NiProperty {
public:
	virtual ~NiAlphaProperty();

	enum AlphaFunction {
		kAlpha_One = 0,
		kAlpha_Zero,
		kAlpha_SrcColor,
		kAlpha_InvSrcColor,
		kAlpha_DestColor,
		kAlpha_InvDestColor,
		kAlpha_SrcAlpha,
		kAlpha_InvSrcAlpha,
		kAlpha_DestAlpha,
		kAlpha_InvDestAlpha,
		kAlpha_SrcAlphaSat,
		kAlpha_Max_Modes,
	};

	enum TestFunction {
		kTest_Always = 0,
		kTest_Less,
		kTest_Equal,
		kTest_LessEqual,
		kTest_Greater,
		kTest_NotEqual,
		kTest_GreaterEqual,
		kTest_Never,
		kTest_Max_Modes,
	};

	UInt16	alphaFlags;		// 28
	UInt8	alphaThreshold;	// 2A
};

// 28
class NiShadeProperty : public NiProperty {
public:
	virtual ~NiShadeProperty();
	//add
	virtual bool SetupGeometry() {};

};

// 90
class BSEffectShaderData : public BSIntrusiveRefCounted {
public:
	BSEffectShaderData() { CALL_MEMBER_FN(this, ctor)(); };
	~BSEffectShaderData() { CALL_MEMBER_FN(this, dtor)(); };

	bool (__cdecl *pNodeFilterFunction)(BSFixedString *);		// 08
	NiPointer<NiTexture>			spBaseTexture;				// 10
	NiPointer<NiTexture>			spPaletteTexture;			// 18
	NiPointer<NiTexture>			spBlockOutTexture;			// 20
	UInt32							eTextureClampMode;			// 28
	NiColorA						FillColor;					// 2C
	NiColorA						RimColor;					// 3C
	float							fBaseFillScale;				// 4C
	float							fBaseFillAlpha;				// 50
	float							fBaseRimAlpha;				// 54
	float							fUOffset;					// 58
	float							fVOffset;					// 5C
	float							fUScale;					// 60
	float							fVScale;					// 64
	float							fEdgeExponent;				// 68
	float							fBoundDiameter;				// 6C
	NiAlphaProperty::AlphaFunction	eSrcBlend;					// 70
	NiAlphaProperty::AlphaFunction	eDestBlend;					// 78
	UInt32							eZTestFunc;					// 80
	char							ucAlphaTestRef;				// 84
	bool							bGrayscaleToColor;			// 85
	bool							bGrayscaleToAlpha;			// 86
	bool							bIgnoreTextureAlpha;		// 87
	bool							bBaseTextureProjectedUVs;	// 88
	bool							bIgnoreBaseGeomTexAlpha;	// 89
	bool							bLighting;					// 8A
	bool							bAlpha;						// 8B

	MEMBER_FN_PREFIX(BSEffectShaderData);
	DEFINE_MEMBER_FN(ctor, void, 0x001D10C0);
	DEFINE_MEMBER_FN(dtor, void, 0x001D1500);
};

// 70
class BSShaderProperty : public NiShadeProperty {
public:

	class RenderPassArray {
	public:

		// members
		BSRenderPass* passList;  // 0
	};
	STATIC_ASSERT(sizeof(RenderPassArray) == 0x8);

	class ForEachVisitor {
	public:
		//virtual ~ForEachVisitor();

	};

	//virtual ~BSShaderProperty();

	//add
	virtual RenderPassArray*	GetRenderPasses_ShadowMapOrMask(BSGeometry* a_geom, UInt32 a_unk, BSShaderAccumulator* a_accum) { return nullptr; };
	virtual RenderPassArray*	GetRenderPasses_LocalMap(BSGeometry* a_geom, UInt32 a_unk, BSShaderAccumulator* a_accum) { return nullptr; };
	virtual BSRenderPass*		CreateVatsMaskRenderPass(BSGeometry* a_geom) { return nullptr; };
	virtual UInt16				GetNumberofPasses(BSGeometry* a_geom) { return 0; };
	virtual BSRenderPass*		GetRenderDepthPass(BSGeometry* a_geom) { return nullptr; };
	virtual bool				CanMerge(BSShaderProperty* a_prop) { return false; };
	virtual void				SetMaterialAlpha(float a_value) { return; };
	virtual float				QMaterialAlpha(void) { return fAlpha; };
	virtual BSFixedString&		GetRootName(void) { return m_name; };
	virtual SInt32				ForEachTexture(ForEachVisitor& functor) { return 0; };
	virtual SInt32				QShader(void) { return 0; };
	virtual void				ClearUnusedMaterialValues(void) { return; };
	virtual BSShaderProperty*	ClarifyShader(BSGeometry* a_geom, bool a_unk1, bool a_unk2) { return nullptr; };
	virtual NiTexture*			GetBaseTexture(void) { return nullptr; };
	virtual RenderPassArray*	GetWaterFogPassList(BSGeometry* a_geom) { return nullptr; };
	virtual bool				AcceptsEffectData(void) { return false; };
	virtual void				PrecacheTextures(void) { return; };
	virtual UInt32				DetermineUtilityShaderDecl(void) { return 0; };
	virtual UInt32				GetMaterialType(void) { return 0; };
	virtual void				DoClearRenderPasses(void) { return; };

	float					fAlpha;					// 28
	SInt32					iLastRenderPassState;	// 2C - Set to 0x7FFFFFFF somekind of lock?
	UInt64					flags;					// 30
	BSRenderPass			* kRenderPassList;		// 38
	BSRenderPass			* kDebugRenderPassList;	// 40
	BSFadeNode				* pFadeNode;			// 48
	BSEffectShaderData		* pEffectData;			// 50
	BSShaderMaterial		* shaderMaterial;		// 58
	UInt32					uiLastAccumTime;		// 60
	float					fLODFade;				// 64
	BSNonReentrantSpinLock	ClearRenderPassesLock;	// 68

	enum : UInt64 {
		kShaderFlags_GrayscaleToPalette	= 0x0000000080000000ULL,	//00000000|80000000 ???
		kShaderFlags_Hair				= 0x0000400000000000ULL,	//00004000|00000000 ???
		kShaderFlags_Refraction			= 0x0000000000008000ULL,	//00000000|00008000 ???
		kShaderFlags_EmitColor			= 0x0000000000400000ULL,	//00000000|00400000 ???
		kShaderFlags_NoExternalEmit		= 0x4000000000000000ULL		//40000000|00000000 ???
	};

	MEMBER_FN_PREFIX(BSShaderProperty);
	DEFINE_MEMBER_FN(SetMaterial, bool, 0x027BC560, BSShaderMaterial*, bool);
	DEFINE_MEMBER_FN(SetFlag, void, 0x027BC3E0, UInt8, bool); // sets or unsets particular flags

	DEFINE_MEMBER_FN(RenderPassArray_Add, BSRenderPass*, 0x027BBB70, BSShader*, BSShaderProperty*, BSGeometry*, UInt32, UInt8, BSLight*, BSLight*, BSLight*, BSLight*);
	DEFINE_MEMBER_FN(RenderPassArray_Replace, BSRenderPass*, 0x027BBC80, BSRenderPass*, BSShader*, BSShaderProperty*, BSGeometry*, UInt32);

	DEFINE_MEMBER_FN(SetEffectShaderData, void, 0x001D1DF0, BSEffectShaderData*);

	BSRenderPass* RenderPassArray_Add(BSShader* a_shade, BSShaderProperty* a_prop, BSGeometry* a_geom, UInt32 a_unk1, UInt8 a_unk2, BSLight* a_light1, BSLight* a_light2, BSLight* a_light3, BSLight* a_light4);
	BSRenderPass* RenderPassArray_Replace(BSRenderPass* a_pass, BSShader* a_shade, BSShaderProperty* a_prop, BSGeometry* a_geom, UInt32 a_unk);

	void SetEffectShaderData(BSEffectShaderData* shaderData);
};
STATIC_ASSERT(sizeof(BSShaderProperty) == 0x70);

// 88
class BSEffectShaderProperty : public BSShaderProperty {
public:
	BSEffectShaderProperty() { CALL_MEMBER_FN(this, ctor)(); };
	//virtual ~BSEffectShaderProperty();

	BSParticleShaderCubeEmitter		* pEnvCubeEmitter;		// 70
	NiColor							* pExternalEmitColor;	// 78
	UInt32							uBaseTextureIndex;		// 80
	float							unk84;					// 84

	MEMBER_FN_PREFIX(BSEffectShaderProperty);
	DEFINE_MEMBER_FN(ctor, void, 0x027CAAC0);
	DEFINE_MEMBER_FN(GetBaseTexture, NiTexture*, 0x027CBFE0);
	DEFINE_MEMBER_FN(GetRenderPasses, BSShaderProperty::RenderPassArray*, 0x027CAE10, BSGeometry*, UInt32, BSShaderAccumulator*);
	DEFINE_MEMBER_FN(QBaseTexture, NiTexture*, 0x027CC0B0);
	DEFINE_MEMBER_FN(QEffectShaderMaterial, BSEffectShaderMaterial*, 0x001E0930);
	DEFINE_MEMBER_FN(QEnvMap, NiTexture*, 0x027CC0C0);
	DEFINE_MEMBER_FN(QEnvMapMask, NiTexture*, 0x027CC0D0);
	DEFINE_MEMBER_FN(QGrayscaleTexture, NiTexture*, 0x027CC0E0);
	DEFINE_MEMBER_FN(QNormalMap, NiTexture*, 0x027CC110);
	DEFINE_MEMBER_FN(SetEnvMap, void, 0x00551140, NiTexture*);
	DEFINE_MEMBER_FN(SetNormalMap, void, 0x00551390, NiTexture*);
	DEFINE_MEMBER_FN(SetupGeometry, bool, 0x027CAB60, BSGeometry* geom);

	BSShaderProperty::RenderPassArray* GetRenderPasses(BSGeometry* a_geom, UInt32 a1, BSShaderAccumulator* a_accumulator);
	NiTexture* QBaseTexture();
	BSEffectShaderMaterial* QEffectShaderMaterial();
	NiTexture* QEnvMap();
	NiTexture* QEnvMapMask();
	NiTexture* QGrayscaleTexture();
	NiTexture* QNormalMap();
	void SetBaseTexture(NiTexture* newTex);
	void SetEnvMap(NiTexture* newTex);
	void SetEnvMapMask(NiTexture* newTex);
	void SetGrayscaleTexture(NiTexture* newTex);
	void SetNormalMap(NiTexture* newTex);
	bool SetupGeometry(BSGeometry* geom);

	static BSEffectShaderProperty* Create();
};
STATIC_ASSERT(sizeof(BSEffectShaderProperty) == 0x88);

// E8
class BSLightingShaderProperty : public BSShaderProperty {
public:
	//virtual ~BSLightingShaderProperty();
	//NiRefObject::DeleteThis
	//virtual NiRTTI				* GetRTTI() override;

	NiColorA		kProjectedUVColor;				// 70
	NiColorA		kProjectedUVParams;				// 80
	BSRenderPass	* kDepthMapRenderPassListA[3];	// 90
	BSRenderPass	* pDepthRenderPass;				// A8
	BSRenderPass	* kForwardPassList;				// B0
	NiColor			* pEmissiveColor;				// B8
	BSFixedString	rootName;						// C0
	float			fEmitColorScale;				// C8
	float			fForcedDarkness;				// CC
	float			fSpecularLODFade;				// D0
	float			fEnvmapLODFade;					// D4
	UInt32			uiBaseTechniqueID;				// D8
	UInt32			ClearCommandBufferCount;		// DC
	UInt16			usDebugTintIndex;				// E0
	UInt16			uiStencilRef;					// E2
	UInt32			unkE4;							// E4

	MEMBER_FN_PREFIX(BSLightingShaderProperty);
	DEFINE_MEMBER_FN(ctor, BSLightingShaderProperty *, 0x027CC880);
	DEFINE_MEMBER_FN(MakeValidForRendering, void, 0x027CCB70, BSGeometry*); // previously InvalidateShader
	DEFINE_MEMBER_FN(ApplyMaterial, bool, 0x00054170); // Calls BSShaderProperty::SetMaterial
	DEFINE_MEMBER_FN(LoadTextureSet, void, 0x027CD200, UInt32); // unk1 usually 0, called after material Releases textures (previously InvalidateTextures)

	static BSLightingShaderProperty * Create();
};
STATIC_ASSERT(sizeof(BSLightingShaderProperty) == 0xE8);

// C0
class BSWaterShaderProperty : public BSShaderProperty {
public:
	UInt32						uiWaterFlags;						// 70
	UInt32						iStencilMask;						// 74
	NiPlane						kWaterPlane;						// 78
	BSRenderPass				* kSimpleRenderPassArray;			// 88
	BSRenderPass				* kRainOcclusionMapRenderPassList;	// 90
	BSShaderPropertyLightData	kLightData;							// 98
};
STATIC_ASSERT(sizeof(BSWaterShaderProperty) == 0xC0);