%module game2d

%include "../../math/swig/math.i"

%{
    #include "nyra/graphics/sfml/RenderTarget.h"
    #include "nyra/game/Game.h"
    #include "nyra/game/Types.h"
    #include "nyra/game/twod/Game.h"
    #include "nyra/game/Actor.h"
%}

%ignore addRenderable;
%ignore render;
%ignore setScript;
%ignore RenderableT;
%ignore RenderTargetT;

%include "nyra/game/Actor.h"

%template(Actor2D) nyra::game::Actor<nyra::game::twod::GameType>;

%extend nyra::game::Actor<nyra::game::twod::GameType>
{
    // I really hate that I need to redefine. 
    // There has to be a better way.
    nyra::math::Transform<nyra::math::Vector2F,
                          nyra::math::Vector2F,
                          float,
                          nyra::math::Vector2F,
                          nyra::math::Vector2F,
                          nyra::math::Matrix3x3>* getTransform()
    {
        return $self;
    }
    
    size_t nyra_pointer()
    {
        return reinterpret_cast<size_t>($self);
    }
}

%rename(Actor) Actor2D;

%pythoncode
%{
import nyra.game2d

Actor2D.transform = property(Actor2D.getTransform)
%}