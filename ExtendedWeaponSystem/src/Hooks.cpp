#include "Hooks.h"

BSEventNotifyControl BGSOnPlayerUseWorkBenchEventSink::ProcessEvent(const BGSOnPlayerUseWorkBenchEvent& a_event, BSTEventSource<BGSOnPlayerUseWorkBenchEvent>* a_source) {
	ignoreEquip = true;
	return BSEventNotifyControl::kContinue;
}

BSEventNotifyControl MenuOpenCloseEventSink::ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_source) {
	const BSFixedString LoadingMenu("LoadingMenu");

	if (a_event.menuName == LoadingMenu && a_event.opening) {
		logInfo("Loading...");
		gameLoading = true;
		ignoreEquip = true;
		ignoreScope = true;
	}
	if (a_event.menuName == LoadingMenu && !a_event.opening) {
		logInfo("Loading Complete");
		ignoreEquip = false;
		if (gameLoadingSave) {
			HandleWeaponOnLoadGame(FillWeaponInfo(WeaponInfo::weapInfo));
			gameLoadingSave = false;
		}
	}
	return BSEventNotifyControl::kContinue;
}

BSEventNotifyControl PlayerAmmoCountEventSink::ProcessEvent(const PlayerAmmoCountEvent& a_event, BSTEventSource<PlayerAmmoCountEvent>* a_source) {
	if (weaponHasSequentialReload == false) {
		return BSEventNotifyControl::kContinue;
	}
	if (!a_event.weapon) {
		return BSEventNotifyControl::kContinue;
	}
	if (!a_event.weaponInstance) {
		return BSEventNotifyControl::kContinue;
	}
	if (a_event.weaponInstance != WeaponInfo::weapCurrentInstanceData) {
		WeaponInfo::weapCurrentInstanceData = a_event.weaponInstance;
		WeaponInfo::weapInfo.weapAmmoCapacity = WeaponInfo::weapCurrentInstanceData->ammoCapacity;
	}

	//logInfo("PlayerAmmoCountEvent Dump");
	//Dump(const_cast<PlayerAmmoCountEvent*>(&a_event), 0x30);

	WeaponInfo::weapInfo.weapAmmoCurrentCount = a_event.optionalValue.value().clipAmmo;
	WeaponInfo::weapInfo.weapAmmoTotalCount = a_event.optionalValue.value().reserveAmmo;
	logInfo("ammo count: " + std::to_string(WeaponInfo::weapInfo.weapAmmoCurrentCount));
	return BSEventNotifyControl::kContinue;
}

BSTEventSource<PlayerAmmoCountEvent>* PlayerAmmoCountEventSink::GetEventSource() {
	return GET_EVENT_SOURCE(PlayerAmmoCountEvent);
}

