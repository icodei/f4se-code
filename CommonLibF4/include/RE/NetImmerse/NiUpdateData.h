#pragma once

namespace RE
{
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
		NiUpdateData* ctor(float time, std::uint32_t flags) {
			using func_t = decltype(&NiUpdateData::ctor);
			REL::Relocation<func_t> func{ REL::ID(927837), 0x10 };
			return func(this, time, flags);
		}
	};
}
