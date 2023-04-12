#pragma once
#include "RE/Havok/Common/Base/Math/Vector/hkVector4.h"
#include "RE/Havok/Common/Base/Types/hkBaseDefs.h"

namespace RE
{
	typedef hkUint16 hkObjectIndex;
	typedef hkReal hkTime;

	//class hkFinishLoadedObjectFlag
	//{
	//	//+hk.MemoryTracker(ignore=True)
	//public:
	//	hkFinishLoadedObjectFlag() :
	//		m_finishing(0) {}
	//	int m_finishing;
	//};

	class hkClass;

	/// A generic object with metadata.

	struct hkVariant
	{
		//+hk.MemoryTracker(ignore=True)
		void* m_object;
		const hkClass* m_class;
	};

	/// A floating point value stored in 16-bit. This is a non IEEE representation using
	/// 1 sign bit, 8 exponent bits and 7 mantissa bits. This is basically a 32-bit float
	/// truncated. It supports the same floating point range as 32-bit float,
	/// but only with 6 bit precision (because the last bit is not rounded and renormalized).
	class hkHalf
	{
		//+hk.MemoryTracker(ignore=True)
	public:
		typedef hkFloat32 Storage;

	private:
		Storage m_value;
	};

	/// A floating point value stored in 16-bit according to the IEEE 754-2008
	/// format 'binary16' which has 1 sign bit, 5 exponent bits and 10 mantissa bits.
	/// This format is compatible with the widely used GPU 'half' variable format.
	/// The supported value range is 6.1035156e-5 to 131008.0 (both pos/neg) with
	/// 10 bit precision.
	///
	/// \warning For performance reasons, our implementation differs from the
	///          IEEE and some GPU definitions in that 32-bit values greater than
	///          the max half value do not get mapped to infinity but to max.
	class hkFloat16
	{
	public:
		//+hk.MemoryTracker(ignore=True)

	public:

	private:
		hkUint16 m_value;
	};

	//#define HK_BOOL32_IS_STRICT
	enum hkBool32FalseType
	{
		hkFalse32 = 0
	};

	typedef hkUint32 hkBool32;
	typedef hkUint64 hkBoolLL;

	/// A wrapper to store a hkBool in one byte, regardless of compiler options.
	class hkBool
	{
		//+hk.MemoryTracker(ignore=True)
	public:

		HK_ALWAYS_INLINE hkBool()
		{
		}

		HK_FORCE_INLINE hkBool(bool b)
		{
			m_bool = static_cast<char>(b);
		}

		HK_FORCE_INLINE operator bool() const
		{
			return m_bool != 0;
		}

		HK_FORCE_INLINE hkBool& operator=(bool e)
		{
			m_bool = static_cast<char>(e);
			return *this;
		}

		HK_FORCE_INLINE hkBool operator==(bool e) const
		{
			return (m_bool != 0) == e;
		}

		HK_FORCE_INLINE hkBool operator!=(bool e) const
		{
			return (m_bool != 0) != e;
		}

	private:
		char m_bool;
	};

	/// A wrapper to store an enum with explicit size.
	template <class ENUM, class STORAGE>
	using hkEnum = stl::enumeration<ENUM, STORAGE>;

	/// A wrapper to store bitfield with an explicit size.
	template <class BITS, class STORAGE>
	using hkFlags = stl::enumeration<BITS, STORAGE>;

	/// wrapper class for variables in structures.
	/// Basically on the PlayStation(R)3 SPU, the SPU can only poorly
	/// access non aligned members. This class give each variable
	/// 16 bytes, thereby dramatically decreasing code size and CPU overhead
	template <class T>
	class hkPadSpu
	{
	public:
		~hkPadSpu() noexcept {}  // NOLINT(modernize-use-equals-default)

		// members
		T storage;
	};

	/// a simple success/failure enum.
	enum class hkResultEnum
	{
		HK_SUCCESS,
		HK_FAILURE
	};

	/// A return type for functions.
	struct hkResult
	{
	public:
		~hkResult() noexcept {}  // NOLINT(modernize-use-equals-default)

		// members
		hkResultEnum e;  // 0
	};
	static_assert(sizeof(hkResult) == 0x4);
}
