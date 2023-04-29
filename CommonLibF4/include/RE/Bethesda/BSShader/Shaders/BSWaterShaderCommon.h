#pragma once

namespace RE 
{
	struct BSWaterShaderCommonFeatures
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
	};
}
