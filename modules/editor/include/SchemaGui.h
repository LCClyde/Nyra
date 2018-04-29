/*
 * Copyright (c) 2018 Clyde Stanfield
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
#ifndef __NYRA_EDITOR_SCHEMA_GUI_H__
#define __NYRA_EDITOR_SCHEMA_GUI_H__

#include <string>
#include <nyra/gui/Gui.h>
#include <nyra/json/JSON.h>
#include <nyra/core/String.h>

namespace nyra
{
namespace editor
{
class SchemaGui
{
public:
    SchemaGui(const std::string& name,
              double yPos,
              double width,
              core::Event<void()> onValueChanged,
              gui::Gui& gui);

    //=======================================================================//
    void onValueChangedImpl(mem::Tree<std::string>* schema,
                            gui::Widget* object);

private:
    class BuildOptions
    {
    public:
        //===================================================================//
        BuildOptions(const std::string& name,
                     const mem::Tree<std::string>& schema,
                     mem::Tree<gui::Widget>& object,
                     mem::Tree<std::string>& serial);

        //===================================================================//
        BuildOptions(const std::string& name,
                     const std::string& title,
                     size_t index,
                     size_t indices,
                     const mem::Tree<std::string>& schema,
                     mem::Tree<gui::Widget>& object,
                     mem::Tree<std::string>& serial);

        //===================================================================//
        std::string getType() const;

        //===================================================================//
        void addWidget(const std::string& suffix,
                       gui::Widget* widget,
                       bool addToSchema);

        //===================================================================//
        void addWidget(gui::Widget* widget,
                       bool addToSchema);

        //===================================================================//
        template <typename T>
        T getDefault(const T& fallback) const
        {
            return getSchemaValue<T>("default", fallback);
        }

        //===================================================================//
        template <typename T>
        T getSchemaValue(const std::string& schemaName,
                         const T& fallback) const
        {
            if (!schema.has(schemaName))
            {
                return fallback;
            }
            return core::str::toType<T>(schema[schemaName].get());
        }

        //===================================================================//
        gui::Widget& getWidget() const
        {
            return *mWidget;
        }

        //===================================================================//
        const std::string name;
        const std::string title;
        const size_t index;
        const size_t indices;
        const mem::Tree<std::string>& schema;
        mem::Tree<gui::Widget>& object;
        mem::Tree<std::string>& serial;

    private:
        gui::Widget* mWidget;
    };
    //=======================================================================//
    void parseSingleObject(BuildOptions& input);

    //=======================================================================//
    void addLabel(BuildOptions& input);

    //=======================================================================//
    void addString(BuildOptions& input);

    //=======================================================================//
    void addNumber(BuildOptions& input);

    //=======================================================================//
    void addInteger(BuildOptions& input);

    //=======================================================================//
    void addObject(BuildOptions& input);

    //=======================================================================//
    void addVector2(BuildOptions& input);

    //=======================================================================//
    nyra::math::Vector2F getPosition(const BuildOptions& options) const;

    //=======================================================================//
    double getWidth(const BuildOptions& options) const;

    void addChangeEvent(BuildOptions& input);

    float mOffset;
    double mWindowWidth;
    size_t mTab;
    const nyra::core::Event<void()>& mOnValueChanged;
    json::JSON mSerial;
};
}
}

#endif
