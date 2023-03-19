#pragma once

namespace RE
{
	class NiNode;
	class NiPoint3;
	class NiColorA;

	class BSNiLinesConstructor
	{
	public:
		//members
		std::uint32_t uiVertexCount;
		NiPoint3* pVertexArray;
		NiColorA* pColorArray;
		std::uint8_t* pBoolArray;
		NiPointer<NiNode> spParentNode;
	};
}
