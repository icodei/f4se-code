#pragma once
#include "Global.h"

struct WeaponInfo {
public:
	WeaponInfo() = default;

	WeaponInfo& operator=(const WeaponInfo& rhs);

	//functions
	bool IsFilled() { return (weapEquip && weapEquipData && weapAmmo && weapForm && weapInstance && weapInstanceData); }
	bool IsCriticalFilled() { return (weapEquip || weapInstanceData); }
	bool IsBothCriticalFilled() { return (weapEquip && weapInstanceData); }

	//static functions
	static void ClearWeaponInfo();
	static void InitSDM();
	
	//static members
	static WeaponInfo weapInfo;
	static TESObjectWEAP::InstanceData* weapCurrentInstanceData;

	//members
	const EquippedWeapon* weapEquip{ nullptr };
	const EquippedWeaponData* weapEquipData{ nullptr };
	const TESAmmo* weapAmmo{ nullptr };
	const TESObjectWEAP* weapForm{ nullptr };
	const BGSObjectInstanceT<TESObjectWEAP>* weapInstance{ nullptr };
	const TESObjectWEAP::InstanceData* weapInstanceData{ nullptr };

	int weapAmmoCapacity{ 0 };
	int weapAmmoCurrentCount{ 0 };
	int weapAmmoIncrementor{ 0 };
	int weapAmmoToAdd{ 0 };
	int weapAmmoTotalCount{ 0 };
};


WeaponInfo& FillWeaponInfo(WeaponInfo& initInfo);
void HanldeWeaponEquip(WeaponInfo& initInfo);
void HanldeWeaponEquipAfter3D(WeaponInfo& initInfo);
void HandleWeaponOnLoadGame(WeaponInfo& initInfo);
void QueueHandlingOfWeapon(WeaponInfo& initInfo);

void HandleWeaponInstantDown();
void HandleWeaponSightsEnter();
void HandleWeaponSightsExit();
