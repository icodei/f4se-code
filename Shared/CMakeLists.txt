# Detours

set(TARGET Detours)
set(DETOURS_SOURCE Detours/src)

set(SOURCES
    ${DETOURS_SOURCE}/creatwth.cpp
    ${DETOURS_SOURCE}/detours.cpp
    ${DETOURS_SOURCE}/detours.h
    ${DETOURS_SOURCE}/detver.h
    ${DETOURS_SOURCE}/disasm.cpp
    ${DETOURS_SOURCE}/disolarm.cpp
    ${DETOURS_SOURCE}/disolarm64.cpp
    ${DETOURS_SOURCE}/disolia64.cpp
    ${DETOURS_SOURCE}/disolx64.cpp
    ${DETOURS_SOURCE}/disolx86.cpp
    ${DETOURS_SOURCE}/image.cpp
    ${DETOURS_SOURCE}/modules.cpp
    ${DETOURS_SOURCE}/uimports.cpp
)

source_group(
	TREE "${CMAKE_CURRENT_SOURCE_DIR}"
	FILES ${SOURCES}
)

add_library(
    ${TARGET}
    STATIC
    ${SOURCES}
)

add_library("${TARGET}::${TARGET}" ALIAS "${TARGET}")

# This file is included and not compiled on its own
set_property (
    SOURCE ${DETOURS_SOURCE}/uimports.cpp
    APPEND PROPERTY HEADER_FILE_ONLY true)

target_compile_options(${TARGET} PRIVATE /W4 /WX /Zi /MT /Gy /Gm- /Zl /Od)
target_include_directories(${TARGET} PUBLIC ${DETOURS_SOURCE})

# Static library for the syelog components
add_library(syelog STATIC Detours/samples/syelog/syelog.cpp
                          Detours/samples/syelog/syelog.h)
target_include_directories(syelog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Detours/samples/syelog)
target_link_libraries(syelog PUBLIC lib_detours ws2_32 secur32)
