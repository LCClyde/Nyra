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

set(INSTALL_DIR ${CMAKE_BINARY_DIR}/../install)
set(INCLUDE_DIR ${INSTALL_DIR}/include)
set(LIB_DIR ${INSTALL_DIR}/lib)
set(BUILD_DIR ${CMAKE_BINARY_DIR}/../build)

file(GLOB DRIVERS_DIR RELATIVE ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/*)
foreach(DIR ${DRIVERS_DIR})
    if (IS_DIRECTORY ${CMAKE_BINARY_DIR}/${DIR})

        # Check for a custom cmake
        if(EXISTS ${CMAKE_BINARY_DIR}/${DIR}/CMakeLists.txt)
            add_subdirectory(${DIR})
        endif()
    endif()
endforeach()


###############################################################################
# FCEUX
###############################################################################
#ExternalProject_Add(
#    FCEUX
#    PREFIX ${BUILD_DIR}
#    SVN_REPOSITORY svn://svn.code.sf.net/p/fceultra/code/fceu/trunk
#    SVN_REVISION -r3256
#    BUILD_IN_SOURCE 1
#    CONFIGURE_COMMAND ""
#    BUILD_COMMAND scons install --prefix=${INSTALL_DIR}
#    INSTALL_COMMAND "")
