#pragma once
#include "Global.h"

class BGSOnPlayerUseWorkBenchEventSink : public BSTEventSink<BGSOnPlayerUseWorkBenchEvent> {
public:
	virtual ~BGSOnPlayerUseWorkBenchEventSink(){};
	virtual BSEventNotifyControl ProcessEvent(const BGSOnPlayerUseWorkBenchEvent& a_event, BSTEventSource<BGSOnPlayerUseWorkBenchEvent>* a_source) override;
};

class MenuOpenCloseEventSink : public BSTEventSink<MenuOpenCloseEvent> {
public:
	virtual ~MenuOpenCloseEventSink(){};
	virtual BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_source) override;
};

class PlayerAmmoCountEventSink : public BSTEventSink<PlayerAmmoCountEvent> {
public:
	virtual ~PlayerAmmoCountEventSink(){};
	virtual BSEventNotifyControl ProcessEvent(const PlayerAmmoCountEvent& a_event, BSTEventSource<PlayerAmmoCountEvent>* a_source) override;

	static BSTEventSource<PlayerAmmoCountEvent>* GetEventSource();
	F4_HEAP_REDEFINE_NEW(PlayerAmmoCountEventSink);
};

class PlayerAnimGraphEventSink {
public:
	typedef BSEventNotifyControl (PlayerAnimGraphEventSink::*FnProcessEvent)(const BSAnimationGraphEvent& a_event, BSTEventSource<BSAnimationGraphEvent>* a_source);
	BSEventNotifyControl HookedProcessEvent(const BSAnimationGraphEvent& a_event, BSTEventSource<BSAnimationGraphEvent>* a_source);
	void HookSink();

protected:
	static std::unordered_map<uintptr_t, FnProcessEvent> fnHash;
};

class PlayerSetWeaponStateEventSink : public BSTEventSink<PlayerSetWeaponStateEvent> {
public:
	virtual ~PlayerSetWeaponStateEventSink(){};
	virtual BSEventNotifyControl ProcessEvent(const PlayerSetWeaponStateEvent& a_event, BSTEventSource<PlayerSetWeaponStateEvent>* a_source) override;
};

class PlayerWeaponReloadEventSink : public BSTEventSink<PlayerWeaponReloadEvent> {
public:
	virtual ~PlayerWeaponReloadEventSink(){};
	virtual BSEventNotifyControl ProcessEvent(const PlayerWeaponReloadEvent& a_event, BSTEventSource<PlayerWeaponReloadEvent>* a_source) override;
};

class TESEquipEventSink : public BSTEventSink<TESEquipEvent> {
public:
	virtual ~TESEquipEventSink(){};
	virtual BSEventNotifyControl ProcessEvent(const TESEquipEvent& a_event, BSTEventSource<TESEquipEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(TESEquipEventSink);
};

class TESFurnitureEventSink : public BSTEventSink<TESFurnitureEvent> {
public:
	virtual ~TESFurnitureEventSink(){};
	virtual BSEventNotifyControl ProcessEvent(const TESFurnitureEvent& a_event, BSTEventSource<TESFurnitureEvent>* a_source) override;
};

class TESLoadGameEventSink : public BSTEventSink<TESLoadGameEvent> {
public:
	virtual ~TESLoadGameEventSink(){};
	virtual BSEventNotifyControl ProcessEvent(const TESLoadGameEvent& a_event, BSTEventSource<TESLoadGameEvent>* a_source) override;
};

static std::unordered_map<const char*, bool> hookedList;

void initHooks();
void initSpecialHooks();
