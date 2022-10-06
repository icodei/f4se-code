#pragma once
#include "f4se/GameAPI.h"
#include "f4se/GameCamera.h"
#include "f4se/GameData.h"
#include "f4se/GameEvents.h"
#include "f4se/GameExtraData.h"
#include "f4se/GameFormComponents.h"
#include "f4se/GameForms.h"
#include "f4se/GameInput.h"
#include "f4se/GameObjects.h"
#include "f4se/GameReferences.h"
#include "f4se/GameRTTI.h"
#include "f4se/GameStreams.h"
#include "f4se/GameTypes.h"
#include "f4se/PapyrusVM.h"
#include "f4se/xbyak/xbyak.h"
#include "f4se/NiNodes.h"
#include "f4se/NiObjects.h"
#include "f4se/NiProperties.h"
#include "f4se/NiTypes.h"
#include "f4se/NiMaterials.h"
#include "f4se/BSGeometry.h"

#include "f4se_common/f4se_version.h"
#include "f4se_common/Utilities.h"
#include "f4se_common/Relocation.h"
#include "f4se_common/BranchTrampoline.h"
#include "f4se_common/SafeWrite.h"

#include "Util.h"
#include "Hooks.h"
#include "Interface3D.h"
#include "Extras.h"

#include <chrono>
#include <ctime>
#include <string>  
#include <iostream> 
#include <sstream> 
#include <stdio.h>
#include <time.h>


#define PLUGIN_NAME	"ExtendedWeaponSystem"
#define PLUGIN_VERSION MAKE_EXE_VERSION(1, 0, 0)

extern bool logEnabled;
extern bool reloadStarted;
extern bool reloadEnd;
extern bool processCurrentWeap;
extern bool processCurrentScope;
extern bool isEmptyReload;
extern bool oncePerSession;

extern int totalAmmoCount;
extern int currentAmmoCount;
extern int ammoCapacity;
extern int incrementor;
extern int toAdd;

extern BSGeometry* ScopeTextureLoader;
extern BSEffectShaderData* shadeData;
extern TESEffectShader* ThermalFXS;
extern BGSKeyword* reloadSequentialKeyword;
extern BGSKeyword* ThermalScopeKeyword;
extern TESObjectWEAP::InstanceData* weapInstance;

#define GET_EVENT_DISPATCHER(EventName) (BSTEventDispatcher<EventName>*) GetGlobalEventDispatcher(*g_globalEvents, #EventName);


