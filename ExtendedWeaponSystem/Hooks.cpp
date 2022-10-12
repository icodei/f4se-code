#include "Global.h"

bool isEmptyReload = false;
bool reloadStarted = false;
bool reloadEnd = true;
bool processCurrentWeap = false;
bool processCurrentScope = false;
bool playerIsInWorkbench = false;

int currentAmmoCount = 0;
int ammoCapacity = 0;
int totalAmmoCount = 0;
int incrementor = 0;
int toAdd = 0;

RelocPtr<float> minCurrentZoom(0x3805130);

RelocAddr<uintptr_t> TogglePOV_Target(0x2D49E48 + 0x40);
RelocAddr<uintptr_t> TogglePOV_FirstToThird_Target(0x2D84518 + 0x40);
RelocAddr<uintptr_t> TogglePOV_ThirdToFirst_Target(0x2D07A38 + 0x40);
_TogglePOV TogglePOV_Original;
_TogglePOV TogglePOV_FirstToThird_Original;
_TogglePOV TogglePOV_ThirdToFirst_Original;

RelocAddr<uintptr_t> MovementHandler_Target(0x2D49908 + 0x40);
_MovementHandler MovementHandler_Original;

RelocAddr<uintptr_t> SprintHandler_Target(0x2D499C8 + 0x40);
_SprintHandler SprintHandler_Original;

RelocAddr<uintptr_t> ReadyWeaponHandler_Target(0x2D49B48 + 0x40);
_ReadyWeaponHandler ReadyWeaponHandler_Original;

RelocAddr<uintptr_t> PlayerAnimGraphEvent_ReceiveEvent_Target(0x2D442D8 + 0x8);
_PlayerAnimGraphEvent_ReceiveEvent PlayerAnimationEvent_Original;

RelocAddr<uintptr_t> PlayerUseAmmoEvent_ReceiveEvent_Target(0x2D438E8 + 0x780);
_PlayerUseAmmoEvent_ReceiveEvent PlayerUseAmmoEvent_Original;

RelocAddr<uintptr_t> MenuOpenCloseEvent_ReceiveEvent_Target(0x2D49200 + 0x08);
_MenuOpenCloseEvent_ReceiveEvent MenuOpenCloseEvent_ReceiveEvent_Original;

BSTEventDispatcher<void*>* GetGlobalEventDispatcher(BSTGlobalEvent* globalEvents, const char* dispatcherName) {
	for (int i = 0; i < globalEvents->eventSources.count; i++) {
		const char* name = GetObjectClassName(globalEvents->eventSources[i]) + 15;    // ?$EventSource@V
		if (strstr(name, dispatcherName) == name) {
			return &globalEvents->eventSources[i]->eventDispatcher;
		}
	}
	return nullptr;
}


void TogglePOV_Hook(void* arg1, ButtonEvent* event) {
	TogglePOV_Original(arg1, event);
}

void TogglePOV_FirstToThird_Hook(void* arg1, ButtonEvent* event) {
	processCurrentScope = false;
	ScopeTextureLoader = nullptr;
	
	TogglePOV_FirstToThird_Original(arg1, event);
}

void TogglePOV_ThirdToFirst_Hook(void* arg1, ButtonEvent* event) {
	static BSFixedString TogglePOV("TogglePOV");
	static BSFixedString ZoomIn("ZoomIn");

	TogglePOV_ThirdToFirst_Original(arg1, event);
}

void MovementHandler_Hook(void* arg1, ButtonEvent* event) {
	static BSFixedString Forward("Forward");
	MovementHandler_Original(arg1, event);
}

void SprintHandler_Hook(void* arg1, ButtonEvent* event) {
	SprintHandler_Original(arg1, event);
}

void ReadyWeaponHandler_Hook(void* arg1, ButtonEvent* event) {
	if ((*g_player) && IsButtonPressed(event)) {
		logIfNeeded("Player Weapon Ready Event via button press");
	}
	logIfNeeded("Player Weapon Ready Event");
	ReadyWeaponHandler_Original(arg1, event);
}

