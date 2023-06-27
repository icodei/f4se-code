#pragma once
#include "RE/Bethesda/BSShader/BSShader.h"
#include "RE/Bethesda/BSShader/BSShaderTechniqueIDMap.h"
#include "RE/NetImmerse/NiMain/NiRefObject.h"

namespace RE
{
	class __declspec(novtable) BSComputeShader :
		public NiRefObject,     // 000
		public BSReloadShaderI  // 010
	{
	public:
		static constexpr auto RTTI{ RTTI::BSComputeShader };
		static constexpr auto VTABLE{ VTABLE::BSComputeShader };

		virtual ~BSComputeShader();

		//add
		virtual void Run(std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t);
		virtual void ReloadShaders(BSIStream*);

		//member
		const char* pFXPFilename;
		BSShaderTechniqueIDMap::MapType<BSGraphics::ComputeShader*> ComputeShaderMap;
	};
}
