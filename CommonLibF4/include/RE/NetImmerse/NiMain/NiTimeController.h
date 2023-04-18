#pragma once

#include "RE/NetImmerse/NiMain/NiFlags.h"
#include "RE/NetImmerse/NiMain/NiObject.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class NiObjectNET;
	class NiUpdateData;

	class __declspec(novtable) NiTimeController :
		public NiObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::NiTimeController };
		static constexpr auto VTABLE{ VTABLE::NiTimeController };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiTimeController };



		// add
		virtual void Start(float a_time);                             // 28
		virtual void Stop();                                          // 28
		virtual void Update(NiUpdateData& a_updateData) = 0;          // 29
		virtual void SetTarget(NiObjectNET* a_target);                // 2A
		virtual bool IsTransformController() const { return false; }  // 2B
		virtual bool IsVertexController() const { return false; }     // 2C
		virtual float ComputeScaledTime(float a_time);                // 2D
		virtual void OnPreDisplay() { return; }                       // 2E
		virtual bool IsStreamable() const { return true; }            // 2F
		virtual void Start() = 0;                                     // 30

		enum AnimType : std::int32_t
		{
			APP_TIME,
			APP_INIT,
		};

		enum CycleType : std::int32_t
		{
			LOOP = 0x0,
			REVERSE = 0x1,
			CLAMP = 0x2,
			MAX_CYCLE_TYPES = 0x3,
		};

		enum : std::int32_t
		{
			MAX_POS = 0x5
		};

		enum : std::int32_t
		{
			ANIMTYPE_MASK = 1,
			ANIMTYPE_POS = 0,
			CYCLETYPE_MASK = 6,
			CYCLETYPE_POS = 1,
			ACTIVE_MASK = 1 << 3,
			DIRECTION_MASK = 1 << 4,
			MANAGERCONTROLLED_MASK = 1 << 5,
			COMPUTESCALEDTIME_MASK = 1 << 6,
			FORCEUDPATE_MASK = 1 << 7,
			MANDATORYUPDATE_MASK = 1 << 8
		};

		// members
		NiTFlags<std::uint16_t, NiTimeController> flags;  // 10
		float frequency;                                  // 14
		float phase;                                      // 18
		float loKeyTime;                                  // 1C
		float hiKeyTime;                                  // 20
		float startTime;                                  // 24
		float lastTime;                                   // 28
		float weightedLastTime;                           // 2C
		float scaledTime;                                 // 30
		NiObjectNET* target;                              // 38
		NiPointer<NiTimeController> next;                 // 40
	};
	static_assert(sizeof(NiTimeController) == 0x48);
}
