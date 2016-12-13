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
#include <stdexcept>
#include <nyra/graphics/gl/Shader.h>
#include <iostream>

namespace
{
//===========================================================================//
static const std::string VERTEX_SHADER =
        "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}\n";

//===========================================================================//
static const std::string FRAGMENT_SHADER =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "    color = vec4(0.8f, 0.8f, 0.8f, 1.0f);\n"
        "}\n";
}

namespace nyra
{
namespace graphics
{
namespace gl
{
//===========================================================================//
Shader::Shader(const std::string& vertexString,
               const std::string& fragmentString)
{
    const GLuint vertexShader = compileShader(
            vertexString.empty() ? VERTEX_SHADER : vertexString,
            GL_VERTEX_SHADER);
    const GLuint fragmentShader = compileShader(
            fragmentString.empty() ? FRAGMENT_SHADER : fragmentString,
            GL_FRAGMENT_SHADER);

    mShader = glCreateProgram();
    glAttachShader(mShader, vertexShader);
    glAttachShader(mShader, fragmentShader);
    glLinkProgram(mShader);

    GLint success;
    glGetProgramiv(mShader, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar errorMessage[512];
        glGetProgramInfoLog(mShader, 512, NULL, errorMessage);
        throw std::runtime_error(
                std::string("Shader linking failed: ") + errorMessage);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

//===========================================================================//
GLuint Shader::compileShader(const std::string& shaderString,
                             GLenum shaderType) const
{
    const GLuint shader = glCreateShader(shaderType);
    const GLchar* shaderCString =
            reinterpret_cast<const GLchar*>(shaderString.c_str());
    glShaderSource(shader, 1, &shaderCString, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar errorMessage[512];
        glGetShaderInfoLog(shader, 512, NULL, errorMessage);
        throw std::runtime_error(
                std::string("Shader compilation failed: ") + errorMessage);
    }
    return shader;
}
}
}
}
