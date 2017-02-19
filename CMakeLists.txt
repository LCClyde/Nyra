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

cmake_minimum_required(VERSION 3.0.2)

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

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY AUTOMOC_TARGETS_FOLDER ${CMAKE_BINARY_DIR}/automoc/)
set(CMAKE_AUTOMOC ON)

#TODO: Only set this if the caller did not set it
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
set(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)
set(CMAKE_TEST_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/tests)
set(CPP_MODULES_DIR ${CMAKE_BINARY_DIR}/modules/cpp/)
set(CMAKE_PREFIX_PATH ${CMAKE_INSTALL_PREFIX})

find_library(GoogleTest NAMES gtest PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(SFMLGraphics NAMES sfml-graphics PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(SFMLWindow NAMES sfml-window PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(SFMLSystem NAMES sfml-system PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(SDL2 NAMES SDL2 PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(OGRE_MAIN NAMES OgreMain PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(LibPNG NAMES png PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(LibArchive NAMES archive PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(CEGUIBase NAMES CEGUIBase-0 PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(CEGUIOpenGLRenderer NAMES CEGUIOpenGLRenderer-0 PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(Cairo NAMES cairo PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(sfeMovie NAMES sfeMovie PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_library(OIS NAMES OIS PATHS ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
find_package(PythonLibs 3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

set(BOOST_ROOT ${CMAKE_INSTALL_PREFIX})
find_package(Boost 1.63.0 REQUIRED COMPONENTS serialization filesystem program_options system)
find_package(Qt5Widgets)
find_package(X11)
include_directories(${CMAKE_INCLUDE_OUTPUT_DIRECTORY})

# SDL does not references includes from its directory, so it needs to be
# added separately
include_directories(${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/SDL2)
include_directories(${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/OGRE)
include_directories(${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/cegui-0)
include_directories(${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/cairo)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

enable_testing()

find_package(Threads)

include(CMakeUtils.txt)

# Get all the modules
file(GLOB MODULES_DIRS RELATIVE ${CPP_MODULES_DIR} ${CPP_MODULES_DIR}/*)

# Loop through each module
foreach (DIR ${MODULES_DIRS})
    set(MODULE_DIR ${CPP_MODULES_DIR}/${DIR})
    set(MODULE_TEST_DIR ${MODULE_DIR}/test/apps)
    set(MODULE_APP_DIR ${MODULE_DIR}/apps)
    set(MODULE_NAME nyra-${DIR}-cpp)
    set(TEST_NAME nyra-${DIR}-test-cpp)

    # Make sure this is a directory and not a file
    if (IS_DIRECTORY ${MODULE_DIR})

        GetDeps(${MODULE_DIR})
        BuildModule(${DIR} ${MODULE_NAME} "" ${MODULE_DIR})
        BuildModule(test ${TEST_NAME} ${MODULE_NAME} ${MODULE_DIR}/test)
        BuildTests(${MODULE_NAME} ${TEST_NAME} ${MODULE_TEST_DIR} ${CMAKE_TEST_OUTPUT_DIRECTORY}/${DIR})
        BuildApps(${MODULE_NAME} ${MODULE_APP_DIR} ${CMAKE_INSTALL_PREFIX}/bin)

    endif()
endforeach()

