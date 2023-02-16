#pragma once

BSTEventDispatcher<void*>* GetGlobalEventDispatcher(BSTGlobalEvent* globalEvents, const char* dispatcherName);


class BSAnimationGraphEvent {
public:
	TESObjectREFR*	refr;
	BSFixedString	name;
	BSFixedString	args;
};

typedef EventResult(*_PlayerAnimGraphEvent_ReceiveEvent)(void*, BSAnimationGraphEvent*, void*);


bool Install();
