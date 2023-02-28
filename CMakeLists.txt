
cmake_minimum_required(VERSION 3.16)
project(sdl-ecs-example)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT> 
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
    )
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# on some windows machines i had the problem that libtifff was linked dynamically 
# so if this dll exists we'll put it into the binary directory here 
# i didn't have time yet to investigate but i think it depends on the settings in the used conan profile
if(EXISTS ${CONAN_BIN_DIRS_LIBTIFF}/tiffd.dll) 
    configure_file(${CONAN_BIN_DIRS_LIBTIFF}/tiffd.dll ${CMAKE_BINARY_DIR}/bin/tiffd.dll COPYONLY)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/src)