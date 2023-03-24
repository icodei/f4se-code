#include "WeaponHandlers.h"

void FillWeaponInfo() {	//TODO: Rename this function to something better
	const EquippedWeapon* equipData = GetPlayerEquippedWeaponByEquipIndex(EquipIndex::kEquipIndex_Default);
	if (!equipData) {
		return;
	}
	TESObjectWEAP* weap = (equipData->weapon.object)->As<TESObjectWEAP>();
	TESAmmo* weapAmmo;
	TESObjectWEAP::InstanceData* equippedWeaponInstance = (TESObjectWEAP::InstanceData*)equipData->weapon.instanceData.get();
	if (equipData->weapon.object) {
		if (equippedWeaponInstance) {
			weapAmmo = equippedWeaponInstance->ammo;
		} else {
			weapAmmo = equipData->weapon.object->As<TESObjectWEAP>()->weaponData.ammo;
		}
		totalAmmoCount = GetInventoryItemCount(pc, weapAmmo);
	} else {
		weapAmmo = nullptr;
	}
	uint32_t ammoCap;
	if (equipData->weapon.object && ((equippedWeaponInstance = (TESObjectWEAP::InstanceData*)equipData->weapon.instanceData.get()) == nullptr ? (ammoCap = weap->weaponData.ammoCapacity) : (ammoCap = equippedWeaponInstance->ammoCapacity), ammoCap)) {
		if (equippedWeaponInstance) {
			ammoCapacity = equippedWeaponInstance->ammoCapacity;
		} else {
			ammoCapacity = weap->weaponData.ammoCapacity;
		}
	} else {
		ammoCapacity = -(weapAmmo != nullptr);
	}
	
	currentAmmoCount = equipData->weaponData->ammoCount;	//TODO: Add this to above part and move the above to a new function
	
	logInfoConditional(";====================== Game Loaded. Getting Initial Weapon Stats =====================;");
	logInfoConditional("Weapon: " + GetFullNameWEAP(weap));
	logInfoConditional("TotalAmmoCount: " + std::to_string(totalAmmoCount));
	logInfoConditional("CurrentAmmoCount: " + std::to_string(currentAmmoCount));
	logInfoConditional("AmmoCapacity: " + std::to_string(ammoCapacity));
	if (WornHasKeywordActor(pc, reloadSequentialKeyword)) {
		processCurrentWeap = true;
		logInfoConditional(GetFullNameWEAP(weap) + " has the reloadSequentialKeyword.");
	} else {
		processCurrentWeap = false;
		logInfoConditional(GetFullNameWEAP(weap) + " does not have the reloadSequentialKeyword.");
	}
	if (WornHasKeywordActor(pc, ThermalScopeKeyword)) {
		processCurrentScope = true;
		logInfoConditional(GetFullNameWEAP(weap) + " has the ThermalScopeKeyword.");
	} else {
		processCurrentScope = false;
		logInfoConditional(GetFullNameWEAP(weap) + " does not have the ThermalScopeKeyword.");
	}
	logInfoConditional(";======================================================================================;");
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

	if (HasKeywordInstWEAP(weap, reloadSequentialKeyword) || WornHasKeywordActor(pc, reloadSequentialKeyword)) {
		processCurrentWeap = true;
		ammoCapacity = currentWeapInstance->ammoCapacity;
		logInfoConditional("reloadSequentialKeyword found. We should process this weapon for sequential reloads.");
		logInfoConditional("weapon instance equipped with ammo capacity of:" + std::to_string(currentWeapInstance->ammoCapacity));
	} else {
		logInfoConditional("No reloadSequentialKeyword found. We can ignore this weapon for sequential reloads.");
		processCurrentWeap = false;
	}
	if (HasKeywordInstWEAP(weap, ThermalScopeKeyword) || WornHasKeywordActor(pc, ThermalScopeKeyword)) {
		processCurrentScope = true;
		nsScope::CreateRenderer();
		logInfoConditional("ThermalScopeKeyword found. We should process this weapon for special scope utility.");
	} else {
		processCurrentScope = false;
		logInfoConditional("No ThermalScopeKeyword found. We can ignore this weapon for special scope utility.");
	}
	logInfoConditional(";======================================================================================;");
}

//Called from anim event of weapon equip. This should happen after the 3d is loaded hopefully
void HanldeWeaponEquipAfter3D() {
	if (!processCurrentScope || ignore) {
		return;
	}
	//Create turned off here for testing
	//nsScope::CreateRenderer();
}
