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
#include <nyra/core/Path.h>
#include <nyra/gui/qt/Label.h>
#include <nyra/gui/qt/EditBox.h>
#include <nyra/gui/qt/Spinner.h>
#include <nyra/gui/qt/GroupBox.h>
#include <nyra/gui/qt/ComboBox.h>
#include <iostream>

namespace
{
//===========================================================================//
const static double OFFSET = 16.0;
const std::string NONE = "<none>";
}

namespace nyra
{
namespace editor
{
//===========================================================================//
SchemaGui::BuildOptions::BuildOptions(const std::string& name,
                                      const mem::Tree<std::string>& schema,
                                      mem::Tree<gui::Widget>& object,
                                      mem::Tree<std::string>& serial) :
    BuildOptions(name, name, 0, 1, schema, object, serial)
{
}

//===========================================================================//
SchemaGui::BuildOptions::BuildOptions(const std::string& name,
                                      const std::string& title,
                                      size_t index,
                                      size_t indices,
                                      const mem::Tree<std::string>& schema,
                                      mem::Tree<gui::Widget>& object,
                                      mem::Tree<std::string>& serial) :
    name(name),
    title(title),
    index(index),
    indices(indices),
    schema(schema),
    object(object),
    serial(serial),
    mWidget(nullptr)
{
    if (!serial.valid())
    {
        serial = "";
    }
}

//===========================================================================//
std::string SchemaGui::BuildOptions::getType() const
{
    if (!schema.has("type"))
    {
        return "";
    }

    return schema["type"].get();
}

//===========================================================================//
void SchemaGui::BuildOptions::addWidget(const std::string& suffix,
                                        gui::Widget* widget,
                                        bool addToSchema)
{
    mWidget = widget;
    if (suffix.empty())
    {
        object[name] = widget;
    }
    else
    {
        object[name + " " + suffix] = widget;
    }

    if (addToSchema)
    {
        const std::string text = widget->getText();
        if (text == NONE)
        {
            serial = "";
        }
        else
        {
            serial = widget->getText();
        }
    }
}

//===========================================================================//
void SchemaGui::BuildOptions::addWidget(gui::Widget* widget,
                                        bool addToSchema)
{
    addWidget("", widget, addToSchema);
}

//===========================================================================//
SchemaGui::SchemaGui(const std::string& name,
                     double yPos,
                     double width,
                     core::Event<void(const json::JSON&)> onValueChanged,
                     gui::Gui& gui) :
    mOffset(yPos + OFFSET),
    mWindowWidth(width),
    mTab(1),
    mOnValueChanged(onValueChanged)
{
    const std::string pathname =
            core::path::join(core::DATA_PATH, "schema/" + name + ".json");
    json::JSON schema(pathname);

    BuildOptions input(name, schema, gui, mSerial);
    input.serial = "";
    addObject(input);
}

//=======================================================================//
void SchemaGui::parseSingleObject(BuildOptions& input)
{
    const std::string type = input.getType();
    if (type == "string")
    {
        addString(input);
    }
    else if (type == "number")
    {
        addNumber(input);
    }
    else if (type == "integer")
    {
        addInteger(input);
    }
    else if (type == "object")
    {
        if (input.schema.has("properties") &&
            input.schema["properties"].has("x") &&
            input.schema["properties"].has("y"))
        {
            BuildOptions output(input.name,
                                input.schema["properties"],
                                input.object,
                                input.serial);
            addVector2(output);
        }
        else
        {
            BuildOptions output(input.name,
                                input.schema,
                                input.object,
                                input.serial);
            addObject(input);
        }
    }
}

//=======================================================================//
void SchemaGui::addLabel(BuildOptions& input)
{
    gui::Widget* widget =
            new gui::qt::Label(
                    getPosition(input), input.title);
    input.addWidget(widget, false);
    mOffset += widget->getSize().y + 4.0f;
}

//=======================================================================//
void SchemaGui::addString(BuildOptions& input)
{
    addLabel(input);

    const std::string value = input.getDefault<std::string>("");
    const std::string directory =
            input.getSchemaValue<std::string>("directory", "");

    gui::Widget* widget = nullptr;
    if (directory.empty())
    {
        widget = new gui::qt::EditBox(
                math::Vector2F(getWidth(input), 48),
                getPosition(input),
                value);
    }
    else
    {
        const std::string dirPath =
                core::path::join(core::DATA_PATH, directory);
        std::vector<std::string> items =
                core::path::listDirectory(dirPath);
        items.push_back("<none>");
        std::sort(items.begin(), items.end());
        widget = new gui::qt::ComboBox(
                math::Vector2F(getWidth(input), 48),
                getPosition(input),
                items);
    }
    input.addWidget("_edit", widget, true);
    mOffset += widget->getSize().y + 4.0f;
    addChangeEvent(input);
}

//=======================================================================//
void SchemaGui::addNumber(BuildOptions& input)
{
    addLabel(input);

    const double value = input.getDefault(0.0);
    const double min = input.getSchemaValue(
            "minimum", -std::numeric_limits<float>::max());
    const double max = input.getSchemaValue(
            "maximum", std::numeric_limits<float>::max());
    const double inc = input.getSchemaValue("increment", 0.1);

    gui::Widget* widget = new gui::qt::Spinner(
            math::Vector2F(getWidth(input), 48),
            getPosition(input),
            gui::qt::Spinner::DOUBLE,
            value, min, max, inc);

    input.addWidget("_num_spinner", widget, true);
    mOffset += widget->getSize().y + 4.0f;
    addChangeEvent(input);
}

//=======================================================================//
void SchemaGui::addInteger(BuildOptions& input)
{
    addLabel(input);

    const double value = input.getDefault(0);
    const double min = input.getSchemaValue(
            "minimum", -std::numeric_limits<int32_t>::min());
    const double max = input.getSchemaValue(
            "maximum", std::numeric_limits<int32_t>::max());
    const double inc = input.getSchemaValue("increment", 1.0);

    gui::Widget* widget = new gui::qt::Spinner(
            math::Vector2F(getWidth(input), 48),
            getPosition(input),
            gui::qt::Spinner::INTEGER,
            value, min, max, inc);

    input.addWidget("_int_spinner", widget, true);
    mOffset += widget->getSize().y + 4.0f;
    addChangeEvent(input);
}

//=======================================================================//
void SchemaGui::addObject(BuildOptions& input)
{
    gui::Widget* widget = new gui::qt::GroupBox(
            math::Vector2F(getWidth(input), 1.0),
            getPosition(input), input.title);
    input.addWidget(widget, false);

    double origOffset = mOffset;
    mOffset = 48.0f;
    mTab++;

    const auto& subTree = input.schema.has("properties") ?
            input.schema["properties"] : input.schema;
    const auto& keys = subTree.keys();
    for (size_t ii = 0; ii < keys.size(); ++ii)
    {
        BuildOptions output(keys[ii], subTree[keys[ii]],
                            input.object[input.name],
                            input.serial[keys[ii]]);
        parseSingleObject(output);
    }

    widget->setSize(math::Vector2F(widget->getSize().x,
                                         mOffset + 16.0));
    mOffset += origOffset + 32.0;
    mTab--;
}

//=======================================================================//
void SchemaGui::addVector2(BuildOptions& input)
{
    const double offset = mOffset;
    BuildOptions outputX("x",
                         input.name + " x",
                         0, 2,
                         input.schema["x"],
                         input.object,
                         input.serial["x"]);
    parseSingleObject(outputX);

    mOffset = offset;
    BuildOptions outputY("y",
                         input.name + " y",
                         1, 2,
                         input.schema["y"],
                         input.object,
                         input.serial["y"]);
    parseSingleObject(outputY);
}

//=======================================================================//
math::Vector2F SchemaGui::getPosition(const BuildOptions& options) const
{
    const double width = getWidth(options);
    return math::Vector2F(
            OFFSET + (width * options.index) + (options.index * OFFSET),
            mOffset);
}

//=======================================================================//
double SchemaGui::getWidth(const BuildOptions& options) const
{
    const size_t spaces = options.indices - 1;
    return (mWindowWidth -
           (mTab * OFFSET * 2) -
           (spaces * OFFSET)) / options.indices;
}

//=======================================================================//
void SchemaGui::addChangeEvent(BuildOptions& options)
{
    options.getWidget().onValueChanged = std::bind(
            &SchemaGui::onValueChangedImpl,
            this, &options.serial, &options.getWidget());
}

//=======================================================================//
void SchemaGui::onValueChangedImpl(mem::Tree<std::string>* activeJson,
                                   gui::Widget* object)
{
    (*activeJson) = object->getText();
    mOnValueChanged(mSerial);
}
}
}
