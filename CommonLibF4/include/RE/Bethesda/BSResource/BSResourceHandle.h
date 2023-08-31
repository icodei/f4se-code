#pragma once

namespace RE
{
	namespace BSResource
	{
		template <class T_Entry, class T_EntryDB>
		class RHandleType
		{
		public:
			using U_Entry = T_Entry;
			using U_EntryDB = T_EntryDB;

			// members
			T_Entry* entry;  // 00
		};
	}
}
