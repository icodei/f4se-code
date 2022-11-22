#include "Global.h"

bool isEmptyReload = false;
bool reloadStarted = false;
bool reloadEnd = true;
bool processCurrentWeap = false;
bool processCurrentScope = false;
bool ignore = false;
bool readyForRender = false;

int currentAmmoCount = 0;
int ammoCapacity = 0;
int totalAmmoCount = 0;
int incrementor = 0;
int toAdd = 0;

BSTEventDispatcher<void*>* GetGlobalEventDispatcher(BSTGlobalEvent* globalEvents, const char* dispatcherName) {
	for (int i = 0; i < globalEvents->eventSources.count; i++) {
		const char* name = GetObjectClassName(globalEvents->eventSources[i]) + 15;
		if (strstr(name, dispatcherName) == name) {
			return &globalEvents->eventSources[i]->eventDispatcher;
		}
	}
	return nullptr;
}

RelocPtr<float> minCurrentZoom(0x3805130);

typedef void(*_TogglePOV)(void*, ButtonEvent*);
RelocAddr<uintptr_t> TogglePOV_Target(0x2D49E48 + 0x40);
_TogglePOV TogglePOV_Original;
void TogglePOV_Hook(void* arg1, ButtonEvent* event) {
	TogglePOV_Original(arg1, event);
}

RelocAddr<uintptr_t> TogglePOV_FirstToThird_Target(0x2D84518 + 0x40);
_TogglePOV TogglePOV_FirstToThird_Original;
void TogglePOV_FirstToThird_Hook(void* arg1, ButtonEvent* event) {
	processCurrentScope = false;
	ScopeTextureLoader = nullptr;
	
	TogglePOV_FirstToThird_Original(arg1, event);
}

RelocAddr<uintptr_t> TogglePOV_ThirdToFirst_Target(0x2D07A38 + 0x40);
_TogglePOV TogglePOV_ThirdToFirst_Original;
void TogglePOV_ThirdToFirst_Hook(void* arg1, ButtonEvent* event) {
	static const BSFixedString TogglePOV("TogglePOV");
	static const BSFixedString ZoomIn("ZoomIn");

	TogglePOV_ThirdToFirst_Original(arg1, event);
}

typedef void(*_MovementHandler)(void*, ButtonEvent*);
RelocAddr<uintptr_t> MovementHandler_Target(0x2D49908 + 0x40);
_MovementHandler MovementHandler_Original;
void MovementHandler_Hook(void* arg1, ButtonEvent* event) {
	static const BSFixedString Forward("Forward");
	MovementHandler_Original(arg1, event);
}

typedef void(*_SprintHandler)(void*, ButtonEvent*);
RelocAddr<uintptr_t> SprintHandler_Target(0x2D499C8 + 0x40);
_SprintHandler SprintHandler_Original;
void SprintHandler_Hook(void* arg1, ButtonEvent* event) {
	SprintHandler_Original(arg1, event);
}

typedef void(*_ReadyWeaponHandler)(void*, ButtonEvent*);
RelocAddr<uintptr_t> ReadyWeaponHandler_Target(0x2D49B48 + 0x40);
_ReadyWeaponHandler ReadyWeaponHandler_Original;
void ReadyWeaponHandler_Hook(void* arg1, ButtonEvent* event) {
	if ((*g_player) && IsButtonPressed(event)) {
		logIfNeeded("Player Weapon Ready Event via button press");
	}
	logIfNeeded("Player Weapon Ready Event");
	ReadyWeaponHandler_Original(arg1, event);
}

typedef std::uint32_t(*_PlayerUseAmmoEvent_ReceiveEvent)(Actor*, const WeaponData&, std::uint32_t, std::uint32_t);
RelocAddr<uintptr_t> PlayerUseAmmoEvent_ReceiveEvent_Target(0x2D438E8 + 0x780);
_PlayerUseAmmoEvent_ReceiveEvent PlayerUseAmmoEvent_Original;
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

typedef EventResult(*_MenuOpenCloseEvent_ReceiveEvent)(void*, MenuOpenCloseEvent*, void*);
RelocAddr<uintptr_t> MenuOpenCloseEvent_ReceiveEvent_Target(0x2D49200 + 0x08);
_MenuOpenCloseEvent_ReceiveEvent MenuOpenCloseEvent_ReceiveEvent_Original;
EventResult MenuOpenCloseEvent_ReceiveEvent_Hook(void* arg1, MenuOpenCloseEvent* evn, void* dispatcher) {
	static const BSFixedString LoadingMenu("LoadingMenu");
	if (evn->menuName == LoadingMenu && evn->isOpen) {
		isEmptyReload = false;
		ignore = true;

		static auto pLoadGameHandler = new TESLoadGameHandler();
		GetEventDispatcher<TESLoadGameEvent>()->AddEventSink(pLoadGameHandler);
	}
	return MenuOpenCloseEvent_ReceiveEvent_Original(arg1, evn, dispatcher);
}

