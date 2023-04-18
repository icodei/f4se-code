#pragma once

namespace RE
{
	template <class Integral, class>
	class NiTFlags
	{
	public:
		using integral_type = Integral;

		static_assert(std::is_integral_v<integral_type>);

		constexpr NiTFlags() noexcept {}  // NOLINT(moderinize-use-equals-default)

		void SetField(integral_type uVal, integral_type uMask, integral_type uPos)
		{
			flags = (flags & ~uMask) | (uVal << uPos);
		}

		integral_type GetField(integral_type uMask, integral_type uPos) const
		{
			return (flags & uMask) >> uPos;
		}

		void SetBit(bool bVal, integral_type uMask)
		{
			if (bVal) {
				flags |= uMask;
			} else {
				flags &= ~uMask;
			}
		}

		bool GetBit(integral_type uMask) const
		{
			return (flags & uMask) != 0;
		}

		NiTFlags& operator=(integral_type& uVal)
		{
			flags = uVal;
			return this;
		}

		NiTFlags& operator=(const integral_type& uVal)
		{
			flags = uVal;
			return this;
		}

		// members
		integral_type flags{ 0 };  // 00
	};
}
