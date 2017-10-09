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
    Box2D
    PREFIX ${BUILD_DIR}
    GIT_REPOSITORY https://github.com/erincatto/Box2D.git
    GIT_TAG v2.3.1
    CONFIGURE_COMMAND ${CMAKE_COMMAND}
            -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} -DBOX2D_INSTALL=ON
            -DBOX2D_BUILD_SHARED=OFF -DBOX2D_BUILD_STATIC=ON
            -DBOX2D_BUILD_EXAMPLES=OFF -DCMAKE_BUILD_TYPE=Release
            -DCMAKE_VERBOSE_MAKEFILE=ON  <SOURCE_DIR>/Box2D)
