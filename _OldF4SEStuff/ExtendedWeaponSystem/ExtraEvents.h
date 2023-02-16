#pragma once
#include "Global.h"

struct BSAnimationGraphEvent {
public:
	TESObjectREFR* refr;
	BSFixedString	name;
	BSFixedString	args;
};

struct TESEquipEvent {
public:
	TESObjectREFR* owner;							// 00
	UInt32							FormID;			// 08	base FormID
	UInt32							unkC;			// 0C	Refr FormID?
	UInt16							unk10;			// 10	ID?
	bool							unk12;			// 12
	bool							isEquipping;	// 15
	UInt8							padding1[111];	// 16
	//16-87 UNK
	BGSInventoryItem::Stack* invItem;				// 88
	UInt8							padding2[15];	// 90
	//90-9F UNK
	TESObject* item;								// A0
	TESObjectWEAP::InstanceData* instanceData;		// A8
};
STATIC_ASSERT(offsetof(TESEquipEvent, instanceData) == 0xA8);
STATIC_ASSERT(offsetof(TESEquipEvent, invItem) == 0x88);
DECLARE_EVENT_DISPATCHER(TESEquipEvent, 0x00442870);

struct PlayerAmmoCountEvent {
public:
	UInt32							ammoCount;			// 00
	UInt32							totalAmmoCount;		// 04
	UInt64							unk08;				// 08
	TESObjectWEAP* weapon;								// 10
	TESObjectWEAP::InstanceData* weaponInstance;		//
														//...
};
STATIC_ASSERT(offsetof(PlayerAmmoCountEvent, weapon) == 0x10);

struct PlayerWeaponReloadEvent {
public:

};

enum class WEAPON_STATE : UInt32 {
	kSheathed,
	kWantToDraw,
	kDrawing,
	kDrawn,
	kWantToSheathe,
	kSheathing
};

struct PlayerSetWeaponStateEvent {
public:
	WEAPON_STATE state;
	bool unk04;
};

struct BGSOnPlayerUseWorkBenchEvent {
public:

};
DECLARE_EVENT_DISPATCHER(BGSOnPlayerUseWorkBenchEvent, 0x00441970);