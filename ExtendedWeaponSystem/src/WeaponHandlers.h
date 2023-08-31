#pragma once
#include "Global.h"

#include "WeaponInfo.h"

void HandleWeaponEquip(WeaponInfo& initInfo);
void HandleWeaponEquipAfter3D(WeaponInfo& initInfo);
void HandleWeaponOnLoadGame(WeaponInfo& initInfo);
void HandleWeaponUnequip(WeaponInfo& initInfo);

void HandleWeaponChange();
void HandleWeaponDown();
void HandleWeaponInstantDown();
void HandleWeaponSightsEnter();
void HandleWeaponSightsExit();

void MarkWeaponForPhysics(Actor* a_actor);

void QueryReload();
void QueryScope();
void QueueHandlingOfWeaponFunctor(WeaponInfo& initInfo, std::function<void(WeaponInfo&)> functor);
void QueueHandlingOfWeaponEquip(WeaponInfo& initInfo);
void QueueHandlingOfWeaponUnequip(WeaponInfo& initInfo);

bool WeaponHasSequentialReload();
bool WeaponHasSpeedReload();
bool WeaponHasMagnificationScope();
bool WeaponHasNightVisionScope();
bool WeaponHasPIPScope();
bool WeaponHasThermalScope();
bool WeaponHasSpecialScope();
bool WeaponHasNoSpecialScopes();
