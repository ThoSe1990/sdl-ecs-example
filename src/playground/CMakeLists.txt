
set(target playground)

add_executable(${target}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(${target} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${target} 
${CONAN_LIBS} 
)


# install(
#     TARGETS ${target}
#     CONFIGURATIONS ${CMAKE_BUILD_TYPE}
#     DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin
# )
# install(
#     FILES ${SDL2_PATH}/bin/SDL2.dll
#     CONFIGURATIONS ${CMAKE_BUILD_TYPE}
#     DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin
# )
