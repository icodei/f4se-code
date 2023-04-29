#pragma once

namespace RE
{
	enum BS_TASK_STATE : std::int32_t
	{
		BS_TASK_STATE_PENDING = 0x0,
		BS_TASK_STATE_QUEUED = 0x1,
		BS_TASK_STATE_MOVING = 0x2,
		BS_TASK_STATE_RUNNING = 0x3,
		BS_TASK_STATE_FINISHED = 0x4,
		BS_TASK_STATE_COMPLETED = 0x5,
		BS_TASK_STATE_CANCELED = 0x6,
		BS_TASK_STATE_POST_PROCESSING = 0x7,
		BS_TASK_STATE_FORCE_DWORD = 0x7FFFFFFF,
	};

	enum class IO_TASK_PRIORITY : std::int32_t
	{
		IO_TASK_PRIORITY_CRITICAL = 0x0,
		IO_TASK_PRIORITY_VERY_HIGH = 0x1,
		IO_TASK_PRIORITY_HIGH = 0x2,
		IO_TASK_PRIORITY_MID = 0x3,
		IO_TASK_PRIORITY_LOW = 0x4,
		IO_TASK_PRIORITY_VERY_LOW = 0x5,
		IO_TASK_PRIORITY_COUNT = 0x6,
		IO_TASK_PRIORITY_INVALID = 0x7,
		IO_TASK_PRIORITY_HIGHEST = 0x0,
		IO_TASK_PRIORITY_LOWEST = 0x5,
	};

	class IOTask
	{
	public:
		static constexpr auto RTTI{ RTTI::IOTask };
		static constexpr auto VTABLE{ VTABLE::IOTask };

		virtual ~IOTask();
		virtual bool GetDescription(char*, std::uint32_t) const;
		virtual void Run(void);
		virtual void Finish() = 0;
		virtual void Cancel(BS_TASK_STATE, void*);
		virtual bool Process(void);
		virtual void PostProcess(void);
		virtual void Requeue(IO_TASK_PRIORITY);
		virtual void GenerateKey(void);
		virtual bool TryCompleteTask(void);

		//members
		std::int64_t iKey;
		IOTask* pLeft;
		IOTask* pRight;
		IOTask** ppRoot;
		std::uint32_t uiParentAndBlack;
		volatile std::int32_t iRefCount;
		BS_TASK_STATE eState;
		const bool bPausable;
	};

}
