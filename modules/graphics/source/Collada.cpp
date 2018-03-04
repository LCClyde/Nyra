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
#include <iostream>
#include <nyra/core/String.h>
#include <nyra/graphics/Collada.h>

namespace
{
struct Source
{
    Source() = default;

    Source(const nyra::mem::Tree<nyra::xml::Element>& floatArray,
           const nyra::mem::Tree<nyra::xml::Element>& accessor)
    {
        data = nyra::core::str::split(floatArray.get().text);
        id = accessor.get().attributes.at("source");

        for (size_t ii = 0; ii < accessor["param"].loopSize(); ++ii)
        {
            params.push_back(
                    accessor["param"][ii].get().attributes.at("name"));
        }

    }

    std::vector<std::string> data;
    std::vector<std::string> params;
    std::string id;
};

struct Input
{
public:
    Input(const nyra::mem::Tree<nyra::xml::Element>& input)
    {
        semantic = input.get().attributes.at("semantic");
        source = input.get().attributes.at("source");
        offset = nyra::core::str::toType<size_t>(
                input.get().attributes.at("offset"));
    }

    std::string semantic;
    std::string source;
    size_t offset;
};
}

namespace nyra
{
namespace graphics
{
Collada::Collada(const std::string& pathname)
{
    xml::XML collada = core::read<xml::XML>(pathname);

    const mem::Tree<xml::Element>& mesh =
            collada["COLLADA"]
                   ["library_geometries"]
                   ["geometry"]
                   ["mesh"];

    initializeVerts(mesh);
}

void Collada::initializeVerts(const mem::Tree<xml::Element>& tree)
{
    const mem::Tree<xml::Element>& source = tree["source"];
    std::unordered_map<std::string, Source> sources;
    for (size_t ii = 0; ii < source.loopSize(); ++ii)
    {
        sources["#" + source[ii].get().attributes.at("id")] = Source(
                source[ii]["float_array"],
                source[ii]["technique_common"]["accessor"]);
    }

    // Save off the vertices
    const Source& sourceVerts =
            sources[tree["vertices"]["input"].get().attributes.at("source")];

    for (size_t ii = 0; ii < sourceVerts.data.size(); ii += 3)
    {
        mVerts.push_back(math::Vector3F(
                core::str::toType<float>(sourceVerts.data[ii]),
                core::str::toType<float>(sourceVerts.data[ii + 1]),
                core::str::toType<float>(sourceVerts.data[ii + 2])));
    }
    std::vector<Input> inputs;

    for (size_t ii = 0; ii < tree["triangles"]["input"].size(); ++ii)
    {
        inputs.push_back(Input(tree["triangles"]["input"][ii]));
    }

    std::vector<std::string> triangles =
            core::str::split(tree["triangles"]["p"].get().text);

    size_t subIndex = 0;
    for (const std::string& index : triangles)
    {
        if (inputs[subIndex].semantic == "VERTEX")
        {
            mIndices.push_back(core::str::toType<size_t>(index));
        }

        ++subIndex;
        subIndex %= inputs.size();
    }
}
}
}
