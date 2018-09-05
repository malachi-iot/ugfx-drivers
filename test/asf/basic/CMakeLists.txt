cmake_minimum_required(VERSION 3.8)

# NOTE: lifted from pga-2 and not totally converted to proper 'basic' example yet

project(basic)

set(START_DIR ${CMAKE_CURRENT_LIST_DIR}/start)
set(EXT_DIR ../../ext)

include(tools/atmel/start/gcc-samd21g18a.cmake)

# this include is mainly so that we pick up 'include' pathing for .h
# we don't use any of the .c discovery
include(${START_CMAKE_DIR}/gather-headers.cmake)

# TODO: Migrate this into atmel makefiles themselves
# note that atmel stock makefiles don't have a flag like this
add_definitions(-DATMEL_ASF=0x040000)

#include(../../ext/estdlib/src/CMakeLists.txt)
include_directories(${EXT_DIR}/estdlib/src)
include_directories(${EXT_DIR}/framework.abstraction/src)
include_directories(${EXT_DIR}/framework.abstraction/src/frab/atmel/asf/fallback)

set(CMAKE_CXX_STANDARD 14)

# doesn't like CPU_OPTIONS in add_compile_options presumably due to -D flag
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CPU_OPTIONS} -DDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPU_OPTIONS}")

add_executable(${PROJECT_NAME}
    main.cpp
    main.h
    basic-demo.c
    mini-printf.c
    mini-printf.h
    spi.cpp
    )

# Note we can't easily do this ELF trick just yet because it goofs up our flash.cmake
#set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}.elf)
#set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .elf)

# explicitly state Reset_Handler since that more or less represents nanolib entry point
# and for some reason atmel-smart lib link-optimizes away the entry stuff
# NOTE: this should go into arch.cmake too but it has to come after add_executable
target_link_libraries(${PROJECT_NAME}
    atmel-start
    -T${LINKER_SCRIPT}
    --specs=nano.specs
    -Wl,--gc-sections
    -uReset_Handler
    m
    )
