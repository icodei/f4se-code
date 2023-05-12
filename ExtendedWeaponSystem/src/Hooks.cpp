#include "Hooks.h"

#include "Global.h"
#include "HookInfo.h"
#include "HookUtil.h"
#include "InputUtil.h"
#include "ReloadHandlers.h"
#include "Util.h"
#include "WeaponHandlers.h"
#include "WeaponInfo.h"

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
		if (pc->autoReload) {
			pc->SetAutoReload(false);
			pc->autoReloadTimer = -1.0F;
		}
	}
	return BSEventNotifyControl::kContinue;
}
#pragma endregion MenuOpenCloseEventSink

#pragma region PlayerAmmoCountEventSink
BSEventNotifyControl PlayerAmmoCountEventSink::ProcessEvent(const PlayerAmmoCountEvent& a_event, BSTEventSource<PlayerAmmoCountEvent>* a_source) {
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
		logInfo("Weapon Sheathed");
		return BSEventNotifyControl::kContinue;
	case WEAPON_STATE::kWantToDraw:
		logInfo("Weapon Wants To Draw");
		return BSEventNotifyControl::kContinue;
	case WEAPON_STATE::kDrawing:
		logInfo("Weapon Drawing");
		return BSEventNotifyControl::kContinue;
	case WEAPON_STATE::kDrawn:
		logInfo("Weapon Drawn");
		return BSEventNotifyControl::kContinue;
	case WEAPON_STATE::kWantToSheathe:
		logInfo("Weapon Wants To Sheathe");
		return BSEventNotifyControl::kContinue;
	case WEAPON_STATE::kSheathing:
		logInfo("Weapon Sheathing");
		return BSEventNotifyControl::kContinue;
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
	if (!a_event.FormID) {
		return BSEventNotifyControl::kContinue;
	}
	if (a_event.owner != pc) {
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
	if (a_event.isEquipping) {
		//std::thread([&Info]() {
		//	HandleWeaponEquip(FillWeaponInfo(Info));
		//}).detach();
		QueueHandlingOfWeaponEquip(FillWeaponInfo(Info));
	} else {
		std::thread([&Info]() {
			HandleWeaponUnequip(FillWeaponInfo(Info));
		}).detach();
		//QueueHandlingOfWeaponUnequip(FillWeaponInfo(Info));
	}

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
	logInfo("Game Loaded");
	return BSEventNotifyControl::kContinue;
}
#pragma endregion TESLoadGameEventSink

#pragma endregion EventSink

/*;========================================================================================================================================================;*/

#pragma region Handlers

#pragma region PlayerAnimationGraphEventHandler
BSEventNotifyControl PlayerAnimationGraphEventHandler::HookedProcessEvent(const BSAnimationGraphEvent& a_event, BSTEventSource<BSAnimationGraphEvent>* a_source) {
	HookInfo& HookInfo = HookInfo::getInstance();
	WeaponInfo& Info = WeaponInfo::getInstance();
	const BSFixedString Event00("Event00");
	const BSFixedString pipboyClosed("pipboyClosed");
	const BSFixedString pipboyOpened("pipboyOpened");
	const BSFixedString ReloadComplete("ReloadComplete");
	const BSFixedString ReloadEnd("ReloadEnd");
	const BSFixedString reloadSequentialReserveStart("reloadSequentialReserveStart");
	const BSFixedString reloadSequentialStart("reloadSequentialStart");
	const BSFixedString reloadStateEnter("reloadStateEnter");
	const BSFixedString reloadStateExit("reloadStateExit");
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
		HandleSequentialReload(a_event);
	}

	if (!weaponHasSequentialReload) {
		if (a_event.name == reloadStateEnter) {
			reloadHasStarted = true;
			reloadHasEnded = false;
		}
		if (a_event.name == reloadStateExit) {
			reloadHasStarted = false;
			reloadHasEnded = true;
		}
	}

	//These functions could be moved into a new hook by hooking sighted and equip handlers
	//if (a_event.name == weaponDraw) {
	//	HandleWeaponEquipAfter3D(Info::weapInfo);
	//}
	//if (a_event.name == sightedStateEnter) {
	//	HandleWeaponSightsEnter();
	//}
	//if (a_event.name == sightedStateExit) {
	//	HandleWeaponSightsExit();
	//}
	if (a_event.name == weaponInstantDown) {
		HandleWeaponInstantDown();
	}

	FnProcessEvent fn = HookInfo.fnPlayerAnimationGraphEventHash.at(*(uintptr_t*)this);
	return fn ? (this->*fn)(a_event, a_source) : BSEventNotifyControl::kContinue;
}

