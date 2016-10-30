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
#ifndef __NYRA_MATH_TRANSFORM_2D_H__
#define __NYRA_MATH_TRANSFORM_2D_H__

#include <nyra/math/Matrix3x3.h>
#include <nyra/math/Vector2.h>
#include <nyra/math/Conversions.h>

namespace nyra
{
namespace math
{
/*
 *  \class Transform2D
 *  \brief Handles setting position, rotation, and scale information for
 *         2D objects
 */
class Transform2D
{
public:
    /*
     *  \func Constructor
     *  \brief Sets up a default Transform
     */
    Transform2D();

    /*
     *  \func Destructor
     *  \brief Necessary for proper inheritance
     */
    virtual ~Transform2D() = default;

    /*
     *  \func setPosition
     *  \brief Sets the position of the object
     *
     *  \param position The desired position
     */
    void setPosition(const Vector2F& position)
    {
        mPosition = position;
        mDirty = true;
    }

    /*
     *  \func moveBy
     *  \brief Moves the object an additional move units
     *
     *  \param move The amount to move by
     */
    void moveBy(const Vector2F& move)
    {
        setPosition(mPosition + move);
    }

    /*
     *  \func getPosition
     *  \brief Gets the object position
     *
     *  \return The position
     */
    const Vector2F& getPosition() const
    {
        return mPosition;
    }

    /*
     *  \func setScale
     *  \brief Sets the scale of the object
     *
     *  \param scale The desired scale
     */
    void setScale(const Vector2F& scale)
    {
        mScale = scale;
        mDirty = true;
    }

    /*
     *  \func setScale
     *  \brief Sets uniform scale
     *
     *  \param scale The desired scale
     */
    void setScale(float scale)
    {
        setScale(Vector2F(scale, scale));
    }

    /*
     *  \func scaleBy
     *  \brief Scale the object by a value
     *
     *  \param scale The amount to scale by
     */
    void scaleBy(const Vector2F& scale)
    {
        setScale(Vector2F(mScale.x() * scale.x(),
                          mScale.y() * scale.y()));
    }

    /*
     *  \func scaleBy
     *  \brief Scale the object by a uniform value
     *
     *  \param scale The amount to scale by
     */
    void scaleBy(float scale)
    {
        setScale(mScale * scale);
    }

    /*
     *  \func getScale
     *  \brief Gets the object scale
     *
     *  \return The object scale
     */
    const Vector2F& getScale() const
    {
        return mScale;
    }

    /*
     *  \func setSize
     *  \brief Sets the size of the object. This is necessary if you want to
     *         set the pivot.
     *
     *  \param size The size of the object
     */
    void setSize(const Vector2F& size)
    {
        mSize = size;
        mDirty = true;
    }

    /*
     *  \func getSize
     *  \brief Gets the size of the object
     *
     *  \return The size of the object
     */
    const Vector2F& getSize() const
    {
        return mSize;
    }

    /*
     *  \func setPivot
     *  \brief Sets the pivot of the object. You must set the size for this
     *         to be meaningful. The pivot should be a 0.0 - 1.0 value.
     *
     *  \param pivot The desired pivot
     */
    void setPivot(const Vector2F& pivot)
    {
        mPivot = pivot;
        mDirty = true;
    }

    /*
     *  \func getPivot
     *  \brief Gets the pivot of the object
     *
     *  \return The object pivot
     */
    const Vector2F& getPivot() const
    {
        return mPivot;
    }

    /*
     *  \func setRotation
     *  \brief Sets the rotation of the object
     *
     *  \param rotation The rotation in degrees
     */
    void setRotation(float rotation)
    {
        mRotation = normalizeAngle(rotation);
        mDirty = true;
    }

    /*
     *  \func rotateBy
     *  \brief Rotates the object by an amount
     *
     *  \param rotation The amount to rotate by
     */
    void rotateBy(float rotation)
    {
        setRotation(mRotation + rotation);
    }

    /*
     *  \func getRotation
     *  \brief Gets the rotation of the object
     *
     *  \return The rotation value of the object
     */
    float getRotation() const
    {
        return mRotation;
    }

    /*
     *  \func getMatrix
     *  \brief Gets the global matrix. You must call update before calling this
     *         to ensure the matrix is using the latest information.
     *
     *  \return The global matrix
     */
    const Matrix3x3& getMatrix() const
    {
        return mGlobal;
    }

    /*
     *  \func updateTransform
     *  \brief Updates the global matrix. You must call this
     *         on the parent transform before calling it on a child node.
     *         TODO: Is there a way to get this to be callable from anywhere?
     *         I could store the parent as a member variable so it can go
     *         up the layers if necessary. The issue there is that it would
     *         not be possible to archive that information. It would also
     *         not be thread safe.
     *
     *  \param parent The parent transform. Use a default constructed
     *         Transform2D for a world matrix
     *  \return The transform matrix
     */
    void updateTransform(const Transform2D& parent);


private:
    NYRA_SERIALIZE()

    template<class ArchiveT>
    void serialize(ArchiveT& archive, const unsigned int version)
    {
        archive & mPosition;
        archive & mScale;
        archive & mSize;
        archive & mPivot;
        archive & mRotation;
        archive & mLocal;
        archive & mGlobal;

        // Force the dirty flag
        mDirty = true;
        archive & mDirty;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const Transform2D& transform);

    Vector2F mPosition;
    Vector2F mScale;
    Vector2F mSize;
    Vector2F mPivot;
    float mRotation;
    Matrix3x3 mLocal;
    Matrix3x3 mGlobal;
    bool mDirty;
};
}
}

#endif
