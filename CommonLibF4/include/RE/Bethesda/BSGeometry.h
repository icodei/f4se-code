#pragma once

#include "RE/NetImmerse/NiSmartPointer.h"
#include "RE/Bethesda/BSTHashMap.h"
#include "RE/Bethesda/BSBound.h"
#include "RE/Bethesda/BSFixedString.h"

namespace RE
{
	class BSDynamicTriShape;
	class NiProperty;

	struct ID3D11Buffer;

	// 38
	struct BSGeometrySegmentFlagData
	{
		BSTHashMap<std::uint32_t, BSFixedString> SegmentDeltas;  // 00
		BSFixedString BaseBoneName;                     // 30
	};

	// 68
	class BSGeometrySegmentSharedData : public BSIntrusiveRefCounted
	{
	public:

		// 28
		struct PerSegmentSharedData
		{
			std::uint32_t uiUserIndex;  // 00
			std::uint32_t uiBoneID;     // 04
			float fValidCutOffsets[8];  // 08
		};

		//members
		BSFixedString SSFFileName;                      // 08
		std::uint32_t uiNumSegments;                    // 10
		std::uint32_t uiTotalNumSegments;               // 14
		std::uint32_t* pSegmentStarts;                  // 18
		PerSegmentSharedData* pPerSegmentSharedData;    // 20
		BSGeometrySegmentFlagData SegmentsEnabledData;  // 28
		bool bProcessedCutOffsets;                      // 60
	};

	// 40
	class BSGeometrySegmentData : public NiObject
	{
	public:

		static constexpr auto RTTI{ RTTI::BSGeometrySegmentData };
		static constexpr auto VTABLE{ VTABLE::BSGeometrySegmentData };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSGeometrySegmentData };

		// 18
		struct Segment
		{
			std::uint32_t uiStartIndex;  // 00
			std::uint32_t uiNumPrimitives;  // 04
			std::uint32_t uiParentArrayIndex;  // 08
			std::uint32_t uiChildCount;        // 0C
			std::uint8_t ucDisabledCount;     // 10
		};

		// 8
		struct DrawData
		{
			std::uint32_t uiStartIndex;  // 00
			std::uint32_t uiNumPrimitives;  // 04
		};

