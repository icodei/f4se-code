#pragma once

namespace RE
{
	namespace CompactingStore
	{
		class Store;
	}

	class BSSmallBlockAllocator;

	struct HeapStats;
	struct MemoryStats;

	enum class MEM_CONTEXT
	{
		MC_CORE_SYSTEM = 0x0,
		MC_CORE_STATICVARS = 0x1,
		MC_CORE_UNKNOWN = 0x2,
		MC_CORE_POOL = 0x3,
		MC_CORE_TASK = 0x4,
		MC_CORE_SMALL_BLOCK = 0x5,
		MC_CORE_STRING = 0x6,
		MC_DEBUG_SYSTEM = 0x7,
		MC_DEBUG_DATA = 0x8,
		MC_FILE_SYSTEM = 0x9,
		MC_FILE_STREAM = 0xA,
		MC_FILE_BUFFER = 0xB,
		MC_FILE_ZIP = 0xC,
		MC_FILE_JSON = 0xD,
		MC_FILE_DBOVERHEAD = 0xE,
		MC_FILE_MATERIALDB = 0xF,
		MC_FILE_MODELDB = 0x10,
		MC_FILE_TEXTUREDB = 0x11,
		MC_VM_SYSTEM = 0x12,
		MC_VM_TASKLET = 0x13,
		MC_VM_OBJECT = 0x14,
		MC_VM_TYPES = 0x15,
		MC_VM_BINDING = 0x16,
		MC_VM_GAME = 0x17,
		MC_RENDER_SYSTEM = 0x18,
		MC_RENDER_SCENE_LISTS = 0x19,
		MC_RENDER_SHADER = 0x1A,
		MC_RENDER_SHADOWS = 0x1B,
		MC_RENDER_PROPERTY = 0x1C,
		MC_RENDER_PRIMITIVE = 0x1D,
		MC_RENDER_ACCUMULATOR = 0x1E,
		MC_RENDER_IMAGESPACE = 0x1F,
		MC_RENDER_GRASS = 0x20,
		MC_RENDER_DECAL = 0x21,
		MC_RENDER_WATER = 0x22,
		MC_RENDER_TREES = 0x23,
		MC_RENDER_MULTIINDEX = 0x24,
		MC_RENDER_TARGET = 0x25,
		MC_RENDER_PRT = 0x26,
		MC_RENDER_UMBRA = 0x27,
		MC_RENDER_DYNAMICTRISHAPE_DATA = 0x28,
		MC_RESOURCE_GENERATED_TEXTURE = 0x29,
		MC_RESOURCE_TEXTURE = 0x2A,
		MC_RESOURCE_GEOMETRY = 0x2B,
		MC_RESOURCE_COMBINEDGEOMETRY = 0x2C,
		MC_RESOURCE_PROCEDURALGEOMETRY = 0x2D,
		MC_AUDIO_SYSTEM = 0x2E,
		MC_AUDIO_SOUND = 0x2F,
		MC_AUDIO_VOICE = 0x30,
		MC_AUDIO_MUSIC = 0x31,
		MC_HAVOK_SYSTEM = 0x32,
		MC_HAVOK_WORLD = 0x33,
		MC_HAVOK_ACTION = 0x34,
		MC_HAVOK_CONSTRAINT = 0x35,
		MC_HAVOK_RIGIDBODY = 0x36,
		MC_HAVOK_SHAPE = 0x37,
		MC_HAVOK_CONTROLLER = 0x38,
		MC_HAVOK_COLLECTION = 0x39,
		MC_HAVOK_CLOTH = 0x3A,
		MC_GB_SYSTEM = 0x3B,
		MC_GB_EXTRADATA = 0x3C,
		MC_GB_SKIN = 0x3D,
		MC_GB_PARTICLES = 0x3E,
		MC_GB_MESH = 0x3F,
		MC_GB_TEXTURE = 0x40,
		MC_GB_COLLISION = 0x41,
		MC_UI_SYSTEM = 0x42,
		MC_UI_FILE = 0x43,
		MC_UI_SCALEFORM = 0x44,
		MC_UI_SCALEFORM_RENDERER = 0x45,
		MC_UI_MOVIE = 0x46,
		MC_NM_SYSTEM = 0x47,
		MC_NM_DATA = 0x48,
		MC_NM_METADATA = 0x49,
		MC_NM_PATH = 0x4A,
		MC_NM_OBSTACLE = 0x4B,
		MC_NM_MOVEMENT = 0x4C,
		MC_FG_SYSTEM = 0x4D,
		MC_FG_TEXTURE = 0x4E,
		MC_FG_MESH = 0x4F,
		MC_FG_ANIM = 0x50,
		MC_LOD_SYSTEM = 0x51,
		MC_LOD_LAND = 0x52,
		MC_LOD_TREE = 0x53,
		MC_LOD_OBJECTS = 0x54,
		MC_GAME_APP_MAIN = 0x55,
		MC_GAME_SYSTEM = 0x56,
		MC_GAME_MISC = 0x57,
		MC_GAME_SAVELOAD = 0x58,
		MC_GAME_SCREENSHOT = 0x59,
		MC_GAME_SKY = 0x5A,
		MC_GAME_HAZARD = 0x5B,
		MC_GAME_EFFECTS = 0x5C,
		MC_GAME_EXPLOSION = 0x5D,
		MC_GAME_EXTRADATA = 0x5E,
		MC_GAME_INVENTORY = 0x5F,
		MC_GAME_MAP = 0x60,
		MC_GAME_MASTERFILE = 0x61,
		MC_GAME_FORMS = 0x62,
		MC_GAME_SETTINGS = 0x63,
		MC_GAME_REF = 0x64,
		MC_GAME_ACTOR = 0x65,
		MC_GAME_PLAYER = 0x66,
		MC_GAME_CELL = 0x67,
		MC_GAME_WORLD = 0x68,
		MC_GAME_TERRAIN = 0x69,
		MC_GAME_PROJECTILE = 0x6A,
		MC_GAME_SCENEDATA = 0x6B,
		MC_GAME_QUESTS = 0x6C,
		MC_AI_HIGH = 0x6D,
		MC_AI_MIDDLEHIGH = 0x6E,
		MC_AI_LOW = 0x6F,
		MC_AI_PROCESS = 0x70,
		MC_AI_COMBAT = 0x71,
		MC_AI_DIALOGUE = 0x72,
		MC_HAVOK_BEHAVIOR = 0x73,
		MC_GB_ANIMATION = 0x74,
		MC_ANIMATION_TEXT_OVERHEAD_CLIP_DATA = 0x75,
		MC_ANIMATION_TEXT_OVERHEAD_FILE_DATA = 0x76,
		MC_ANIMATION_TEXT_OVERHEAD_SYNC_ANIM_DATA = 0x77,
		MC_ANIMATION_TEXT_OVERHEAD_OTHER = 0x78,
		MC_ANIMATION_TEXT_DYNAMIC = 0x79,
		MC_ANIMATION_UNIQUE_BEHAVIORS = 0x7A,
		MC_SCRATCH = 0x7B,
		MC_HEAP_ZERO = 0x7C,
		MC_LUA = 0x7D,
		MC_TOTAL = 0x7E,
		MEM_CONTEXT_COUNT = 0x7F,
	};

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

