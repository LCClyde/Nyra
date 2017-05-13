###############################################################################
#  Copyright (c) 2017 Clyde Stanfield
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
ExternalProject_Add(
    FastNoise
    PREFIX ${BUILD_DIR}
    GIT_REPOSITORY https://github.com/Auburns/FastNoise.git
    GIT_TAG 0.3.1
    BUILD_IN_SOURCE 1
    UPDATE_COMMAND ""
    PATCH_COMMAND patch <SOURCE_DIR>/FastNoise.h < ${CMAKE_BINARY_DIR}/FastNoise/patch.diff
    CONFIGURE_COMMAND ""
    BUILD_COMMAND g++ -std=c++11 -fPIC FastNoise.cpp -shared -o libFastNoise.so
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy
        <SOURCE_DIR>/FastNoise.h ${INCLUDE_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy
        <BINARY_DIR>/${CMAKE_SHARED_LIBRARY_PREFIX}FastNoise${CMAKE_SHARED_LIBRARY_SUFFIX}
        ${LIB_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}FastNoise${CMAKE_SHARED_LIBRARY_SUFFIX})
