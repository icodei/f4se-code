#pragma once

#include "f4se/f4se_common/Utilities.h"

#include "f4se/NiObjects.h"
#include "f4se/BSLight.h"
#include "f4se/BSGraphics.h"
#include "f4se/BSGeometry.h"

class BSShaderPropertyLightData;

// 140
class NiNode : public NiAVObject {
public:
	NiNode() : NiNode(0) { };
	NiNode(UInt16 children) { CALL_MEMBER_FN(this, ctor)(children); };

	//virtual NiRTTI		* GetRTTI(void) override;
	//virtual NiNode		* GetAsNiNode(void) override;
	//virtual const NiNode* IsNode(void) const override;
	//virtual NiObject*	CreateClone(NiCloningProcess* unk1) override;
	//virtual void		LoadBinary(void* stream) override; // LoadBinary
	//virtual void		Unk_1C() override;
	//virtual bool		Unk_1D() override;
	//virtual void		SaveBinary(void* stream) override; // SaveBinary
	//virtual bool		IsEqual(NiObject* object) override; // IsEqual
	//virtual void		ProcessClone(NiCloningProcess& a_cloning) override;
	//virtual void		UpdateControllers(NiUpdateData& a_data) override;
	//virtual void		PerformOp() override;
	//virtual void		AttachProperty() override;
	//virtual NiAVObject* GetObjectByName(BSFixedString& nodeName) override { CALL_MEMBER_FN(this, GetObjectByName_Internal)(nodeName); };
	//virtual void		SetSelectiveUpdateFlags(bool* unk1, bool unk2, bool* unk3) override;
	//virtual void		UpdateDownwardPass() override;
	//virtual void		UpdateSelectedDownwardPass() override;
	//virtual void		UpdateRigidDownwardPass() override;
	//virtual void		UpdateWorldBound() override;
	//virtual void		UpdateTransformAndBounds(NiUpdateData& a_data) override;
	//virtual void		UpdateTransforms(NiUpdateData& a_data) override;
	//virtual void		OnVisible(void) override;
	
	//add
	virtual void		Unk_39(void) {};
	virtual void		AttachChild(NiAVObject* obj, bool firstAvail) {};
	virtual void		InsertChildAt(UInt32 index, NiAVObject* obj) {};
	virtual void		DetachChild(NiAVObject* obj, NiPointer<NiAVObject>& out) {};
	virtual void		RemoveChild(NiAVObject* obj) {};
	virtual void		DetachChildAt(UInt32 i, NiPointer<NiAVObject>& out) {};
	virtual void		RemoveChildAt(UInt32 i) {};
	virtual void		SetAt(UInt32 index, NiAVObject* obj, NiPointer<NiAVObject>& replaced) {};
	virtual void		SetAt(UInt32 index, NiAVObject* obj) {};
	virtual void		UpdateUpwardPass(void) {};

	NiTArray <NiAVObject*>	m_children;	// 120
	float					unk138;
	float					unk13C;

	static NiNode * Create(UInt16 children = 0);

	MEMBER_FN_PREFIX(NiNode);
	DEFINE_MEMBER_FN(ctor, NiNode*, 0x01B98920, UInt16 children);
	DEFINE_MEMBER_FN(GetObjectByName_Internal, NiAVObject*, 0x01B990F0, const BSFixedString& name);

	NiAVObject* GetObjectByName_Internal(const BSFixedString& name);
};
STATIC_ASSERT(sizeof(NiNode) == 0x140);

// 1C0
class BSFadeNode : public NiNode {
public:
	virtual ~BSFadeNode();

	struct FlattenedGeometryData {
		NiBound					kBound;		// 00
		NiPointer<BSGeometry>	spGeometry;	// 10
		UInt32					uiFlags;	// 18
	};

	BSShaderPropertyLightData		kLightData;					// 140
	tArray<FlattenedGeometryData*>	kGeomArray;					// 168
	tArray<NiBound>					MergedGeomBoundsA;			// 180
	float							fNearDistSqr;				// 198
	float							fFarDistSqr;				// 19C
	float							fCurrentFade;				// 1A0
	float							fCurrentDecalFade;			// 1A4
	float							fBoundRadius;				// 1A8
	float							fTimeSinceUpdate;			// 1AC
	SInt32							iFrameCounter;				// 1B0
	float							fPreviousMaxA;				// 1B4
	float							fCurrentShaderLODLevel;		// 1B8
	float							fPreviousShaderLODLevel;	// 1BC
};

// 190
class BSFaceGenNiNode : public NiNode
{
public:
	UInt64	unk140[(0x178 - 0x140) >> 3];	// 140
	UInt32	unk178;							// 178

	// 1FA2A8F9E63D0F771FC6A9BAB875E88A9215810B
	enum
	{
		kFlag_UpdateModel	= (1 << 0),
		kFlag_Unk1			= (1 << 7),
		kFlag_Unk2			= (1 << 8)
	};

	UInt32					flags;			// 17C
	UInt64					unk180;			// 180
	UInt64					unk188;			// 188
};


class BSSceneGraph : public NiNode {
public:
	virtual ~BSSceneGraph();

	//add
	virtual void GetFarDistance();
	virtual void GetNearDistance();
	virtual void SetViewDistanceBasedOnFrameRate();

};

class SceneGraph : public BSSceneGraph {
public:
	virtual ~SceneGraph();

	MEMBER_FN_PREFIX(SceneGraph);
};

class ShadowSceneNode : public NiNode {
public:
	virtual ~ShadowSceneNode();

	MEMBER_FN_PREFIX(ShadowSceneNode);
	DEFINE_MEMBER_FN(ProcessQueuedLights, void, 0x028101E0, BSCullingProcess*);

	void ProcessQueuedLights(BSCullingProcess* cullproc);
};