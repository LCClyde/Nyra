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

include(CMakeUtils.txt)

# Get all the modules
file(GLOB MODULES_DIRS RELATIVE ${CPP_MODULES_DIR} ${CPP_MODULES_DIR}/*)

# Loop through each module
foreach (DIR ${MODULES_DIRS})
    set(MODULE_DIR ${CPP_MODULES_DIR}/${DIR})
    set(MODULE_TEST_DIR ${MODULE_DIR}/test/apps)
    set(MODULE_NAME nyra-${DIR}-cpp)
    set(TEST_NAME nyra-${DIR}-test-cpp)

    # Make sure this is a directory and not a file
    if (IS_DIRECTORY ${MODULE_DIR})

        GetDeps(${MODULE_DIR})
        BuildModule(${DIR} ${MODULE_NAME} "" ${MODULE_DIR})
        BuildModule(test ${TEST_NAME} ${MODULE_NAME} ${MODULE_DIR}/test)
        BuildTests(${MODULE_NAME} ${TEST_NAME} ${MODULE_TEST_DIR} ${CMAKE_TEST_OUTPUT_DIRECTORY}/${DIR})

    endif()
endforeach()

