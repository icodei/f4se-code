#pragma once

namespace RE
{
	template <class T>
	struct IBSTCreator
	{
	public:
		virtual ~IBSTCreator();  // 00

	protected:
		// add
		[[nodiscard]] virtual T* CreateImpl() const = 0;  // 01

	public:
		virtual void Destroy(const T* a_val) const = 0;  // 02

		[[nodiscard]] inline T* Create() const
		{
			return CreateImpl();
		}
	};
	static_assert(sizeof(IBSTCreator<void*>) == 0x8);

	template <class Derived, class Parent>
	struct BSTDerivedCreator : public IBSTCreator<Parent>
	{
	public:
		virtual ~BSTDerivedCreator();  // 00

	protected:
		// override (IBSTCreator<Parent>)
		Parent* CreateImpl() const override;  // 01

	public:
		void Destroy(const Parent* a_val) const override;  // 02

		Derived* Create() const
		{
			return static_cast<Derived*>(CreateImpl());
		}
	};
	static_assert(sizeof(BSTDerivedCreator<void*, void*>) == 0x8);

	// auto registers the factory with the manager
	template <class Parent, class Manager>
	class AutoRegisterFactory : public Parent
	{
	public:
		static_assert(sizeof(AutoRegisterFactory) == 0x8);
		virtual ~AutoRegisterFactory();  // 00
	};

	template <class Derived, class Manager>
	struct AutoRegisterCreator : public AutoRegisterFactory<BSTDerivedCreator<Derived, typename Manager::mapped_type>, Manager>
	{
	public:
		virtual ~AutoRegisterCreator();  // 00
	};
}
