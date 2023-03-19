#pragma once
#include "RE/Bethesda/BSLock.h"
#include "RE/NetImmerse/NiMain/BSGeometrySegmentData.h"
#include "RE/NetImmerse/NiMain/BSTriShape.h"
#include "RE/NetImmerse/NiMain/BSGeometry.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class BSDynamicTriShape : public BSTriShape
	{
	public:
		static constexpr auto RTTI{ RTTI::BSDynamicTriShape };
		static constexpr auto VTABLE{ VTABLE::BSDynamicTriShape };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSDynamicTriShape };
		static constexpr auto TYPE{ GeometryType::GEOMETRY_TYPE_DYNAMIC_TRISHAPE };

		//members
		std::uint32_t uiDynamicDataSize;              // 170
		std::uint32_t uiFrameCount;                   // 174
		BSSpinLock lock;                              // 178
		std::uint8_t* dynamicVertices;                // 180 - geometry pointer, must lock/unlock when altering
		NiPointer<BSGeometrySegmentData> spSegments;  // 188
		void* unk190;                                 // 190
		void* unk198;                                 // 198
	};
	static_assert(sizeof(BSDynamicTriShape) == 0x1A0);
}