void PlayerAnimationGraphEventHandler::HookSink() {
	HookInfo& Info = HookInfo::getInstance();
	uintptr_t vtable = *(uintptr_t*)this;
	auto it = Info.fnPlayerAnimationGraphEventHash.find(vtable);
	if (it == Info.fnPlayerAnimationGraphEventHash.end()) {
		FnProcessEvent fn = HookUtil::SafeWrite64Function(vtable + 0x8, &PlayerAnimationGraphEventHandler::HookedProcessEvent);
		Info.fnPlayerAnimationGraphEventHash.insert(std::pair<uintptr_t, FnProcessEvent>(vtable, fn));
	}
}
#pragma endregion PlayerAnimationGraphEventHandler

#pragma region PlayerAttackHandler
void PlayerAttackHandler::HandleButtonEvent(const ButtonEvent* inputEvent) {
	if (inputEvent->strUserEvent == "SecondaryAttack") {
	}
	if (inputEvent->strUserEvent == "PrimaryAttack") {
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

void PlayerAttackHandlerHook::HookedHandleButtonEvent(const ButtonEvent* inputEvent) {
	HookInfo& Info = HookInfo::getInstance();
	if (inputEvent->strUserEvent == "SecondaryAttack") {
	}
	if (inputEvent->strUserEvent == "PrimaryAttack") {
	}
	FnHandleButtonEvent fn = Info.fnPlayerAttackHash.at(*(uintptr_t*)this);
	if (fn) {
		(this->*fn)(inputEvent);
	}
}

void PlayerAttackHandlerHook::HookSink() {
	HookInfo& Info = HookInfo::getInstance();
	uintptr_t vtable = *(uintptr_t*)this;
	auto it = Info.fnPlayerAttackHash.find(vtable);
	if (it == Info.fnPlayerAttackHash.end()) {
		FnHandleButtonEvent fn = HookUtil::SafeWrite64Function(vtable + 0x40, &PlayerAttackHandlerHook::HookedHandleButtonEvent);
		Info.fnPlayerAttackHash.insert(std::pair<uintptr_t, FnHandleButtonEvent>(vtable, fn));
	}
}
#pragma endregion PlayerAttackHandler

#pragma region PlayerReadyWeaponHandler
void PlayerReadyWeaponHandler::HandleButtonEvent(const ButtonEvent* inputEvent) {
}

void PlayerReadyWeaponHandlerHook::HookedHandleButtonEvent(const ButtonEvent* inputEvent) {
	HookInfo& Info = HookInfo::getInstance();
	if (weaponHasSpeedReload && HasReloadEnded()) {
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
			if (ShouldReload()) {
				DoSpeedReload();
				PlayerControls::GetSingleton()->readyWeaponHandler->unk20 = 1;  //Could be problematic?
			}
		}
		//IsButtonDoubleTapFunctor(inputEvent, &DoSpeedReload);
	}
	FnHandleButtonEvent fn = Info.fnPlayerReadyWeaponHash.at(*(uintptr_t*)this);
	if (fn) {
		(this->*fn)(inputEvent);
	}
}

void PlayerReadyWeaponHandlerHook::HookSink() {
	HookInfo& Info = HookInfo::getInstance();
	uintptr_t vtable = *(uintptr_t*)this;
	auto it = Info.fnPlayerReadyWeaponHash.find(vtable);
	if (it == Info.fnPlayerReadyWeaponHash.end()) {
		FnHandleButtonEvent fn = HookUtil::SafeWrite64Function(vtable + 0x40, &PlayerReadyWeaponHandlerHook::HookedHandleButtonEvent);
		Info.fnPlayerReadyWeaponHash.insert(std::pair<uintptr_t, FnHandleButtonEvent>(vtable, fn));
	}
}
#pragma endregion PlayerReadyWeaponHandler

#pragma region PlayerSightedStateChange
bool PlayerSightedStateChangeHandler::HookedSetInIronSights(bool EnterIronSights) {
	HookInfo& Info = HookInfo::getInstance();
	if (EnterIronSights) {
		HandleWeaponSightsEnter();
	} else if (!EnterIronSights) {
		HandleWeaponSightsExit();
	}

	FnSetInIronSights fn = Info.fnPlayerSetIronSightsHash.at(*(uintptr_t*)this);
	return fn ? (this->*fn)(EnterIronSights) : false;
}

void PlayerSightedStateChangeHandler::HookSink() {
	HookInfo& Info = HookInfo::getInstance();
	uintptr_t vtable = *(uintptr_t*)this;
	auto it = Info.fnPlayerSetIronSightsHash.find(vtable);
	if (it == Info.fnPlayerSetIronSightsHash.end()) {
		FnSetInIronSights fn = HookUtil::SafeWrite64Function(vtable + 0x128, &PlayerSightedStateChangeHandler::HookedSetInIronSights);
		Info.fnPlayerSetIronSightsHash.insert(std::pair<uintptr_t, FnSetInIronSights>(vtable, fn));
	}
}
#pragma endregion PlayerSightedStateChangeHandler

#pragma endregion Handlers

#pragma region TryHooks

void TryHookMenuOpenCloseEvent() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("MenuOpenCloseEvent") == true) {
		return;
	}
	BSTEventSource<MenuOpenCloseEvent>* eventSource = UI::GetSingleton()->GetEventSource<MenuOpenCloseEvent>();
	if (eventSource) {
		MenuOpenCloseEventSink* OnMenuOpenCloseEventSink = new MenuOpenCloseEventSink();
		eventSource->RegisterSink(OnMenuOpenCloseEventSink);
		Info.hookedList.at("MenuOpenCloseEvent") = true;
	}
}

