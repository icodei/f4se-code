#pragma once

class TESEquipEventSink : public BSTEventSink<TESEquipEvent> {
protected:
	virtual ~TESEquipEventSink() { };
	virtual EventResult ReceiveEvent(TESEquipEvent* evn, void* dispatcher) override;
};

class PlayerAmmoCountEventSink : public BSTEventSink<PlayerAmmoCountEvent> {
public:
	virtual ~PlayerAmmoCountEventSink() { };
	virtual EventResult ReceiveEvent(PlayerAmmoCountEvent* evn, void* dispatcher) override;
};

class PlayerWeaponReloadEventSink : public BSTEventSink<PlayerWeaponReloadEvent> {
public:
	virtual ~PlayerWeaponReloadEventSink() { };
	virtual EventResult ReceiveEvent(PlayerWeaponReloadEvent* evn, void* dispatcher) override;
};

class PlayerSetWeaponStateEventSink : public BSTEventSink<PlayerSetWeaponStateEvent> {
public:
	virtual ~PlayerSetWeaponStateEventSink() { };
	virtual EventResult ReceiveEvent(PlayerSetWeaponStateEvent* evn, void* dispatcher) override;
};

class TESLoadGameHandler : public BSTEventSink<TESLoadGameEvent> {
public:
	virtual ~TESLoadGameHandler() { };
	virtual EventResult ReceiveEvent(TESLoadGameEvent* evn, void* dispatcher) override;
};

class BGSOnPlayerUseWorkBenchEventSink : public BSTEventSink<BGSOnPlayerUseWorkBenchEvent> {
public:
	virtual ~BGSOnPlayerUseWorkBenchEventSink() { };
	virtual EventResult ReceiveEvent(BGSOnPlayerUseWorkBenchEvent* evn, void* dispatcher) override;
};

class TESFurnitureEventSink : public BSTEventSink<TESFurnitureEvent> {
public:
	virtual ~TESFurnitureEventSink() { };
	virtual EventResult ReceiveEvent(TESFurnitureEvent* evn, void* dispatcher) override;
};

bool Install();
bool RegisterAfterLoadEvents();