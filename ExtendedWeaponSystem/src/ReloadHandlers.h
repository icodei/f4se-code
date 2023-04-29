#pragma once
#include "Global.h"

void DoSpeedReload(int32_t id);

bool HasReloadStarted();
bool HasReloadEnded();

void reloadStop();
void reloadContinue();
void reloadContinueFromEmpty();
void reloadStartHandle();
void reloadEndHandle();

void StopLesserAmmo();

void SetWeapAmmoCapacity(int amount);
