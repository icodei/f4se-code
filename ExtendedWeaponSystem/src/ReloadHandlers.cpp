#include "ReloadHandlers.h"

void DoSpeedReload(int32_t id) {
	logInfo("Speed Reload");
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
	PlayerCharacter::GetSingleton()->SetGraphVariableBool(bReloadLoop, false);
}

void reloadContinue() {
	const BSFixedString bReloadLoop("bReloadLoop");
	const BSFixedString reloadSequentialReserveStart("reloadSequentialReserveStart");

	logInfo("Continuing reload loop");
	PlayerCharacter::GetSingleton()->SetGraphVariableBool(bReloadLoop, true);
	PlayerCharacter::GetSingleton()->NotifyAnimationGraphImpl(reloadSequentialReserveStart);
}

void reloadContinueFromEmpty() {
	const BSFixedString bReloadLoop("bReloadLoop");
	const BSFixedString reloadSequentialStart("reloadSequentialStart");

	logInfo("Continuing reload loop");
	PlayerCharacter::GetSingleton()->SetGraphVariableBool(bReloadLoop, true);
	PlayerCharacter::GetSingleton()->NotifyAnimationGraphImpl(reloadSequentialStart);
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
