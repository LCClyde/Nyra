/*
 * Copyright (c) 2018 Clyde Stanfield
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
#include <nyra/graphics/ogre/Camera.h>

namespace nyra
{
namespace graphics
{
namespace ogre
{
//===========================================================================//
Camera::Camera(const graphics::ogre::RenderTarget& target) :
    mCamera(target.getCamera())
{
    auto pos = mCamera->getPosition();
    setPosition(math::Vector3F(pos.x, pos.y, pos.z));
    auto rot = mCamera->getDirection();
    setRotation(math::Vector3F(rot.x, rot.y, rot.z));
}

//===========================================================================//
void Camera::render(graphics::RenderTarget& target)
{
    // TODO: This is not quite correct. Somethings are negated compared
    //       what ogre calculates.
    /*const math::Matrix4x4& m = getMatrix();
    Ogre::Matrix4 matrix(m(0, 0), m(0, 1), m(0, 2), m(0, 3),
                         m(1, 0), m(1, 1), m(1, 2), m(1, 3),
                         m(2, 0), m(2, 1), m(2, 2), m(2, 3),
                         m(3, 0), m(3, 1), m(3, 2), m(3, 3));

    mCamera->setCustomViewMatrix(true, matrix);*/

    const math::Vector3F& position = getPosition();
    mCamera->setPosition(position.x, position.y, position.z);

    math::Vector3F rotation = getRotation();
    std::swap(rotation.x, rotation.z);
    const math::Vector<float, 4> quaternion = math::eulerToQuaternion(rotation);
    mCamera->setOrientation(Ogre::Quaternion(quaternion[0],
                                             quaternion[1],
                                             quaternion[2],
                                             quaternion[3]));
}
}
}
}
