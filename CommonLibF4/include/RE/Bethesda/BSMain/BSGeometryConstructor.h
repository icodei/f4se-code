#pragma once
#include "RE/Bethesda/BSMain/BSNiLinesConstructor.h"
#include "RE/Bethesda/BSMain/BSNiTriShapeConstructor.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class NiNode;

	class BSGeometryConstructor
	{
	public:

		bool IsEmpty()
		{
			using func_t = decltype(&BSGeometryConstructor::IsEmpty);
			REL::Relocation<func_t> func{ REL::ID(1490431), 0x30 };
			return func(this);
		}
		//members
		BSNiTriShapeConstructor TriShapeConstructor;
		BSNiLinesConstructor LinesConstructor;
		NiPointer<NiNode> spParentNode;
	};

}
