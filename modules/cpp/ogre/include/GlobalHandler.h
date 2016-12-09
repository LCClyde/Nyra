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
#ifndef __NYRA_OGRE_GLOBAL_HANDLER_H__
#define __NYRA_OGRE_GLOBAL_HANDLER_H__

#include <memory>
#include <OgreRoot.h>
#include <nyra/pattern/GlobalHandler.h>

namespace nyra
{
namespace ogre
{
/*
 *  \class GlobalHandler
 *  \brief Handles the SDL global init and shutdown commands. All SDL classes
 *         should add a GlobalDependency to this class.
 */
class GlobalHandler : public pattern::GlobalHandler
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up a default GlobalHandler.
     */
    GlobalHandler();

    /*
     *  \func getRoot
     *  \brief Retrieves the Ogre Root object,
     *
     *  \return The Ogre::Root object or nullptr if it has not been initialized
     */
    Ogre::Root* getRoot() const
    {
        return mRoot.get();
    }

    /*
     *  \func getSceneManager
     *  \brief Retrieves the Ogre Scene Manager.
     *
     *  \return The Ogre::SceneManager object.
     */
    Ogre::SceneManager* getSceneManager() const
    {
        return mSceneManager;
    }

private:
    void initializeGlobal() override;

    void shutdownGlobal() override;

    friend std::ostream& operator<<(std::ostream& os,
                                    const GlobalHandler& app);

    std::unique_ptr<Ogre::Root> mRoot;
    Ogre::SceneManager* mSceneManager;
};
}
}

#endif
