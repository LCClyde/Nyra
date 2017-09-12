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
    #include "nyra/script/py3/Object.h"
%}

%inline %{
class Component
{
public:
    Component(void* ptr) :
        mPtr(ptr)
    {
    }

    nyra::math::Transform<nyra::math::Vector2F,
                          nyra::math::Vector2F,
                          float,
                          nyra::math::Vector2F,
                          nyra::math::Vector2F,
                          nyra::math::Matrix3x3>* _transform() const
    {
        return reinterpret_cast<nyra::math::Transform<
                nyra::math::Vector2F,
                nyra::math::Vector2F,
                float,
                nyra::math::Vector2F,
                nyra::math::Vector2F,
                nyra::math::Matrix3x3>*>(mPtr);
    }
    
    nyra::graphics::TileMap<nyra::graphics::sfml::Sprite>* _tile_map() const
    {
        return reinterpret_cast<nyra::graphics::TileMap<
                nyra::graphics::sfml::Sprite>*>(mPtr);
    }
    
private:
    void* mPtr;
};
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
%ignore TileMap(const std::string& spritePathname,
                const mem::Buffer2D<size_t>& tiles,
                const math::Vector2U tileSize);
%ignore getRenderable;
%ignore addActor;
%ignore getActor;

%rename(is_down) isDown;
%rename(is_pressed) isPressed;
%rename(is_released) isReleased;
%rename(value) getValue;

%include "std_string.i"
%include "nyra/game/Actor.h"
%include "nyra/game/Input.h"
%include "nyra/game/Map.h"
%include "nyra/graphics/TileMap.h"
 
%template(Actor2D) nyra::game::Actor<nyra::game::twod::GameType>;
%template(input) nyra::game::Input<nyra::game::twod::GameType>;
%template(TileMap2D) nyra::graphics::TileMap<nyra::graphics::sfml::Sprite>;
%template(map) nyra::game::Map<nyra::game::twod::GameType>;

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

    Component _getComponent(const std::string& name)
    {
        return Component(&($self->getRenderable(name)));
    }

    size_t nyra_pointer()
    {
        return reinterpret_cast<size_t>($self);
    }
}

%extend nyra::game::Map<nyra::game::twod::GameType>
{
    static PyObject* get_actor(const std::string& name)
    {
        const nyra::script::Object& object =
                nyra::game::Map<nyra::game::twod::GameType>::getActor(name).getScript();
        const nyra::script::py3::Object& pyObject =
                dynamic_cast<const nyra::script::py3::Object&>(object);
        return pyObject.getNative().steal();
    }
}

%rename(Actor) Actor2D;

%pythoncode
%{
import nyra.game2d
from collections import namedtuple

def move(self, vec):
    self.moveBy(nyra.game2d.Vector2D(vec[0], vec[1]))
    
def _get_tile_size(self):
    v = self.getTileSize()
    return (v.x, v.y)

Actor2D.transform = property(Actor2D.getTransform)
Actor2D.move = move
Actor2D.__getitem__ = Actor2D._getComponent
Actor2D.animation = property(Actor2D.getAnimation, Actor2D.playAnimation)
TileMap2D.tile_size = property(_get_tile_size)
Component.transform = property(Component._transform)
Component.tile_map = property(Component._tile_map)
%}