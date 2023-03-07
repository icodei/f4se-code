#pragma once
#include "RE/Bethesda/BSLock.h"
#include "RE/Bethesda/BSTArray.h"
#include "RE/NetImmerse/NiNode.h"
#include "RE/NetImmerse/NiPoint3.h"
#include "RE/NetImmerse/NiSmartPointer.h"

namespace RE
{
	class BSShadowDirectionalLight;
	class BSFogProperty; //sizeof 0x88
	class BSPortalGraph;
	class BSLight;
	class NiTexture;

	class BSDeferredDecal // - TODO Add to different file
	{
	public:
		class BSDFDecal
		{};
	};

	//SceneGraphInit
	//	World ShadowSceneNode
	//	0	SkyRoot
	//	1	WeatherRoot
	//	2	LandLOD
	//		0	LandAndObjectLOD
	//		1	WaterLOD
	//		2	LODTrees
	//	3	ObjectLOD
	//	4	Unk
	//	5	BSParticleSystemManager
	//

	class ShadowSceneNode : public NiNode
	{
	public:
		static constexpr auto RTTI{ RTTI::ShadowSceneNode };
		static constexpr auto VTABLE{ VTABLE::ShadowSceneNode };
		static constexpr auto Ni_RTTI{ Ni_RTTI::ShadowSceneNode };

		virtual ~ShadowSceneNode();

		//add

		void ProcessQueuedLights(BSCullingProcess* a_cullingprocess)
		{
			using func_t = decltype(&ShadowSceneNode::ProcessQueuedLights);
			REL::Relocation<func_t> func{ REL::ID(1369106) };
			return func(this, a_cullingprocess);
		}

		//members
		std::uint64_t field_140;
		std::uint64_t field_148;
		std::uint64_t field_150;
		BSTArray<NiPointer<BSLight>> LightArray;
		BSTArray<NiPointer<BSLight>> ShadowLightArray;
		BSTArray<NiPointer<BSLight>> AmbientLightArray;
		BSTArray<NiPointer<BSLight>> QueuedLightArrayMaybe;
		BSTArray<NiPointer<BSLight>> field_1B8;
		BSSpinLock lock;
		BSTArray<NiPointer<BSDeferredDecal::BSDFDecal>> DecalArray;
		std::uint32_t field_1F0;
		std::uint32_t field_1F4;
		BSLight* SunLight;
		BSLight* CloudSunLight;
		BSShadowDirectionalLight* ShadowSunLight;
		BSLight* LocalSunLight;
		std::uint64_t field_218;
		std::uint8_t gap220[4];
		std::uint8_t SceneGraphIndex;
		bool DisableLightUpdate;
		bool Wireframe;
		bool OpaqueWireframe;
		bool AlwaysUpdateLights;
		BSFogProperty* FogProperty;
		BSPortalGraph* PortalGraph;
		BSTArray<void*> ShadowLightForAccumArray;
		std::uint32_t field_258;
		std::uint8_t gap25C[152];
		std::uint32_t field_2F4;
		float WetnessLevel;
		float rainLevel;
		NiPoint3 LightingOffset;
		NiPoint3 EyePosition;
		std::uint8_t field_318;
		NiTexture* WetnessEnvMap;
		float WindMagnitude;
	};
	static_assert(sizeof(ShadowSceneNode) == 0x330);
}
