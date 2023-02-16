#pragma once
#include "f4se/NiObjects.h"
#include "f4se/BSCompoundFrustum.h"
#include "f4se/NiNodes.h"

class BSMultiBoundRoom;
class BSMultiBoundNode;

class BSPortalGraph : public NiRefObject {
public:
	BSTArray<void*> QOccluderList; //NiTPointerList<BSOcclusionShape *>
	BSTArray<void*> QPortalList; //NiTPointerList<BSPortal *>
	BSTArray<NiPointer<BSMultiBoundRoom>> QRooms;
	BSTArray<NiPointer<NiAVObject>> QAlwaysRenderArray;
	NiNode* QPortalNodeRoot;
	BSTArray<void*> unk78;
	BSTArray<void*> unk90;
	BSTArray<NiPointer<NiNode>> QUnboundNodes;
	UInt32 QWorldID;
};

class BSPortalGraphEntry : public NiRefObject {
public:
	BSPortalGraph* QPortalGraph;
	BSTArray<NiPointer<BSMultiBoundRoom>> QRoomAccumList;
	BSMultiBoundRoom* QRoomRoot;
	UInt8 gap38[12];
	UInt32 field_44;
	UInt32 field_48;
	UInt32 field_4C;
	UInt32 field_50;
	UInt8 gap54[12];
	UInt64 field_60;
	BSCompoundFrustum QUnboundCompoundFrustum;
	bool QVisibleUnboundSpace;
	UInt32 field_13C;
	UInt16 field_140;
	UInt32 field_144;
	UInt32 field_148;
};