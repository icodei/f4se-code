#pragma once

namespace RE
{
#define HK_TRANSPOSE3 HK_TRANSPOSE3f
#define HK_TRANSPOSE4 HK_TRANSPOSE4f

	//typedef hkVector8f hkVector8;
	//typedef hkMatrix6f hkMatrix6;
	//typedef hkVectorNf hkVectorN;
	//typedef hkMatrixfNm hkMatrixNm;
	//typedef hkVector2f hkVector2;

	//template <int SIZE>
	//class hkInplaceVectorN : public hkInplaceVectorNf<SIZE>
	//{};
	//typedef hkVectorNf hkVectorN;

#define HK_REAL_PI HK_FLOAT_PI
#define HK_REAL_DEG_TO_RAD HK_FLOAT_DEG_TO_RAD
#define HK_REAL_RAD_TO_DEG HK_FLOAT_RAD_TO_DEG
#define HK_REAL_EPSILON HK_FLOAT_EPSILON
#define HK_REAL_MIN HK_FLOAT_MIN
#define HK_REAL_MAX HK_FLOAT_MAX
#define HK_REAL_HIGH HK_FLOAT_HIGH

#ifndef HK_MASK_TO_VECTOR
#	define HK_MASK_TO_VECTOR(x) (hkQuadReal) x
#endif
}
