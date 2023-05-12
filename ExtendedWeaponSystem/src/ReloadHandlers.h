#pragma once
#include "Global.h"

void DoSpeedReload();

void HandleSequentialReload(const BSAnimationGraphEvent& a_event);

bool HasReloadStarted();
bool HasReloadEnded();

void reloadStop();
void reloadContinue();
void reloadContinueFromEmpty();
void reloadStartHandle();
void reloadEndHandle();

bool ShouldReload();

void StopLesserAmmo();

void SetWeapAmmoCapacity(int amount);
