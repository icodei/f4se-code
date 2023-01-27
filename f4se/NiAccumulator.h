#pragma once
#include "f4se/BSGeometry.h"
#include "f4se/GameObjects.h"
#include "f4se/NiCamera.h"

class NiAccumulator : public NiObject {
public:
	//virtual ~NiAccumulator();
	//NiAccumulator::StartAccumulating
	//NiAccumulator::FinishAccumulating
	//_purecall_0
	//NiAccumulator::StartGroupingAlphas
	//NiAccumulator::StopGroupingAlphas
	//NiAccumulator::RegisterObject

	NiCamera* m_pkCamera;
};

class NiBackToFrontAccumulator : public NiAccumulator {
public:
	//virtual ~NiBackToFrontAccumulator();

	SInt8			_pad[24];
	SInt32			m_iNumItems;
	SInt32			m_iMaxItems;
	BSGeometry** m_ppkItems;
	float* m_pfDepths;
	SInt32			m_iCurrItem;
};

class NiAlphaAccumulator : public NiBackToFrontAccumulator {
public:
	//virtual ~NiAlphaAccumulator();

	bool m_bObserveNoSortHint;
	bool m_bSortByClosestPoint;
	bool m_bInterfaceSort;
};