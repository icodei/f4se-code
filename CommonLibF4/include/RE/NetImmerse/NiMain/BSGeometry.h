#pragma once

#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSMain/BSBound.h"
#include "RE/Bethesda/BSSkin.h"
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"
#include "RE/NetImmerse/NiMain/BSGeometrySegmentData.h"
#include "RE/NetImmerse/NiMain/NiAVObject.h"
#include "RE/NetImmerse/NiMain/NiBound.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class BSDynamicTriShape;
	class NiProperty;
	class NiUpdateData;
	class BSCombinedTriShape;
	class BSMergeInstancedTriShape;
	class BSMultiIndexTriShape;

	struct ID3D11Buffer;

	namespace BSGraphics
	{
		struct IndexBuffer;
	}

	struct GeometryType
	{
		enum : std::int32_t
		{
			GEOMETRY_TYPE_GEOMETRY = 0x0,
			GEOMETRY_TYPE_PARTICLES = 0x1,
			GEOMETRY_TYPE_STRIP_PARTICLES = 0x2,
			GEOMETRY_TYPE_TRISHAPE = 0x3,
			GEOMETRY_TYPE_DYNAMIC_TRISHAPE = 0x4,
			GEOMETRY_TYPE_MESHLOD_TRISHAPE = 0x5,
			GEOMETRY_TYPE_LOD_MULTIINDEX_TRISHAPE = 0x6,
			GEOMETRY_TYPE_MULTIINDEX_TRISHAPE = 0x7,
			GEOMETRY_TYPE_SUBINDEX_TRISHAPE = 0x8,
			GEOMETRY_TYPE_SUBINDEX_LAND_TRISHAPE = 0x9,
			GEOMETRY_TYPE_MULTISTREAMINSTANCE_TRISHAPE = 0xA,
			GEOMETRY_TYPE_PARTICLE_SHADER_DYNAMIC_TRISHAPE = 0xB,
			GEOMETRY_TYPE_LINES = 0xC,
			GEOMETRY_TYPE_DYNAMIC_LINES = 0xD,
			GEOMETRY_TYPE_INSTANCE_GROUP = 0xE,
			GEOMETRY_TYPE_COMBINED_TRISHAPE = 0xF,
		};
	};

	class BSGeometryData
	{
	public:
		struct VertexData
		{
			ID3D11Buffer* d3d11Buffer;       // 00 - const CLayeredObjectWithCLS<class CBuffer>::CContainedObject::`vftable'{for `CPrivateDataImpl<struct ID3D11Buffer>'}
			std::uint8_t* vertexBlock;       // 08
			std::uint64_t unk10;             // 10
			std::uint64_t unk18;             // 18
			std::uint64_t unk20;             // 20
			std::uint64_t unk28;             // 28
			std::uint64_t unk30;             // 30
			volatile std::int32_t refCount;  // 38
		};

		struct TriangleData
		{
			ID3D11Buffer* d3d11Buffer;       // 00 - Same buffer as VertexData
			std::uint16_t* triangles;        // 08
			std::uint64_t unk10;             // 10
			std::uint64_t unk18;             // 18
			std::uint64_t unk20;             // 20
			std::uint64_t unk28;             // 28
			std::uint64_t unk30;             // 30
			volatile std::int32_t refCount;  // 38
		};

		//members
		std::uint64_t vertexDesc;
		VertexData* vertexData;          // 08
		TriangleData* triangleData;      // 10
		volatile std::int32_t refCount;  // 18
	};

	class BSGeometry : public NiAVObject
	{
	public:
		static constexpr auto RTTI{ RTTI::BSGeometry };
		static constexpr auto VTABLE{ VTABLE::BSGeometry };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSGeometry };
		static constexpr auto TYPE{ GeometryType::GEOMETRY_TYPE_GEOMETRY };

		//add
		virtual void UpdatePropertyControllers([[maybe_unused]] NiUpdateData& a_data) { return; }
		virtual BSGeometrySegmentData* GetSegmentData() { return nullptr; }
		virtual void SetSegmentData([[maybe_unused]] BSGeometrySegmentData* a_data) { return; }
		virtual BSGraphics::IndexBuffer* GetCustomIndexBuffer() { return nullptr; }
		virtual BSCombinedTriShape* IsBSCombinedTriShape() { return nullptr; }
		virtual BSMergeInstancedTriShape* IsBSMergeInstancedTriShape() { return nullptr; }
		virtual BSMultiIndexTriShape* IsMultiIndexTriShape() { return nullptr; }
		virtual std::uint32_t GetRenderableTris([[maybe_unused]] std::uint32_t a_unk) { return 0; }

		union VertexDesc
		{
			struct Desc
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

		BSShaderProperty* QShaderProperty()
		{
			using func_t = decltype(&BSGeometry::QShaderProperty);
			REL::Relocation<func_t> func{ REL::ID(1286348) };
			return func(this);
		}

		void SetProperty(NiShadeProperty* a_property)
		{
			using func_t = decltype(&BSGeometry::SetProperty);
			REL::Relocation<func_t> func{ REL::ID(254895), -0x18 };
			return func(this, a_property);
		}

		//members
		NiBound kModelBound;                       // 120
		NiPointer<NiProperty> effectState;         // 130
		NiPointer<NiProperty> shaderProperty;      // 138
		NiPointer<BSSkin::Instance> skinInstance;  // 140
		void* geometryData;                        // 148
		std::uint64_t vertexDesc;                  // 150
		std::uint8_t ucType;                       // 158
		bool Registered;                           // 159
		std::uint16_t pad15A;                      // 15A
		std::uint32_t unk15C;                      // 15C
	};
	static_assert(sizeof(BSGeometry) == 0x160);
}
