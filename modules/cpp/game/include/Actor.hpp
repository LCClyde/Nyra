/*
 * Copyright (c) 2017 Clyde Stanfield
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
#ifndef __NYRA_GAME_ACTOR_HPP__
#define __NYRA_GAME_ACTOR_HPP__

#include <memory>
#include <vector>
#include <iostream>
#include <nyra/json/JSON.h>
#include <nyra/core/String.h>
#include <nyra/mem/Buffer2D.h>
#include <nyra/graphics/TileMap.h>
#include <nyra/core/Path.h>
#include <nyra/script/Function.h>
#include <nyra/anim/Frame.h>
#include <nyra/game/NavMesh.h>
#include <nyra/game/Gui.h>
#include <nyra/physics/Body.h>
#include <nyra/core/Event.h>

namespace nyra
{
namespace game
{
//===========================================================================//
template <typename GameT>
Actor<GameT>::Actor() :
    mCurrentAnimation(nullptr),
    mGUI(nullptr),
    mLayer(0),
    mHasInit(false)
{
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::update(float delta)
{
    if (mScript.get() && mUpdate.get())
    {
        mUpdate->call(VariableT(delta));
    }

    if (mCurrentAnimation)
    {
        mCurrentAnimation->update(delta);
    }

    if (mGUI)
    {
        mGUI->update(delta);
    }
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::initialize()
{
    if (mHasInit)
    {
        return;
    }

    if (mScript.get() && mInitialize.get())
    {
        mInitialize->call();
    }
    mHasInit = true;
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::addNavMesh(NavMesh<GameT>* mesh)
{
    mNavMesh.reset(mesh);
}

//===========================================================================//
template <typename GameT>
const NavMesh<GameT>& Actor<GameT>::getNavMesh() const
{
    return *mNavMesh;
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::addRenderable(RenderableT* renderable)
{
    mRenderable.reset(renderable);
}

//===========================================================================//
template <typename GameT>
typename GameT::Graphics::Renderable& Actor<GameT>::getRenderable()
{
    return *mRenderable;
}

//===========================================================================//
template <typename GameT>
const typename GameT::Graphics::Renderable& Actor<GameT>::getRenderable() const
{
    return *mRenderable;
}

//===========================================================================//
template <typename GameT>
const nyra::script::Object& Actor<GameT>::getScript() const
{
    return *mScript;
}

//===========================================================================//
template <typename GameT>
bool Actor<GameT>::hasScript() const
{
    return mScript.get() != nullptr;
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::addGUI(Gui<GameT>* gui)
{
    mGUI = gui;
    addRenderable(gui);
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::addBody(physics::Body<TransformT>* body)
{
    mBody.reset(body);
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::addCircleCollision(double radius,
                        const VectorT& offset)
{
    mBody->addCircle(radius, offset);
    mCollision.push_back(std::unique_ptr<RenderableT>(new SpriteT(
            core::path::join(core::DATA_PATH,
                             "textures/collision_circle.png"))));
    mCollision.back()->setPosition(offset);
    mCollision.back()->setScale(math::Vector2F(radius / 64.0,
                                               radius / 64.0));
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::renderCollision(graphics::RenderTarget& target)
{
    for (size_t ii = 0; ii < mCollision.size(); ++ii)
    {
        mCollision[ii]->updateTransform(*this);
        mCollision[ii]->render(target);
    }
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::updatePhysics()
{
    if (mBody.get())
    {
        mBody->update();
        TransformT::resetDirty();
    }
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::updateTransform()
{
    static TransformT transform;
    TransformT::updateTransform(transform);
    if (mRenderable.get())
    {
        mRenderable->updateTransform(*this);
    }
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::render(graphics::RenderTarget& target)
{
    if (mRenderable.get())
    {
        mRenderable->render(target);
    }
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::setScript(ObjectT* script)
{
    mScript.reset(script);
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::setUpdateFunction(const std::string& name)
{
    mUpdate = mScript->function(name);
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::setInitializeFunction(const std::string& name)
{
    mInitialize = mScript->function(name);
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::callActivateFunction(const std::string& name)
{
    mScript->function(name)->call();
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::setActivatedFunction(const std::string& name,
                           core::Event<void()>& event)
{
    event = std::bind(&Actor::callActivateFunction, this, name);
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::addAnimation(const std::string& name,
                  anim::Animation* anim)
{
    mAnimations[name] = std::unique_ptr<anim::Animation>(anim);
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::playAnimation(const std::string& name)
{
    anim::Animation* newAnim =  mAnimations.at(name).get();

    if (newAnim != mCurrentAnimation)
    {
        mCurrentAnimation = newAnim;
        mCurrentAnimation->reset();
        mCurrentAnimationName = name;
    }
}

//===========================================================================//
template <typename GameT>
const std::string& Actor<GameT>::getAnimation() const
{
    return mCurrentAnimationName;
}

//===========================================================================//
template <typename GameT>
const std::string& Actor<GameT>::getName() const
{
    return mName;
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::setName(const std::string& name)
{
    mName = name;
}

//===========================================================================//
template <typename GameT>
int32_t Actor<GameT>::getLayer() const
{
    return mLayer;
}

//===========================================================================//
template <typename GameT>
void Actor<GameT>::setLayer(int32_t layer)
{
    mLayer = layer;
}

//===========================================================================//
template <typename GameT>
physics::Body<typename GameT::Graphics::Transform>& Actor<GameT>::getPhysics()
{
    return *mBody;
}

//===========================================================================//
template <typename GameT>
const physics::Body<typename GameT::Graphics::Transform>&
Actor<GameT>::getPhysics() const
{
    return *mBody;
}

//===========================================================================//
template <typename GameT>
gui::Widget& Actor<GameT>::getWidget(const std::string& name)
{
    return mGUI->getWidget(name);
}
}
}

#endif
