#pragma once

#include "RE/Bethesda/BSShader/BSShaderProperty.h"
#include "RE/Bethesda/BSShader/BSShaderPropertyLightData.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/NetImmerse/NiNode.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BSGeometry;
	class BSLight;

	class __declspec(novtable) BSFadeNode :
		public NiNode  // 000
	{
	public:
		static constexpr auto RTTI{ RTTI::BSFadeNode };
		static constexpr auto VTABLE{ VTABLE::BSFadeNode };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSFadeNode };


		enum AppFrustrumResult : std::int32_t
		{
			TestFrustrum = 0x0,
			DontTestFrustrum = 0x1,
		};

		struct FlattenedGeometryData
		{
		public:
			// members
			NiBound bound;                   // 00
			NiPointer<BSGeometry> geometry;  // 10
			std::uint32_t flags;             // 18
		};
		static_assert(sizeof(FlattenedGeometryData) == 0x20);

		struct FadeUpdateData
		{
		public:
			//members
			NiPoint3 Pos;
			float fFadeAdjust;
		};

		enum MESH_LOD_FADING_MODE : std::int32_t
		{
			MLOD_FADING_OUT_FIRST = 0x0,
			MLOD_FADING_OUT = 0x1,
			MLOD_NOT_FADING = 0x2,
			MLOD_FADING_IN = 0x3,
			MLOD_FADING_IN_FIRST = 0x4,
		};


		// members
		BSShaderPropertyLightData lightData;              // 140
		BSTArray<FlattenedGeometryData> geomArray;        // 168
		BSTAlignedArray<NiBound, 0x10> mergedGeomBounds;  // 180
		float nearDistSqr;                                // 198
		float farDistSqr;                                 // 19C
		float currentFade;                                // 1A0
		float currentDecalFade;                           // 1A4
		float boundRadius;                                // 1A8
		float timeSinceUpdate;                            // 1AC
		std::int32_t frameCounter;                        // 1B0
		float previousMaxA;                               // 1B4
		float currentShaderLODLevel;                      // 1B8
		float previousShaderLODLevel;                     // 1BC
	};
	static_assert(sizeof(BSFadeNode) == 0x1C0);
}