std::uint32_t PlayerUseAmmoEvent_ReceiveEvent_Hook(Actor* actor, const WeaponData& a_weapon, std::uint32_t a_equipIndex, std::uint32_t a_shotCount) {
	if (processCurrentWeap) {
		if (actor == *g_player) {
			Actor::MiddleProcess::Data08::EquipData* equipData = GetEquipDataByEquipIndex(EquipIndex::kEquipIndex_Default);
			TESObjectWEAP::InstanceData* weapInst = GetWeaponInstanceData(a_weapon.item, a_weapon.instanceData);
			if (weapInst && weapInst != currentWeapInstance) {
				currentWeapInstance = weapInst;
				ammoCapacity = currentWeapInstance->ammoCapacity;
			}
			currentAmmoCount = equipData->equippedData->unk18;
			totalAmmoCount = GetInventoryItemCount(actor, weapInst->ammo);
			logIfNeeded("ammo count: " + std::to_string(currentAmmoCount));
		}
	}
	return PlayerUseAmmoEvent_Original(actor, a_weapon, a_equipIndex, a_shotCount);
}

EventResult PlayerAnimGraphEvent_ReceiveEvent_Hook(void* arg1, BSAnimationGraphEvent* evn, void* dispatcher) {
	static BSFixedString WeaponFire("WeaponFire");
	static BSFixedString ReloadEnd("ReloadEnd");
	static BSFixedString ReloadComplete("ReloadComplete");
	static BSFixedString Event00("Event00");
	static BSFixedString reloadSequentialStart("reloadSequentialStart");
	static BSFixedString reloadSequentialReserveStart("reloadSequentialReserveStart");
	static BSFixedString sightedStateEnter("sightedStateEnter");
	static BSFixedString sightedStateExit("sightedStateExit");
	static BSFixedString weaponDraw("weaponDraw");

	if (currentWeapInstance && processCurrentWeap)	{
		if (!reloadStarted && reloadEnd) {
			if (evn->name == Event00) {
				reloadStartHandle();
				StopLesserAmmo();
				isEmptyReload = currentAmmoCount == 0 ? true : false;
			}
		}
		if (reloadStarted && !reloadEnd) {
			if (evn->name == ReloadEnd) {
				logIfNeeded("ReloadEnd");
				reloadStop();
			}
			if (evn->name == ReloadComplete) {
				logIfNeeded("reloadComplete");
				if ((ammoCapacity - 1) == currentAmmoCount) {
					reloadStop();
				}
				else {
					SetWeapAmmoCapacity(currentAmmoCount + 1);
					if (isEmptyReload) {
						reloadContinueFromEmpty();
					}
					else {
						reloadContinue();
					}
				}
				//if (toAdd != ammoCapacity && reloadStarted && !reloadEnd) {
				//	incrementor++;
				//	logIfNeeded("incrementor++");
				//	SetWeapAmmoCapacity(currentAmmoCount + 1);
				//	if (incrementor >= toAdd) {
				//		logIfNeeded("incrementor >= toAdd. Reload Stop");
				//		reloadStop();
				//	}
				//}
			}
		}
		//Manually handle relaod end for various situations
		if (reloadStarted && !reloadEnd && !_strcmpi("pipboyOpened", evn->name.c_str())) {
			reloadStop();
			logIfNeeded("pipboy opened");
		}
		if (reloadStarted && !reloadEnd && !_strcmpi("weaponSwing", evn->name.c_str())) {
			reloadStop();
			logIfNeeded("weapon swing");
		}
		if (reloadStarted && !reloadEnd && !_strcmpi("throwEnd", evn->name.c_str())) {
			reloadStop();
			logIfNeeded("throw end");
		}
	}
	if (evn->name == weaponDraw) {
		HanldeWeaponEquipAfter3D();
		return PlayerAnimationEvent_Original(arg1, evn, dispatcher);
	}
	if (currentWeapInstance && processCurrentScope) {
		if (evn->name == sightedStateEnter) {
			(ThermalFXS)->StartEffectShader(ThermalFXS, ScopeTextureLoader, effectShaderData, true);
			return PlayerAnimationEvent_Original(arg1, evn, dispatcher);
		}
		else if (evn->name == sightedStateExit) {
			(ThermalFXS)->StopEffectShader(ThermalFXS, ScopeTextureLoader, effectShaderData);
			return PlayerAnimationEvent_Original(arg1, evn, dispatcher);
		}
	}
	return PlayerAnimationEvent_Original(arg1, evn, dispatcher);
}

