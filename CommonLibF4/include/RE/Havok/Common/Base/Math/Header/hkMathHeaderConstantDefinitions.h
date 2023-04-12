#pragma once

namespace RE
{
	/// A list of constants.
	/// \warning Do not change the order of the following constants and keep synchronized with value array: g_vectorConstants[] because algorithms rely on this order.
	enum hkVectorConstant
	{
		HK_QUADREAL_BEGIN,  ///< Start marker, do not use

		HK_QUADREAL_MINUS1,
		HK_QUADREAL_0,
		HK_QUADREAL_1,
		HK_QUADREAL_2,
		HK_QUADREAL_3,
		HK_QUADREAL_4,
		HK_QUADREAL_5,
		HK_QUADREAL_6,
		HK_QUADREAL_7,
		HK_QUADREAL_8,
		HK_QUADREAL_15,
		HK_QUADREAL_16,
		HK_QUADREAL_255,
		HK_QUADREAL_256,
		HK_QUADREAL_2_POW_23,

		HK_QUADREAL_INV_0,  ///< 0.0f, 0.0f, 0.0f
		HK_QUADREAL_INV_1,  ///< 1 1 1 1
		HK_QUADREAL_INV_2,  ///< .5 .5 .5 .5
		HK_QUADREAL_INV_3,  ///< 1/3 1/3 1/3 1/3
		HK_QUADREAL_INV_4,
		HK_QUADREAL_INV_5,
		HK_QUADREAL_INV_6,
		HK_QUADREAL_INV_7,
		HK_QUADREAL_INV_8,
		HK_QUADREAL_INV_15,   ///< 1/15 x 4
		HK_QUADREAL_INV_127,  ///< 1/127 x 4
		HK_QUADREAL_INV_226,  ///< 1/226 x 4, Used to unpack AABB.
		HK_QUADREAL_INV_255,  ///< 1/255 x 4
		HK_QUADREAL_1000,     ///< The next 4 are also the matrix identity, don't change the order.
		HK_QUADREAL_0100,
		HK_QUADREAL_0010,
		HK_QUADREAL_0001,
		HK_QUADREAL_MAX,
		HK_QUADREAL_HIGH,  ///< A high number (~ sqrd(HK_QUADREAL_MAX) )
		HK_QUADREAL_EPS,
		HK_QUADREAL_EPS_SQRD,  ///< Eps squared, really really tiny number
		HK_QUADREAL_MIN,       ///< The smallest positive number, which is not a denormal
		HK_QUADREAL_MINUS_MAX,
		HK_QUADREAL_MINUS_MIN,
		HK_QUADREAL_m11m11,             ///< -1,1,-1,1
		HK_QUADREAL_1m11m1,             ///< 1,-1,1,-1
		HK_QUADREAL_1010,               ///< 1,0,1,0
		HK_QUADREAL_1100,               ///< 1,1,0,0
		HK_QUADREAL_0011,               ///< 0,0,1,1
		HK_QUADREAL_1248,               ///< 1,2,4,8
		HK_QUADREAL_8421,               ///< 8,4,2,1
		HK_QUADREAL_PACK_HALF,          ///< Used to pack hkHalfs
		HK_QUADREAL_PACK16_UNIT_VEC,    ///< Used to compress unit vectors
		HK_QUADREAL_UNPACK16_UNIT_VEC,  ///< Used to uncompress unit vectors
		HK_QUADREAL_PI,
		HK_QUADREAL_PI_HALF,
		HK_QUADREAL_PI_QUARTER,
		HK_QUADREAL_FOUR_PI_THIRD,
		HK_QUADREAL_TWO_PI,
		HK_QUADREAL_FOUR_PI,
		HK_QUADREAL_DEG2RAD,
		HK_QUADREAL_RAD2DEG,

		HK_QUADREAL_END  ///< End marker, do not use
	};

	/// A list of constants.
	/// \warning Do not change the order of the following constants and keep synchronized with value array: g_intVectorConstants[] because algorithms rely on this order.
	enum hkIntVectorConstant
	{
		HK_QUADINT_BEGIN,  ///< Start marker, do not use

		HK_QUADINT_0,
		HK_QUADINT_1,
		HK_QUADINT_2,
		HK_QUADINT_4,
		HK_QUADINT_0123,
		HK_QUADINT_0123_INT24W,  ///< lower bits hold 0123, upper bits are set, so that reinterpreting this value as float will give a valid floating point number
		HK_QUADINT_3,
		HK_QUADINT_FFFF,  ///< mask used for selecting the lower 16 bit

		// Permutation constants, for Xbox broadcast(i), do not change order!
		HK_QUADINT_PERM_XXXX,
		HK_QUADINT_PERM_YYYY,
		HK_QUADINT_PERM_ZZZZ,
		HK_QUADINT_PERM_WWWW,

		HK_QUADINT_END  ///< End marker, do not use
	};
}
