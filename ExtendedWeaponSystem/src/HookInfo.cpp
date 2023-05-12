#include "HookInfo.h"

void HookInfo::ClearHookInfo() {
	HookInfo& Info = HookInfo::getInstance();

	Info.fnPlayerAnimationGraphEventHash.clear();
	Info.fnPlayerAttackHash.clear();
	Info.fnPlayerReadyWeaponHash.clear();
	Info.fnPlayerSetIronSightsHash.clear();

	if (!Info.hookedList.empty()) {
		for (const std::pair<const char*, bool>& n : Info.hookedList) {
			Info.hookedList[n.first] = false;
		}
	}
}

HookInfo& HookInfo::getInstance() {
	static HookInfo instance;
	return instance;
}
