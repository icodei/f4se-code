#pragma once

namespace RE
{
	namespace BSLightingShaderVertexDecl  //Line 36
	{
		enum Flag
		{
			NONE = static_cast<std::underlying_type_t<Flag>>(-1),
			VERTEX_COLORS = 1 << 0,
			SKINNED = 1 << 1,
			MODELSPACENORMALS = 1 << 2,

			NEXT_BIT = 1 << 3,
			MASK = 7,

			COUNT = 3
		};
		const char* GetString(std::uint32_t constant);
	}

	namespace BSLightingShaderCommonFeatures  //Line 51
	{
		enum
		{
			PROJECTED_UV = 1 << 3,
			ANISO_LIGHTING = 1 << 4,
			PIPBOY_SCREEN = 1 << 5,
			GRADIENT_REMAP = 1 << 6,
			MENU_SCREEN = 1 << 7,
			NEXT_BIT = 1 << 8,

			COUNT = 5
		};
	}

	namespace BSLightingShaderUniqueFeatures  //Line 67
	{
		enum Technique
		{
			NONE = 0,                           //Names
			ENVMAP,                             //Envmap
			GLOWMAP,                            //Glowmap
			PARALLAX,                           //Parallax
			FACE,                               //Face
			SKIN_TINT,                          //SkinTint
			HAIR_TINT,                          //HairTint
			PARALLAX_OCC,                       //ParallaxOcc
			MULTI_TEXTURE_LANDSCAPE,            //Landscape
			LOD_LANDSCAPE,                      //LODLand
			SNOW,                               //Snow
			MULTI_LAYER_PARALLAX,               //MultiLayerParallax
			TREE_ANIM,                          //TreeAnim
			LOD_OBJECTS,                        //LODObjects
			MULTI_INDEX_TRISHAPE_SNOW,          //MultiIndexTriShapeSnow
			LOD_OBJECTS_HD,                     //LODObjectsHD
			EYE,                                //Eye
			CLOUD,                              //Cloud
			LOD_LANDSCAPE_NOISE,                //LODLandNoise
			MULTI_TEXTURE_LANDSCAPE_LOD_BLEND,  //LODLandBlend
			DISMEMBERMENT,                      //Dismember

			COUNT,

			NUM_BITS = 6,
			MASK = 63,
		};

		enum Feature
		{
			//							 //Names
			VC = 1 << 0,                 //Vc
			SKINNED = 1 << 1,            //Sk
			MODELSPACENORMALS = 1 << 2,  //Msn
			PROJECTED_UV = 1 << 3,       //Projuv
			ANISO_LIGHTING = 1 << 4,     //Aniso
			PIPBOY_SCREEN = 1 << 5,      //Pipboy
			GRADIENT_REMAP = 1 << 6,     //GradientRemap
			MENU_SCREEN = 1 << 7,        //Menu
		};

		std::uint32_t GetUniqueFeature(std::uint32_t ID) { return (ID >> 8) & MASK; }
	}

	namespace BSLightingShaderVertexConstants  //Line 113
	{
		enum Constant
		{
			None = static_cast<std::underlying_type_t<Constant>>(-1),
			WorldViewProj = 0,
			World,
			Bones,
			EyePosition,
			LandBlendParams,
			TexcoordOffset,
			TreeParams,
			IndexScale,
			HighDetailRange,
			TextureProj,
			LeftEyeCenter,
			RightEyeCenter,
			WorldMapOverlayParameters,

			COUNT
		};
		const char* GetString(std::uint32_t constant);
	}

	namespace BSLightingShaderPixelConstants
	{
		enum Constant
		{
			None = static_cast<std::underlying_type_t<Constant>>(-1),
			PointLightPosition = 0,
			PointLightColor,
			DirLightDirection,
			DirLightColor,
			DirectionalAmbient,
			AmbientSpecularTintAndFresnelPower,
			MaterialData,
			EmitColor,
			AlphaTestRef,
			VPOSOffset,
			ProjectedUVParams,
			ProjectedUVParams2,
			SplitDistance,
			ShadowLightCounts,
			SpecularParam,
			ShadowSampleParam,
			DirShadowMapProj,
			SplitDistances,
			AmbientColor,
			EnvmapData,
			ParallaxOccData,
			TintColor,
			WorldWetnessLevel,
			WorldRainLevel,
			LODTexParams,
			SpecularColor,
			MultiLayerParallaxData,
			LightingEffectParams,
			MenuScreenParams,

			COUNT
		};
		const char* GetString(std::uint32_t constant);
	}

	namespace BSLightingShaderTextures  //Line 192
	{
		enum Texture
		{
			None = static_cast<std::underlying_type_t<Texture>>(-1),
			DiffuseSampler = 0,
			NormalSampler,
			SmoothnessSpecMaskSampler,
			HeightSampler,
			EnvSampler,
			EnvMaskSampler,
			GlowSampler,
			VolumetricNoiseSampler,
			ShadowMapCompSampler,
			BackLightMaskSampler,
			SparkleSampler,
			ProjectedNoiseSampler,
			SubSurfaceSampler,
			WorldMapOverlayNormalSampler,
			MenuScreenSampler,
			WorldMapOverlayNormalSnowSampler,
			MultiTextureDiffuseLODSampler,
			PipboyFXSampler,
			ShadowMapSampler,
			LODNoiseSampler,
			ColorLookupSampler,

			COUNT
		};
		const char* GetString(std::uint32_t constant);
	}

	namespace BSLightingShaderMacros
	{
	}
}
