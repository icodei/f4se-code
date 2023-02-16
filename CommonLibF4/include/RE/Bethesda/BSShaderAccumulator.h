#pragma once
#include "RE/Bethesda/BSBatchRenderer.h"
#include "RE/Bethesda/BSGraphics.h"
#include "RE/NetImmerse/NiAccumulator.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiPoint3.h"

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
		//virtual ~BSShaderAccumulator();

		//BSShaderAccumulator::StartAccumulating
		//BSShaderAccumulator::FinishAccumulating
		//NiAlphaAccumulator::RegisterObjectArray
		//BSShaderAccumulator::StartGroupingAlphas
		//BSShaderAccumulator::StopGroupingAlphas
		//BSShaderAccumulator::RegisterObject
		//BSShaderAccumulator::FinishAccumulatingPreResolveDepth
		//BSShaderAccumulator::FinishAccumulatingPostResolveDepth

		void ClearActivePasses(bool a1)  //0x0282F080
		{
		}

		void ClearEffectPasses()  //0x0282EED0
		{
		}

		void ClearGroupPasses(std::int32_t a1, bool a2)  //0x0282EAD0
		{
		}

		void RenderBatches(std::int32_t a1, bool a2, std::int32_t a3)  //0x0282EF70
		{
		}

		void RenderBlendedDecals()  //0x0282E300
		{
		}

		void RenderOpaqueDecals()  //0x0282E190
		{
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
		bool m_firstPerson;
		bool QZPrePass;
		NiColorA QSilhouetteColor;
		std::int8_t QRenderDecals;
		std::int8_t field_C5;
		BSBatchRenderer BatchRenderer;
		std::int64_t field_548;
		std::int8_t field_550;
		ShadowSceneNode* ShadowSceneNode;
		BSShaderManager::etRenderMode renderMode;
		BSLight* shadowLight;
		NiPoint3 QEyePosition;
		std::uint32_t QDepthPassIndex;

	private:
		BSShaderAccumulator* ctor()  //0x0282CC00
		{
		}
	};
}
