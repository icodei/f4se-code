#pragma once
#include "RE/Havok/Common/Base/Types/hkBaseDefs.h"
#include "RE/Havok/Common/Base/Types/hkBaseTypes.h"

namespace RE
{
	/// Intermediate value for pointer return values. To avoid a resource leak,
	/// it needs to have a reference removed when the object is no longer needed.
	/// Usually this type is used as an intermediate return value for functions and will
	/// be assigned directly to a hkRefPtr.
	/// Note that this indicates a newly added reference, not necessarily a new object, i.e.
	/// the returned object may be shared.
	template <typename TYPE>
	class hkRefNew
	{
	public:
		/// Implicit conversion from raw pointer.
		hkRefNew(TYPE* t) :
			m_pntr(t) {}
		/// Assume ownership of this reference.
		/// Assumes responsibility for calling removeReference in the future.
		TYPE* stealOwnership()
		{
			TYPE* t = m_pntr;
			m_pntr = HK_NULL;
			return t;
		}

	private:
		hkRefNew();                         ///< Not implemented
		void operator=(const hkRefNew& b);  ///< Not implemented
		TYPE* m_pntr;
	};

	/// The contained object is owned by another object. Usually used as an intermediate
	/// value for function return types, it indicates that a reference has not been added to
	/// the returned object. It is still owned and managed by somebody else. If the owning object
	/// is modified, the reference may become invalid (dangling pointer).
	/// Assign to a hkRefPtr to prevent the reference being removed prematurely.
	template <typename TYPE>
	class hkRefLoan
	{
	public:
		/// Implicit conversion from raw pointer.
		hkRefLoan(TYPE* t) :
			m_pntr(t) {}
		/// Implicit conversion to raw pointer.
		operator TYPE*() const { return m_pntr; }

	private:
		hkRefLoan();                         ///< Not implemented
		void operator=(const hkRefLoan& b);  ///< Not implemented
		TYPE* m_pntr;
	};

	/// A simple helper class to automatically add and remove references to objects.
	template <class TYPE>
	class hkRefPtr
	{
	public:
		typedef hkRefPtr<TYPE> ThisType;

		/// Default constructor.
		/// Stored pointer is set to HK_NULL.
		HK_FORCE_INLINE hkRefPtr() :
			m_pntr(HK_NULL)
		{
		}

		/// Copy constructor.
		/// Increase reference count for object in 'rp' and set pointer to it.
		HK_FORCE_INLINE hkRefPtr(const hkRefPtr& rp)
		{
			if (rp.m_pntr) {
				rp.m_pntr->addReference();
			}
			m_pntr = rp.m_pntr;
		}

		/// Add a reference count for object in 'rp' and set pointer to it.
		HK_FORCE_INLINE hkRefPtr(hkRefLoan<TYPE> rp)
		{
			if (TYPE* t = rp) {
				t->addReference();
			}
			m_pntr = rp;
		}

		/// Steal (don't increment) the reference from 'rp'.
		HK_FORCE_INLINE hkRefPtr(hkRefNew<TYPE> rp)
		{
			m_pntr = rp.stealOwnership();
		}

		/// Constructor from pointer.
		/// Increase reference count for object 'e' and set the pointer to it.
		HK_FORCE_INLINE hkRefPtr(TYPE* e)
		{
			if (e) {
				e->addReference();
			}
			m_pntr = e;
		}

		/// Destructor.
		/// Decrease reference count for stored object.
		HK_FORCE_INLINE ~hkRefPtr()
		{
			if (m_pntr) {
				m_pntr->removeReference();
			}
			m_pntr = HK_NULL;
		}

		/// Assignment operator.
		/// Increase reference count for object in 'rp',
		/// decrease reference count for stored object and set pointer to object from 'rp'.
		HK_FORCE_INLINE void operator=(const hkRefPtr& rp)
		{
			if (rp.m_pntr) {
				rp.m_pntr->addReference();  // add reference first to allow self-assignment
			}
			if (m_pntr) {
				m_pntr->removeReference();
			}
			m_pntr = rp.m_pntr;
		}

		/// Assignment operator.
		/// Increase reference count for object in 'rp',
		/// decrease reference count for stored object and set pointer to object from 'rp'.
		HK_FORCE_INLINE void operator=(hkRefLoan<TYPE> rp)
		{
			operator=(static_cast<TYPE*>(rp));
		}

		/// Assignment operator.
		/// Steals (does not increment) the reference from 'rp'.
		/// Decrease the original reference count and set pointer to object from 'rp'.
		HK_FORCE_INLINE void operator=(hkRefNew<TYPE> rp)
		{
			if (m_pntr) {
				m_pntr->removeReference();
			}
			m_pntr = rp.stealOwnership();
		}

		/// Assignment operator.
		/// Increase reference count for object 'e',
		/// decrease reference count for stored object and set pointer to 'e'.
		HK_FORCE_INLINE void operator=(TYPE* e)
		{
			if (e) {
				e->addReference();  // add reference first to allow self-assignment
			}
			if (m_pntr) {
				m_pntr->removeReference();
			}
			m_pntr = e;
		}

		/// Return pointer to stored object.
		HK_FORCE_INLINE TYPE* val() const
		{
			return m_pntr;
		}

		/// Pointer to stored object.
		HK_FORCE_INLINE TYPE* operator->() const
		{
			return m_pntr;
		}

		/// Replace stored pointer with 'e' without incrementing reference count for 'e'.
		/// Reference count for previously stored object is decreased.
		HK_FORCE_INLINE void setAndDontIncrementRefCount(TYPE* e)
		{
			if (m_pntr && m_pntr != e) {
				m_pntr->removeReference();
			}
			m_pntr = e;
		}

		/// Unset stored pointer without decreasing the reference count.
		HK_FORCE_INLINE void unsetAndDontDecrementRefCount()
		{
			m_pntr = HK_NULL;
		}

		/// Return pointer to stored object.
		HK_FORCE_INLINE operator TYPE*() const
		{
			return val();
		}

	private:
		TYPE* m_pntr;
	};
}