typedef EventResult(*_PlayerAnimGraphEvent_ReceiveEvent)(void*, BSAnimationGraphEvent*, void*);
RelocAddr<uintptr_t> PlayerAnimGraphEvent_ReceiveEvent_Target(0x2D442D8 + 0x8);
_PlayerAnimGraphEvent_ReceiveEvent PlayerAnimationEvent_Original;
EventResult PlayerAnimGraphEvent_ReceiveEvent_Hook(void* arg1, BSAnimationGraphEvent* evn, void* dispatcher) {
	static const BSFixedString WeaponFire("WeaponFire");
	static const BSFixedString ReloadEnd("ReloadEnd");
	static const BSFixedString ReloadComplete("ReloadComplete");
	static const BSFixedString Event00("Event00");
	static const BSFixedString reloadSequentialStart("reloadSequentialStart");
	static const BSFixedString reloadSequentialReserveStart("reloadSequentialReserveStart");
	static const BSFixedString sightedStateEnter("sightedStateEnter");
	static const BSFixedString sightedStateExit("sightedStateExit");
	static const BSFixedString weaponDraw("weaponDraw");
	static const BSFixedString weaponInstantDown("weaponInstantDown");

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
				} else {
					SetWeapAmmoCapacity(currentAmmoCount + 1);
					if (isEmptyReload) {
						reloadContinueFromEmpty();
					} else {
						reloadContinue();
					}
				}
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
	}
	if (evn->name == weaponInstantDown) {
		ignore = true;
	}
	if (currentWeapInstance && processCurrentScope) {
		if (evn->name == sightedStateEnter) {
			ignore = false;
			if (readyForRender && (ignore == false) && ScopeTextureLoader && scopePOV) {
				ScopeRendererManager::RenderHelper(true);
			}
			//(ThermalFXS)->StartEffectShader(ThermalFXS, ScopeTextureLoader, effectShaderData, true);
		} else if (evn->name == sightedStateExit) {
			ignore = true;
			//(ThermalFXS)->StopEffectShader(ThermalFXS, ScopeTextureLoader, effectShaderData);
		}
	}
	return PlayerAnimationEvent_Original(arg1, evn, dispatcher);
}

