#pragma once

namespace RE
{
	enum UPDATE_FLAGS
	{
		UF_UPDATE_CONTROLLERS = 1 << 0,
		UF_UPDATE_PARALLEL = 1 << 1,
		UF_FADENODE_CULLED = 1 << 2,
		UF_SKIP_MULTIBOUNDS = 1 << 3,
		UF_MOVE_COLLISION_USING_VEL = 1 << 8,
		UF_NO_UPWARD_PASS = 1 << 9,
		UF_NO_USING_CHECKS = 1 << 10,
		UF_FOUND_PARTICLES = 1 << 16,
		UF_FOUND_MORPHS = 1 << 17,
		UF_SCENEGRAPH_CHANGE = 1 << 18,
		UF_BOUND_CHANGE = 1 << 19,
		UF_FOUND_TRANSF_CONTROL_UD = 1 << 20,
		UF_FOUND_EFFECT_LIGHTING = 1 << 21,
		UF_SETONUPDATE_MASK = -65536
	};

	class NiUpdateData
	{
	public:
		NiUpdateData() = delete;
		NiUpdateData(float time, std::uint32_t flags) { ctor(time, flags); }

		struct AutoFadeNodeDepth
		{
		public:
			//members
			NiUpdateData* rData;
		};

		//members
		float fTime{ 0.0F };
		std::uint32_t RenderUseDepth{ 0 };
		NiCamera* pCamera{ nullptr };
		std::uint32_t Flags{ 0 };  //NiAVObject::UpdateFlags
		std::uint32_t RenderObjects{ 0 };
		std::uint32_t FadeNodeDepth{ 0 };

	private:
		NiUpdateData* ctor(float time, std::uint32_t flags)
		{
			using func_t = decltype(&NiUpdateData::ctor);
			REL::Relocation<func_t> func{ REL::ID(927837), 0x10 };
			return func(this, time, flags);
		}
	};
}