EventResult TESEquipEventSink::ReceiveEvent(TESEquipEvent* evn, void* dispatcher) {
	if (evn->owner == *g_player && evn->isEquipping) {
		TESForm* form = LookupFormByID(evn->FormID);
		if (form && form->formType == kFormType_WEAP) {
			if (playerIsInWorkbench == false) {
				Actor::MiddleProcess::Data08::EquipData* equipData = GetEquipDataByEquipIndex(EquipIndex::kEquipIndex_Default);
				if (equipData) {
					TESObjectWEAP* weap = DYNAMIC_CAST(equipData->item, TESForm, TESObjectWEAP);;
					TESObjectWEAP::InstanceData* weapInst = GetWeaponInstanceData(equipData->item, equipData->instanceData);
					logIfNeeded("Player TESEquipEvent: " + GetFullNameWEAP(weap));
					HanldeWeaponEquip(weapInst);
				}
			}
			else {
				logIfNeeded("Player EquipEvent recieved but the player is curently in a workbench. We will ignore this equip.");
			}
			
		}
	}
	return kEvent_Continue;
}

EventResult PlayerAmmoCountEventSink::ReceiveEvent(PlayerAmmoCountEvent* evn, void* dispatcher) {
	if (processCurrentWeap) {
		if (evn->weapon || evn->weaponInstance || evn->unk08 == 1) {
			if (evn->unk08 == 1 && evn->weapon && evn->weaponInstance && evn->weaponInstance != currentWeapInstance) {
				currentWeapInstance = evn->weaponInstance;
				ammoCapacity = currentWeapInstance->ammoCapacity;
			}
			currentAmmoCount = evn->ammoCount;
			totalAmmoCount = evn->totalAmmoCount;
			logIfNeeded("ammo count: " + std::to_string(currentAmmoCount));
		}
	}
	return kEvent_Continue;
}
PlayerAmmoCountEventSink playerAmmoCountEventSink;

EventResult PlayerWeaponReloadEventSink::ReceiveEvent(PlayerWeaponReloadEvent* evn, void* dispatcher) {
	//logIfNeeded("PlayerWeaponReloadEvent");
	return kEvent_Continue;
}
PlayerWeaponReloadEventSink playerWeaponReloadEventSink;

EventResult PlayerSetWeaponStateEventSink::ReceiveEvent(PlayerSetWeaponStateEvent* evn, void* dispatcher) {
	return kEvent_Continue;
}
PlayerSetWeaponStateEventSink playerSetWeaponStateEventSink;

EventResult TESLoadGameHandler::ReceiveEvent(TESLoadGameEvent* evn, void* dispatcher)	{
	RegisterAfterLoadEvents();
	if (oncePerSession == false) {
		if (!RegisterAfterLoadEvents()) {
			logIfNeeded("unable to register for events on game load");
		}
		oncePerSession = true;
	}
	return kEvent_Continue;
}

EventResult MenuOpenCloseEvent_ReceiveEvent_Hook(void* arg1, MenuOpenCloseEvent* evn, void* dispatcher) {
	static BSFixedString LoadingMenu("LoadingMenu");
	if (evn->menuName == LoadingMenu && evn->isOpen) {
		isEmptyReload = false;

		static auto pLoadGameHandler = new TESLoadGameHandler();
		GetEventDispatcher<TESLoadGameEvent>()->AddEventSink(pLoadGameHandler);
	}
	return MenuOpenCloseEvent_ReceiveEvent_Original(arg1, evn, dispatcher);
}

EventResult BGSOnPlayerUseWorkBenchEventSink::ReceiveEvent(BGSOnPlayerUseWorkBenchEvent* evn, void* dispatcher) {
	processCurrentWeap = false;
	processCurrentScope = false;
	playerIsInWorkbench = true;
	//logIfNeeded("Player used a workbench.");
	return kEvent_Continue;
}

EventResult TESFurnitureEventSink::ReceiveEvent(TESFurnitureEvent* evn, void* dispatcher) {
	if (evn->actor == (*g_player)) {
		if (evn->isGettingUp == true) {
			logIfNeeded("Player is leaving the workbench. We may resume our work.");
			playerIsInWorkbench = false;
		}
		else {
			logIfNeeded("Player is entering a workbench. We need to ignore certain events during this time.");
			playerIsInWorkbench = true;
			processCurrentWeap = false;
			processCurrentScope = false;
		}
	}
	return kEvent_Continue;
}

