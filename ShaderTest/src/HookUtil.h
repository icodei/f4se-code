#pragma once
#include "Global.h"

namespace HookUtil {
	template <typename T>
	T GetVirtualFunction(void* baseObject, int vtblIndex) {
		uintptr_t* vtbl = reinterpret_cast<uintptr_t**>(baseObject)[0];
		return reinterpret_cast<T>(vtbl[vtblIndex]);
	}

	template <typename T>
	T GetOffset(const void* baseObject, int offset) {
		return *reinterpret_cast<T*>((uintptr_t)baseObject + offset);
	}

	template <class T>
	T SafeWrite64Function(uintptr_t addr, T data) {
		DWORD oldProtect;
		void* _d[2];
		memcpy(_d, &data, sizeof(data));
		size_t len = sizeof(_d[0]);

		VirtualProtect((void*)addr, len, PAGE_EXECUTE_READWRITE, &oldProtect);
		T olddata;
		memset(&olddata, 0, sizeof(T));
		memcpy(&olddata, (void*)addr, len);
		memcpy((void*)addr, &_d[0], len);
		VirtualProtect((void*)addr, len, oldProtect, &oldProtect);
		return olddata;
	}

	template <class Ty>
	static inline Ty SafeWrite_Impl(uintptr_t addr, Ty data) {
		DWORD oldProtect = 0;
		Ty oldVal = 0;

		if (VirtualProtect((void*)addr, sizeof(Ty), PAGE_EXECUTE_READWRITE, &oldProtect)) {
			Ty* p = (Ty*)addr;
			oldVal = *p;
			*p = data;
			VirtualProtect((void*)addr, sizeof(Ty), oldProtect, &oldProtect);
		}

		return oldVal;
	}

	uintptr_t SafeWrite64(uintptr_t addr, uintptr_t data);

	template <class Ty, class TRet, class... TArg>
	inline auto SafeWrite64(uintptr_t jumpSrc, TRet (Ty::*fn)(TArg...)) -> decltype(fn) {
		typedef decltype(fn) Fn;
		union {
			uintptr_t u64;
			Fn fn;
		} data;

		data.fn = fn;

		data.u64 = SafeWrite64(jumpSrc, data.u64);
		return data.fn;
	}

	template <class TRet, class... TArg>
	inline auto SafeWrite64(uintptr_t jumpSrc, TRet (*fn)(TArg...)) -> decltype(fn) {
		typedef decltype(fn) Fn;
		return (Fn)SafeWrite64(jumpSrc, (uintptr_t)fn);
	}
}

BSTEventSource<void*>* GetGlobalEventSource(BSTGlobalEvent_OLD* globalEvents, const char* globalName);
const char* GetObjectClassNameImpl(const char* result, void* objBase);
const char* GetObjectClassName(void* objBase);
