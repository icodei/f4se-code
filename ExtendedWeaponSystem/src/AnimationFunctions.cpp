#include "Global.h"

void SetPlayerAnimationVariableBool(BSFixedString& asVariableName, bool newVal) {
	(pc)->SetGraphVariableBool(asVariableName, newVal);
}

void SetPlayerAnimationVariableInt(BSFixedString& asVariableName, int newVal) {
	(pc)->SetGraphVariableInt(asVariableName, newVal);
}

void SetPlayerAnimationVariableFloat(BSFixedString& asVariableName, float newVal) {
	(pc)->SetGraphVariableFloat(asVariableName, newVal);
}

void ReloadSubgraph() {
	//(taskInterface)->AddTaskFunc([]() {
	//	
	//});
}

/*
code from Bingle
void ReloadSubgraph() {
	uint64_t oldSubgraph = p->currentProcess->middleHigh->currentWeaponSubGraphID[1].identifier;
	p->HandleItemEquip(false);
	std::thread([oldSubgraph]() -> void {
		int timeout = 0;
		while (oldSubgraph == p->currentProcess->middleHigh->currentWeaponSubGraphID[1].identifier && timeout < 100) {
			++timeout;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		*(float*)((uintptr_t)pcam->cameraStates[CameraState::kFirstPerson].get() + 0x78) = lastSightedTransition;
		taskInterface->AddTask([]() {
			F4::BGSAnimationSystemUtils::InitializeActorInstant(*p, false);
			if (sideAim) {
				NotifyWeaponGraphManager("Extend");
			}
			if (wantSighted && !UI::GetSingleton()->GetMenu("ScopeMenu").get()) {
				pcon->DoAction(DEFAULT_OBJECT::kActionSighted, 2);
				p->SetGraphVariableInt("iSyncWeaponDrawState", 1);
				p->SetGraphVariableInt("iSyncSightedState", 1);
				p->UpdateAnimation(0.05f);
				NiUpdateData ud = NiUpdateData();
				ud.unk10 = 0x303;
				p->Get3D()->UpdateSelectedDownwardPass(ud, 0);
			}
			});
		}).detach();
}

suggestions by Bingle
BGSAnimationSystemUtils::InitializeActorInstant
Actor::HandleItemEquip
AIProcess::RequestLoadAnimationsForWeaponChange
*/
