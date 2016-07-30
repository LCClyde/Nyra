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

#TODO: Only set this if the caller did not set it
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

set(CPP_MODULES_DIR ${CMAKE_BINARY_DIR}/modules/c++)
set(EXTERNAL_DIR ${CMAKE_BINARY_DIR}/external/install)

file(GLOB MODULES_DIRS RELATIVE ${CPP_MODULES_DIR} ${CPP_MODULES_DIR}/*)
message(${CPP_MODULES_DIR})
foreach(DIR ${MODULES_DIRS})
    message(${DIR})
    if (IS_DIRECTORY ${CPP_MODULES_DIR}/${DIR})
        list(APPEND MODULES ${CPP_MODULES_DIR}/${DIR})

        # Check for a custom cmake
        #if(EXISTS ${CPP_MODULES_DIR}/${dir}/CMakeLists.txt)
        #    add_subdirectory(${CPP_MODULES_DIR}/${dir})
        #endif()

        # Build the file
        #file(GLOB files ${CPP_MODULES_DIR}/${dir} ${PROJECTS_DIRECTORY}/${dir}/*.cpp)
        #add_executable(${dir} ${files})
        #target_link_libraries(${dir} nyra)
    endif()
endforeach()



message(${MODULES})
