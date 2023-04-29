#pragma once

namespace RE 
{
	struct BSLightingShaderCommonFeatures
	{
		enum
		{
			PROJECTED_UV = 1 << 3,
			ANISO_LIGHTING = 1 << 4,
			PIPBOY_SCREEN = 1 << 5,
			GRADIENT_REMAP = 1 << 6,
			MENU_SCREEN = 1 << 7,
			NEXT_BIT = 1 << 8,

			COUNT = 5
		};
	};
}
