#pragma once

#include "RE/NetImmerse/NiMain/NiFlags.h"
#include "RE/NetImmerse/NiMain/NiProperty.h"

namespace RE
{
	class __declspec(novtable) NiAlphaProperty :
		NiProperty  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::NiAlphaProperty };
		static constexpr auto VTABLE{ VTABLE::NiAlphaProperty };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiAlphaProperty };
		static constexpr auto TYPE{ ALPHA };

		NiAlphaProperty() { ctor(); }

		enum class AlphaFunction
		{
			kOne,
			kZero,
			kSrcColor,
			kInvSrcColor,
			kDestColor,
			kInvDestColor,
			kSrcAlpha,
			kInvSrcAlpha,
			kDestAlpha,
			kInvDestAlpha,
			kSrcAlphaTest
		};

		enum class TestFunction
		{
			kAlways,
			kLess,
			kEqual,
			kLessEqual,
			kGreater,
			kNotEqual,
			kGreaterEqual,
			kNever
		};

		bool GetEnableEditorAlphaRef(void) const { return this->flags.flags >> 15; }
		AlphaFunction GetDestBlendMode(void) const { return (AlphaFunction)((this->flags.flags >> 5) & 0xF); }
		bool GetNoSorter(void) const { return (this->flags.flags >> 13) & 1; }
		AlphaFunction GetSrcBlendMode(void) const { return (AlphaFunction)((this->flags.flags >> 1) & 0xF); }
		TestFunction GetTestMode(void) const { return (TestFunction)((this->flags.flags >> 10) & 7); }

		// members
		NiTFlags<std::uint16_t, NiProperty> flags;  // 28
		std::int8_t alphaTestRef;                   // 2A

	private:
		NiAlphaProperty* ctor()
		{
			using func_t = decltype(&NiAlphaProperty::ctor);
			REL::Relocation<func_t> func{ REL::ID(1487963) };
			return func(this);
		}
	};
	static_assert(sizeof(NiAlphaProperty) == 0x30);
}
