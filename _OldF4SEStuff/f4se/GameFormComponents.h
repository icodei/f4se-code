#pragma once

#include "f4se/GameTypes.h"
#include "f4se/NiObjects.h"
#include "f4se/GameEvents.h"
#include "f4se/GameAnimation.h"

class ActorValueInfo;
class BGSAimModel;
class BGSBlockBashData;
class BGSBodyPartData;
class BGSDamageType;
class BGSEquipSlot;
class BGSImpactDataSet;
class BGSInstanceNamingRules;
class BGSKeyword;
class BGSKeywordForm;
class BGSMaterialSwap;
class BGSMaterialType;
class BGSObjectInstanceExtra;
class BGSRefAlias;
class BGSSoundDescriptorForm;
class BGSSoundKeywordMapping;
class BGSTerminal;
class BGSTextureSet;
class BGSVoiceType;
class BGSZoomData;
class BSAnimationGraphChannel;
class BSAnimationGraphManager;
class BSAnimationGraphVariableCache;
class BSCloneReserver;
class BShkbAnimationGraph;
class BSSoundHandle;
class Condition;
class EnchantmentItem;
class ExtraDataList;
class QueuedFile;
class TESAmmo;
class TESBoundObject;
class TESForm;
class TESLevItem;
class TESObjectARMA;
class TESObjectARMO;
class TESObjectREFR;
class TESObjectWEAP;
class TESRace;

enum class ATTACK_STATE_ENUM;

typedef bool (* _EvaluationConditions)(Condition ** condition, TESObjectREFR * ref1, TESObjectREFR * ref2);
extern RelocAddr <_EvaluationConditions> EvaluationConditions; // Evaluates whole condition LinkedList

// 10
class TBO_InstanceData : public BSIntrusiveRefCounted {
public:
	TBO_InstanceData() { CALL_MEMBER_FN(this, ctor)(); };
	virtual ~TBO_InstanceData();  // 00

	// add
	virtual BGSKeywordForm* GetKeywordData();
	virtual void DeleteKeywordData();
	virtual void CreateKeywordData();
	virtual BGSBlockBashData* GetBlockBashData();
	virtual void DeleteBlockBashData();
	virtual void CreateBlockBashData();
	virtual BSTArray<EnchantmentItem*>* GetEnchantmentArray();
	virtual void DeleteEnchantmentArray();
	virtual void CreateEnchantmentArray();
	virtual BSTArray<BGSMaterialSwap*>* GetMaterialSwapArray();
	virtual void DeleteMaterialSwapArray();
	virtual void CreateMaterialSwapArray();
	virtual float GetWeight();
	virtual SInt32 GetValue();
	virtual UInt32 GetHealth();
	virtual float GetColorRemappingIndex();
	virtual void PostAttach3D(NiAVObject * a_obj3D, TESObjectREFR * a_ref);
	virtual void PostApplyMods(const TESBoundObject*);

	struct DamageTypes
	{
		BGSDamageType	* damageType;	// 00
		UInt32			value;			// 08
	};

	struct ValueModifier
	{
		ActorValueInfo * avInfo;	// 00
		UInt32			unk08;		// 08
	};

	MEMBER_FN_PREFIX(TBO_InstanceData);
	DEFINE_MEMBER_FN(ctor, void, 0x0334BB0);
};
//STATIC_ASSERT(sizeof(TBO_InstanceData) == 0x10);

// 08
class BaseFormComponent
{
public:
	BaseFormComponent();
	virtual ~BaseFormComponent();

	virtual void	Unk_01(void); //GetGameFormComponentType?
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);

//	void	** _vtbl;	// 00
};

// 08
class IAnimationGraphManagerHolder
{
public:
	virtual ~IAnimationGraphManagerHolder();

	// add
	virtual bool NotifyAnimationGraphImpl_vtble(const BSFixedString& a_eventName);
	virtual void EventSuccessfullyProcessed() { return; };
	virtual void ModifyInitialAnimationStateImpl(const bool) { return; };
	virtual bool GetAnimationGraphManagerImpl(BSAnimationGraphManager* a_animGraphMgr) { return false; };
	virtual bool SetAnimationGraphManagerImpl(const BSAnimationGraphManager* a_animGraphMgr) { return false; };
	virtual bool PopulateGraphNodesToTarget(tArray<NiAVObject*> a_nodesToAnimate) { return false; };
	virtual bool ConstructAnimationGraph(BShkbAnimationGraph* a_animGraph) { return false; };
	virtual bool InitializeAnimationGraphVariables(const BShkbAnimationGraph* a_newGraph) { return true; };
	virtual bool SetupAnimEventSinks(const BShkbAnimationGraph* a_newGraph) { return true; };
	virtual void DoFailedToLoadGraph() { return; };
	virtual bool CreateAnimationChannels(tArray<BSAnimationGraphChannel*> a_channels) { return false; };
	virtual void PostCreateAnimationGraphManager(BSAnimationGraphManager* a_animGraphMgr) { return; };
	virtual void PostChangeAnimationManager(const BSAnimationGraphManager* a_newAnimGraphMgr, const BSAnimationGraphManager* a_oldAnimGraphMgr) { return; };
	virtual bool ShouldUpdateAnimation() { return true; };
	virtual UInt32 GetGraphVariableCacheSize() { return 0; };
	virtual bool GetGraphVariableImpl(UInt32 a_graphVarID, float& a_out) { return false; };
	virtual bool GetGraphVariableImpl(UInt32 a_graphVarID, bool& a_out) { return false; };
	virtual bool GetGraphVariableImpl(UInt32 a_graphVarID, SInt32& a_out) { return false; };
	virtual bool GetGraphVariableImpl(const BSFixedString& a_variable, float& a_out);
	virtual bool GetGraphVariableImpl(const BSFixedString& a_variable, SInt32& a_out);
	virtual bool GetGraphVariableImpl(const BSFixedString& a_variable, bool& a_out);
	virtual void PreUpdateAnimationGraphManager(const BSAnimationGraphManager* a_animGraphMgr) { return; };
	virtual void PostUpdateAnimationGraphManager(const BSAnimationGraphManager* a_animGraphMgr) { return; };
	virtual void PreLoadAnimationGraphManager(const BSAnimationGraphManager* a_animGraphMgr) { return; };
	virtual void PostLoadAnimationGraphManager(const BSAnimationGraphManager* a_animGraphMgr) { return; };

	MEMBER_FN_PREFIX(IAnimationGraphManagerHolder);
	DEFINE_MEMBER_FN(GetGraphVariableInt, bool, 0x004DDFE0, const BSFixedString& asVariableName, UInt32 unk2);
	DEFINE_MEMBER_FN(GetGraphVariableFloat, bool, 0x004DDFF0, const BSFixedString& asVariableName, float unk2);
	DEFINE_MEMBER_FN(GetGraphVariableBool, bool, 0x0080A530, const BSFixedString& asVariableName, bool unk2);
	DEFINE_MEMBER_FN(GetGraphVariableNiPoint3, bool, 0x0081D3C0, const BSFixedString& asVariableName, NiPoint3 unk2);
	DEFINE_MEMBER_FN(GetGraphVariableImplBool, bool, 0x0081E1A0, const BSFixedString& asVariableName, bool unk2);
	DEFINE_MEMBER_FN(SetGraphVariableBool, bool, 0x0081D3D0, const BSFixedString& asVariableName, bool newVal);
	DEFINE_MEMBER_FN(SetGraphVariableInt, bool, 0x0081D3F0, const BSFixedString& asVariableName, UInt32 newVal);
	DEFINE_MEMBER_FN(SetGraphVariableFloat, bool, 0x0081D410, const BSFixedString& asVariableName, float newVal);
	DEFINE_MEMBER_FN(SetGraphVariableNiPoint3, bool, 0x0081D430, const BSFixedString& asVariableName, NiPoint3 newVal);
	DEFINE_MEMBER_FN(SetGraphVariableNiQuaternion, bool, 0x0081D440, const BSFixedString& asVariableName, NiQuaternion newVal);
	DEFINE_MEMBER_FN(NotifyAnimationGraphImpl, bool, 0x0081DFC0, const BSFixedString& asEventName);

