#pragma once

#include "RE/Bethesda/BSFixedString.h"
#include "RE/Bethesda/BSGraphics.h"
#include "RE/Bethesda/BSTSmartPointer.h"
#include "RE/NetImmerse/NiObject.h"

namespace RE
{
	namespace BSResource
	{
		class Stream;
	}

	struct BSTextureArray
	{
		class Texture;
	};
	static_assert(std::is_empty_v<BSTextureArray>);

	class __declspec(novtable) NiTexture :
		public NiObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::NiTexture };
		static constexpr auto VTABLE{ VTABLE::NiTexture };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiTexture };

		// add
		virtual BSTextureArray::Texture* IsBSTextureArray() { return nullptr; }  // 28

		[[nodiscard]] std::string_view GetName() const { return name; }

		static NiTexture* Create(BSFixedString& name, [[maybe_unused]] bool a1, bool a2)
		{
			using func_t = decltype(&NiTexture::Create);
			REL::Relocation<func_t> func{ REL::ID(1071950) };
			return func(name, a1, a2);
		}

		static NiTexture* CreateEmpty(BSFixedString& name, bool isDDX, [[maybe_unused]] bool a1)
		{
			using func_t = decltype(&NiTexture::CreateEmpty);
			REL::Relocation<func_t> func{ REL::ID(1255534) };
			return func(name, isDDX, a1);
		}

		// members
		BSFixedString name;                          // 10
		std::uint32_t flags;                         // 18
		NiTexture* prev;                             // 29
		NiTexture* next;                             // 28
		BSTSmartPointer<BSResource::Stream> stream;  // 30
		BSGraphics::Texture* rendererTexture;        // 38
		std::int8_t desiredDegradeLevel;             // 40
		std::int8_t savedDegradeLevel;               // 41
		bool isDDX: 1;                               // 42:0
		bool isSRGB: 1;                              // 42:1
	};
	static_assert(sizeof(NiTexture) == 0x48);
}
