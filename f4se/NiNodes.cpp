#include "f4se/NiNodes.h"

NiNode * NiNode::Create(UInt16 children) {
	NiNode * node = (NiNode*)Heap_Allocate(sizeof(NiNode));
	CALL_MEMBER_FN(node, ctor)(children);
	return node;
}

NiAVObject* NiNode::GetObjectByName_Internal(const BSFixedString& name) {
	return CALL_MEMBER_FN(this, GetObjectByName_Internal)(name);
};

void ShadowSceneNode::ProcessQueuedLights(BSCullingProcess* cullproc) {
	CALL_MEMBER_FN(this, ProcessQueuedLights)(cullproc);
}
