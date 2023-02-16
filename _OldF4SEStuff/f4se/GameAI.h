#pragma once
#include "f4se/GameReferences.h"
#include "f4se/GameAnimation.h"
#include "f4se/GameEvents.h"
#include "f4se/GameHandle.h"
#include "f4se/GameForms.h"
#include "f4se/GameFormComponents.h"
#include "f4se/GameTypes.h"

class IProcedureTreeExecState;
class IAnimationStanceData;
class BSFaceGenNiNode;
class BSLightingShaderProperty;
class MuzzleFlash;
class PackageLocation;
class PerkEntryVisitor;
class QueuedFile;
class QueuedItem;
class EffectItem;
class EquippedItem;
class EquippedItemData;
class HitData;
class ActiveEffect;
class DeferredHideLimb;
class BSClothExtraData;
class TESIdleForm;
class BSFaceGenAnimationData;
class MagicItem;
class TESObjectWEAP;

struct ObjectstoAcquire;

enum class PTYPE : UInt32 {
	kExplore = 0,
	kFollow = 1,
	kEscore = 2,
	kEat = 3,
	kSleep = 4,
	kWander = 5,
	kTravel = 6,
	kAccompany = 7,
	kUseItemAt = 8,
	kAmbush = 9,
	kFleeNonCombat = 10,
	kCastMagic = 11,
	kSandbox = 12,
	kPatrol = 13,
	kGuard = 14,
	kDialogue = 15,
	kUseWeapon = 16,
	kFind = 17,
	kCustom = 18,
	kTemplate = 19,
	kActivate = 20,
	kAlarm = 21,
	kFlee = 22,
	kTrespass = 23,
	kSpectator = 24,
	kGreet = 25,
	kGetUp = 26,
	kDoNothing = 27,
	kInGameDialogue = 28,
	kSurface = 29,
	kSearchForAttacker = 30,
	kAvoidReference = 31,
	kBumpReaction = 32,
	kGrenadeMineReaction = 33,
	kStealWarning = 34,
	kPickpocketWarning = 35,
	kMovementBlocked = 36,
	kVampireFeed = 37,
	kCannibal = 38,
	kLand = 39,
	kUnused = 40,
	kMountActor = 41,
	kDismountActor = 42,
	kClearMountPosition = 43,
	kClearPowerArmorExit = 44,
};

class ActiveEffectList {
public:
	// members
	BSTArray<ActiveEffect*> data;  // 00
	SInt8 iterating;               // 18
};
STATIC_ASSERT(sizeof(ActiveEffectList) == 0x20);

class ActorPackageData {
public:

	virtual ~ActorPackageData();

	// add
	virtual PTYPE GetPackageType();
	virtual IProcedureTreeExecState* GetProcedureExecState();
	virtual void SetProcedureExecState();
	virtual void ClearProcedureExecState();
	virtual void SaveGame();
	virtual void LoadGame();
	virtual void InitLoadGame();
	virtual void ResetPackData();
};
STATIC_ASSERT(sizeof(ActorPackageData) == 0x8);

class ActorPackage {
public:
	// members
	BSSpinLock packageLock;               // 00
	void* package;						  // 08
	ActorPackageData* data;               // 10
	BSPointerHandle<TESObjectREFR> target;// 18
	SInt32 currentProcedureIndex;		  // 1C
	float packageStartTime;               // 20
	UInt32 modifiedPackageFlag;			  // 24
	UInt16 modifiedInterruptFlag;		  // 28
	SInt8 actorPackageFlags;			  // 2A
	SInt8 preferredSpeed;				  // 2B
};
STATIC_ASSERT(sizeof(ActorPackage) == 0x30);

class CachedValueData {
public:
	// members
	float value;  // 0
	bool dirty;   // 4
};
STATIC_ASSERT(sizeof(CachedValueData) == 0x8);

class CachedValues {
public:
	// members
	float cachedRadius;                                  // 00
	float cachedWidth;                                   // 04
	float cachedLength;                                  // 08
	float cachedForwardLength;                           // 0C
	float cachedDPS;                                     // 10
	float cachedEyeLevel;                                // 14
	float cachedWalkSpeed;                               // 18
	float cachedRunSpeed;                                // 1C
	float cachedJogSpeed;                                // 20
	float cachedFastWalkSpeed;                           // 24
	UInt32 booleanValues;								 // 28
	UInt32 flags;										 // 2C
	BSTArray<CachedValueData> actorValueCache;           // 30
	BSTArray<CachedValueData> permanentActorValueCache;  // 48
};
STATIC_ASSERT(sizeof(CachedValues) == 0x60);

