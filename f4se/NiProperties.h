#pragma once

#include "f4se/BSGraphics.h"
#include "f4se/BSLight.h"
#include "f4se/NiObjects.h"
#include "f4se/NiTextures.h"
#include "f4se/NiTypes.h"

class BSEffectShaderMaterial;
class BSFadeNode;
class BSParticleShaderCubeEmitter;

class BSRenderPass;
class BSShader;
class BSShaderAccumulator;

class BSShaderMaterial;

class NiProperty : public NiObjectNET
{
public:
	virtual ~NiProperty();
	//NiRefObject::DeleteThis
	//virtual NiRTTI				* GetRTTI() override;
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
	//virtual NiObject			* CreateClone(NiCloningProcess* unk1) override { return nullptr; };
	//virtual void				LoadBinary(void* stream) override { }; // LoadBinary
	//virtual void				LinkObject() override { }; //1C
	//virtual bool				RegisterStreamables() override { return false; }; //1D
	//virtual void				SaveBinary(void* stream) override { }; // SaveBinary
	//virtual bool				IsEqual(NiObject* object) override { return false; }	// IsEqual
	//NiObjectNET::ProcessClone
	//NiObjectNET::PostLinkObject
	//NiObject::StreamCanSkip
	//NiObject::GetStreamableRTTI
	//NiObject::GetBlockAllocationSize
	//NiObject::GetGroup
	//NiObject::SetGroup
	//NiObject::IsNiControllerManager
	virtual SInt32				GetType(void);
	virtual void				Update(NiAVObject::NiUpdateData&);

	enum
	{
		kTypeAlpha = 0,
		kTypeShade = 1
	};

	
};

// 30
class NiAlphaProperty : public NiProperty
{
public:
	virtual ~NiAlphaProperty();
	//NiRefObject::DeleteThis
	//virtual NiRTTI				* GetRTTI() override;
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
	//NiAlphaProperty::CreateClone
	//NiAlphaProperty::LoadBinary
	//NiAlphaProperty::LinkObject
	//NiAlphaProperty::RegisterStreamables
	//NiAlphaProperty::SaveBinary
	//NiAlphaProperty::IsEqual
	//NiObjectNET::ProcessClone
	//NiObjectNET::PostLinkObject
	//NiObject::StreamCanSkip
	//NiObject::GetStreamableRTTI
	//NiObject::GetBlockAllocationSize
	//NiObject::GetGroup
	//NiObject::SetGroup
	//NiObject::IsNiControllerManager
	//NiAlphaProperty::Type
	//NiProperty::Update

	enum AlphaFunction
	{
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

	enum TestFunction
	{
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
class NiShadeProperty : public NiProperty
{
public:
	virtual ~NiShadeProperty();
	//NiRefObject::DeleteThis
	//virtual NiRTTI				* GetRTTI() override;
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
	//NiShadeProperty::CreateClone
	//NiShadeProperty::LoadBinary
	//NiShadeProperty::LinkObject
	//NiShadeProperty::RegisterStreamables
	//NiShadeProperty::SaveBinary
	//NiShadeProperty::IsEqual
	//NiObjectNET::ProcessClone
	//NiObjectNET::PostLinkObject
	//NiObject::StreamCanSkip
	//NiObject::GetStreamableRTTI
	//NiObject::GetBlockAllocationSize
	//NiObject::GetGroup
	//NiObject::SetGroup
	//NiObject::IsNiControllerManager
	//NiShadeProperty::Type
	//NiProperty::Update
	virtual void SetupGeometry();

};

// 90
class BSEffectShaderData : public BSIntrusiveRefCounted
{
public:
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

	inline BSEffectShaderData() {
		CALL_MEMBER_FN(this, ctor)();
	}
	inline ~BSEffectShaderData() {
		CALL_MEMBER_FN(this, dtor)();
	}

	MEMBER_FN_PREFIX(BSEffectShaderData);
	DEFINE_MEMBER_FN(ctor, void, 0x001D10C0);
	DEFINE_MEMBER_FN(dtor, void, 0x001D1500);

};

// 70
class BSShaderProperty : public NiShadeProperty
{
public:

	class RenderPassArray {
	public:

		// members
		BSRenderPass* passList{ nullptr };  // 0
	};
	STATIC_ASSERT(sizeof(RenderPassArray) == 0x8);

	class ForEachVisitor {
	public:
		virtual ~ForEachVisitor();

	};

	virtual ~BSShaderProperty();
	//NiRefObject::DeleteThis
	//virtual NiRTTI				* GetRTTI() override;
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
	//BSShaderProperty::CreateClone
	//BSShaderProperty::LoadBinary
	//BSShaderProperty::LinkObject
	//BSShaderProperty::RegisterStreamables
	//BSShaderProperty::SaveBinary
	//BSShaderProperty::IsEqual
	//NiObjectNET::ProcessClone
	//BSShaderProperty::PostLinkObject
	//NiObject::StreamCanSkip
	//NiObject::GetStreamableRTTI
	//NiObject::GetBlockAllocationSize
	//NiObject::GetGroup
	//NiObject::SetGroup
	//NiObject::IsNiControllerManager
	//NiShadeProperty::Type
	//NiProperty::Update
	//BSShaderProperty::SetupGeometry
	//_purecall_0
	virtual RenderPassArray				* GetRenderPasses_ShadowMapOrMask(BSGeometry* a_geom, UInt32, BSShaderAccumulator*);
	virtual RenderPassArray				* GetRenderPasses_LocalMap(BSGeometry*, UInt32, BSShaderAccumulator*);
	virtual BSRenderPass				* CreateVatsMaskRenderPass(BSGeometry*);
	virtual UInt16						GetNumberofPasses(BSGeometry*);
	virtual BSRenderPass				* GetRenderDepthPass(BSGeometry*);
	virtual bool						CanMerge(BSShaderProperty*);
	virtual void						SetMaterialAlpha(float);
	virtual float						QMaterialAlpha(void);
	virtual BSFixedString				& GetRootName(void);
	virtual SInt32						ForEachTexture(ForEachVisitor& functor);
	virtual SInt32						QShader(void);
	virtual void						ClearUnusedMaterialValues(void);
	virtual BSShaderProperty			* ClarifyShader(BSGeometry*, bool, bool);
	virtual NiTexture					* GetBaseTexture(void);
	virtual RenderPassArray				* GetWaterFogPassList(BSGeometry*);
	virtual bool						AcceptsEffectData(void);
	virtual void						PrecacheTextures(void);
	virtual UInt32						DetermineUtilityShaderDecl(void);
	virtual UInt32						GetMaterialType(void);
	virtual void						DoClearRenderPasses(void);

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

