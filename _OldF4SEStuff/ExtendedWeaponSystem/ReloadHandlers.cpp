#include "Global.h"

void reloadStop() {
	logIfNeeded("Stopping reload loop");
	reloadEndHandle();
	(*g_player)->animGraphHolder.SetGraphVariableBool(BSFixedString("bReloadLoop"), false);
}

void reloadContinue() {
	logIfNeeded("Continuing reload loop");
	(*g_player)->animGraphHolder.SetGraphVariableBool(BSFixedString("bReloadLoop"), true);
	(*g_player)->animGraphHolder.NotifyAnimationGraphImpl(BSFixedString("reloadSequentialReserveStart"));
}

void reloadContinueFromEmpty() {
	logIfNeeded("Continuing reload loop");
	(*g_player)->animGraphHolder.SetGraphVariableBool(BSFixedString("bReloadLoop"), true);
	(*g_player)->animGraphHolder.NotifyAnimationGraphImpl(BSFixedString("reloadSequentialStart"));
}

//ready needed stuff when reload is started
void reloadStartHandle() {
	logIfNeeded("reloadStartHandle");
	incrementor = 0;
	toAdd = ammoCapacity - currentAmmoCount;
	reloadStarted = true;
	reloadEnd = false;
	SetWeapAmmoCapacity(currentAmmoCount);
}

//clear needed stuff when reload ends
void reloadEndHandle() {
	logIfNeeded("reloadEndHandle");
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
		log("Weapon instance is nullptr. Could not set ammo.");
		return;
	}

	if (amount > ammoCapacity) { //This if statement is for when ammo complete of the animation goes over the original max ammo count. Will be edited later for +1 and +2 loading
		currentWeapInstance->ammoCapacity = ammoCapacity;
		logIfNeeded("Ammo count set to: " + std::to_string(ammoCapacity));
	} else {
		currentWeapInstance->ammoCapacity = amount;
		logIfNeeded("Ammo count set to: " + std::to_string(amount));
	}
}