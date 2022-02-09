# CWT 2D Game Engine

Welcome to my 2D game engine. This is a blog series from [CodingWithThomas](https://www.codingwiththomas.com/). You can find all articles in the following links and they are tagged in this repository accordingly:

- ... 
- ...

## Linux Build

Run following commands to install following libraries to run Linux (Ubuntu) builds
````bash
sudo apt install libsdl2-dev
sudo apt install libsdl2-image-dev
sudo apt install libsdl2-ttf-dev
sudo apt install libspdlog-dev
sudo apt-get install libgtest-dev
````
Then navigate in the project directory and run cmake:
````bash
cmake -S . -B ./build
cmake --build ./build
````


## Windows Build
For Windows builds install the following external libraries manually, as described in the subsections.  

### SDL 
Download prebuild SDL.

https://www.libsdl.org/download-2.0.php  
https://www.libsdl.org/projects/SDL_image/

### spdlog 

Clone the spdlog git repository and build it. Set `CMAKE_INSTALL_DIRECTORY` to the desired install location.
````
git clone https://github.com/gabime/spdlog.git
cd spdlog 
cmake -S . -B ./build -DCMAKE_INSTALL_PREFIX=<your install location>
cmake --build ./build
cmake --install ./build
````
  
### Gtest

Like spdlog, download and bulid googletest from GitHub. Set `CMAKE_INSTALL_DIRECTORY` to the desired install location.
 ```` 
git clone https://github.com/google/googletest.git
cd googletest
cmake -S . -B ./build -DCMAKE_INSTALL_PREFIX=<your install location>
cmake --build ./build
cmake --install ./build
````

### Running CMake In Windows
Compared to Linux builds, where we find the dev libraries on the filesystem, set following variables on Windows for CMake.
````
-DSDL2_PATH="C:\Projects\extern\SDL2-2.0.20\x86_64-w64-mingw32"
-DSDL2_IMAGE_PATH="C:\Projects\extern\SDL2_image-2.0.5\x86_64-w64-mingw32"
-Dspdlog_DIR="C:\Projects\extern\spdlog\build\out\lib\cmake\spdlog"
-DGTEST_ROOT="C:\\location"
````
The CMake command from the project directory would look like:
````
cmake -S . -B ./build -G "MinGW Makefiles" \
-DSDL2_PATH="C:\Projects\extern\SDL2-2.0.20\x86_64-w64-mingw32" \
-DSDL2_IMAGE_PATH="C:\Projects\extern\SDL2_image-2.0.5\x86_64-w64-mingw32" \
-Dspdlog_DIR="C:\Projects\extern\spdlog\build\out\lib\cmake\spdlog" \
-DGTEST_ROOT="C:\\location" 

cmake --build ./build
````

# Build Options and Tools

  
  
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