struct MiddleLowProcessData {
public:
	// members
	SInt32 hourPackageEvaluated;  // 0
};
STATIC_ASSERT(sizeof(MiddleLowProcessData) == 0x4);

struct MiddleHighProcessData {
public:
	// members
	BSTEventSource<ActorInventoryEvent> inventoryEventSource;
	NiPointer<bhkNPCollisionObject> poseBound;
	ActorPackage runOncePackage;
	BSTArray<BSPointerHandle<Actor>> deadDetectList;
	tList<TESObjectREFR*> refListChairBed;
	NiPoint3 rotation;
	NiPoint3 rotationSpeed;
	NiPoint3 actorMountPosition;
	NiPoint3 furniturePathPoint;
	NiPoint3 lastSeenPosition;
	BSPointerHandle<Actor> bleedoutAttacker;
	SInt32 wardState;
	void* animResponse;
	BSTArray<void*> commandedActors;
	NiNode* damageRootNode[26];
	NiNode* weaponBone;
	NiAVObject* headNode;
	NiAVObject* torsoNode;
	NiAVObject* faceTargetSourceNode;
	BSFaceGenNiNode* faceNodeSkinned;
	NiPointer<BSLightingShaderProperty> lightingProperty;
	QueuedItem* listItemstoEquipUnequip;
	HitData* lastHitData;
	DeferredHideLimb* headDeferredHideLimb;
	ActiveEffectList activeEffects;
	BSAnimationGraphManager* animationGraphManager;
	BSAnimationGraphVariableCache* animationVariableCache;
	BSTArray<SubGraphIdleRootData> subGraphIdleManagerRoots;
	BSSpinLock equippedItemsLock;
	BSTArray<EquippedItem> equippedItems;																	  // 288
	BSTArray<BSClothExtraData*> clothExtraDataCache;
	UInt64 subGraphHandles[(0x2D0 - 0x2B8) / 8];
	UInt64 currentDefaultSubGraphID[(0x2F0 - 0x2D0) / 8];
	UInt64 requestedDefaultSuBGraphID[(0x310 - 0x2F0) / 8];
	UInt64 currentWeaponSubGraphID[(0x330 - 0x310) / 8];
	UInt64 requestedWeaponSubGraphID[(0x350 - 0x330) / 8];
	IAnimationStanceData* stanceData;
	BSTArray<BSTTuple<UInt32, AnimationStanceNodeLocationData<NiPoint3>>> nodeLocationArray;
	float stanceHeightArray[6][2];
	float headHeightOffset;
	BSPointerHandle<TESObjectREFR> currentFurniture;														  // 3A4
	BSPointerHandle<TESObjectREFR> occupiedFurniture;														  // 3A8
	TESIdleForm* currentIdle;
	BSPointerHandle<Actor> commandingActor;
	const TESIdleForm* furnitureIdle;
	BSFaceGenAnimationData* faceAnimationData;
	MagicItem* currentPackageSpell;
	TESObjectWEAP* lastBoundWeapon;
	void* charController;
	void* penetrationDetectUtil;
	void* bodyPartPreload;																					  // 3F0
	TESIdleForm* lastIdlePlayed;																			  // 3F8
	void* perkData;																							  // 400
	NiPoint3 lookAtLocation;																				  // 408
	float pursueTimer;                                                                                        // 414
	float furnitureAngle;                                                                                     // 418
	float furnitureEntryFootstepDeltaTarget;                                                                  // 41C
	float packageIdleTimer;                                                                                   // 420
	float equippedWeight;                                                                                     // 424
	float desiredSpeed;                                                                                       // 428
	float animationSpeed;                                                                                     // 42C
	float bleedoutTimer;                                                                                      // 430
	float bleedoutRate;                                                                                       // 434
	float bleedoutMaxHealth;                                                                                  // 438
	float maxWardPower;                                                                                       // 43C
	float animGraphEventTimeout;                                                                              // 440
	float torchEvalTimer;                                                                                     // 444
	float alphaMult;                                                                                          // 448
	float scriptRefractPower;                                                                                 // 44C
	float sleepingTimer;                                                                                      // 450
	float deferredKillTimer;                                                                                  // 454
	float killMoveTimer;                                                                                      // 458
	float staggerTimer;                                                                                       // 45C
	float mountDismountSafetyTimer;                                                                           // 460
	float rangeWaypointIdleTimer;																			  // 464
	UInt32 packageIdleNumber;																				  // 468
	UInt32 reservationSlot;																					  // 46C
	SubgraphIdentifier currentFurnitureSubgraphID;                                                            // 470
	UInt32 currentFurnitureMarkerID;																		  // 478
	UInt32 occupiedFurnitureMarkerID;																		  // 47C
	UInt64 nextExtraArrow3DUpdate;																			  // 480
	UInt32 deferredKill;																					  // 488
	UInt32 flareFlags;																						  // 48C
	UInt32 useItem;																							  // 490
	UInt16 animActionSuccess;																				  // 494
	UInt16 update3DModel;																					  // 496
	UInt8 weaponCullCounter;																				  // 498
	UInt8 archetypeChangeType;																				  // 499
	bool animWeaponCull;                                                                                      // 49A
	bool aimingTarget;                                                                                        // 49B
	bool doneClothesChange;                                                                                   // 49C
	bool pickPackIdle;                                                                                        // 49D
	bool doneOnce;                                                                                            // 49E
	bool refreshFlareFlags;                                                                                   // 49F
	bool pickPocketed;                                                                                        // 4A0
	bool summonedCreature;                                                                                    // 4A1
	bool forceNextUpdate;                                                                                     // 4A2
	bool playedBeginIdles;                                                                                    // 4A3
	bool playedEndIdles;                                                                                      // 4A4
	bool quickPlacement;                                                                                      // 4A5
	bool beenAttacked;                                                                                        // 4A6
	bool alwaysHit;                                                                                           // 4A7
	bool doNoDamage;                                                                                          // 4A8
	bool soulTrapped;                                                                                         // 4A9
	bool lookAt;                                                                                              // 4AA
	bool eating;                                                                                              // 4AB
	bool calcLight;                                                                                           // 4AC
	bool preventCombat;                                                                                       // 4AD
	bool dyingFromBleedout;                                                                                   // 4AE
	bool fleeing;                                                                                             // 4AF
	bool instantGetOut;                                                                                       // 4B0
	bool hostileGuard;                                                                                        // 4B1
	bool stopIdleFailed;                                                                                      // 4B2
	bool killQueued;                                                                                          // 4B3
	bool ragdollInstant;                                                                                      // 4B4
	bool scriptDeferredKill;                                                                                  // 4B5
	bool furnitureEntryLeftFootFirst;                                                                         // 4B6
	bool furnitureAnimationPlayed;                                                                            // 4B7
	bool queuedInstantInteractionAnimation;                                                                   // 4B8
	bool queuedModifyInitialAnimationPose;                                                                    // 4B9
	bool avoidPlayer;                                                                                         // 4BA
	bool usingPathingFaceTargetWhileTrackingOutOfRange;                                                       // 4BB

};
STATIC_ASSERT(sizeof(MiddleHighProcessData) == 0x4C0);

