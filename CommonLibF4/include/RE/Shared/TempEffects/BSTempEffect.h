#pragma once
#include "RE/NetImmerse/NiMain/NiObject.h"

namespace RE
{
	class BGSSaveGameBuffer;

	enum class TEMP_EFFECT_TYPE : std::uint32_t
	{
		kTerrain,
		kWeaponBlood,
		kScreenSpaceDecal,
		kGeometryDecal,
		kParticle,
		kDebris,
		kSPG,
		kEffect,
		kReference,
		kModelReference,
		kShaderReference,
	};

	class __declspec(novtable) BSTempEffect :
		public NiObject  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSTempEffect };
		static constexpr auto VTABLE{ VTABLE::BSTempEffect };
		static constexpr auto Ni_RTTI{ Ni_RTTI::BSTempEffect };
		static constexpr auto TYPE{ TEMP_EFFECT_TYPE::kEffect };

		BSTempEffect() { ctor(); }
		BSTempEffect(TESObjectCELL* a_cell, float a_time) { ctor2(a_cell, a_time); }
		virtual ~BSTempEffect() {}

		// add
		virtual void Initialize() { return; };
		virtual void Attach() { return; };
		virtual void Detach() { return; };
		virtual bool Update(float) { return false; };
		virtual NiAVObject* Get3D() { return nullptr; };
		virtual bool GetManagerHandlesSaveLoad() { return false; };
		virtual bool GetClearWhenCellIsUnloaded() { return false; };
		virtual TEMP_EFFECT_TYPE GetType() { return TYPE; };
		virtual void SaveGame(BGSSaveGameBuffer*) { return; };
		virtual void LoadGame(BGSLoadGameBuffer*) { return; };
		virtual void FinishLoadGame(BGSLoadGameBuffer*) { return; };
		virtual bool IsInterfaceEffect() { return false; };
		virtual void SetInterfaceEffect() { return; };
		virtual bool GetStackable() { return false; };
		virtual bool GetStackableMatch(BSTempEffect*) { return false; };
		virtual void Push() { return; };
		virtual void Pop() { return; };
		virtual void HandleDeferredDeleteImpl() { return; };

		// members
		float lifetime;
		std::uint32_t pad14;
		TESObjectCELL* cell;
		float age;
		bool active;
		std::uint32_t effectID;
		NiAVObject* obj;
		ObjectRefHandle target;

	private:
		BSTempEffect* ctor()
		{
			using func_t = decltype(&BSTempEffect::ctor);
			REL::Relocation<func_t> func{ REL::ID(3328) };
			return func(this);
		}

		BSTempEffect* ctor2(TESObjectCELL* a_cell, float a_time)
		{
			using func_t = decltype(&BSTempEffect::ctor2);
			REL::Relocation<func_t> func{ REL::ID(176918) };
			return func(this, a_cell, a_time);
		}
	};
	static_assert(sizeof(BSTempEffect) == 0x40);
}