void TryHookPlayerAmmoCountEvent() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("PlayerAmmoCountEvent") == true) {
		return;
	}
	BSTEventSource<PlayerAmmoCountEvent>* eventSource = PlayerAmmoCountEvent::GetEventSource();
	if (eventSource) {
		PlayerAmmoCountEventSink* OnPlayerAmmoCountEventSink = new PlayerAmmoCountEventSink();
		eventSource->RegisterSink(OnPlayerAmmoCountEventSink);
		Info.hookedList.at("PlayerAmmoCountEvent") = true;
	}
}

void TryHookPlayerAnimGraphEvent() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("PlayerAnimGraphEvent") == true) {
		return;
	}
	auto player = PlayerCharacter::GetSingleton();
	if (player) {
		((PlayerAnimationGraphEventHandler*)((uintptr_t)player + 0x38))->HookSink();
		Info.hookedList.at("PlayerAnimGraphEvent") = true;
	}
}

void TryHookPlayerAttackHandler() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("PlayerAttackHandler") == true) {
		return;
	}
	auto controls = PlayerControls::GetSingleton();
	if (controls) {
		PlayerAttackHandler* OnPlayerAttack = new PlayerAttackHandler(controls->data);
		controls->RegisterHandler(OnPlayerAttack);
		((PlayerAttackHandlerHook*)controls->attackHandler)->HookSink();
		Info.hookedList.at("PlayerAttackHandler") = true;
	}
}

void TryHookPlayerReadyWeaponHandler() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("PlayerReadyWeaponHandler") == true) {
		return;
	}
	auto controls = PlayerControls::GetSingleton();
	if (controls) {
		PlayerReadyWeaponHandler* OnPlayerReadyWeapon = new PlayerReadyWeaponHandler(controls->data);
		controls->RegisterHandler(OnPlayerReadyWeapon);
		((PlayerReadyWeaponHandlerHook*)controls->readyWeaponHandler)->HookSink();
		Info.hookedList.at("PlayerReadyWeaponHandler") = true;
	}
}

void TryHookPlayerSetWeaponStateEvent() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("PlayerSetWeaponStateEvent") == true) {
		return;
	}
	BSTEventSource<PlayerSetWeaponStateEvent>* eventSource = PlayerSetWeaponStateEvent::GetEventSource();
	if (eventSource) {
		PlayerSetWeaponStateEventSink* OnPlayerSetWeaponStateEvent = new PlayerSetWeaponStateEventSink();
		eventSource->RegisterSink(OnPlayerSetWeaponStateEvent);
		Info.hookedList.at("PlayerSetWeaponStateEvent") = true;
	}
}

void TryHookPlayerSightedStateChangeHandler() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("PlayerSightedStateChangeHandler") == true) {
		return;
	}
	auto player = PlayerCharacter::GetSingleton();
	if (player) {
		((PlayerSightedStateChangeHandler*)((uintptr_t)player + 0x128))->HookSink();
		Info.hookedList.at("PlayerSightedStateChangeHandler") = true;
	}
}

