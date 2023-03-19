#pragma once
#include "RE/NetImmerse/NiMain/NiObject.h"

namespace RE
{
	class BSMultiBoundShape : public NiObject
	{
		static constexpr auto RTTI{ RTTI::BSMultiBoundShape };
		static constexpr auto VTABLE{ VTABLE::BSMultiBoundShape };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSMultiBoundShape };
		
		enum BSMBCullResult : std::int32_t
		{
			BS_CULL_UNTESTED = 0x0,
			BS_CULL_VISIBLE = 0x1,
			BS_CULL_CULLED = 0x2,
			BS_CULL_OCCLUDED = 0x3,
		};

		enum BSMBIntersectResult : std::int32_t
		{
			BS_INTERSECT_NONE = 0x0,
			BS_INTERSECT_PARTIAL = 0x1,
			BS_INTERSECT_CONTAINSTARGET = 0x2,
		};

		enum BSMBShapeType : std::int32_t
		{
			BS_SHAPE_INVALID = 0x0,
			BS_SHAPE_AABB = 0x1,
			BS_SHAPE_OBB = 0x2,
			BS_SHAPE_SPHERE = 0x3,
			BS_SHAPE_CAPSULE = 0x4,
		};

		//members
		BSMultiBoundShape::BSMBCullResult kCullResult;
	};
}
