#include "WeaponHandlers.h"

bool WeaponHasSequentialReload() {
	return PlayerCharacter::GetSingleton()->WornHasKeyword(weaponHasSequentialReloadKeyword);
}

bool WeaponHasThermalScope() {
	return PlayerCharacter::GetSingleton()->WornHasKeyword(weaponHasThermalScopeKeyword);
}

WeaponInfo& WeaponInfo::operator=(const WeaponInfo& rhs) {
	weapEquip = rhs.weapEquip;
	weapEquipData = rhs.weapEquipData;
	weapAmmo = rhs.weapAmmo;
	weapForm = rhs.weapForm;
	weapInstance = rhs.weapInstance;
	weapInstanceData = rhs.weapInstanceData;
	return *this;
}

void WeaponInfo::ClearWeaponInfo() {
	weapInfo.weapEquip = nullptr;
	weapInfo.weapEquipData = nullptr;
	weapInfo.weapAmmo = nullptr;
	weapInfo.weapForm = nullptr;
	weapInfo.weapInstance = nullptr;
	weapInfo.weapInstanceData = nullptr;

	weapInfo.weapAmmoCapacity = 0;
	weapInfo.weapAmmoCurrentCount = 0;
	weapInfo.weapAmmoIncrementor = 0;
	weapInfo.weapAmmoToAdd = 0;
	weapInfo.weapAmmoTotalCount = 0;

	weapCurrentInstanceData = nullptr;
}

void WeaponInfo::InitSDM() {
	logInfo("Weapon Info Static Data Init");
	logger::info(FMT_STRING("WeapInfo: {:p}"), fmt::ptr(&weapInfo));
	weapInfo.weapEquip = nullptr;
	weapInfo.weapEquipData = nullptr;
	weapInfo.weapAmmo = nullptr;
	weapInfo.weapForm = nullptr;
	weapInfo.weapInstance = nullptr;
	weapInfo.weapInstanceData = nullptr;

	weapInfo.weapAmmoCapacity = 0;
	weapInfo.weapAmmoCurrentCount = 0;
	weapInfo.weapAmmoIncrementor = 0;
	weapInfo.weapAmmoToAdd = 0;
	weapInfo.weapAmmoTotalCount = 0;

	weapCurrentInstanceData = nullptr;
}

WeaponInfo WeaponInfo::weapInfo;
TESObjectWEAP::InstanceData* WeaponInfo::weapCurrentInstanceData;