#pragma region PlayerAnimGraphEventSink
BSEventNotifyControl PlayerAnimGraphEventSink::HookedProcessEvent(const BSAnimationGraphEvent& a_event, BSTEventSource<BSAnimationGraphEvent>* a_source) {
	const BSFixedString reloadSequentialReserveStart("reloadSequentialReserveStart");
	const BSFixedString reloadSequentialStart("reloadSequentialStart");
	const BSFixedString Event00("Event00");
	const BSFixedString pipboyClosed("pipboyClosed");
	const BSFixedString pipboyOpened("pipboyOpened");
	const BSFixedString ReloadComplete("ReloadComplete");
	const BSFixedString ReloadEnd("ReloadEnd");
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

	if (weaponHasSequentialReload) {
		if (!reloadHasStarted && reloadHasEnded) {
			if (a_event.name == Event00) {
				reloadStartHandle();
				StopLesserAmmo();
				isEmptyReload = WeaponInfo::weapInfo.weapAmmoCurrentCount == 0 ? true : false;
			}
		}
		if (reloadHasStarted && !reloadHasEnded) {
			if (a_event.name == ReloadEnd) { //Better way to do this? Bolt action stuff calls reloadend event during bolt charge and reload
				logInfo("Event Recieved: ReloadEnd");
				reloadStop();
			}
			if (a_event.name == ReloadComplete) {
				logInfo("Event Recieved: reloadComplete");
				if ((WeaponInfo::weapInfo.weapAmmoCapacity - 1) == WeaponInfo::weapInfo.weapAmmoCurrentCount) {
					reloadStop();
				} else {
					SetWeapAmmoCapacity(WeaponInfo::weapInfo.weapAmmoCurrentCount + 1);
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
	if (a_event.name == weaponDraw) {
		HanldeWeaponEquipAfter3D(WeaponInfo::weapInfo);
	}

	if (weaponHasScopeThermal) {
		if (a_event.name == sightedStateEnter) {
			HandleWeaponSightsEnter();
		} else if (a_event.name == sightedStateExit) {
			HandleWeaponSightsExit();
		}
		if (a_event.name == weaponInstantDown) {
			HandleWeaponInstantDown();
		}
	}
	FnProcessEvent fn = fnHash.at(*(uintptr_t*)this);
	return fn ? (this->*fn)(a_event, a_source) : BSEventNotifyControl::kContinue;
}

void PlayerAnimGraphEventSink::HookSink() {
	uintptr_t vtable = *(uintptr_t*)this;
	auto it = fnHash.find(vtable);
	if (it == fnHash.end()) {
		FnProcessEvent fn = SafeWrite64Function(vtable + 0x8, &PlayerAnimGraphEventSink::HookedProcessEvent);
		fnHash.insert(std::pair<uintptr_t, FnProcessEvent>(vtable, fn));
	}
}

std::unordered_map<uintptr_t, PlayerAnimGraphEventSink::FnProcessEvent> PlayerAnimGraphEventSink::fnHash;
#pragma endregion

#pragma region PlayerSetWeaponStateEventSink
BSEventNotifyControl PlayerSetWeaponStateEventSink::ProcessEvent(const PlayerSetWeaponStateEvent& a_event, BSTEventSource<PlayerSetWeaponStateEvent>* a_source) {
	bool isDrawing = false;
	WEAPON_STATE state = a_event.optionalValue.value();
	if (state == WEAPON_STATE::kDrawing) {
		logInfo("Weapon is being equiped.");
		isDrawing = true;
	}
	if (state == WEAPON_STATE::kDrawn && isDrawing) {
		logInfo("Weapon has finished being equiped.");
		isDrawing = false;
	}
	if (state == WEAPON_STATE::kSheathing || state == WEAPON_STATE::kSheathed) {
		isDrawing = false;
	}
	return BSEventNotifyControl::kContinue;
}
#pragma endregion

#pragma region PlayerWeaponReloadEventSink
BSEventNotifyControl PlayerWeaponReloadEventSink::ProcessEvent(const PlayerWeaponReloadEvent& a_event, BSTEventSource<PlayerWeaponReloadEvent>* a_source) {
	//logInfo("PlayerWeaponReloadEvent");
	return BSEventNotifyControl::kContinue;
}
#pragma endregion

#pragma region TESEquipEventSink
//adding too much to this hook causes the equip to stall and do weird things
//Bingle showed me how threading worked :) hopefully that should fix the issues with the above comment
BSEventNotifyControl TESEquipEventSink::ProcessEvent(const TESEquipEvent& a_event, BSTEventSource<TESEquipEvent>* a_source) {
	if (a_event.isEquipping == false) {
		return BSEventNotifyControl::kContinue;
	}
	if (a_event.owner != PlayerCharacter::GetSingleton()) {
		return BSEventNotifyControl::kContinue;
	}

	logInfo("TESEquipEvent Dump");
	Dump(const_cast<TESEquipEvent*>(&a_event), 0xB0);

	TESForm* form = TESForm::GetFormByID(a_event.FormID);
	if (!form || form->formType != ENUM_FORM_ID::kWEAP) {
		return BSEventNotifyControl::kContinue;
	}
	if (WeaponInfo::weapCurrentInstanceData != a_event.instanceData) {
		WeaponInfo::weapCurrentInstanceData = a_event.instanceData;
	}
	std::thread([]() {
		HanldeWeaponEquip(FillWeaponInfo(WeaponInfo::weapInfo));
	}).detach();

	return BSEventNotifyControl::kContinue;
}
#pragma endregion

#pragma region TESFurnitureEventSink
//TODO: check what furniture the player is getting into. Might be able to ignore power armor frame
BSEventNotifyControl TESFurnitureEventSink::ProcessEvent(const TESFurnitureEvent& a_event, BSTEventSource<TESFurnitureEvent>* a_source) {
	if (a_event.actor.get() == PlayerCharacter::GetSingleton()) {
		if (a_event.type.get() == TESFurnitureEvent::FurnitureEventType::kExit) {
			logInfo("Player is leaving the workbench. We may resume our work.");
			ignoreEquip = false;
		} else {
			logInfo("Player is entering a workbench. We need to ignore certain events during this time.");
			ignoreEquip = true;
		}
	}
	return BSEventNotifyControl::kContinue;
}
#pragma endregion

#pragma region TESLoadGameEventSink
BSEventNotifyControl TESLoadGameEventSink::ProcessEvent(const TESLoadGameEvent& a_event, BSTEventSource<TESLoadGameEvent>* a_source) {
	return BSEventNotifyControl::kContinue;
}
#pragma endregion

#pragma region TryHooks
void TryHookBGSOnPlayerUseWorkBenchEvent() {
	if (hookedList.at("BGSOnPlayerUseWorkBenchEvent") == true) {
		return;
	}

	BSTEventSource<BGSOnPlayerUseWorkBenchEvent>* eventSource = BGSOnPlayerUseWorkBenchEvent::GetEventSource();
	if (eventSource) {
		BGSOnPlayerUseWorkBenchEventSink* OnPlayerUseWorkBenchEventSink = new BGSOnPlayerUseWorkBenchEventSink();
		eventSource->RegisterSink(OnPlayerUseWorkBenchEventSink);
		hookedList.at("BGSOnPlayerUseWorkBenchEvent") = true;
	}
}

void TryHookMenuOpenCloseEvent() {
	if (hookedList.at("MenuOpenCloseEvent") == true) {
		return;
	}
	BSTEventSource<MenuOpenCloseEvent>* eventSource = UI::GetSingleton()->GetEventSource<MenuOpenCloseEvent>();
	if (eventSource) {
		MenuOpenCloseEventSink* OnMenuOpenCloseEventSink = new MenuOpenCloseEventSink();
		eventSource->RegisterSink(OnMenuOpenCloseEventSink);
		hookedList.at("MenuOpenCloseEvent") = true;
	}
}

void TryHookPlayerAmmoCountEvent() {
	if (hookedList.at("PlayerAmmoCountEvent") == true) {
		return;
	}
	//BSTEventSource<PlayerAmmoCountEvent>* eventSource = PlayerAmmoCountEventSink::GetEventSource();
	BSTEventSource<PlayerAmmoCountEvent>* eventSource = PlayerAmmoCountEvent::GetEventSource();
	if (eventSource) {
		PlayerAmmoCountEventSink* OnPlayerAmmoCountEventSink = new PlayerAmmoCountEventSink();
		eventSource->RegisterSink(OnPlayerAmmoCountEventSink);
		hookedList.at("PlayerAmmoCountEvent") = true;
	}
}

void TryHookPlayerAnimGraphEvent() {
	if (hookedList.at("PlayerAnimGraphEvent") == true) {
		return;
	}
	auto p = PlayerCharacter::GetSingleton();
	if (p) {
		//PlayerAnimGraphEventSink* OnPlayerAnimGraphEventSink = ((PlayerAnimGraphEventSink*)((uintptr_t)p + 0x38));
		//OnPlayerAnimGraphEventSink->HookSink();
		((PlayerAnimGraphEventSink*)((uintptr_t)p + 0x38))->HookSink();
		hookedList.at("PlayerAnimGraphEvent") = true;
	}
}

void TryHookPlayerSetWeaponStateEvent() {
	if (hookedList.at("PlayerSetWeaponStateEvent") == true) {
		return;
	}
	BSTEventSource<PlayerSetWeaponStateEvent>* eventSource = PlayerSetWeaponStateEvent::GetEventSource();
	if (eventSource) {
		PlayerSetWeaponStateEventSink* OnPlayerSetWeaponStateEvent = new PlayerSetWeaponStateEventSink();
		eventSource->RegisterSink(OnPlayerSetWeaponStateEvent);
		hookedList.at("PlayerSetWeaponStateEvent") = true;
	}
}

void TryHookPlayerWeaponReloadEvent() {
	if (hookedList.at("PlayerWeaponReloadEvent") == true) {
		return;
	}
	BSTEventSource<PlayerWeaponReloadEvent>* eventSource = PlayerWeaponReloadEvent::GetEventSource();
	if (eventSource) {
		PlayerWeaponReloadEventSink* OnPlayerWeaponReloadEvent = new PlayerWeaponReloadEventSink();
		eventSource->RegisterSink(OnPlayerWeaponReloadEvent);
		hookedList.at("PlayerWeaponReloadEvent") = true;
	}
}

void TryHookTESEquipEvent() {
	if (hookedList.at("TESEquipEvent") == true) {
		return;
	}
	BSTEventSource<TESEquipEvent>* eventSource = &TESEquipEvent::GetSingleton();
	if (eventSource) {
		TESEquipEventSink* OnTESEquipEvent = new TESEquipEventSink();
		eventSource->RegisterSink(OnTESEquipEvent);
		hookedList.at("TESEquipEvent") = true;
	}
}

void TryHookTESFurnitureEvent() {
	if (hookedList.at("TESFurnitureEvent") == true) {
		return;
	}
	BSTEventSource<TESFurnitureEvent>* eventSource = TESFurnitureEvent::GetEventSource();
	if (eventSource) {
		TESFurnitureEventSink* OnTESFurnitureEvent = new TESFurnitureEventSink();
		eventSource->RegisterSink(OnTESFurnitureEvent);
		hookedList.at("TESFurnitureEvent") = true;
	}
}

void TryHookTESLoadGameEvent() {
	if (hookedList.at("TESLoadGameEvent") == true) {
		return;
	}
	BSTEventSource<TESLoadGameEvent>* eventSource = TESLoadGameEvent::GetEventSource();
	if (eventSource) {
		TESLoadGameEventSink* OnTESLoadGameEvent = new TESLoadGameEventSink();
		eventSource->RegisterSink(OnTESLoadGameEvent);
		hookedList.at("TESLoadGameEvent") = true;
	}
}

void TryHooks() {
	logInfo("Trying for hooks...");
	TryHookBGSOnPlayerUseWorkBenchEvent();
	TryHookMenuOpenCloseEvent();
	TryHookPlayerAnimGraphEvent();
	TryHookTESEquipEvent();
	TryHookTESFurnitureEvent();
	TryHookTESLoadGameEvent();
}

//Used to hook certain things that CTD if hooked at the wrong time
void TrySpecialHooks() {
	logInfo("Trying for special hooks...");
	TryHookPlayerAmmoCountEvent();
	TryHookPlayerSetWeaponStateEvent();
	TryHookPlayerWeaponReloadEvent();
}
#pragma endregion

#pragma region Init
void initHooks() {
	if (hookedList.empty()) {
		hookedList = {
			{ "BGSOnPlayerUseWorkBenchEvent", false },
			{ "MenuOpenCloseEvent", false },
			{ "PlayerAmmoCountEvent", false },
			{ "PlayerAnimGraphEvent", false },
			{ "PlayerSetWeaponStateEvent", false },
			{ "PlayerWeaponReloadEvent", false },
			{ "TESEquipEvent", false },
			{ "TESFurnitureEvent", false },
			{ "TESLoadGameEvent", false },
		};
	}
	TryHooks();
	logInfo(";=============================== Hooks Install Complete ===============================;");
	print_map(std::as_const(hookedList));
	logInfo(";======================================================================================;");
}

//Mostly for global events
void initSpecialHooks() {
	TrySpecialHooks();
	logInfo(";=========================== Special Hooks Install Complete ===========================;");
	print_map(std::as_const(hookedList));
	logInfo(";======================================================================================;");
}
#pragma endregion
