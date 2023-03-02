#pragma once

namespace RE
{

	enum class COL_LAYER : std::uint32_t
	{
		L_UNIDENTIFIED = 0x0,
		L_STATIC = 0x1,
		L_ANIMSTATIC = 0x2,
		L_TRANSPARENT = 0x3,
		L_CLUTTER = 0x4,
		L_WEAPON = 0x5,
		L_PROJECTILE = 0x6,
		L_SPELL = 0x7,
		L_BIPED = 0x8,
		L_TREES = 0x9,
		L_PROPS = 0xA,
		L_WATER = 0xB,
		L_TRIGGER = 0xC,
		L_TERRAIN = 0xD,
		L_TRAP = 0xE,
		L_NONCOLLIDABLE = 0xF,
		L_CLOUDTRAP = 0x10,
		L_GROUND = 0x11,
		L_PORTAL = 0x12,
		L_DEBRIS_SMALL = 0x13,
		L_DEBRIS_LARGE = 0x14,
		L_ACOUSTIC_SPACE = 0x15,
		L_ACTORZONE = 0x16,
		L_PROJECTILEZONE = 0x17,
		L_GASTRAP = 0x18,
		L_SHELLCASING = 0x19,
		L_TRANSPARENT_SMALL = 0x1A,
		L_INVISIBLE_WALL = 0x1B,
		L_TRANSPARENT_SMALL_ANIM = 0x1C,
		L_CLUTTER_LARGE = 0x1D,
		L_CHARCONTROLLER = 0x1E,
		L_STAIRHELPER = 0x1F,
		L_DEADBIP = 0x20,
		L_BIPED_NO_CC = 0x21,
		L_AVOIDBOX = 0x22,
		L_COLLISIONBOX = 0x23,
		L_CAMERASPHERE = 0x24,
		L_DOORDETECTION = 0x25,
		L_CONEPROJECTILE = 0x26,
		L_CAMERA = 0x27,
		L_ITEMPICKER = 0x28,
		L_LOS = 0x29,
		L_PATHINGPICK = 0x2A,
		L_UNUSED_0 = 0x2B,
		L_UNUSED_1 = 0x2C,
		L_SPELLEXPLOSION = 0x2D,
		L_DROPPINGPICK = 0x2E,
		NUMFILTERLAYERS = 0x2F,
		DATADEFINEDLAYERSBEGIN = 0x2F,
		L_DATADEFINED_1 = 0x30,
		L_DATADEFINED_2 = 0x31,
		L_DATADEFINED_3 = 0x32,
		L_DATADEFINED_4 = 0x33,
		L_DATADEFINED_5 = 0x34,
		L_DATADEFINED_6 = 0x35,
		L_DATADEFINED_7 = 0x36,
		L_DATADEFINED_8 = 0x37,
		L_DATADEFINED_9 = 0x38,
		L_DATADEFINED_10 = 0x39,
		L_DATADEFINED_11 = 0x3A,
		L_DATADEFINED_12 = 0x3B,
		L_DATADEFINED_13 = 0x3C,
		L_DATADEFINED_14 = 0x3D,
		L_DATADEFINED_15 = 0x3E,
		L_DATADEFINED_16 = 0x3F,
		MAXLAYERSIZE = 0x40,
	};

	class CFilter
	{
	public:
		~CFilter() noexcept {}  // intentional

		// members
		std::uint32_t filter;  // 0
	};
	static_assert(sizeof(CFilter) == 0x4);
}