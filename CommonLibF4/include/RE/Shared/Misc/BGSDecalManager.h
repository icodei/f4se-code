#pragma once

namespace RE
{
	class DECAL_CREATION_DATA
	{

	};

	class BGSDecalManager
	{
	public:

		static constexpr auto MAX_DYNAMIC_OBJECTS_WITH_DECALS{ 63 };

		static BGSDecalManager* GetSingleton()
		{
			REL::Relocation<BGSDecalManager**> singleton{ REL::ID(716374) };
			return *singleton;
		}

		struct PendingSkinnedDecal
		{

		};


	};
}