	class __declspec(novtable) IMemoryHeap :
		public IMemoryStore  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::IMemoryHeap };
		static constexpr auto VTABLE{ VTABLE::IMemoryHeap };

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~IMemoryHeap() = default;

		// override (IMemoryStore)
		bool ContainsBlockImpl(const void* a_block) const override { return PointerInHeap(a_block); }                              // 03
		void* AllocateAlignImpl(std::size_t a_size, std::uint32_t a_alignment) override { return Allocate(a_size, a_alignment); }  // 04
		void DeallocateAlignImpl(void*& a_block) override { Deallocate(a_block, 0); }                                              // 05

		// add
		virtual const char* GetName() const = 0;                                               // 07
		virtual void* Allocate(std::size_t a_size, std::uint32_t a_alignment) = 0;             // 08
		virtual void Deallocate(void* a_mem, std::uint32_t) = 0;                               // 09
		virtual bool PointerInHeap(const void* a_pointer) const = 0;                           // 0A
		virtual std::size_t TotalSize(const void* a_pointer) const = 0;                        // 0B
		virtual void GetHeapStats(HeapStats* a_stats, bool a_fullBlockInfo) = 0;               // 0C
		virtual bool ShouldTrySmallBlockPools(std::size_t a_size, MEM_CONTEXT a_context) = 0;  // 0D
		virtual std::uint32_t GetPageSize() const = 0;                                         // 0E
	};
	static_assert(sizeof(IMemoryHeap) == 0x8);

	class __declspec(novtable) ScrapHeap :
		public IMemoryStore  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::ScrapHeap };
		static constexpr auto VTABLE{ VTABLE::ScrapHeap };

		struct Block
		{
		public:
			// members
			std::size_t sizeFlags;  // 00
			Block* prev;            // 08
		};
		static_assert(sizeof(Block) == 0x10);

		struct FreeBlock :
			public Block  // 00
		{
		public:
			// members
			FreeBlock* left;   // 10
			FreeBlock* right;  // 18
		};
		static_assert(sizeof(FreeBlock) == 0x20);

		struct FreeTreeNode :
			public FreeBlock  // 00
		{
		public:
			// members
			FreeTreeNode** root;         // 20
			FreeTreeNode* leftNode;      // 28
			FreeTreeNode* rightNode;     // 30
			std::size_t parentAndBlack;  // 38
		};
		static_assert(sizeof(FreeTreeNode) == 0x40);

		// NOLINTNEXTLINE(modernize-use-equals-default)
		~ScrapHeap() override { WinAPI::VirtualFree(baseAddress, 0, (WinAPI::MEM_RELEASE)); }  // 00

		// override (IMemoryStore)
		std::size_t Size(void const* a_mem) const override { return *static_cast<const std::size_t*>(a_mem) & ~(std::size_t{ 3 } << 62); }  // 01
		void GetMemoryStats(MemoryStats*) override { return; }                                                                              // 02
		bool ContainsBlockImpl(const void* a_block) const override { return baseAddress <= a_block && a_block <= endAddress; }              // 03
		void* AllocateAlignImpl(std::size_t a_size, std::uint32_t a_alignment) override { return Allocate(a_size, a_alignment); }           // 04
		void DeallocateAlignImpl(void*& a_block) override { Deallocate(a_block), a_block = nullptr; }                                       // 05

		void* Allocate(std::size_t a_size, std::size_t a_alignment)
		{
			using func_t = decltype(&ScrapHeap::Allocate);
			REL::Relocation<func_t> func{ REL::ID(1085394) };
			return func(this, a_size, a_alignment);
		}

		void Deallocate(void* a_mem)
		{
			using func_t = decltype(&ScrapHeap::Deallocate);
			REL::Relocation<func_t> func{ REL::ID(923307) };
			return func(this, a_mem);
		}

		// members
		FreeBlock* smallBlocks[6]{ nullptr };     // 08
		FreeTreeNode* freeList{ nullptr };        // 38
		Block* lastBlock{ nullptr };              // 40
		std::byte* baseAddress{ nullptr };        // 48
		std::byte* endAddress{ nullptr };         // 50
		std::byte* commitEnd{ nullptr };          // 58
		std::size_t reserveSize;                  // 60
		std::size_t minCommit{ 1u << 17 };        // 68
		std::size_t totalAllocated{ 0 };          // 70
		std::uint32_t keepPagesRequest{ 0 };      // 78
		std::uint32_t totalFreeBlocks{ 0 };       // 7C
		std::uint32_t freeSmallBlocks{ 0 };       // 80
		std::uint32_t totalAllocatedBlocks{ 0 };  // 84
		std::uint32_t pmpBarrier{ 0 };            // 88
	};
	static_assert(sizeof(ScrapHeap) == 0x90);

	class MemoryManager
	{
	public:
		struct AutoScrapBuffer
		{
		public:
			AutoScrapBuffer() { Ctor(); }
			~AutoScrapBuffer() { Dtor(); }

			[[nodiscard]] void* GetPtr() const noexcept { return ptr; }

			// members
			void* ptr{ nullptr };  // 0

		private:
			AutoScrapBuffer* Ctor()
			{
				using func_t = decltype(&AutoScrapBuffer::Ctor);
				REL::Relocation<func_t> func{ REL::ID(1571567) };
				return func(this);
			}

			void Dtor()
			{
				using func_t = decltype(&AutoScrapBuffer::Dtor);
				REL::Relocation<func_t> func{ REL::ID(68625) };
				return func(this);
			}
		};
		static_assert(sizeof(AutoScrapBuffer) == 0x8);

		struct ThreadScrapHeap
		{
		public:
			// members
			ScrapHeap heap;                                              // 00
			ThreadScrapHeap* next{ nullptr };                            // 90
			std::uint32_t owningThread{ WinAPI::GetCurrentThreadID() };  // 98
		};
		static_assert(sizeof(ThreadScrapHeap) == 0xA0);

		[[nodiscard]] static MemoryManager& GetSingleton()
		{
			using func_t = decltype(&MemoryManager::GetSingleton);
			const REL::Relocation<func_t> func{ REL::ID(343176) };
			return func();
		}

		[[nodiscard]] void* Allocate(std::size_t a_size, std::uint32_t a_alignment, bool a_alignmentRequired)
		{
			using func_t = decltype(&MemoryManager::Allocate);
			const REL::Relocation<func_t> func{ REL::ID(652767) };
			return func(this, a_size, a_alignment, a_alignmentRequired);
		}

		void Deallocate(void* a_mem, bool a_alignmentRequired)
		{
			using func_t = decltype(&MemoryManager::Deallocate);
			const REL::Relocation<func_t> func{ REL::ID(1582181) };
			return func(this, a_mem, a_alignmentRequired);
		}

		[[nodiscard]] ScrapHeap* GetThreadScrapHeap()
		{
			using func_t = decltype(&MemoryManager::GetThreadScrapHeap);
			const REL::Relocation<func_t> func{ REL::ID(1495205) };
			return func(this);
		}

		[[nodiscard]] void* Reallocate(void* a_oldMem, std::size_t a_newSize, std::uint32_t a_alignment, bool a_alignmentRequired)
		{
			using func_t = decltype(&MemoryManager::Reallocate);
			const REL::Relocation<func_t> func{ REL::ID(1502917) };
			return func(this, a_oldMem, a_newSize, a_alignment, a_alignmentRequired);
		}

		void RegisterMemoryManager()
		{
			using func_t = decltype(&MemoryManager::RegisterMemoryManager);
			const REL::Relocation<func_t> func{ REL::ID(453212) };
			return func(this);
		}

		// members
		bool initialized{ false };                              // 000
		std::uint16_t numHeaps{ 0 };                            // 002
		std::uint16_t numPhysicalHeaps{ 0 };                    // 004
		IMemoryHeap** heaps{ nullptr };                         // 008
		bool* allowOtherContextAllocs{ nullptr };               // 010
		IMemoryHeap* heapsByContext[127]{ nullptr };            // 018
		ThreadScrapHeap* threadScrapHeap{ nullptr };            // 410
		IMemoryHeap** physicalHeaps{ nullptr };                 // 418
		IMemoryHeap* bigAllocHeap{ nullptr };                   // 420
		IMemoryHeap* emergencyHeap{ nullptr };                  // 428
		BSSmallBlockAllocator* smallBlockAllocator{ nullptr };  // 430
		CompactingStore::Store* compactingStore{ nullptr };     // 438
		IMemoryHeap* externalHavokAllocator{ nullptr };         // 440
		bool specialHeaps{ false };                             // 448
		bool allowPoolUse{ true };                              // 449
		std::uint32_t sysAllocBytes{ 0 };                       // 44C
		std::uint32_t mallocBytes{ 0 };                         // 450
		std::uint32_t alignmentForPools{ 4 };                   // 454
		std::uint32_t mainThreadMemoryProblemPassSignal{ 0 };   // 458
		std::size_t failedAllocationSize{ 0 };                  // 460
		std::uint32_t numMemoryProblemPassesRun{ 0 };           // 468
		std::size_t timeOfLastMemoryProblemPass{ 0 };           // 470
		IMemoryHeap* defaultHeap{ nullptr };                    // 478
	};
	static_assert(sizeof(MemoryManager) == 0x480);

	[[nodiscard]] inline void* malloc(std::size_t a_size)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Allocate(a_size, 0, false);
	}

	template <class T>
	[[nodiscard]] T* malloc()
	{
		return static_cast<T*>(malloc(sizeof(T)));
	}

	[[nodiscard]] inline void* aligned_alloc(std::size_t a_alignment, std::size_t a_size)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Allocate(a_size, static_cast<std::uint32_t>(a_alignment), true);
	}

	template <class T>
	[[nodiscard]] T* aligned_alloc()
	{
		return static_cast<T*>(aligned_alloc(alignof(T), sizeof(T)));
	}

	[[nodiscard]] inline void* calloc(std::size_t a_num, std::size_t a_size)
	{
		const auto ret = malloc(a_num * a_size);
		if (ret) {
			std::memset(ret, 0, a_num * a_size);
		}
		return ret;
	}

	template <class T>
	[[nodiscard]] T* calloc(std::size_t a_num)
	{
		return static_cast<T*>(calloc(a_num, sizeof(T)));
	}

	[[nodiscard]] inline void* realloc(void* a_ptr, std::size_t a_newSize)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Reallocate(a_ptr, a_newSize, 0, false);
	}

	[[nodiscard]] inline void* aligned_realloc(void* a_ptr, std::size_t a_alignment, std::size_t a_newSize)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Reallocate(a_ptr, a_newSize, static_cast<std::uint32_t>(a_alignment), true);
	}

	inline void free(void* a_ptr)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Deallocate(a_ptr, false);
	}

	inline void aligned_free(void* a_ptr)
	{
		auto& mem = MemoryManager::GetSingleton();
		return mem.Deallocate(a_ptr, true);
	}
}

