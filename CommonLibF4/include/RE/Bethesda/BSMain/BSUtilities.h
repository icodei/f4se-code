#pragma once

#include "RE/Bethesda/BSSystem/BSFixedString.h"

namespace RE
{

	class NiAVObject;

	namespace BSUtilities
	{
		inline NiAVObject* GetObjectByName(NiAVObject* a_object, const BSFixedString& a_name, bool tryInternal, bool dontAttach)
		{
			using func_t = decltype(&BSUtilities::GetObjectByName);
			REL::Relocation<func_t> func{ REL::ID(843650) };
			return func(a_object, a_name, tryInternal, dontAttach);
		}

		inline NiAVObject* GetObjectByString(NiAVObject* a_object, const char *a_name, bool tryInternal, bool dontAttach)
		{
			const BSFixedString string(a_name);
			using func_t = decltype(&BSUtilities::GetObjectByName);
			REL::Relocation<func_t> func{ REL::ID(843650) };
			return func(a_object, string, tryInternal, dontAttach);
		}
	}
}
