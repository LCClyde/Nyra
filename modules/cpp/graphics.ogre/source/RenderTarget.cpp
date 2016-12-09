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
#include <nyra/graphics/ogre/RenderTarget.h>
#include <OgreColourValue.h>
#include <OgreHardwarePixelBuffer.h>

namespace nyra
{
namespace graphics
{
namespace ogre
{
//===========================================================================//
RenderTarget::RenderTarget(const math::Vector2U& size) :
    mWindow(nullptr),
    mRenderTexture(nullptr)
{
    initialize(size);
}

//===========================================================================//
RenderTarget::RenderTarget(win::Window& window) :
    mWindow(nullptr),
    mRenderTexture(nullptr)
{
    initialize(window);
    initialize(window.getSize());
}

//===========================================================================//
void RenderTarget::initialize(win::Window& window)
{
    mWindow = reinterpret_cast<Ogre::RenderWindow*>(window.getNative());
}

//===========================================================================//
void RenderTarget::initialize(const math::Vector2U& size)
{
    mTexture = Ogre::TextureManager::getSingleton().createManual(
        "RenderTexture",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Ogre::TEX_TYPE_2D,
        size.x(),
        size.y(),
        0,
        Ogre::PF_R8G8B8,
        Ogre::TU_RENDERTARGET);
    mRenderTexture = mTexture->getBuffer()->getRenderTarget();

    static size_t cameraNumber = 0;
    mCamera = getGlobalInstance().getSceneManager()->createCamera(
            "RenderTargetCamera_" + std::to_string(++cameraNumber));
    mCamera->setPosition(0, 0, 5);
    mCamera->lookAt(Ogre::Vector3(0, 0, 0));
    mRenderTexture->addViewport(mCamera);
    mRenderTexture->setAutoUpdated(false);
    mRenderTexture->getViewport(0)->setClearEveryFrame(true);
}

//===========================================================================//
math::Vector2U RenderTarget::getSize() const
{
    return math::Vector2U(mTexture->getWidth(),
                          mTexture->getHeight());
}

//===========================================================================//
void RenderTarget::resize(const math::Vector2U& size)
{
    initialize(size);
}

//===========================================================================//
void RenderTarget::clear(const img::Color& color)
{
    mRenderTexture->getViewport(0)->setBackgroundColour(
            Ogre::ColourValue(color.r / 255.0f,
                              color.g / 255.0f,
                              color.b / 255.0f,
                              color.a / 255.0f));
}

//===========================================================================//
void RenderTarget::flush()
{
    getGlobalInstance().getRoot()->renderOneFrame();
    mRenderTexture->update();
}

//===========================================================================//
img::Image RenderTarget::getPixels() const
{
    Ogre::Image::Box imageBox;
    Ogre::HardwarePixelBufferSharedPtr returnBuffer = mTexture->getBuffer();
    const Ogre::PixelBox& returnBufferPixelBox =
            returnBuffer->lock(imageBox, Ogre::HardwareBuffer::HBL_NORMAL);
    const img::Image ret(
            static_cast<uint8_t*>(returnBufferPixelBox.data),
            getSize(),
            img::Image::BGRA);
    returnBuffer -> unlock();
    return ret;
}
}
}
}
