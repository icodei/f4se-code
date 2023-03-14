#pragma once
#include "RE/Bethesda/BSPortalGraph.h"
#include "RE/NetImmerse/NiMain/NiCullingProcess.h"
#include "RE/NetImmerse/NiMain/NiSmartPointer.h"

namespace RE
{
	class BSCompoundFrustum;
	class BSMultiBound;
	class BSOcclusionPlane;
	class NiAccumulator;
	class NiAVObject;
	class NiBound;
	class NiVisibleArray;

	class BSCullingProcess : public NiCullingProcess
	{
	public:
		static constexpr auto RTTI{ RTTI::BSCullingProcess };
		static constexpr auto VTABLE{ VTABLE::BSCullingProcess };

		enum BSCPCullingType
		{
			BSCP_CULL_NORMAL = 0x0,
			BSCP_CULL_ALLPASS = 0x1,
			BSCP_CULL_ALLFAIL = 0x2,
			BSCP_CULL_IGNOREMULTIBOUNDS = 0x3,
			BSCP_CULL_FORCEMULTIBOUNDSNOUPDATE = 0x4,
		};

		BSCullingProcess() = delete;
		BSCullingProcess(NiVisibleArray* a_array) :
			NiCullingProcess(0)
		{
			ctor(a_array);
		};

		//add
		virtual void AppendNonAccum(NiAVObject& a_object) { return; };
		virtual bool TestBaseVisibility_BSMultiBound(BSMultiBound& a_bound) { return false; };
		virtual bool TestBaseVisibility_BSOcclusionPlane(BSOcclusionPlane& a_plane) { return false; };
		virtual bool TestBaseVisibility_NiBound(NiBound& a_bound) { return false; };

		void SetAccumulator(NiAccumulator* accumulator) {
			using func_t = decltype(&BSCullingProcess::SetAccumulator);
			REL::Relocation<func_t> func{ REL::ID(236955) };
			return func(this, accumulator);
		}

		//members
		std::uint32_t field_128;
		std::uint32_t field_12C;
		std::uint32_t field_130;
		std::uint32_t field_134;
		void* field_138;
		std::uint64_t gap140;
		std::uint64_t field_148;
		BSPortalGraphEntry* QPortalGraphEntry;
		BSCPCullingType CullingType;
		std::uint8_t gap15C[40];
		std::uint32_t field_184;
		BSCompoundFrustum* pCompoundFrustum;
		NiPointer<NiAccumulator> spAccumulator;
		bool bRecurseToGeometry;

	private:
		BSCullingProcess* ctor(NiVisibleArray* a_array)
		{
			using func_t = decltype(&BSCullingProcess::ctor);
			REL::Relocation<func_t> func{ REL::ID(423200) };
			return func(this, a_array);
		};
	};
	static_assert(sizeof(BSCullingProcess) == 0x1A0);
}
