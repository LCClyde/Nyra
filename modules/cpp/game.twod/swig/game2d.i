%module game2d

%include "../../math/swig/math.i"

%{
    #include "nyra/win/Window.h"
    #include "nyra/graphics/sfml/RenderTarget.h"
    #include "nyra/game/Game.h"
    #include "nyra/game/Types.h"
    #include "nyra/game/twod/Game.h"
    #include "nyra/game/Actor.h"
    #include "nyra/input/Mouse.h"
    #include "nyra/input/Keyboard.h"
    #include "nyra/game/Input.h"
%}

%ignore addRenderable;
%ignore render;
%ignore setScript;
%ignore RenderableT;
%ignore RenderTargetT;
%ignore update;
%ignore addAnimation;
%ignore Input(const nyra::win::Window& window,
              const std::string& filename);

%rename(is_down) isDown;
%rename(is_pressed) isPressed;
%rename(is_released) isReleased;

%include "std_string.i"
%include "nyra/game/Actor.h"
%include "nyra/game/Input.h"
 
%template(Actor2D) nyra::game::Actor<nyra::game::twod::GameType>;
%template(input) nyra::game::Input<nyra::game::twod::GameType>;

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

def move(self, vec):
    self.moveBy(nyra.game2d.Vector2D(vec[0], vec[1]))

Actor2D.transform = property(Actor2D.getTransform)
Actor2D.move = move
Actor2D.animation = property(Actor2D.getAnimation, Actor2D.playAnimation)
%}