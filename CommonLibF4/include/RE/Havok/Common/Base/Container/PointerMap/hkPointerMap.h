#pragma once
#include "RE/Havok/Common/Base/Container/PointerMap/hkMap.h"

namespace RE
{
	// Helpers to get the hkMap implementation for a given key size.
	template <int N>
	struct hkPointerMapStorage
	{
		typedef hkUlong Type;
	};

	template <>
	struct hkPointerMapStorage<8>
	{
		typedef hkUint64 Type;
	};

	// Helpers to convert between keys/values and storage.
	// Normally we can do a simple cast, but for floats/doubles, we have to do a copy.
	template <typename T, typename Storage>
	struct hkPointerMapCast
	{
		static HK_FORCE_INLINE Storage StoreCast(T t)
		{
			return Storage(t);
		}

		static HK_FORCE_INLINE T LoadCast(Storage s)
		{
			typedef typename hkPointerMapStorage<sizeof(T)>::Type ValueType;
			return (T)(ValueType)s;
		}
	};

	template <typename Storage>
	struct hkPointerMapCast<hkFloat32, Storage>
	{
		static HK_FORCE_INLINE Storage StoreCast(hkFloat32 r)
		{
			Storage s = 0;
			std::memcpy(&s, &r, sizeof(hkFloat32));
			return s;
		}

		static HK_FORCE_INLINE hkFloat32 LoadCast(Storage s)
		{
			hkFloat32 r;
			std::memcpy(&r, &s, sizeof(hkFloat32));
			return r;
		}
	};

	template <typename Storage>
	struct hkPointerMapCast<hkDouble64, Storage>
	{
		static HK_FORCE_INLINE Storage StoreCast(hkDouble64 r)
		{
			Storage s = 0;
			std::memcpy(&s, &r, sizeof(hkDouble64));
			return s;
		}

		static HK_FORCE_INLINE hkDouble64 LoadCast(Storage s)
		{
			hkDouble64 r;
			std::memcpy(&r, &s, sizeof(hkDouble64));
			return r;
		}
	};

	/// A class to map between pointer or integer keys and arbitrary pointer/integer values.
	/// The key is not allowed to be -1.
	template <typename K, typename V, typename Allocator = hkContainerHeapAllocator>
	class hkPointerMap
	{
	public:

		// Note: pick the larger type for storage, so we don't truncate one
		typedef typename hkPointerMapStorage<sizeof(K) >= sizeof(V) ? sizeof(K) : sizeof(V)>::Type Storage;

		template <typename T>
		static Storage StoreCast(T t)
		{
			return hkPointerMapCast<T, Storage>::StoreCast(t);
		};

		template <typename T>
		static T LoadCast(Storage s)
		{
			return hkPointerMapCast<T, Storage>::LoadCast(s);
		};

		/// Iterator class.
		/// All iterators are invalidated after a mutating operation, i.e., insertion, removal.
		typedef typename hkMap<Storage, Storage>::Iterator Iterator;

		//typedef hkPointerMap<K, V, hkContainerTempAllocator> Temp;
		//typedef hkPointerMap<K, V, hkContainerDebugAllocator> Debug;
		typedef hkPointerMap<K, V, hkContainerHeapAllocator> Heap;

		/// Create an empty pointermap.
		hkPointerMap()
		{
		}

		/// Create pointer map initially using preallocated memory block.
		/// Use the getSizeInBytesFor(int numKeys) method to find the buffer size
		/// required for a given number of keys.
		hkPointerMap(void* ptr, int sizeInBytes) :
			m_map(ptr, sizeInBytes)
		{
		}

		~hkPointerMap() {}

	protected:
		/// For creating an uninitialized map.
		enum InternalInitializer
		{
			UNINITIALIZED,
		};

		/// Creates an uninitialized hkPointerMap. For internal use.
		hkPointerMap(InternalInitializer ii) :
			m_map(hkMap<Storage, Storage, hkMapOperations<Storage>, Allocator>::UNINITIALIZED) {}

	public:
		/// Create pointer map initially using preallocated memory block.
		/// Use the getSizeInBytesFor(int numKeys) method to find the buffer size
		/// required for a given number of keys.
		HK_FORCE_INLINE void init(void* ptr, int sizeInBytes)
		{
			return m_map.init(ptr, sizeInBytes);
		}

		///	Insert key with associated value val. Keys are unique and cannot be -1.
		/// If key already exists it is overwritten. Returns true if the key is new
		/// and false if an existing key was overwritten.
		HK_FORCE_INLINE hkBool32 insert(K key, V val)
		{
			return m_map.insert(StoreCast(key), StoreCast(val));
		}

