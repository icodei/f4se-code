#pragma once

namespace RE
{
	class BSSpinLock
	{
	public:
		bool IsLocked()
		{
			return _lockCount != 0;
		}

		bool IsLockedByUs()
		{
			using func_t = decltype(&BSSpinLock::IsLockedByUs);
			REL::Relocation<func_t> func{ REL::ID(1477730) };
			return func(this);
		}

		void lock(const char* a_id = nullptr)
		{
			using func_t = decltype(&BSSpinLock::lock);
			REL::Relocation<func_t> func{ REL::ID(1425657) };
			return func(this, a_id);
		}

		[[nodiscard]] bool try_lock()
		{
			using func_t = decltype(&BSSpinLock::try_lock);
			REL::Relocation<func_t> func{ REL::ID(267930) };
			return func(this);
		}

		void unlock()
		{
			stl::atomic_ref lockCount{ _lockCount };
			std::uint32_t expected{ 1 };
			if (lockCount == expected) {
				_owningThread = 0;
				lockCount.compare_exchange_strong(expected, 0);
			} else {
				--lockCount;
			}
		}

	protected:
		// members
		std::uint32_t _owningThread{ 0 };        // 0
		volatile std::uint32_t _lockCount{ 0 };  // 4
	};
	static_assert(sizeof(BSSpinLock) == 0x8);
}
