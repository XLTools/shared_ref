#  :copyright: (c) 2017 The Regents of the University of California.
#  :license: MIT, see LICENSE.md for more details.

cmake_minimum_required(VERSION 2.8)
project(lattice CXX)

# FLAGS
# -----

set(CMAKE_CXX_STANDARD 11)

# OPTIONS
# -------

option(BUILD_TESTS "Build unittests (requires GTest)" OFF)

if(UNIX)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
elseif(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} /MTd /O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /Ox")
endif()


# TESTS
# -----

set(TEST_FILES
    test/main.cpp
)

if(BUILD_TESTS)
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
    if(NOT TARGET gtest)
        add_subdirectory(googletest)
    endif()
    add_executable(shared_ref_test ${TEST_FILES})
    target_link_libraries(shared_ref_test
        gtest
        gtest_main
    )
    set_target_properties(shared_ref_test PROPERTIES OUTPUT_NAME test)

     add_custom_target(check_shared_ref
        COMMAND $<TARGET_FILE:shared_ref_test>
        DEPENDS shared_ref_test
    )
endif()
