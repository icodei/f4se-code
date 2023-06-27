#include "WeaponHandlers.h"

#include "Custom Renderer/CustomRenderer.h"
#include "Util.h"
#include "Global.h"

void HandleWeaponEquip(WeaponInfo& initInfo) {
	WeaponInfo& Info = WeaponInfo::getInstance();
	string weaponName = initInfo.weapForm->GetFullName();
	if (initInfo.weapCurrentInstanceData != initInfo.weapInstanceData) {
		initInfo.weapCurrentInstanceData = const_cast<TESObjectWEAP::InstanceData*>(initInfo.weapInstanceData);
	}
	if (!initInfo.weapCurrentInstanceData || !initInfo.weapInstanceData) {
		return;
	}
	logInfo(fmt::format(FMT_STRING(";{0:=^{1}};"), " Player TESEquipEvent "sv, 80));
	logInfo("Weapon: " + weaponName);
	logInfo("CurrentAmmoCount: " + std::to_string(initInfo.weapAmmoCurrentCount));
	logInfo("AmmoCapacity: " + std::to_string(initInfo.weapAmmoCapacity));
	logInfo("TotalAmmoCount: " + std::to_string(initInfo.weapAmmoTotalCount));
	QueryReload();
	QueryScope();
	logInfo(fmt::format(FMT_STRING(";{0:=^{1}};"), ""sv, 80));
	HandleWeaponChange();
}

void HandleWeaponEquipAfter3D(WeaponInfo& initInfo) {
	//if (!ScopeRenderer::initialized || !ScopeRenderer::scopeCustomRenderer) {
	//
	//}
	//ScopeRenderer::scopeCustomRenderer->pRendererCamera->Update3D();
}

void HandleWeaponOnLoadGame(WeaponInfo& initInfo) {
	TESObjectWEAP::InstanceData* currentWeapon = const_cast<TESObjectWEAP::InstanceData*>(initInfo.weapInstanceData);
	if (initInfo.weapCurrentInstanceData != initInfo.weapInstanceData) {
		initInfo.weapCurrentInstanceData = const_cast<TESObjectWEAP::InstanceData*>(initInfo.weapInstanceData);
	}
	string weaponName = initInfo.weapForm->GetFullName();
	logInfo(fmt::format(FMT_STRING(";{0:=^{1}};"), ""sv, 80));
	logInfo(fmt::format(FMT_STRING(";{0: ^{1}};"), " Game Loaded "sv, 80));
	logInfo(fmt::format(FMT_STRING(";{0: ^{1}};"), " Getting Initial Weapon Stats "sv, 80));
	logInfo(fmt::format(FMT_STRING(";{0:=^{1}};"), ""sv, 80));
	logInfo("Weapon: " + weaponName);
	logInfo("CurrentAmmoCount: " + std::to_string(initInfo.weapAmmoCurrentCount));
	logInfo("AmmoCapacity: " + std::to_string(initInfo.weapAmmoCapacity));
	logInfo("TotalAmmoCount: " + std::to_string(initInfo.weapAmmoTotalCount));
	QueryReload();
	QueryScope();
	logInfo(fmt::format(FMT_STRING(";{0:=^{1}};"), ""sv, 80));
	HandleWeaponChange();
}

void HandleWeaponUnequip(WeaponInfo& initInfo) {
	string weaponName = initInfo.weapForm->GetFullName();
	logInfo(fmt::format(FMT_STRING(";{0:=^{1}};"), " Player Unequip "sv, 80));
	logInfo("Weapon: " + weaponName);
	logInfo(fmt::format(FMT_STRING(";{0:=^{1}};"), ""sv, 80));
	HandleWeaponChange();
	WeaponInfo::ClearWeaponInfo();
}

void HandleWeaponChange() {
	if (!ScopeRenderer::scopeCustomRenderer && WeaponHasSpecialScope()) {
		//logInfo("Weapon needs custom renderer");
		//ScopeRenderer::CreateCustomRenderer();
		//ScopeRenderer::scopeCustomRenderer->pRendererCamera->StartCorrectState();
	} else {
		//ScopeRenderer::DestroyCustomRenderer();
	}

	if (!ScopeRenderer::scopeLensRenderer && WeaponHasSpecialScope()) {
		logInfo("Weapon needs custom renderer");
		ScopeRenderer::CreateLensRenderer();
	} else {
		if (ScopeRenderer::scopeLensRenderer->visible) {
			ScopeRenderer::scopeLensRenderer->Hide();
		}
		ScopeRenderer::DestroyLensRenderer();
	}
}

void HandleWeaponDown() {
	if (ScopeRenderer::scopeCustomRenderer) {
		ScopeRenderer::DestroyCustomRenderer();
	}
	if (ScopeRenderer::scopeLensRenderer) {
		ScopeRenderer::DestroyLensRenderer();
	}
}

void HandleWeaponInstantDown() {
	if (ScopeRenderer::scopeCustomRenderer) {
		ScopeRenderer::DestroyCustomRenderer();
	}
	if (ScopeRenderer::scopeLensRenderer) {
		ScopeRenderer::scopeLensRenderer->Hide();
		ScopeRenderer::DestroyLensRenderer();
	}
}

void HandleWeaponSightsEnter() {
	if (ScopeRenderer::scopeCustomRenderer) {
		ScopeRenderer::scopeCustomRenderer->pRendererCamera->UpdateCamera();
		ScopeRenderer::Render();
	}
	if (ScopeRenderer::scopeLensRenderer) {
		ScopeRenderer::scopeLensRenderer->Show(true);
	}
}

void HandleWeaponSightsExit() {
	if (ScopeRenderer::scopeLensRenderer) {
		ScopeRenderer::scopeLensRenderer->Hide();
	}
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
		logInfo("Weapon has night vision scope");
	} else {
		weaponHasScopeNV = false;
	}
	if (WeaponHasPIPScope()) {
		weaponHasScopePIP = true;
		i++;
		logInfo("Weapon has PIP scope");
	} else {
		weaponHasScopePIP = false;
	}
	if (WeaponHasThermalScope()) {
		weaponHasScopeThermal = true;
		i++;
		logInfo("Weapon has thermal scope");
	} else {
		weaponHasScopeThermal = false;
	}

	if (WeaponHasNoSpecialScopes()) {
		logInfo("Weapon does not have special scopes");
	}

	if (i > 1) {
		auto error = "Found more than one scope type. Unexpected results may happen"sv;
		logError(fmt::format(FMT_STRING(";{0: ^{1}};"), (ASSERT(error)), 80));
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
