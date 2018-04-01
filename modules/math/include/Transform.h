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
#ifndef __NYRA_MATH_TRANSFORM_H__
#define __NYRA_MATH_TRANSFORM_H__

#include <iostream>
#include <nyra/math/Matrix3x3.h>
#include <nyra/math/Vector2.h>
#include <nyra/math/Matrix4x4.h>
#include <nyra/math/Vector3.h>
#include <nyra/math/Conversions.h>

namespace nyra
{
namespace math
{
/*
 *  \class Transform
 *  \brief Handles setting position, rotation, and scale information for
 *         objects
 */
template <typename PositionT,
          typename ScaleT,
          typename RotationT,
          typename SizeT,
          typename PivotT,
          typename MatrixT>
class Transform
{
public:
    typedef PositionT Position;
    typedef ScaleT Scale;
    typedef RotationT Rotation;
    typedef SizeT Size;
    typedef PivotT Pivot;

    /*
     *  \func Constructor
     *  \brief Sets up a default Transform
     */
    Transform() :
        mScale(1.0f),
        mPivot(0.5f),
        mRotation(0.0f),
        mDirty(true),
        mRebuildMatrix(true)
    {
    }

    /*
     *  \func Destructor
     *  \brief Necessary for proper inheritance
     */
    virtual ~Transform() = default;

    /*
     *  \func setPosition
     *  \brief Sets the position of the object
     *
     *  \param position The desired position
     */
    void setPosition(const PositionT& position)
    {
        mPosition = position;
        setDirty();
    }

    /*
     *  \func moveBy
     *  \brief Moves the object an additional move units
     *
     *  \param move The amount to move by
     */
    void moveBy(const PositionT& move)
    {
        setPosition(mPosition + move);
    }

    /*
     *  \func getPosition
     *  \brief Gets the object position
     *
     *  \return The position
     */
    const PositionT& getPosition() const
    {
        return mPosition;
    }

    /*
     *  \func setScale
     *  \brief Sets the scale of the object
     *
     *  \param scale The desired scale
     */
    void setScale(const ScaleT& scale)
    {
        mScale = scale;
        setDirty();
    }

    /*
     *  \func setScale
     *  \brief Sets uniform scale
     *
     *  \param scale The desired scale
     */
    void setScale(float scale)
    {
        setScale(ScaleT(scale));
    }

