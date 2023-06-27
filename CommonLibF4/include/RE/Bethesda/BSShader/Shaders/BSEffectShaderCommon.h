#pragma once

namespace RE
{
	namespace BSEffectShaderCommonFeatures
	{
		enum
		{
			
		};
	}

	namespace BSEffectShaderUniqueFeatures
	{
		enum Technique
		{
			NONE,                           //Names
			VC = 1 << 0,                    //Vc
			SKINNED = 1 << 1,               //Sk
			TEXTURE = 1 << 2,               //
			INDEXED_TEXTURE = 1 << 3,       //
			FALLOFF = 1 << 4,               //
			ADDBLEND = 1 << 5,              //
			MULTBLEND = 1 << 6,             //
			PARTICLES = 1 << 7,             //
			STRIP_PARTICLES = 1 << 8,       //
			MEMBRANE = 1 << 9,              //
			LIGHTING = 1 << 10,             //
			PROJECTED_UV = 1 << 11,         //
			SOFT = 1 << 12,                 //
			GRAYSCALE_TO_COLOR = 1 << 13,   //
			GRAYSCALE_TO_ALPHA = 1 << 14,   //
			IGNORE_TEX_ALPHA = 1 << 15,     //
			MULTBLEND_DECAL = 1 << 16,      //
			ALPHA_TEST = 1 << 17,           //
			SKY_OBJECT = 1 << 18,           //
			ENVMAP = 1 << 19,               //
			PIPBOY_SCREEN = 1 << 20,        //
			RGB_FALLOFF = 1 << 21,          //
			PARTICLE_DISTORTION = 1 << 22,  //
			NORMALS = 1 << 23,              //
			ENVCUBE_RAIN = 1 << 24,         //
			ENVCUBE_SNOW = 1 << 25,         //
			EYE = 1 << 26,                  //
			UI_MASK_RECTS = 1 << 27,        //
			DECAL = 1 << 28,                //
			MERGE_INSTANCED = 1 << 29,      //
			PREMULTIPLY_ALPHA = 1 << 30,    //
		};

		enum Feature
		{
			None,
		};

		std::uint32_t GetUniqueFeature(std::uint32_t ID) { return (ID >> 8) & 0x3F; }
	}

	namespace BSEffectShaderVertexConstants
	{
		enum Constant
		{
			None = static_cast<std::underlying_type_t<Constant>>(-1),
			WorldViewProj = 0,
			World,
			Bones,
			PreviousBones,
			EyePosition,
			FalloffData,
			SoftMaterialVSParams,
			TexcoordOffset,
			TexcoordOffsetMembrane,
			SubTexOffset,
			PosAdjust,
			MatProj,
			ScaleAdjust,
			EnvcubeParticleOffset_RotationOffset,
			EnvcubeCameraOffset_Alpha,
			EnvcubeSize,
			EnvcubeVelocity,
			EyeCenterLeft,
			EyeCenterRight,
			VertexAttribOffsets1,
			VertexAttribOffsets2,
			OcclusionWorldViewProj
		};
		const char* GetString(std::uint32_t constant);
	}

	namespace BSEffectShaderPixelConstants
	{
		enum Constant : std::uint8_t
		{
			None = static_cast<std::underlying_type_t<Constant>>(-1),  //Size
			PropertyColor = 0,                                         //00
			AlphaTestRef,                                              //00
			MembraneRimColor,                                          //00
			MembraneVars,                                              //00
			PLightPositionX,                                           //00
			PLightPositionY,                                           //00
			PLightPositionZ,                                           //00
			PSpotDirX,                                                 //00
			PSpotDirY,                                                 //00
			PSpotDirZ,                                                 //00
			PSpotPower,                                                //00
			PSpotAngle,                                                //00
			PLightingRadiusInverseSquared,                             //00
			PLightColorR,                                              //00
			PLightColorG,                                              //00
			PLightColorB,                                              //00
			DLightColor,                                               //00
			CameraData,                                                //00
			BaseColor,                                                 //00
			BaseColorScale,                                            //00
			LightingInfluence,                                         //00
			EnvmapScale,                                               //00
			PipboyParams,                                              //00
			UIMaskRectParams,                                          //01
			UIMaskRects,                                               //00
			UIMaskRectColors,                                          //16
			OcclusionMapSize                                           //00
		};
		const char* GetString(std::uint32_t constant);
	}

	namespace BSEffectShaderSamplers
	{
		enum Constant
		{
			None = static_cast<std::underlying_type_t<Constant>>(-1),
			BaseSampler = 0,
			NormalSampler,
			NoiseSampler,
			DepthSampler,
			GrayscaleSampler,
			EnvmapSampler,
			PipboyScreenSampler,
			EnvmapMaskSampler,
			OcclusionSampler
		};
		const char* GetString(std::uint32_t constant);
	}

	namespace BSEffectShaderMacros
	{
	}
}
