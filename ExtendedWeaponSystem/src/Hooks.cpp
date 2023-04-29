#include "Hooks.h"

#pragma region EventSink

#pragma region MenuOpenCloseEventSink
BSEventNotifyControl MenuOpenCloseEventSink::ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_source) {
	const BSFixedString LoadingMenu("LoadingMenu");
	WeaponInfo& Info = WeaponInfo::getInstance();
	if (a_event.menuName == LoadingMenu && a_event.opening) {
		logInfo("Loading...");
		gameLoading = true;
	}
	if (a_event.menuName == LoadingMenu && !a_event.opening) {
		logInfo("Loading Complete");
		if (gameLoadingSave) {
			HandleWeaponOnLoadGame(FillWeaponInfo(Info));
			gameLoadingSave = false;
		}
	}
	return BSEventNotifyControl::kContinue;
}
#pragma endregion MenuOpenCloseEventSink

#pragma region PlayerAmmoCountEventSink
BSEventNotifyControl PlayerAmmoCountEventSink::ProcessEvent(const PlayerAmmoCountEvent& a_event, BSTEventSource<PlayerAmmoCountEvent>* a_source) {
	if (!weaponHasSequentialReload) {
		return BSEventNotifyControl::kContinue;
	}
	if (!a_event.optionalValue.has_value()) {
		return BSEventNotifyControl::kContinue;
	}
	if (!a_event.weapon) {
		return BSEventNotifyControl::kContinue;
	}
	if (!a_event.weaponInstance) {
		return BSEventNotifyControl::kContinue;
	}

	WeaponInfo& Info = WeaponInfo::getInstance();

	if (a_event.weaponInstance != Info.weapCurrentInstanceData) {
		Info.weapCurrentInstanceData = a_event.weaponInstance;
		Info.weapAmmoCapacity = a_event.weapon->weaponData.ammoCapacity;
	}

	//logInfo("PlayerAmmoCountEvent Dump");
	//Dump(const_cast<PlayerAmmoCountEvent*>(&a_event), 0x30);

	Info.weapAmmoCurrentCount = a_event.optionalValue.value().clipAmmo;
	Info.weapAmmoTotalCount = a_event.optionalValue.value().reserveAmmo;
	logInfo("ammo count: " + std::to_string(Info.weapAmmoCurrentCount));
	return BSEventNotifyControl::kContinue;
}

BSTEventSource<PlayerAmmoCountEvent>* PlayerAmmoCountEventSink::GetEventSource() {
	return GET_EVENT_SOURCE(PlayerAmmoCountEvent);
}
#pragma endregion PlayerAmmoCountEventSink

#pragma region PlayerSetWeaponStateEventSink
BSEventNotifyControl PlayerSetWeaponStateEventSink::ProcessEvent(const PlayerSetWeaponStateEvent& a_event, BSTEventSource<PlayerSetWeaponStateEvent>* a_source) {
	//logger::info(FMT_STRING("PlayerSetWeaponStateEvent at {:p}"), fmt::ptr(std::addressof(a_event)));
	//logInfo("PlayerSetWeaponStateEvent Dump");
	//Dump(const_cast<PlayerSetWeaponStateEvent*>(&a_event), 0x16);

	WEAPON_STATE state = a_event.optionalValue.value();
	switch (state) {
	case WEAPON_STATE::kSheathed:
		if (nsScope::initialized) {
			logInfo("Scope Weapon Sheathed");
		}
	case WEAPON_STATE::kWantToDraw:

	case WEAPON_STATE::kDrawing:
		if (nsScope::initialized) {
			logInfo("Scope Weapon Drawing");
		}
	case WEAPON_STATE::kDrawn:
		if (nsScope::initialized) {
			logInfo("Scope Weapon Drawn");
		}
	case WEAPON_STATE::kWantToSheathe:

	case WEAPON_STATE::kSheathing:
		if (nsScope::initialized) {
			logInfo("Scope Weapon Sheathing");
		}
	default:
		return BSEventNotifyControl::kContinue;
	}
}
#pragma endregion PlayerSetWeaponStateEventSink

