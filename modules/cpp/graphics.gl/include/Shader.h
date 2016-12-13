/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef __NYRA_GRAPHICS_GL_SHADER_H__
#define __NYRA_GRAPHICS_GL_SHADER_H__

#include <string>
#include <GL/glew.h>
#include <nyra/pattern/GlobalDependency.h>
#include <nyra/gl/GlobalHandler.h>

namespace nyra
{
namespace graphics
{
namespace gl
{
/*
 *  \class Shader
 *  \brief Compiles and holds an OpenGL shader.
 */
class Shader :
        private nyra::pattern::GlobalDependency<nyra::gl::GlobalHandler>
{
public:
    /*
     *  \func Constructor
     *  \brief Compiles the shader.
     *
     *  \param vertexString The vertex shader. Pass in an empty string
     *         to create a trivial shader.
     *  \param fragmentString The fragment shader. Pass in an empty string
     *         to create a trivial shader.
     */
    Shader(const std::string& vertexString,
           const std::string& fragmentString);

    /*
     *  \func getNative
     *  \brief Gets the underlying OpenGL object.
     *
     *  \return The OpenGL shader program.
     */
    GLuint getNative() const
    {
        return mShader;
    }

private:
    GLuint compileShader(const std::string& shaderString,
                         GLenum shaderType) const;

    GLuint mShader;
};
}
}
}

#endif
