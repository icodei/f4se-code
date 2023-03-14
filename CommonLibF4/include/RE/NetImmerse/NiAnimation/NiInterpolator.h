#pragma once
#include "RE/NetImmerse/NiMain/NiColor.h"
#include "RE/NetImmerse/NiMain/NiObject.h"
#include "RE/NetImmerse/NiMain/NiPoint3.h"
#include "RE/NetImmerse/NiMain/NiQuatTransform.h"
#include "RE/NetImmerse/NiMain/NiQuaternion.h"

namespace RE
{
	class NiAVObjectPalette;
	class NiBoolInterpolator;

	class NiInterpolator : public NiObject
	{
	public:
		static constexpr auto RTTI{ RTTI::NiInterpolator };
		static constexpr auto VTABLE{ VTABLE::NiInterpolator };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiInterpolator };

		virtual ~NiInterpolator() { return; }

		//add
		virtual bool Update_QuatTransform(float, NiObjectNET*, NiQuatTransform&) { return false; }
		virtual bool Update_ColorA(float, NiObjectNET*, NiColorA&) { return false; }
		virtual bool Update_Point3(float, NiObjectNET*, NiPoint3&) { return false; }
		virtual bool Update_Quaternion(float, NiObjectNET*, NiQuaternion&) { return false; }
		virtual bool Update_Float(float, NiObjectNET*, float&) { return false; }
		virtual bool Update_Bool(float, NiObjectNET*, bool&) { return false; }
		virtual bool IsBoolValueSupported() { return false; }
		virtual bool IsFloatValueSupported() { return false; }
		virtual bool IsQuaternionValueSupported() { return false; }
		virtual bool IsPoint3ValueSupported() { return false; }
		virtual bool IsColorAValueSupported() { return false; }
		virtual bool IsTransformValueSupported() { return false; }
		virtual void Collapse() { return; }
		virtual void GuaranteeTimeRange(float, float) { return; }
		virtual NiInterpolator* GetSequenceInterpolator(float, float) { return nullptr; }
		virtual bool ResolveDependencies(NiAVObjectPalette*) { return false; }
		virtual bool SetUpDependencies() { return false; }
		virtual bool AlwaysUpdate() { return false; }
		virtual NiBoolInterpolator* IsNiBoolInterpolator() { return nullptr; }

		//members
		float m_fLastTime;
	};
}
