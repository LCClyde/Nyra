/*
 * Copyright (c) 2016 Clyde Stanfield
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
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
#ifndef __NYRA_PATTERN_GLOBAL_UPDATE_H__
#define __NYRA_PATTERN_GLOBAL_UPDATE_H__

#include <unordered_set>
#include <ostream>

namespace nyra
{
namespace pattern
{
/*
 *  \class GlobalUpdate
 *  \brief Used to manage updates of classes that have an underlying update
 *         that targets all objects not just one. For example a Window update
 *         that is actually an updateAllWindows can be abstracted away with
 *         this.
 *         The common update looks for loops and updates whenever a new loop
 *         is encountered. As a result if you need fine grain control this
 *         will have negative results.
 *         An archive function is not necessary for this as it holds onto
 *         pointers and which will change after an archive. Instead, after
 *         an archive, updates are reset.
 */
class GlobalUpdate
{
public:
    /*
     *  \func tryUpdate
     *  \brief See if an update should be performed. If a loop is encountered,
     *         then the global update should be called.
     *
     *  \param data The pointer representing the wrapper object.
     *  \return true if you should perform an update.
     */
    bool tryUpdate(const void* data);

private:
    friend std::ostream& operator<<(std::ostream& os,
                                    const GlobalUpdate& update);

    std::unordered_set<const void*> mData;
};
}
}

#endif
