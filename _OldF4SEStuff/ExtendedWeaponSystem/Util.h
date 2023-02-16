#pragma once
#include "Global.h"

template <typename T>
T GetVirtualFunction(void* baseObject, int vtblIndex) {
	uintptr_t* vtbl = reinterpret_cast<uintptr_t**>(baseObject)[0];
	return reinterpret_cast<T>(vtbl[vtblIndex]);
}

template <typename T>
T GetOffset(const void* baseObject, int offset) {
	return *reinterpret_cast<T*>((uintptr_t)baseObject + offset);
}

BSTEventDispatcher<void*>* GetGlobalEventDispatcher(BSTGlobalEvent* globalEvents, const char* dispatcherName);

enum AmmoType {
	kAmmoType_Default = 0x00,
	kAmmoType_Charging = 0x01,
	kAmmoType_FusionCore = 0x02,
	kAmmoType_NeverEnding = 0x04
};

enum EquipIndex {
	kEquipIndex_Invalid = -1,
	kEquipIndex_Default = 0,
	kEquipIndex_Throwable = 2
};

struct IsReloadableData {
	UInt64 unk00;
	Actor* actor;
};

struct IsReloadableDataWrapper {
	void* arg1;
	void* arg2;
};

bool IsReloading();
bool IsSprinting();
bool IsFirstPerson();
bool IsThirdPerson();
bool IsWeaponDrawn();
bool IsWeaponReloadable();
bool IsButtonPressed(ButtonEvent* btnEvent);
bool IsHoldingButton(ButtonEvent* btnEvent);

bool WornHasKeywordActor(Actor* akTarget, BGSKeyword* akKeyword);
bool HasKeyword(TESForm* form, BGSKeyword* keyword);
bool HasKeywordInstWEAP(TESObjectWEAP::InstanceData* thisInstance, BGSKeyword* kwdToCheck);
TESForm* GetFormFromIdentifier(const std::string& identifier);
bool GetForms();
BSFixedString GetDisplayName(ExtraDataList* extraDataList, TESForm* kbaseForm);
std::string GetFullNameWEAP(TESObjectWEAP* weap);


const BSTArray<EquippedItem>* GetPlayerEquippedItemArray();
EquippedItem* GetPlayerEquippedItemByFormID(UInt32 formId);
EquippedItem* GetPlayerEquippedItemByEquipIndex(EquipIndex equipIndex);
EquippedWeapon* GetPlayerEquippedWeaponByEquipIndex(EquipIndex equipIndex);
EquippedWeaponData* GetPlayerEquippedWeaponDataByEquipIndex(EquipIndex equipIndex);
TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(TESForm* weapForm, TBO_InstanceData* weapInst);
TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(EquippedItem& a_item);
TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(EquippedWeapon& a_weapon);
UInt32 GetInventoryItemCount(Actor* actor, TESForm* item);


NiAVObject* GetByNameHelper(const BSFixedString& name);





const std::string currentDateTime();
const std::string prefixLog();
void logIfNeeded(std::string text);
void log(std::string text);

