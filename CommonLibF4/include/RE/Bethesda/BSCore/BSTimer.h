#pragma once

namespace RE
{
	class BSTimer
	{
	public:
		static BSTimer& GetTimer()
		{
			REL::Relocation<BSTimer*> timer{ REL::ID(1256126) };
			return *timer;
		}

		// members
		std::int64_t highPrecisionInitTime;  // 00
		float clamp;                         // 08
		float clampRemainder;                // 0C
		float delta;                         // 10
		float realTimeDelta;                 // 14
		std::uint64_t lastTime;              // 18
		std::uint64_t firstTime;             // 20
		std::uint64_t disabledLastTime;      // 28
		std::uint64_t disabledFirstTime;     // 30
		std::uint32_t disableCounter;        // 38
		bool useGlobalTimeMultiplierTarget;  // 3C
	};
	static_assert(sizeof(BSTimer) == 0x40);
}
