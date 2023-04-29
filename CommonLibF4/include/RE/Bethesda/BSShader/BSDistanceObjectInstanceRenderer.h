#pragma once
#include "RE/Bethesda/BSCore/BSTArray.h"

namespace RE
{
	class BSLightingShaderMaterial;
	class BSRenderPass;

	class BSDistantObjectInstanceRenderer
	{
	public:
		struct InstancedGeom
		{
			std::uint64_t unk00;
			NiAVObject* object;
			BSTArray<void*> unk10;
		};

		static BSDistantObjectInstanceRenderer& QInstance()
		{
			using func_t = decltype(&BSDistantObjectInstanceRenderer::QInstance);
			REL::Relocation<func_t> func{ REL::ID(1094113) };
			return func();
		}

		//members
		BSTArray<InstancedGeom> instancedGeomA;
		int field_18;
		BSRenderPass* renderPass;
		BSLightingShaderMaterial* material;
		int field_30;
		NiPoint3 transform;
		NiMatrix3 rotation;
		bool enabled;
	};
	static_assert(sizeof(BSDistantObjectInstanceRenderer) == 0x80);
}
