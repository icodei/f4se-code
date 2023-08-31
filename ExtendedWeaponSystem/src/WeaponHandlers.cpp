#include "WeaponHandlers.h"

#include "Custom Renderer/CustomRenderer.h"
#include "Global.h"
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
	logInfo(MESSAGE_TITLE_FANCY_CENTERED(" Player TESEquipEvent "));
	logInfo(MESSAGE_BODY_2_FANCY_LEFT(" Weapon", initInfo.weapForm->fullName.c_str()));
	logInfo(MESSAGE_BODY_2_FANCY_LEFT(" CurrentAmmoCount", std::to_string(initInfo.weapAmmoCurrentCount)));
	logInfo(MESSAGE_BODY_2_FANCY_LEFT(" AmmoCapacity", std::to_string(initInfo.weapAmmoCapacity)));
	logInfo(MESSAGE_BODY_2_FANCY_LEFT(" TotalAmmoCount", std::to_string(initInfo.weapAmmoTotalCount)));
	QueryReload();
	QueryScope();
	logInfo(MESSAGE_FOOTER_FANCY_CENTERED);
	HandleWeaponChange();
}

void HandleWeaponEquipAfter3D(WeaponInfo& initInfo) {
	if (ScopeRenderer::customRendererInitialized) {
		ScopeRenderer::scopeCustomRenderer->pRendererCamera->Update3D();
	}
}

void HandleWeaponOnLoadGame(WeaponInfo& initInfo) {
	TESObjectWEAP::InstanceData* currentWeapon = const_cast<TESObjectWEAP::InstanceData*>(initInfo.weapInstanceData);
	if (initInfo.weapCurrentInstanceData != initInfo.weapInstanceData) {
		initInfo.weapCurrentInstanceData = const_cast<TESObjectWEAP::InstanceData*>(initInfo.weapInstanceData);
	}

	logInfo(MESSAGE_HEADER_FANCY_CENTERED);
	logInfo(MESSAGE_BODY_FANCY_CENTERED(" Game Loaded "));
	logInfo(MESSAGE_BODY_FANCY_CENTERED(" Getting Initial Weapon Stats "));
	logInfo(MESSAGE_SUBHEADER_FANCY_CENTERED);
	logInfo(MESSAGE_BODY_2_FANCY_LEFT(" Weapon", initInfo.weapForm->fullName.c_str()));
	logInfo(MESSAGE_BODY_2_FANCY_LEFT(" CurrentAmmoCount", std::to_string(initInfo.weapAmmoCurrentCount)));
	logInfo(MESSAGE_BODY_2_FANCY_LEFT(" AmmoCapacity", std::to_string(initInfo.weapAmmoCapacity)));
	logInfo(MESSAGE_BODY_2_FANCY_LEFT(" TotalAmmoCount", std::to_string(initInfo.weapAmmoTotalCount)));
	QueryReload();
	QueryScope();
	logInfo(MESSAGE_FOOTER_FANCY_CENTERED);
	HandleWeaponChange();
}

void HandleWeaponUnequip(WeaponInfo& initInfo) {
	logInfo(MESSAGE_TITLE_FANCY_CENTERED(" Player Unequip "));
	logInfo(MESSAGE_BODY_2_FANCY_LEFT(" Weapon", initInfo.weapForm->fullName.c_str()));
	logInfo(MESSAGE_FOOTER_FANCY_CENTERED);
	HandleWeaponChange();
	WeaponInfo::ClearWeaponInfo();
}

void HandleWeaponChange() {
	if (!WeaponHasSpecialScope()) {
		return;
	}
	if (!ScopeRenderer::scopeCustomRenderer) {
		ScopeRenderer::CreateCustomRenderer();
		ScopeRenderer::scopeCustomRenderer->pRendererCamera->StartCorrectState();
	} else {
		ScopeRenderer::DestroyCustomRenderer();
	}

	if (!ScopeRenderer::scopeLensRenderer && weaponHasScopeMagnification) {
		ScopeRenderer::CreateLensRenderer();
	} else {
		ScopeRenderer::DestroyLensRenderer();
	}

	if (!ScopeRenderer::scopeReticleRenderer) {
		ScopeRenderer::CreateReticleRenderer();
	} else {
		ScopeRenderer::DestroyReticleRenderer();
	}
}

void HandleWeaponDown() {
	if (ScopeRenderer::scopeCustomRenderer) {
		ScopeRenderer::DestroyCustomRenderer();
	}
	if (ScopeRenderer::scopeLensRenderer) {
		ScopeRenderer::DestroyLensRenderer();
	}
	if (ScopeRenderer::scopeReticleRenderer) {
		ScopeRenderer::DestroyReticleRenderer();
	}
}

