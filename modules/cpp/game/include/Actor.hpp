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
#include <nyra/core/Path.h>
#include <nyra/script/py3/Variable.h>
#include <nyra/math/Transform.h>
#include <nyra/game/Types.h>
#include <nyra/script/Object.h>

namespace nyra
{
namespace game
{
//===========================================================================//
Actor::Actor() :
    mCurrentAnimation(nullptr),
    mGUI(nullptr),
    mLayer(0),
    mHasInit(false)
{
}

//===========================================================================//
void Actor::update(float delta)
{
    if (mScript.get() && mUpdate.get())
    {
        mUpdate->call(script::py3::Variable(delta));
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
void Actor::initialize()
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
void Actor::addNavMesh(NavMesh* mesh)
{
    mNavMesh.reset(mesh);
}

//===========================================================================//
const NavMesh& Actor::getNavMesh() const
{
    return *mNavMesh;
}

//===========================================================================//
void Actor::addRenderable(graphics::Renderable2D* renderable)
{
    mRenderable.reset(renderable);
}

//===========================================================================//
graphics::Renderable2D& Actor::getRenderable()
{
    return *mRenderable;
}

//===========================================================================//
const graphics::Renderable2D& Actor::getRenderable() const
{
    return *mRenderable;
}

//===========================================================================//
const nyra::script::Object& Actor::getScript() const
{
    return *mScript;
}

//===========================================================================//
bool Actor::hasScript() const
{
    return mScript.get() != nullptr;
}

//===========================================================================//
void Actor::addGUI(Gui* gui)
{
    mGUI = gui;
    addRenderable(gui);
}

//===========================================================================//
void Actor::addBody(physics::Body<math::Transform2D>* body)
{
    mBody.reset(body);
}

//===========================================================================//
void Actor::addCircleCollision(double radius,
                               const math::Vector2F& offset)
{
    mBody->addCircle(radius, offset);
    mCollision.push_back(std::unique_ptr<graphics::Renderable2D>(
            new SpriteT(
            core::path::join(core::DATA_PATH,
                             "textures/collision_circle.png"))));
    mCollision.back()->setPosition(offset);
    mCollision.back()->setScale(math::Vector2F(radius / 64.0,
                                               radius / 64.0));
}

//===========================================================================//
void Actor::renderCollision(graphics::RenderTarget& target)
{
    for (size_t ii = 0; ii < mCollision.size(); ++ii)
    {
        mCollision[ii]->updateTransform(*this);
        mCollision[ii]->render(target);
    }
}

//===========================================================================//
void Actor::updatePhysics()
{
    if (mBody.get())
    {
        mBody->update();
        resetDirty();
    }
}

//===========================================================================//
void Actor::updateTransform()
{
    static math::Transform2D transform;
    math::Transform2D::updateTransform(transform);
    if (mRenderable.get())
    {
        mRenderable->updateTransform(*this);
    }
}

//===========================================================================//
void Actor::render(graphics::RenderTarget& target)
{
    if (mRenderable.get())
    {
        mRenderable->render(target);
    }
}

//===========================================================================//
void Actor::setScript(script::Object* script)
{
    mScript.reset(script);
}

//===========================================================================//
void Actor::setUpdateFunction(const std::string& name)
{
    mUpdate = mScript->function(name);
}

//===========================================================================//
void Actor::setInitializeFunction(const std::string& name)
{
    mInitialize = mScript->function(name);
}

//===========================================================================//
void Actor::callActivateFunction(const std::string& name)
{
    mScript->function(name)->call();
}

//===========================================================================//
void Actor::setActivatedFunction(const std::string& name,
                                 core::Event<void()>& event)
{
    event = std::bind(&Actor::callActivateFunction, this, name);
}

//===========================================================================//
void Actor::addAnimation(const std::string& name,
                         anim::Animation* anim)
{
    mAnimations[name] = std::unique_ptr<anim::Animation>(anim);
}

//===========================================================================//
void Actor::playAnimation(const std::string& name)
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
const std::string& Actor::getAnimation() const
{
    return mCurrentAnimationName;
}

//===========================================================================//
const std::string& Actor::getName() const
{
    return mName;
}

//===========================================================================//
void Actor::setName(const std::string& name)
{
    mName = name;
}

//===========================================================================//
int32_t Actor::getLayer() const
{
    return mLayer;
}

//===========================================================================//
void Actor::setLayer(int32_t layer)
{
    mLayer = layer;
}

//===========================================================================//
physics::Body<math::Transform2D>& Actor::getPhysics()
{
    return *mBody;
}

//===========================================================================//
const physics::Body<math::Transform2D>& Actor::getPhysics() const
{
    return *mBody;
}

//===========================================================================//
gui::Widget& Actor::getWidget(const std::string& name)
{
    return mGUI->getWidget(name);
}
}
}

#endif
