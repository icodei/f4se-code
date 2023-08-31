#pragma once
#include "RE/NetImmerse/NiMain/NiObject.h"

namespace RE
{
	class TESImageSpaceModifier;
	class TESImageSpaceModifierForm;
	class ImageSpaceModifierInstanceForm;

	class ImageSpaceModifierFinder
	{
	public:
		// members
		TESImageSpaceModifierForm* modifier;  // 00
		const BSFixedString& modifierToFind;  // 08
	};
	static_assert(sizeof(ImageSpaceModifierFinder) == 0x10);

	class ImageSpaceModifierInstance : public NiObject
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstance };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstance };

		virtual ~ImageSpaceModifierInstance();  // 00

		//add
		virtual bool IsExpired() { return false; }                            // 28
		virtual void Apply() = 0;                                             // 29
		virtual void PrintInfo(char*) = 0;                                    // 2A
		virtual ImageSpaceModifierInstanceForm* IsForm() { return nullptr; }  // 2B

		enum FLAGS
		{
			kPermanent = 1 << 0,

			kPlaying = 1 << 4,
		};

		//members
		float strength;                //10
		NiPointer<NiAVObject> target;  //18
		float age;                     //20
		std::uint32_t flags;           //24
	};
	static_assert(sizeof(ImageSpaceModifierInstance) == 0x28);

	class ImageSpaceModifierInstanceForm : public ImageSpaceModifierInstance
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstanceForm };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstanceForm };

		virtual ~ImageSpaceModifierInstanceForm();  // 00

		//override
		virtual bool IsExpired() override;                          // 28
		virtual void Apply() override;                              // 29
		virtual void PrintInfo(char*) override;                     // 2A
		virtual ImageSpaceModifierInstanceForm* IsForm() override;  // 2B

		static ImageSpaceModifierInstanceForm* Trigger(const BSFixedString& a_name)
		{
			using func_t = decltype(&ImageSpaceModifierInstanceForm::Trigger);
			REL::Relocation<func_t> func{ REL::ID(1216312) };
			return func(a_name);
		}

		static void Stop(const BSFixedString& a_name)
		{
			using func_t = decltype(&ImageSpaceModifierInstanceForm::Stop);
			REL::Relocation<func_t> func{ REL::ID(549773) };
			return func(a_name);
		}

		// members
		TESImageSpaceModifier* imageSpaceMod;      // 28
		TESImageSpaceModifier* lastImageSpaceMod;  // 30
		float lastStrength;                        // 38
		NiPointer<NiAVObject> lastTarget;          // 40
		float transitionTime;                      // 48
	};
	static_assert(sizeof(ImageSpaceModifierInstanceForm) == 0x50);

	class ImageSpaceModifierInstanceTemp : public ImageSpaceModifierInstance
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstanceTemp };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstanceTemp };

		virtual ~ImageSpaceModifierInstanceTemp();  // 00

		// override (ImageSpaceModifierInstance)
		virtual bool IsExpired() override;                // 28
		virtual void PrintInfo(char* a_buffer) override;  // 2A

		// members
		float duration;  // 28
	};
	static_assert(sizeof(ImageSpaceModifierInstanceTemp) == 0x30);

	class ImageSpaceModifierInstanceDOF : public ImageSpaceModifierInstanceTemp
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstanceDOF };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstanceDOF };

		virtual ~ImageSpaceModifierInstanceDOF();  // 00

		// override (ImageSpaceModifierInstanceTemp)
		virtual void Apply() override;                    // 29
		virtual void PrintInfo(char* a_buffer) override;  // 2A

		// members
		ImageSpaceModData data;  // 30
	};
	static_assert(sizeof(ImageSpaceModifierInstanceDOF) == 0x80);

	class ImageSpaceModifierInstanceRB : public ImageSpaceModifierInstanceTemp
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstanceRB };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstanceRB };

		virtual ~ImageSpaceModifierInstanceRB();  // 00

		// override (ImageSpaceModifierInstanceTemp)
		virtual void Apply() override;                    // 29
		virtual void PrintInfo(char* a_buffer) override;  // 2A

		// members
		ImageSpaceModData data;  // 30
	};
	static_assert(sizeof(ImageSpaceModifierInstanceRB) == 0x80);
}
