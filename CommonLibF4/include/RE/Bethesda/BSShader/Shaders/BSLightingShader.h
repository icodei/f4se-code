#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	class BSLightingShader : public BSShader
	{
		static constexpr auto RTTI{ RTTI::BSLightingShader };
		static constexpr auto VTABLE{ VTABLE::BSLightingShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_LIGHTING };

		static constexpr auto X{ 0 };
		static constexpr auto Y{ 1 };
		static constexpr auto Z{ 2 };
		static constexpr auto W{ 3 };

		static constexpr auto TECHNIQUE_COUNT{ 0x540000 };

		static BSLightingShader* GetInstance()
		{
			REL::Relocation<BSLightingShader**> instance{ REL::ID(482744) };
			return *instance;
		}

		std::byte gap[0x158 - 0x118];
	};
	static_assert(sizeof(BSLightingShader) == 0x158);
}
