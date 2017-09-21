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
    size_t nyra_pointer()
    {
        return reinterpret_cast<size_t>($self);
    }
    
    void destroy()
    {
        nyra::game::Map<nyra::game::twod::GameType>::getMap().destroyActor($self);
    }
    
    const nyra::math::Vector2F& _getPosition() const
    {
        return $self->getPosition();
    }
    
    void _setPosition(const nyra::math::Vector2F& pos)
    {
        $self->setPosition(pos);
    }
    
    const nyra::math::Vector2F& _getSize() const
    {
        return $self->getRenderable().getSize();
    }
    
    const nyra::math::Vector2U& _getTileSize() const
    {
         return reinterpret_cast<const nyra::graphics::TileMap<
                nyra::graphics::sfml::Sprite>&>($self->getRenderable()).getTileSize();
    }
    
    void _moveBy(const nyra::math::Vector2F& amount)
    {
        $self->moveBy(amount);
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
    
    static nyra::game::Actor<nyra::game::twod::GameType>& _spawn(const std::string& filename,
                       const std::string& name,
                       const nyra::math::Vector2F& position,
                       float rotation,
                       const nyra::math::Vector2F& scale)
    {
        nyra::game::Actor<nyra::game::twod::GameType>& actor =
                nyra::game::Map<nyra::game::twod::GameType>::getMap().spawnActor(
                        filename, name, true);
        actor.setPosition(position);
        actor.setRotation(rotation);
        actor.setScale(scale);
        return actor;
    }
}

%rename(Actor) Actor2D;

%pythoncode
%{
import nyra.game2d
from collections import namedtuple

def move(self, vec):
    self._moveBy(nyra.game2d.Vector2D(vec[0], vec[1]))
    
def _get_tile_size(self):
    v = self.getTileSize()
    return (v.x, v.y)
    
def _get_position(self):
    v = self._getPosition()
    return (v.x, v.y)

def _set_position(self, pos):
    self._setPosition(nyra.game2d.Vector2D(pos[0], pos[1]))
    
def _get_size(self):
    v = self._getSize()
    return (v.x, v.y)
    
def _get_tile_size(self):
    v = self._getTileSize()
    return (v.x, v.y)

def spawn(filename,
          name='',
          position=(0, 0),
          rotation=0,
          scale=(1, 1),
          pivot=(0.5, 0.5)):
    return nyra.game2d.map._spawn(filename,
                           name,
                           nyra.game2d.Vector2D(position[0], position[1]),
                           rotation,
                           nyra.game2d.Vector2D(scale[0], scale[1]))

Actor2D.move = move
Actor2D.position = property(_get_position, _set_position)
Actor2D.size = property(_get_size)
Actor2D.tile_size = property(_get_tile_size)
Actor2D.animation = property(Actor2D.getAnimation, Actor2D.playAnimation)
map.spawn = spawn
Actor2D.tile_size = property(_get_tile_size)
%}