	bool GetGraphVariableInt(const BSFixedString& asVariableName, UInt32 unk2);
	bool GetGraphVariableFloat(const BSFixedString& asVariableName, float unk2);
	bool GetGraphVariableBool(const BSFixedString& asVariableName, bool unk2);
	bool GetGraphVariableNiPoint3(const BSFixedString& asVariableName, NiPoint3 unk2);
	bool GetGraphVariableImplBool(const BSFixedString& asVariableName);
	bool SetGraphVariableBool(const BSFixedString& asVariableName, bool newVal);
	bool SetGraphVariableInt(const BSFixedString& asVariableName, UInt32 newVal);
	bool SetGraphVariableFloat(const BSFixedString& asVariableName, float newVal);
	bool SetGraphVariableNiPoint3(const BSFixedString& asVariableName, NiPoint3 newVal);
	bool SetGraphVariableNiQuaternion(const BSFixedString& asVariableName, NiQuaternion newVal);
	bool NotifyAnimationGraphImpl(const BSFixedString& asEventName);
};
STATIC_ASSERT(sizeof(IAnimationGraphManagerHolder) == 0x8);

// 08
class IKeywordFormBase
{
public:
	virtual ~IKeywordFormBase();

	virtual	void	Unk_01(void);	//bool	HasKeyword(const BGSKeyword* a_keyword, const TBO_InstanceData* a_data);
	virtual void	Unk_02(void);

//	void	** _vtbl;
};
STATIC_ASSERT(sizeof(IKeywordFormBase) == 0x8);

// 08
class ActorValueOwner
{
public:
	virtual ~ActorValueOwner();

	virtual float	GetValue(ActorValueInfo * actorValueInfo);
	virtual float	GetMaximum(ActorValueInfo * actorValueInfo);
	virtual float	GetBase(ActorValueInfo * actorValueInfo);
	virtual void	SetBase(ActorValueInfo * actorValueInfo, float value);
	virtual void	ModBase(ActorValueInfo * actorValueInfo, float value);
	virtual void	Mod(UInt32 unk1, ActorValueInfo * actorValueInfo, float value); // unk1=0 for regular ModAV
	virtual float	GetMod(UInt32 unk1, ActorValueInfo * actorValueInfo);
	virtual void	Unk_08(ActorValueInfo * actorValueInfo, float value); // Calls Mod with unk1=2
	virtual void	Unk_09(ActorValueInfo * actorValueInfo, float value); // Just calls SetBase
	virtual void	Unk_0A(void);

//	void	** _vtbl;	// 00
};
STATIC_ASSERT(sizeof(ActorValueOwner) == 0x8);

// 10
class TESFullName : public BaseFormComponent
{
public:
	virtual ~TESFullName();

	virtual void	Unk_07(void);
	virtual void	Unk_08(void);

	BSFixedString name;	// 08
};

// 10
class BGSPreviewTransform : public BaseFormComponent
{
public:
	virtual ~BGSPreviewTransform();

	void	* unk08;	// 08
};

// 08
class BGSSoundTagComponent : public BaseFormComponent
{
public:
	virtual ~BGSSoundTagComponent();
};


// 68
class TESActorBaseData : public BaseFormComponent
{
public:
	virtual ~TESActorBaseData();

	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);

	enum
	{
		kFlagFemale = 0x01,
		kFlagEssential = 0x02,
		kFlagIsPreset = 0x04,
		kFlagRespawn = 0x08,
		kFlagAutoCalcStats = 0x10,
		kFlagUnique = 0x20,
		kFlagDoesntAffectStealthMeter = 0x40,
		kFlagPCLevelMult = 0x80,
		kFlagProtected = 0x800
	};

	UInt64			flags;			// 08
	UInt64			unk10;			// 10
	UInt64			unk18;			// 18
	UInt64			unk20;			// 20
	BGSVoiceType	* voiceType;	// 28
	UInt64			unk30[7];		// 30

	MEMBER_FN_PREFIX(TESActorBaseData);
	DEFINE_MEMBER_FN(SetSex, void, 0x00149720, UInt32 unk1, bool isFemale, UInt32 unk2); // unk1 = 1, unk2 = 1
	DEFINE_MEMBER_FN(GetLevel, UInt16, 0x001497F0);
};
STATIC_ASSERT(sizeof(TESActorBaseData) == 0x68);

// 18
class TESContainer : public BaseFormComponent
{
public:
	struct Entry
	{
		struct Data
		{
			UInt32	unk00;
			UInt32	unk04;
			float	unk08;
		};

		UInt32	count;	// 00
		UInt32	pad04;	// 04
		TESForm	* form;	// 08
		Data	* data; // 10 - extra data?
	};

	Entry	** entries;	// 08
	UInt32	numEntries;	// 10
	UInt32	pad14;		// 14
};

// 28
class TESAIForm : public BaseFormComponent
{
public:
	UInt64	unk08[(0x28 - 0x08) / 8];	// 08
};

// 10
class BGSSkinForm : public BaseFormComponent
{
public:
	TESObjectARMO	* skin;	// 08
};

// 10
class TESSpellList : public BaseFormComponent
{
public:
	void	* unk08;	// 08
};

// 30
class TESModel : public BaseFormComponent
{
public:
	virtual const char *	GetModelName(void);
	virtual void			SetModelName(const char * name);
	virtual UInt32			Unk_07(void);

	BSFixedString		name;	// 08 StringCache::Ref

	UInt32				unk0C;	// 0C
	UInt32				unk10;	// 10
	UInt16				unk14;	// 14
	UInt8				unk16;	// 16
	UInt8				unk17;	// 17
	UInt32				unk18;	// 18
	void				* unk20;	// 20
	UInt32				unk28;		// 28

	enum
	{
		kFlag_Dynamic = (1 << 0),
		kFlag_Unknown = (1 << 1)
	};

	UInt8				flags;		// 2C
	UInt8				unk2D;		// 2D
	UInt16				unk2E;		// 2E
};

// 30
class BGSBehaviorGraphModel : public TESModel
{
public:
	virtual ~BGSBehaviorGraphModel();
};

// 30
class BGSTextureModel : public TESModel
{
public:
	virtual ~BGSTextureModel();
};

// 30
class TESModelTri : public TESModel
{
public:
	virtual ~TESModelTri();
};

// 40
class BGSModelMaterialSwap : public TESModel
{
public:
	virtual void			Unk_08(void);
	virtual void			Unk_09(void);

	BGSMaterialSwap	* materialSwap;	// 30
	float	unk38;		// 34
	UInt32	pad3C;		// 38
};
STATIC_ASSERT(sizeof(BGSModelMaterialSwap) == 0x40);


// 10
class TESTexture : public BaseFormComponent
{
public:
	virtual UInt32			Unk_07(void);
	virtual void			Unk_08(void); 	//virtual void			GetNormalMapName(BSString * out);	// might have const char * retn type
	virtual void			Unk_09(void);	//virtual const char *	GetSearchDir(void);	

	BSFixedString	str;	// 08 StringCache::Ref
};

// 10
class TESIcon : public TESTexture
{
public:
	virtual ~TESIcon();
};

// 08
class BGSPreloadable : public BaseFormComponent
{
public:
	virtual void			Unk_07(void);
};

// 18
class BGSMessageIcon : public BaseFormComponent
{
public:
	TESIcon	unk08;	// 08
};
STATIC_ASSERT(sizeof(BGSMessageIcon) == 0x18);

// 18
class BGSBlockBashData : public BaseFormComponent
{
public:
	BGSImpactDataSet	* impactDataSet;	// 08	BGSImpactDataSet*
	BGSMaterialType	* materialType;	// 10	BGSMaterialType *
};

