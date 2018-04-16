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
#include <nyra/editor/SchemaGui.h>
#include <nyra/json/JSON.h>
#include <nyra/core/Path.h>
#include <nyra/gui/qt/Label.h>
#include <nyra/gui/qt/EditBox.h>
#include <nyra/gui/qt/GroupBox.h>
#include <iostream>

namespace
{
//===========================================================================//
const nyra::math::Vector2F SCHEMA_SIZE(400, 800);
const nyra::math::Vector2F DEFAULT_POSITION(16, 16);
const nyra::math::Vector2F OBJECT_SIZE(
        SCHEMA_SIZE.x - DEFAULT_POSITION.x * 2, 800);

//===========================================================================//
class SchemaBuilder
{
public:
    SchemaBuilder(const std::string& name,
                  double yPos,
                  const nyra::mem::Tree<std::string>& schema,
                  nyra::gui::Gui& gui) :
        mOffset(yPos)
    {
        addObject(name, schema, gui);
    }

private:
    void parseSingleObject(const std::string& name,
                           const nyra::mem::Tree<std::string>& schema,
                           nyra::mem::Tree<nyra::gui::Widget>& object)
    {
        if (schema["type"].get() == "string")
        {
            addString(name, schema, object);
        }
        else if (schema["type"].get() == "object")
        {
            addObject(name, schema, object);
        }
    }

    void parseObject(const nyra::mem::Tree<std::string>& schema)
    {
        /*const std::vector<std::string> keys = schema["properties"].keys();
        for (size_t ii = 0; ii < keys.size(); ++ii)
        {
            const auto& map = schema["properties"][keys[ii]];
            if (map["type"].get() == "string")
            {
                mCurrent = &mObject[mName];
                addString(keys[ii], map["default"].get());
            }
        }*/
    }

    void addString(const std::string& name,
                   const nyra::mem::Tree<std::string>& schema,
                   nyra::mem::Tree<nyra::gui::Widget>& object)
    {
        nyra::gui::Widget* widget =
                new nyra::gui::qt::Label(getPosition(),
                                         name);
        object[name] = widget;
        mOffset += widget->getSize().y + 4.0f;

        std::string value;
        if (schema.has("default"))
        {
            value = schema["default"].get();
        }
        widget = new nyra::gui::qt::EditBox(
                nyra::math::Vector2F(256, 48),
                getPosition(),
                value);
        object[name + " edit"] = widget;
        mOffset += widget->getSize().y + 4.0f;
    }

    void addObject(const std::string& name,
                   const nyra::mem::Tree<std::string>& schema,
                   nyra::mem::Tree<nyra::gui::Widget>& object)
    {
        nyra::gui::Widget* widget = new nyra::gui::qt::GroupBox(
                OBJECT_SIZE, getPosition(), name);
        object[name] = widget;

        double origOffset = mOffset;
        mOffset = 48.0f;

        const auto& subTree = schema.has("properties") ? schema["properties"] : schema;
        const auto& keys = subTree.keys();
        for (size_t ii = 0; ii < keys.size(); ++ii)
        {
            parseSingleObject(keys[ii], subTree[keys[ii]], object[name]);
        }

        widget->setSize(nyra::math::Vector2F(widget->getSize().x,
                                             mOffset + 16.0));
        mOffset += origOffset;
    }

    nyra::math::Vector2F getPosition() const
    {
        return nyra::math::Vector2F(DEFAULT_POSITION.x, mOffset);
    }

    float mOffset;
};
}

namespace nyra
{
namespace editor
{
//===========================================================================//
void buildSchema(const std::string& name, gui::Gui& gui)
{
    const std::string pathname =
            core::path::join(core::DATA_PATH, "schema/" + name + ".json");
    json::JSON schema(pathname);

    SchemaBuilder(name, DEFAULT_POSITION.y, schema, gui);
}
}
}