WeaponInfo& FillWeaponInfo(WeaponInfo& initInfo) {
	logInfo("Filling Weapon Info...");
	
	/*
	const EquippedWeapon* weaponEquip = initInfo.weapEquip;
	const EquippedWeaponData* weaponEquipData = initInfo.weapEquipData;
	const TESObjectWEAP::InstanceData* weaponInstanceData = initInfo.weapInstanceData;
	const TESAmmo* weaponAmmo = initInfo.weapAmmo;
	const BGSObjectInstanceT<TESObjectWEAP>* weaponInstance = initInfo.weapInstance;
	const TESObjectWEAP* weaponForm = initInfo.weapForm;
	
	PlayerCharacter::GetSingleton()->currentProcess->GetEquippedItemArrayLock()->lock();
	//If weaponInstanceData is nullptr and weaponEquip is nullptr
	if ((initInfo.IsBothCriticalFilled() == false) || (weaponEquip->IsValid() == false)) {
		weaponEquip = &GetPlayerEquippedWeaponDefault();
		weaponInstanceData = (TESObjectWEAP::InstanceData*)weaponEquip->weapon.instanceData.get();
	}
	//If weaponInstanceData is nullptr or weaponEquip is nullptr
	if (initInfo.IsCriticalFilled()) {
		//If weaponInstanceData is nullptr
		if ((weaponInstanceData == nullptr) && weaponEquip && weaponEquip->IsValid()) {
			weaponInstanceData = (TESObjectWEAP::InstanceData*)weaponEquip->weapon.instanceData.get();
		}
		//If weaponEquip is nullptr
		if (weaponEquip == nullptr) {
			weaponEquip = &GetPlayerEquippedWeaponDefault();
		}
	}
	
	if (weaponInstanceData) {
		weaponInstance = &GetPlayerEquippedWeaponDefault().weapon;  //Could we get this a different way?
		weaponForm = weaponInstance->object->As<TESObjectWEAP>();
		weaponAmmo = weaponInstanceData->ammo;
		weapAmmoCapacity = weaponInstanceData->ammoCapacity;
		weapAmmoCurrentCount = pc->GetCurrentAmmoCount();
		weapAmmoTotalCount = GetPlayerInventoryObjectCount(weaponAmmo);
	} else if (weaponEquip->weapon.object) {
		weaponInstance = &weaponEquip->weapon;
		weaponForm = (weaponEquip->weapon.object)->As<TESObjectWEAP>();
		weaponAmmo = weaponForm->weaponData.ammo;
		weapAmmoCapacity = weaponForm->weaponData.ammoCapacity;
		weapAmmoCurrentCount = weaponEquip->weaponData->ammoCount;
		weapAmmoTotalCount = GetPlayerInventoryObjectCount(weaponAmmo);
	} else {
		weaponInstance = &GetPlayerEquippedWeaponDefault().weapon;
		weaponForm = weaponInstance->object->As<TESObjectWEAP>();
		weaponAmmo = pc->GetCurrentAmmo();
		weapAmmoCapacity = weaponForm->weaponData.ammoCapacity;
		weapAmmoCurrentCount = pc->GetCurrentAmmoCount();
		weapAmmoTotalCount = GetPlayerInventoryObjectCount(weaponAmmo);
	}
	PlayerCharacter::GetSingleton()->currentProcess->GetEquippedItemArrayLock()->unlock();
	*/

	PlayerCharacter::GetSingleton()->currentProcess->GetEquippedItemArrayLock()->lock();
	EquippedItem& a_item = PlayerCharacter::GetSingleton()->currentProcess->middleHigh->equippedItems[EquipIndex::kDefault];
	initInfo.weapEquip = const_cast<EquippedWeapon*>(reinterpret_cast<EquippedWeapon*>(&a_item));
	initInfo.weapEquipData = (EquippedWeaponData*)a_item.data.get();
	initInfo.weapInstance = &initInfo.weapEquip->weapon;
	initInfo.weapInstanceData = (TESObjectWEAP::InstanceData*)a_item.item.instanceData.get();
	initInfo.weapForm = a_item.item.object->As<TESObjectWEAP>();
	initInfo.weapAmmo = initInfo.weapInstanceData->ammo; //weapInstanceData is nullptr needs fix
	initInfo.weapAmmoCapacity = initInfo.weapInstanceData->ammoCapacity; //weapInstanceData is nullptr needs fix
	initInfo.weapAmmoCurrentCount = PlayerCharacter::GetSingleton()->GetCurrentAmmoCount();
	initInfo.weapAmmoTotalCount = GetPlayerInventoryObjectCount(initInfo.weapAmmo);
	PlayerCharacter::GetSingleton()->currentProcess->GetEquippedItemArrayLock()->unlock();

	const EquippedWeapon* weaponEquip = initInfo.weapEquip;
	const EquippedWeaponData* weaponEquipData = initInfo.weapEquipData;
	const TESObjectWEAP::InstanceData* weaponInstanceData = initInfo.weapInstanceData;
	const TESAmmo* weaponAmmo = initInfo.weapAmmo;
	const BGSObjectInstanceT<TESObjectWEAP>* weaponInstance = initInfo.weapInstance;
	const TESObjectWEAP* weaponForm = initInfo.weapForm;
	const int weaponAmmoCapacity = initInfo.weapAmmoCapacity;
	const int weaponAmmoCurrentCount = initInfo.weapAmmoCurrentCount;
	const int weaponAmmoTotalCount = initInfo.weapAmmoTotalCount;

	WeaponInfo::weapInfo.weapAmmo = weaponAmmo;
	WeaponInfo::weapInfo.weapForm = weaponForm;
	WeaponInfo::weapInfo.weapEquip = weaponEquip;
	WeaponInfo::weapInfo.weapInstance = weaponInstance;
	WeaponInfo::weapInfo.weapInstanceData = weaponInstanceData;
	WeaponInfo::weapInfo.weapAmmoCapacity = weaponAmmoCapacity;
	WeaponInfo::weapInfo.weapAmmoCurrentCount = weaponAmmoCurrentCount;
	WeaponInfo::weapInfo.weapAmmoTotalCount = weaponAmmoTotalCount;
	return WeaponInfo::weapInfo;
}

