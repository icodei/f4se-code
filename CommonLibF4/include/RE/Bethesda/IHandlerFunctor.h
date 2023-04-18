#pragma once
#include "RE/Bethesda/BSSystem/BSFixedString.h"
#include "RE/Bethesda/BSSystem/BSTSmartPointer.h"
#include "RE/Bethesda/BSCore/BSTObjectDictonary.h"
#include "RE/Bethesda/BSSystem/BSTFactory.h"

namespace RE
{
	class Actor;

	template <class Handler, class Parameter>
	class IHandlerFunctor :
		public BSIntrusiveRefCounted  // 08
	{
	public:
		IHandlerFunctor() = default;
		virtual ~IHandlerFunctor() = default;  // 00

		// add
		virtual bool ExecuteHandler(Handler& a_handler, const Parameter& a_parameter) = 0;

		inline bool operator()(Handler& a_handler, const Parameter& a_parameter)
		{
			return ExecuteHandler(a_handler, a_parameter);
		}

		// members
		std::uint32_t pad0C;  // 0C
	};
	//static_assert(sizeof(IHandlerFunctor) == 0x10);

	template <class T, class Key>
	class HandlerCreationMissPolicy
	{
	public:
		virtual ~HandlerCreationMissPolicy();  // 00
	};
	//static_assert(sizeof(HandlerCreationMissPolicy) == 0x8);

	template <class T, class Key>
	class NoInitializationPolicy
	{
	public:
		virtual ~NoInitializationPolicy();  // 00
	};
	//static_assert(sizeof(NoInitializationPolicy) == 0x8);

	class ActorAnimationHandler : public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		static constexpr auto RTTI{ RTTI::IHandlerFunctor_Actor_BSFixedString_ };
		static constexpr auto VTABLE{ VTABLE::IHandlerFunctor_Actor_BSFixedString_ };
	};

	class ActorAnimationHandlerDictionary :
		public BSTObjectDictionary<
			BSTSmartPointer<ActorAnimationHandler>,
			BSFixedString,
			HandlerCreationMissPolicy,
			NoInitializationPolicy>
	{
	public:
		static ActorAnimationHandlerDictionary& GetSingleton()
		{
			REL::Relocation<ActorAnimationHandlerDictionary*> singleton{ REL::ID(340630) };
			return *singleton;
		}

		static ActorAnimationHandlerDictionary* GetSingletonPtr()
		{
			REL::Relocation<ActorAnimationHandlerDictionary**> singleton{ REL::ID(1048465) };
			return *singleton;
		}

		static ActorAnimationHandlerDictionary* GetInstance()
		{
			using func_t = decltype(&ActorAnimationHandlerDictionary::GetInstance);
			REL::Relocation<func_t> func{ REL::ID(755490), 0xE };
			return func();
		}

		static ActorAnimationHandlerDictionary*& GetInstancePtr()
		{
			using func_t = decltype(&ActorAnimationHandlerDictionary::GetInstancePtr);
			REL::Relocation<func_t> func{ REL::ID(930001), 0x100 };
			return func();
		}
	};
	//static_assert(sizeof(HandlerDictionary) == 0x50);

	class ActorAnimationHandlerFactoryManager : public BSTFactoryManager<BSFixedString, IBSTCreator<ActorAnimationHandler>, 256, BSTSingletonImplicit>
	{
	public:
		static ActorAnimationHandlerFactoryManager& GetSingleton()
		{
			REL::Relocation<ActorAnimationHandlerFactoryManager*> singleton{ REL::ID(930001) };
			return *singleton;
		}
	};
}
