#pragma once
#include "RE/NetImmerse/NiObject.h"
//#include "RE/NetImmerse/NiBound.h"

namespace RE
{
	class BSGeometry;
	class NiCamera;
	class NiBound;

	class NiAccumulator : public NiObject
	{
	public:
		static constexpr auto RTTI{ RTTI::NiAccumulator };
		static constexpr auto VTABLE{ VTABLE::NiAccumulator };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiAccumulator };

		virtual ~NiAccumulator();

		//add
		virtual void StartAccumulating(NiCamera* a_camera);
		virtual void FinishAccumulating();
		//_purecall_0 //virtual void RegisterObjectArray(NiVisibleArray &); //???
		virtual void StartGroupingAlphas(NiBound& a_bound, bool a_unk);
		virtual void StopGroupingAlphas();
		virtual bool RegisterObject(BSGeometry* a_geometry);

		//members
		NiCamera* m_pkCamera;  //10
	};
	static_assert(sizeof(NiAccumulator) == 0x18);

	class NiBackToFrontAccumulator : public NiAccumulator
	{
	public:
		static constexpr auto RTTI{ RTTI::NiBackToFrontAccumulator };
		static constexpr auto VTABLE{ VTABLE::NiBackToFrontAccumulator };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiBackToFrontAccumulator };

		virtual ~NiBackToFrontAccumulator();

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

		virtual ~NiAlphaAccumulator();

		//members
		bool m_bObserveNoSortHint;
		bool m_bSortByClosestPoint;
		bool m_bInterfaceSort;
	};
	static_assert(sizeof(NiAlphaAccumulator) == 0x58);
}
