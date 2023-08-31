#pragma once
#include "RE/Havok/Common/Base/Math/Vector/hkVector4.h"
#include "RE/Havok/Common/Base/Types/hkBaseTypes.h"
#include "RE/Havok/Physics/Physics/Collide/Query/hknpCollisionQuery.h"
#include "RE/Havok/hknpBodyId.h"
#include "RE/Havok/hknpMaterialId.h"

namespace RE
{
	struct hknpCollisionResult
	{
	public:
		struct BodyInfo
		{
		public:
			// members
			hknpBodyId bodyId;                                 // 00
			hknpMaterialId shapeMaterialId;                    // 04
			hkPadSpu<std::uint32_t> shapeKey;                  // 08
			hkPadSpu<std::uint32_t> shapeCollisionFilterInfo;  // 0C
			hkPadSpu<std::uint64_t> shapeUserData;             // 10
		};
		static_assert(sizeof(BodyInfo) == 0x18);

		// members
		hkVector4f position;                                           // 00
		hkVector4f normal;                                             // 10
		hkPadSpu<float> fraction;                                      // 20
		BodyInfo queryBodyInfo;                                        // 28
		BodyInfo hitBodyInfo;                                          // 40
		hkEnum<hknpCollisionQueryType::Enum, std::int32_t> queryType;  // 58
		hkPadSpu<std::uint32_t> hitResult;                             // 5C
	};
	static_assert(sizeof(hknpCollisionResult) == 0x60);

	struct hknpRayCastQueryResult : public hknpCollisionResult
	{
	public:
	};
}
