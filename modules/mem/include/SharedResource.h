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
#ifndef __NYRA_MEM_SHARED_RESOURCE_H__
#define __NYRA_MEM_SHARED_RESOURCE_H__

#include <unordered_map>
#include <memory>
#include <string>

namespace nyra
{
namespace mem
{
/*
 *  \class SharedResource
 *  \brief Creates a resource, primary from disk that can be shared among
 *         objects. The resource is killed when it goes out of scope.
 */
template <typename ResourceT>
class SharedResource
{
public:
    /*
     *  \func Index Operator
     *  \brief Gets or creates a new resource from a key.
     *
     *  \param key Key to find the resource. This is usually a pathname.
     *  \return A shared_ptr to the resource.
     */
    std::shared_ptr<ResourceT> operator[](const std::string& key)
    {
        auto resource = mMap.find(key);
        if (resource != mMap.end() && !resource->second.expired())
        {
            return resource->second.lock();
        }
        else
        {
            std::shared_ptr<ResourceT> shared(new ResourceT(key));
            mMap[key] = shared;
            return shared;
        }
    }

private:
    std::unordered_map<std::string, std::weak_ptr<ResourceT> > mMap;
};
}
}

#endif
