cmake_minimum_required(VERSION 3.12)

# https://cmake.org/cmake/help/latest/prop_tgt/MSVC_RUNTIME_LIBRARY.html
cmake_policy(SET CMP0091 NEW)

project(masscalc)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

message(STATUS "CMAKE_VERSION = ${CMAKE_VERSION}")
message(STATUS "CMAKE_GENERATOR = ${CMAKE_GENERATOR}")
message(STATUS "C Compiler executable: ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler executable: ${CMAKE_CXX_COMPILER}")
message(STATUS "Linker executable: ${CMAKE_LINKER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Dependency setup with conan
include(conan_setup)

# Read GIT metadata
find_package(Git REQUIRED)

# Extract the current git sha
execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --always --abbrev=7
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE MASSCALC_GIT_SHA
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
# The marked constants in application.hpp will be replaced with the following values
set(MASSCALC_APP_NAME "Masscalc")

set(MASSCALC_ENGINE_VERSION_MAJOR 0)
set(MASSCALC_ENGINE_VERSION_MINOR 1)
set(MASSCALC_ENGINE_VERSION_PATCH 0)

set(MASSCALC_APP_VERSION_MAJOR 0)
set(MASSCALC_APP_VERSION_MINOR 1)
set(MASSCALC_APP_VERSION_PATCH 0)

set(MASSCALC_GITHUB_WEBSITE "https://github.com/IAmNotHanni/masscalc")

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmarks)
add_subdirectory(example)
