
cmake_minimum_required(VERSION 3.16)
project(cwt-game-engine)

set(CMAKE_BUILD_TYPE Debug)


set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")
option(ENABLE_COVERAGE "Create Coverage Report ON/OFF" OFF) 
include(cmake/StaticAnalyzers.cmake)
include(cmake/CodeCoverage.cmake)
include(cmake/FindSDL2.cmake)
include(cmake/FindSDL2_image.cmake)

add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)


option(ENABLE_PRECOMPILED_HEADERS "pre compile system headers ON/OFF" OFF)
add_library(precompiled_headers INTERFACE)
add_library(precompiled_headers_gtest INTERFACE)
if(ENABLE_PRECOMPILED_HEADERS)
  target_precompile_headers(precompiled_headers INTERFACE ${PROJECT_SOURCE_DIR}/src/cwt_pch/cwt_pch.hpp)
  target_precompile_headers(precompiled_headers_gtest INTERFACE ${PROJECT_SOURCE_DIR}/gtest/cwt_gtest.hpp)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)


add_subdirectory(${PROJECT_SOURCE_DIR}/src/cwt_game_engine)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/playground)

enable_testing()
add_subdirectory(${PROJECT_SOURCE_DIR}/gtest)
