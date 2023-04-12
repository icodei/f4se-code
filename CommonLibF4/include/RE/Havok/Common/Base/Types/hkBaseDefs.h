#pragma once

namespace RE
{
#ifndef HKBASE_HKBASEDEFS_H
#	define HKBASE_HKBASEDEFS_H
#	define HK_REAL_IS_FLOAT

//
// compiler
//
#	if defined(_MSC_VER)  // Intel compiler defines this too (most of the time, not on LRB etc though)
#		define HK_COMPILER_MSVC
#	else
#		error Could not detect compiler
#	endif

//
// architecture
//
#	if defined(_M_AMD64) || defined(_M_X64)
#		define HK_ARCH_X64
#		define HK_ARCH_INTEL
#		define HK_ENDIAN_LITTLE 1
#		define HK_ENDIAN_BIG 0
#		define HK_POINTER_SIZE 8
#		define HK_ARCH_SUPPORTS_INT64
#		define HK_NUM_SIMD_REGISTERS 16
#	else
#		error Could not autodetect target architecture
#	endif

#	ifndef HK_NATIVE_ALIGN_CHECK
#		define HK_NATIVE_ALIGN_CHECK 0xf  // ptr & 0xf == 0 for 16 bytes
#	endif
//
// platform
//
#	if defined(_WIN32)
#		define HK_PLATFORM_WIN32
#		if defined(_WIN64)
#			define HK_PLATFORM_X64
#		endif
#		ifndef HK_PLATFORM_IS_CONSOLE
#			define HK_PLATFORM_IS_CONSOLE 0
#		endif
#	else
#		error Could not autodetect target platform.
#	endif

#	if defined(HK_COMPILER_MSVC)
#		define HK_ALIGN_OF(T) __alignof(T)
#	else
#		error fixme
#	endif

	//
	// useful macros
	//

#	if (defined(DEBUG) || defined(_DEBUG) || defined(HK_DEBUG)) && !defined(HK_DISABLE_DEBUG)
#		undef HK_DEBUG
#		define HK_DEBUG
#		define HK_ON_DEBUG(CODE) CODE
#	else
#		undef HK_DEBUG
#		define HK_ON_DEBUG(CODE)
#	endif

// use the compiler friendly but programmer ugly version for release only
#	ifdef HK_DEBUG
#		define HK_MULTILINE_MACRO_BEGIN do {
#		define HK_MULTILINE_MACRO_END \
			}                          \
			while (0)
#	else
#		define HK_MULTILINE_MACRO_BEGIN if (1) {
#		define HK_MULTILINE_MACRO_END \
			}                          \
			else
#	endif

#	if defined(HK_ARCH_X64)
#		if defined(HK_COMPILER_MSVC)
#			define HK_BREAKPOINT(ID) __debugbreak();
#		else
#			error unknown asm syntax for PC platform
#		endif
#	else
#		define HK_BREAKPOINT(ID) ((*((int*)0)) = ID);
#	endif

	// Utility structure, for use with the HK_DEBUG_ONLY_MEMBER macro. This class
	// should not be used directly.
	template <typename T>
	struct hkDebugOnlyMember
	{
		hkDebugOnlyMember() :
			member() {}

	private:
		T member;
	};

	// Debug-only members, for use with state assertions. All such members should
	// be declared with //+serialized(false), if declared in a reflected class.

#	if defined(HK_DEBUG) || defined(__HAVOK_PARSER__)  // In debug mode, or for reflection, declare normally
#		define HK_DEBUG_ONLY_MEMBER(TYPE, NAME) TYPE NAME
#	else  // In release mode, declare as inaccessible padding, to prevent accidental use
#		define HK_DEBUG_ONLY_MEMBER(TYPE, NAME) hkDebugOnlyMember<TYPE> NAME
#	endif

#	define HK_NULL 0

