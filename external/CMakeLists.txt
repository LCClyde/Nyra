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

###############################################################################
# Simple and Fast Multimedia Library
###############################################################################
ExternalProject_Add(
    SFML
    PREFIX ${BUILD_DIR}
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.3.2
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR})

###############################################################################
# Google Test
###############################################################################
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

###############################################################################
# Graphics Math Template Library
###############################################################################
ExternalProject_Add(
    GMTL
    PREFIX ${BUILD_DIR}
    SVN_REPOSITORY http://svn.code.sf.net/p/ggt/code/tags/0.6.1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
        <SOURCE_DIR>/gmtl/ ${INCLUDE_DIR}/gmtl)

###############################################################################
# Boost 1.61.0
###############################################################################
set(Boost_Bootstrap_Command)
if (UNIX)
    set(Boost_Bootstrap_Command ./bootstrap.sh)
    set(Boost_b2_Command ./b2)
else()
    if (WIN32)
        set(Boost_Bootstrap_Command bootstrap.bat)
        set(Boost_b2_Command b2.exe)
    endif()
endif()

ExternalProject_Add(
    Boost
    PREFIX ${BUILD_DIR}
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.61.0
    BUILD_IN_SOURCE 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ${Boost_Bootstrap_Command}
    BUILD_COMMAND  ${Boost_b2_Command} install
        --prefix=${INSTALL_DIR}
        --link=shared
        --variant=release
    INSTALL_COMMAND ""
    INSTALL_DIR ${INSTALL_DIR})

###############################################################################
# Boost 1.61.0
###############################################################################

