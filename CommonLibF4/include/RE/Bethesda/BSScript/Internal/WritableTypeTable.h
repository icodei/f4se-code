#pragma once

#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"

namespace RE
{
	namespace BSScript
	{
		class ObjectTypeInfo;
		class StructTypeInfo;

		namespace Internal
		{
			class WritableTypeTable
			{
			public:
				// members
				BSTScrapHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>* objectTypeMap;  // 00
				BSTScrapHashMap<BSFixedString, BSTSmartPointer<StructTypeInfo>>* structTypeMap;  // 08
			};
			static_assert(sizeof(WritableTypeTable) == 0x10);
		}
	}
}
