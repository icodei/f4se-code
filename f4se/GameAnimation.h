#pragma once
#include "f4se/GameTypes.h"

class Actor;

class IPostAnimationChannelUpdateFunctor {
public:
	virtual ~IPostAnimationChannelUpdateFunctor();  // 00

	// add
	virtual void DoPostAnimationChannelUpdate();  // 01
};
STATIC_ASSERT(sizeof(IPostAnimationChannelUpdateFunctor) == 0x8);

struct SubgraphHandle {
public:
	// members
	UInt64 handle;  // 0
};
STATIC_ASSERT(sizeof(SubgraphHandle) == 0x8);

template <class>
class AnimationStanceFireLocationData {

};

template <class T>
class AnimationStanceNodeLocationData {
public:
	// members
	T nodeLocationArray[3];  // 00
};

struct SubgraphIdentifier {
public:
	// members
	size_t identifier;  // 0
};
STATIC_ASSERT(sizeof(SubgraphIdentifier) == 0x8);

struct SubGraphIdleRootData {
public:
	// members
	SubgraphIdentifier	subGraphID;		// 00
	BSFixedString		idleRootName;   // 08
	UInt8				count;          // 10
	UInt8				activeCount;    // 11
	bool				forFirstPerson; // 12
};
STATIC_ASSERT(sizeof(SubGraphIdleRootData) == 0x18);

namespace BGSAnimationSystemUtils {
	typedef bool(*_InitalizeActorInstant)(Actor&, bool);
	bool InitializeActorInstant(Actor& a_actor, bool a1);
}