#pragma region PlayerWeaponReloadEventSink
BSEventNotifyControl PlayerWeaponReloadEventSink::ProcessEvent(const PlayerWeaponReloadEvent& a_event, BSTEventSource<PlayerWeaponReloadEvent>* a_source) {
	//logInfo("PlayerWeaponReloadEvent");
	return BSEventNotifyControl::kContinue;
}
#pragma endregion PlayerWeaponReloadEventSink

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
	TESForm* form = TESForm::GetFormByID(a_event.FormID);
	if (!form || form->formType != ENUM_FORM_ID::kWEAP) {
		return BSEventNotifyControl::kContinue;
	}

	//logger::info(FMT_STRING("TESEquipEvent at {:p}"), fmt::ptr(std::addressof(a_event)));
	//logInfo("TESEquipEvent Dump");
	//Dump(const_cast<TESEquipEvent*>(&a_event), 0xB0);

	WeaponInfo& Info = WeaponInfo::getInstance();

	if (Info.weapCurrentInstanceData != a_event.instanceData) {
		Info.weapCurrentInstanceData = a_event.instanceData;
	}
	std::thread([&Info]() {
		HanldeWeaponEquip(FillWeaponInfo(Info));
	}).detach();

	return BSEventNotifyControl::kContinue;
}
#pragma endregion TESEquipEventSink

#pragma region TESFurnitureEventSink
//TODO: check what furniture the player is getting into. Might be able to ignore power armor frame
BSEventNotifyControl TESFurnitureEventSink::ProcessEvent(const TESFurnitureEvent& a_event, BSTEventSource<TESFurnitureEvent>* a_source) {
	if (a_event.actor.get() != PlayerCharacter::GetSingleton()) {
		return BSEventNotifyControl::kContinue;
	}
	if (a_event.type.get() == TESFurnitureEvent::FurnitureEventType::kExit) {
	} else {
	}
	return BSEventNotifyControl::kContinue;
}
#pragma endregion TESFurnitureEventSink

#pragma region TESLoadGameEventSink
BSEventNotifyControl TESLoadGameEventSink::ProcessEvent(const TESLoadGameEvent& a_event, BSTEventSource<TESLoadGameEvent>* a_source) {
	return BSEventNotifyControl::kContinue;
}
#pragma endregion TESLoadGameEventSink

#pragma endregion EventSink

/*;========================================================================================================================================================;*/

#pragma region Handlers

