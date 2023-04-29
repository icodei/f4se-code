#pragma once
#include "RE/Shared/Animation/IAnimationGraphManagerHolder.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class SimpleAnimationGraphManagerLoadingTask;

	class __declspec(novtable) SimpleAnimationGraphManagerHolder :
		public IAnimationGraphManagerHolder
	{
	public:
		static constexpr auto RTTI{ RTTI::SimpleAnimationGraphManagerHolder };
		static constexpr auto VTABLE{ VTABLE::SimpleAnimationGraphManagerHolder };

		virtual ~SimpleAnimationGraphManagerHolder() = default;  // 00

		// add
		virtual void BackgroundTaskFinishedLoading() { return; }  // 01

		bool CreateBackgroundSimpleManager(NiAVObject& a_object, IO_TASK_PRIORITY a_priority)
		{
			using func_t = decltype(&SimpleAnimationGraphManagerHolder::CreateBackgroundSimpleManager);
			REL::Relocation<func_t> func{ REL::ID(505018) };
			return func(this, a_object, a_priority);
		}

		// members
		BSTSmartPointer<BSAnimationGraphManager> animationGraphManager;  // 08
		NiPointer<SimpleAnimationGraphManagerLoadingTask> loadingTask;   // 10
	};
	static_assert(sizeof(SimpleAnimationGraphManagerHolder) == 0x18);
}
