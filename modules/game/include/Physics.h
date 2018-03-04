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
#ifndef __NYRA_GAME_PHYSICS_H__
#define __NYRA_GAME_PHSYICS_H__

#include <memory>
#include <nyra/physics/Body.h>
#include <nyra/physics/Trigger.h>
#include <nyra/graphics/RenderTarget.h>
#include <nyra/graphics/Renderable.h>
#include <nyra/script/Object.h>
#include <nyra/script/Function.h>

namespace nyra
{
namespace game
{
class Physics
{
public:
    Physics(math::Transform2D& transform);

    void addCircleCollision(double radius,
                            const math::Vector2F& offset);

    void addBoxCollision(const math::Vector2F& size,
                         const math::Vector2F& offset);

    void addBody(physics::Body2D* body);

    void addTrigger(physics::Trigger2D* trigger);

    void render(graphics::RenderTarget& target);

    void update();

    math::Vector2F getVelocity() const
    {
        return mBody->getVelocity();
    }

    void setVelocity(const math::Vector2F& velocity)
    {
        mBody->setVelocity(velocity);
    }

    void setOnEnter(const std::string& functionName);

    void onEnter(physics::Body2D& body);

    void setOnExit(const std::string& functionName);

    void onExit(physics::Body2D& body);

    void setScript(const std::shared_ptr<script::Object>& script)
    {
        mScript = script;
    }

private:
    std::string getTextureName() const;

    std::unique_ptr<physics::Body2D> mBody;
    std::unique_ptr<physics::Trigger2D> mTrigger;
    physics::Body2D* mLastBody;
    std::vector<std::unique_ptr<graphics::Renderable2D>> mCollision;
    math::Transform2D& mTransform;
    std::shared_ptr<script::Object> mScript;
    script::FunctionPtr mOnEnter;
    script::FunctionPtr mOnExit;
};
}
}

#endif