// 20
class BGSKeywordForm : public BaseFormComponent, public IKeywordFormBase {
public:
	BGSKeywordForm() { CALL_MEMBER_FN(this, ctor)(); };

	// override (BaseFormComponent)
	//void InitializeDataComponent() override;			//02
	//void ClearDataComponent() override;               //03
	//void InitComponent() override;		            //04
	//void CopyComponent(BaseFormComponent*) override;	//06

	// override (IKeywordFormBase)
	virtual bool	HasKeyword(const BGSKeyword* keyword, const TBO_InstanceData* a_data = nullptr);	//01
	//void CollectAllKeywords(BSScrapArray<const BGSKeyword*>&, const TBO_InstanceData*);				//02

	//add
	virtual UInt32	GetDefaultKeyword(void);	//07

	BGSKeyword	** keywords;		// 10 BGSKeyword
	UInt32		numKeywords;		// 18
	UInt32		unk14;				// 1C

	MEMBER_FN_PREFIX(BGSKeywordForm);
	DEFINE_MEMBER_FN(ctor, void, 0x0140F00);
	DEFINE_MEMBER_FN(AddKeyword, void, 0x01416E0, BGSKeyword*);
	DEFINE_MEMBER_FN(ClearAllKeywords, void, 0x0141640);
	DEFINE_MEMBER_FN(ContainsKeyword, bool, 0x0142030, BGSKeyword*);

	void AddKeyword(BGSKeyword* keyword) { CALL_MEMBER_FN(this, AddKeyword)(keyword); };
	void ClearAllKeywords() { CALL_MEMBER_FN(this, ClearAllKeywords)(); };
	bool ContainsKeyword(BGSKeyword* keyword) { return CALL_MEMBER_FN(this, ContainsKeyword)(keyword); };
	BGSKeywordForm* GetFormAsKeywordForm(TESForm* form);
	const BGSKeywordForm* GetFormAsKeywordFormConst(TESForm* form);
	BGSKeywordForm* GetInstanceKeywordData(TBO_InstanceData* instanceData);
	bool IsEmpty();
	void Load(void* file); //TESFile
	void ModKeywords(TBO_InstanceData& instanceData, void* mod, TESBoundObject* boundObj, unsigned char unk01);
	void RemoveKeywords(BGSKeyword* keyword);
};
STATIC_ASSERT(sizeof(BGSKeywordForm) == 0x20);

// 18
class BGSPickupPutdownSounds : public BaseFormComponent
{
public:
	BGSSoundDescriptorForm	* pickUp;		// 08 BGSSoundDescriptorForm
	BGSSoundDescriptorForm	* putDown;	// 10 BGSSoundDescriptorForm
};

// 18
class TESEnchantableForm : public BaseFormComponent
{
public:
	virtual UInt16	Unk_07(void);		// return unk10

	EnchantmentItem		* enchantment;	// 08 EnchantmentItem
	UInt16				unk10;			// 10
	UInt16				maxCharge;		// 12
	UInt16				pad14[2];		// 14
};

// 10
class BGSDestructibleObjectForm : public BaseFormComponent
{
public:
	void	* data;	// 08
};

class BGSEquipIndex {
public:
	BGSEquipIndex() { index = 0; }
	BGSEquipIndex(UInt32 newIndex) { index = newIndex; }
	~BGSEquipIndex() {}

	BGSEquipIndex& operator=(const BGSEquipIndex& newIndex) { index = newIndex.index; return *this; }
	operator UInt32() const { return index; }

	// members
	UInt32 index;  // 0
};
STATIC_ASSERT(sizeof(BGSEquipIndex) == 0x4);

// 10
class BGSEquipType : public BaseFormComponent
{
public:
	virtual	BGSEquipSlot *	GetEquipSlot(void);
	virtual void			SetEquipSlot(BGSEquipSlot * type);

	BGSEquipSlot * equipSlot;	// 08
};

// 18
class TESDescription : public BaseFormComponent
{
public:
	void	* unk08;	// 08
	void	* unk10;	// 10

	MEMBER_FN_PREFIX(TESDescription);
	DEFINE_MEMBER_FN(Get, void, 0x0014FAF0, BSString * out, TESForm * parent);
};

// 10
class BGSInstanceNamingRulesForm : public BaseFormComponent
{
public:
	BGSInstanceNamingRules	* rules;	// 08
};

// 10
class BGSTypedKeywordValueArray
{
public:
	void	* unk00;	// 00
	void	* unk08;	// 08
};

// 18
class BGSAttachParentArray : public BaseFormComponent
{
public:
	BGSTypedKeywordValueArray	unk08;
};

// 10
class BGSAttackDataForm : public BaseFormComponent
{
public:
	void	* unk08; // 08
};

// 18
class BGSPerkRankArray : public BaseFormComponent
{
public:
	void	* unk08;	// 08
	UInt32	unk10;		// 10
	UInt32	pad14;		// 14
};


// 10
class BGSPropertySheet : public BaseFormComponent
{
public:

	struct AVIFProperty
	{
		ActorValueInfo * actorValue;	// 00
		float			value;			// 08
		UInt32			pad0C;			// 0C
	};

	tArray<AVIFProperty>	* sheet;	// 08
};

// 10
class TESRaceForm : public BaseFormComponent
{
public:
	TESRace	* race;	// 08
};

// 38
class BGSOverridePackCollection : public BaseFormComponent
{
public:
	UInt64	unk08;	// 08
	UInt64	unk10;	// 08
	UInt64	unk18;	// 08
	UInt64	unk20;	// 08
	UInt64	unk28;	// 08
	UInt64	unk30;	// 08
};

// 10
class BGSForcedLocRefType : public BaseFormComponent
{
public:
	void	* unk08;	// 08
};

// 10
class BGSNativeTerminalForm : public BaseFormComponent
{
public:
	BGSTerminal	* terminal;	// 08
};

// 10
class BGSBipedObjectForm : public BaseFormComponent
{
public:
	// applicable to DefaultRace
	enum
	{
		kPart_Head =		1 << 0,
		kPart_Hair =		1 << 1,
		kPart_Body =		1 << 2,
		kPart_Hands =		1 << 3,
		kPart_Forearms =	1 << 4,
		kPart_Amulet =		1 << 5,
		kPart_Ring =		1 << 6,
		kPart_Feet =		1 << 7,
		kPart_Calves =		1 << 8,
		kPart_Shield =		1 << 9,
		kPart_Unnamed10 =	1 << 10,
		kPart_LongHair =	1 << 11,
		kPart_Circlet =		1 << 12,
		kPart_Ears =		1 << 13,
		kPart_Unnamed14 =	1 << 14,
		kPart_Unnamed15 =	1 << 15,
		kPart_Unnamed16 =	1 << 16,
		kPart_Unnamed17 =	1 << 17,
		kPart_Unnamed18 =	1 << 18,
		kPart_Unnamed19 =	1 << 19,
		kPart_Unnamed20 =	1 << 20,
		kPart_Unnamed21 =	1 << 21,
		kPart_Unnamed22 =	1 << 22,
		kPart_Unnamed23 =	1 << 23,
		kPart_Unnamed24 =	1 << 24,
		kPart_Unnamed25 =	1 << 25,
		kPart_Unnamed26 =	1 << 26,
		kPart_Unnamed27 =	1 << 27,
		kPart_Unnamed28 =	1 << 28,
		kPart_Unnamed29 =	1 << 29,
		kPart_Unnamed30 =	1 << 30,
		kPart_FX01 =		1 << 31,
	};

	enum
	{
		kWeight_Light =	0,
		kWeight_Heavy,
		kWeight_None,
	};

	struct Data
	{
		UInt32	parts;			// 00 - init'd to 0
		UInt32	weightClass;	// 04 - init'd to 2 (none)
	};

	Data	data;	// 08

	UInt32 GetSlotMask() const { return data.parts; }
	void SetSlotMask(UInt32 mask) { data.parts = mask; }