	enum : UInt64
	{
		kShaderFlags_GrayscaleToPalette	= 0x0000000080000000ULL,	//00000000|80000000 ???
		kShaderFlags_Hair				= 0x0000400000000000ULL,	//00004000|00000000 ???
		kShaderFlags_Refraction			= 0x0000000000008000ULL,	//00000000|00008000 ???
		kShaderFlags_EmitColor			= 0x0000000000400000ULL,	//00000000|00400000 ???
		kShaderFlags_NoExternalEmit		= 0x4000000000000000ULL		//40000000|00000000 ???
	};

	MEMBER_FN_PREFIX(BSShaderProperty);
	DEFINE_MEMBER_FN(SetMaterial, bool, 0x027BC560, BSShaderMaterial * material, bool unk1);
	DEFINE_MEMBER_FN(SetFlag, void, 0x027BC3E0, UInt8 flags, bool enabled); // sets or unsets particular flags

	DEFINE_MEMBER_FN(RenderPassArray_Add, BSRenderPass*, 0x027BBB70, BSShader*, BSShaderProperty*, BSGeometry*, UInt32, UInt8, BSLight*, BSLight*, BSLight*, BSLight*);
	DEFINE_MEMBER_FN(RenderPassArray_Replace, BSRenderPass*, 0x027BBC80, BSRenderPass*, BSShader*, BSShaderProperty*, BSGeometry*, UInt32);

	DEFINE_MEMBER_FN(SetEffectShaderData, void, 0x001D1DF0, BSEffectShaderData* shaderData);

	BSRenderPass* RenderPassArray_Add(BSShader*, BSShaderProperty*, BSGeometry*, UInt32, UInt8, BSLight*, BSLight*, BSLight*, BSLight*);
	BSRenderPass* RenderPassArray_Replace(BSRenderPass*, BSShader*, BSShaderProperty*, BSGeometry*, UInt32);

	void SetEffectShaderData(BSEffectShaderData* shaderData);
};
STATIC_ASSERT(sizeof(BSShaderProperty) == 0x70);

// 88
class BSEffectShaderProperty : public BSShaderProperty
{
public:
	virtual ~BSEffectShaderProperty();

	BSParticleShaderCubeEmitter		* pEnvCubeEmitter;		// 70
	NiColor							* pExternalEmitColor;	// 78
	UInt32							uBaseTextureIndex;		// 80
	float							unk84;					// 84

	MEMBER_FN_PREFIX(BSEffectShaderProperty);
	DEFINE_MEMBER_FN(ctor, void, 0x027CAAC0);

	static BSEffectShaderProperty* Create();

	DEFINE_MEMBER_FN(QEffectShaderMaterial, BSEffectShaderMaterial*, 0x001E0930);
	DEFINE_MEMBER_FN(SetupGeometry, bool, 0x027CAB60, BSGeometry* geom);
	DEFINE_MEMBER_FN(GetRenderPasses, BSShaderProperty::RenderPassArray*, 0x027CAE10, BSGeometry*, UInt32, BSShaderAccumulator*);

	BSEffectShaderMaterial* QEffectShaderMaterial();
	bool SetupGeometry(BSGeometry* geom);
	BSShaderProperty::RenderPassArray* GetRenderPasses(BSGeometry* a_geom, UInt32 a1, BSShaderAccumulator* a_accumulator);
};
STATIC_ASSERT(sizeof(BSEffectShaderProperty) == 0x88);

// E8
class BSLightingShaderProperty : public BSShaderProperty
{
public:
	virtual ~BSLightingShaderProperty();
	//NiRefObject::DeleteThis
	virtual NiRTTI				* GetRTTI() override;

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
	DEFINE_MEMBER_FN(MakeValidForRendering, void, 0x027CCB70, BSGeometry * geometry); // previously InvalidateShader
	DEFINE_MEMBER_FN(ApplyMaterial, bool, 0x00054170); // Calls BSShaderProperty::SetMaterial
	DEFINE_MEMBER_FN(LoadTextureSet, void, 0x027CD200, UInt32 unk1); // unk1 usually 0, called after material Releases textures (previously InvalidateTextures)

	static BSLightingShaderProperty * Create();
};
STATIC_ASSERT(sizeof(BSLightingShaderProperty) == 0xE8);

// C0
class BSWaterShaderProperty : public BSShaderProperty
{
public:
	UInt32						uiWaterFlags;						// 70
	UInt32						iStencilMask;						// 74
	NiPlane						kWaterPlane;						// 78
	BSRenderPass				* kSimpleRenderPassArray;			// 88
	BSRenderPass				* kRainOcclusionMapRenderPassList;	// 90
	BSShaderPropertyLightData	kLightData;							// 98
};

STATIC_ASSERT(sizeof(BSWaterShaderProperty) == 0xC0);
