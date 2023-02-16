#pragma once
#include <f4se/GameCamera.h>
#include <f4se/GameData.h>
#include <f4se/GameEvents.h>
#include <f4se/GameExtraData.h>
#include <f4se/GameFormComponents.h>
#include <f4se/GameForms.h>
#include <f4se/GameInput.h>
#include <f4se/GameObjects.h>
#include <f4se/GameReferences.h>
#include <f4se/GameRTTI.h>
#include <f4se/GameTypes.h>
#include <f4se/PapyrusVM.h>
#include <f4se/xbyak/xbyak.h>

#include "f4se_common/f4se_version.h"
#include "f4se_common/SafeWrite.h"

#include "Util.h"
#include "Hooks.h"

#include <chrono>
#include <ctime>
#include <string>  
#include <iostream> 
#include <sstream> 
#include <stdio.h>
#include <time.h>


#define PLUGIN_NAME	"AnimationEventLog"
#define PLUGIN_VERSION MAKE_EXE_VERSION(1, 0, 0)

extern bool logEnabled;
extern bool eventLogEnabled;

#define GET_EVENT_DISPATCHER(EventName) (BSTEventDispatcher<EventName>*) GetGlobalEventDispatcher(*g_globalEvents, #EventName);

