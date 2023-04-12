#pragma once

namespace RE
{
	class hkFinishLoadedObjectFlag
	{
		//+hk.MemoryTracker(ignore=True)
	public:
		hkFinishLoadedObjectFlag() :
			m_finishing(0) {}
		int m_finishing;

	private:
		
	};
}