struct HighProcessData {
public:

};

class AITimer {
public:
	float startTime;
	float targetTime;
};
STATIC_ASSERT(sizeof(AITimer) == 0x8);

class AIProcess {
public:

	// members
	MiddleLowProcessData* middleLow;						// 00
	MiddleHighProcessData* middleHigh;						// 08
	HighProcessData* high;									// 10
	ActorPackage currentPackage;							// 18
	float hourLastProcessed;								// 48
	float timeAdjustmentsMade;								// 4C
	UInt32 dateLastProcessed;								// 50
	CachedValues* cachedValues;								// 58
	UInt32 numberItemsActivate;								// 60
	tList<ObjectstoAcquire*> objectList;					// 68
	tList<TESObjectREFR*> genericLocationsList;				// 78
	ObjectstoAcquire* acquireObject;						// 88
	ObjectstoAcquire* savedAcquireObject;					// 90
	float essentialDownTimer;								// 98
	float deathTime;										// 9C
	float trackedDamage;									// A0
	TESBoundObject* itemBeingUsed;							// A8
	AITimer combatDelayTimer;								// B0
	BSPointerHandle<TESObjectREFR> followTarget;            // B8
	BSPointerHandle<TESObjectREFR> target;                  // BC
	BSPointerHandle<TESObjectREFR> genericLocation;         // C0
	BSPointerHandle<TESObjectREFR> genericSecondLocation;   // C4
	BGSListForm* targetFormList;							// C8
	UInt32 currentSpeakingTopicID;							// D0
	BSPointerHandle<TESObjectREFR> patrolLocation;			// D4
	BSPointerHandle<TESObjectREFR> idleTarget;				// D8
	UInt16 formListNumb;									// DC
	char lowProcessFlags;									// DE
	char processLevel;										// DF
	bool skippedTimeStampForPathing;						// E0
	bool ignoringCombat;									// E1
	bool endAlarmOnActor;									// E2
	bool escortingPlayer;									// E3
	bool updateEditorDeadModel;								// E4
	bool editorDeadActive;									// E5
	bool initializingPosition;								// E6

