#pragma once

#include <functional>

#include "f4se/GameTypes.h"
#include "f4se/NiTypes.h"

class NiRTTI;
class NiExtraData;
class NiNode;
class NiSwitchNode;
class TESObjectREFR;
class NiGeometry;
class BSGeometry;
class BSTriShape;
class BSDynamicTriShape;
class BSSubIndexTriShape;
class NiCloningProcess;
class NiCollisionObject;
class bhkNiCollisionObject;
class bhkBlendCollisionObject;
class bhkNPCollisionObject;
class bhkRigidBody;
class bhkLimitedHingeConstraint;

typedef void (* _WorldToScreen)(NiPoint3 * in, NiPoint3 * out);
extern RelocAddr <_WorldToScreen> WorldToScreen_Internal;

// 10
class NiRefObject
{
public:
	NiRefObject() : m_uiRefCount(0) { };
	virtual ~NiRefObject() { };

	virtual void	DeleteThis(void) { delete this; };	// calls virtual dtor

	void	IncRef(void);
	void	DecRef(void);
	bool	Release(void);

//	void	** _vtbl;		// 00
	volatile SInt32	m_uiRefCount;	// 08
};

// 10
class NiObject : public NiRefObject
{
public:
	virtual ~NiObject();
	virtual NiRTTI				* GetRTTI(void) { return nullptr; };
	virtual NiNode				* GetAsNiNode(void) { return nullptr; };
	virtual NiNode				* GetAsNiNode2(void) { return nullptr; };
	virtual NiSwitchNode		* GetAsNiSwitchNode(void) { return nullptr; };
	virtual void				* GetAsFadeNode() { return nullptr; };
	virtual void				* GetAsMultiBoundNode() { return nullptr; };
	virtual BSGeometry			* GetAsBSGeometry(void) { return nullptr; };
	virtual void				* GetAsBStriStrips() { return nullptr; };
	virtual BSTriShape			* GetAsBSTriShape(void) { return nullptr; };
	virtual BSDynamicTriShape	* GetAsBSDynamicTriShape(void) { return nullptr; };
	virtual void				* GetAsSegmentedTriShape() { return nullptr; };
	virtual BSSubIndexTriShape	* GetAsBSSubIndexTriShape(void) { return nullptr; };
	virtual void				* GetAsNiGeometry() { return nullptr; };
	virtual void				* GetAsNiTriBasedGeom() { return nullptr; };
	virtual void				* GetAsNiTriShape() { return nullptr; };
	virtual void				* GetAsParticlesGeom() { return nullptr; };
	virtual void				* GetAsParticleSystem() { return nullptr; };
	virtual void				* GetAsLinesGeom() { return nullptr; };
	virtual void				* GetAsLight() { return nullptr; };
	virtual bhkNiCollisionObject		* GetAsBhkNiCollisionObject() { return nullptr; };
	virtual bhkBlendCollisionObject		* GetAsBhkBlendCollisionObject() { return nullptr; };
	virtual bhkRigidBody				* GetAsBhkRigidBody() { return nullptr; };
	virtual bhkLimitedHingeConstraint	* GetAsBhkLimitedHingeConstraint() { return nullptr; };
	virtual bhkNPCollisionObject		* GetAsbhkNPCollisionObject() { return nullptr; };
	virtual NiObject			* CreateClone(NiCloningProcess * unk1) { return nullptr; };
	virtual void				LoadBinary(void * stream) { }; // LoadBinary
	virtual void				LinkObject() { }; //1C
	virtual bool				RegisterStreamables() { return false; }; //1D
	virtual void				SaveBinary(void * stream) { }; // SaveBinary
	virtual bool				IsEqual(NiObject * object) { return CALL_MEMBER_FN(this, Internal_IsEqual)(object); }	// IsEqual
	virtual void				ProcessClone(NiCloningProcess& a_cloning) { return; };
	virtual void				PostLinkObject() { };
	virtual bool				StreamCanSkip() { return false; };
	virtual NiRTTI				* GetStreamableRTTI() { return GetRTTI(); };
	virtual bool				GetBlockAllocationSize() { return false; }; //24
	virtual bool				GetGroup() { return false; }; //25
	virtual void				SetGroup() { }; //26
	virtual bool				IsNiControllerManager() { return false; }; //27

	MEMBER_FN_PREFIX(NiObject);
	DEFINE_MEMBER_FN(Internal_IsEqual, bool, 0x01B94A90, NiObject * object);
};

// 28
class NiObjectNET : public NiObject
{
public:
	virtual ~NiObjectNET();
	//virtual void DeleteThis();
	virtual NiRTTI* GetRTTI(void) override { return nullptr; };

	enum CopyType
	{
		COPY_NONE,
		COPY_EXACT,
		COPY_UNIQUE
	};

	BSFixedString					m_name;			// 10
	void							* unk10;		// 18 - Controller?
	tMutexArray<NiExtraData*>		* m_extraData;	// 20 - must be locked/unlocked when altering/acquiring

