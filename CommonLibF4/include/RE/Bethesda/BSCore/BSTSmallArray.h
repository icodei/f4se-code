#pragma once

#include "RE/Bethesda/BSCore/MemoryManager.h"
#include "RE/Bethesda/BSCore/BSTArray.h"

namespace RE
{
	class ScrapHeap;

	template <std::uint32_t N>
	class BSTSmallArrayHeapAllocator
	{
	public:
		using size_type = std::uint32_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::false_type;

		BSTSmallArrayHeapAllocator() noexcept = default;
		BSTSmallArrayHeapAllocator(const BSTSmallArrayHeapAllocator&) = delete;
		BSTSmallArrayHeapAllocator(BSTSmallArrayHeapAllocator&&) = delete;

		~BSTSmallArrayHeapAllocator() noexcept = default;

		BSTSmallArrayHeapAllocator& operator=(const BSTSmallArrayHeapAllocator&) = delete;
		BSTSmallArrayHeapAllocator& operator=(BSTSmallArrayHeapAllocator&&) = delete;

		[[nodiscard]] void* allocate(uint32_t a_bytes)
		{
			if (a_bytes > N) {
				return malloc(a_bytes);
			} else {
				return _stack;
			}
		}

		void deallocate(void* a_ptr)
		{
			if (a_ptr != _stack) {
				free(a_ptr);
			}
		}

		[[nodiscard]] void* data() noexcept { return _local ? _stack : _heap; }
		[[nodiscard]] const void* data() const noexcept { return _local ? _stack : _heap; }

		void set_data(void* a_data) noexcept
		{
			if (a_data != _stack) {
				_heap = a_data;
			}
		}

		[[nodiscard]] size_type capacity() const noexcept { return _capacity; }

		void set_capacity(size_type a_capacity, size_type a_bytes) noexcept
		{
			_local = a_bytes <= N ? true : false;
			_capacity = a_capacity;
		}

	private:
		// members
		size_type _capacity: 31 { 0 };  // 00:00
		size_type _local: 1 { 0 };      // 00:31
		union
		{
			void* _heap{ nullptr };
			std::byte _stack[N];
		};  // 08
	};

	template <class T, std::uint32_t N = 1>
	using BSTSmallArray = BSTArray<T, BSTSmallArrayHeapAllocator<sizeof(T) * N>>;

	template <class T>
	class BSTSmallSharedArray
	{
	public:
		using value_type = T;
		using size_type = std::uint32_t;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = pointer;
		using const_iterator = const_pointer;

		~BSTSmallSharedArray() { stl::report_and_fail("unimplemented"sv); }

		[[nodiscard]] reference operator[](size_type a_pos) noexcept
		{
			assert(a_pos < _size);
			return data()[a_pos];
		}

		[[nodiscard]] const_reference operator[](size_type a_pos) const noexcept
		{
			assert(a_pos < _size);
			return data()[a_pos];
		}

		[[nodiscard]] pointer data() noexcept
		{
			return size() > 1 ? heap : std::addressof(local);
		}

		[[nodiscard]] const_pointer data() const noexcept
		{
			return size() > 1 ? heap : std::addressof(local);
		}

		[[nodiscard]] iterator begin() noexcept { return data(); }
		[[nodiscard]] const_iterator begin() const noexcept { return data(); }
		[[nodiscard]] const_iterator cbegin() const noexcept { return begin(); }

		[[nodiscard]] iterator end() noexcept { return data() + size(); }
		[[nodiscard]] const_iterator end() const noexcept { return data() + size(); }
		[[nodiscard]] const_iterator cend() const noexcept { return end(); }

		[[nodiscard]] bool empty() const noexcept { return size() != 0; }

		[[nodiscard]] size_type size() const noexcept { return _size; }

	private:
		// members
		std::uint32_t _size{ 0 };  // 00
		union
		{
			pointer heap{ 0 };
			value_type local;
		};  // 08
	};
}
