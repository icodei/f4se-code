#pragma once
#include "RE/NetImmerse/NiMain/BSGeometry.h"
#include "RE/NetImmerse/NiMain/BSGeometrySegmentData.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	struct ID3D11Buffer;

	class BSTriShape : public BSGeometry
	{
	public:
		static constexpr auto RTTI{ RTTI::BSTriShape };
		static constexpr auto VTABLE{ VTABLE::BSTriShape };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSTriShape };
		static constexpr auto TYPE{ GeometryType::GEOMETRY_TYPE_TRISHAPE };

		//members
		std::uint32_t numTriangles;  // 160
		std::uint16_t numVertices;   // 164
		std::uint16_t unk166;        // 166
		float unk168;                // 168
		float unk16C;                // 16C
	};
	static_assert(sizeof(BSTriShape) == 0x170);

	class BSSubIndexTriShape : public BSTriShape
	{
	public:
		static constexpr auto RTTI{ RTTI::BSSubIndexTriShape };
		static constexpr auto VTABLE{ VTABLE::BSSubIndexTriShape };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSSubIndexTriShape };
		static constexpr auto TYPE{ GeometryType::GEOMETRY_TYPE_SUBINDEX_TRISHAPE };

		struct SegmentData
		{
			ID3D11Buffer* d3d11Buffer;       // 00 - const CLayeredObjectWithCLS<class CBuffer>::CContainedObject::vftable'{forCPrivateDataImpl<struct ID3D11Buffer>'}
			std::uint8_t* segmentBlock;      // 08
			std::uint64_t unk10;             // 10
			std::uint64_t unk18;             // 18
			std::uint64_t unk20;             // 20
			void* unk28;                     // 28
			std::uint32_t unk30;             // 30
			std::uint32_t unk34;             // 34
			volatile std::int32_t refCount;  // 38
		};

		//members
		NiPointer<BSGeometrySegmentData> spSegments;  // 170
		SegmentData* segmentData;                     // 178
		std::uint32_t numIndices;                     // 180
		std::uint32_t unk184;                         // 184
		void* unk188;                                 // 188
	};
	static_assert(sizeof(BSSubIndexTriShape) == 0x190);
}
