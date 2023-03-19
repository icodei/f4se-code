#pragma once
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSCore/BSTScatterTable.h"
#include "RE/NetImmerse/NiObjectNET.h"

namespace RE
{
	class NiCloningProcess
	{
	public:
		//members
		BSTHashMap<NiObject*, NiObject*> m_kCloneMap;
		BSTHashMap<NiObject*, bool> m_kProcessMap;
		NiObjectNET::CopyType m_eCopyType;
		char m_cAppendChar;
		NiPoint3 Scale;
	};

}
