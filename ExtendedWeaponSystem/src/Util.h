#pragma once
#include "Global.h"

enum AmmoType {
	kAmmoType_Default = 0x0,
	kAmmoType_Charging = 0x1,
	kAmmoType_FusionCore = 0x2,
	kAmmoType_NeverEnding = 0x4
};

enum EquipIndex {
	kInvalid = -1,
	kDefault = 0,
	kThrowable = 2
};

struct IsReloadableDataWrapper {
	void* arg1;
	void* arg2;
};

bool IsPlayerInFirstPerson();
bool IsPlayerInThirdPerson();
bool IsPlayerSprinting();
bool IsPlayerWeaponDrawn();
bool IsPlayerWeaponReloadable();
bool IsPlayerWeaponReloading();
bool IsPlayerWeaponThrowable();
bool IsWeaponReloadable(IsReloadableDataWrapper* data, const EquippedItem* item);
bool IsWeaponThrowable(uint32_t equipIndex);

EquippedItem& GetPlayerEquippedItemDefault();
EquippedWeapon& GetPlayerEquippedWeaponDefault();
const uint32_t GetPlayerInventoryObjectCount(const TESBoundObject* item);

const NiAVObject* GetByNameFromPlayer3D(const BSFixedString& name);
const NiAVObject* GetByNameFromPlayer3D(const char* name);

/*;========================================================================================================================================================;*/

TESForm* GetFormFromIdentifier(const string& identifier);
bool GetForms();

char* _MESSAGE(const char* fmt, ...);
void Dump(void* mem, unsigned int size);

template <typename K, typename V>
void print_map(unordered_map<K, V> const& map) {
	auto print_key_value = [](const auto& key, const auto& value) {
		if (!value) {
			logger::warn(FMT_STRING("Hook: {:s} IsHooked: {:s}"), key, value);
		} else {
			logger::info(FMT_STRING("Hook: {:s} IsHooked: {:s}"), key, value);
		}
	};
	for (const std::pair<K, V>& n : map) {
		print_key_value(n.first, n.second);
	}
	
	//std::for_each(map.begin(), map.end(), [](std::pair<K, V> p) {
	//	logger::info(FMT_STRING("Hook: {:s} IsHooked: {%t}"), p.first, p.second);
	//});
}

//Functions to write a simple line of text to logs
void logInfo(string text);
void logInfo(string text);
void logWarn(string text);
void logError(string text);
void logCritical(string text);
