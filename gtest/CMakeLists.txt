
set(target unittests)

add_executable(${target}
${CMAKE_CURRENT_SOURCE_DIR}/main.cc
${CMAKE_CURRENT_SOURCE_DIR}/test.cc
)

target_link_libraries(${target}    
    ${CONAN_LIBS}
    project_warnings
)
set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY "")

add_test(NAME ${target} COMMAND ${target})
