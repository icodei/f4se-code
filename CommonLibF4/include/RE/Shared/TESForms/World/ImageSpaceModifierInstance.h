#pragma once
#include "RE/NetImmerse/NiMain/NiObject.h"

namespace RE
{
	class ImageSpaceModifierInstanceForm;

	class ImageSpaceModifierInstance : public NiObject
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstance };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstance };

		//add
		virtual bool IsExpired() { return false; }
		virtual void Apply() = 0;
		virtual void PrintInfo(char*) = 0;
		virtual ImageSpaceModifierInstanceForm* IsForm() { return nullptr; }

		enum FLAGS
		{
			kPermanent = 1 << 0,



			kPlaying = 1 << 4,
		};

		//members
		float strength;					//10
		NiPointer<NiAVObject> target;	//18
		float age;						//20
		std::uint32_t flags;			//24
	};

	class ImageSpaceModifierInstanceForm : public ImageSpaceModifierInstance
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstanceForm };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstanceForm };

		//override
		virtual bool IsExpired() override;
		virtual void Apply() override;
		virtual void PrintInfo(char*) override;
		virtual ImageSpaceModifierInstanceForm* IsForm() override;
	};

	class ImageSpaceModifierInstanceTemp : public ImageSpaceModifierInstance
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstanceTemp };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstanceTemp };

		//override
		virtual bool IsExpired() override;
		virtual void PrintInfo(char*) override;
	};

	class ImageSpaceModifierInstanceDOF : public ImageSpaceModifierInstanceTemp
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstanceDOF };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstanceDOF };

		//override
		virtual void Apply() override;
		virtual void PrintInfo(char*) override;
	};

	class ImageSpaceModifierInstanceRB : public ImageSpaceModifierInstanceTemp
	{
	public:
		static constexpr auto RTTI{ RTTI::ImageSpaceModifierInstanceRB };
		static constexpr auto VTABLE{ VTABLE::ImageSpaceModifierInstanceRB };

		//override
		virtual void Apply() override;
		virtual void PrintInfo(char*) override;
	};
}