bool Install() { //Called at GameLoaded
	bool toReturn = true;
	log("Hooks Install");

	//TogglePOV_Original = *(_TogglePOV*)(TogglePOV_Target.GetUIntPtr());
	//SafeWrite64(TogglePOV_Target.GetUIntPtr(), (uintptr_t)TogglePOV_Hook);

	//TogglePOV_FirstToThird_Original = *(_TogglePOV*)(TogglePOV_FirstToThird_Target.GetUIntPtr());
	//SafeWrite64(TogglePOV_FirstToThird_Target.GetUIntPtr(), (uintptr_t)TogglePOV_FirstToThird_Hook);

	//TogglePOV_ThirdToFirst_Original = *(_TogglePOV*)(TogglePOV_ThirdToFirst_Target.GetUIntPtr());
	//SafeWrite64(TogglePOV_ThirdToFirst_Target.GetUIntPtr(), (uintptr_t)TogglePOV_ThirdToFirst_Hook);

	//MovementHandler_Original = *(_MovementHandler*)(MovementHandler_Target.GetUIntPtr());
	//SafeWrite64(MovementHandler_Target.GetUIntPtr(), (uintptr_t)MovementHandler_Hook);

	//SprintHandler_Original = *(_SprintHandler*)(SprintHandler_Target.GetUIntPtr());
	//SafeWrite64(SprintHandler_Target.GetUIntPtr(), (uintptr_t)SprintHandler_Hook);

	//PlayerUseAmmoEvent_Original = *(_PlayerUseAmmoEvent_ReceiveEvent*)(PlayerUseAmmoEvent_ReceiveEvent_Target.GetUIntPtr());
	//SafeWrite64(PlayerUseAmmoEvent_ReceiveEvent_Target, (uintptr_t)PlayerUseAmmoEvent_ReceiveEvent_Hook);

	ReadyWeaponHandler_Original = *(_ReadyWeaponHandler*)(ReadyWeaponHandler_Target.GetUIntPtr());
	SafeWrite64(ReadyWeaponHandler_Target.GetUIntPtr(), (uintptr_t)ReadyWeaponHandler_Hook);

	PlayerAnimationEvent_Original = *(_PlayerAnimGraphEvent_ReceiveEvent*)(PlayerAnimGraphEvent_ReceiveEvent_Target.GetUIntPtr());
	SafeWrite64(PlayerAnimGraphEvent_ReceiveEvent_Target, (uintptr_t)PlayerAnimGraphEvent_ReceiveEvent_Hook);

	MenuOpenCloseEvent_ReceiveEvent_Original = *(_MenuOpenCloseEvent_ReceiveEvent*)(MenuOpenCloseEvent_ReceiveEvent_Target.GetUIntPtr());
	SafeWrite64(MenuOpenCloseEvent_ReceiveEvent_Target.GetUIntPtr(), (uintptr_t)MenuOpenCloseEvent_ReceiveEvent_Hook);

	GetEventDispatcher<TESEquipEvent>()->AddEventSink(new TESEquipEventSink());
	GetEventDispatcher<BGSOnPlayerUseWorkBenchEvent>()->AddEventSink(new BGSOnPlayerUseWorkBenchEventSink());
	GetEventDispatcher<TESFurnitureEvent>()->AddEventSink(new TESFurnitureEventSink());
	return toReturn;
}

bool RegisterAfterLoadEvents() { //Called at LoadingMenu, mostly for global events
	auto PlayerAmmoCountEventDispatcher = GET_EVENT_DISPATCHER(PlayerAmmoCountEvent);
	if (PlayerAmmoCountEventDispatcher) {
		PlayerAmmoCountEventDispatcher->AddEventSink(&playerAmmoCountEventSink);
	}
	else {
		log("Unable to register PlayerAmmoCountEvent.");
		return false;
	}

	auto PlayerWeaponReloadEventDispatcher = GET_EVENT_DISPATCHER(PlayerWeaponReloadEvent);
	if (PlayerWeaponReloadEventDispatcher) {
		PlayerWeaponReloadEventDispatcher->AddEventSink(&playerWeaponReloadEventSink);
	}
	else {
		log("Unable to register PlayerWeaponReloadEvent.");
		return false;
	}
	return true;
}


