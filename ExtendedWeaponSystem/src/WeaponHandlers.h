#pragma once
#include "Global.h"

struct WeaponInfo {
public:
	WeaponInfo() = default;
	~WeaponInfo() = default;

	WeaponInfo& operator=(const WeaponInfo& rhs);

	//functions
	bool IsFilled() { return (weapEquip && weapEquipData && weapAmmo && weapForm && weapInstance && weapInstanceData); }
	bool IsCriticalFilled() { return (weapEquip || weapInstanceData); }
	bool IsBothCriticalFilled() { return (weapEquip && weapInstanceData); }

	//static functions
	static void ClearWeaponInfo();

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

namespace Info {
	extern WeaponInfo weapInfo;
	extern TESObjectWEAP::InstanceData* weapCurrentInstanceData;
}


WeaponInfo& FillWeaponInfo(WeaponInfo& initInfo);
void HanldeWeaponEquip(WeaponInfo& initInfo);
void HanldeWeaponEquipAfter3D(WeaponInfo& initInfo);
void HandleWeaponOnLoadGame(WeaponInfo& initInfo);

void HandleWeaponChange();
void HandleWeaponInstantDown();
void HandleWeaponSightsEnter();
void HandleWeaponSightsExit();

void QueryReload();
void QueryScope();
void QueueHandlingOfWeapon(WeaponInfo& initInfo);

bool WeaponHasSequentialReload();
bool WeaponHasNightVisionScope();
bool WeaponHasPIPScope();
bool WeaponHasThermalScope();
bool WeaponHasSpecialScope();
bool WeaponHasNoSpecialScopes();
