#pragma once
#include "Global.h"

struct WeaponInfo;

void HanldeWeaponEquip(WeaponInfo& initInfo);
void HanldeWeaponEquipAfter3D(WeaponInfo& initInfo);
void HandleWeaponOnLoadGame(WeaponInfo& initInfo);

void HandleWeaponChange();
void HandleWeaponDown();
void HandleWeaponSightsEnter();
void HandleWeaponSightsExit();

void QueryReload();
void QueryScope();
void QueueHandlingOfWeapon(WeaponInfo& initInfo);

bool WeaponHasSequentialReload();
bool WeaponHasSpeedReload();
bool WeaponHasNightVisionScope();
bool WeaponHasPIPScope();
bool WeaponHasThermalScope();
bool WeaponHasSpecialScope();
bool WeaponHasNoSpecialScopes();
