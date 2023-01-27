#include "Global.h"

void FillWeaponInfo() {
	EquippedItem* equipData = GetPlayerEquippedItemByEquipIndex(EquipIndex::kEquipIndex_Default);
	if (!equipData) {
		return;
	}
	TESObjectWEAP* weap = DYNAMIC_CAST(equipData->item.object, TESForm, TESObjectWEAP);;
	TESObjectWEAP::InstanceData* equippedWeaponInstance = GetPlayerWeaponInstanceData(equipData->item.object, equipData->item.instanceData);
	ammoCapacity = equippedWeaponInstance->ammoCapacity;
	currentAmmoCount = ((EquippedWeaponData*)(equipData->data).get())->ammoCount;
	totalAmmoCount = GetInventoryItemCount(*g_player, equippedWeaponInstance->ammo);
	logIfNeeded(";====================== Game Loaded. Getting Initial Weapon Stats =====================;");
	logIfNeeded("Weapon: " + GetFullNameWEAP(weap));
	logIfNeeded("TotalAmmoCount: " + std::to_string(totalAmmoCount));
	logIfNeeded("CurrentAmmoCount: " + std::to_string(currentAmmoCount));
	logIfNeeded("AmmoCapacity: " + std::to_string(ammoCapacity));
	if (WornHasKeywordActor(*g_player, reloadSequentialKeyword)) {
		processCurrentWeap = true;
		logIfNeeded(GetFullNameWEAP(weap) + " has the reloadSequentialKeyword.");
	} else {
		processCurrentWeap = false;
		logIfNeeded(GetFullNameWEAP(weap) + " does not have the reloadSequentialKeyword.");
	}
	if (WornHasKeywordActor(*g_player, ThermalScopeKeyword)) {
		processCurrentScope = true;
		logIfNeeded(GetFullNameWEAP(weap) + " has the ThermalScopeKeyword.");
	} else {
		processCurrentScope = false;
		ScopeTextureLoader = nullptr;
		logIfNeeded(GetFullNameWEAP(weap) + " does not have the ThermalScopeKeyword.");
	}
	logIfNeeded(";======================================================================================;");
}

//Equip Handler
void HanldeWeaponEquip(TESObjectWEAP::InstanceData* weap) {
	if (!weap) {
		return;
	}
	if (currentWeapInstance != weap) {
		currentWeapInstance = weap;
	}
	if (!currentWeapInstance) {
		return;
	}

	if (HasKeywordInstWEAP(weap, reloadSequentialKeyword) || WornHasKeywordActor(*g_player, reloadSequentialKeyword)) {
		processCurrentWeap = true;
		ammoCapacity = currentWeapInstance->ammoCapacity;
		logIfNeeded("reloadSequentialKeyword found. We should process this weapon for sequential reloads.");
		logIfNeeded("weapon instance equipped with ammo capacity of:" + std::to_string(currentWeapInstance->ammoCapacity));
	} else {
		logIfNeeded("No reloadSequentialKeyword found. We can ignore this weapon for sequential reloads.");
		processCurrentWeap = false;
	}
	if (HasKeywordInstWEAP(weap, ThermalScopeKeyword) || WornHasKeywordActor(*g_player, ThermalScopeKeyword)) {
		processCurrentScope = true;
		logIfNeeded("ThermalScopeKeyword found. We should process this weapon for special scope utility.");
	} else {
		processCurrentScope = false;
		logIfNeeded("No ThermalScopeKeyword found. We can ignore this weapon for special scope utility.");
	}
	logIfNeeded(";======================================================================================;");
}

//Called from anim event of weapon equip. This should happen after the 3d is loaded hopefully
void HanldeWeaponEquipAfter3D() {
	if (processCurrentScope == false || ignore == true) {
		return;
	}

}
