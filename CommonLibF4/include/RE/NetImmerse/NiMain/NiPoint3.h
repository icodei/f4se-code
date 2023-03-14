#pragma once

namespace RE
{
	class NiPoint3
	{
	public:
		using value_type = float;
		using size_type = std::size_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;

		static const NiPoint3 ZERO;
		static const NiPoint3 UNIT_X;
		static const NiPoint3 UNIT_Y;
		static const NiPoint3 UNIT_Z;
		static const NiPoint3 UNIT_ALL;

		NiPoint3() = default;
		NiPoint3(value_type aValue) :
			x(aValue), y(aValue), z(aValue) {}
		NiPoint3(value_type aX, value_type aY, value_type aZ) :
			x(aX), y(aY), z(aZ) {}

		[[nodiscard]] reference operator[](size_type a_pos) noexcept
		{
			assert(a_pos < 3);
			return reinterpret_cast<pointer>(std::addressof(x))[a_pos];
		}

		[[nodiscard]] const_reference operator[](size_type a_pos) const noexcept
		{
			assert(a_pos < 3);
			return reinterpret_cast<const_pointer>(std::addressof(x))[a_pos];
		}

		[[nodiscard]] bool operator==(const NiPoint3& a_rhs) const
		{
			return (x == a_rhs.x && y == a_rhs.y && z == a_rhs.z);
		}

		// members
		value_type x{ 0.0F };  // 0
		value_type y{ 0.0F };  // 4
		value_type z{ 0.0F };  // 8
	};
	static_assert(sizeof(NiPoint3) == 0xC);

	class alignas(0x10) NiPoint3A :
		public NiPoint3
	{
	public:
	};
	static_assert(sizeof(NiPoint3A) == 0x10);
}
