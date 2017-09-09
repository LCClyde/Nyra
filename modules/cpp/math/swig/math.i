%module math

%{
    #include "nyra/math/Vector.h"
    #include "nyra/math/Vector2.h"
    #include "nyra/math/Matrix.h"
    #include "nyra/math/Matrix3x3.h"
    #include "nyra/math/Transform.h"
%}

%include "../../core/swig/core.i"

%ignore x;
%ignore y;

%include "nyra/math/Transform.h"
%include "nyra/math/Vector.h"
%include "nyra/math/Vector2.h"

%template(Vector2Raw) nyra::math::Vector<float, 2>;
%template(Vector2D) nyra::math::Vector2<float>;
%template(Vector2U) nyra::math::Vector2<uint32_t>;

%extend nyra::math::Vector2<float>
{
    float _get_x() const
    {
        return $self->x;
    }

    float _get_y() const
    {
        return $self->y;
    }

    void _set_x(float x)
    {
        $self->x = x;
    }

    void _set_y(float y)
    {
        $self->y = y;
    }
}

%extend nyra::math::Vector2<uint32_t>
{
    float _get_x() const
    {
        return $self->x;
    }

    float _get_y() const
    {
        return $self->y;
    }

    void _set_x(float x)
    {
        $self->x = x;
    }

    void _set_y(float y)
    {
        $self->y = y;
    }
}

%template(Transform2D) nyra::math::Transform<nyra::math::Vector2F,
                                             nyra::math::Vector2F,
                                             float,
                                             nyra::math::Vector2F,
                                             nyra::math::Vector2F,
                                             nyra::math::Matrix3x3>;

%pythoncode
%{
import nyra.math

Vector2D.x = property(Vector2D._get_x, Vector2D._set_x)
Vector2D.y = property(Vector2D._get_y, Vector2D._set_y)
Vector2U.x = property(Vector2U._get_x, Vector2U._set_x)
Vector2U.y = property(Vector2U._get_y, Vector2U._set_y)

def _set_position(self, values):
    self.setPosition(Vector2D(values[0], values[1]))

def _get_position(self):
    v = self.getPosition()
    return (v.x, v.y)

def _set_scale(self, values):
    self.setScale(Vector2D(values[0], values[1]))
    
def _get_scale(self):
    v = self.getScale()
    return (v.x, v.y)

def _set_pivot(self, values):
    self.setPivot(Vector2D(values[0], values[1]))
    
def _get_pivot(self):
    v = self.getPivot()
    return (v.x, v.y)
    
def _set_rotation(self, val):
    self.setRotation(val)
    
def _get_rotation(self):
    return self.getRotation()
    
def _move(self, val):
    self.moveBy(Vector2D(val[0], val[1]))
    
def _get_size(self):
    size = self.getSize()
    return (size.x, size.y)
    
def _set_size(self, val):
    self.setSize(Vector2D(values[0], values[1]))
    
Transform2D.position = property(_get_position, _set_position)
Transform2D.scale = property(_get_scale, _set_scale)
Transform2D.pivot = property(_get_pivot, _set_pivot)
Transform2D.rotation = property(_get_rotation, _set_rotation)
Transform2D.size = property(_get_size, _set_size)
Transform2D.move = _move

%}
