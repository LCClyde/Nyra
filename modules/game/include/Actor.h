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
#include <nyra/script/Function.h>
#include <nyra/anim/Frame.h>
#include <nyra/game/Types.h>
#include <nyra/game/NavMesh.h>
#include <nyra/game/Gui.h>
#include <nyra/core/Event.h>
#include <nyra/game/Physics.h>
#include <nyra/game/Gui.h>

namespace nyra
{
namespace game
{
/*
 *  \class Actor
 *  \brief Generic class for anything that interacts with the game
 */
class Actor : public graphics::Renderable2D
{
public:
    enum Type
    {
        OTHER,
        SPRITE,
        TILEMAP,
        CAMERA,
        GUI
    };

    /*
     *  \func Actor
     *  \brief Creates a black actor.
     */
    Actor();

    /*
     *  \func update
     *  \brief Updates the actor object
     *
     *  \param delta The time in seconds since the last update
     */
    void update(double delta);

    /*
     *  \func initialize
     *  \brief Called after the actor has been initialized
     */
    void initialize();

    /*
     *  \func addNavMesh
     *  \brief Adds a nav mesh to the actor
     *
     *  \param mesh The initialized nav mesh
     */
    void addNavMesh(NavMesh* mesh);
    /*
     *  \func getNavMesh
     *  \brief Returns a nav mesh. This will segfault if the actor does not
     *         have a valid nav mesh.
     *
     *  \return The nav mesh
     */
    const NavMesh& getNavMesh() const;

    /*
     *  \func getRenderable
     *  \brief Gets a renderable
     *
     *  \return The renderable
     */
    graphics::Renderable2D& getRenderable();

    /*
     *  \func getRenderable
     *  \brief Gets a renderable
     *
     *  \return The renderable
     */
    const graphics::Renderable2D& getRenderable() const;

    /*
     *  \func getScript
     *  \brief Gets the script object
     *
     *  \return The script object
     */
    const nyra::script::Object& getScript() const
    {
        return *mScript;
    }

    nyra::script::Object& getScript()
    {
        return *mScript;
    }

    /*
     *  \func hasScript
     *  \brief Does the actor have a script?
     *
     *  \return True if this has a script
     */
    bool hasScript() const;

    /*
     *  \func addGUI
     *  \brief Function to add a gui object
     *
     *  \param gui The GUI to add. This takes ownership
     */
    void addGUI(Gui* gui);

    void addSprite(graphics::Sprite* sprite)
    {
        addRenderable(sprite);
        mType = SPRITE;
    }

    void addTileMap(TileMapT* tilemap)
    {
        addRenderable(tilemap);
        mType = TILEMAP;
    }

    void addCamera(graphics::Camera2D* camera)
    {
        addRenderable(camera);
        mType = CAMERA;
    }

    /*
     *  \func updateTransform
     *  \brief Updates the spatial transform of the actor
     */
    void updateTransform();

    /*
     *  \func render
     *  \brief Renders the actor to the screen
     *
     *  \param target The target to render to
     */
    void render(graphics::RenderTarget& target) override;
    /*
     *  \func setScript
     *  \brief Sets the script that is used to control the actor
     *
     *  \param script The script object
     */
    void setScript(script::Object* script);

    /*
     *  \func setUpdateFunction
     *  \brief Sets the per frame update function
     *
     *  \param name The name of the function
     */
    void setUpdateFunction(const std::string& name);

    /*
     *  \func setInitializeFunction
     *  \brief Sets the function that occurs after initialization
     *
     *  \param name The name of the function
     */
    void setInitializeFunction(const std::string& name);

    void callActivateFunction(const std::string& name);

    void setActivatedFunction(const std::string& name,
                               core::Event<void()>& event);

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
                      anim::Animation* anim);

    /*
     *  \func playAnimation
     *  \brief Plays an animation. The animation must have been added
     *         with addAnimation first.
     *
     *  \name The name of the animation
     */
    void playAnimation(const std::string& name);

    /*
     *  \func getAnimation
     *  \brief Gets the currently playing animation
     *
     *  \return The name of the playing animation or an empty string
     *          if nothing is playing.
     */
    const std::string& getAnimation() const;

    /*
     *  \func getName
     *  \brief Gets the actor unique name
     *
     *  \return The actor name
     */
    const std::string& getName() const;

    /*
     *  \func setName
     *  \brief Sets the actor name. This should only be called internally
     *
     *  \param name The name. This must be unique.
     */
    void setName(const std::string& name);

    /*
     *  \func getLayer
     *  \brief Gets the render layer
     *
     *  \return The layer
     */
    int32_t getLayer() const;

    /*
     *  \func setLayer
     *  \brief Sets the render layer
     *
     *  \param layer The desired layer
     */
    void setLayer(int32_t layer);

    gui::Widget& getWidget(const std::string& name);

    Type getType() const
    {
        return mType;
    }

    void setType(Type type)
    {
        mType = type;
    }

    Physics& getPhysics()
    {
        return mPhysics;
    }

    const Physics& getPhysics() const
    {
        return mPhysics;
    }

private:
    /*
     *  \func addRenderable
     *  \brief Adds a new renderable to the actor
     *
     *  \param renderable The object to add
     */
    void addRenderable(graphics::Renderable2D* renderable);

    std::shared_ptr<script::Object> mScript;
    std::unique_ptr<NavMesh> mNavMesh;

    script::FunctionPtr mUpdate;
    script::FunctionPtr mInitialize;

    std::unique_ptr<graphics::Renderable2D> mRenderable;
    std::unordered_map<std::string,
            std::unique_ptr<anim::Animation>> mAnimations;
    anim::Animation* mCurrentAnimation;
    Gui* mGUI;
    Physics mPhysics;

    std::string mCurrentAnimationName;
    std::string mName;
    int32_t mLayer;
    bool mHasInit;
    Type mType;
};
}
}

#endif