#	if __cplusplus >= 201103
#		define HK_OVERRIDE override
#		define HK_FINAL final
#		define HK_FINAL_OVERRIDE final override
#	elif defined(HK_COMPILER_MSVC)
#		if (_MSC_VER >= 1700)
#			define HK_OVERRIDE override
#			define HK_FINAL final
#			define HK_FINAL_OVERRIDE final override
#		elif (_MSC_VER >= 1600)
#			define HK_OVERRIDE override
#			define HK_FINAL sealed
#			define HK_FINAL_OVERRIDE sealed override
#		elif (_MSC_VER >= 1400)
#			define HK_OVERRIDE override
#			define HK_FINAL
#			define HK_FINAL_OVERRIDE override
#		else
#			define HK_OVERRIDE
#			define HK_FINAL
#			define HK_FINAL_OVERRIDE
#		endif
#	else
#		define HK_OVERRIDE
#		define HK_FINAL
#		define HK_FINAL_OVERRIDE
#	endif

/// Note that ALIGNMENT must be a power of two for this to work.
/// Note: to use this macro you must cast your pointer to a byte pointer or to an integer value.
#	define HK_NEXT_MULTIPLE_OF(ALIGNMENT, VALUE) (((VALUE) + ((ALIGNMENT)-1)) & (~((ALIGNMENT) + (VALUE)*0 - 1)))

/// The offset of a member within a structure
#	define HK_OFFSET_OF(CLASS, MEMBER) int(reinterpret_cast<hkLong>(&(reinterpret_cast<CLASS*>(16)->MEMBER)) - 16)

/// A check for whether the offset of a member within a structure is as expected
#	define HK_OFFSET_EQUALS(CLASS, MEMBER, OFFSET) (HK_OFFSET_OF(CLASS, MEMBER) == OFFSET)

/// Join two preprocessor tokens, even when a token is itself a macro.
#	define HK_PREPROCESSOR_JOIN_TOKEN(A, B) HK_PREPROCESSOR_JOIN_TOKEN2(A, B)
#	define HK_PREPROCESSOR_JOIN_TOKEN2(A, B) HK_PREPROCESSOR_JOIN_TOKEN3(A, B)
#	define HK_PREPROCESSOR_JOIN_TOKEN3(A, B) A##B

