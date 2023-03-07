#pragma once
#include "RE/Bethesda/BSResource/BSResourceArchive2.h"
#include "RE/Bethesda/BSTEvent.h"


namespace RE
{
	class TESWorldSpace;
	class TESObjectCell;

	struct PositionPlayerEvent;

	class TES : BSTEventSink<BSResource::Archive2::StreamOpenedEvent>, BSTEventSink<PositionPlayerEvent>
	{
	public:
		[[nodiscard]] static TES* GetSingleton()
		{
			REL::Relocation<TES**> singleton{ REL::ID(1194835) };
			return *singleton;
		}

		TESWorldSpace* GetWorldSpace()
		{
			using func_t = decltype(&TES::GetWorldSpace);
			REL::Relocation<func_t> func{ REL::ID(778800) };
			return func(this);
		}

		TESObjectCell* GetSkyCell()
		{
			using func_t = decltype(&TES::GetSkyCell);
			REL::Relocation<func_t> func{ REL::ID(993788) };
			return func(this);
		}

		//members
		std::byte gap[0x138 - 0x10];	//TODO
	};
	static_assert(sizeof(TES) == 0x138);

}
