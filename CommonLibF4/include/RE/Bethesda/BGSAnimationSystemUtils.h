#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSTSmartPointer.h"

namespace RE
{

	class NiAVObject;
	class TESObjectREFR;
	class BSAnimationGraphManager;

	namespace BGSAnimationSystemUtils
	{
		inline bool NotifySinksAnimEvent(BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr, const char* a_event, const char* a_argument, TESObjectREFR* a_reference)
		{
			using func_t = decltype(&BGSAnimationSystemUtils::NotifySinksAnimEvent);
			REL::Relocation<func_t> func{ REL::ID(5426) };
			return func(a_animGraphMgr, a_event, a_argument, a_reference);
		}
	}
}