	UInt32 AddSlotToMask(UInt32 slot)
	{
		data.parts |= slot;
		return data.parts;
	}

	UInt32 RemoveSlotFromMask(UInt32 slot)
	{
		data.parts &= ~slot;
		return data.parts;
	}
};

// 08
class BSISoundDescriptor
{
public:
	virtual ~BSISoundDescriptor();

	virtual void	Unk_01(void) = 0;
	virtual void	Unk_02(void) = 0;
	virtual void	Unk_03(void) = 0;
	virtual void	Unk_04(void) = 0;

	//	void	** _vtbl;	// 00
};

// 08
class BGSSoundDescriptor : public BSISoundDescriptor
{
public:
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);

	//	void	** _vtbl;	// 00
};

// 10
class TESWeightForm : public BaseFormComponent
{
public:
	float	weight;	// 08
	UInt32	pad0C;	// 0C
};

// 10
class BGSCraftingUseSound : public BaseFormComponent
{
public:
	UInt64	unk08;	// 08
};

// 10
class BGSMenuDisplayObject : public BaseFormComponent
{
public:
	UInt64	unk08;	// 08
};

// 10
class TESValueForm : public BaseFormComponent
{
public:
	UInt32	value;	// 08
	UInt32	unk0C;	// 0C
};

// 108
class TESBipedModelForm : public BaseFormComponent
{
public:
	UInt64 unk[(0x108-0x8)/8];
};
STATIC_ASSERT(sizeof(TESBipedModelForm) == 0x108);

// 10
class BGSFeaturedItemMessage : public BaseFormComponent
{
public:
	UInt64	unk08;	// 08
};

// 30
class TESLeveledList : public BaseFormComponent
{
public:
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);

	struct Entry
	{
		TESForm * form;		// 00
		void	* unk08;	// 08
		UInt16	count;		// 04
		UInt16	level;		// 06
		UInt32	unk8;		// 08
	};

	enum
	{
		kFlagCalculateFromAllLevelsLTPCLevel =	1 << 0,
		kFlagCalculateForEachItemInCount	 =	1 << 1
	};

	UInt64	unk08;					// 08
	tArray<BGSKeyword*>	* filterKeywords;	// 10
	Entry	* entries;				// 18
	Entry	** scriptAddedEntries;	// 20
	UInt8	scriptAdded;			// 28
	UInt8	length;					// 29
	UInt8	unk2A;					// 2A
	UInt8	flags;					// 2B
	UInt32	unk2C;					// 2C
};
STATIC_ASSERT(sizeof(TESLeveledList) == 0x30);

// 18
class MagicTarget
{
public:
	virtual ~MagicTarget();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);

	void * unk08;	// 08
	void * unk10;	// 10
};

// 08
struct IMovementInterface
{
public:
	virtual ~IMovementInterface();
};

// 08
class IMovementState : public IMovementInterface
{
public:
	virtual void	Unk_01() = 0;
	virtual void	Unk_02() = 0;
	virtual void	Unk_03() = 0;
	virtual void	Unk_04() = 0;
	virtual void	Unk_05() = 0;
	virtual void	Unk_06() = 0;
	virtual void	Unk_07() = 0;
	virtual void	Unk_08() = 0;
	virtual void	Unk_09() = 0;
	virtual void	Unk_0A() = 0;
	virtual void	Unk_0B() = 0;
	virtual void	Unk_0C() = 0;
	virtual void	Unk_0D() = 0;
	virtual void	Unk_0E() = 0;
	virtual void	Unk_0F() = 0;
	virtual void	Unk_10() = 0;
	virtual void	Unk_11() = 0;
	virtual void	Unk_12() = 0;
	virtual void	Unk_13() = 0;
	virtual void	Unk_14() = 0;
	virtual void	Unk_15() = 0;
	virtual void	Unk_16() = 0;
	virtual void	Unk_17() = 0;
	virtual void	Unk_18() = 0;
	virtual void	Unk_19() = 0;
	virtual void	Unk_1A() = 0;
	virtual void	Unk_1B() = 0;
	virtual void	Unk_1C() = 0;
	virtual void	Unk_1D() = 0;
	virtual void	Unk_1E() = 0;
	virtual void	Unk_1F() = 0;
	virtual void	Unk_20() = 0;
};

// 10
class ActorState : public IMovementState
{
public:
	virtual void	Unk_01();
	virtual void	Unk_02();
	virtual void	Unk_03();
	virtual void	Unk_04();
	virtual void	Unk_05();
	virtual void	Unk_06();
	virtual void	Unk_07();
	virtual void	Unk_08();
	virtual void	Unk_09();
	virtual void	Unk_0A();
	virtual void	Unk_0B();
	virtual void	Unk_0C();
	virtual void	Unk_0D();
	virtual void	Unk_0E();
	virtual void	Unk_0F();
	virtual void	Unk_10();
	virtual void	Unk_11();
	virtual void	Unk_12();
	virtual void	Unk_13();
	virtual void	Unk_14();
	virtual void	Unk_15();
	virtual void	Unk_16();
	virtual void	Unk_17();
	virtual void	Unk_18();
	virtual void	Unk_19();
	virtual void	Unk_1A();
	virtual void	Unk_1B();
	virtual void	Unk_1C();
	virtual void	Unk_1D();
	virtual void	Unk_1E();
	virtual void	Unk_1F();
	virtual void	Unk_20();

	enum Flags
	{
		kUnk1 =							0x80000,
		kUnk2 =							0x40000,

		kWeaponStateShift =				1,
		kWeaponStateMask =				0x07,

		kWeaponState_Sheathed =			0x00,
		kWeaponState_WantToDraw =		0x01,
		kWeaponState_Drawing =			0x02,
		kWeaponState_Drawn =			0x03,
		kWeaponState_WantToSheathe =	0x04,
		kWeaponState_Sheathing =		0x05
	};

	UInt32	unk08;	// 08
	UInt32	flags;	// 0C

	UInt32 GetWeaponState() { return (flags >> kWeaponStateShift) & kWeaponStateMask; }
	bool IsWeaponDrawn()	{ return GetWeaponState() >= kWeaponState_Drawn; }
};
STATIC_ASSERT(sizeof(ActorState) == 0x10);

// 38
class Condition
{
public:
	enum CompareFlags {
		kCompareFlag_And = 0x00,
		kCompareFlag_Or = 0x01,
		kCompareFlag_Equal = 0x00,
		kCompareFlag_UseAliases = 0x02,
		kCompareFlag_Global = 0x04,
		kCompareFlag_UsePackData = 0x08,
		kCompareFlag_SwapTarget = 0x10,
	};

	enum CompareOperators {
		kCompareOp_Equal = 0,
		kCompareOp_NotEqual,
		kCompareOp_Greater,
		kCompareOp_GreaterEqual,
		kCompareOp_Less,
		kCompareOp_LessEqual
	};

