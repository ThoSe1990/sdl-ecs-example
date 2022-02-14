
set(target gtest)

add_executable(${target}
    ${CMAKE_CURRENT_SOURCE_DIR}/test.cc
)
target_link_libraries(gtest
    precompiled_headers_gtest    
    project_warnings
    spdlog::spdlog
    GTest::Main
    GTest::GTest
)
set_target_properties(${target} PROPERTIES CXX_CLANG_TIDY "")

if(ENABLE_COVERAGE)
    set(CMAKE_BUILD_TYPE Debug)
    if(CMAKE_COMPILER_IS_GNUCXX)
        include(${PROJECT_SOURCE_DIR}/cmake/CodeCoverage.cmake)
        append_coverage_compiler_flags()
        setup_target_for_coverage_lcov(
            NAME ${target}_coverage
            EXECUTABLE ${target}
            EXCLUDE "/usr/include/*"
        )
    endif()
endif(ENABLE_COVERAGE)
unset(ENABLE_COVERAGE CACHE) 