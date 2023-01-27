#pragma once
#include "f4se/GameTypes.h"
#include "f4se/NiObjects.h"

namespace BSUtilities {
	typedef NiAVObject* (*_GetObjectByName)(NiAVObject* a_object, const BSFixedString& a_name, bool a3, bool a4);
	NiAVObject* GetObjectByName(NiAVObject* a_object, const BSFixedString& a_name, bool a3, bool a4);
	extern RelocAddr<_GetObjectByName> GetObjectByName_Internal;
}