#define F4_HEAP_REDEFINE_HELPER(...)                                                                          \
	[[nodiscard]] void* operator new(std::size_t a_count, std::align_val_t a_alignment)                       \
	{                                                                                                         \
		const auto mem = RE::aligned_alloc(static_cast<std::size_t>(a_alignment), a_count);                   \
		if (mem) {                                                                                            \
			return mem;                                                                                       \
		} else {                                                                                              \
			stl::report_and_fail("out of memory"sv);                                                          \
		}                                                                                                     \
	}                                                                                                         \
                                                                                                              \
	[[nodiscard]] void* operator new[](std::size_t a_count, std::align_val_t a_alignment)                     \
	{                                                                                                         \
		const auto mem = RE::aligned_alloc(static_cast<std::size_t>(a_alignment), a_count);                   \
		if (mem) {                                                                                            \
			return mem;                                                                                       \
		} else {                                                                                              \
			stl::report_and_fail("out of memory"sv);                                                          \
		}                                                                                                     \
	}                                                                                                         \
                                                                                                              \
	[[nodiscard]] void* operator new(std::size_t, void* a_ptr) noexcept { return a_ptr; }                     \
	[[nodiscard]] void* operator new[](std::size_t, void* a_ptr) noexcept { return a_ptr; }                   \
	[[nodiscard]] void* operator new(std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }   \
	[[nodiscard]] void* operator new[](std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; } \
                                                                                                              \
	void operator delete(void*, void*) noexcept { return; }                                                   \
	void operator delete[](void*, void*) noexcept { return; }                                                 \
                                                                                                              \
	void operator delete(void* a_ptr, std::align_val_t) { RE::aligned_free(a_ptr); }                          \
	void operator delete[](void* a_ptr, std::align_val_t) { RE::aligned_free(a_ptr); }                        \
	void operator delete(void* a_ptr, std::size_t, std::align_val_t) { RE::aligned_free(a_ptr); }             \
	void operator delete[](void* a_ptr, std::size_t, std::align_val_t) { RE::aligned_free(a_ptr); }

