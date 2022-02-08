# CWT 2D Game Engine

Welcome to my 2D game engine. This is a blog series from [CodingWithThomas](https://www.codingwiththomas.com/). You can find all articles in the following links and they are tagged in this repository accordingly:

- ... 
- ...

## Project Setup: External Dependencies

The project has some external dependencies and optional tooling for development. All external libraries and tools are listed here.

## SDL
The game engine uses SDL as its media layer.  
downlaods:
https://www.libsdl.org/download-2.0.php
https://www.libsdl.org/projects/SDL_image/

sdl
https://github.com/tcbrindle/sdl2-cmake-scripts
set(SDL2_PATH "C:\Projects\extern\SDL2-2.0.20\x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "C:\Projects\extern\SDL2_image-2.0.5\x86_64-w64-mingw32")


## clang-tidy
warnings and clang-tidy cmake files, .clnang format, .clang-tidy:
{added -p on clang-tidy!}
https://github.com/cpp-best-practices/cpp_starter_project


## clang-format
clang-format


## lcov
lcov

## cmake, additional cmake files 



## coverage 
coverage (linux ubuntu only)
https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake
sudo apt install lcov


## spdlog
git clone https://github.com/gabime/spdlog.git
cd spdlog 
cmake -S . -B ./build -DCMAKE_INSTALL_PREFIX=<your install location>
cmake --build ./build
cmake --install ./build

-Dspdlog_DIR:FILEPATH="C:\Projects\extern\spdlog\build\out\lib\cmake\spdlog"


## Gtest
git clone https://github.com/google/googletest.git
cd googletest
cmake -S . -B ./build -DCMAKE_INSTALL_PREFIX=<your install location>
cmake --build ./build
cmake --install ./build


## Windwos Build

## Linux Build