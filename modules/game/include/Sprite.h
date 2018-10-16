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
#ifndef __NYRA_GAME_SPRITE_H__
#define __NYRA_GAME_SPRITE_H__

#include <nyra/game/Types.h>
#include <nyra/json/JSON.h>

namespace nyra
{
namespace game
{
/*
 *  \class Sprite
 *  \brief Holds onto a sprite object that knows how to serialize to JSON
 *         and includes all necessary metadata for game development.
 */
class Sprite : public graphics::Renderable2D
{
public:
    /*
     *  \func Constructor
     *  \breif Creates an empty sprite.
     */
    Sprite() = default;

    /*
     *  \func Constructor
     *  \brief Creates a Sprite object.
     *
     *  \param filename The texture filename
     *  \param pivot The pivot offset
     *  \param frames The number of x/y frames
     */
    Sprite(const std::string& filename,
           const math::Vector2F& pivot,
           const math::Vector2U& frames);

    /*
     *  \func initialize
     *  \brief Resets a sprite.
     *
     *  \param filename The texture filename
     *  \param pivot The pivot offset
     *  \param frames The number of x/y frames
     */
    void initialize(const std::string& filename,
                    const math::Vector2F& pivot,
                    const math::Vector2U& frames);

    /*
     *  \func initialize
     *  \brief Resets a sprite.
     *
     *  \param tree The json tree.
     */
    void initialize(const json::JSON& tree);

    /*
     *  \func getFilename
     *  \brief Gets the texture filename.
     *
     *  \return The filename
     */
    const std::string& getFilename() const
    {
        return mFilename;
    }

    /*
     *  \func getPivot
     *  \brief Gets the sprite pivot point
     *
     *  \return The pivot point
     */
    const math::Vector2F getPivot() const
    {
        return mSprite.getPivot();
    }

    /*
     *  \func getFrames
     *  \brief Gets the sprite frames
     *
     *  \return The sprite frames.
     */
    const math::Vector2U getFrames() const
    {
        return mFrames;
    }

    /*
     *  \func render
     *  \brief Renders the actor to the screen
     *
     *  \param target The target to render to
     */
    void render(graphics::RenderTarget& target) override;

    /*
     *  \func updateTransform
     *  \brief Updates the underlying matrix
     *
     *  \param parent The parent transform
     */
    void updateTransform(const math::Transform2D& parent) override;

private:
    std::string mFilename;
    math::Vector2U mFrames;
    SpriteT mSprite;
};
}

namespace core
{
/*
 *  \func write
 *  \brief Serializes Sprite to disk
 *
 *  \param data The data object to serialize
 *  \param pathname The location to write to
 *  \param type The archive type is ignored. It will always write JSON.
 */
template <>
void write<game::Sprite>(const game::Sprite& data,
                         const std::string& pathname,
                         core::ArchiveType type);

/*
 *  \func read
 *  \brief Deserializes a Sprite object from disk.
 *
 *  \param pathname The file to read
 *  \param data[OUTPUT] The data to load into
 *  \param type The archive type is ignored. It will always read JSON.
 */
template <>
void read<game::Sprite>(const std::string& pathname,
                        game::Sprite& data,
                        core::ArchiveType type);
}
}

#endif
