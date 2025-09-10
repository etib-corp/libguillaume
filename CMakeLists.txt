cmake_minimum_required(VERSION 3.10)

# ------------------------------------------------------------------------------
# Project Metadata
# ------------------------------------------------------------------------------
project(
    guillaume-connector
    VERSION 0.1.0
    DESCRIPTION "Connector for Guillaume, a React-inspired Python XR framework optimized for AR/VR applications."
    HOMEPAGE_URL "https://github.com/etib-corp/guillaume-connector"
    LANGUAGES CXX
)

# ------------------------------------------------------------------------------
# Compiler Settings
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------------------------
# Module Imports
# ------------------------------------------------------------------------------
include(FetchContent)

include(CTest)
enable_testing()

# ------------------------------------------------------------------------------
# Xerces-C Setup
# ------------------------------------------------------------------------------
FetchContent_Declare(
    xerces-c
    GIT_REPOSITORY https://github.com/apache/xerces-c.git
    GIT_TAG v3.3.0
)
FetchContent_MakeAvailable(xerces-c)

# ------------------------------------------------------------------------------
# GoogleTest Setup 
# ------------------------------------------------------------------------------

# Force shared CRT on Windows for GoogleTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

# ------------------------------------------------------------------------------
# Directory Structure
# ------------------------------------------------------------------------------
set(HEADERS_DIRECTORY ${PROJECT_SOURCE_DIR}/headers)
set(SOURCES_DIRECTORY ${PROJECT_SOURCE_DIR}/sources)
set(TESTS_DIRECTORY ${PROJECT_SOURCE_DIR}/tests)

include_directories(${HEADERS_DIRECTORY})

# ------------------------------------------------------------------------------
# Source Files
# ------------------------------------------------------------------------------
file(GLOB_RECURSE SOURCES ${SOURCES_DIRECTORY}/*.cpp)
file(GLOB_RECURSE TESTS ${TESTS_DIRECTORY}/*.cpp)

# ------------------------------------------------------------------------------
# Targets
# ------------------------------------------------------------------------------

# Main library target
add_library(guillaume-connector STATIC ${SOURCES})
target_link_libraries(guillaume-connector PRIVATE xerces-c)
target_include_directories(guillaume-connector PUBLIC ${HEADERS_DIRECTORY})

# Test targets
foreach(test_file ${TESTS})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(test_${test_name} ${test_file})
    target_link_libraries(test_${test_name} PRIVATE guillaume-connector)
    target_link_libraries(test_${test_name} PRIVATE gtest gtest_main)
    add_test(NAME ${test_name} COMMAND test_${test_name})
endforeach()