		//members
		BSGeometrySegmentSharedData* spSharedData;  // 10
		Segment* pSegments;                         // 18
		DrawData* pSegmentDrawData;                 // 20
		std::uint32_t uiNumDraws;                   // 28
		std::uint32_t uiNumSegments;                // 2C
		std::uint32_t uiTotalNumSegments;           // 30
		std::uint32_t uiTotalNumPrimitives;         // 34
		std::uint32_t uiSegToZeroMap;               // 38
		bool bSegmentsChanged;                      // 3C
		bool bIgnoreSegments;                       // 3D
	};

	class BSGeometryData
	{
	public:
		
		struct VertexData
		{
			ID3D11Buffer* d3d11Buffer;  // 00 - const CLayeredObjectWithCLS<class CBuffer>::CContainedObject::`vftable'{for `CPrivateDataImpl<struct ID3D11Buffer>'}
			std::uint8_t* vertexBlock;  // 08
			std::uint64_t unk10;        // 10
			std::uint64_t unk18;        // 18
			std::uint64_t unk20;        // 20
			std::uint64_t unk28;        // 28
			std::uint64_t unk30;        // 30
			volatile std::int32_t refCount;  // 38
		};

		struct TriangleData
		{
			ID3D11Buffer* d3d11Buffer;  // 00 - Same buffer as VertexData
			std::uint16_t* triangles;   // 08
			std::uint64_t unk10;        // 10
			std::uint64_t unk18;        // 18
			std::uint64_t unk20;        // 20
			std::uint64_t unk28;        // 28
			std::uint64_t unk30;        // 30
			volatile std::int32_t refCount;  // 38
		};

		//members
		std::uint64_t vertexDesc;
		VertexData* vertexData;      // 08
		TriangleData* triangleData;  // 10
		volatile std::int32_t refCount;  // 18
	};

	// 160
	class BSGeometry : public NiAVObject
	{
	public:

		static constexpr auto RTTI{ RTTI::BSGeometry };
		static constexpr auto VTABLE{ VTABLE::BSGeometry };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSGeometry };

		virtual void Unk_39() { return; };
		virtual void Unk_3A() { return; };
		virtual void Unk_3B() { return; };
		virtual void Unk_3C() { return; };
		virtual void Unk_3D() { return; };
		virtual void Unk_3E() { return; };
		virtual void Unk_3F() { return; };
		virtual void Unk_40() { return; };

		union VertexDesc
		{
			struct
			{
				std::uint8_t szVertexData: 4;
				std::uint8_t szVertex: 4;  // 0 when not dynamic
				std::uint8_t oTexCoord0: 4;
				std::uint8_t oTexCoord1: 4;
				std::uint8_t oNormal: 4;
				std::uint8_t oTangent: 4;
				std::uint8_t oColor: 4;
				std::uint8_t oSkinningData: 4;
				std::uint8_t oLandscapeData: 4;
				std::uint8_t oEyeData: 4;
				std::uint16_t vertexFlags: 16;
				std::uint8_t unused: 8;
			};
			std::uint64_t vertexDesc;
		};

		enum : std::uint64_t
		{
			kFlag_Unk1 = (1ULL << 40),
			kFlag_Unk2 = (1ULL << 41),
			kFlag_Unk3 = (1ULL << 42),
			kFlag_Unk4 = (1ULL << 43),
			kFlag_Vertex = (1ULL << 44),
			kFlag_UVs = (1ULL << 45),
			kFlag_Unk5 = (1ULL << 46),
			kFlag_Normals = (1ULL << 47),
			kFlag_Tangents = (1ULL << 48),
			kFlag_VertexColors = (1ULL << 49),
			kFlag_Skinned = (1ULL << 50),
			kFlag_Unk6 = (1ULL << 51),
			kFlag_MaleEyes = (1ULL << 52),
			kFlag_Unk7 = (1ULL << 53),
			kFlag_FullPrecision = (1ULL << 54),
			kFlag_Unk8 = (1ULL << 55),
		};

		//members
		NiBound kModelBound;                       // 120
		NiPointer<NiProperty> effectState;         // 130
		NiPointer<NiProperty> shaderProperty;      // 138
		NiPointer<BSSkin::Instance> skinInstance;  // 140
		BSGeometryData* geometryData;  // 148
		std::uint64_t vertexDesc;      // 150
		std::uint8_t ucType;  // 158
		bool Registered;  // 159
		std::uint16_t pad15A;  // 15A
		std::uint32_t unk15C;  // 15C

	};
	static_assert(sizeof(BSGeometry) == 0x160);

	// 170
	class BSTriShape : public BSGeometry
	{
	public:

		static constexpr auto RTTI{ RTTI::BSTriShape };
		static constexpr auto VTABLE{ VTABLE::BSTriShape };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSTriShape };

		//members
		std::uint32_t numTriangles;  // 160
		std::uint16_t numVertices;   // 164
		std::uint16_t unk166;        // 166
		float unk168;         // 168
		float unk16C;         // 16C

	};
	static_assert(sizeof(BSTriShape) == 0x170);

	// 1A0
	class BSDynamicTriShape : public BSTriShape
	{
	public:

		static constexpr auto RTTI{ RTTI::BSDynamicTriShape };
		static constexpr auto VTABLE{ VTABLE::BSDynamicTriShape };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSDynamicTriShape };

		//members
		std::uint32_t uiDynamicDataSize;                     // 170
		std::uint32_t uiFrameCount;                          // 174
		BSSpinLock lock;                              // 178
		std::uint8_t* dynamicVertices;                       // 180 - geometry pointer, must lock/unlock when altering
		NiPointer<BSGeometrySegmentData> spSegments;  // 188
		void* unk190;                                 // 190
		void* unk198;                                 // 198

	};
	//static_assert(sizeof(BSDynamicTriShape) == 0x1A0);

	// 190
	class BSSubIndexTriShape : public BSTriShape
	{
	public:

		static constexpr auto RTTI{ RTTI::BSSubIndexTriShape };
		static constexpr auto VTABLE{ VTABLE::BSSubIndexTriShape };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSSubIndexTriShape };

		struct SegmentData
		{
			ID3D11Buffer* d3d11Buffer;  // 00 - const CLayeredObjectWithCLS<class CBuffer>::CContainedObject::vftable'{forCPrivateDataImpl<struct ID3D11Buffer>'}
			std::uint8_t* segmentBlock;        // 08
			std::uint64_t unk10;               // 10
			std::uint64_t unk18;               // 18
			std::uint64_t unk20;               // 20
			void* unk28;                // 28
			std::uint32_t unk30;               // 30
			std::uint32_t unk34;               // 34
			volatile std::int32_t refCount;   // 38
		};

		//members
		NiPointer<BSGeometrySegmentData> spSegments;  // 170
		SegmentData* segmentData;  // 178
		std::uint32_t numIndices;         // 180
		std::uint32_t unk184;             // 184
		void* unk188;              // 188
	};
	static_assert(sizeof(BSSubIndexTriShape) == 0x190);
}
