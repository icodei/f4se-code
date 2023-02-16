#pragma once
#include "f4se_common/Utilities.h"
#include "f4se/NiAccumulator.h"
#include "f4se/NiCamera.h"
#include "f4se/NiCullingProcess.h"
#include "f4se/NiTypes.h"
#include "f4se/BSCompoundFrustum.h"
#include "f4se/BSPortalGraph.h"

class NiVisibleArray;

//0x1A0
class BSCullingProcess : public NiCullingProcess {
public:

	enum BSCPCullingType {
		kNormal = 0,
		kAllPass = 1,
		kAllFail = 2,
		kIgnoreMultiBounds = 3,
		kForceMultiBoundsNoUpdate = 4
	};

	BSCullingProcess() {};
	BSCullingProcess(NiVisibleArray* a1) { CALL_MEMBER_FN(this, ctor)(a1); };
	~BSCullingProcess() { CALL_MEMBER_FN(this, dtor)(); };
	//virtual void GetRTTI();
	//virtual void IsNode();
	//virtual void IsNode2();
	//virtual void IsSwitchNode();
	//virtual void IsFadeNode();
	//virtual void IsMultiBoundNode();
	//virtual void IsGeometry();
	//virtual void IsTriStrips();
	//virtual void IsTriShape();
	//virtual void IsDynamicTriShape();
	//virtual void IsSegmentedTriShape();
	//virtual void IsSubIndexTriShape();
	//virtual void IsNiGeometry();
	//virtual void IsNiTriBasedGeom();
	//virtual void IsNiTriShape();
	//virtual void IsParticlesGeom();
	//virtual void IsParticleSystem();
	//virtual void IsLinesGeom();
	//virtual void IsLight();
	//virtual void IsBhkNiCollisionObject();
	//virtual void IsBhkBlendCollisionObject();
	//virtual void IsBhkRigidBody();
	//virtual void IsBhkLimitedHingeConstraint();
	//virtual void IsbhkNPCollisionObject();
	//virtual ~BSCullingProcess();
	//virtual void Process();
	//virtual void Process2();
	//virtual void AppendVirtual();

	//add
	virtual void AppendNonAccum() {};
	virtual void TestBaseVisibility_BSMultiBound() {};
	virtual void TestBaseVisibility_BSOcclusionPlane() {};
	virtual void TestBaseVisibility_NiBound() {};

	SInt32 field_128;
	SInt32 field_12C;
	SInt32 field_130;
	SInt32 field_134;
	void* field_138;
	SInt64 gap140;
	SInt64 field_148;
	BSPortalGraphEntry* QPortalGraphEntry;
	BSCPCullingType CullingType;
	UInt8 gap15C[40];
	SInt32 field_184;
	BSCompoundFrustum* field_188;
	NiPointer<NiAccumulator> Accumulator;
	bool QRecurseToGeometry;

	MEMBER_FN_PREFIX(BSCullingProcess);
	DEFINE_MEMBER_FN(ctor, void, 0x01CCDE90, NiVisibleArray*);
	DEFINE_MEMBER_FN(dtor, void, 0x01CCDF10);
	DEFINE_MEMBER_FN(SetAccumulator, void, 0x01CCDF70, NiAccumulator*);

	void SetAccumulator(NiAccumulator* accumulator);
};
//STATIC_ASSERT(sizeof(BSCullingProcess) == 0x1A0);