/// Creates an uninitialized buffer large enough for object of type TYPE to fit in while aligned to ALIGN boundary. Creates a pointer VAR to this aligned address.
#	define HK_DECLARE_ALIGNED_LOCAL_PTR(TYPE, VAR, ALIGN) \
		const int VAR##BufferSize = ALIGN + sizeof(TYPE);  \
		char VAR##Buffer[VAR##BufferSize];                 \
		TYPE* VAR = reinterpret_cast<TYPE*>(HK_NEXT_MULTIPLE_OF(ALIGN, hkUlong(VAR##Buffer)));

	//
	// compiler specific settings
	//

	// *************************************
	//			MICROSOFT and INTEL
	// *************************************
#	if defined(HK_COMPILER_MSVC)
#		define HK_COMPILER_SUPPORTS_PCH
#		define HK_COMPILER_MSVC_VERSION _MSC_VER
#		ifdef __INTEL_COMPILER
#			define HK_COMPILER_INTEL_VERSION __INTEL_COMPILER
#		else
#			define HK_COMPILER_INTEL_VERSION _MSC_VER
#		endif
#		if (_MSC_VER >= 1400)  // 2005 only
#			define HK_RESTRICT __restrict
#		else
#			define HK_RESTRICT
#		endif
#		pragma warning(disable: 4786)  // Debug tuncated to 255:
#		pragma warning(disable: 4530)  // C++ Exception handler used but not enabled:(used in <xstring>)
#		if defined(HK_PLATFORM_WIN32)
#			define HK_ALIGN(DECL, ALIGNMENT) __declspec(align(ALIGNMENT)) DECL
#			define HK_ALIGN8(DECL) __declspec(align(8)) DECL
#			define HK_ALIGN16(DECL) __declspec(align(16)) DECL
#			define HK_ALIGN32(DECL) __declspec(align(32)) DECL
#			define HK_ALIGN64(DECL) __declspec(align(64)) DECL
#			define HK_ALIGN128(DECL) __declspec(align(128)) DECL
#			define HK_FORCE_INLINE __forceinline
#			define HK_CLASSALIGN(DECL, ALIGNMENT) HK_ALIGN(DECL, ALIGNMENT)
#			define HK_CLASSALIGN8(DECL) HK_ALIGN8(DECL)
#			define HK_CLASSALIGN16(DECL) HK_ALIGN16(DECL)
#			define HK_VISIBILITY_HIDDEN /*empty*/
#			define HK_NEVER_INLINE __declspec(noinline)
#		else
#			error "fix the alignment on this platform"
#		endif
#		if defined(HK_ARCH_X64)
	typedef unsigned __int64 hkUint64;
	typedef __int64 hkInt64;
	typedef __int64 hkSystemTime;
	typedef unsigned __int64 hk_size_t;
#			ifdef HK_ARCH_LRB
#				define HK_COMPILER_HAS_INTRINSICS_LRB
#			else
#				define HK_COMPILER_HAS_INTRINSICS_IA32
#			endif
#		else
#			error No defs for this architecture
#		endif
	// calling convention
#		if defined(HK_DYNAMIC_DLL)
#			if defined(HK_COMMON_BUILD)  // DLL export for base etc
#				define HK_EXPORT_COMMON __declspec(dllexport)
#				define HK_EXPORT_COMMON_TEMPLATE_SPECIALIZATION
#			else  // Being used in a non common build, but still a dll
#				define HK_EXPORT_COMMON __declspec(dllimport)
#				define HK_EXPORT_COMMON_TEMPLATE_SPECIALIZATION extern  // see http://support.microsoft.com/kb/168958
#			endif
#		endif
#		ifndef HK_COMPILER_INTEL
#			define HK_CALL __cdecl
#			define HK_FAST_CALL __fastcall
#		else
#			define HK_CALL
#			define HK_FAST_CALL
#		endif
// deprecation
#		if defined(HK_PLATFORM_WIN32) && (_MSC_VER >= 1300) && !defined(MIDL_PASS)
#			define HK_DEPRECATED __declspec(deprecated)
#			define HK_DEPRECATED2(MSG) __declspec(deprecated(MSG))
#		else
#			define HK_DEPRECATED       /* nothing */
#			define HK_DEPRECATED2(MSG) /* nothing */
#		endif

#	else
#		error Unknown compiler
#	endif  // compilers

#	ifndef HK_LINKONCE_VTABLES
#		define HK_LINKONCE_VTABLES 1
#	endif

#	ifndef HK_HASHCODE_VTABLE_REGISTRY
#		define HK_HASHCODE_VTABLE_REGISTRY 0
#	endif

#	ifndef HK_NATIVE_ALIGNMENT
#		define HK_NATIVE_ALIGNMENT 16
#	endif

// Product not in DLL mode (as yet)
#	define HK_EXPORT_BEHAVIOR
#	define HK_EXPORT_CLOTH
#	define HK_EXPORT_PHYSICS_2012
#	define HK_EXPORT_DESTRUCTION
#	define HK_EXPORT_DESTRUCTION_2012
#	define HK_EXPORT_FX_PHYSICS

#	ifndef HK_EXPORT_COMMON
#		define HK_EXPORT_COMMON
#		define HK_EXPORT_COMMON_TEMPLATE_SPECIALIZATION
#		ifndef HK_DYNAMIC_DLL  // then not in a DLL build at all. Define all products to none so that no impact in code to existing setups
#			define HK_EXPORT_ANIMATION
#			define HK_EXPORT_PHYSICS
#			define HK_EXPORT_AI
#		endif
#	endif

#	define HK_ON_PLATFORM_SIM(code)

#	define HK_ON_PLATFORM_HAS_SPU(code)

#	define HK_PLATFORM_MULTI_THREAD

#	define HK_ALWAYS_INLINE HK_FORCE_INLINE
#	define HK_LOCAL_INLINE HK_FORCE_INLINE
#	define HK_ASM_SEP(a)

#	ifndef HK_AUTO_INLINE
#		define HK_AUTO_INLINE HK_FORCE_INLINE
#	endif

#	if defined(HK_PLATFORM_SPU)
#		define HK_NOSPU_VIRTUAL
// This macro is implemented to define DMA destinations as const on CPU/PPU and non-const on SPU
#		define HK_CPU_CONST
#	else
#		define HK_NOSPU_VIRTUAL virtual
#		define HK_CPU_CONST const
#	endif

#	ifndef HK_RESTRICT
#		define HK_RESTRICT
#	endif
#	ifndef HK_VERY_UNLIKELY
#		define HK_VERY_UNLIKELY(EXPR) EXPR
#		define HK_VERY_LIKELY(EXPR) EXPR
#	endif
#	ifndef HK_INIT_FUNCTION
#		define HK_INIT_FUNCTION(FN) FN
#		define HK_INIT_FUNCTION2(FN, SECTION_SUFFIX) FN
#	endif

//
// HK_STD_NAMESPACE definition
//
#	ifndef HK_STD_NAMESPACE  // nothing
#		define HK_STD_NAMESPACE
#	endif

// VS 2008 x64 compiler bug workaround
#	if defined(HK_COMPILER_MSVC) && (_MSC_VER == 1500) && defined(HK_ARCH_X64) && defined(HK_COMPILER_OPTIMIZATIONS_ON)
#		define HK_DISABLE_OPTIMIZATION_VS2008_X64 __pragma(optimize("g", off))
#		define HK_RESTORE_OPTIMIZATION_VS2008_X64 __pragma(optimize("g", on))
#	else
#		define HK_DISABLE_OPTIMIZATION_VS2008_X64
#		define HK_RESTORE_OPTIMIZATION_VS2008_X64
#	endif

	//
	// types
	//

	/// hkFloat is provided if floats are explicitly required.
	typedef float hkFloat32;
	/// hkDouble is provided if doubles are explicit required.
	typedef double hkDouble64;

	/// Signed 8 bit integer
	typedef signed char hkChar;
	/// Signed 8 bit integer
	typedef signed char hkInt8;
	/// Signed 16 bit integer
	typedef signed short hkInt16;
	/// Signed 32 bit integer
	typedef signed int hkInt32;

	/// Unsigned 8 bit integer
	typedef unsigned char hkUchar;
	/// Unsigned 8 bit integer
	typedef unsigned char hkUint8;
	/// Unsigned 16 bit integer
	typedef unsigned short hkUint16;
	/// Unsigned 32 bit integer
	typedef unsigned int hkUint32;

#	define HK_ALIGN_FLOAT HK_ALIGN16
#	define HK_ALIGN_DOUBLE HK_ALIGN32
#	define HK_FLOAT_ALIGNMENT 16
#	define HK_DOUBLE_ALIGNMENT 32
#	define HK_FLOAT_SIZE 4
#	define HK_DOUBLE_SIZE 8

#	if defined(HK_ARCH_X64)
#		if defined(HK_PLATFORM_X64)
	typedef unsigned __int64 hkUlong;  // MS- specific
	typedef signed __int64 hkLong;     // MS- specific
#		endif
#	elif defined(HK_COMPILER_MSVC) && (_MSC_VER >= 1300)
	typedef unsigned long __w64 hkUlong;  // VC7.0 or higher, 64bit warnings
	typedef signed long __w64 hkLong;
#	else
	typedef unsigned long hkUlong;
	typedef signed long hkLong;
#	endif

#	define HK_CPU_PTR(A) A

	typedef void* hk_va_list;

/// hkReal is the default floating point type.
#	if !defined(HK_REAL_IS_DOUBLE)
	typedef hkFloat32 hkReal;
#		define HK_ALIGN_REAL HK_ALIGN_FLOAT
#		define HK_REAL_ALIGNMENT HK_FLOAT_ALIGNMENT
#		define HK_REAL_SIZE HK_FLOAT_SIZE
#	endif
#endif  // HKBASE_HKBASEDEFS_H
}
