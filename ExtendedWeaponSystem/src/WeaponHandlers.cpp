#include "WeaponHandlers.h"

#include "Custom Renderer/CustomRenderer.h"
#include "Util.h"

void HandleWeaponEquip(WeaponInfo& initInfo) {
	WeaponInfo& Info = WeaponInfo::getInstance();
	string weaponName = initInfo.weapForm->GetFullName();
	if (initInfo.weapCurrentInstanceData != initInfo.weapInstanceData) {
		initInfo.weapCurrentInstanceData = const_cast<TESObjectWEAP::InstanceData*>(initInfo.weapInstanceData);
	}
	if (!initInfo.weapCurrentInstanceData || !initInfo.weapInstanceData) {
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

void HandleWeaponEquipAfter3D(WeaponInfo& initInfo) {
	if (!nsScope::initialized || !nsScope::scopeRenderer) {
		goto skipRender;
	}

	nsScope::scopeRenderer->pRendererCamera->Update3D();

skipRender:
	{
		//In the future anything further added that does not involve the scope renderer should go here
	}
}

void HandleWeaponOnLoadGame(WeaponInfo& initInfo) {
	TESObjectWEAP::InstanceData* currentWeapon = const_cast<TESObjectWEAP::InstanceData*>(initInfo.weapInstanceData);
	if (initInfo.weapCurrentInstanceData != initInfo.weapInstanceData) {
		initInfo.weapCurrentInstanceData = const_cast<TESObjectWEAP::InstanceData*>(initInfo.weapInstanceData);
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

void HandleWeaponUnequip(WeaponInfo& initInfo) {
	string weaponName = initInfo.weapForm->GetFullName();
	logInfo(";=================================== Player Unequip ===================================;");
	logInfo("Weapon: " + weaponName);
	WeaponInfo::ClearWeaponInfo();
	logInfo(";======================================================================================;");
}

void HandleWeaponChange() {
	if (!nsScope::scopeRenderer && WeaponHasSpecialScope()) {
		logInfo("Weapon needs custom renderer");
		nsScope::CreateRenderer();
		nsScope::scopeRenderer->pRendererCamera->StartCorrectState();
	} else {
		nsScope::DestroyRenderer();
	}
}

void HandleWeaponDown() {
	nsScope::DestroyRenderer();
}

void HandleWeaponInstantDown() {
	nsScope::DestroyRenderer();
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
	if (WeaponHasSpeedReload()) {
		weaponHasSpeedReload = true;
		logInfo("Weapon has speed reloads");
	} else {
		weaponHasSpeedReload = false;
		logInfo("Weapon does not have speed reloads");
	}
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

void QueueHandlingOfWeaponFunctor(WeaponInfo& initInfo, std::function<void(WeaponInfo&)> functor) {
	//Weapon is already in queue
	if (weaponIsQueued) {
		return;
	}
	weaponIsQueued = true;

	std::thread([&initInfo, &functor]() -> void {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//Is weapon still in queue
		if (weaponIsQueued) {
			g_taskInterface->AddTask([&initInfo, &functor]() {
				if (*(bool*)((uintptr_t)pc->currentProcess->high + 0x594)) {
					weaponIsQueued = false;
					QueueHandlingOfWeaponFunctor(initInfo, functor);
					return;
				}

				//Reset variables here?

				if (pc->currentProcess->middleHigh->equippedItems.size() == 0) {
					weaponIsQueued = false;
					return;
				}

				functor(FillWeaponInfo(initInfo));
				weaponIsQueued = false;
			});
		}
	}).detach();
}

void QueueHandlingOfWeaponEquip(WeaponInfo& initInfo) {
	//Weapon is already in queue
	if (weaponIsQueued) {
		return;
	}
	weaponIsQueued = true;

	std::thread([&initInfo]() -> void {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//Is weapon still in queue
		if (weaponIsQueued) {
			g_taskInterface->AddTask([&initInfo]() {
				if (*(bool*)((uintptr_t)pc->currentProcess->high + 0x594)) {
					weaponIsQueued = false;
					QueueHandlingOfWeaponEquip(initInfo);
					return;
				}

				//Reset variables here?

				if (pc->currentProcess->middleHigh->equippedItems.size() == 0) {
					weaponIsQueued = false;
					return;
				}

				HandleWeaponEquip(FillWeaponInfo(initInfo));
				weaponIsQueued = false;
			});
		}
	}).detach();
}

void QueueHandlingOfWeaponUnequip(WeaponInfo& initInfo) {
	//Weapon is already in queue
	if (weaponIsQueued) {
		return;
	}
	weaponIsQueued = true;

	std::thread([&initInfo]() -> void {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//Is weapon still in queue
		if (weaponIsQueued) {
			g_taskInterface->AddTask([&initInfo]() {
				if (*(bool*)((uintptr_t)pc->currentProcess->high + 0x594)) {
					weaponIsQueued = false;
					QueueHandlingOfWeaponUnequip(initInfo);
					return;
				}

				//Reset variables here?

				if (pc->currentProcess->middleHigh->equippedItems.size() == 0) {
					weaponIsQueued = false;
					return;
				}

				HandleWeaponUnequip(FillWeaponInfo(initInfo));
				weaponIsQueued = false;
			});
		}
	}).detach();
}

bool WeaponHasSequentialReload() {
	return pc->WornHasKeyword(weaponHasSequentialReloadKeyword);
}

bool WeaponHasSpeedReload() {
	return pc->WornHasKeyword(weaponHasSpeedReloadKeyword);
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
