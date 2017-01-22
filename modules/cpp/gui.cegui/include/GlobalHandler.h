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
#ifndef __NYRA_GUI_CEGUI_GLOBAL_HANDLER_H__
#define __NYRA_GUI_CEGUI_GLOBAL_HANDLER_H__

#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>
#include <nyra/mem/GlobalHandler.h>

namespace nyra
{
namespace gui
{
namespace cegui
{
/*
 *  \class GlobalHandler
 *  \brief Handles the CEGUI global init and shutdown commands. All CEGUI
 *         classes should add a GlobalDependency to this class.
 */
class GlobalHandler : public mem::GlobalHandler
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an uninitialized CEGUI Global Handler object.
     */
    GlobalHandler();

    /*
     *  \func getRenderer
     *  \brief Retrieves the CEGUI object,
     *
     *  \return The CEGUI object or nullptr if it has not been initialized
     */
    CEGUI::Renderer* getRenderer() const
    {
        return mRenderer;
    }

    /*
     *  \func getWindowManager
     *  \brief Retrieves the CEGUI object,
     *
     *  \return The CEGUI object or nullptr if it has not been initialized
     */
    CEGUI::WindowManager* getWindowManager() const
    {
        return mWindowManager;
    }

    /*
     *  \func getRoot
     *  \brief Retrieves the CEGUI object,
     *
     *  \return The CEGUI object or nullptr if it has not been initialized
     */
    CEGUI::Window* getRoot() const
    {
        return mRoot;
    }

    /*
     *  \func getSystem
     *  \brief Retrieves the CEGUI object,
     *
     *  \return The CEGUI object or nullptr if it has not been initialized
     */
    CEGUI::System* getSystem() const
    {
        return mSystem;
    }

    /*
     *  \func createWidget
     *  \brief Creates a CEGUI Window object.
     *
     *  \param type The type that represents the widget in the XML.
     *  \return The created object.
     */
    CEGUI::Window& createWidget(const std::string& type) const;

private:
    void initializeGlobal() override;

    void shutdownGlobal() override;

    friend std::ostream& operator<<(std::ostream& os,
                                    const GlobalHandler& app);

    CEGUI::OpenGLRenderer* mRenderer;
    CEGUI::WindowManager* mWindowManager;
    CEGUI::Window* mRoot;
    CEGUI::System* mSystem;
    std::string mScheme;
};
}
}
}

#endif
