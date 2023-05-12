#include "ReloadHandlers.h"

#include "Util.h"
#include "WeaponInfo.h"

void DoSpeedReload() {
	//logInfo("Speed Reload");
	const BSFixedString reloadSpeedStart("reloadSpeedStart");
	const BSFixedString reloadSpeedReserveStart("reloadSpeedReserveStart");
	const BSFixedString reloadSequentialSpeedStart("reloadSequentialSpeedStart");
	const BSFixedString reloadSequentialSpeedReserveStart("reloadSequentialSpeedReserveStart");

	WeaponInfo& Info = WeaponInfo::getInstance();

	if (Info.weapAmmoCurrentCount) {
		if (weaponHasSequentialReload) {
			//
		} else {
			pc->NotifyAnimationGraphImpl(reloadSpeedReserveStart);
		}
	} else {
		if (weaponHasSequentialReload) {
			//
		} else {
			pc->NotifyAnimationGraphImpl(reloadSpeedStart);
		}
	}
}

void HandleSequentialReload(const BSAnimationGraphEvent& a_event) {
	WeaponInfo& Info = WeaponInfo::getInstance();
	const BSFixedString Event00("Event00");
	const BSFixedString pipboyClosed("pipboyClosed");
	const BSFixedString pipboyOpened("pipboyOpened");
	const BSFixedString ReloadComplete("ReloadComplete");
	const BSFixedString ReloadEnd("ReloadEnd");
	const BSFixedString reloadSequentialReserveStart("reloadSequentialReserveStart");
	const BSFixedString reloadSequentialStart("reloadSequentialStart");
	const BSFixedString sightedStateEnter("sightedStateEnter");
	const BSFixedString sightedStateExit("sightedStateExit");
	const BSFixedString throwEnd("throwEnd");
	const BSFixedString weapEquip("weapEquip");
	const BSFixedString weapForceEquip("weapForceEquip");
	const BSFixedString weaponDraw("weaponDraw");
	const BSFixedString WeaponFire("WeaponFire");
	const BSFixedString weaponInstantDown("weaponInstantDown");
	const BSFixedString weaponSwing("weaponSwing");
	const BSFixedString weapUnequip("weapUnequip");

	if (HasReloadEnded()) {
		if (a_event.name == Event00) {
			reloadStartHandle();
			StopLesserAmmo();
			isEmptyReload = Info.weapAmmoCurrentCount == 0 ? true : false;
		}
	}
	if (HasReloadStarted()) {
		if (a_event.name == ReloadEnd) {  //Better way to do this? Bolt action stuff calls reloadend event during bolt charge and reload
			logInfo("Event Recieved: ReloadEnd");
			reloadStop();
		}
		if (a_event.name == ReloadComplete) {
			logInfo("Event Recieved: reloadComplete");
			if ((Info.weapAmmoCapacity - 1) == Info.weapAmmoCurrentCount) {
				reloadStop();
			} else {
				SetWeapAmmoCapacity(Info.weapAmmoCurrentCount + 1);
				if (isEmptyReload) {
					reloadContinueFromEmpty();
				} else {
					reloadContinue();
				}
			}
		}
		//Manually handle reload end for various situations
		if (a_event.name == pipboyOpened) {
			reloadStop();
			logInfo("Event Recieved: pipboy opened");
		}
		if (a_event.name == weaponSwing) {
			reloadStop();
			logInfo("Event Recieved: weapon swing");
		}
		if (a_event.name == throwEnd) {
			reloadStop();
			logInfo("Event Recieved: throw end");
		}
	}
}

bool HasReloadStarted() {
	return reloadHasStarted && !reloadHasEnded;
}

bool HasReloadEnded() {
	return !reloadHasStarted && reloadHasEnded;
}

void reloadStop() {
	const BSFixedString bReloadLoop("bReloadLoop");

	logInfo("Stopping reload loop");
	reloadEndHandle();
	pc->SetGraphVariableBool(bReloadLoop, false);
}

void reloadContinue() {
	const BSFixedString bReloadLoop("bReloadLoop");
	const BSFixedString reloadSequentialReserveStart("reloadSequentialReserveStart");

	logInfo("Continuing reload loop");
	pc->SetGraphVariableBool(bReloadLoop, true);
	pc->NotifyAnimationGraphImpl(reloadSequentialReserveStart);
}

void reloadContinueFromEmpty() {
	const BSFixedString bReloadLoop("bReloadLoop");
	const BSFixedString reloadSequentialStart("reloadSequentialStart");

	logInfo("Continuing reload loop");
	pc->SetGraphVariableBool(bReloadLoop, true);
	pc->NotifyAnimationGraphImpl(reloadSequentialStart);
}

//ready needed stuff when reload is started
void reloadStartHandle() {
	logInfo("reloadStartHandle");
	WeaponInfo& Info = WeaponInfo::getInstance();
	Info.weapAmmoIncrementor = 0;
	Info.weapAmmoToAdd = Info.weapAmmoCapacity - Info.weapAmmoCurrentCount;
	reloadHasStarted = true;
	reloadHasEnded = false;
	SetWeapAmmoCapacity(Info.weapAmmoCurrentCount);
}

//clear needed stuff when reload ends
void reloadEndHandle() {
	logInfo("reloadEndHandle");
	WeaponInfo& Info = WeaponInfo::getInstance();
	reloadHasEnded = true;
	reloadHasStarted = false;
	Info.weapAmmoIncrementor = 0;
	Info.weapAmmoToAdd = 0;
	SetWeapAmmoCapacity(Info.weapAmmoCapacity);
}

bool ShouldReload() {
	WeaponInfo& Info = WeaponInfo::getInstance();
	if (Info.weapCurrentInstanceData->ammoCapacity == Info.weapAmmoCurrentCount) {
		return false;
	} else {
		return true;
	}
}

//Stops the reload early if there is not enough ammo in the inventory
void StopLesserAmmo() {
	WeaponInfo& Info = WeaponInfo::getInstance();
	if ((Info.weapAmmoTotalCount + Info.weapAmmoCurrentCount) - Info.weapAmmoCapacity < 0) {
		Info.weapAmmoToAdd = Info.weapAmmoTotalCount;
	}
}

//Set weapon capacity to needed amount to be sure reloadComplete fills needed amount of ammo
void SetWeapAmmoCapacity(int amount) {
	WeaponInfo& Info = WeaponInfo::getInstance();
	if (!Info.weapCurrentInstanceData) {
		logInfo("Weapon instance is nullptr. Could not set ammo.");
		return;
	}

	//This if statement is for when ammo complete of the animation goes over the original max ammo count. Will be edited later for +1 and +2 loading
	if (amount > Info.weapAmmoCapacity) {
		Info.weapCurrentInstanceData->ammoCapacity = Info.weapAmmoCapacity;
		logInfo("Ammo count set to: " + std::to_string(Info.weapAmmoCapacity));
	} else {
		Info.weapCurrentInstanceData->ammoCapacity = amount;
		logInfo("Ammo count set to: " + std::to_string(amount));
	}
}
