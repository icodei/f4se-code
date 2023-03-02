#pragma once

namespace RE 
{
	struct BSWaterShaderCommonFeatures
	{
		enum
		{
			REFLECTIONS = 0x4,
			REFRACTIONS = 0x8,
			DEPTH = 0x10,
			INTERIOR = 0x20,
			DISPLACEMENT = 0x40,
			VA_DEPTH = 0x80,
			CUBEMAP = 0x100,
			SSLR = 0x200,
			CLIP_VOLUME = 0x400,
			DEPTH_WRITE = 0x800,
			UNDERWATER = 0x1000,
			NEXT_BIT = 0x2000,

			COUNT = 0xB,
		};
	};
}
