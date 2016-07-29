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

include(ExternalProject)

set(INSTALL_DIR ${CMAKE_BINARY_DIR}/install)
set(INCLUDE_DIR ${INSTALL_DIR}/include)
set(LIB_DIR ${INSTALL_DIR}/lib)
set(BUILD_DIR ${CMAKE_BINARY_DIR}/build)

ExternalProject_Add(
    SFML
    PREFIX ${BUILD_DIR}
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.3.2
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR})

ExternalProject_Add(
    GoogleTest
    PREFIX ${BUILD_DIR}
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.7.0
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
        <SOURCE_DIR>/include/ ${INCLUDE_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy
        <BINARY_DIR>/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
        ${LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
        COMMAND ${CMAKE_COMMAND} -E copy
        <BINARY_DIR>/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
        ${LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})

#include_directories(${EXTERNAL_INCLUDE_DIR})
#link_directories(${EXTERNAL_LIB_DIR})

