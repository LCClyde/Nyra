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
if (UNIX)
    set(BOOTSTRAP ./bootstrap.sh)
    set(B2 ./b2)
else()
    if (WIN32)
        set(BOOTSTRAP bootstrap.bat)
        set(B2 b2.exe)
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
    CONFIGURE_COMMAND ${BOOTSTRAP}
    BUILD_COMMAND ${B2} headers COMMAND ${B2} install
        --prefix=${INSTALL_DIR}
        --disable-icu
        --variant=release
        -j4
    INSTALL_COMMAND ""
    INSTALL_DIR ${INSTALL_DIR})