    /*
     *  \func scaleBy
     *  \brief Scale the object by a value
     *
     *  \param scale The amount to scale by
     */
    void scaleBy(const ScaleT& scale)
    {
        setScale(mScale * scale);
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
    const ScaleT& getScale() const
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
    void setSize(const SizeT& size)
    {
        mSize = size;
        setDirty();
    }

    /*
     *  \func getSize
     *  \brief Gets the size of the object
     *
     *  \return The size of the object
     */
    const SizeT& getSize() const
    {
        return mSize;
    }

    /*
     *  \func getScaledSize
     *  \brief Gets the size of the object after being scaled
     *
     *  \return The scaled size of the object.
     */
    SizeT getScaledSize()
    {
        return mSize * mScale;
    }

    /*
     *  \func setPivot
     *  \brief Sets the pivot of the object. You must set the size for this
     *         to be meaningful. The pivot should be a 0.0 - 1.0 value.
     *
     *  \param pivot The desired pivot
     */
    void setPivot(const PivotT& pivot)
    {
        mPivot = pivot;
        setDirty();
    }

    /*
     *  \func getPivot
     *  \brief Gets the pivot of the object
     *
     *  \return The object pivot
     */
    const PivotT& getPivot() const
    {
        return mPivot;
    }

    /*
     *  \func setRotation
     *  \brief Sets the rotation of the object
     *
     *  \param rotation The rotation in degrees
     */
    void setRotation(RotationT rotation)
    {
        mRotation = normalizeAngle(rotation);
        setDirty();
    }

    /*
     *  \func rotateBy
     *  \brief Rotates the object by an amount
     *
     *  \param rotation The amount to rotate by
     */
    void rotateBy(RotationT rotation)
    {
        setRotation(mRotation + rotation);
    }

    /*
     *  \func getRotation
     *  \brief Gets the rotation of the object
     *
     *  \return The rotation value of the object
     */
    const RotationT& getRotation() const
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
    const MatrixT& getMatrix() const
    {
        return mGlobal;
    }

    /*
     *  \func isDirty
     *  \brief This is an external flag that can be used to determine if the
     *         values have changed since last update.
     *
     *  \return True if the values have changed
     */
    bool isDirty() const
    {
        return mDirty;
    }

    /*
     *  \func resetDirty
     *  \brief Resets the external dirty flag to flase
     */
    void resetDirty()
    {
        mDirty = false;
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
    virtual void updateTransform(const Transform<PositionT,
                                                 ScaleT,
                                                 RotationT,
                                                 SizeT,
                                                 PivotT,
                                                 MatrixT>& parent)
    {
        if (mRebuildMatrix)
        {
            mLocal.transform(mPosition,
                             mScale,
                             mRotation,
                             mPivot * (mSize * -1.0f));
        }

        // We could optimize out this matrix transform but you can get into
        // strange situations where it you optimize it out by accident if you
        // change the parent to a stable matrix.
        mGlobal = mLocal * parent.mGlobal;
        mRebuildMatrix = false;
    }


protected:
    void setDirty()
    {
        mDirty = true;
        mRebuildMatrix = true;
    }

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
                                    const Transform<PositionT,
                                                    ScaleT,
                                                    RotationT,
                                                    SizeT,
                                                    PivotT,
                                                    MatrixT>& transform)
    {
        os << "Position: " << transform.getPosition() << "\n"
           << "Scale: " << transform.getScale() << "\n"
           << "Rotation: " << transform.getRotation() << "\n"
           << "Pivot: " << transform.getPivot();
        return os;
    }

    PositionT mPosition;
    ScaleT mScale;
    SizeT mSize;
    PivotT mPivot;
    RotationT mRotation;
    MatrixT mLocal;
    MatrixT mGlobal;
    bool mDirty;
    bool mRebuildMatrix;
};

/*
 *  \type Transform2D
 *  \brief Transform usable to 2D objects.
 */
typedef Transform<Vector2F,
                  Vector2F,
                  float,
                  Vector2F,
                  Vector2F,
                  Matrix3x3> Transform2D;

/*
 *  \type Transform3D
 *  \brief Transform usable to 3D objects.
 */
class Transform3D : public Transform<Vector3F,
                                    Vector3F,
                                    Vector3F,
                                    Vector3F,
                                    Vector3F,
                                    Matrix4x4>
{
public:
    /*
     *  \func getYaw
     *  \brief Gets the yaw angle in degrees
     *
     *  \return The current yaw
     */
    float getYaw() const
    {
        return mRotation.y;
    }

    /*
     *  \func getPitch
     *  \brief Gets the pitch angle in degrees
     *
     *  \return The current pitch
     */
    float getPitch() const
    {
        return mRotation.x;
    }

    /*
     *  \func getRoll
     *  \brief Gets the roll angle in degrees
     *
     *  \return The current roll
     */
    float getRoll() const
    {
        return mRotation.z;
    }

    /*
     *  \func setYaw
     *  \brief Sets the yaw angle
     *
     *  \param yaw The desired yaw in degrees
     */
    void setYaw(float yaw)
    {
        mRotation.y = normalizeAngle(yaw);
        setDirty();
    }

    /*
     *  \func setPitch
     *  \brief Sets the pitch angle
     *
     *  \param pitch The desired pitch in degrees
     */
    void setPitch(float pitch)
    {
        mRotation.x = normalizeAngle(pitch);
        setDirty();
    }

    /*
     *  \func setRoll
     *  \brief Sets the roll angle
     *
     *  \param roll The desired roll in degrees
     */
    void setRoll(float roll)
    {
        mRotation.z = normalizeAngle(roll);
        setDirty();
    }
};
}
}

#endif
