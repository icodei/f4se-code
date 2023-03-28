#include "ReloadHandlers.h"

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
	WeaponInfo::weapInfo.weapAmmoIncrementor = 0;
	WeaponInfo::weapInfo.weapAmmoToAdd = WeaponInfo::weapInfo.weapAmmoCapacity - WeaponInfo::weapInfo.weapAmmoCurrentCount;
	reloadHasStarted = true;
	reloadHasEnded = false;
	SetWeapAmmoCapacity(WeaponInfo::weapInfo.weapAmmoCurrentCount);
}

//clear needed stuff when reload ends
void reloadEndHandle() {
	logInfo("reloadEndHandle");
	reloadHasEnded = true;
	reloadHasStarted = false;
	WeaponInfo::weapInfo.weapAmmoIncrementor = 0;
	WeaponInfo::weapInfo.weapAmmoToAdd = 0;
	SetWeapAmmoCapacity(WeaponInfo::weapInfo.weapAmmoCapacity);
}

//Stops the reload early if there is not enough ammo in the inventory
void StopLesserAmmo() {
	if ((WeaponInfo::weapInfo.weapAmmoTotalCount + WeaponInfo::weapInfo.weapAmmoCurrentCount) - WeaponInfo::weapInfo.weapAmmoCapacity < 0) {
		WeaponInfo::weapInfo.weapAmmoToAdd = WeaponInfo::weapInfo.weapAmmoTotalCount;
	}
}

//Set weapon capacity to needed amount to be sure reloadComplete fills needed amount of ammo
void SetWeapAmmoCapacity(int amount) {
	if (!WeaponInfo::weapCurrentInstanceData) {
		logInfo("Weapon instance is nullptr. Could not set ammo.");
		return;
	}

	//This if statement is for when ammo complete of the animation goes over the original max ammo count. Will be edited later for +1 and +2 loading
	if (amount > WeaponInfo::weapInfo.weapAmmoCapacity) {
		WeaponInfo::weapCurrentInstanceData->ammoCapacity = WeaponInfo::weapInfo.weapAmmoCapacity;
		logInfo("Ammo count set to: " + std::to_string(WeaponInfo::weapInfo.weapAmmoCapacity));
	} else {
		WeaponInfo::weapCurrentInstanceData->ammoCapacity = amount;
		logInfo("Ammo count set to: " + std::to_string(amount));
	}
}
