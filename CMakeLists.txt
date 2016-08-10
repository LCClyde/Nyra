###############################################################################
#  Copyright (c) 2016 Clyde Stanfield
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to
#  deal in the Software without restriction, including without limitation the
#  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
#  sell copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
#  IN THE SOFTWARE.
###############################################################################

cmake_minimum_required(VERSION 3.0)
project(Nyra)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -fPIC")

# Add platform defines
# TODO: Add more platforms as necessary
if (WIN32)
    add_definitions(-DNYRA_WIN32=${CMAKE_SYSTEM})
elseif (APPLE)
    add_definitions(-DNYRA_APPLE=${CMAKE_SYSTEM})
else()
    add_definitions(-DNYRA_POSIX=${CMAKE_SYSTEM})
endif()

#TODO: Only set this if the caller did not set it
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
set(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)
set(CMAKE_TEST_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/tests)
set(CPP_MODULES_DIR ${CMAKE_BINARY_DIR}/modules/c++/)

find_library(GoogleTest NAMES gtest PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(SFMLGraphics NAMES sfml-graphics PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(SFMLWindow NAMES sfml-window PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(SFMLSystem NAMES sfml-system PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(BOOST_ROOT ${CMAKE_INSTALL_PREFIX})
find_package(Boost 1.61.0 REQUIRED COMPONENTS serialization)
find_package(X11 REQUIRED)
include_directories(${CMAKE_INCLUDE_OUTPUT_DIRECTORY})

enable_testing()

find_package(Threads)

# Get all the modules
file(GLOB MODULES_DIRS RELATIVE ${CPP_MODULES_DIR} ${CPP_MODULES_DIR}/*)

# Loop through each module
foreach (DIR ${MODULES_DIRS})
    set(MODULE_DIR ${CPP_MODULES_DIR}/${DIR})
    set(MODULE_NAME nyra-${DIR}-cpp)
    set(MODULE_TEST_DIR ${MODULE_DIR}/tests)

    # Make sure this is a directory and not a file
    if (IS_DIRECTORY ${MODULE_DIR})

        # Clear out MOD and TEST DEPS
        set(MOD_DEPS "")
        set(TEST_DEPS "")

        if(EXISTS ${MODULE_DIR}/CMakeLists.txt)
            add_subdirectory(${MODULE_DIR})
        endif()

        # Get all the source files
        file(GLOB SOURCES ${MODULE_DIR}/source/*.cpp)
        file(GLOB INCLUDES ${MODULE_DIR}/include/*.h ${MODULE_DIR}/include/*.hpp)

        list(LENGTH SOURCES SOURCE_LENGTH)
        if (SOURCE_LENGTH EQUAL 0)
            add_library(${MODULE_NAME} INTERFACE)
            target_sources(${MODULE_NAME} INTERFACE ${INCLUDES})
            target_link_libraries(${MODULE_NAME} INTERFACE ${MOD_DEPS})
        else()
            add_library(${MODULE_NAME} ${SOURCES} ${INCLUDES})
            target_link_libraries(${MODULE_NAME} ${MOD_DEPS})
        endif()

        # Copy the headers
        add_custom_target(${MODULE_NAME}-inc
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${MODULE_DIR}/include/ ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/nyra/${DIR})
        add_dependencies(${MODULE_NAME} ${MODULE_NAME}-inc)

        # Build the unittests
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TEST_OUTPUT_DIRECTORY}/${DIR})
        if (IS_DIRECTORY ${MODULE_TEST_DIR})
            file(GLOB TESTS ${MODULE_TEST_DIR}/*.cpp)
            foreach (TEST ${TESTS})
                get_filename_component(TEST_NAME ${TEST} NAME_WE)
                add_executable(${TEST_NAME} ${TEST})
                target_link_libraries(${TEST_NAME} ${MODULE_NAME} nyra-test-cpp ${GoogleTest} ${CMAKE_THREAD_LIBS_INIT} ${TEST_DEPS} ${MOD_DEPS})
                add_test(run_${TEST_NAME} ${CMAKE_TEST_OUTPUT_DIRECTORY}/${DIR}/${TEST_NAME})
            endforeach()
        endif()
    endif()
endforeach()

