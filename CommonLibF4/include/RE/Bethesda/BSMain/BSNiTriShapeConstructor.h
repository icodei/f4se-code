#pragma once
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class NiNode;
	class NiPoint3;
	class NiColorA;

	class BSNiTriShapeConstructor
	{
		//using VertexArray = BSScrapArray<NiPoint3> 

		//members
		NiPointer<NiNode> spParentNode;
		NiPoint3*  pVertexArray;
		NiColorA*  pColorArray;
		std::uint16_t*  pIndicesArray;
		std::uint32_t uiVertexCount;
		std::uint32_t uiIndicesCount;
	};
}
