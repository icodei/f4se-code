#pragma once
#include "Global.h"

#include "Hooks.h"

struct HookInfo {
private:
	HookInfo() {}
	~HookInfo() { ClearHookInfo(); }

public:
	HookInfo(HookInfo const&) = delete;
	void operator=(HookInfo const&) = delete;

	//static functions
	static void ClearHookInfo();
	static HookInfo& getInstance();

	//members
	uintptr_t PCUpdateMainThreadOrig;

	std::unordered_map<uintptr_t, PlayerAnimationGraphEventHandler::FnProcessEvent> fnPlayerAnimationGraphEventHash;
	std::unordered_map<uintptr_t, PlayerAttackHandlerHook::FnHandleButtonEvent> fnPlayerAttackHash;
	std::unordered_map<uintptr_t, PlayerReadyWeaponHandlerHook::FnHandleButtonEvent> fnPlayerReadyWeaponHash;
	std::unordered_map<uintptr_t, PlayerSightedStateChangeHandler::FnSetInIronSights> fnPlayerSetIronSightsHash;
	std::unordered_map<const char*, bool> hookedList;
};
