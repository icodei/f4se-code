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

BSTEventSource<void*>* GetGlobalEventSource(BSTGlobalEvent* globalEvents, const char* globalName);
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

struct IsReloadableData {
	std::uint64_t unk00;
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
bool IsThrowableWeapon(std::uint32_t equipIndex);
bool IsButtonPressed(ButtonEvent* btnEvent);
bool IsHoldingButton(ButtonEvent* btnEvent);

bool WornHasKeywordActor(Actor* akTarget, BGSKeyword* akKeyword);
bool HasKeyword(TESForm* form, BGSKeyword* keyword);
bool HasKeywordInstWEAP(TESObjectWEAP::InstanceData* thisInstance, BGSKeyword* kwdToCheck);
TESForm* GetFormFromIdentifier(const std::string& identifier);
bool GetForms();
std::string GetFullNameWEAP(TESObjectWEAP* weap);

const BSTArray<EquippedItem>* GetPlayerEquippedItemArray();
const EquippedItem* GetPlayerEquippedItemByFormID(std::uint32_t formId);
const EquippedItem* GetPlayerEquippedItemByEquipIndex(EquipIndex equipIndex);
const EquippedWeapon* GetPlayerEquippedWeaponByEquipIndex(EquipIndex equipIndex);
const EquippedWeaponData* GetPlayerEquippedWeaponDataByEquipIndex(EquipIndex equipIndex);
const TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(TESForm* weapForm, TBO_InstanceData* weapInst);
const TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(EquippedItem& a_item);
const TESObjectWEAP::InstanceData* GetPlayerWeaponInstanceData(EquippedWeapon& a_weapon);
const std::uint32_t GetInventoryItemCount(Actor* actor, TESForm* item);

const NiAVObject* GetByNameHelper(const BSFixedString& name);

char tempbuf[8192] = { 0 };
char* _MESSAGE(const char* fmt, ...) {
	va_list args;

	va_start(args, fmt);
	vsnprintf(tempbuf, sizeof(tempbuf), fmt, args);
	va_end(args);
	spdlog::log(spdlog::level::warn, tempbuf);

	return tempbuf;
}

const std::string currentDateTime();
const std::string prefixLog();
void logIfNeeded(std::string text);
void log(std::string text);
