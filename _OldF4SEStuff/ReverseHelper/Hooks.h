#pragma once

BSTEventDispatcher<void*>* GetGlobalEventDispatcher(BSTGlobalEvent* globalEvents, const char* dispatcherName);


class TESLoadGameHandler : public BSTEventSink<TESLoadGameEvent> {
public:
	virtual ~TESLoadGameHandler() { };
	virtual EventResult ReceiveEvent(TESLoadGameEvent* evn, void* dispatcher) override;
};

typedef EventResult(*_MenuOpenCloseEvent_ReceiveEvent)(void*, MenuOpenCloseEvent*, void*);

bool Install();
bool RegisterAfterLoadEvents();
