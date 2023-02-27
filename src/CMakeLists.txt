
set(target game)

add_executable(${target}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(${target} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${target} 
${CONAN_LIBS} 
)

