#pragma once
#include "RE/Bethesda/BSCore/BSTArray.h"
#include "RE/NetImmerse/NiMain/NiMatrix3.h"
#include "RE/NetImmerse/NiMain/NiPoint3.h"
#include "RE/NetImmerse/NiMain/NiRefObject.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

#include <DirectXMath.h>

namespace RE
{
	class BSCullingProcess;
	class BSFadeNode;
	class BSGeometry;
	class BSLensFlareRenderData;
	class BSMultiBoundNode;
	class BSPortalGraph;
	class NiCamera;
	class NiLight;
	class NiNode;
	class NiTexture;

	template <class T>
	using FadeNodeListT = NiTPointerList<T>;

	class BSLight : public NiRefObject
	{
	public:
		static constexpr auto RTTI{ RTTI::BSLight };
		static constexpr auto VTABLE{ VTABLE::BSLight };

		virtual ~BSLight();

		//add
		virtual void SetLight(NiLight* aLight);
		virtual bool GetIsShadowLight();
		virtual void GetProjection(std::uint32_t, DirectX::XMFLOAT4X4A& outValue);

		enum eFrustumCull : std::int32_t
		{
			BSL_NONE = 0x0,
			BSL_POSX = 0x1,
			BSL_NEGX = 0x2,
			BSL_POSY = 0x4,
			BSL_NEGY = 0x8,
			BSL_POSZ = 0x10,
			BSL_NEGZ = 0x20,
			BSL_TILED = 0xFE,
			BSL_ALL = 0xFF,
		};

		enum eShape : std::int32_t
		{
			BSL_SHAPE_NONE = 0x0,
			BSL_SHAPE_SCREENQUAD = 0x1,
			BSL_SHAPE_SPHERE = 0x2,
			BSL_SHAPE_HEMISPHERE = 0x3,
			BSL_SHAPE_OVOID = 0x4,
			BSL_SHAPE_BOX = 0x5,
			BSL_SHAPE_CONE = 0x6,
		};

		//members
		float fLODDimmer;
		float fLuminance;
		std::uint32_t usFrustumCull;
		std::uint32_t pad014;
		std::uint32_t pad018;
		DirectX::XMFLOAT4X4A kGoboProjection;
		NiMatrix3 kShapeRotation;
		NiPoint3A bPointPosition;
		union
		{
			float fCenterAndHalfExtents[6];
			float fRadius;
			float fSpotParam[2];
		};
		NiPointer<NiLight> spLight;
		FadeNodeListT<NiPointer<BSFadeNode>> lFadeNodeList;
		void* kGeomListFence;
		BSTArray<BSMultiBoundNode*> kMultiboundRooms;
		BSTArray<BSPortal*> kPortals;
		BSTArray<NiNode*> kProcessedNodes;
		BSPortalGraph* pPortalGraph;
		BSCullingProcess* pCullingProcess;
		NiPointer<BSGeometry> spGeometry;
		NiPointer<NiCamera> spCamera;
		NiPointer<NiTexture> spGoboTexture;
		std::uint32_t uiAddFadeNodeLock;
		std::uint32_t LensFlareLastFrame;
		std::uint32_t LensFlareFrameCount;
		std::uint32_t LensFlareIndex;
		bool bPointLight;
		bool bAmbientLight;
		bool bDynamicLight;
		bool bPortalStrict;
		bool bShowDebugTexture;
		bool bAffectLand;
		bool bAffectWater;
		bool bLODFade;
		bool bSpecular;
		bool bAttenuationOnly;
		bool bIgnoreRoughness;
		bool bIgnoreRim;
		bool bOccluded;
		bool bStencilVolume;
		bool bTemporary;
		stl::enumeration<BSLight::eShape, std::int32_t> kShape;
		BSLensFlareRenderData* pLensFlare;
	};
	static_assert(sizeof(BSLight) == 0x190);
}