	enum Functions {
		kFunction_GetWantBlocking = 0,
		kFunction_GetDistance,
		kFunction_GetLocked = 5,
		kFunction_GetPos,
		kFunction_GetAngle = 8,
		kFunction_GetStartingPos = 10,
		kFunction_GetStartingAngle,
		kFunction_GetSecondsPassed,
		kFunction_GetValue = 14,
		kFunction_GetCurrentTime = 18,
		kFunction_GetScale = 24,
		kFunction_IsMoving,
		kFunction_IsTurning,
		kFunction_GetLineOfSight,
		kFunction_GetInSameCell = 32,
		kFunction_GetDisabled = 35,
		kFunction_MenuMode,
		kFunction_GetDisease = 39,
		kFunction_GetClothingValue = 41,
		kFunction_SameFaction,
		kFunction_SameRace,
		kFunction_SameSex,
		kFunction_GetDetected,
		kFunction_GetDead,
		kFunction_GetItemCount,
		kFunction_GetGold,
		kFunction_GetSleeping,
		kFunction_GetTalkedToPC,
		kFunction_GetQuestRunning = 56,
		kFunction_GetStage = 58,
		kFunction_GetStageDone,
		kFunction_GetFactionRankDifference,
		kFunction_GetAlarmed,
		kFunction_IsRaining,
		kFunction_GetAttacked,
		kFunction_GetIsCreature,
		kFunction_GetLockLevel,
		kFunction_GetShouldAttack,
		kFunction_GetInCell,
		kFunction_GetIsClass,
		kFunction_GetIsRace,
		kFunction_GetIsSex,
		kFunction_GetInFaction,
		kFunction_GetIsID,
		kFunction_GetFactionRank,
		kFunction_GetGlobalValue,
		kFunction_IsSnowing,
		kFunction_GetRandomPercent = 77,
		kFunction_WouldBeStealing = 79,
		kFunction_GetLevel,
		kFunction_IsRotating,
		kFunction_GetDeadCount = 84,
		kFunction_GetIsAlerted = 91,
		kFunction_GetPlayerControlsDisabled = 98,
		kFunction_GetHeadingAngle,
		kFunction_IsWeaponMagicOut = 101,
		kFunction_IsTorchOut,
		kFunction_IsShieldOut,
		kFunction_IsFacingUp = 106,
		kFunction_GetKnockedState,
		kFunction_GetWeaponAnimType,
		kFunction_IsWeaponSkillType,
		kFunction_GetCurrentAIPackage,
		kFunction_IsWaiting,
		kFunction_IsIdlePlaying,
		kFunction_IsIntimidatedbyPlayer = 116,
		kFunction_IsPlayerInRegion,
		kFunction_GetActorAggroRadiusViolated,
		kFunction_GetCrime = 122,
		kFunction_IsGreetingPlayer,
		kFunction_IsGuard = 125,
		kFunction_HasBeenEaten = 127,
		kFunction_GetStaminaPercentage,
		kFunction_HasBeenRead,
		kFunction_GetDying,
		kFunction_GetSceneActionPercent,
		kFunction_WouldRefuseCommand,
		kFunction_SameFactionAsPC,
		kFunction_SameRaceAsPC,
		kFunction_SameSexAsPC,
		kFunction_GetIsReference,
		kFunction_IsTalking = 141,
		kFunction_GetComponentCount,
		kFunction_GetCurrentAIProcedure,
		kFunction_GetTrespassWarningLevel,
		kFunction_IsTrespassing,
		kFunction_IsInMyOwnedCell,
		kFunction_GetWindSpeed,
		kFunction_GetCurrentWeatherPercent,
		kFunction_GetIsCurrentWeather,
		kFunction_IsContinuingPackagePCNear,
		kFunction_GetIsCrimeFaction = 152,
		kFunction_CanHaveFlames,
		kFunction_HasFlames,
		kFunction_GetOpenState = 157,
		kFunction_GetSitting = 159,
		kFunction_GetIsCurrentPackage = 161,
		kFunction_IsCurrentFurnitureRef,
		kFunction_IsCurrentFurnitureObj,
		kFunction_GetDayOfWeek = 170,
		kFunction_GetTalkedToPCParam = 172,
		kFunction_IsPCSleeping = 175,
		kFunction_IsPCAMurderer,
		kFunction_HasSameEditorLocationAsRef = 180,
		kFunction_HasSameEditorLocationAsRefAlias,
		kFunction_GetEquipped,
		kFunction_IsSwimming = 185,
		kFunction_GetAmountSoldStolen = 190,
		kFunction_GetIgnoreCrime = 192,
		kFunction_GetPCExpelled,
		kFunction_GetPCFactionMurder = 195,
		kFunction_GetPCEnemyofFaction = 197,
		kFunction_GetPCFactionAttack = 199,
		kFunction_GetDestroyed = 203,
		kFunction_HasMagicEffect = 214,
		kFunction_GetDefaultOpen,
		kFunction_IsSpellTarget = 223,
		kFunction_GetVATSMode,
		kFunction_GetPersuasionNumber,
		kFunction_GetVampireFeed,
		kFunction_GetCannibal,
		kFunction_GetIsClassDefault,
		kFunction_GetClassDefaultMatch,
		kFunction_GetInCellParam,
		kFunction_GetPlayerDialogueInput,
		kFunction_GetVatsTargetHeight = 235,
		kFunction_GetIsGhost = 237,
		kFunction_GetUnconscious = 242,
		kFunction_GetRestrained = 244,
		kFunction_GetIsUsedItem = 246,
		kFunction_GetIsUsedItemType,
		kFunction_IsScenePlaying,
		kFunction_IsInDialogueWithPlayer,
		kFunction_GetLocationCleared,
		kFunction_GetIsPlayableRace = 254,
		kFunction_GetOffersServicesNow,
		kFunction_HasAssociationType = 258,
		kFunction_HasFamilyRelationship,
		kFunction_HasParentRelationship = 261,
		kFunction_IsWarningAbout,
		kFunction_IsWeaponOut,
		kFunction_HasSpell,
		kFunction_IsTimePassing,
		kFunction_IsPleasant,
		kFunction_IsCloudy,
		kFunction_IsSmallBump = 274,
		kFunction_GetBaseValue = 277,
		kFunction_IsOwner,
		kFunction_IsCellOwner = 280,
		kFunction_IsHorseStolen = 282,
		kFunction_IsLeftUp = 285,
		kFunction_IsSneaking,
		kFunction_IsRunning,
		kFunction_GetFriendHit,
		kFunction_IsInCombat,
		kFunction_IsInInterior = 300,
		kFunction_IsWaterObject = 304,
		kFunction_GetPlayerAction,
		kFunction_IsActorUsingATorch,
		kFunction_IsXBox = 309,
		kFunction_GetInWorldspace,
		kFunction_GetPCMiscStat = 312,
		kFunction_GetPairedAnimation,
		kFunction_IsActorAVictim,
		kFunction_GetTotalPersuasionNumber,
		kFunction_GetIdleDoneOnce = 318,
		kFunction_GetNoRumors = 320,
		kFunction_GetCombatState = 323,
		kFunction_GetWithinPackageLocation = 325,
		kFunction_IsRidingMount = 327,
		kFunction_IsFleeing = 329,
		kFunction_IsInDangerousWater = 332,
		kFunction_GetIgnoreFriendlyHits = 338,
		kFunction_IsPlayersLastRiddenMount,
		kFunction_IsActor = 353,
		kFunction_IsEssential,
		kFunction_IsPlayerMovingIntoNewSpace = 358,
		kFunction_GetInCurrentLocation,
		kFunction_GetInCurrentLocationAlias,
		kFunction_GetTimeDead,
		kFunction_HasLinkedRef,
		kFunction_IsChild = 365,
		kFunction_GetStolenItemValueNoCrime,
		kFunction_GetLastPlayerAction,
		kFunction_IsPlayerActionActive,
		kFunction_IsTalkingActivatorActor = 370,
		kFunction_IsInList = 372,
		kFunction_GetStolenItemValue,
		kFunction_GetCrimeGoldViolent = 375,
		kFunction_GetCrimeGoldNonviolent,
		kFunction_IsOwnedBy = 378,
		kFunction_GetCommandDistance = 380,
		kFunction_GetCommandLocationDistance,
		kFunction_GetHitLocation = 390,
		kFunction_IsPC1stPerson,
		kFunction_GetCauseofDeath = 396,
		kFunction_IsLimbGone,
		kFunction_IsWeaponInList,
		kFunction_IsBribedbyPlayer = 402,
		kFunction_GetRelationshipRank,
		kFunction_GetVATSValue = 407,
		kFunction_IsKiller,
		kFunction_IsKillerObject,
		kFunction_GetFactionCombatReaction,
		kFunction_Exists = 414,
		kFunction_GetGroupMemberCount,
		kFunction_GetGroupTargetCount,
		kFunction_GetIsVoiceType = 426,
		kFunction_GetPlantedExplosive,
		kFunction_IsScenePackageRunning = 429,
		kFunction_GetHealthPercentage,
		kFunction_GetIsObjectType = 432,
		kFunction_PlayerVisualDetection = 434,
		kFunction_PlayerAudioDetection,
		kFunction_GetIsCreatureType = 437,
		kFunction_HasKey,
		kFunction_IsFurnitureEntryType,
		kFunction_GetInCurrentLocationFormList = 444,
		kFunction_GetInZone,
		kFunction_GetVelocity,
		kFunction_GetGraphVariableFloat,
		kFunction_HasPerk,
		kFunction_GetFactionRelation,
		kFunction_IsLastIdlePlayed,
		kFunction_GetPlayerTeammate = 453,
		kFunction_GetPlayerTeammateCount,
		kFunction_GetActorCrimePlayerEnemy = 458,
		kFunction_GetCrimeGold,
		kFunction_IsPlayerGrabbedRef = 463,
		kFunction_GetKeywordItemCount = 465,
		kFunction_GetDestructionStage = 470,
		kFunction_GetIsAlignment = 473,
		kFunction_IsProtected = 476,
		kFunction_GetThreatRatio,
		kFunction_GetIsUsedItemEquipType = 479,
		kFunction_GetPlayerActivated = 483,
		kFunction_GetFullyEnabledActorsInHigh = 485,
		kFunction_IsCarryable = 487,
		kFunction_GetConcussed,
		kFunction_GetMapMarkerVisible = 491,
		kFunction_PlayerKnows = 493,
		kFunction_GetPermanentValue,
		kFunction_GetKillingBlowLimb,
		kFunction_CanPayCrimeGold = 497,
		kFunction_GetDaysInJail = 499,
		kFunction_EPAlchemyGetMakingPoison,
		kFunction_EPAlchemyEffectHasKeyword,
		kFunction_GetAllowWorldInteractions = 503,
		kFunction_DialogueGetAv = 506,
		kFunction_DialogueHasPerk,
		kFunction_GetLastHitCritical,
		kFunction_DialogueGetItemCount = 510,
		kFunction_LastCrippledCondition,
		kFunction_HasSharedPowerGrid,
		kFunction_IsCombatTarget,
		kFunction_GetVATSRightAreaFree = 515,
		kFunction_GetVATSLeftAreaFree,
		kFunction_GetVATSBackAreaFree,
		kFunction_GetVATSFrontAreaFree,
		kFunction_GetIsLockBroken,
		kFunction_IsPS3,
		kFunction_IsWindowsPC,
		kFunction_GetVATSRightTargetVisible,
		kFunction_GetVATSLeftTargetVisible,
		kFunction_GetVATSBackTargetVisible,
		kFunction_GetVATSFrontTargetVisible,
		kFunction_IsInCriticalStage = 528,
		kFunction_GetXPForNextLevel = 530,
		kFunction_GetInfamy = 533,
		kFunction_GetInfamyViolent,
		kFunction_GetInfamyNonViolent,
		kFunction_GetTypeCommandPerforming,
		kFunction_GetQuestCompleted = 543,
		kFunction_GetSpeechChallengeSuccessLevel,
		kFunction_IsGoreDisabled = 547,
		kFunction_IsSceneActionComplete = 550,
		kFunction_GetSpellUsageNum = 552,
		kFunction_GetActorsInHigh = 554,
		kFunction_HasLoaded3D,
		kFunction_HasKeyword = 560,
		kFunction_HasRefType,
		kFunction_LocationHasKeyword,
		kFunction_LocationHasRefType,
		kFunction_GetIsEditorLocation = 565,
		kFunction_GetIsAliasRef,
		kFunction_GetIsEditorLocationAlias,
		kFunction_IsSprinting,
		kFunction_IsBlocking,
		kFunction_HasEquippedSpell,
		kFunction_GetCurrentCastingType,
		kFunction_GetCurrentDeliveryType,
		kFunction_GetAttackState = 574,
		kFunction_GetEventData = 576,
		kFunction_IsCloserToAThanB,
		kFunction_LevelMinusPCLevel,
		kFunction_IsBleedingOut = 580,
		kFunction_GetRelativeAngle = 584,
		kFunction_GetMovementDirection = 589,
		kFunction_IsInScene,
		kFunction_GetRefTypeDeadCount,
		kFunction_GetRefTypeAliveCount,
		kFunction_GetIsFlying = 594,
		kFunction_IsCurrentSpell,
		kFunction_SpellHasKeyword,
		kFunction_GetEquippedItemType,
		kFunction_GetLocationAliasCleared,
		kFunction_GetLocationAliasRefTypeDeadCount = 600,
		kFunction_GetLocationAliasRefTypeAliveCount,
		kFunction_IsWardState,
		kFunction_IsInSameCurrentLocationAsRef,
		kFunction_IsInSameCurrentLocationAsRefAlias,
		kFunction_LocationAliasIsLocation,
		kFunction_GetKeywordDataForLocation,
		kFunction_GetKeywordDataForAlias = 608,
		kFunction_LocationAliasHasKeyword = 610,
		kFunction_IsNullPackageData,
		kFunction_GetNumericPackageData,
		kFunction_IsPlayerRadioOn,
		kFunction_GetPlayerRadioFrequency,
		kFunction_GetHighestRelationshipRank,
		kFunction_GetLowestRelationshipRank,
		kFunction_HasAssociationTypeAny,
		kFunction_HasFamilyRelationshipAny,
		kFunction_GetPathingTargetOffset,
		kFunction_GetPathingTargetAngleOffset,
		kFunction_GetPathingTargetSpeed,
		kFunction_GetPathingTargetSpeedAngle,
		kFunction_GetMovementSpeed,
		kFunction_GetInContainer,
		kFunction_IsLocationLoaded,
		kFunction_IsLocationAliasLoaded,
		kFunction_IsDualCasting,
		kFunction_GetVMQuestVariable = 629,
		kFunction_GetCombatAudioDetection,
		kFunction_GetCombatVisualDetection,
		kFunction_IsCasting,
		kFunction_GetFlyingState,
		kFunction_IsInFavorState = 635,
		kFunction_HasTwoHandedWeaponEquipped,
		kFunction_IsFurnitureExitType,
		kFunction_IsInFriendStatewithPlayer,
		kFunction_GetWithinDistance,
		kFunction_GetValuePercent,
		kFunction_IsUnique,
		kFunction_GetLastBumpDirection,
		kFunction_GetInfoChallangeSuccess = 644,
		kFunction_GetIsInjured,
		kFunction_GetIsCrashLandRequest,
		kFunction_GetIsHastyLandRequest,
		kFunction_IsLinkedTo = 650,
		kFunction_GetKeywordDataForCurrentLocation,
		kFunction_GetInSharedCrimeFaction,
		kFunction_GetBribeSuccess = 654,
		kFunction_GetIntimidateSuccess,
		kFunction_GetArrestedState,
		kFunction_GetArrestingActor,
		kFunction_HasVMScript = 659,
		kFunction_GetVMScriptVariable,
		kFunction_GetWorkshopResourceDamage,
		kFunction_HasValidRumorTopic = 664,
		kFunction_IsAttacking = 672,
		kFunction_IsPowerAttacking,
		kFunction_IsLastHostileActor,
		kFunction_GetGraphVariableInt,
		kFunction_ShouldAttackKill = 678,
		kFunction_GetActivationHeight = 680,
		kFunction_WornHasKeyword = 682,
		kFunction_GetPathingCurrentSpeed,
		kFunction_GetPathingCurrentSpeedAngle,
		kFunction_GetWorkshopObjectCount = 691,
		kFunction_EPMagic_SpellHasKeyword = 693,
		kFunction_GetNoBleedoutRecovery,
		kFunction_EPMagic_SpellHasSkill = 696,
		kFunction_IsAttackType,
		kFunction_IsAllowedToFly,
		kFunction_HasMagicEffectKeyword,
		kFunction_IsCommandedActor,
		kFunction_IsStaggered,
		kFunction_IsRecoiling,
		kFunction_HasScopeWeaponEquipped,
		kFunction_IsPathing,
		kFunction_GetShouldHelp,
		kFunction_HasBoundWeaponEquipped,
		kFunction_GetCombatTargetHasKeyword,
		kFunction_GetCombatGroupMemberCount = 709,
		kFunction_IsIgnoringCombat,
		kFunction_GetLightLevel,
		kFunction_SpellHasCastingPerk = 713,
		kFunction_IsBeingRidden,
		kFunction_IsUndead,
		kFunction_GetRealHoursPassed,
		kFunction_IsUnlockedDoor = 718,
		kFunction_IsHostileToActor,
		kFunction_GetTargetHeight,
		kFunction_IsPoison,
		kFunction_WornApparelHasKeywordCount,
		kFunction_GetItemHealthPercent,
		kFunction_EffectWasDualCast,
		kFunction_GetKnockStateEnum,
		kFunction_DoesNotExist,
		kFunction_GetPlayerWalkAwayFromDialogueScene = 728,
		kFunction_GetActorStance,
		kFunction_CanProduceForWorkshop = 734,
		kFunction_CanFlyHere,
		kFunction_EPIsDamageType,
		kFunction_GetActorGunState = 738,
		kFunction_GetVoiceLineLength,
		kFunction_ObjectTemplateItem_HasKeyword = 741,
		kFunction_ObjectTemplateItem_HasUniqueKeyword,
		kFunction_ObjectTemplateItem_GetLevel,
		kFunction_MovementIdleMatches,
		kFunction_GetActionData,
		kFunction_GetActionDataShort,
		kFunction_GetActionDataByte,
		kFunction_GetActionDataFlag,
		kFunction_ModdedItemHasKeyword,
		kFunction_GetAngryWithPlayer,
		kFunction_IsCameraUnderWater,
		kFunction_IsActorRefOwner = 753,
		kFunction_HasActorRefOwner,
		kFunction_GetLoadedAmmoCount = 756,
		kFunction_IsTimeSpanSunrise,
		kFunction_IsTimeSpanMorning,
		kFunction_IsTimeSpanAfternoon,
		kFunction_IsTimeSpanEvening,
		kFunction_IsTimeSpanSunset,
		kFunction_IsTimeSpanNight,
		kFunction_IsTimeSpanMidnight,
		kFunction_IsTimeSpanAnyDay,
		kFunction_IsTimeSpanAnyNight,
		kFunction_CurrentFurnitureHasKeyword,
		kFunction_GetWeaponEquipIndex,
		kFunction_IsOverEncumbered = 769,
		kFunction_IsPackageRequestingBlockedIdles,
		kFunction_GetActionDataInt,
		kFunction_GetVATSRightMinusLeftAreaFree,
		kFunction_GetInIronSights,
		kFunction_GetActorStaggerDirection,
		kFunction_GetActorStaggerMagnitude,
		kFunction_WornCoversBipedSlot,
		kFunction_GetInventoryValue,
		kFunction_IsPlayerInConversation,
		kFunction_IsInDialogueCamera,
		kFunction_IsMyDialogueTargetPlayer,
		kFunction_IsMyDialogueTargetActor,
		kFunction_GetMyDialogueTargetDistance,
		kFunction_IsSeatOccupied,
		kFunction_IsPlayerRiding,
		kFunction_IsTryingEventCamera,
		kFunction_UseLeftSideCamera,
		kFunction_GetNoteType,
		kFunction_LocationHasPlayerOwnedWorkshop,
		kFunction_IsStartingAction,
		kFunction_IsMidAction,
		kFunction_IsWeaponChargeAttack,
		kFunction_IsInWorkshopMode,
		kFunction_IsWeaponChargingHoldAttack,
		kFunction_IsEncounterAbovePlayerLevel,
		kFunction_IsMeleeAttacking,
		kFunction_GetVATSQueuedTargetsUnique,
		kFunction_GetCurrentLocationCleared,
		kFunction_IsPowered,
		kFunction_GetTransmitterDistance,
		kFunction_GetCameraPlaybackTime,
		kFunction_IsInWater,
		kFunction_GetWithinActivateDistance,
		kFunction_IsUnderWater,
		kFunction_IsInSameSpace,
		kFunction_LocationAllowsReset,
		kFunction_GetVATSBackRightAreaFree,
		kFunction_GetVATSBackLeftAreaFree,
		kFunction_GetVATSBackRightTargetVisible,
		kFunction_GetVATSBackLeftTargetVisible,
		kFunction_GetVATSTargetLimbVisible,
		kFunction_IsPlayerListening,
		kFunction_GetPathingRequestedQuickTurn,
		kFunction_EPIsCalculatingBaseDamage,
		kFunction_GetReanimating,
		kFunction_IsInRobotWorkbench = 817
	};

