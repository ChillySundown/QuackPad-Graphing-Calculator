cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(barkeshli_s22 LANGUAGES CXX)

include(GNUInstallDirs)
include(FetchContent)

if(MSVC)
    add_compile_options(/W3)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
else()
    # add_compile_options(-Wall -Wextra -pedantic)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Enabling code coverage flags for Debug build.")
        add_compile_options("-fprofile-arcs" "-ftest-coverage")
        add_link_options("-fprofile-arcs" "-ftest-coverage")
    endif()
endif()

message(STATUS "Setting up GoogleTest via FetchContent.")
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.17.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of googletest" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

message(STATUS "Setting up SFML via FetchContent (version 3.0.1)")
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# set(SFML_USE_STATIC_LIBS OFF CACHE BOOL "Build SFML as shared libraries" FORCE)

set(SFML_GRAPHICS_TARGET sfml-graphics)
message(STATUS "SFML target to link against: ${SFML_GRAPHICS_TARGET}")

set(INCLUDES_FOLDER includes)
message(STATUS "Looking for source files in: ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDES_FOLDER}")

file(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${INCLUDES_FOLDER}/*.cpp"
)

file(GLOB_RECURSE HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${INCLUDES_FOLDER}/*.h"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDES_FOLDER})

add_executable(main
        main.cpp
        ${SOURCE_FILES}
    ${HEADER_FILES}
)
target_link_libraries(main PRIVATE ${SFML_GRAPHICS_TARGET})
target_compile_features(main PRIVATE cxx_std_17)
message(STATUS "Added executable 'main' linked against ${SFML_GRAPHICS_TARGET}")

add_executable(basic_test
        _tests/_test_files/basic_test.cpp
        ${SOURCE_FILES}
        ${HEADER_FILES}
)
target_link_libraries(basic_test PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(basic_test PRIVATE ${SFML_GRAPHICS_TARGET})
message(STATUS "Added executable 'basic_test' linked against GoogleTest")

add_executable(testB
        _tests/_test_files/testB.cpp
        ${SOURCE_FILES}
        ${HEADER_FILES}
)
target_link_libraries(testB PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(testB PRIVATE ${SFML_GRAPHICS_TARGET})
message(STATUS "Added executable 'testB' linked against GoogleTest")

include(GoogleTest)
gtest_discover_tests(basic_test)
gtest_discover_tests(testB)
message(STATUS "GoogleTest discovery enabled for test executables.")
 

