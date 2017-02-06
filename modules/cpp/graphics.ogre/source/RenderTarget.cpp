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
#include <atomic>
#include <OGRE/OgreColourValue.h>
#include <OGRE/OgreHardwarePixelBuffer.h>
#include <nyra/graphics/ogre/RenderTarget.h>

namespace
{
static std::atomic_size_t TARGET_NUMBER(0);
}

namespace nyra
{
namespace graphics
{
namespace ogre
{
//===========================================================================//
RenderTarget::RenderTarget(const math::Vector2U& size) :
    mID(0),
    mWindow(nullptr),
    mRenderTexture(nullptr),
    mScreen(true),
    mScreenNode(nullptr),
    mScreenManager(nullptr)
{
    initialize(size);
}

//===========================================================================//
RenderTarget::RenderTarget(win::Window& window) :
    mID(0),
    mWindow(nullptr),
    mRenderTexture(nullptr),
    mScreen(true),
    mScreenNode(nullptr),
    mScreenManager(nullptr)
{
    initialize(window.getSize());
    initialize(window);
}

//===========================================================================//
void RenderTarget::initialize(win::Window& window)
{
    mWindow = reinterpret_cast<Ogre::RenderWindow*>(window.getNative());

    mScreenManager = getGlobalInstance().getRoot()->createSceneManager(
            Ogre::ST_GENERIC);
    Ogre::Camera* camera = mCamera =
            mScreenManager->createCamera(
            "FullscreenCamera_" + std::to_string(mID));

    mWindow->addViewport(camera);
    mWindow->setAutoUpdated(false);
    mWindow->getViewport(0)->setClearEveryFrame(true);
    mWindow->getViewport(0)->setBackgroundColour(
            Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f));

    mScreen.setCorners(-1.0, 1.0, 1.0, -1.0);
    mScreen.setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);

    mScreenNode = mScreenManager->getRootSceneNode()->createChildSceneNode();
    mScreenNode->attachObject(&mScreen);

    mRenderMaterial =
            Ogre::MaterialManager::getSingleton().create(
            "RttMat",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    mRenderMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(false);
    mRenderMaterial->getTechnique(0)->getPass(0)->createTextureUnitState(
            "RenderTexture_" + std::to_string(mID));
    mScreen.setMaterial("RttMat");
}

//===========================================================================//
void RenderTarget::initialize(const math::Vector2U& size)
{
    Ogre::SceneManager& manager = *getGlobalInstance().getSceneManager();

    // TODO: Do I need to destroy this? It causes crashes, but need
    //       to verify.
    //if (mCamera)
    //{
    //    manager.destroyCamera(mCamera);
    //}

    mID = (TARGET_NUMBER++);

    // TODO: Do I need to destroy the previous texture?
    mTexture = Ogre::TextureManager::getSingleton().createManual(
        "RenderTexture_" + std::to_string(mID),
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Ogre::TEX_TYPE_2D,
        size.x(),
        size.y(),
        0,
        Ogre::PF_R8G8B8,
        Ogre::TU_RENDERTARGET);
    mRenderTexture = mTexture->getBuffer()->getRenderTarget();

    mCamera = manager.createCamera("RenderTargetCamera_" + std::to_string(mID));
    mCamera->setPosition(Ogre::Vector3(0, 0, 500));
    mCamera->lookAt(Ogre::Vector3(0, 0, 0));
    mCamera->setNearClipDistance(5);
    mRenderTexture->addViewport(mCamera);
    mRenderTexture->setAutoUpdated(true);
    mCamera->setAspectRatio(
            Ogre::Real(mRenderTexture->getViewport(0)->getActualWidth()) /
            Ogre::Real(mRenderTexture->getViewport(0)->getActualHeight()));
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
    if (mWindow)
    {
        mWindow->update();
    }
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
