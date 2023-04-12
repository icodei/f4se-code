#pragma once

namespace RE
{
	class hkVector4f;
	class hkVector4d;
	class hkVector4fComparison;
	class hkVector4dComparison;
	class hkSimdFloat32;
	class hkSimdDouble64;
	class hkQuaternionf;
	class hkQuaterniond;
	class hkMatrix3f;
	class hkMatrix3d;
	class hkMatrix4f;
	class hkMatrix4d;
	class hkRotationf;
	class hkRotationd;
	class hkTransformf;
	class hkTransformd;
	class hkQTransformf;
	class hkQTransformd;
	class hkQsTransformf;
	class hkQsTransformd;

	// Type discriminator for floating point resolution
	template <typename POD>
	struct hkRealTypes
	{};

	// Specialization for single precision
	template <>
	struct hkRealTypes<hkFloat32>
	{
		//typedef hkVector4f Vector;
		//typedef hkVector4fParameter VectorParameter;
		//typedef hkQuaternionf Quaternion;
		//typedef hkQuaternionfParameter QuaternionParameter;
		//typedef hkSimdFloat32 Scalar;
		//typedef hkSimdFloat32Parameter ScalarParameter;
		//typedef hkVector4fComparison Comparison;
		//typedef hkVector4fComparisonParameter ComparisonParameter;
		//typedef hkFloat32 Pod;
		//typedef hkMatrix3f Matrix3;
		//typedef hkSymmetricMatrix3f SymmetricMatrix3;
		//typedef hkMatrix4f Matrix4;
		//typedef hkRotationf Rotation;
		//typedef hkTransformf Transform;
		//typedef hkQTransformf QTransform;
		//typedef hkQsTransformf QsTransform;
	};
}
