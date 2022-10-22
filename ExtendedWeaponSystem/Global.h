#pragma once
#include "f4se/xbyak/xbyak.h"
#include "f4se/PapyrusVM.h"
#include "f4se/NiTypes.h"
#include "f4se/NiTextures.h"
#include "f4se/NiRTTI.h"
#include "f4se/NiProperties.h"
#include "f4se/NiObjects.h"
#include "f4se/NiNodes.h"
#include "f4se/NiMaterials.h"
#include "f4se/GameTypes.h"
#include "f4se/GameStreams.h"
#include "f4se/GameRTTI.h"
#include "f4se/GameReferences.h"
#include "f4se/GameObjects.h"
#include "f4se/GameInput.h"
#include "f4se/GameForms.h"
#include "f4se/GameFormComponents.h"
#include "f4se/GameExtraData.h"
#include "f4se/GameEvents.h"
#include "f4se/GameData.h"
#include "f4se/GameCamera.h"
#include "f4se/GameAPI.h"
#include "f4se/BSGraphics.h"
#include "f4se/BSGeometry.h"

#include "f4se_common/BranchTrampoline.h"
#include "f4se_common/f4se_version.h"
#include "f4se_common/Relocation.h"
#include "f4se_common/SafeWrite.h"
#include "f4se_common/Utilities.h"

#include "Extras.h"
#include "Hooks.h"
#include "Interface3D.h"
#include "Util.h"
#include "CustomRenderer.h"

#include <chrono>
#include <ctime>
#include <iostream> 
#include <sstream> 
#include <stdio.h>
#include <string>  
#include <time.h>


#define PLUGIN_NAME	"ExtendedWeaponSystem"
#define PLUGIN_VERSION MAKE_EXE_VERSION(1, 0, 0)

extern bool isEmptyReload;
extern bool logEnabled;
extern bool oncePerSession;
extern bool playerIsInWorkbench;
extern bool processCurrentScope;
extern bool processCurrentWeap;
extern bool reloadEnd;
extern bool reloadStarted;

extern int ammoCapacity;
extern int currentAmmoCount;
extern int incrementor;
extern int toAdd;
extern int totalAmmoCount;


extern BGSKeyword* reloadSequentialKeyword;
extern BGSKeyword* ThermalScopeKeyword;
extern TESObjectWEAP::InstanceData* currentWeapInstance;

//This stuff is for the thermal scope shader and geom
extern BSGeometry* ScopeTextureLoader;
extern BSEffectShaderData* effectShaderData;
extern TESEffectShader* ThermalFXS;

#define GET_EVENT_DISPATCHER(EventName) (BSTEventDispatcher<EventName>*) GetGlobalEventDispatcher(*g_globalEvents, #EventName);

#define _BYTE  UInt8
#define _WORD  UInt16
#define _DWORD UInt32
#define _QWORD UInt64

#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define DWORDn(x, n)  (*((_DWORD*)&(x)+n))

#define LODWORD(x) DWORDn(x,LOW_IND(x,_DWORD))
#define HIDWORD(x) DWORDn(x,HIGH_IND(x,_DWORD))
#define BYTE0(x)   BYTEn(x,  0)
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE3(x)   BYTEn(x,  3)
#define BYTE4(x)   BYTEn(x,  4)
#define BYTE5(x)   BYTEn(x,  5)
#define BYTE6(x)   BYTEn(x,  6)
#define BYTE7(x)   BYTEn(x,  7)
#define BYTE8(x)   BYTEn(x,  8)
#define BYTE9(x)   BYTEn(x,  9)
#define BYTE10(x)  BYTEn(x, 10)
#define BYTE11(x)  BYTEn(x, 11)
#define BYTE12(x)  BYTEn(x, 12)
#define BYTE13(x)  BYTEn(x, 13)
#define BYTE14(x)  BYTEn(x, 14)
#define BYTE15(x)  BYTEn(x, 15)
#define WORD1(x)   WORDn(x,  1)
#define WORD2(x)   WORDn(x,  2)         // third word of the object, unsigned
#define WORD3(x)   WORDn(x,  3)
#define WORD4(x)   WORDn(x,  4)
#define WORD5(x)   WORDn(x,  5)
#define WORD6(x)   WORDn(x,  6)
#define WORD7(x)   WORDn(x,  7)

#define FToRGB 0.0039215689