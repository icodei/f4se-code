#pragma once
#include "RE/Bethesda/BSCore/BSTEvent.h"
#include "RE/Shared/Animation/SimpleAnimationGraphManagerHolder.h"
#include "RE/Shared/TempEffects/BSTempEffect.h"
#include "RE/Shared/TempEffects/ReferenceEffect.h"

namespace RE
{
	struct BSAnimationGraphEvent;

	class __declspec(novtable) ModelReferenceEffect :
		public ReferenceEffect,
		public SimpleAnimationGraphManagerHolder,
		public BSTEventSink<BSAnimationGraphEvent>
	{
	public:
		static constexpr auto RTTI{ RTTI::ModelReferenceEffect };
		static constexpr auto VTABLE{ VTABLE::ModelReferenceEffect };
		static constexpr auto Ni_RTTI{ Ni_RTTI::ModelReferenceEffect };
		static constexpr auto TYPE{ TEMP_EFFECT_TYPE::kModelReference };

		enum Flag
		{
		};

		// add

		// members
	};
	//static_assert(sizeof(ModelReferenceEffect) == 0x40);
}
