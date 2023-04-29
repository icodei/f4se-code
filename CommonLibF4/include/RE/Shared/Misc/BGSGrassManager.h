#pragma once
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSCore/BSTArray.h"

namespace RE
{
	class GrassType;

	class BGSGrassManager
	{
	public:
		[[nodiscard]] static BGSGrassManager* GetSingleton()
		{
			REL::Relocation<BGSGrassManager**> singleton{ REL::ID(347939) };
			return *singleton;
		}

		//members
		bool gap0;
		bool bGenerateGrassDataFiles;
		std::byte pad[6];
		BSTHashMap<std::uint64_t, GrassType*> grassTypes;
		void* lockerMaybe;
		BSTArray<void*> instanceShapesA;
		float grassFade;
		NiNode* grassNode;
		int iGrassEvalSize;
		int field_6C;
		int field_70;
		std::byte gap74[4];
		void* field_78;
		bool enabled;
	};
}
