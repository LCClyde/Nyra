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
#ifndef __NYRA_CEGUI_GLOBAL_HANDLER_H__
#define __NYRA_CEGUI_GLOBAL_HANDLER_H__

#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>
#include <nyra/pattern/GlobalHandler.h>

namespace nyra
{
namespace cegui
{
/*
 *  \class GlobalHandler
 *  \brief Handles the CEGUI global init and shutdown commands. All CEGUI
 *         classes should add a GlobalDependency to this class.
 */
class GlobalHandler : public pattern::GlobalHandler
{
public:
    /*
     *  \func Constructor
     *  \brief Creates an uninitialized CEGUI Global Handler object.
     */
    GlobalHandler();

    /*
     *  \func get
     *  \brief Retrieves the CEGUI object,
     *
     *  \return The CEGUI object or nullptr if it has not been initialized
     */
    CEGUI::Renderer* get()
    {
        return mRenderer;
    }

    /*
     *  \func get
     *  \brief Retrieves the CEGUI object,
     *
     *  \return The CEGUI object or nullptr if it has not been initialized
     */
    const CEGUI::Renderer* get() const
    {
        return mRenderer;
    }

private:
    void initializeGlobal() override;

    void shutdownGlobal() override;

    friend std::ostream& operator<<(std::ostream& os,
                                    const GlobalHandler& app);

    CEGUI::OpenGLRenderer* mRenderer;
};
}
}

#endif
