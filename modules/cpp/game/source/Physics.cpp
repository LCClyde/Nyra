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
#include <nyra/game/Physics.h>
#include <nyra/game/Types.h>
#include <nyra/core/Path.h>

namespace nyra
{
namespace game
{
//===========================================================================//
Physics::Physics(math::Transform2D& transform) :
    mLastBody(nullptr),
    mTransform(transform)
{
}

//===========================================================================//
void Physics::addBody(physics::Body2D* body)
{
    mBody.reset(body);
    mLastBody = body;

    mBody->setUserData(mScript.get());
}

//===========================================================================//
void Physics::addTrigger(physics::Trigger2D* body)
{
    mTrigger.reset(body);
    mLastBody = body;
}

//===========================================================================//
void Physics::addCircleCollision(double radius,
                                 const math::Vector2F& offset)
{
    mLastBody->addCircle(radius, offset);
    mCollision.push_back(std::unique_ptr<graphics::Renderable2D>(
            new SpriteT(
            core::path::join(core::DATA_PATH, "textures/" +
                             getTextureName() + "_circle.png"))));
    mCollision.back()->setPosition(offset);
    mCollision.back()->setScale(math::Vector2F(radius / 64.0,
                                               radius / 64.0));
}

//===========================================================================//
void Physics::addBoxCollision(const math::Vector2F& size,
                              const math::Vector2F& offset)
{
    mLastBody->addBox(size, offset);
    mCollision.push_back(std::unique_ptr<graphics::Renderable2D>(
            new SpriteT(
            core::path::join(core::DATA_PATH, "textures/" +
                             getTextureName() + "_box.png"))));
    mCollision.back()->setPosition(offset);
    mCollision.back()->setScale(math::Vector2F(size.x / 128.0,
                                               size.y / 128.0));
}

//===========================================================================//
void Physics::render(graphics::RenderTarget& target)
{
    for (size_t ii = 0; ii < mCollision.size(); ++ii)
    {
        mCollision[ii]->updateTransform(mTransform);
        mCollision[ii]->render(target);
    }
}

//===========================================================================//
void Physics::update()
{
    if (mTrigger.get())
    {
        mTrigger->update();
    }

    if (mBody.get())
    {
        mBody->update();
        mTransform.resetDirty();
    }
}

//===========================================================================//
void Physics::setOnEnter(const std::string& functionName)
{
    mOnEnter = mScript->function(functionName);
    mTrigger->onEnter = std::bind(&Physics::onEnter, this, std::placeholders::_1);
}

//===========================================================================//
void Physics::onEnter(physics::Body2D& body)
{
    mOnEnter->call(VariableT(*static_cast<script::Object*>(
            body.getUserData())));
}

//===========================================================================//
void Physics::setOnExit(const std::string& functionName)
{
    mOnExit = mScript->function(functionName);
    mTrigger->onExit = std::bind(&Physics::onExit, this, std::placeholders::_1);
}

//===========================================================================//
void Physics::onExit(physics::Body2D& body)
{
    mOnExit->call();
}

//===========================================================================//
std::string Physics::getTextureName() const
{
    if (mLastBody == mBody.get())
    {
        return "collision";
    }
    return "trigger";
}
}
}
