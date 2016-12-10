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
#ifndef __NYRA_GRAPHICS_SPRITE_H__
#define __NYRA_GRAPHICS_SPRITE_H__

#include <nyra/graphics/Renderable.h>
#include <nyra/math/Transform.h>

namespace nyra
{
namespace graphics
{
/*
 *  \class Sprite
 *  \brief Class for rendering images to a render target.
 */
class Sprite : public Renderable<math::Transform2D>
{
public:
    /*
     *  \func Destructor
     *  \brief Here for proper inheritance.
     */
    virtual ~Sprite() = default;

    /*
     *  \func load
     *  \brief Loads a Sprite from a texture on disk.
     *
     *  \param texture The name of the texture.
     */
    virtual void load(const std::string& texture) = 0;
};
}
}

#endif
