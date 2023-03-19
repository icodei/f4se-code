#pragma once

#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"
#include "RE/NetImmerse/NiMain/NiObject.h"

namespace RE
{
	class BSGeometrySegmentFlagData
	{
		BSTHashMap<std::uint32_t, BSFixedString> SegmentDeltas;  // 00
		BSFixedString BaseBoneName;                              // 30
	};
	static_assert(sizeof(BSGeometrySegmentFlagData) == 0x38);

	class BSGeometrySegmentSharedData : public BSIntrusiveRefCounted
	{
	public:
		struct PerSegmentSharedData
		{
			std::uint32_t uiUserIndex;  // 00
			std::uint32_t uiBoneID;     // 04
			float fValidCutOffsets[8];  // 08
		};
		static_assert(sizeof(PerSegmentSharedData) == 0x28);

		//members
		BSFixedString SSFFileName;                      // 08
		std::uint32_t uiNumSegments;                    // 10
		std::uint32_t uiTotalNumSegments;               // 14
		std::uint32_t* pSegmentStarts;                  // 18
		PerSegmentSharedData* pPerSegmentSharedData;    // 20
		BSGeometrySegmentFlagData SegmentsEnabledData;  // 28
		bool bProcessedCutOffsets;                      // 60
	};
	static_assert(sizeof(BSGeometrySegmentSharedData) == 0x68);

	class BSGeometrySegmentData : public NiObject
	{
	public:
		static constexpr auto RTTI{ RTTI::BSGeometrySegmentData };
		static constexpr auto VTABLE{ VTABLE::BSGeometrySegmentData };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSGeometrySegmentData };

		class Segment
		{
			std::uint32_t uiStartIndex;        // 00
			std::uint32_t uiNumPrimitives;     // 04
			std::uint32_t uiParentArrayIndex;  // 08
			std::uint32_t uiChildCount;        // 0C
			std::uint8_t ucDisabledCount;      // 10
		};
		static_assert(sizeof(Segment) == 0x14);

		struct DrawData
		{
			std::uint32_t uiStartIndex;     // 00
			std::uint32_t uiNumPrimitives;  // 04
		};
		static_assert(sizeof(DrawData) == 0x8);

		//members
		BSTSmartPointer<BSGeometrySegmentSharedData> spSharedData;  // 10
		Segment* pSegments;                                         // 18
		DrawData* pSegmentDrawData;                                 // 20
		std::uint32_t uiNumDraws;                                   // 28
		std::uint32_t uiNumSegments;                                // 2C
		std::uint32_t uiTotalNumSegments;                           // 30
		std::uint32_t uiTotalNumPrimitives;                         // 34
		std::uint32_t uiSegToZeroMap;                               // 38
		bool bSegmentsChanged;                                      // 3C
		bool bIgnoreSegments;                                       // 3D
	};
	static_assert(sizeof(BSGeometrySegmentData) == 0x40);
}
