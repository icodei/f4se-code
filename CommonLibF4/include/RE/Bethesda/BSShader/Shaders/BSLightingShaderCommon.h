#pragma once

namespace RE 
{
	struct BSLightingShaderCommonFeatures
	{
		enum
		{
			PROJECTED_UV = 8,
			ANISO_LIGHTING = 16,
			PIPBOY_SCREEN = 32,
			GRADIENT_REMAP = 64,
			MENU_SCREEN = 128,
			NEXT_BIT = 256,

			COUNT = 5
		};
	};
}
