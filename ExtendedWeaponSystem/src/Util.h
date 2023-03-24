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

template <class T>
T SafeWrite64Function(uintptr_t addr, T data) {
	DWORD oldProtect;
	void* _d[2];
	memcpy(_d, &data, sizeof(data));
	size_t len = sizeof(_d[0]);

	VirtualProtect((void*)addr, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	T olddata;
	memset(&olddata, 0, sizeof(T));
	memcpy(&olddata, (void*)addr, len);
	memcpy((void*)addr, &_d[0], len);
	VirtualProtect((void*)addr, len, oldProtect, &oldProtect);
	return olddata;
}

BSTEventSource<void*>* GetGlobalEventSource(BSTGlobalEvent_OLD* globalEvents, const char* globalName);
const char* GetObjectClassNameImpl(const char* result, void* objBase);
const char* GetObjectClassName(void* objBase);

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

struct IsReloadableDataWrapper {
	void* arg1;
	void* arg2;
};

bool IsPlayerActive();

bool IsButtonPressed(ButtonEvent* btnEvent);
bool IsHoldingButton(ButtonEvent* btnEvent);
bool IsPlayerInFirstPerson();
bool IsPlayerInThirdPerson();
bool IsPlayerSprinting();
bool IsPlayerWeaponDrawn();
bool IsPlayerWeaponReloadable();
bool IsPlayerWeaponReloading();
bool IsPlayerWeaponThrowable();
bool IsWeaponReloadable(IsReloadableDataWrapper* data, const EquippedItem* item);
bool IsWeaponThrowable(uint32_t equipIndex);

bool WornHasKeywordActor(Actor* akTarget, BGSKeyword* akKeyword);
bool HasKeyword(TESForm* form, BGSKeyword* keyword);
bool HasKeywordInstWEAP(TESObjectWEAP::InstanceData* thisInstance, BGSKeyword* kwdToCheck);
TESForm* GetFormFromIdentifier(const string& identifier);
bool GetForms();
string GetFullNameWEAP(TESObjectWEAP* weap);

const BSTArray<EquippedItem>* GetPlayerEquippedItemArray();
const EquippedItem* GetPlayerEquippedItemByFormID(uint32_t formId);
const EquippedItem* GetPlayerEquippedItemByEquipIndex(EquipIndex equipIndex);
const EquippedWeapon* GetPlayerEquippedWeaponByEquipIndex(EquipIndex equipIndex);
const EquippedWeaponData* GetPlayerEquippedWeaponDataByEquipIndex(EquipIndex equipIndex);
const TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(TESForm* weapForm, TBO_InstanceData* weapInst);
const TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(EquippedItem& a_item);
const TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(EquippedWeapon& a_weapon);
const uint32_t GetInventoryItemCount(Actor* actor, TESForm* item);

const NiAVObject* GetByNameFromPlayer3D(const BSFixedString& name);

template <typename K, typename V>
void print_map(unordered_map<K, V> const& map) {
	auto print_key_value = [](const auto& key, const auto& value) {
		logger::info(FMT_STRING("Hook: {:s} IsHooked: {:s}"), key, value);
	};
	for (const std::pair<K, V>& n : map) {
		print_key_value(n.first, n.second);
	}
	
	//std::for_each(map.begin(), map.end(), [](std::pair<K, V> p) {
	//	logger::info(FMT_STRING("Hook: {:s} IsHooked: {%t}"), p.first, p.second);
	//});
}

//Functions to write a simple line of text to logs
void logInfoConditional(string text);
void logInfo(string text);
void logWarn(string text);
void logError(string text);
void logCritical(string text);