	enum ReferenceTypes {
		kReferenceType_Subject = 0,
		kReferenceType_Target,
		kReferenceType_Reference,
		kReferenceType_CombatTarget,
		kReferenceType_LinkedRef,
		kReferenceType_Alias,
		kReferenceType_PackageData,
		kReferenceType_EventData
	};

	union Param
	{
		float	f32;
		UInt32	u32;
		SInt32	s32;
		TESForm	* form;
	};

	Condition	* next;					// 00
	float		compareValue;			// 08
	UInt32		unk0C;					// 0C
	UInt32		refHandle;				// 10
	UInt32		unk14;					// 14 - FFFFFFFF
	UInt16		functionId;				// 18
	UInt8		unk1A;					// 1A
	UInt8		unk1B;					// 1B
	UInt32		unk1C;					// 1C
	Param		param1;					// 20
	Param		param2;					// 28

	struct CompareType
	{
		unsigned char flags : 5;
		unsigned char op : 3;
	};

	CompareType		comparisonType;			// 30
	UInt8			referenceType;			// 31
	UInt8			unk32[6];				// 32

	// 78
	class Evaluator
	{
	public:
		Evaluator(TESForm * a1, TESForm * a2)
		{
			CALL_MEMBER_FN(this, ctor)(a1, a2, 0);
		}