	bool GetEquippedItem(BGSEquipIndex a_index, EquippedItem& a_item) { return CALL_MEMBER_FN(this, GetEquippedItemByIndex)(a_index, a_item); }
	BGSObjectInstance GetEquippedItem(const BGSEquipSlot* a_slot) { return CALL_MEMBER_FN(this, GetEquippedItemBySlot)(a_slot); }
	BSTArray<EquippedItem>* GetEquippedItemArray() { return CALL_MEMBER_FN(this, GetEquippedItemArray)(); }
	bool GetEquippedWeapon(BGSEquipIndex a_index, EquippedWeapon& a_weapon) { return CALL_MEMBER_FN(this, GetEquippedWeaponByIndex)(a_index, a_weapon); }
	bool GetEquippedWeaponData(BGSEquipIndex a_index, NiPointer<EquippedWeaponData>& a_data) { return CALL_MEMBER_FN(this, GetEquippedWeaponData)(a_index, a_data); }
	UInt32 GetEquippedWeapons(BSTArray<EquippedWeapon>& a_weapons) { return CALL_MEMBER_FN(this, GetEquippedWeapons)(a_weapons); }
	void GetItemsInSlot(BGSEquipSlot* a_slot, BSTArray<EquippedItem>& a_items) { return CALL_MEMBER_FN(this, GetItemsInSlot)(a_slot, a_items); }
	void Update(Actor* a_actor) { return CALL_MEMBER_FN(this, Update)(a_actor); }
	bool RequestLoadAnimationsForWeaponCharge(Actor& a_actor) { return CALL_MEMBER_FN(this, RequestLoadAnimationsForWeaponCharge)(a_actor); }

private:
	MEMBER_FN_PREFIX(AIProcess);
	DEFINE_MEMBER_FN(GetEquippedItemByIndex, bool, 0x0E2C100, BGSEquipIndex, EquippedItem&);
	DEFINE_MEMBER_FN(GetEquippedItemBySlot, BGSObjectInstance, 0x0E2BF70, const BGSEquipSlot*);
	DEFINE_MEMBER_FN(GetEquippedItemArray, BSTArray<EquippedItem>*, 0x0E7AD00);
	DEFINE_MEMBER_FN(GetEquippedWeaponByIndex, bool, 0x0713BF0, BGSEquipIndex, EquippedWeapon&);
	DEFINE_MEMBER_FN(GetEquippedWeaponData, bool, 0x0E8D8B0, BGSEquipIndex, NiPointer<EquippedWeaponData>&);
	DEFINE_MEMBER_FN(GetEquippedWeapons, UInt32, 0x0DEB080, BSTArray<EquippedWeapon>&);
	DEFINE_MEMBER_FN(GetItemsInSlot, void, 0x0E2C220, BGSEquipSlot*, BSTArray<EquippedItem>&);
	DEFINE_MEMBER_FN(Update, void, 0x0E28200, Actor*);
	DEFINE_MEMBER_FN(RequestLoadAnimationsForWeaponCharge, bool, 0x0E38DC0, Actor&)
};
STATIC_ASSERT(sizeof(AIProcess) == 0xE8);