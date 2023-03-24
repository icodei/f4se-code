#pragma once
#include "RE/NetImmerse/NiMain/NiObject.h"

namespace RE
{
	class BSGeometry;
	class NiCamera;
	class NiBound;
	class NiVisibleArray;

	class __declspec(novtable) NiAccumulator : public NiObject
	{
	public:
		static constexpr auto RTTI{ RTTI::NiAccumulator };
		static constexpr auto VTABLE{ VTABLE::NiAccumulator };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiAccumulator };

		virtual ~NiAccumulator() {}

		//add
		virtual void StartAccumulating([[maybe_unused]] NiCamera* a_camera) { return; }
		virtual void FinishAccumulating() { return; }
		virtual void RegisterObjectArray([[maybe_unused]] NiVisibleArray& a_array) { return; }
		virtual void StartGroupingAlphas([[maybe_unused]] NiBound& a_bound, [[maybe_unused]] bool a_unk) { return; }
		virtual void StopGroupingAlphas() { return; }
		virtual bool RegisterObject([[maybe_unused]] BSGeometry* a_geometry) { return false; }

		//members
		NiCamera* m_pkCamera{ nullptr };  //10
	};
	static_assert(sizeof(NiAccumulator) == 0x18);

	class NiBackToFrontAccumulator : public NiAccumulator
	{
	public:
		static constexpr auto RTTI{ RTTI::NiBackToFrontAccumulator };
		static constexpr auto VTABLE{ VTABLE::NiBackToFrontAccumulator };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiBackToFrontAccumulator };

		virtual ~NiBackToFrontAccumulator() {}

		//members
		std::uint64_t field_18;     //18
		std::uint64_t field_20;     //20
		int field_28;               //28
		int field_2C;               //2C
		std::uint64_t m_iMaxItems;  //30
		BSGeometry** m_ppkItems;    //38
		float* m_pfDepths;          //40
		std::uint32_t m_iCurrItem;  //48
	};
	static_assert(sizeof(NiBackToFrontAccumulator) == 0x50);

	class NiAlphaAccumulator : public NiBackToFrontAccumulator
	{
	public:
		static constexpr auto RTTI{ RTTI::NiAlphaAccumulator };
		static constexpr auto VTABLE{ VTABLE::NiAlphaAccumulator };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiAlphaAccumulator };

		virtual ~NiAlphaAccumulator() {}

		//members
		bool m_bObserveNoSortHint;
		bool m_bSortByClosestPoint;
		bool m_bInterfaceSort;
	};
	static_assert(sizeof(NiAlphaAccumulator) == 0x58);
}
