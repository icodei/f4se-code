#include "ReloadHandlers.h"

void reloadStop() {
	logInfoConditional("Stopping reload loop");
	reloadEndHandle();
	(pc)->SetGraphVariableBool(BSFixedString("bReloadLoop"), false);
}

void reloadContinue() {
	logInfoConditional("Continuing reload loop");
	(pc)->SetGraphVariableBool(BSFixedString("bReloadLoop"), true);
	(pc)->NotifyAnimationGraphImpl(BSFixedString("reloadSequentialReserveStart"));
}

void reloadContinueFromEmpty() {
	logInfoConditional("Continuing reload loop");
	(pc)->SetGraphVariableBool(BSFixedString("bReloadLoop"), true);
	(pc)->NotifyAnimationGraphImpl(BSFixedString("reloadSequentialStart"));
}

//ready needed stuff when reload is started
void reloadStartHandle() {
	logInfoConditional("reloadStartHandle");
	incrementor = 0;
	toAdd = ammoCapacity - currentAmmoCount;
	reloadStarted = true;
	reloadEnd = false;
	SetWeapAmmoCapacity(currentAmmoCount);
}

//clear needed stuff when reload ends
void reloadEndHandle() {
	logInfoConditional("reloadEndHandle");
	reloadEnd = true;
	reloadStarted = false;
	incrementor = 0;
	toAdd = 0;
	SetWeapAmmoCapacity(ammoCapacity);
}

//Stops the reload early if there is not enough ammo in the inventory
void StopLesserAmmo() {
	if ((totalAmmoCount + currentAmmoCount) - ammoCapacity < 0) {
		toAdd = totalAmmoCount;
	}
}

//Set weapon capacity to needed amount to be sure reloadComplete fills needed amount of ammo
void SetWeapAmmoCapacity(int amount) {
	if (!currentWeapInstance) {
		logInfo("Weapon instance is nullptr. Could not set ammo.");
		return;
	}

	if (amount > ammoCapacity) { //This if statement is for when ammo complete of the animation goes over the original max ammo count. Will be edited later for +1 and +2 loading
		currentWeapInstance->ammoCapacity = ammoCapacity;
		logInfoConditional("Ammo count set to: " + std::to_string(ammoCapacity));
	} else {
		currentWeapInstance->ammoCapacity = amount;
		logInfoConditional("Ammo count set to: " + std::to_string(amount));
	}
}
