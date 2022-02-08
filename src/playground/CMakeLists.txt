
set(target playground)

add_executable(${target}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)


target_include_directories(${target} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${PROJECT_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

target_link_libraries(${target} 
    cwt_game_engine
    precompiled_headers
    spdlog::spdlog
    ${SDL2_LIBRARY}
)


