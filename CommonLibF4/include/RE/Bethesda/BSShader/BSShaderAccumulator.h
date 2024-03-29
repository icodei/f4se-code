#pragma once
#include "RE/Bethesda/BSGraphics/BSGraphics.h"
#include "RE/Bethesda/BSShader/BSBatchRenderer.h"
#include "RE/Bethesda/BSShader/BSShaderManager.h"
#include "RE/NetImmerse/NiAccumulator.h"
#include "RE/NetImmerse/NiMain/NiColor.h"
#include "RE/NetImmerse/NiMain/NiPoint3.h"

namespace RE
{
	class BSLight;
	class ShadowSceneNode;

	class BSShaderAccumulator : public NiAlphaAccumulator
	{
	public:
		static constexpr auto RTTI{ RTTI::BSShaderAccumulator };
		static constexpr auto VTABLE{ VTABLE::BSShaderAccumulator };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSShaderAccumulator };

		enum BATCHRENDERER_CREATION_MODE
		{
		};

		BSShaderAccumulator() { ctor(); };

		virtual ~BSShaderAccumulator() {}

		//add
		virtual void FinishAccumulatingPreResolveDepth() {}
		virtual void FinishAccumulatingPostResolveDepth() {}

		void ClearActivePasses(bool clearLists)
		{
			using func_t = decltype(&BSShaderAccumulator::ClearActivePasses);
			REL::Relocation<func_t> func{ REL::ID(596187) };
			return func(this, clearLists);
		}

		void ClearEffectPasses()
		{
			using func_t = decltype(&BSShaderAccumulator::ClearEffectPasses);
			REL::Relocation<func_t> func{ REL::ID(1407520) };
			return func(this);
		}

		void ClearGroupPasses(std::int32_t geomGroup, bool freePasses)
		{
			using func_t = decltype(&BSShaderAccumulator::ClearGroupPasses);
			REL::Relocation<func_t> func{ REL::ID(226148) };
			return func(this, geomGroup, freePasses);
		}

		static bool RegisterObject_Standard(BSShaderAccumulator* a_accumulator, BSGeometry* a_geometry, BSShaderProperty* a_property) {
			using func_t = decltype(&BSShaderAccumulator::RegisterObject_Standard);
			REL::Relocation<func_t> func{ REL::ID(289935) };
			return func(a_accumulator, a_geometry, a_property);
		}

		void RenderBatches(std::int32_t passIndex, bool alpha, std::int32_t geometryGroup)
		{
			using func_t = decltype(&BSShaderAccumulator::RenderBatches);
			REL::Relocation<func_t> func{ REL::ID(1048494) };
			return func(this, passIndex, alpha, geometryGroup);
		}

		void RenderBlendedDecals()
		{
			using func_t = decltype(&BSShaderAccumulator::RenderBlendedDecals);
			REL::Relocation<func_t> func{ REL::ID(761249) };
			return func(this);
		}

		void RenderOpaqueDecals()
		{
			using func_t = decltype(&BSShaderAccumulator::RenderOpaqueDecals);
			REL::Relocation<func_t> func{ REL::ID(163409) };
			return func(this);
		}

		//members
		std::int32_t field_58;
		std::int8_t field_5C;
		float StoredSunOcclustionPercent;
		BSGraphics::OcclusionQuery* occlusionQuery;
		std::int64_t field_70;
		std::int32_t field_78;
		std::int8_t field_7C;
		std::int64_t field_80;
		std::int64_t field_88;
		std::int32_t field_90;
		std::int8_t field_94;
		std::int64_t field_98;
		std::int64_t field_A0;
		std::int32_t field_A8;
		std::int32_t field_AC;
		bool firstPerson;
		bool ZPrePass;
		NiColorA SilhouetteColor;
		std::int8_t RenderDecals;
		std::int8_t field_C5;
		BSBatchRenderer batchRenders;
		std::int64_t field_548;
		std::int8_t field_550;
		ShadowSceneNode* activeShadowSceneNode;
		BSShaderManager::etRenderMode renderMode;
		BSLight* shadowLight;
		NiPoint3 eyePosition;
		std::uint32_t DepthPassIndex;
		std::uint64_t gap[(0x590 - 0x580) / 6];

	private:
		BSShaderAccumulator* ctor()
		{
			using func_t = decltype(&BSShaderAccumulator::ctor);
			REL::Relocation<func_t> func{ REL::ID(690952) };
			return func(this);
		}
	};
	static_assert(sizeof(BSShaderAccumulator) == 0x590);
}
