#pragma once
#include "f4se/GameForms.h"
#include "f4se/GameTypes.h"
#include "f4se/GameFormComponents.h"

class BSSoundHandle {
public:
	~BSSoundHandle() noexcept {}  // NOLINT(modernize-use-equals-default)

	// members
	UInt32 soundID;			// 0
	bool assumeSuccess;     // 4
	UInt8 state;			// 5
};
STATIC_ASSERT(sizeof(BSSoundHandle) == 0x8);

class BGSSoundKeywordMapping : public TESForm {
public:

	// members
	BSTSet<BGSKeyword*> keywordSet;                                    // 20
	BSTHashMap<UInt32, BGSSoundDescriptorForm*> reverbDescMap;		   // 50
	BGSSoundDescriptorForm* descriptor;                                // 80
	BGSSoundDescriptorForm* exteriorTail;                              // 88
	BGSSoundDescriptorForm* vatsDescriptor;                            // 90
	float vatsDescThreshold;                                           // 98
};
STATIC_ASSERT(sizeof(BGSSoundKeywordMapping) == 0xA0);