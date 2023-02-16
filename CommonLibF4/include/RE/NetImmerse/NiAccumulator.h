#pragma once
#include "RE/NetImmerse/NiObject.h"

namespace RE
{
	class BSGeometry;
	class NiCamera;

	class NiAccumulator : public NiObject
	{
	public:
		static constexpr auto RTTI{ RTTI::NiAccumulator };
		static constexpr auto VTABLE{ VTABLE::NiAccumulator };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiAccumulator };

		//virtual ~NiAccumulator();
		//virtual StartAccumulating
		//virtual FinishAccumulating
		//_purecall_0
		//virtual StartGroupingAlphas
		//virtual StopGroupingAlphas
		//virtual RegisterObject

		//members
		NiCamera* m_pkCamera;
	};

	class NiBackToFrontAccumulator : public NiAccumulator
	{
	public:

		static constexpr auto RTTI{ RTTI::NiBackToFrontAccumulator };
		static constexpr auto VTABLE{ VTABLE::NiBackToFrontAccumulator };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiBackToFrontAccumulator };

		//virtual ~NiBackToFrontAccumulator();

		//members
		std::uint8_t _pad[24];
		std::uint32_t m_iNumItems;
		std::uint32_t m_iMaxItems;
		BSGeometry** m_ppkItems;
		float* m_pfDepths;
		std::uint32_t m_iCurrItem;
	};

	class NiAlphaAccumulator : public NiBackToFrontAccumulator
	{
	public:

		static constexpr auto RTTI{ RTTI::NiAlphaAccumulator };
		static constexpr auto VTABLE{ VTABLE::NiAlphaAccumulator };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiAlphaAccumulator };

		//virtual ~NiAlphaAccumulator();

		//members
		bool m_bObserveNoSortHint;
		bool m_bSortByClosestPoint;
		bool m_bInterfaceSort;
	};
}
