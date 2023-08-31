#pragma once
#include "RE/Havok/Geometry/Internal/Types/hkcdRay.h"
#include "RE/Havok/Physics/Physics/hknpTypes.h"

namespace RE
{
	class hknpCollisionFilter;

	struct hknpCollisionQueryType
	{
	public:
		enum class Enum
		{
			UNDEFINED,
			RAY_CAST,
			SHAPE_CAST,
			POINT_QUERY,
			GET_CLOSEST_POINTS,
			QUERY_AABB,
		};
	};

	struct hknpCollisionQuery
	{
	public:
		//members
		hkPadSpu<hknpCollisionFilter*> filter;
		hknpQueryFilterData filterData;
		std::uint8_t levelOfDetail;
	};

	struct hknpRayCastQuery : public hknpCollisionQuery
	{
	public:
		//members
		hkcdRay ray;
		hkFlags<hkcdRayQueryFlags::Enum, std::uint32_t> flags;
	};
}
