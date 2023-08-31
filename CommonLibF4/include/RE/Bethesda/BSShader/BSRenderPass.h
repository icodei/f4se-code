#pragma once

namespace RE
{
	class BSShader;
	class BSShaderProperty;
	class BSGeometry;
	class BSLight;
	class BSInstanceGroupPass;

	class BSRenderPass
	{
	public:
		BSRenderPass()
		{
			typedef BSRenderPass* func_t(BSRenderPass*);
			REL::Relocation<func_t> func{ REL::ID(1309529) };
			func(this);
		}
		BSRenderPass(BSShader* aShader, BSShaderProperty* aProperty, BSGeometry* aGeom, std::uint32_t passEnum, std::uint8_t numLights, BSLight** lights)
		{
			typedef BSRenderPass* func_t(BSRenderPass*, BSShader*, BSShaderProperty*, BSGeometry*, std::uint32_t, std::uint8_t, BSLight**);
			REL::Relocation<func_t> func{ REL::ID(1482704) };
			func(this, aShader, aProperty, aGeom, passEnum, numLights, lights);
		}

		~BSRenderPass()
		{
			typedef void* func_t(BSRenderPass*);
			REL::Relocation<func_t> func{ REL::ID(1514864) };
			func(this);
		}

		[[nodiscard]] void* operator new(std::size_t a_count)
		{
			typedef void* func_t(std::size_t);
			REL::Relocation<func_t> func{ REL::ID(657126) };

			const auto mem = func(a_count);
			if (mem) {
				return mem;
			} else {
				stl::report_and_fail("out of memory"sv);
			}
		}

		[[nodiscard]] void* operator new[](std::size_t a_count)
		{
			typedef void* func_t(std::size_t);
			REL::Relocation<func_t> func{ REL::ID(657126) };

			const auto mem = func(a_count);
			if (mem) {
				return mem;
			} else {
				stl::report_and_fail("out of memory"sv);
			}
		}

		void operator delete(void* a_ptr)
		{
			typedef void func_t(void*, std::uint64_t);
			REL::Relocation<func_t> func{ REL::ID(1268435) };
			func(a_ptr, 0x58);
		}
		void operator delete[](void* a_ptr)
		{
			typedef void func_t(void*, std::uint64_t);
			REL::Relocation<func_t> func{ REL::ID(1268435) };
			func(a_ptr, 0x58);
		}
		void operator delete(void* a_ptr, std::size_t)
		{
			typedef void func_t(void*, std::uint64_t);
			REL::Relocation<func_t> func{ REL::ID(1268435) };
			func(a_ptr, 0x58);
		}
		void operator delete[](void* a_ptr, std::size_t)
		{
			typedef void func_t(void*, std::uint64_t);
			REL::Relocation<func_t> func{ REL::ID(1268435) };
			func(a_ptr, 0x58);
		}

		[[nodiscard]] void* operator new(std::size_t a_count, std::align_val_t a_alignment)
		{
			const auto mem = RE::aligned_alloc(static_cast<std::size_t>(a_alignment), a_count);
			if (mem) {
				return mem;
			} else {
				stl::report_and_fail("out of memory"sv);
			}
		}

		[[nodiscard]] void* operator new[](std::size_t a_count, std::align_val_t a_alignment)
		{
			const auto mem = RE::aligned_alloc(static_cast<std::size_t>(a_alignment), a_count);
			if (mem) {
				return mem;
			} else {
				stl::report_and_fail("out of memory"sv);
			}
		}

		[[nodiscard]] void* operator new(std::size_t, void* a_ptr) noexcept { return a_ptr; }
		[[nodiscard]] void* operator new[](std::size_t, void* a_ptr) noexcept { return a_ptr; }
		[[nodiscard]] void* operator new(std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }
		[[nodiscard]] void* operator new[](std::size_t, std::align_val_t, void* a_ptr) noexcept { return a_ptr; }

		void operator delete(void*, void*) noexcept { return; }
		void operator delete[](void*, void*) noexcept { return; }

		void operator delete(void* a_ptr, std::align_val_t) { RE::aligned_free(a_ptr); }
		void operator delete[](void* a_ptr, std::align_val_t) { RE::aligned_free(a_ptr); }
		void operator delete(void* a_ptr, std::size_t, std::align_val_t) { RE::aligned_free(a_ptr); }
		void operator delete[](void* a_ptr, std::size_t, std::align_val_t) { RE::aligned_free(a_ptr); }

		//members
		BSShader* unk;
		BSShader* m_Shader;
		BSShaderProperty* m_ShaderProperty;
		BSGeometry* m_Geometry;
		BSInstanceGroupPass* m_InstanceGroupPass;
		BSRenderPass* m_Next;
		BSLight** m_SceneLights;
		BSRenderPass* m_next;
		BSRenderPass* m_PassGroupNext;
		std::uint32_t m_PassEnum;
		std::uint8_t field_4C;
		std::uint8_t field_4D;
		std::uint8_t field_4E;
		std::uint8_t field_4F;
		std::uint8_t m_NumLights;
	};
	static_assert(sizeof(BSRenderPass) == 0x58);
}