		TESForm * a1;	// 00
		TESForm * a2;	// 08
		UInt64	unk10[(0x78 - 0x08) >> 3];

		MEMBER_FN_PREFIX(Evaluator);
		DEFINE_MEMBER_FN(ctor, void, 0x0072A770, TESForm * a1, TESForm * a2, UInt64 unk1); // a1 might be player or subject, not sure yet
	};

	MEMBER_FN_PREFIX(Condition);
	// DB2ACB0447C58B663FE4E9C862B96256D0C2716D+15
	DEFINE_MEMBER_FN(Evaluate, bool, 0x0072C530, Evaluator * eval); // Evaluates only a single condition
};
STATIC_ASSERT(offsetof(Condition, referenceType) == 0x31);
STATIC_ASSERT(sizeof(Condition) == 0x38);

// ??
struct IMovementPlayerControlsFilter : public IMovementInterface
{
public:
	virtual void	Unk_01();
	virtual void	Unk_02();
	virtual void	Unk_03();
	virtual void	Unk_04();
	virtual void	Unk_05();
	virtual void	Unk_06();
	virtual void	Unk_07();
	virtual void	Unk_08();
	virtual void	Unk_09();
};

// ??
class ActorEquipData
{
public:
	UInt64	unk00;					// 00
	NiNode	* flattenedBoneTree;	// 08

	enum
	{
		kMaxSlots = 44
	};

	// 58
	struct SlotData
	{
		TESForm							* item;			// 00
		TBO_InstanceData				* instanceData;	// 08
		BGSObjectInstanceExtra			* extraData;	// 10
		TESForm							* model;		// 18 - ARMA for ARMO and WEAP for WEAP
		BGSModelMaterialSwap			* modelMatSwap;	// 20
		BGSTextureSet					* textureSet;	// 28
		NiAVObject						* node;			// 30
		void							* unk38;		// 38
		IAnimationGraphManagerHolder	* unk40;		// 40
		UInt64							unk48;			// 48
		UInt32							unk50;			// 50
		UInt32							unk54;			// 54
	};

