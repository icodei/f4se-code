#pragma once

namespace RE
{
	namespace BSCoreUtils
	{
		struct BSCPUFeatures
		{
			bool x64;
			bool FPU;
			bool MMX;
			bool MMXEXT;
			bool SSE;
			bool SSE2;
			bool SSE3;
			bool SSSE3;
			bool SSE41;
			bool SSE42;
			bool SSE4a;
			bool AVX;
			bool AVX2;
			bool AVX512;
			bool AVX512DQ;
			bool AVX512PF;
			bool AVX512ER;
			bool AVX512CD;
			bool AVX512BW;
			bool AVX512VL;
			bool AES;
			bool ADX;
			bool SHA;
			bool XOP;
			bool FMA3;
			bool FMA4;
		};

		struct StackTrace
		{
			std::uint32_t uiNumFrames;
			std::uint64_t FramesA[64];
		};
	}
}

