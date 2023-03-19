#pragma once
#include "RE/Bethesda/BSCore/BSNonReEntrantSpinLock.h"
#include "RE/Bethesda/BSCore/BSReadWriteLock.h"
#include "RE/Bethesda/BSCore/BSSpinLock.h"

namespace RE
{
	template <class Mutex>
	struct BSAutoLockDefaultPolicy
	{
	public:
		static void lock(Mutex& a_mutex) { a_mutex.lock(); }
		static void unlock(Mutex& a_mutex) { a_mutex.unlock(); }
	};

	extern template struct BSAutoLockDefaultPolicy<BSSpinLock>;

	template <class Mutex>
	struct BSAutoLockReadLockPolicy
	{
	public:
		static void lock(Mutex& a_mutex) { a_mutex.lock_read(); }
		static void unlock(Mutex& a_mutex) { a_mutex.unlock_read(); }
	};

	extern template struct BSAutoLockReadLockPolicy<BSReadWriteLock>;

	template <class Mutex>
	struct BSAutoLockWriteLockPolicy
	{
	public:
		static void lock(Mutex& a_mutex) { a_mutex.lock_write(); }
		static void unlock(Mutex& a_mutex) { a_mutex.unlock_write(); }
	};

	extern template struct BSAutoLockWriteLockPolicy<BSReadWriteLock>;

	template <class Mutex, template <class> class Policy = BSAutoLockDefaultPolicy>
	class BSAutoLock
	{
	public:
		using mutex_type = Mutex;
		using policy_type = Policy<mutex_type>;

		explicit BSAutoLock(mutex_type& a_mutex) :
			_lock(std::addressof(a_mutex))
		{
			policy_type::lock(*_lock);
		}

		explicit BSAutoLock(mutex_type* a_mutex) :
			_lock(a_mutex)
		{
			if (_lock) {
				policy_type::lock(*_lock);
			}
		}

		~BSAutoLock()
		{
			if (_lock) {
				policy_type::unlock(*_lock);
			}
		}

	private:
		// members
		mutex_type* _lock{ nullptr };  // 00
	};

	template <class Mutex>
	BSAutoLock(Mutex&) -> BSAutoLock<Mutex>;

	template <class Mutex>
	BSAutoLock(Mutex*) -> BSAutoLock<Mutex>;

	extern template class BSAutoLock<BSSpinLock, BSAutoLockDefaultPolicy>;
	extern template class BSAutoLock<BSReadWriteLock, BSAutoLockReadLockPolicy>;
	extern template class BSAutoLock<BSReadWriteLock, BSAutoLockWriteLockPolicy>;

	using BSAutoReadLock = BSAutoLock<BSReadWriteLock, BSAutoLockReadLockPolicy>;
	using BSAutoWriteLock = BSAutoLock<BSReadWriteLock, BSAutoLockWriteLockPolicy>;
}
