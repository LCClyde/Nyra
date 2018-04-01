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
#include <nyra/test/RenderTarget.h>
#include <nyra/graphics/ogre/RenderTarget.h>
#include <nyra/graphics/ogre/Mesh.h>
#include <nyra/graphics/ogre/Camera.h>
#include <nyra/test/Image.h>
#include <nyra/graphics/Collada.h>
#include <nyra/win/ogre/Window.h>

namespace nyra
{
namespace graphics
{
namespace ogre
{
TEST(Camera, Render)
{
    RenderTarget target(math::Vector2U(300, 150));
    graphics::Collada collada(core::path::join(
            core::DATA_PATH, "models/teapot.dae"));
    Mesh mesh(collada.getVertices(), collada.getIndices());
    Camera camera(target);

    const float defaultZ = 125.0f;
    const float offset = 25.0f;
    camera.setPosition(math::Vector3F(0.0f, 0.0f, 125.0f));

    //=======================================================================//
    camera.setYaw(-15);
    camera.updateTransform(math::Transform3D());
    camera.render(target);

    target.clear(img::Color(128, 128, 128));
    mesh.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(target.getPixels(), "test_ogre_camera_yaw_-15.png"));

    //=======================================================================//
    camera.setYaw(15);
    camera.updateTransform(math::Transform3D());
    camera.render(target);

    target.clear(img::Color(128, 128, 128));
    mesh.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(target.getPixels(), "test_ogre_camera_yaw_15.png"));
    camera.setYaw(0);

    //=======================================================================//
    camera.setPitch(-15);
    camera.updateTransform(math::Transform3D());
    camera.render(target);

    target.clear(img::Color(128, 128, 128));
    mesh.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(target.getPixels(), "test_ogre_camera_pitch_-15.png"));

    //=======================================================================//
    camera.setPitch(15);
    camera.updateTransform(math::Transform3D());
    camera.render(target);

    target.clear(img::Color(128, 128, 128));
    mesh.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(target.getPixels(), "test_ogre_camera_pitch_15.png"));
    camera.setPitch(0);

    //=======================================================================//
    camera.setRoll(-15);
    camera.updateTransform(math::Transform3D());
    camera.render(target);

    target.clear(img::Color(128, 128, 128));
    mesh.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(target.getPixels(), "test_ogre_camera_roll_-15.png"));

    //=======================================================================//
    camera.setRoll(15);
    camera.updateTransform(math::Transform3D());
    camera.render(target);

    target.clear(img::Color(128, 128, 128));
    mesh.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(target.getPixels(), "test_ogre_camera_roll_15.png"));
    camera.setRoll(0);

    //=======================================================================//
    camera.setPosition(math::Vector3F(offset, 0.0f, defaultZ));
    camera.updateTransform(math::Transform3D());
    camera.render(target);

    target.clear(img::Color(128, 128, 128));
    mesh.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(target.getPixels(), "test_ogre_camera_x.png"));

    //=======================================================================//
    camera.setPosition(math::Vector3F(0.0f, offset, defaultZ));
    camera.updateTransform(math::Transform3D());
    camera.render(target);

    target.clear(img::Color(128, 128, 128));
    mesh.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(target.getPixels(), "test_ogre_camera_y.png"));

    //=======================================================================//
    camera.setPosition(math::Vector3F(00.0f, 0.0f, defaultZ + offset));
    camera.updateTransform(math::Transform3D());
    camera.render(target);

    target.clear(img::Color(128, 128, 128));
    mesh.render(target);
    target.flush();
    EXPECT_TRUE(test::compareImage(target.getPixels(), "test_ogre_camera_z.png"));
}
}
}
}

NYRA_TEST()
