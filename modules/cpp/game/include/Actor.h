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
#ifndef __NYRA_GAME_ACTOR_H__
#define __NYRA_GAME_ACTOR_H__

#include <memory>
#include <vector>
#include <nyra/json/JSON.h>
#include <nyra/core/String.h>
#include <nyra/mem/Buffer2D.h>
#include <nyra/graphics/TileMap.h>
#include <nyra/core/Path.h>
#include <nyra/script/Function.h>
#include <nyra/anim/Frame.h>
#include <nyra/game/NavMesh.h>

namespace nyra
{
namespace game
{
/*
 *  \class Actor
 *  \brief Generic class for anything that interacts with the game
 *
 *  \tparam GameT The game type
 */
template <typename GameT>
class Actor : public GameT::Graphics::Renderable
{
private:
    typedef typename GameT::Graphics::RenderTarget RenderTargetT;
    typedef typename GameT::Graphics::Renderable RenderableT;
    typedef typename GameT::Graphics::Transform TransformT;
    typedef typename GameT::Graphics::Sprite SpriteT;
    typedef std::vector<std::unique_ptr<RenderableT>> RenderList;
    typedef typename GameT::Script::Object ObjectT;
    typedef typename GameT::Script::Variable VariableT;
    typedef typename GameT::Graphics::Vector VectorT;

public:
    /*
     *  \func Actor
     *  \brief Creates a black actor.
     */
    Actor() :
        mCurrentAnimation(nullptr)
    {
    }

    /*
     *  \func update
     *  \brief Updates the actor object
     *
     *  \param delta The time in seconds since the last update
     */
    void update(float delta)
    {
        if (mScript.get() && mUpdate.get())
        {
            mUpdate->call(VariableT(delta));
        }

        if (mCurrentAnimation)
        {
            mCurrentAnimation->update(delta);
        }
    }

    /*
     *  \func initialize
     *  \brief Called after the actor has been initialized
     */
    void initialize()
    {
        if (mScript.get() && mInitialize.get())
        {
            mInitialize->call();
        }
    }

    /*
     *  \func addRenderable
     *  \brief Adds a new renderable to the actor
     *
     *  \param renderable The object to add
     */
    void addRenderable(RenderableT* renderable)
    {
        mRenderable.reset(renderable);
    }

    /*
     *  \func getRenderable
     *  \brief Gets a renderable by name. This only works if the renderable
     *         has been setup by name.
     *
     *  \param name The name of the renderable
     *  \return The renderable
     */
    RenderableT& getRenderable()
    {
        return *mRenderable;
    }

    const RenderableT& getRenderable() const
    {
        return *mRenderable;
    }

    /*
     *  \func getScript
     *  \brief Gets the script object
     *
     *  \return The script objectt
     */
    const  nyra::script::Object& getScript() const
    {
        return *mScript;
    }

    /*
     *  \func updateTransform
     *  \brief Updates the spatial transform of the actor
     */
    void updateTransform()
    {
        static TransformT transform;
        TransformT::updateTransform(transform);
        if (mRenderable.get())
        {
            mRenderable->updateTransform(*this);
        }
    }

    /*
     *  \func render
     *  \brief Renders the actor to the screen
     *
     *  \param target The target to render to
     */
    void render(graphics::RenderTarget& target) override
    {
        if (mRenderable.get())
        {
            mRenderable->render(target);
        }
    }

    /*
     *  \func setScript
     *  \brief Sets the script that is used to control the actor
     *
     *  \param script The script object
     */
    void setScript(ObjectT* script)
    {
        mScript.reset(script);
    }

    /*
     *  \func setUpdateFunction
     *  \brief Sets the per frame update function
     *
     *  \param name The name of the function
     */
    void setUpdateFunction(const std::string& name)
    {
        mUpdate = mScript->function("update");
    }

    /*
     *  \func setInitializeFunction
     *  \brief Sets the function that occurs after initialization
     *
     *  \param name The name of the function
     */
    void setInitializeFunction(const std::string& name)
    {
        mInitialize = mScript->function("initialize");
    }

    /*
     *  \func addAnimation
     *  \brief Adds a new animation to the actor. The animation is not
     *         played, it is simply stored in a map that can be looked
     *         up later.
     *
     *  \param name The name of the animation
     *  \param anim The animation object. The actor will take ownership.
     */
    void addAnimation(const std::string& name,
                      anim::Animation* anim)
    {
        mAnimations[name] = std::unique_ptr<anim::Animation>(anim);
    }

    /*
     *  \func playAnimation
     *  \brief Plays an animation. The animation must have been added
     *         with addAnimation first.
     *
     *  \name The name of the animation
     */
    void playAnimation(const std::string& name)
    {
        anim::Animation* newAnim =  mAnimations.at(name).get();

        if (newAnim != mCurrentAnimation)
        {
            mCurrentAnimation = newAnim;
            mCurrentAnimation->reset();
            mCurrentAnimationName = name;
        }
    }

    /*
     *  \func getAnimation
     *  \brief Gets the currently playing animation
     *
     *  \return The name of the playing animation or an empty string
     *          if nothing is playing.
     */
    const std::string& getAnimation() const
    {
        return mCurrentAnimationName;
    }

    /*
     *  \func getName
     *  \brief Gets the actor unique name
     *
     *  \return The actor name
     */
    const std::string& getName() const
    {
        return mName;
    }

    /*
     *  \func setName
     *  \brief Sets the actor name. This should only be called internally
     *
     *  \param name The name. This must be unique.
     */
    void setName(const std::string& name)
    {
        mName = name;
    }

private:
    RenderList mRenderables;
    std::unique_ptr<ObjectT> mScript;

    script::FunctionPtr mUpdate;
    script::FunctionPtr mInitialize;

    std::unique_ptr<RenderableT> mRenderable;
    std::unordered_map<std::string, std::unique_ptr<anim::Animation>> mAnimations;
    anim::Animation* mCurrentAnimation;
    std::string mCurrentAnimationName;
    std::string mName;
};
}
}

#endif