//adding too much to this hook causes the equip to stall and do weird things
//Bingle showed me how threading worked :) hopefully that should fix the issues with the above comment
EventResult TESEquipEventSink::ReceiveEvent(TESEquipEvent* evn, void* dispatcher) {
	if (evn->owner == *g_player && evn->isEquipping && ignore == false) {
		TESForm* form = LookupFormByID(evn->FormID);
		if (form && form->formType == kFormType_WEAP) {
			Actor::MiddleProcess::Data08::EquipData* equipData = GetEquipDataByEquipIndex(EquipIndex::kEquipIndex_Default);
			if (equipData) {
				TESObjectWEAP* weap = DYNAMIC_CAST(equipData->item, TESForm, TESObjectWEAP);;
				TESObjectWEAP::InstanceData* weapInst = GetWeaponInstanceData(equipData->item, equipData->instanceData);
				logIfNeeded(";======================================================================================;");
				logIfNeeded("Player TESEquipEvent: " + GetFullNameWEAP(weap));
				std::thread([weapInst]() { HanldeWeaponEquip(weapInst); }).detach();
				//HanldeWeaponEquip(weapInst);
				return kEvent_Continue;
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
	bool isDrawing;
	if (evn->state == WEAPON_STATE::kDrawing) {
		logIfNeeded("Weapon is being equiped.");
		isDrawing = true;
	}
	if (evn->state == WEAPON_STATE::kDrawn && isDrawing) {
		//HanldeWeaponEquipAfter3D();
		ignore = false;
		logIfNeeded("Weapon has finished being equiped.");
		isDrawing = false;
	}
	if (evn->state == WEAPON_STATE::kSheathing || evn->state == WEAPON_STATE::kSheathed) {
		isDrawing = false;
		ignore = true;
	}
	return kEvent_Continue;
}
PlayerSetWeaponStateEventSink playerSetWeaponStateEventSink;

EventResult TESLoadGameHandler::ReceiveEvent(TESLoadGameEvent* evn, void* dispatcher)	{
	RegisterAfterLoadEvents();
	return kEvent_Continue;
}

EventResult BGSOnPlayerUseWorkBenchEventSink::ReceiveEvent(BGSOnPlayerUseWorkBenchEvent* evn, void* dispatcher) {
	ignore = true;
	return kEvent_Continue;
}

//TODO: check what furniture the player is getting into. Might be able to ignore power armor frame
EventResult TESFurnitureEventSink::ReceiveEvent(TESFurnitureEvent* evn, void* dispatcher) {
	if (evn->actor == (*g_player)) {
		if (evn->isGettingUp == true) {
			logIfNeeded("Player is leaving the workbench. We may resume our work.");
			ignore = false;
		} else {
			logIfNeeded("Player is entering a workbench. We need to ignore certain events during this time.");
			ignore = true;
		}
	}
	return kEvent_Continue;
}

typedef void(*_PlayerUpdate)(void*, float);
RelocAddr<uintptr_t> PlayerUpdate_Target(0x02D43F60); //PlayerCharacter vtbl
_PlayerUpdate PlayerUpdate_Original;
void PlayerUpdate_Hook(void* player, float a1) {
	if (processCurrentScope && readyForRender && (ignore == false) && ScopeTextureLoader && scopePOV) {
		//ScopeRendererManager::RenderHelper(true);
	}
	return PlayerUpdate_Original(player, a1);
}

//IDK how to hook this function :( I will use the player update hook above
//Hook DrawWorld
//typedef void(*_DrawWorld_And_UI)(void*, bool);
//RelocAddr<_DrawWorld_And_UI> DrawWorld_And_UI_Original(0x00D3CBE0);

//Hook DrawWorld Func
//void DrawWorld_And_UI_Hook(void* main, bool a1) {
//	//if (processCurrentScope && scopeRenderer) {
//	//	nsScope_Render();
//	//}
//	if (processCurrentScope && ScopeTextureLoader && readyForRender) {
//		ScopeRendererManager::RenderHelper(1);
//	}
//	return DrawWorld_And_UI_Original(main, a1);
//}

bool Install() { //Called at GameLoaded
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

	//ReadyWeaponHandler_Original = *(_ReadyWeaponHandler*)(ReadyWeaponHandler_Target.GetUIntPtr());
	//SafeWrite64(ReadyWeaponHandler_Target.GetUIntPtr(), (uintptr_t)ReadyWeaponHandler_Hook);

	//g_branchTrampoline.Write6Branch(DrawWorld_And_UI_Original.GetUIntPtr(), (uintptr_t)DrawWorld_And_UI_Hook);
	//g_branchTrampoline.Write5Call(DrawWorld_And_UI_Original.GetUIntPtr(), (uintptr_t)DrawWorld_And_UI_Hook);
	
	PlayerUpdate_Original = *(_PlayerUpdate*)(PlayerUpdate_Target.GetUIntPtr());
	SafeWrite64(PlayerUpdate_Target, (uintptr_t)PlayerUpdate_Hook);

	PlayerAnimationEvent_Original = *(_PlayerAnimGraphEvent_ReceiveEvent*)(PlayerAnimGraphEvent_ReceiveEvent_Target.GetUIntPtr());
	SafeWrite64(PlayerAnimGraphEvent_ReceiveEvent_Target, (uintptr_t)PlayerAnimGraphEvent_ReceiveEvent_Hook);

	MenuOpenCloseEvent_ReceiveEvent_Original = *(_MenuOpenCloseEvent_ReceiveEvent*)(MenuOpenCloseEvent_ReceiveEvent_Target.GetUIntPtr());
	SafeWrite64(MenuOpenCloseEvent_ReceiveEvent_Target.GetUIntPtr(), (uintptr_t)MenuOpenCloseEvent_ReceiveEvent_Hook);

	GetEventDispatcher<TESEquipEvent>()->AddEventSink(new TESEquipEventSink());
	GetEventDispatcher<BGSOnPlayerUseWorkBenchEvent>()->AddEventSink(new BGSOnPlayerUseWorkBenchEventSink());
	GetEventDispatcher<TESFurnitureEvent>()->AddEventSink(new TESFurnitureEventSink());
	log("Hooks Install Complete");
	return true;
}

bool RegisterAfterLoadEvents() { //Called at LoadingMenu, mostly for global events
	auto PlayerAmmoCountEventDispatcher = GET_EVENT_DISPATCHER(PlayerAmmoCountEvent);
	if (PlayerAmmoCountEventDispatcher) {
		PlayerAmmoCountEventDispatcher->AddEventSink(&playerAmmoCountEventSink);
	} else {
		log("Unable to register PlayerAmmoCountEvent.");
		return false;
	}

	auto PlayerSetWeaponStateEventDispatcher = GET_EVENT_DISPATCHER(PlayerSetWeaponStateEvent);
	if (PlayerSetWeaponStateEventDispatcher) {
		PlayerSetWeaponStateEventDispatcher->AddEventSink(&playerSetWeaponStateEventSink);
	} else {
		log("Unable to register PlayerSetWeaponStateEvent.");
		return false;
	}

	//auto PlayerWeaponReloadEventDispatcher = GET_EVENT_DISPATCHER(PlayerWeaponReloadEvent);
	//if (PlayerWeaponReloadEventDispatcher) {
	//	PlayerWeaponReloadEventDispatcher->AddEventSink(&playerWeaponReloadEventSink);
	//} else {
	//	log("Unable to register PlayerWeaponReloadEvent.");
	//	return false;
	//}

	if (!scopePOV || !scopePOVRoot || !pScopeManagerCullingProc || !pScopeManagerAccumulator || !pScopeManagerShaderParam) {
		ScopeRendererManager::Setup();
	}

	//if (!scopeRenderer) {
	//	//nsScope_CreateRenderer(); //CTD during creation. For some reason the ctor of ScopeCamera is called twice and crashes at the second called ctor
	//}

	return true;
}