	bool AddExtraData(NiExtraData * extraData);
	NiExtraData * GetExtraData(const BSFixedString & name);
	bool HasExtraData(const BSFixedString & name) { return GetExtraData(name) != nullptr; }

	MEMBER_FN_PREFIX(NiObjectNET);
	DEFINE_MEMBER_FN(Internal_AddExtraData, bool, 0x01B978C0, NiExtraData * extraData);
};

// 120
class NiAVObject : public NiObjectNET
{
public:

	struct NiUpdateData {
		NiUpdateData() : unk00(nullptr), pCamera(nullptr), flags(0), unk14(0), unk18(0), unk20(0), unk28(0), unk30(0), unk38(0) { }

		void* unk00;			// 00
		void* pCamera;			// 08
		UInt32	flags;				// 10
		UInt32	unk14;				// 14
		UInt64	unk18;				// 18
		UInt64	unk20;				// 20
		UInt64	unk28;				// 28
		UInt64	unk30;				// 30
		UInt64	unk38;				// 38
	};

	virtual void UpdateControllers(NiUpdateData& a_data);
	virtual void PerformOp();
	virtual void AttachProperty();
	virtual void SetMaterialNeedsUpdate(bool unk); // empty?
	virtual void SetDefaultMaterialNeedsUpdateFlag(bool unk); // empty?
	virtual void SetAppCulled(bool set);
	virtual NiAVObject * GetObjectByName(const BSFixedString* nodeName);
	virtual void SetSelectiveUpdateFlags(bool * unk1, bool unk2, bool * unk3);
	virtual void UpdateDownwardPass();
	virtual void UpdateSelectedDownwardPass();
	virtual void UpdateRigidDownwardPass();
	virtual void UpdateWorldBound();
	virtual void UpdateWorldData(NiUpdateData * a_data);
	virtual void UpdateTransformAndBounds(NiUpdateData & a_data);
	virtual void UpdateTransforms(NiUpdateData& a_data);
	virtual void PreAttachUpdate(NiNode* a_eventualParent, NiUpdateData& a_data); //37?
	virtual void PostAttachUpdate(); //38?

	NiNode						* m_parent;				// 28
	NiTransform					m_localTransform;		// 30
	NiTransform					m_worldTransform;		// 70
	NiBound						m_worldBound;			// B0
	NiTransform					m_previousWorld;		// C0
	NiPointer<NiCollisionObject> m_spCollisionObject;	// 100

	enum : UInt64
	{
		kFlagAlwaysDraw = (1 << 11),
		kFlagIsMeshLOD = (1 << 12),
		kFlagFixedBound = (1 << 13),
		kFlagTopFadeNode = (1 << 14),
		kFlagIgnoreFade = (1 << 15),
		kFlagNoAnimSyncX = (1 << 16),
		kFlagNoAnimSyncY = (1 << 17),
		kFlagNoAnimSyncZ = (1 << 18),
		kFlagNoAnimSyncS = (1 << 19),
		kFlagNoDismember = (1 << 20),
		kFlagNoDismemberValidity = (1 << 21),
		kFlagRenderUse = (1 << 22),
		kFlagMaterialsApplied = (1 << 23),
		kFlagHighDetail = (1 << 24),
		kFlagForceUpdate = (1 << 25),
		kFlagPreProcessedNode = (1 << 26),
		kFlagScenegraphChange = (1 << 29),
		kFlagInInstanceGroup = (1LL << 35),
		kFlagLODFadingOut = (1LL << 36),
		kFlagFadedIn = (1LL << 37),
		kFlagForcedFadeOut = (1LL << 38),
		kFlagNotVisible = (1LL << 39),
		kFlagShadowCaster = (1LL << 40),
		kFlagNeedsRendererData = (1LL << 41),
		kFlagAccumulated = (1LL << 42),
		kFlagAlreadyTraversed = (1LL << 43),
		kFlagPickOff = (1LL << 44),
		kFlagUpdateWorldData = (1LL << 45),
		kFlagHasPropController = (1LL << 46),
		kFlagHasLockedChildAccess = (1LL << 47),
		kFlagHasMovingSound = (1LL << 49),
	};

	UInt64			flags;				// 108
	void			* unk110;			// 110
	float			unk118;				// 118
	UInt32			unk11C;				// 11C

	MEMBER_FN_PREFIX(NiAVObject);
	DEFINE_MEMBER_FN(GetAVObjectByName, NiAVObject*, 0x01C93980, BSFixedString * name, bool unk1, bool unk2);
	DEFINE_MEMBER_FN(SetScenegraphChange, void, 0x01BA47C0);

	// Return true in the functor to halt traversal
	bool Visit(const std::function<bool(NiAVObject*)>& functor);
};
STATIC_ASSERT(sizeof(NiAVObject) == 0x120);