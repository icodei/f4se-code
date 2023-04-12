#pragma once
#include "Hooks.h"
#include "Util.h"

extern F4SE::PluginHandle g_pluginHandle;
extern const F4SE::MessagingInterface* g_messaging;
extern const F4SE::TaskInterface* g_taskInterface;
extern const F4SE::Trampoline* g_trampoline;

#define GET_EVENT_SOURCE(EventName) (BSTEventSource<EventName>*)GetGlobalEventSource(BSTGlobalEvent_OLD::GetSingleton(), #EventName);

#define _BYTE std::uint8_t
#define _WORD std::uint16_t
#define _DWORD std::uint32_t
#define _QWORD std::uint64_t

#define BYTEn(x, n) (*((_BYTE*)&(x) + n))
#define WORDn(x, n) (*((_WORD*)&(x) + n))
#define DWORDn(x, n) (*((_DWORD*)&(x) + n))

#define LODWORD(x) DWORDn(x, LOW_IND(x, _DWORD))
#define HIDWORD(x) DWORDn(x, HIGH_IND(x, _DWORD))
#define BYTE0(x) BYTEn(x, 0)
#define BYTE1(x) BYTEn(x, 1)  // byte 1 (counting from 0)
#define BYTE2(x) BYTEn(x, 2)
#define BYTE3(x) BYTEn(x, 3)
#define BYTE4(x) BYTEn(x, 4)
#define BYTE5(x) BYTEn(x, 5)
#define BYTE6(x) BYTEn(x, 6)
#define BYTE7(x) BYTEn(x, 7)
#define BYTE8(x) BYTEn(x, 8)
#define BYTE9(x) BYTEn(x, 9)
#define BYTE10(x) BYTEn(x, 10)
#define BYTE11(x) BYTEn(x, 11)
#define BYTE12(x) BYTEn(x, 12)
#define BYTE13(x) BYTEn(x, 13)
#define BYTE14(x) BYTEn(x, 14)
#define BYTE15(x) BYTEn(x, 15)
#define WORD1(x) WORDn(x, 1)
#define WORD2(x) WORDn(x, 2)  // third word of the object, unsigned
#define WORD3(x) WORDn(x, 3)
#define WORD4(x) WORDn(x, 4)
#define WORD5(x) WORDn(x, 5)
#define WORD6(x) WORDn(x, 6)
#define WORD7(x) WORDn(x, 7)
