#pragma once

const std::string currentDateTime();
const std::string prefixLog();
void logIfNeeded(std::string text);
void log(std::string text);

void DumpClassX(void* theClassPtr, UInt64 nIntsToDump);