#include "Hooks.h"

BSEventNotifyControl BGSOnPlayerUseWorkBenchEventSink::ProcessEvent(const BGSOnPlayerUseWorkBenchEvent& a_event, BSTEventSource<BGSOnPlayerUseWorkBenchEvent>* a_source) {
	ignore = true;
	return BSEventNotifyControl::kContinue;
}

BSEventNotifyControl MenuOpenCloseEventSink::ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_source) {
	const BSFixedString LoadingMenu("LoadingMenu");

	if (a_event.menuName == LoadingMenu && a_event.opening) {
		ignore = true;
		//initSpecialHooks();
	}
	if (a_event.menuName == LoadingMenu && !a_event.opening) {
		ignore = false;
	}
	return BSEventNotifyControl::kContinue;
}

BSEventNotifyControl PlayerAmmoCountEventSink::ProcessEvent(const PlayerAmmoCountEvent& a_event, BSTEventSource<PlayerAmmoCountEvent>* a_source) {
	if (processCurrentWeap == false) {
		return BSEventNotifyControl::kContinue;
	}
	if (!a_event.weapon) {
		return BSEventNotifyControl::kContinue;
	}
	if (!a_event.weaponInstance) {
		return BSEventNotifyControl::kContinue;
	}
	if (a_event.unk08 != 1) {
		return BSEventNotifyControl::kContinue;
	}
	if (a_event.weaponInstance != currentWeapInstance) {
		currentWeapInstance = a_event.weaponInstance;
		ammoCapacity = currentWeapInstance->ammoCapacity;
	}
	currentAmmoCount = a_event.optionalValue.value().clipAmmo;
	totalAmmoCount = a_event.optionalValue.value().reserveAmmo;
	logInfoConditional("ammo count: " + std::to_string(currentAmmoCount));
	return BSEventNotifyControl::kContinue;
}

BSTEventSource<PlayerAmmoCountEvent>* PlayerAmmoCountEventSink::GetEventSource() {
	return GET_EVENT_SOURCE(PlayerAmmoCountEvent);
}

