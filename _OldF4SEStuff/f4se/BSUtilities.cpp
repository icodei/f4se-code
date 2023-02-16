#include "f4se/BSUtilities.h"

namespace BSUtilities {
	NiAVObject* GetObjectByName(NiAVObject* a_object, const BSFixedString& a_name, bool a3, bool a4) {
		NiAVObject* obj = GetObjectByName_Internal(a_object, a_name, a3, a4);
		return obj;
	}
	RelocAddr<_GetObjectByName> GetObjectByName_Internal(0x01C93980);
}
