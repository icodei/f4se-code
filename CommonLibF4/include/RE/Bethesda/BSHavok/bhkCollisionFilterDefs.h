#pragma once

namespace RE
{
	enum BIPED_PART : std::int32_t
	{
		P_OTHER = 0x0,
		P_HEAD = 0x1,
		P_BODY = 0x2,
		P_SPINE1 = 0x3,
		P_SPINE2 = 0x4,
		P_LUPPERARM = 0x5,
		P_LFOREARM = 0x6,
		P_LHAND = 0x7,
		P_LTHIGH = 0x8,
		P_LCALF = 0x9,
		P_LFOOT = 0xA,
		P_RUPPERARM = 0xB,
		P_RFOREARM = 0xC,
		P_RHAND = 0xD,
		P_RTHIGH = 0xE,
		P_RCALF = 0xF,
		P_RFOOT = 0x10,
		P_TAIL = 0x11,
		P_SHIELD = 0x12,
		P_QUIVER = 0x13,
		P_WEAPON = 0x14,
		P_PONYTAIL = 0x15,
		P_WING = 0x16,
		P_PACK = 0x17,
		P_CHAIN = 0x18,
		P_ADDONHEAD = 0x19,
		P_ADDONCHEST = 0x1A,
		P_ADDONLEG = 0x1B,
		P_ADDONARM = 0x1C,
		NUMFILTERPARTS = 0x20,
	};

}
