#pragma once
#include "RE/Bethesda/BSMain/IOManager.h"
#include "RE/Bethesda/BSCore/MemoryDefs.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class QueuedChildren;

	class QueuedFile : public IOTask
	{
	public:
		static constexpr auto RTTI{ RTTI::QueuedFile };
		static constexpr auto VTABLE{ VTABLE::QueuedFile };

		virtual ~QueuedFile();

		//override
		virtual void Run(void) override;
		virtual void Finish(void) override;
		virtual void Cancel(BS_TASK_STATE,void *) override;
		virtual void Requeue(IO_TASK_PRIORITY) override;

		//add
		virtual void DoOnQueueMe(void);
		virtual void DoOnChildrenFinished(void);
		virtual void DoOnTaskFinished(void);

		//members
		MEM_CONTEXT eContext;
		NiPointer<QueuedFile> spParent;
		QueuedChildren* pChildren;
		volatile std::uint32_t uiState;
	};
}
