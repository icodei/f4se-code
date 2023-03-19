#pragma once

#include "RE/Bethesda/BSContainer.h"
#include "RE/Bethesda/BSCore/BSTEvent.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"

namespace RE
{
	class NiAVObject;
	class TESObjectREFR;
	class BSAnimationGraphManager;

	struct BSAnimationGraphEvent;

	namespace AnimationSystemUtils
	{
		/*
		template <class T>
		BSContainer::ForEachResult SetGraphVariableFunctor(std::function<bool(BSFixedString&, T&)>& a_functor)
		{
			return;
		}

		template <class T>
		BSContainer::ForEachResult GetEventSourcePointersFunctor(std::function<void(BSScrapArray<BSTEventSource<BSAnimationGraphEvent>*>&)>& a_functor)
		{
			return;
		}

		template <class T>
		bool GetEventSourcePointerFromGraph(BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr, std::uint32_t a_num, BSTEventSource<T>*& a_source)
		{
			return false;
		}
		*/

		inline bool GetEventSourcePointerFromGraphManager(BSTSmartPointer<BSAnimationGraphManager>& a_animGraphMgr, std::uint32_t a_num, BSTEventSource<BSAnimationGraphEvent>*& a_source)
		{
			using func_t = decltype(&AnimationSystemUtils::GetEventSourcePointerFromGraphManager);
			REL::Relocation<func_t> func{ REL::ID(323983) };
			return func(a_animGraphMgr, a_num, a_source);
		}

		inline bool GetEventSourcePointerFromReference(TESObjectREFR& a_object, BSTEventSource<BSAnimationGraphEvent>*& a_source, std::uint32_t a_num)
		{
			using func_t = decltype(&AnimationSystemUtils::GetEventSourcePointerFromReference);
			REL::Relocation<func_t> func{ REL::ID(137530) };
			return func(a_object, a_source, a_num);
		}

		inline bool ActivateGamebryoSequence(NiAVObject* a_object, const BSFixedString& a_name)
		{
			using func_t = decltype(&AnimationSystemUtils::ActivateGamebryoSequence);
			REL::Relocation<func_t> func{ REL::ID(628888) };
			return func(a_object, a_name);
		}
	}
}
