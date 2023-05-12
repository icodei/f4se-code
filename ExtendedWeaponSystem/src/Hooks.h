#pragma once
#include "Global.h"

class MenuOpenCloseEventSink : public BSTEventSink<MenuOpenCloseEvent> {
public:
	virtual ~MenuOpenCloseEventSink() {}
	virtual BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(MenuOpenCloseEventSink);
};

class PlayerAmmoCountEventSink : public BSTEventSink<PlayerAmmoCountEvent> {
public:
	virtual ~PlayerAmmoCountEventSink() {}
	virtual BSEventNotifyControl ProcessEvent(const PlayerAmmoCountEvent& a_event, BSTEventSource<PlayerAmmoCountEvent>* a_source) override;

	static BSTEventSource<PlayerAmmoCountEvent>* GetEventSource();

	F4_HEAP_REDEFINE_NEW(PlayerAmmoCountEventSink);
};

class PlayerSetWeaponStateEventSink : public BSTEventSink<PlayerSetWeaponStateEvent> {
public:
	virtual ~PlayerSetWeaponStateEventSink() {}
	virtual BSEventNotifyControl ProcessEvent(const PlayerSetWeaponStateEvent& a_event, BSTEventSource<PlayerSetWeaponStateEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(PlayerSetWeaponStateEventSink);
};

class PlayerWeaponReloadEventSink : public BSTEventSink<PlayerWeaponReloadEvent> {
public:
	virtual ~PlayerWeaponReloadEventSink() {}
	virtual BSEventNotifyControl ProcessEvent(const PlayerWeaponReloadEvent& a_event, BSTEventSource<PlayerWeaponReloadEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(PlayerWeaponReloadEventSink);
};

class TESEquipEventSink : public BSTEventSink<TESEquipEvent> {
public:
	virtual ~TESEquipEventSink() {}
	virtual BSEventNotifyControl ProcessEvent(const TESEquipEvent& a_event, BSTEventSource<TESEquipEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(TESEquipEventSink);
};

class TESFurnitureEventSink : public BSTEventSink<TESFurnitureEvent> {
public:
	virtual ~TESFurnitureEventSink() {}
	virtual BSEventNotifyControl ProcessEvent(const TESFurnitureEvent& a_event, BSTEventSource<TESFurnitureEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(TESFurnitureEventSink);
};

class TESLoadGameEventSink : public BSTEventSink<TESLoadGameEvent> {
public:
	virtual ~TESLoadGameEventSink() {}
	virtual BSEventNotifyControl ProcessEvent(const TESLoadGameEvent& a_event, BSTEventSource<TESLoadGameEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(TESLoadGameEventSink);
};

/*;========================================================================================================================================================;*/

class PlayerAnimationGraphEventHandler {
public:
	~PlayerAnimationGraphEventHandler() {}
	BSEventNotifyControl HookedProcessEvent(const BSAnimationGraphEvent& a_event, BSTEventSource<BSAnimationGraphEvent>* a_source);
	void HookSink();

	using FnProcessEvent = decltype(&HookedProcessEvent);

	F4_HEAP_REDEFINE_NEW(PlayerAnimationGraphEventHandler);
};

class PlayerAttackHandler : public HeldStateHandler {
public:
	PlayerAttackHandler() = delete;
	PlayerAttackHandler(PlayerControlsData& a_data) :
		HeldStateHandler(a_data) {}

	virtual ~PlayerAttackHandler() {}
	virtual void HandleButtonEvent(const ButtonEvent* inputEvent) override;

	void DoLeftAttack();
	void DoRightAttack();
	void HandleDualAttack(const ButtonEvent* inputEvent);
	void HandleLeftAttack(const ButtonEvent* inputEvent);
	void HandleRightAttack(const ButtonEvent* inputEvent);

	F4_HEAP_REDEFINE_NEW(PlayerAttackHandler);
};

class PlayerAttackHandlerHook {
public:
	~PlayerAttackHandlerHook() {}
	void HookedHandleButtonEvent(const ButtonEvent* inputEvent);
	void HookSink();

	using FnHandleButtonEvent = decltype(&HookedHandleButtonEvent);

	F4_HEAP_REDEFINE_NEW(PlayerAttackHandlerHook);
};

class PlayerReadyWeaponHandler : public PlayerInputHandler {
public:
	PlayerReadyWeaponHandler() = delete;
	PlayerReadyWeaponHandler(PlayerControlsData& a_data) :
		PlayerInputHandler(a_data) {}

	virtual ~PlayerReadyWeaponHandler() {}
	virtual void HandleButtonEvent(const ButtonEvent* inputEvent) override;

	F4_HEAP_REDEFINE_NEW(PlayerReadyWeaponHandler);
};

class PlayerReadyWeaponHandlerHook {
public:
	~PlayerReadyWeaponHandlerHook() {}
	void HookedHandleButtonEvent(const ButtonEvent* inputEvent);
	void HookSink();

	using FnHandleButtonEvent = decltype(&HookedHandleButtonEvent);

	F4_HEAP_REDEFINE_NEW(PlayerReadyWeaponHandlerHook);
};

class PlayerSightedStateChangeHandler {
public:
	~PlayerSightedStateChangeHandler() {}
	bool HookedSetInIronSights(bool EnterIronSights);
	void HookSink();

	using FnSetInIronSights = decltype(&HookedSetInIronSights);

	F4_HEAP_REDEFINE_NEW(PlayerSightedStateChangeHandler);
};

void initHooks();
void initSpecialHooks();
