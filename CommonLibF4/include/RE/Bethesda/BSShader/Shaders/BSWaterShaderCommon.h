#pragma once

namespace RE
{
	namespace BSWaterShaderVertexDecl
	{
		enum
		{
			NONE,
			VERTEX_COLORS = 1 << 0,
			NORMAL_TEXCOORD = 1 << 1,
			NEXT_BIT = 1 << 2,

			COUNT = 2,

			MASK = 3,
		};
	}

	namespace BSWaterShaderCommonFeatures
	{
		enum
		{
			REFLECTIONS = 1 << 2,
			REFRACTIONS = 1 << 3,
			DEPTH = 1 << 4,
			INTERIOR = 1 << 5,
			DISPLACEMENT = 1 << 6,
			VA_DEPTH = 1 << 7,
			CUBEMAP = 1 << 8,
			SSLR = 1 << 9,
			CLIP_VOLUME = 1 << 10,
			DEPTH_WRITE = 1 << 11,
			UNDERWATER = 1 << 12,
			NEXT_BIT = 1 << 13,

			COUNT = 11,
		};
	}

	namespace BSWaterShaderUniqueFeatures
	{
		enum
		{
			SPECULAR_NUM_LIGHTS = 0,
			LOD = 8,
			STENCIL,
			STENCIL_DISPLACEMENT,
			SIMPLE,
			FOG,

			COUNT,

			NUM_BITS = 5,
			MASK = 15,
		};
	}
}
