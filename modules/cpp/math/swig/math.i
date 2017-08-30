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
%include "nyra/math/Vector2.h"

%template(Vector2F) nyra::math::Vector2<float>;

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

%template(Transform2D) nyra::math::Transform<nyra::math::Vector2F,
                                             nyra::math::Vector2F,
                                             float,
                                             nyra::math::Vector2F,
                                             nyra::math::Vector2F,
                                             nyra::math::Matrix3x3>;

%pythoncode
%{
import nyra.math

Vector2F.x = property(Vector2F._get_x, Vector2F._set_x)
Vector2F.y = property(Vector2F._get_y, Vector2F._set_y)

def _set_position(self, values):
    self.setPosition(Vector2F(values[0], values[1]))

def _get_position(self):
    v = self.getPosition()
    return (v.x, v.y)

def _set_scale(self, values):
    self.setScale(Vector2F(values[0], values[1]))
    
def _get_scale(self):
    v = self.getScale()
    return (v.x, v.y)

def _set_pivot(self, values):
    self.setPivot(Vector2F(values[0], values[1]))
    
def _get_pivot(self):
    v = self.getPivot()
    return (v.x, v.y)
    
def _set_rotation(self, val):
    self.setRotation(val)
    
def _get_rotation(self):
    return self.getRotation()
    
Transform2D.position = property(_get_position, _set_position)
Transform2D.scale = property(_get_scale, _set_scale)
Transform2D.pivot = property(_get_pivot, _set_pivot)
Transform2D.rotation = property(_get_rotation, _set_rotation)

%}