		///	Try to insert key with associated value val. Keys are unique and cannot be -1.
		/// If key already exists it is overwritten. Returns true if the key is new
		/// and false if an existing key was overwritten.
		/// If insertion fails (due to being unable to expand the table), res is set to HK_FAILURE,
		/// otherwise it is set to HK_SUCCESS.
		HK_FORCE_INLINE hkBool32 tryInsert(K key, V val, hkResult& res)
		{
			return m_map.tryInsert(StoreCast(key), StoreCast(val), res);
		}

		/// Return the iterator associated with key or the end iterator if not present.
		HK_FORCE_INLINE Iterator findKey(K key) const
		{
			return m_map.findKey(StoreCast(key));
		}

		/// If key is present return its iterator, else insert (key,val) and return the new iterator.
		/// Thus the returned iterator is always valid.
		HK_FORCE_INLINE Iterator findOrInsertKey(K key, V val)
		{
			return m_map.findOrInsertKey(StoreCast(key), StoreCast(val));
		}

		/// Return if this map contains the given key.
		HK_FORCE_INLINE hkBool hasKey(K key) const
		{
			return m_map.hasKey(StoreCast(key));
		}

		/// Return the value associated with key or def if not present.
		HK_FORCE_INLINE V getWithDefault(K key, V def) const
		{
			return LoadCast<V>(m_map.getWithDefault(StoreCast(key), StoreCast(def)));
		}

		/// If key present, write value into out and return HK_SUCCESS. Else return HK_FAILURE.
		hkResult get(K key, V* out) const
		{
			Storage tmp;
			if (m_map.get(StoreCast(key), &tmp) == hkResultEnum::HK_SUCCESS) {
				*out = LoadCast<V>(tmp);
				return hkResultEnum::HK_SUCCESS;
			}
			return hkResultEnum::HK_FAILURE;
		}

		/// Remove pair at it. The iterator is no longer valid after this call.
		void remove(Iterator it)
		{
			m_map.remove(it);
		}

		/// If key present, remove it and return HK_SUCCESS. Otherwise return HK_FAILURE.
		hkResult remove(K key)
		{
			return m_map.remove(StoreCast(key));
		}

		/// Return the number of elements in this map.
		int getSize() const
		{
			return m_map.getSize();
		}

		/// Return the number of elements that can be stored in this map without reallocation.
		int getCapacity() const
		{
			return m_map.getCapacity();
		}

		/// Return the amount of allocated memory in bytes. Use for statistics.
		int getMemSize() const
		{
			return m_map.getMemSize();
		}

		/// Return the start address in memory of the hashmap. Use for statistics.
		void* getMemStart() const
		{
			return m_map.getMemStart();
		}

		/// Perform internal consistency check.
		hkBool isOk() const
		{
			return m_map.isOk();
		}

		/// Get an iterator over the keys of this map.
		Iterator getIterator() const
		{
			return m_map.getIterator();
		}

		/// Get the key at iterator i.
		K getKey(Iterator i) const
		{
			return LoadCast<K>(m_map.getKey(i));
		}

		/// Get the value at iterator i.
		V getValue(Iterator i) const
		{
			return LoadCast<V>(m_map.getValue(i));
		}

		/// Overwrite the value at iterator i.
		void setValue(Iterator i, V val)
		{
			m_map.setValue(i, StoreCast(val));
		}

		/// Get the next iterator after i.
		Iterator getNext(Iterator i) const
		{
			return m_map.getNext(i);
		}

		/// Return if the iterator has reached the end.
		hkBool isValid(Iterator i) const
		{
			return m_map.isValid(i);
		}

		/// clear the table
		void clear()
		{
			m_map.clear();
		}

		/// Reserve space for at least numElements;
		void reserve(int numElements)
		{
			m_map.reserve(numElements);
		}

		/// Swap the internal representation with another map.
		void swap(hkPointerMap& other)
		{
			m_map.swap(other.m_map);
		}

		/// Return true if the map was constructed with a buffer which was too small.
		inline hkBool wasReallocated() const { return m_map.wasReallocated(); }

		/// Advanced use only.
		void setOwnedData(void* ptr, int size, int capacity)
		{
			m_map.setOwnedData(ptr, size, capacity);
		}

		/// Calculates buffer size required to store the specified number of keys.
		static int HK_CALL getSizeInBytesFor(int numOfKeys) { return hkMap<Storage, Storage>::getSizeInBytesFor(numOfKeys); }

	private:
		void operator=(const hkPointerMap<K, V>& map) {}
		hkPointerMap(const hkPointerMap<K, V>& map) {}

	public:

		hkMap<Storage, Storage, hkMapOperations<Storage>, Allocator> m_map;
	};
}
