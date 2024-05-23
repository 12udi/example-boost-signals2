cmake_minimum_required(VERSION 3.25.2)

include(GenerateExportHeader)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

project(example-boost-signals
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(EXAMPLE_INSTALL_SUFFIX bin/example)
set(EXAMPLE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/${EXAMPLE_INSTALL_SUFFIX} CACHE PATH "")

find_package(boost_signals2 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_subdirectory(example)

enable_testing()
include(GoogleTest)
find_package(GTest CONFIG REQUIRED)
message(STATUS "${PROJECT_NAME}: Using GTest v" ${GTest_VERSION})
set(CMAKE_GTEST_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(test/unit)
