#pragma once
#include "Global.h"

struct WeaponInfo {
private:
	WeaponInfo(){};

public:
	WeaponInfo(WeaponInfo const&) = delete;
	void operator=(WeaponInfo const&) = delete;

	//static functions
	static void ClearWeaponInfo();
	static WeaponInfo& getInstance();

	//members
	const EquippedWeapon* weapEquip{ nullptr };
	const EquippedWeaponData* weapEquipData{ nullptr };
	const TESAmmo* weapAmmo{ nullptr };
	const TESObjectWEAP* weapForm{ nullptr };
	const BGSObjectInstanceT<TESObjectWEAP>* weapInstance{ nullptr };
	const TESObjectWEAP::InstanceData* weapInstanceData{ nullptr };

	TESObjectWEAP::InstanceData* weapCurrentInstanceData{ nullptr };

	int weapAmmoCapacity{ 0 };
	int weapAmmoCurrentCount{ 0 };
	int weapAmmoTotalCount{ 0 };
	int weapAmmoIncrementor{ 0 };
	int weapAmmoToAdd{ 0 };
};

WeaponInfo& FillWeaponInfo(WeaponInfo& initInfo);