#define F4_HEAP_REDEFINE_NEW(...)                                         \
	[[nodiscard]] void* operator new(std::size_t a_count)                 \
	{                                                                     \
		const auto mem = RE::malloc(a_count);                             \
		if (mem) {                                                        \
			return mem;                                                   \
		} else {                                                          \
			stl::report_and_fail("out of memory"sv);                      \
		}                                                                 \
	}                                                                     \
                                                                          \
	[[nodiscard]] void* operator new[](std::size_t a_count)               \
	{                                                                     \
		const auto mem = RE::malloc(a_count);                             \
		if (mem) {                                                        \
			return mem;                                                   \
		} else {                                                          \
			stl::report_and_fail("out of memory"sv);                      \
		}                                                                 \
	}                                                                     \
                                                                          \
	void operator delete(void* a_ptr) { RE::free(a_ptr); }                \
	void operator delete[](void* a_ptr) { RE::free(a_ptr); }              \
	void operator delete(void* a_ptr, std::size_t) { RE::free(a_ptr); }   \
	void operator delete[](void* a_ptr, std::size_t) { RE::free(a_ptr); } \
                                                                          \
	F4_HEAP_REDEFINE_HELPER(__VA_ARGS__)

#define F4_HEAP_REDEFINE_ALIGNED_NEW(...)                                         \
	[[nodiscard]] void* operator new(std::size_t a_count)                         \
	{                                                                             \
		const auto mem = RE::aligned_alloc(alignof(__VA_ARGS__), a_count);        \
		if (mem) {                                                                \
			return mem;                                                           \
		} else {                                                                  \
			stl::report_and_fail("out of memory"sv);                              \
		}                                                                         \
	}                                                                             \
                                                                                  \
	[[nodiscard]] void* operator new[](std::size_t a_count)                       \
	{                                                                             \
		const auto mem = RE::aligned_alloc(alignof(__VA_ARGS__), a_count);        \
		if (mem) {                                                                \
			return mem;                                                           \
		} else {                                                                  \
			stl::report_and_fail("out of memory"sv);                              \
		}                                                                         \
	}                                                                             \
                                                                                  \
	void operator delete(void* a_ptr) { RE::aligned_free(a_ptr); }                \
	void operator delete[](void* a_ptr) { RE::aligned_free(a_ptr); }              \
	void operator delete(void* a_ptr, std::size_t) { RE::aligned_free(a_ptr); }   \
	void operator delete[](void* a_ptr, std::size_t) { RE::aligned_free(a_ptr); } \
                                                                                  \
	F4_HEAP_REDEFINE_HELPER(__VA_ARGS__)
