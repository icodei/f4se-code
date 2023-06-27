#pragma once
#define _AMD64_

#pragma warning(push)
#include "F4SE/F4SE.h"
#include "RE/Fallout.h"

#include <Windows.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <thread>
#include <time.h>
#include <unordered_map>
#include <xbyak/xbyak.h>

#ifdef NDEBUG
#	include <spdlog/sinks/basic_file_sink.h>
#else
#	include <spdlog/sinks/msvc_sink.h>
#endif
#pragma warning(pop)
#pragma warning(disable: 4100);
#pragma warning(disable: 4189);
#pragma warning(disable: 4244);
#pragma warning(disable: 4302);
#pragma warning(disable: 4311);
#pragma warning(disable: 4172);

#define DLLEXPORT __declspec(dllexport)

using namespace std::literals;
using namespace RE;
using std::unordered_map;
using std::is_empty_v;
using std::string;

namespace logger = F4SE::log;

#include "Version.h"