void HanldeWeaponEquip(WeaponInfo& initInfo) {
	TESObjectWEAP::InstanceData* currentWeapon = const_cast<TESObjectWEAP::InstanceData*>(initInfo.weapInstanceData);
	if (WeaponInfo::weapCurrentInstanceData != initInfo.weapInstanceData) {
		WeaponInfo::weapCurrentInstanceData = currentWeapon;
	}
	string weaponName = initInfo.weapForm->GetFullName();
	if (!WeaponInfo::weapCurrentInstanceData) {
		return;
	}
	logInfo(";================================ Player TESEquipEvent ================================;");
	logInfo("Weapon: " + weaponName);
	logInfo("CurrentAmmoCount: " + std::to_string(initInfo.weapAmmoCurrentCount));
	logInfo("AmmoCapacity: " + std::to_string(initInfo.weapAmmoCapacity));
	logInfo("TotalAmmoCount: " + std::to_string(initInfo.weapAmmoTotalCount));
	if (WeaponHasSequentialReload()) {
		weaponHasSequentialReload = true;
		logInfo("Weapon has sequential reloads");
		logInfo("Weapon instance equipped with ammo capacity of:" + std::to_string(WeaponInfo::weapCurrentInstanceData->ammoCapacity));
	} else {
		logInfo("Weapon does not have sequential reloads");
		weaponHasSequentialReload = false;
	}
	if (WeaponHasThermalScope()) {
		weaponHasThermalScope = true;
		logInfo("Thermal scope found");
		nsScope::CreateRenderer();
	} else {
		weaponHasThermalScope = false;
		logInfo("No thermal scope found");
	}
	logInfo(";======================================================================================;");
}

//Called from anim event of weapon equip. This should happen after the 3d is loaded hopefully
void HanldeWeaponEquipAfter3D(WeaponInfo& initInfo) {
	if (weaponHasThermalScope) {
		//Create turned off here for testing
		//nsScope::CreateRenderer();
	}
}

void HandleWeaponOnLoadGame(WeaponInfo& initInfo) {
	TESObjectWEAP::InstanceData* currentWeapon = const_cast<TESObjectWEAP::InstanceData*>(initInfo.weapInstanceData);
	if (WeaponInfo::weapCurrentInstanceData != initInfo.weapInstanceData) {
		WeaponInfo::weapCurrentInstanceData = currentWeapon;
	}
	string weaponName = initInfo.weapForm->GetFullName();
	logInfo(";====================== Game Loaded. Getting Initial Weapon Stats =====================;");
	logInfo("Weapon: " + weaponName);
	logInfo("CurrentAmmoCount: " + std::to_string(initInfo.weapAmmoCurrentCount));
	logInfo("AmmoCapacity: " + std::to_string(initInfo.weapAmmoCapacity));
	logInfo("TotalAmmoCount: " + std::to_string(initInfo.weapAmmoTotalCount));
	if (WeaponHasSequentialReload()) {
		weaponHasSequentialReload = true;
		logInfo(weaponName + " reloads sequentially");
	} else {
		weaponHasSequentialReload = false;
		logInfo(weaponName + " does not reload sequnetially");
	}
	if (WeaponHasThermalScope()) {
		weaponHasThermalScope = true;
		logInfo(weaponName + " has a thermal scope");
	} else {
		weaponHasThermalScope = false;
		logInfo(weaponName + " does not have a thermal scope");
	}
	logInfo(";======================================================================================;");
}

void QueueHandlingOfWeapon(WeaponInfo& initInfo) {
	//Weapon is already in queue
	if (weaponIsQueued) {
		return;
	}
	weaponIsQueued = true;

	std::thread([]() -> void {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//Is weapon still in queue
		if (weaponIsQueued) {
			g_taskInterface->AddTask([]() {
				if (*(bool*)((uintptr_t)PlayerCharacter::GetSingleton()->currentProcess->high + 0x594)) {
					weaponIsQueued = false;
					QueueHandlingOfWeapon(WeaponInfo::weapInfo);
					return;
				}

				//Reset variables here?

				if (PlayerCharacter::GetSingleton()->currentProcess->middleHigh->equippedItems.size() == 0) {
					weaponIsQueued = false;
					return;
				}

				HanldeWeaponEquip(FillWeaponInfo(WeaponInfo::weapInfo));
				weaponIsQueued = false;
			});
		}
	}).detach();
}