#pragma region PlayerAnimGraphEventSink
BSEventNotifyControl PlayerAnimGraphEventSink::HookedProcessEvent(const BSAnimationGraphEvent& a_event, BSTEventSource<BSAnimationGraphEvent>* a_source) {
	FnProcessEvent fn = fnHash.at(*(uintptr_t*)this);

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

	if (!currentWeapInstance) {
		return BSEventNotifyControl::kContinue;
	}
	
	if (processCurrentWeap) {
		if (!reloadStarted && reloadEnd) {
			if (a_event.name == Event00) {
				reloadStartHandle();
				StopLesserAmmo();
				isEmptyReload = currentAmmoCount == 0 ? true : false;
			}
		}
		if (reloadStarted && !reloadEnd) {
			if (a_event.name == ReloadEnd) {
				logInfoConditional("Event Recieved: ReloadEnd");
				reloadStop();
			}
			if (a_event.name == ReloadComplete) {
				logInfoConditional("Event Recieved: reloadComplete");
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
			//Manually handle reload end for various situations
			if (a_event.name == pipboyOpened) {
				reloadStop();
				logInfoConditional("Event Recieved: pipboy opened");
			}
			if (a_event.name == weaponSwing) {
				reloadStop();
				logInfoConditional("Event Recieved: weapon swing");
			}
			if (a_event.name == throwEnd) {
				reloadStop();
				logInfoConditional("Event Recieved: throw end");
			}
		}
	}
	if (a_event.name == weaponDraw) {
		HanldeWeaponEquipAfter3D();
	}

	if (processCurrentScope) {
		if (a_event.name == sightedStateEnter) {
			ignore = false;
		} else if (a_event.name == sightedStateExit) {
			ignore = true;
		}
		if (a_event.name == weaponInstantDown) {
			ignore = true;
			//Destroy turned off for testing
			//nsScope::DestroyRenderer();
		}
	}
	return fn ? (this->*fn)(const_cast<BSAnimationGraphEvent&>(a_event), a_source) : BSEventNotifyControl::kContinue;
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
	if (a_event.optionalValue.value() == WEAPON_STATE::kDrawing) {
		logInfoConditional("Weapon is being equiped.");
		isDrawing = true;
	}
	if (a_event.optionalValue.value() == WEAPON_STATE::kDrawn && isDrawing) {
		//HanldeWeaponEquipAfter3D();
		ignore = false;
		logInfoConditional("Weapon has finished being equiped.");
		isDrawing = false;
	}
	if (a_event.optionalValue.value() == WEAPON_STATE::kSheathing || a_event.optionalValue.value() == WEAPON_STATE::kSheathed) {
		isDrawing = false;
		ignore = true;
	}
	return BSEventNotifyControl::kContinue;
}
#pragma endregion

#pragma region PlayerWeaponReloadEventSink
BSEventNotifyControl PlayerWeaponReloadEventSink::ProcessEvent(const PlayerWeaponReloadEvent& a_event, BSTEventSource<PlayerWeaponReloadEvent>* a_source) {
	//logInfoConditional("PlayerWeaponReloadEvent");
	return BSEventNotifyControl::kContinue;
}
#pragma endregion

#pragma region TESEquipEventSink
//adding too much to this hook causes the equip to stall and do weird things
//Bingle showed me how threading worked :) hopefully that should fix the issues with the above comment
BSEventNotifyControl TESEquipEventSink::ProcessEvent(const TESEquipEvent& a_event, BSTEventSource<TESEquipEvent>* a_source) {
	if (ignore == true) {
		return BSEventNotifyControl::kContinue;
	}
	if (a_event.isEquipping == false) {
		return BSEventNotifyControl::kContinue;
	}
	if (a_event.owner != pc) {
		return BSEventNotifyControl::kContinue;
	}
	TESForm* form = TESForm::GetFormByID(a_event.FormID);
	if (!form || form->formType != ENUM_FORM_ID::kWEAP) {
		return BSEventNotifyControl::kContinue;
	}
	auto equipData = GetPlayerEquippedItemByEquipIndex(EquipIndex::kEquipIndex_Default);
	if (!equipData) {
		return BSEventNotifyControl::kContinue;
	}
	TESObjectWEAP* weap = static_cast<TESObjectWEAP*>(equipData->item.object);
	TESObjectWEAP::InstanceData* weapInst = const_cast<TESObjectWEAP::InstanceData*>(GetPlayerWeaponInstanceData(equipData->item.object, equipData->item.instanceData.get()));
	logInfoConditional(";======================================================================================;");
	logInfoConditional("Player TESEquipEvent: " + GetFullNameWEAP(weap));
	std::thread([weapInst]() { HanldeWeaponEquip(weapInst); }).detach();

	return BSEventNotifyControl::kContinue;
}
#pragma endregion

//TODO: check what furniture the player is getting into. Might be able to ignore power armor frame
BSEventNotifyControl TESFurnitureEventSink::ProcessEvent(const TESFurnitureEvent& a_event, BSTEventSource<TESFurnitureEvent>* a_source) {
	if (a_event.actor.get() == (pc)) {
		if (a_event.type.get() == TESFurnitureEvent::FurnitureEventType::kExit) {
			logInfoConditional("Player is leaving the workbench. We may resume our work.");
			ignore = false;
		} else {
			logInfoConditional("Player is entering a workbench. We need to ignore certain events during this time.");
			ignore = true;
		}
	}
	return BSEventNotifyControl::kContinue;
}

BSEventNotifyControl TESLoadGameEventSink::ProcessEvent(const TESLoadGameEvent& a_event, BSTEventSource<TESLoadGameEvent>* a_source) {
	//initSpecialHooks();
	return BSEventNotifyControl::kContinue;
}

void PlayerUpdate_Hook(void* player, float a1) {
	if (processCurrentScope && readyForRender && (ignore == false)) {
		//ScopeRendererManager::RenderHelper(true);
	}
	return;
}

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
	if (pc) {
		PlayerAnimGraphEventSink* OnPlayerAnimGraphEventSink = ((PlayerAnimGraphEventSink*)((uintptr_t)pc + 0x38));
		OnPlayerAnimGraphEventSink->HookSink();
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
void initSpecialHooks()  // TODO - This function might be called more than once? should we keep track of created things?
{
	TrySpecialHooks();
	logInfo(";=========================== Special Hooks Install Complete ===========================;");
	print_map(std::as_const(hookedList));
	logInfo(";======================================================================================;");
}
