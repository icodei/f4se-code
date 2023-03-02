#pragma once
#include "RE/Bethesda/BSShader/BSShaderProperty.h"

namespace RE
{
	class BSWaterShaderProperty : public BSShaderProperty
	{
	public:
		static constexpr auto RTTI{ RTTI::BSWaterShaderProperty };
		static constexpr auto VTABLE{ VTABLE::BSWaterShaderProperty };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSWaterShaderProperty };

		enum EWaterShaderPropertyFlag
		{
			BSWSP_DISPLACEMENT = 0x0,
			BSWSP_LOD = 0x1,
			BSWSP_DEPTH = 0x2,
			BSWSP_ACTOR_IN_WATER = 0x3,
			BSWSP_ACTOR_IN_WATER_IS_MOVING = 0x4,
			BSWSP_UNDERWATER = 0x5,
			BSWSP_REFLECTIONS = 0x6,
			BSWSP_REFRACTIONS = 0x7,
			BSWSP_VERTEX_UV = 0x8,
			BSWSP_VERTEX_ALPHA_DEPTH = 0x9,
			BSWSP_PROCEDURAL = 0xA,
			BSWSP_FOG = 0xB,
			BSWSP_UPDATE_CONSTANTS = 0xC,
			BSWSP_CUBEMAP = 0xD,
		};

		//members
		std::uint32_t uiWaterFlags;
		std::uint32_t iStencilMask;
		NiPlane kWaterPlane;
		RenderPassArray kSimpleRenderPassArray;
		RenderPassArray kRainOcclusionMapRenderPassList;
		BSShaderPropertyLightData kLightData;
	};
}
