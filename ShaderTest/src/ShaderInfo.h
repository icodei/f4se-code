#pragma once
#include "Global.h"

struct ShaderInfo {
private:
	ShaderInfo() {}
	~ShaderInfo() {}

public:
	ShaderInfo(ShaderInfo const&) = delete;
	void operator=(ShaderInfo const&) = delete;

	//static functions
	static ShaderInfo& getInstance();

	//static fill functions
	static void EraseAllShaderInfo();
	static void FillAllShaderInfo();
	static void PrintAllShaderInfo(unordered_map<const char*, uintptr_t> const& map);
	static void EraseShaderInfo(const char* a_name);
	static void FillShaderInfo(const char* a_name, BSReloadShaderI* a_shader, bool a_print);
	static void PrintShaderInfo(const char* a_name, BSReloadShaderI* a_shader);
	static void PrintShaderName(const char* a_name, BSReloadShaderI* a_shader);

	//static util functions
	static bool IsCompute(const char* a_name);
	static bool IsImagespace(const char* a_name);

	static const char* PrepareFilePath(const char* a_name, uint32_t a_techniqueID, const char* a_techniqueName, const char* a_extension, const std::filesystem::path a_basepath = "Data/ShaderDump/");

	//members
	std::unordered_map<const char*, uintptr_t> shaderList;
};
