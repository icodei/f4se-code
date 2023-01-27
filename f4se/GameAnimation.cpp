#include "f4se/GameAnimation.h"

namespace BGSAnimationSystemUtils {
	RelocAddr<_InitalizeActorInstant> InitalizeActorInstant_Internal(0x0F925F0);
	bool InitializeActorInstant(Actor& a_actor, bool a1) {
		return InitalizeActorInstant_Internal(a_actor, a1);
	}
}