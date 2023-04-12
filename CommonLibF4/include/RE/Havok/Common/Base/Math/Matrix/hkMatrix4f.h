#pragma once

namespace RE
{
	class hkMatrix4f
	{
	public:

		HK_FORCE_INLINE hkMatrix4f() {} 

		/*HK_FORCE_INLINE void setIdentity()
		{
			const hkVector4f* HK_RESTRICT id = (const hkVector4f*)(g_vectorfConstants + HK_QUADREAL_1000);
			m_col0 = id[0];
			m_col1 = id[1];
			m_col2 = id[2];
			m_col3 = id[3];
		}*/

	protected:
		friend class hkQuaternionf;

		hkVector4f m_col0;
		hkVector4f m_col1;
		hkVector4f m_col2;
		hkVector4f m_col3;
	};
}
