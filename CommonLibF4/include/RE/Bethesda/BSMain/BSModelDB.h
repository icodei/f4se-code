#pragma once
#include "RE/Bethesda/BSResource/BSResourceEnums.h"
#include "RE/Bethesda/BSResource/BSResourceHandle.h"
#include "RE/Bethesda/BSResource/BSResourceEntryDB.h"
#include "RE/Bethesda/BSResource/BSResourceEntry.h"

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
				// members
				stl::enumeration<ENUM_LOD_MULT, std::int32_t> lodFadeMult;  // 00
				std::uint32_t loadLevel;                                    // 04
				std::uint8_t prepareAfterLoad: 1;                           // 08:00
				std::uint8_t faceGenModel: 1;                               // 08:01
				std::uint8_t useErrorMarker: 1;                             // 08:02
				std::uint8_t performProcess: 1;                             // 08:03
				std::uint8_t createFadeNode: 1;                             // 08:04
				std::uint8_t loadTextures: 1;                               // 08:05
			};
			static_assert(sizeof(ArgsType) == 0x0C);

			static BSResource::EntryDB<BSModelDB::DBTraits>* GetSingleton()
			{
				REL::Relocation<BSResource::EntryDB<BSModelDB::DBTraits>**> singleton{ REL::ID(45807) };
				return *singleton;
			}
		};
		static_assert(std::is_empty_v<DBTraits>);

		/*static BSResource::ErrorCode Demand(
			const char* a_name,
			BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>, BSResource::EntryDBTraits<BSModelDB::DBTraits, BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>& a_result,
			const DBTraits::ArgsType& a_args)
		{
			using func_t = BSResource::ErrorCode (*)(const char*, BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>, BSResource::EntryDBTraits<BSModelDB::DBTraits, BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>&, const DBTraits::ArgsType&);
			REL::Relocation<func_t> func{ REL::ID(1066398) };
			return func(a_name, a_result, a_args);
		}*/

		/*static BSResource::ErrorCode Demand(
			const char* a_name,
			NiPointer<NiNode>* a_result,
			const DBTraits::ArgsType& a_args)
		{
			using func_t = BSResource::ErrorCode (*)(const char*, NiPointer<NiNode>*, const DBTraits::ArgsType&);
			REL::Relocation<func_t> func{ REL::ID(1225688) };
			return func(a_name, a_result, a_args);
		}*/
	}
}
