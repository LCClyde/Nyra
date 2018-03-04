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
#ifndef __NYRA_GRAPHICS_RENDERABLE_H__
#define __NYRA_GRAPHICS_RENDERABLE_H__

#include <nyra/graphics/RenderTarget.h>
#include <nyra/math/Transform.h>

namespace nyra
{
namespace graphics
{
/*
 *  \class Renderable
 *  \brief Interface class for objects that can be rendered
 */
template <class TransformT>
class Renderable : public TransformT
{
public:
    /*
     *  \func Destructor
     *  \brief Here for inheritance
     */
    virtual ~Renderable() = default;

    /*
     *  \func render
     *  \brief Renders to the screen
     *
     *  \param transform The transform that represents this object
     *  \param target The target to render to
     */
    virtual void render(RenderTarget& target) = 0;
};

typedef Renderable<math::Transform2D> Renderable2D;
typedef Renderable<math::Transform3D> Renderable3D;
}
}

#endif
