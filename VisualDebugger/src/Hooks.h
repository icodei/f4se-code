#pragma once
#include "Global.h"

class MenuOpenCloseEventSink : public BSTEventSink<MenuOpenCloseEvent> {
public:
	virtual ~MenuOpenCloseEventSink(){};
	virtual BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(MenuOpenCloseEventSink);
};

class TESLoadGameEventSink : public BSTEventSink<TESLoadGameEvent> {
public:
	virtual ~TESLoadGameEventSink(){};
	virtual BSEventNotifyControl ProcessEvent(const TESLoadGameEvent& a_event, BSTEventSource<TESLoadGameEvent>* a_source) override;

	F4_HEAP_REDEFINE_NEW(TESLoadGameEventSink);
};

static std::unordered_map<const char*, bool> hookedList;

void initHooks();
void initSpecialHooks();