	SlotData	slots[kMaxSlots];
};

class BGSObjectInstance {
public:
	BGSObjectInstance() { BGSObjectInstance(nullptr, nullptr); }
	BGSObjectInstance(TESForm* a_object, TBO_InstanceData* a_instanceData) { ctor(a_object, a_instanceData); }
	BGSObjectInstance(BGSObjectInstance& a_copy) { ctorCopy(a_copy); }

	// members
	TESForm* object;                 // 00
	TBO_InstanceData* instanceData;  // 08

	MEMBER_FN_PREFIX(BGSObjectInstance);
	DEFINE_MEMBER_FN(ctor, BGSObjectInstance*, 0x02F7B50, TESForm*, TBO_InstanceData*);
	DEFINE_MEMBER_FN(ctorCopy, BGSObjectInstance*, 0x02F7BF0, BGSObjectInstance&);

	bool IsValid() { return object != nullptr; };

private:
	BGSObjectInstance* ctor(TESForm* a_object, TBO_InstanceData* a_instanceData) {
		return CALL_MEMBER_FN(this, ctor)(a_object, a_instanceData);
	}

	BGSObjectInstance* ctorCopy(BGSObjectInstance& a_copy) {
		return CALL_MEMBER_FN(this, ctorCopy)(a_copy);
	}
};
STATIC_ASSERT(sizeof(BGSObjectInstance) == 0x10);

template <class T>
class BGSObjectInstanceT : public BGSObjectInstance {
public:
	BGSObjectInstanceT() : BGSObjectInstance() {}
	BGSObjectInstanceT(T* a_object, TBO_InstanceData* a_instanceData) : BGSObjectInstance(a_object, a_instanceData) {}
};

// 08
class EquippedItemData : public NiRefObject {
public:
	virtual ~EquippedItemData();
};
//STATIC_ASSERT(sizeof(EquippedItemData) == 0x10);

// 38
class EquippedWeaponData : public EquippedItemData {
public:
	virtual ~EquippedWeaponData();

	TESAmmo* ammo;																				 // 10
	UInt32 ammoCount;																			 // 18
	void* aimModel;																				 // 20
	void* muzzleFlash;																			 // 28
	NiAVObject* fireNode;																		 // 30
	ATTACK_STATE_ENUM attackState;                                                               // 38
	BSTArray<BSTTuple<UInt32, AnimationStanceFireLocationData<NiPoint3>>> fireLocations;		 // 40
	NiPointer<QueuedFile> weaponPreload;                                                         // 58
	NiPointer<QueuedFile> projectilePreload;                                                     // 60
	NiPointer<BSCloneReserver> reserveProjectileClones;                                          // 68

	UInt64 unk070[(0x98 - 0x70) / 8];															 // 70 - 90
	/*
	BSSoundHandle idleSound;                                                                     // 70
	BSSoundHandle attackSound;                                                                   // 78
	BSSoundHandle reverbSound;                                                                   // 80
	BSSoundHandle prevAttack;                                                                    // 88
	BSSoundHandle prevReverb;                                                                    // 90
	*/
	const BGSSoundKeywordMapping* attackSoundData;                                               // 98
	bool reverbSoundIsTail;                                                                      // A0
	
};
STATIC_ASSERT(sizeof(EquippedWeaponData) == 0xA8);

class EquippedItem {
public:
	EquippedItem() { ctor(); }
	EquippedItem(EquippedItem& a_copy) { ctorCopy(a_copy); }
	EquippedItem(BGSObjectInstance& a_instanceData, BGSEquipSlot* a_slot, BGSEquipIndex a_index, EquippedItemData* a_data) { ctorAdv(a_instanceData, a_slot, a_index, a_data); }

	// members
	BGSObjectInstance item;            // 00
	const BGSEquipSlot* equipSlot;     // 10
	BGSEquipIndex equipIndex;          // 18
	NiPointer<EquippedItemData> data;  // 20

	MEMBER_FN_PREFIX(EquippedItem);
	DEFINE_MEMBER_FN(ctor, EquippedItem*, 0x07133C0);
	DEFINE_MEMBER_FN(ctorCopy, EquippedItem*, 0x0010920, EquippedItem&);
	DEFINE_MEMBER_FN(ctorAdv, EquippedItem*, 0x0E335A0, BGSObjectInstance&, BGSEquipSlot*, BGSEquipIndex, EquippedItemData*);

	bool IsValid() { return item.IsValid(); }
private:
	EquippedItem* ctor() {
		return CALL_MEMBER_FN(this, ctor)();
	}
	EquippedItem* ctorCopy(EquippedItem& a_copy) { 
		return CALL_MEMBER_FN(this, ctorCopy)(a_copy);
	}
	EquippedItem* ctorAdv(BGSObjectInstance& a_instanceData, BGSEquipSlot* a_slot, BGSEquipIndex a_index, EquippedItemData* a_data) {
		return CALL_MEMBER_FN(this, ctorAdv)(a_instanceData, a_slot, a_index, a_data);
	}
};
STATIC_ASSERT(sizeof(EquippedItem) == 0x28);

class EquippedWeapon {
public:
	EquippedWeapon() { ctor(); }
	EquippedWeapon(EquippedWeapon& a_copy) { ctorCopy(a_copy); }

	//members
	BGSObjectInstanceT<TESObjectWEAP> weapon;	// 00
	const BGSEquipSlot* equipSlot;				// 10
	BGSEquipIndex equipIndex;					// 18
	NiPointer<EquippedWeaponData> weaponData;	// 20

	MEMBER_FN_PREFIX(EquippedWeapon);
	DEFINE_MEMBER_FN(ctor, EquippedWeapon*, 0x07133F0);
	DEFINE_MEMBER_FN(ctorCopy, EquippedWeapon*, 0x0010970, EquippedWeapon&);

	bool IsValid() { return weapon.IsValid(); }
private:
	EquippedWeapon* ctor() {
		return CALL_MEMBER_FN(this, ctor)();
	}
	EquippedWeapon* ctorCopy(EquippedWeapon& a_equippedWeapon) {
		return CALL_MEMBER_FN(this, ctorCopy)(a_equippedWeapon);
	}
};
STATIC_ASSERT(sizeof(EquippedWeapon) == 0x28);

// 10
struct BGSInventoryItem
{
	TESForm * form;	// 00

	// 28
	class Stack : public BSIntrusiveRefCounted
	{
	public:
		virtual ~Stack();

		Stack			* next;			// 10
		ExtraDataList	* extraData;	// 18
		SInt32			count;			// 20

		enum
		{
			kFlagEquipped = 7
		};

		UInt16	flags;		// 24

#ifdef _DEBUG
		void Dump();
#endif
		template<typename T>
		bool Visit(T & f)
		{
			if(f(this) && next)
				return next->Visit(f);
			return true; // Continue
		}
	};

#ifdef _DEBUG
	void Dump();
#endif

	Stack * stack;	// 08
};

// ??
class BGSInventoryList
{
public:
	UInt64	unk00;	// 00
	tArray<BSTEventSink<BGSInventoryListEvent::Event>> eventSinks;	// 08
	UInt64	unk20[(0x58-0x20)/8];		// 20
	tArray<BGSInventoryItem> items;		// 58
	float			inventoryWeight;	// 70 - is (-1) when not calculated
	UInt32			unk74;				// 74
	BSReadWriteLock	inventoryLock;		// 78
};

class IAliasFunctor
{
public:
	virtual ~IAliasFunctor() { }

	virtual UInt32 Visit(BGSRefAlias * alias) = 0;
};

// 08
class BGSPerkEntry
{
public:
	virtual ~BGSPerkEntry();

	void	* unk08;	// 08
};
