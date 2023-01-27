#include "Global.h"

typedef void(*_SetAnimationVariableBoolPapyrus)(VirtualMachine* vm, UInt32 stackId, TESObjectREFR* ref, BSFixedString& asVariableName, bool newVal);
RelocAddr <_SetAnimationVariableBoolPapyrus> SetAnimationVariableBoolPapyrusInternal(0x140EB30);
void SetAnimationVariableBoolPapyrus(TESObjectREFR* ref, BSFixedString& asVariableName, bool newVal) {
	SetAnimationVariableBoolPapyrusInternal((*g_gameVM)->m_virtualMachine, 1, ref, asVariableName, newVal);
}

typedef void(*_SetAnimationVariableIntPapyrus)(VirtualMachine* vm, UInt32 stackId, TESObjectREFR* ref, BSFixedString& asVariableName, int newVal);
RelocAddr <_SetAnimationVariableIntPapyrus> SetAnimationVariableIntPapyrusInternal(0x140EC70);
void SetAnimationVariableIntPapyrus(TESObjectREFR* ref, BSFixedString& asVariableName, int newVal) {
	SetAnimationVariableIntPapyrusInternal((*g_gameVM)->m_virtualMachine, 1, ref, asVariableName, newVal);
}

typedef void(*_SetAnimationVariableFloatPapyrus)(VirtualMachine* vm, UInt32 stackId, TESObjectREFR* ref, BSFixedString& asVariableName, float newVal);
RelocAddr <_SetAnimationVariableFloatPapyrus> SetAnimationVariableFloatPapyrusInternal(0x140EBD0);
void SetAnimationVariableFloatPapyrus(TESObjectREFR* ref, BSFixedString& asVariableName, float newVal) {
	SetAnimationVariableFloatPapyrusInternal((*g_gameVM)->m_virtualMachine, 1, ref, asVariableName, newVal);
}

typedef void(*_SetSubGraphFloatVariablePapyrus)(VirtualMachine* vm, UInt32 stackId, Actor* actor, BSFixedString asVariableName, float newVal);
RelocAddr <_SetSubGraphFloatVariablePapyrus> SetSubGraphFloatVariablePapyrusInternal(0x138B430);
void SetSubGraphFloatVariablePapyrus(Actor* actor, BSFixedString& asVariableName, float newVal) {
	SetSubGraphFloatVariablePapyrusInternal((*g_gameVM)->m_virtualMachine, 0, actor, asVariableName, newVal);
}

#include "f4se/PluginManager.h"

void ReloadSubgraph() {
	(&g_F4SETaskInterface)->AddTaskFunc([]() {
		
	});
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