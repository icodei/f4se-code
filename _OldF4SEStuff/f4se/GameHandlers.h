#pragma once
#include "f4se/GameTypes.h"
#include "f4se/GameStreams.h"

class Actor;

template <class Handler, class Parameter>
class IHandlerFunctor : public BSIntrusiveRefCounted {
	IHandlerFunctor();
	virtual ~IHandlerFunctor();

	//add
	virtual bool ExecuteHandler(Handler& a_handler, const Parameter& a_parameter);

	inline bool operator()(Handler& a_handler, const Parameter& a_parameter) { return ExecuteHandler(a_handler, a_parameter); }
};

template <class T, class Key>
class HandlerCreationMissPolicy {
public:
	virtual ~HandlerCreationMissPolicy();  // 00
};
STATIC_ASSERT(sizeof(HandlerCreationMissPolicy<void*, void*>) == 0x8);

template <class T, class Key>
class NoInitializationPolicy {
public:
	virtual ~NoInitializationPolicy();  // 00
};
STATIC_ASSERT(sizeof(NoInitializationPolicy<void*, void*>) == 0x8);

template <
	class T,
	class Key,
	template <class, class> class MissPolicy,
	template <class, class> class InitializationPolicy>
class BSTObjectDictionary :
	public MissPolicy<T, Key>,                                                             // 00
	public InitializationPolicy<T, Key>,                                                   // 08
	public BSTSingletonSDM<BSTObjectDictionary<T, Key, MissPolicy, InitializationPolicy>>  // 10
{
public:
	std::uint8_t       pad11;              // 11
	std::uint16_t      pad12;              // 12
	std::uint32_t      pad14;              // 14
	BSTHashMap<Key, T> objectDefinitions;  // 18
	mutable BSSpinLock definitionLock;     // 48
};
//STATIC_ASSERT(sizeof(BSTObjectDictionary) == 0x50);

class HandlerDictionary :
	public BSTObjectDictionary<
	IHandlerFunctor<Actor, BSFixedString>*,
	BSFixedString,
	HandlerCreationMissPolicy,
	NoInitializationPolicy>
{
public:
	static HandlerDictionary* GetSingleton();
};
STATIC_ASSERT(sizeof(HandlerDictionary) == 0x50);

template <class T>
struct IBSTCreator {
public:
	virtual ~IBSTCreator();  // 00

protected:
	// add
	virtual T* CreateImpl();  // 01

public:
	virtual void Destroy(const T* a_val);  // 02

	inline T* Create() { return CreateImpl(); }
};
STATIC_ASSERT(sizeof(IBSTCreator<void*>) == 0x8);

template <class Derived, class Parent>
struct BSTDerivedCreator : public IBSTCreator<Parent> {
public:
	virtual ~BSTDerivedCreator();  // 00

protected:
	// override (IBSTCreator<Parent>)
	Parent* CreateImpl() override;  // 01

public:
	void Destroy(const Parent* a_val) override;  // 02

	Derived* Create() { return static_cast<Derived*>(CreateImpl()); }
};

// auto registers the factory with the manager
template <class Parent, class Manager>
class AutoRegisterFactory : public Parent {
public:
	
	virtual ~AutoRegisterFactory();  // 00
};
STATIC_ASSERT(sizeof(AutoRegisterFactory<void*, void*>) == 0x8);

template <class Derived, class Manager>
struct AutoRegisterCreator : public AutoRegisterFactory<BSTDerivedCreator<Derived, typename Manager::mapped_type>, Manager> {
public:
	virtual ~AutoRegisterCreator();  // 00
};