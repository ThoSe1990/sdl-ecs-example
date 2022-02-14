
set(target cwt_game_engine)

add_library(${target} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
) 


target_include_directories(${target} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

target_link_libraries(${target} 
    spdlog::spdlog
    ${SDL2_LIBRARY}
)

