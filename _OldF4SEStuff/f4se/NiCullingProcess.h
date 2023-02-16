#pragma once
#include "f4se/BSCompoundFrustum.h"
#include "f4se/BSPortalGraph.h"
#include "f4se/NiAccumulator.h"
#include "f4se/NiCamera.h"
#include "f4se/NiTypes.h"
#include "f4se_common/Utilities.h"

class NiVisibleArray;

class NiCullingProcess {
public:
	NiCullingProcess() : m_bUseVirtualAppend(0), m_pkVisibleSet(nullptr), m_pkCamera(nullptr), m_kFrustum(), m_kPlanes(), kCustomCullPlanes(), m_bCameraRelatedUpdates(0), bUpdateAccumulateFlag(0), bIgnorePreprocess(0), bCustomCullPlanes(0), bUnknownBool1(0), bUnknownBool2(0) { CALL_MEMBER_FN(this, ctor)(m_pkVisibleSet); };
	NiCullingProcess(NiVisibleArray* a1) : m_bUseVirtualAppend(0), m_pkVisibleSet(nullptr) { CALL_MEMBER_FN(this, ctor)(a1); };
	virtual void GetRTTI() {};
	virtual void IsNode() {};
	virtual void IsNode2() {};
	virtual void IsSwitchNode() {};
	virtual void IsFadeNode() {};
	virtual void IsMultiBoundNode() {};
	virtual void IsGeometry() {};
	virtual void IsTriStrips() {};
	virtual void IsTriShape() {};
	virtual void IsDynamicTriShape() {};
	virtual void IsSegmentedTriShape() {};
	virtual void IsSubIndexTriShape() {};
	virtual void IsNiGeometry() {};
	virtual void IsNiTriBasedGeom() {};
	virtual void IsNiTriShape() {};
	virtual void IsParticlesGeom() {};
	virtual void IsParticleSystem() {};
	virtual void IsLinesGeom() {};
	virtual void IsLight() {};
	virtual void IsBhkNiCollisionObject() {};
	virtual void IsBhkBlendCollisionObject() {};
	virtual void IsBhkRigidBody() {};
	virtual void IsBhkLimitedHingeConstraint() {};
	virtual void IsbhkNPCollisionObject() {};
	virtual ~NiCullingProcess() {};
	virtual void Process() {};
	virtual void Process2() {};
	virtual void AppendVirtual() {};

	const bool m_bUseVirtualAppend;
	NiVisibleArray* m_pkVisibleSet;
	NiCamera* m_pkCamera;
	NiFrustum m_kFrustum;
	NiFrustumPlanes m_kPlanes;
	NiFrustumPlanes kCustomCullPlanes;
	bool m_bCameraRelatedUpdates;
	bool bUpdateAccumulateFlag;
	bool bIgnorePreprocess;
	bool bCustomCullPlanes;
	bool bUnknownBool1;
	bool bUnknownBool2;

	MEMBER_FN_PREFIX(NiCullingProcess);
	DEFINE_MEMBER_FN(ctor, void, 0x01BC4A60, NiVisibleArray*);
	DEFINE_MEMBER_FN(dtor, void, 0x01BC4A40);
};