#pragma region PlayerAnimGraphEventHandler
BSEventNotifyControl PlayerAnimGraphEventHandler::HookedProcessEvent(const BSAnimationGraphEvent& a_event, BSTEventSource<BSAnimationGraphEvent>* a_source) {
	WeaponInfo& Info = WeaponInfo::getInstance();
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
		if (HasReloadEnded()) {
			if (a_event.name == Event00) {
				reloadStartHandle();
				StopLesserAmmo();
				isEmptyReload = Info.weapAmmoCurrentCount == 0 ? true : false;
			}
		}
		if (HasReloadStarted()) {
			if (a_event.name == ReloadEnd) {  //Better way to do this? Bolt action stuff calls reloadend event during bolt charge and reload
				logInfo("Event Recieved: ReloadEnd");
				reloadStop();
			}
			if (a_event.name == ReloadComplete) {
				logInfo("Event Recieved: reloadComplete");
				if ((Info.weapAmmoCapacity - 1) == Info.weapAmmoCurrentCount) {
					reloadStop();
				} else {
					SetWeapAmmoCapacity(Info.weapAmmoCurrentCount + 1);
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

	//These functions could be moved into a new hook by hooking sighted and equip handlers
	//if (a_event.name == weaponDraw) {
	//	HanldeWeaponEquipAfter3D(Info::weapInfo);
	//}
	//if (a_event.name == sightedStateEnter) {
	//	HandleWeaponSightsEnter();
	//}
	//if (a_event.name == sightedStateExit) {
	//	HandleWeaponSightsExit();
	//}
	//if (a_event.name == weaponInstantDown) {
	//	HandleWeaponDown();
	//}

	FnProcessEvent fn = fnHash.at(*(uintptr_t*)this);
	return fn ? (this->*fn)(a_event, a_source) : BSEventNotifyControl::kContinue;
}

void PlayerAnimGraphEventHandler::HookSink() {
	uintptr_t vtable = *(uintptr_t*)this;
	auto it = fnHash.find(vtable);
	if (it == fnHash.end()) {
		FnProcessEvent fn = HookUtil::SafeWrite64Function(vtable + 0x8, &PlayerAnimGraphEventHandler::HookedProcessEvent);
		fnHash.insert(std::pair<uintptr_t, FnProcessEvent>(vtable, fn));
	}
}
std::unordered_map<uintptr_t, PlayerAnimGraphEventHandler::FnProcessEvent> PlayerAnimGraphEventHandler::fnHash;
#pragma endregion PlayerAnimGraphEventHandler

#pragma region PlayerAttackHandler
void PlayerAttackHandler::HandleButtonEvent(const ButtonEvent* inputEvent) {
	if (weaponHasSpeedReload) {
		if (inputEvent->value == 1.0f && inputEvent->heldDownSecs == 0.0f) {
			if (inputEvent->strUserEvent == std::string_view("ReadyWeapon")) {
				IsButtonDoubleTapFunctor(inputEvent->idCode, &DoSpeedReload);
			}
		}
	}
}

void PlayerAttackHandler::DoLeftAttack() {
}

void PlayerAttackHandler::DoRightAttack() {
}

void PlayerAttackHandler::HandleDualAttack(const ButtonEvent* inputEvent) {
}

void PlayerAttackHandler::HandleLeftAttack(const ButtonEvent* inputEvent) {
}

void PlayerAttackHandler::HandleRightAttack(const ButtonEvent* inputEvent) {
}

void PlayerAttackHandler::HookedHandleButtonEvent(const ButtonEvent* inputEvent) {
	if (inputEvent->strUserEvent == "SecondaryAttack") {
	}
	if (inputEvent->strUserEvent == "PrimaryAttack") {
	}
	FnHandleButtonEvent fn = fnHash.at(*(uintptr_t*)this);
	if (fn) {
		(this->*fn)(inputEvent);
	}
}

void PlayerAttackHandler::HookSink() {
	uintptr_t vtable = *(uintptr_t*)this;
	auto it = fnHash.find(vtable);
	if (it == fnHash.end()) {
		FnHandleButtonEvent fn = HookUtil::SafeWrite64Function(vtable + 0x40, &PlayerAttackHandler::HookedHandleButtonEvent);
		fnHash.insert(std::pair<uintptr_t, FnHandleButtonEvent>(vtable, fn));
	}
}
std::unordered_map<uintptr_t, PlayerAttackHandler::FnHandleButtonEvent> PlayerAttackHandler::fnHash;
#pragma endregion PlayerAttackHandler

#pragma region PlayerSightedStateChange
bool PlayerSightedStateChangeHandler::HookedExecuteHandler(void* a_handler, Actor& a_actor, BSFixedString& a_event) {
	if (a_event == "Enter") {
		logInfo("SightedStateEnter");
		HandleWeaponSightsEnter();
	} else if (a_event == "Exit") {
		logInfo("SightedStateExit");
		HandleWeaponSightsExit();
	}

	RETURN_HANDLER;
}

void PlayerSightedStateChangeHandler::Hook() {
	REL::Relocation<uintptr_t> HandlerVtable{ VTABLE::PlayerSightedStateChangeHandler[0] };
	fnOriginal = (FnExecuteHandler)HandlerVtable.write_vfunc(0x1, PlayerSightedStateChangeHandler::HookedExecuteHandler);
}
PlayerSightedStateChangeHandler::FnExecuteHandler PlayerSightedStateChangeHandler::fnOriginal;
#pragma endregion PlayerSightedStateChangeHandler

#pragma region PlayerWeaponAttachHandler
bool PlayerWeaponAttachHandler::HookedExecuteHandler(void* a_handler, Actor& a_actor, BSFixedString& a_event) {
	if (&a_actor != pc) {
		RETURN_HANDLER;
	}

	logInfo("PlayerWeaponAttachHandler");
	HanldeWeaponEquipAfter3D(WeaponInfo::getInstance());
	RETURN_HANDLER;
}

void PlayerWeaponAttachHandler::Hook() {
	REL::Relocation<uintptr_t> HandlerVtable{ VTABLE::WeaponAttachHandler[0] };
	fnOriginal = (FnExecuteHandler)HandlerVtable.write_vfunc(0x1, PlayerWeaponDrawHandler::HookedExecuteHandler);
}
PlayerWeaponAttachHandler::FnExecuteHandler PlayerWeaponAttachHandler::fnOriginal;
#pragma endregion PlayerWeaponAttachHandler

#pragma region PlayerWeaponDrawHandler
bool PlayerWeaponDrawHandler::HookedExecuteHandler(void* a_handler, Actor& a_actor, BSFixedString& a_event) {
	if (&a_actor != pc) {
		RETURN_HANDLER;
	}

	logInfo("PlayerWeaponDrawHandler");
	RETURN_HANDLER;
}

void PlayerWeaponDrawHandler::Hook() {
	REL::Relocation<uintptr_t> HandlerVtable{ VTABLE::WeaponDrawHandler[0] };
	fnOriginal = (FnExecuteHandler)HandlerVtable.write_vfunc(0x1, PlayerWeaponDrawHandler::HookedExecuteHandler);
}
PlayerWeaponDrawHandler::FnExecuteHandler PlayerWeaponDrawHandler::fnOriginal;
#pragma endregion PlayerWeaponDrawHandler

#pragma region PlayerWeaponSheatheHandler
bool PlayerWeaponSheatheHandler::HookedExecuteHandler(void* a_handler, Actor& a_actor, BSFixedString& a_event) {
	if (&a_actor != pc) {
		RETURN_HANDLER;
	}

	logInfo("PlayerWeaponSheatheHandler");
	HandleWeaponDown();
	RETURN_HANDLER;
}

void PlayerWeaponSheatheHandler::Hook() {
	REL::Relocation<uintptr_t> HandlerVtable{ VTABLE::WeaponSheatheHandler[0] };
	fnOriginal = (FnExecuteHandler)HandlerVtable.write_vfunc(0x1, PlayerSightedStateChangeHandler::HookedExecuteHandler);
}
PlayerWeaponSheatheHandler::FnExecuteHandler PlayerWeaponSheatheHandler::fnOriginal;
#pragma endregion PlayerWeaponSheatheHandler

#pragma endregion Handlers

#pragma region TryHooks

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
	auto player = PlayerCharacter::GetSingleton();
	if (player) {
		((PlayerAnimGraphEventHandler*)((uintptr_t)player + 0x38))->HookSink();
		hookedList.at("PlayerAnimGraphEvent") = true;
	}
}

void TryHookPlayerAttackHandler() {
	if (hookedList.at("PlayerAttackHandler") == true) {
		return;
	}
	auto controls = PlayerControls::GetSingleton();
	if (controls) {
		PlayerAttackHandler* OnPlayerAttack = new PlayerAttackHandler(controls->data);
		controls->RegisterHandler(OnPlayerAttack);
		//((PlayerAttackHandler*)controls->attackHandler)->HookSink();
		hookedList.at("PlayerAttackHandler") = true;
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

void TryHookPlayerSightedStateChangeHandler() {
	if (hookedList.at("PlayerSightedStateChangeHandler") == true) {
		return;
	}
	auto player = PlayerCharacter::GetSingleton();
	if (player) {
		PlayerSightedStateChangeHandler::Hook();
		hookedList.at("PlayerSightedStateChangeHandler") = true;
	}
}

void TryHookPlayerWeaponAttachHandler() {
	if (hookedList.at("PlayerWeaponAttachHandler") == true) {
		return;
	}
	auto player = PlayerCharacter::GetSingleton();
	if (player) {
		PlayerWeaponAttachHandler::Hook();
		hookedList.at("PlayerWeaponAttachHandler") = true;
	}
}

void TryHookPlayerWeaponDrawHandler() {
	if (hookedList.at("PlayerWeaponDrawHandler") == true) {
		return;
	}
	auto player = PlayerCharacter::GetSingleton();
	if (player) {
		PlayerWeaponDrawHandler::Hook();
		hookedList.at("PlayerWeaponDrawHandler") = true;
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

void TryHookPlayerWeaponSheatheHandler() {
	if (hookedList.at("PlayerWeaponSheatheHandler") == true) {
		return;
	}
	auto player = PlayerCharacter::GetSingleton();
	if (player) {
		PlayerWeaponSheatheHandler::Hook();
		hookedList.at("PlayerWeaponSheatheHandler") = true;
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
	TryHookMenuOpenCloseEvent();
	TryHookPlayerAttackHandler();
	TryHookPlayerAnimGraphEvent();
	TryHookPlayerSightedStateChangeHandler();
	TryHookPlayerWeaponAttachHandler();
	TryHookPlayerWeaponDrawHandler();
	TryHookPlayerWeaponSheatheHandler();
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
			{ "MenuOpenCloseEvent", false },
			{ "PlayerAmmoCountEvent", false },
			{ "PlayerAnimGraphEvent", false },
			{ "PlayerAttackHandler", false },
			{ "PlayerSetWeaponStateEvent", false },
			{ "PlayerSightedStateChangeHandler", false },
			{ "PlayerWeaponAttachHandler", false },
			{ "PlayerWeaponDrawHandler", false },
			{ "PlayerWeaponReloadEvent", false },
			{ "PlayerWeaponSheatheHandler", false },
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
