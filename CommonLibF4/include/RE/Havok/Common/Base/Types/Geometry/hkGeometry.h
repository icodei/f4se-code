#pragma once
#include "RE/Havok/Common/Base/Container/Array/hkArray.h"

namespace RE
{
	///	Stores a triangle based mesh.
	/// Check out #include "RE/Havok/Common/GeometryUtilities/Misc/hkGeometryUtils.h"
	struct hkGeometry : public hkReferencedObject
	{
	public:
		static constexpr auto RTTI{ RTTI::hkGeometry };
		static constexpr auto VTABLE{ VTABLE::hkGeometry };

		enum GeometryType
		{
			GEOMETRY_STATIC,
			GEOMETRY_DYNAMIC_VERTICES,
		};

			/// A hkTriangle contains indices into an array of vertices and a material index.
		struct Triangle
		{
			//members
			int m_a;
			int m_b;
			int m_c;
			int m_material;
		};

		hkGeometry() {}
		hkGeometry(const hkGeometry& other);
		//hkGeometry(hkFinishLoadedObjectFlag f);

		//members
		hkArray<hkVector4f> m_vertices;
		hkArray<Triangle> m_triangles;
	};
}