void HandleWeaponInstantDown() {
	if (ScopeRenderer::scopeCustomRenderer) {
		ScopeRenderer::DestroyCustomRenderer();
	}
	if (ScopeRenderer::scopeLensRenderer) {
		ScopeRenderer::DestroyLensRenderer();
	}
	if (ScopeRenderer::scopeReticleRenderer) {
		ScopeRenderer::DestroyReticleRenderer();
	}
}

void HandleWeaponSightsEnter() {
	if (ScopeRenderer::scopeCustomRenderer) {
		ScopeRenderer::scopeCustomRenderer->pRendererCamera->UpdateCamera();
		//ScopeRenderer::Render();
	}
	if (ScopeRenderer::scopeLensRenderer) {
		ScopeRenderer::scopeLensRenderer->Show(true);
	}
	if (ScopeRenderer::scopeReticleRenderer) {
		ScopeRenderer::scopeReticleRenderer->Show(true);
	}
}

void HandleWeaponSightsExit() {
	if (ScopeRenderer::scopeLensRenderer) {
		ScopeRenderer::scopeLensRenderer->Hide();
	}
	if (ScopeRenderer::scopeReticleRenderer) {
		ScopeRenderer::scopeReticleRenderer->Hide();
	}
}

void MarkWeaponForPhysics(Actor* a_actor) {
	NiNode* node = a_actor->Get3D()->IsNode();
	bhkWorld* world = a_actor->parentCell->GetbhkWorld();
	if (node && node->children[0].get()) {
		BSVisit::VisitSimple(node->children[0].get(), [&](NiAVObject* obj) {
			if (obj->name.length() != 0 && obj->collisionObject) {  //TODO
				BSVisit::VisitSimple(obj, [a_actor, world](NiAVObject* obj) {
					if (!obj->collisionObject)
						return BSVisit::Stop;

					logInfo("Collision object found");
					bhkNPCollisionObject* colObj = obj->collisionObject->IsbhkNPCollisionObject();
					if (!colObj || !world) {
						logWarn("Obj is not bhkNPCollisionObject or bhkWorld does not exist");
						return BSVisit::Stop;
					}
					hknpBSWorld* hkWorld = *(hknpBSWorld**)((uintptr_t)world + 0x60);
					if (hkWorld) {
						hkWorld->MarkForWrite();
					}
					colObj->CreateInstance(*world);
					CFilter filter;
					filter.filter = (((a_actor)->GetCollisionFilter().filter >> 16) << 16) | 0x1408;
					colObj->SetCollisionFilterInfo(filter);
					colObj->SetMotionType(hknpMotionPropertiesId::Preset::KEYFRAMED);
					if (hkWorld) {
						hkWorld->UnmarkForWrite();
					}
					return BSVisit::Stop;
				});
				logInfo("Activate Havok - Done");
			}
			return BSVisit::Stop;
		});
	}
}

void QueryReload() {
	if (WeaponHasSpeedReload()) {
		weaponHasSpeedReload = true;
		logInfo(MESSAGE_BODY_FANCY_LEFT(" Weapon has speed reloads"));
	} else {
		weaponHasSpeedReload = false;
		logInfo(MESSAGE_BODY_FANCY_LEFT(" Weapon does not have speed reloads"));
	}
	if (WeaponHasSequentialReload()) {
		weaponHasSequentialReload = true;
		logInfo(MESSAGE_BODY_FANCY_LEFT(" Weapon has sequential reloads"));
	} else {
		weaponHasSequentialReload = false;
		logInfo(MESSAGE_BODY_FANCY_LEFT(" Weapon does not have sequential reloads"));
	}
}

void QueryScope() {
	int i = 0;
	if (WeaponHasNightVisionScope()) {
		weaponHasScopeNV = true;
		i++;
		logInfo(MESSAGE_BODY_FANCY_LEFT(" Weapon has night vision scope"));
	} else {
		weaponHasScopeNV = false;
	}
	if (WeaponHasPIPScope()) {
		weaponHasScopePIP = true;
		i++;
		logInfo(MESSAGE_BODY_FANCY_LEFT(" Weapon has PIP scope"));
	} else {
		weaponHasScopePIP = false;
	}
	if (WeaponHasThermalScope()) {
		weaponHasScopeThermal = true;
		i++;
		logInfo(MESSAGE_BODY_FANCY_LEFT(" Weapon has thermal scope"));
	} else {
		weaponHasScopeThermal = false;
	}

	if (WeaponHasNoSpecialScopes()) {
		logInfo(MESSAGE_BODY_FANCY_LEFT(" Weapon does not have special scopes"));
	}

	ASSERT(((i == 1) || (i == 0)), MESSAGE_CENTERED("Found more than one scope type. Unexpected results may happen"));
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

bool WeaponHasMagnificationScope() {
	return pc->WornHasKeyword(weaponHasScopeMagnificationKeyword);
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
