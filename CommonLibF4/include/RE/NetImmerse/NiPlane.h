#pragma once
#include "RE/NetImmerse/NiPoint3.h"

namespace RE
{
	struct NiPlane
	{
	public:
		NiPlane() { ctor(); }
		NiPlane(NiPlane& a_copy) { ctorCopy(a_copy); } 

		//members
		NiPoint3 m_kNormal;
		float m_fConstant;

	private:
		NiPlane* ctor() {
			using func_t = decltype(&NiPlane::ctor);
			REL::Relocation<func_t> func{ REL::ID(327814) };
			return func(this);
		}

		NiPlane* ctorCopy(NiPlane& a_copy)
		{
			using func_t = decltype(&NiPlane::ctorCopy);
			REL::Relocation<func_t> func{ REL::ID(476025), 0xF };
			return func(this, a_copy);
		}
	};
}
