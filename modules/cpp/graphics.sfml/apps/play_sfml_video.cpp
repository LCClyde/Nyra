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
#include <iostream>
#include <exception>
#include <nyra/win/sfml/Window.h>
#include <nyra/graphics/sfml/RenderTarget.h>
#include <nyra/graphics/sfml/Video.h>

using namespace nyra;

int main(int argc, char** argv)
{
    try
    {
        if (argc < 2)
        {
            std::cout << "Usage: " << argv[0] << " <Video>\n";
            return 1;
        }

        const math::Vector2U windowSize(1280, 720);

        win::sfml::Window window("Run Video", windowSize);
        graphics::sfml::RenderTarget target(window);
        graphics::sfml::Video video(argv[1]);
        video.setPosition(windowSize / 2);
        float scale = std::min(
                static_cast<float>(windowSize.x()) / video.getSize().x(),
                static_cast<float>(windowSize.y()) / video.getSize().y());
        video.setScale(scale);
        video.updateTransform(math::Transform2D());
        video.play();

        while (window.isOpen())
        {
            window.update();
            video.update();
            target.clear();
            video.render(target);
            target.flush();
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << "STD Exception: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown Exception: System Error!" << std::endl;
    }



    return 0;
}
