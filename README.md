
[![Build Status](https://dev.azure.com/thomassedlmair/cwt-2d-game-engine/_apis/build/status/ThoSe1990.cwt_game_engine?branchName=main)](https://dev.azure.com/thomassedlmair/cwt-2d-game-engine/_build/latest?definitionId=10&branchName=main)
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
Download prebuild SDL libraries (SDL2 and SDL_image). Place them on a destination of choice.

https://www.libsdl.org/download-2.0.php  
https://www.libsdl.org/projects/SDL_image/

### spdlog 

Clone the spdlog git repository and build it. Set `CMAKE_INSTALL_DIRECTORY` to the desired install location. On my private computer I use in general `./build/out` as install directory.
````
git clone https://github.com/gabime/spdlog.git
cd spdlog 
cmake -S . -B ./build -DCMAKE_INSTALL_PREFIX=<drive>/<current project path>/build/out
cmake --build ./build
cmake --install ./build
````
  
### Gtest

Like spdlog, download and bulid googletest from GitHub. Set `CMAKE_INSTALL_DIRECTORY` to the desired install location.
 ```` 
git clone https://github.com/google/googletest.git
cd googletest
cmake -S . -B ./build -DCMAKE_INSTALL_PREFIX=<drive>/<current project path>/build/out
cmake --build ./build
cmake --install ./build
````

### Running CMake In Windows
Compared to Linux builds, where we find the dev libraries on the filesystem, set following variables on Windows for CMake. After building the project, run the install command. The executable with the needed SDL runtime libraries are installed to your build directory in: `<cwt-2d-game-engine>/build/<build-type>/bin` with `<build-type>` Release or Debug. Default build is currently on Debug.
````
-DSDL2_PATH="<path to SDL2>\SDL2-2.0.20\x86_64-w64-mingw32"
-DSDL2_IMAGE_PATH="<path to SDL2_image>\SDL2_image-2.0.5\x86_64-w64-mingw32"
-Dspdlog_DIR="<drive>\\<projects>\\spdlog\\build\\out\\lib\\cmake\\spdlog"
-DGTEST_ROOT="<drive>\\<projects>\\googletest\\build\\out"
````
The CMake command from the project directory would look like:
````
cmake -S . -B ./build -G "MinGW Makefiles" 
-DSDL2_PATH="<path to SDL2>\\SDL2-2.0.20\\x86_64-w64-mingw32"
-DSDL2_IMAGE_PATH="<path to SDL2_image>\\SDL2_image-2.0.5\\x86_64-w64-mingw32"
-Dspdlog_DIR="<drive>\\<projects>\\spdlog\\build\\out\\lib\\cmake\\spdlog"
-DGTEST_ROOT="<drive>\\<projects>\\googletest\\build\\out"

cmake --build ./build
cmake --install ./build
````

Run the executable in the install directory und you'll see an empty SDL windows for a couple of seconds. 
