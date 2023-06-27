#pragma once
#include "RE/Bethesda/BSResource/BSResourceEnums.h"

namespace RE
{
	enum ENUM_LOD_MULT
	{
	};

	namespace BSModelDB
	{
		struct DBTraits
		{
		public:
			static constexpr auto RTTI{ RTTI::BSModelDB__DBTraits };

			struct ArgsType
			{
			public:
				//members
				ENUM_LOD_MULT LODmult{ (ENUM_LOD_MULT)0 };  // 0
				std::uint32_t texLoadLevel{ 3 };            // 4
				bool unk8{ true };                          // 8
				bool unk9{ false };                         // 9
				bool unkA{ true };                          // A
				bool postProcess{ true };                   // B
			};
		};

		//BSResource::ErrorCode Demand(char const*, BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>, BSResource::EntryDBTraits<BSModelDB::DBTraits, BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>&, BSModelDB::DBTraits::ArgsType const&)
		//{
		//}

		BSResource::ErrorCode Demand(char const* a_filepath, NiPointer<NiNode>& a_return, DBTraits::ArgsType const& a_args)
		{
			using func_t = decltype(&BSModelDB::Demand);
			REL::Relocation<func_t> func{ REL::ID(1225688) };
			return func(a_filepath, a_return, a_args);
		}
	}
}
