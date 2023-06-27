#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"

namespace RE
{
	namespace BSBloodSplatterCommonFeatures
	{
	}

	namespace BSBloodSplatterUniqueFeatures
	{
		enum Technique
		{
			NONE,          //Names
			SPLATTER = 0,  //Splatter
			FLARE          //Flare
		};

		enum Feature
		{
			None,
		};
	}

	namespace BSBloodSplatterShaderVertexConstants
	{
		enum Constant
		{
			None = static_cast<std::underlying_type_t<Constant>>(-1),  //Size
			WorldViewProj = 0,                                         //04
			LightLoc,                                                  //01
			Ctrl                                                       //00
		};
		const char* GetString(std::uint32_t constant);
	}

	namespace BSBloodSplatterPixelConstants
	{
		enum Constant : std::uint8_t
		{
			None = static_cast<std::underlying_type_t<Constant>>(-1),  //Size
			Alpha = 0                                                  //00
		};
		const char* GetString(std::uint32_t constant);
	}

	namespace BSBloodSplatterSamplers
	{
		enum Constant
		{
			None = static_cast<std::underlying_type_t<Constant>>(-1),
			BloodColor = 0,
			BloodAlpha,
			FlareColor,
			FlareHDR
		};
		const char* GetString(std::uint32_t constant);
	}

	namespace BSBloodSplatterMacros
	{
	}

	class BSBloodSplatterShader : public BSShader
	{
		static constexpr auto RTTI{ RTTI::BSBloodSplatterShader };
		static constexpr auto VTABLE{ VTABLE::BSBloodSplatterShader };
		static constexpr auto TYPE{ BSShaderManager::BSSM_SHADER_BLOODSPLATTER };

		static constexpr auto TECHNIQUE_COUNT{ 2 };

		void* unk;
	};
	static_assert(sizeof(BSBloodSplatterShader) == 0x120);
}
