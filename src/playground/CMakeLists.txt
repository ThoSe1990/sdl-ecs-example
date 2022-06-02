
set(target playground)

add_executable(${target}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${PROJECT_SOURCE_DIR}/imgui/imgui_tables.cpp 
    ${PROJECT_SOURCE_DIR}/imgui/imgui_widgets.cpp 
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl.cpp
    ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_sdlrenderer.cpp
)


target_include_directories(${target} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/imgui
    ${PROJECT_SOURCE_DIR}/imgui/backends
)

target_link_libraries(${target} 
    precompiled_headers
    cwt_game_engine
    spdlog::spdlog
    ${SDL2_LIBRARY}
)


install(
    TARGETS ${target}
    CONFIGURATIONS ${CMAKE_BUILD_TYPE}
    DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin
)
install(
    FILES ${SDL2_PATH}/bin/SDL2.dll
    CONFIGURATIONS ${CMAKE_BUILD_TYPE}
    DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin
)
