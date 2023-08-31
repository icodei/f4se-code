#pragma once
#include "RE/Bethesda/BSCore/BSTHashMap.h"
#include "RE/Bethesda/BSCore/BSTScatterTable.h"
#include "RE/NetImmerse/NiObjectNET.h"

namespace RE
{
	class NiCloningProcess
	{
	public:
		NiCloningProcess() = delete;
		NiCloningProcess(std::uint32_t unk) { ctor(unk); }
		~NiCloningProcess() { dtor(); }

		template <class Key, class T>
		using CloneMapType = BSTHashMap<Key, T>;

		template <class Key, class T>
		using ProcessMapType = BSTHashMap<Key, T>;

		//members
		CloneMapType<NiObject*, NiObject*> m_kCloneMap;
		ProcessMapType<NiObject*, bool> m_kProcessMap;
		stl::enumeration<NiObjectNET::CopyType, std::int32_t> m_eCopyType{ NiObjectNET::COPY_EXACT };
		char m_cAppendChar{ '$' };
		NiPoint3 Scale{ NiPoint3::UNIT_ALL };

	private:
		NiCloningProcess* ctor(std::uint32_t unk)
		{
			using func_t = decltype(&NiCloningProcess::ctor);
			REL::Relocation<func_t> func{ REL::ID(1510731), 0x3 };
			return func(this, unk);
		}
		void* dtor()
		{
			using func_t = decltype(&NiCloningProcess::dtor);
			REL::Relocation<func_t> func{ REL::ID(241551) };
			return func(this);
		}
	};

}