void TryHookPlayerWeaponReloadEvent() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("PlayerWeaponReloadEvent") == true) {
		return;
	}
	BSTEventSource<PlayerWeaponReloadEvent>* eventSource = PlayerWeaponReloadEvent::GetEventSource();
	if (eventSource) {
		PlayerWeaponReloadEventSink* OnPlayerWeaponReloadEvent = new PlayerWeaponReloadEventSink();
		eventSource->RegisterSink(OnPlayerWeaponReloadEvent);
		Info.hookedList.at("PlayerWeaponReloadEvent") = true;
	}
}

void TryHookTESEquipEvent() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("TESEquipEvent") == true) {
		return;
	}
	BSTEventSource<TESEquipEvent>* eventSource = &TESEquipEvent::GetSingleton();
	if (eventSource) {
		TESEquipEventSink* OnTESEquipEvent = new TESEquipEventSink();
		eventSource->RegisterSink(OnTESEquipEvent);
		Info.hookedList.at("TESEquipEvent") = true;
	}
}

void TryHookTESFurnitureEvent() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("TESFurnitureEvent") == true) {
		return;
	}
	BSTEventSource<TESFurnitureEvent>* eventSource = TESFurnitureEvent::GetEventSource();
	if (eventSource) {
		TESFurnitureEventSink* OnTESFurnitureEvent = new TESFurnitureEventSink();
		eventSource->RegisterSink(OnTESFurnitureEvent);
		Info.hookedList.at("TESFurnitureEvent") = true;
	}
}

void TryHookTESLoadGameEvent() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.at("TESLoadGameEvent") == true) {
		return;
	}
	BSTEventSource<TESLoadGameEvent>* eventSource = TESLoadGameEvent::GetEventSource();
	if (eventSource) {
		TESLoadGameEventSink* OnTESLoadGameEvent = new TESLoadGameEventSink();
		eventSource->RegisterSink(OnTESLoadGameEvent);
		Info.hookedList.at("TESLoadGameEvent") = true;
	}
}

void TryHooks() {
	HookInfo& Info = HookInfo::getInstance();
	if (!Info.hookedList.empty()) {
		int i = 0;
		for (const std::pair<const char*, bool>& n : Info.hookedList) {
			if (n.second) {
				++i;
			}
		}
		if (i && i == Info.hookedList.size()) {
			return;
		}
	}

	logInfo("Trying for hooks...");
	TryHookMenuOpenCloseEvent();
	TryHookPlayerAttackHandler();
	TryHookPlayerAnimGraphEvent();
	TryHookPlayerReadyWeaponHandler();
	TryHookPlayerSightedStateChangeHandler();
	TryHookTESEquipEvent();
	TryHookTESFurnitureEvent();
	TryHookTESLoadGameEvent();
}

void TrySpecialHooks() {
	HookInfo& Info = HookInfo::getInstance();

	logInfo("Trying for special hooks...");
	TryHookPlayerAmmoCountEvent();
	TryHookPlayerSetWeaponStateEvent();
	TryHookPlayerWeaponReloadEvent();
}
#pragma endregion

#pragma region Init
void initHooks() {
	HookInfo& Info = HookInfo::getInstance();
	if (Info.hookedList.empty()) {
		Info.hookedList = {
			{ "MenuOpenCloseEvent", false },
			{ "PlayerAmmoCountEvent", false },
			{ "PlayerAnimGraphEvent", false },
			{ "PlayerAttackHandler", false },
			{ "PlayerReadyWeaponHandler", false },
			{ "PlayerSetWeaponStateEvent", false },
			{ "PlayerSightedStateChangeHandler", false },
			{ "PlayerWeaponReloadEvent", false },
			{ "TESEquipEvent", false },
			{ "TESFurnitureEvent", false },
			{ "TESLoadGameEvent", false },
		};
	}
	TryHooks();
	logInfo(";=============================== Hooks Install Complete ===============================;");
	print_map(std::as_const(Info.hookedList));
	logInfo(";======================================================================================;");
}

//Mostly for global events
void initSpecialHooks() {
	HookInfo& Info = HookInfo::getInstance();
	if (!Info.hookedList.empty()) {
		int i = 0;
		for (const std::pair<const char*, bool>& n : Info.hookedList) {
			if (n.second) {
				++i;
			}
		}
		if (i && i == Info.hookedList.size()) {
			return;
		}
	}
	TrySpecialHooks();
	logInfo(";=========================== Special Hooks Install Complete ===========================;");
	print_map(std::as_const(Info.hookedList));
	logInfo(";======================================================================================;");
}
#pragma endregion
