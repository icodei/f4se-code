#pragma once
#include "Global.h"

//I made this not knowing that Heap_Allocate() from f4se does the same thing
//class MemoryManager {
//public:
//
//	MEMBER_FN_PREFIX(MemoryManager);
//	DEFINE_MEMBER_FN(Allocate, void*, 0x01B0EFD0, unsigned __int64 a_size, unsigned int a_alignment, bool a_alignmentRequired);
//
//	void* Allocate(unsigned __int64 a_size, unsigned int a_alignment, bool a_alignmentRequired);
//};
//extern RelocPtr<MemoryManager>	MemoryManager_Instance;

extern RelocPtr<NiPointer<NiCamera>>	spCustomCamera;
extern RelocPtr<NiPointer<NiCamera>>	spCamera;
