
set(target game)

set(BIRD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/assets/bird.png)
set(BLUE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/assets/blue.png)
set(ORANGE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/assets/orange.png)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/assets.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/assets.hpp)

add_executable(${target}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bindings/imgui_impl_sdl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bindings/imgui_impl_sdlrenderer.cpp 
)

target_include_directories(${target} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${target} 
${CONAN_LIBS} 
)

