#include "WeaponHandlers.h"

#pragma region WeaponInfo
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
	Info::weapInfo.weapEquip = nullptr;
	Info::weapInfo.weapEquipData = nullptr;
	Info::weapInfo.weapAmmo = nullptr;
	Info::weapInfo.weapForm = nullptr;
	Info::weapInfo.weapInstance = nullptr;
	Info::weapInfo.weapInstanceData = nullptr;

	Info::weapInfo.weapAmmoCapacity = 0;
	Info::weapInfo.weapAmmoCurrentCount = 0;
	Info::weapInfo.weapAmmoIncrementor = 0;
	Info::weapInfo.weapAmmoToAdd = 0;
	Info::weapInfo.weapAmmoTotalCount = 0;

	Info::weapCurrentInstanceData = nullptr;
}

namespace Info {
	WeaponInfo weapInfo = WeaponInfo();
	TESObjectWEAP::InstanceData* weapCurrentInstanceData = nullptr;
}

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
		if (!weaponInstanceData && weaponEquip && weaponEquip->IsValid()) {
			weaponInstanceData = (TESObjectWEAP::InstanceData*)weaponEquip->weapon.instanceData.get();
		}
		//If weaponEquip is nullptr
		if (!weaponEquip) {
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

	pc->currentProcess->GetEquippedItemArrayLock()->lock();
	EquippedItem& a_item = pc->currentProcess->middleHigh->equippedItems[EquipIndex::kDefault];
	initInfo.weapEquip = const_cast<EquippedWeapon*>(reinterpret_cast<EquippedWeapon*>(&a_item));
	initInfo.weapEquipData = (EquippedWeaponData*)a_item.data.get();
	initInfo.weapInstance = &initInfo.weapEquip->weapon;
	initInfo.weapInstanceData = (TESObjectWEAP::InstanceData*)a_item.item.instanceData.get();
	initInfo.weapForm = a_item.item.object->As<TESObjectWEAP>();
	initInfo.weapAmmo = pc->GetCurrentAmmo();
	initInfo.weapAmmoCapacity = a_item.item.object->As<TESObjectWEAP>()->weaponData.ammoCapacity;
	initInfo.weapAmmoCurrentCount = pc->GetCurrentAmmoCount();
	initInfo.weapAmmoTotalCount = GetPlayerInventoryObjectCount(initInfo.weapAmmo);
	pc->currentProcess->GetEquippedItemArrayLock()->unlock();

	const EquippedWeapon* weaponEquip = initInfo.weapEquip;
	const EquippedWeaponData* weaponEquipData = initInfo.weapEquipData;
	const TESObjectWEAP::InstanceData* weaponInstanceData = initInfo.weapInstanceData;
	const TESAmmo* weaponAmmo = initInfo.weapAmmo;
	const BGSObjectInstanceT<TESObjectWEAP>* weaponInstance = initInfo.weapInstance;
	const TESObjectWEAP* weaponForm = initInfo.weapForm;
	const int weaponAmmoCapacity = initInfo.weapAmmoCapacity;
	const int weaponAmmoCurrentCount = initInfo.weapAmmoCurrentCount;
	const int weaponAmmoTotalCount = initInfo.weapAmmoTotalCount;

	Info::weapInfo.weapAmmo = weaponAmmo;
	Info::weapInfo.weapForm = weaponForm;
	Info::weapInfo.weapEquip = weaponEquip;
	Info::weapInfo.weapInstance = weaponInstance;
	Info::weapInfo.weapInstanceData = weaponInstanceData;
	Info::weapInfo.weapAmmoCapacity = weaponAmmoCapacity;
	Info::weapInfo.weapAmmoCurrentCount = weaponAmmoCurrentCount;
	Info::weapInfo.weapAmmoTotalCount = weaponAmmoTotalCount;
	return Info::weapInfo;
}
#pragma endregion

void HanldeWeaponEquip(WeaponInfo& initInfo) {
	TESObjectWEAP::InstanceData* currentWeapon = const_cast<TESObjectWEAP::InstanceData*>(initInfo.weapInstanceData);
	string weaponName = initInfo.weapForm->GetFullName();
	if (Info::weapCurrentInstanceData != initInfo.weapInstanceData) {
		Info::weapCurrentInstanceData = currentWeapon;
	}
	if (!Info::weapCurrentInstanceData) {
		return;
	}
	logInfo(";================================ Player TESEquipEvent ================================;");
	logInfo("Weapon: " + weaponName);
	logInfo("CurrentAmmoCount: " + std::to_string(initInfo.weapAmmoCurrentCount));
	logInfo("AmmoCapacity: " + std::to_string(initInfo.weapAmmoCapacity));
	logInfo("TotalAmmoCount: " + std::to_string(initInfo.weapAmmoTotalCount));
	QueryReload();
	QueryScope();
	logInfo(";======================================================================================;");
	HandleWeaponChange();
}

