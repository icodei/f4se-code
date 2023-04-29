#pragma once

namespace RE
{
	struct MemoryStats;

	class __declspec(novtable) IMemoryStoreBase
	{
	public:
		static constexpr auto RTTI{ RTTI::IMemoryStoreBase };
		static constexpr auto VTABLE{ VTABLE::IMemoryStoreBase };

		virtual ~IMemoryStoreBase() = default;  // 00

		// add
		virtual std::size_t Size(void const* a_mem) const = 0;          // 01
		virtual void GetMemoryStats(MemoryStats* a_stats) = 0;          // 02
		virtual bool ContainsBlockImpl(const void* a_block) const = 0;  // 03
	};
	static_assert(sizeof(IMemoryStoreBase) == 0x8);

	class __declspec(novtable) IMemoryStore :
		public IMemoryStoreBase  // 0
	{
	public:
		static constexpr auto RTTI{ RTTI::IMemoryStore };
		static constexpr auto VTABLE{ VTABLE::IMemoryStore };

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~IMemoryStore() = default;  // 00

		// add
		virtual void* AllocateAlignImpl(std::size_t a_size, std::uint32_t a_alignment) = 0;                                                 // 04
		virtual void DeallocateAlignImpl(void*& a_block) = 0;                                                                               // 05
		virtual void* TryAllocateImpl([[maybe_unused]] std::size_t a_size, [[maybe_unused]] std::uint32_t a_alignment) { return nullptr; }  // 06
	};
	static_assert(sizeof(IMemoryStore) == 0x8);
}
