#pragma once

#include "RE/Havok/Common/Base/Types/hkRefPtr.h"
#include "RE/Havok/Physics/Physics/Collide/Query/Collector/hknpAllHitsCollector.h"

namespace RE
{
	class hknpBSWorld;

	class __declspec(novtable) hknpUniqueBodyIdHitCollector :
		public hknpAllHitsCollector  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpUniqueBodyIdHitCollector };
		static constexpr auto VTABLE{ VTABLE::hknpUniqueBodyIdHitCollector };

		// members
		hkRefPtr<hknpBSWorld> latentWorld;  // 3F0
	};
	static_assert(sizeof(hknpUniqueBodyIdHitCollector) == 0x400);
	
	class __declspec(novtable) hknpClosestUniqueBodyIdHitCollector :
		public hknpUniqueBodyIdHitCollector  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpClosestUniqueBodyIdHitCollector };
		static constexpr auto VTABLE{ VTABLE::hknpClosestUniqueBodyIdHitCollector };

		// members
		hkVector4f center;  // 400
	};
	static_assert(sizeof(hknpClosestUniqueBodyIdHitCollector) == 0x410);
}
