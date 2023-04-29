#pragma once
#include "Global.h"

class MenuOpenCloseEventSink : public BSTEventSink<MenuOpenCloseEvent> {
public:
	virtual ~MenuOpenCloseEventSink(){}
	virtual BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(MenuOpenCloseEventSink);
};

class PlayerAmmoCountEventSink : public BSTEventSink<PlayerAmmoCountEvent> {
public:
	virtual ~PlayerAmmoCountEventSink(){}
	virtual BSEventNotifyControl ProcessEvent(const PlayerAmmoCountEvent& a_event, BSTEventSource<PlayerAmmoCountEvent>* a_source) override;

	static BSTEventSource<PlayerAmmoCountEvent>* GetEventSource();

	F4_HEAP_REDEFINE_NEW(PlayerAmmoCountEventSink);
};

class PlayerSetWeaponStateEventSink : public BSTEventSink<PlayerSetWeaponStateEvent> {
public:
	virtual ~PlayerSetWeaponStateEventSink(){}
	virtual BSEventNotifyControl ProcessEvent(const PlayerSetWeaponStateEvent& a_event, BSTEventSource<PlayerSetWeaponStateEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(PlayerSetWeaponStateEventSink);
};

class PlayerWeaponReloadEventSink : public BSTEventSink<PlayerWeaponReloadEvent> {
public:
	virtual ~PlayerWeaponReloadEventSink(){}
	virtual BSEventNotifyControl ProcessEvent(const PlayerWeaponReloadEvent& a_event, BSTEventSource<PlayerWeaponReloadEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(PlayerWeaponReloadEventSink);
};

class TESEquipEventSink : public BSTEventSink<TESEquipEvent> {
public:
	virtual ~TESEquipEventSink(){}
	virtual BSEventNotifyControl ProcessEvent(const TESEquipEvent& a_event, BSTEventSource<TESEquipEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(TESEquipEventSink);
};

class TESFurnitureEventSink : public BSTEventSink<TESFurnitureEvent> {
public:
	virtual ~TESFurnitureEventSink(){}
	virtual BSEventNotifyControl ProcessEvent(const TESFurnitureEvent& a_event, BSTEventSource<TESFurnitureEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(TESFurnitureEventSink);
};

class TESLoadGameEventSink : public BSTEventSink<TESLoadGameEvent> {
public:
	virtual ~TESLoadGameEventSink(){}
	virtual BSEventNotifyControl ProcessEvent(const TESLoadGameEvent& a_event, BSTEventSource<TESLoadGameEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(TESLoadGameEventSink);
};

/*;========================================================================================================================================================;*/

class PlayerAnimGraphEventHandler {
public:
	BSEventNotifyControl HookedProcessEvent(const BSAnimationGraphEvent& a_event, BSTEventSource<BSAnimationGraphEvent>* a_source);
	void HookSink();

private:
	using FnProcessEvent = decltype(&HookedProcessEvent);

protected:
	static std::unordered_map<uintptr_t, FnProcessEvent> fnHash;
};

class PlayerAttackHandler : public AttackBlockHandler {
public:

	PlayerAttackHandler() = delete;
	PlayerAttackHandler(PlayerControlsData& a_data) : AttackBlockHandler(a_data){}

	virtual ~PlayerAttackHandler() {}
	virtual void HandleButtonEvent(const ButtonEvent*) override;

	void DoLeftAttack();
	void DoRightAttack();
	void HandleDualAttack(const ButtonEvent* inputEvent);
	void HandleLeftAttack(const ButtonEvent* inputEvent);
	void HandleRightAttack(const ButtonEvent* inputEvent);
	void HookedHandleButtonEvent(const ButtonEvent* inputEvent);
	void HookSink();

private:
	using FnHandleButtonEvent = decltype(&HookedHandleButtonEvent);

protected:
	static std::unordered_map<uintptr_t, FnHandleButtonEvent> fnHash;
};

class PlayerSightedStateChangeHandler {
public:
	static bool HookedExecuteHandler(void* a_handler, Actor& a_actor, BSFixedString& a_event);
	static void Hook();

private:
	using FnExecuteHandler = decltype(&HookedExecuteHandler);

protected:
	static FnExecuteHandler fnOriginal;
};

class PlayerWeaponAttachHandler {
public:
	static bool HookedExecuteHandler(void* a_handler, Actor& a_actor, BSFixedString& a_event);
	static void Hook();

private:
	using FnExecuteHandler = decltype(&HookedExecuteHandler);

protected:
	static FnExecuteHandler fnOriginal;
};

class PlayerWeaponDrawHandler {
public:
	static bool HookedExecuteHandler(void* a_handler, Actor& a_actor, BSFixedString& a_event);
	static void Hook();

private:
	using FnExecuteHandler = decltype(&HookedExecuteHandler);

protected:
	static FnExecuteHandler fnOriginal;
};

class PlayerWeaponSheatheHandler {
public:
	static bool HookedExecuteHandler(void* a_handler, Actor& a_actor, BSFixedString& a_event);
	static void Hook();

private:
	using FnExecuteHandler = decltype(&HookedExecuteHandler);

protected:
	static FnExecuteHandler fnOriginal;
};

static std::unordered_map<const char*, bool> hookedList;

void initHooks();
void initSpecialHooks();