void HanldeWeaponEquipAfter3D(WeaponInfo& initInfo) {
	if (!nsScope::initialized || !nsScope::scopeRenderer) {
		goto skipRender;
	}

	nsScope::scopeRenderer->pRendererCamera->Update3D();

skipRender:
	{

	}
}

void HandleWeaponOnLoadGame(WeaponInfo& initInfo) {
	TESObjectWEAP::InstanceData* currentWeapon = const_cast<TESObjectWEAP::InstanceData*>(initInfo.weapInstanceData);
	if (Info::weapCurrentInstanceData != initInfo.weapInstanceData) {
		Info::weapCurrentInstanceData = currentWeapon;
	}
	string weaponName = initInfo.weapForm->GetFullName();
	logInfo(";====================== Game Loaded. Getting Initial Weapon Stats =====================;");
	logInfo("Weapon: " + weaponName);
	logInfo("CurrentAmmoCount: " + std::to_string(initInfo.weapAmmoCurrentCount));
	logInfo("AmmoCapacity: " + std::to_string(initInfo.weapAmmoCapacity));
	logInfo("TotalAmmoCount: " + std::to_string(initInfo.weapAmmoTotalCount));
	QueryReload();
	QueryScope();
	logInfo(";======================================================================================;");
	HandleWeaponChange();
}

void HandleWeaponChange() {
	if (!nsScope::scopeRenderer && WeaponHasSpecialScope()) {
		logInfo("Weapon needs custom renderer");
		nsScope::CreateRenderer();
		nsScope::scopeRenderer->pRendererCamera->StartCorrectState();
	} else {
		if (nsScope::scopeRenderer) {
			nsScope::DestroyRenderer();
		}
	}
}

void HandleWeaponInstantDown() {
}

void HandleWeaponSightsEnter() {
	if (!nsScope::initialized || !nsScope::scopeRenderer) {
		goto skipRender;
	}
	nsScope::scopeRenderer->pRendererCamera->UpdateCamera();
	nsScope::Render();

skipRender:
	{
		//In the future anything further added that does not involve the scope renderer should go here
	}
}

void HandleWeaponSightsExit() {
}

void QueryReload() {
	if (WeaponHasSequentialReload()) {
		weaponHasSequentialReload = true;
		logInfo("Weapon has sequential reloads");
	} else {
		weaponHasSequentialReload = false;
		logInfo("Weapon does not have sequential reloads");
	}
}

void QueryScope() {
	int i = 0;
	if (WeaponHasNightVisionScope()) {
		weaponHasScopeNV = true;
		i++;
		logInfo("NightVision scope found");
	} else {
		weaponHasScopeNV = false;
	}
	if (WeaponHasPIPScope()) {
		weaponHasScopePIP = true;
		i++;
		logInfo("PIP scope found");
	} else {
		weaponHasScopePIP = false;
	}
	if (WeaponHasThermalScope()) {
		weaponHasScopeThermal = true;
		i++;
		logInfo("Thermal scope found");
	} else {
		weaponHasScopeThermal = false;
	}

	if (WeaponHasNoSpecialScopes()) {
		logInfo("No special scopes were found");
	}

	if (i > 1) {
		logError("QueryScope() Found more than one scope type. Unexpected results may happen");
	}
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
				if (*(bool*)((uintptr_t)pc->currentProcess->high + 0x594)) {
					weaponIsQueued = false;
					QueueHandlingOfWeapon(Info::weapInfo);
					return;
				}

				//Reset variables here?

				if (pc->currentProcess->middleHigh->equippedItems.size() == 0) {
					weaponIsQueued = false;
					return;
				}

				HanldeWeaponEquip(FillWeaponInfo(Info::weapInfo));
				weaponIsQueued = false;
			});
		}
	}).detach();
}

bool WeaponHasSequentialReload() {
	return pc->WornHasKeyword(weaponHasSequentialReloadKeyword);
}

bool WeaponHasNightVisionScope() {
	return pc->WornHasKeyword(weaponHasScopeNVKeyword);
}

bool WeaponHasPIPScope() {
	return pc->WornHasKeyword(weaponHasScopePIPKeyword);
}

bool WeaponHasThermalScope() {
	return pc->WornHasKeyword(weaponHasScopeThermalKeyword);
}

bool WeaponHasSpecialScope() {
	return (weaponHasScopeNV || weaponHasScopePIP || weaponHasScopeThermal);
}

bool WeaponHasNoSpecialScopes() {
	return (!weaponHasScopeNV && !weaponHasScopePIP && !weaponHasScopeThermal);
}
