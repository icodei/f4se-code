#include "WeaponInfo.h"

void WeaponInfo::ClearWeaponInfo() {
	WeaponInfo& info = WeaponInfo::getInstance();
	info.weapEquip = nullptr;
	info.weapEquipData = nullptr;
	info.weapAmmo = nullptr;
	info.weapForm = nullptr;
	info.weapInstance = nullptr;
	info.weapInstanceData = nullptr;

	info.weapCurrentInstanceData = nullptr;

	info.weapAmmoCapacity = 0;
	info.weapAmmoCurrentCount = 0;
	info.weapAmmoIncrementor = 0;
	info.weapAmmoToAdd = 0;
	info.weapAmmoTotalCount = 0;
}

WeaponInfo& WeaponInfo::getInstance() {
	static WeaponInfo instance;
	return instance;
}

WeaponInfo& FillWeaponInfo(WeaponInfo& initInfo) {
	logInfo("Filling Weapon Info...");
	WeaponInfo& Info = WeaponInfo::getInstance();

	pc->currentProcess->GetEquippedItemArrayLock()->lock();
	EquippedItem& a_item = pc->currentProcess->middleHigh->equippedItems[EquipIndex::kDefault];
	initInfo.weapEquip = const_cast<EquippedWeapon*>(reinterpret_cast<EquippedWeapon*>(&a_item));
	initInfo.weapEquipData = (EquippedWeaponData*)a_item.data.get();
	initInfo.weapAmmo = pc->GetCurrentAmmo();
	initInfo.weapForm = a_item.item.object->As<TESObjectWEAP>();
	initInfo.weapInstance = &initInfo.weapEquip->weapon;
	initInfo.weapInstanceData = (TESObjectWEAP::InstanceData*)a_item.item.instanceData.get();
	initInfo.weapCurrentInstanceData = (TESObjectWEAP::InstanceData*)pc->GetCurrentWeapon().instanceData.get();
	initInfo.weapAmmoCapacity = a_item.item.object->As<TESObjectWEAP>()->weaponData.ammoCapacity;
	initInfo.weapAmmoCurrentCount = pc->GetCurrentAmmoCount();
	initInfo.weapAmmoTotalCount = GetPlayerInventoryObjectCount(initInfo.weapAmmo);
	pc->currentProcess->GetEquippedItemArrayLock()->unlock();

	const EquippedWeapon* weaponEquip = initInfo.weapEquip;
	const EquippedWeaponData* weaponEquipData = initInfo.weapEquipData;
	const TESAmmo* weaponAmmo = initInfo.weapAmmo;
	const TESObjectWEAP* weaponForm = initInfo.weapForm;
	const BGSObjectInstanceT<TESObjectWEAP>* weaponInstance = initInfo.weapInstance;
	const TESObjectWEAP::InstanceData* weaponInstanceData = initInfo.weapInstanceData;
	TESObjectWEAP::InstanceData* weaponCurrentInstance = initInfo.weapCurrentInstanceData;
	const int weaponAmmoCapacity = initInfo.weapAmmoCapacity;
	const int weaponAmmoCurrentCount = initInfo.weapAmmoCurrentCount;
	const int weaponAmmoTotalCount = initInfo.weapAmmoTotalCount;

	Info.weapAmmo = weaponAmmo;
	Info.weapForm = weaponForm;
	Info.weapEquip = weaponEquip;
	Info.weapInstance = weaponInstance;
	Info.weapInstanceData = weaponInstanceData;
	Info.weapCurrentInstanceData = weaponCurrentInstance;
	Info.weapAmmoCapacity = weaponAmmoCapacity;
	Info.weapAmmoCurrentCount = weaponAmmoCurrentCount;
	Info.weapAmmoTotalCount = weaponAmmoTotalCount;
	return Info;
}
