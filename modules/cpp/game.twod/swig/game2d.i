%module game2d

%include "../../math/swig/math.i"
%include "std_vector.i"

%{
    #include "nyra/win/Window.h"
    #include "nyra/graphics/sfml/RenderTarget.h"
    #include "nyra/game/Game.h"
    #include "nyra/game/Types.h"
    #include "nyra/game/twod/Game.h"
    #include "nyra/physics/Body.h"
    #include "nyra/game/Actor.h"
    #include "nyra/input/Mouse.h"
    #include "nyra/input/Keyboard.h"
    #include "nyra/game/Input.h"
    #include "nyra/script/py3/Object.h"
    #include "nyra/math/PathResults.h"
%}

%ignore addRenderable;
%ignore render;
%ignore setScript;
%ignore RenderableT;
%ignore RenderTargetT;
%ignore update;
%ignore addAnimation;
%ignore addNavMesh;
%ignore getNavMesh;
%ignore Input(const nyra::win::Window& window,
              const std::string& filename);
%ignore TileMap(const std::string& spritePathname,
                const mem::Buffer2D<size_t>& tiles,
                const math::Vector2U tileSize);
%ignore getRenderable;
%ignore addActor;
%ignore getActor;
%ignore addGUI;
%ignore Map(const game::Input<GameT>& input,
            const graphics::RenderTarget& target);
%ignore getMouse;
%ignore getPhysics;
%ignore addBody;

%rename(is_down) isDown;
%rename(is_pressed) isPressed;
%rename(is_released) isReleased;
%rename(value) getValue;

%include "std_string.i"
%include "nyra/game/Actor.h"
%include "nyra/game/Input.h"
%include "nyra/game/Map.h"
%include "nyra/graphics/TileMap.h"
%include "nyra/math/PathResults.h"

%template(Actor2D) nyra::game::Actor<nyra::game::twod::GameType>;
%template(input) nyra::game::Input<nyra::game::twod::GameType>;
%template(TileMap2D) nyra::graphics::TileMap<nyra::graphics::sfml::Sprite>;
%template(map) nyra::game::Map<nyra::game::twod::GameType>;
%template(VectorVector2D) std::vector<nyra::math::Vector2F>;
%template(PathResultsTileMap) nyra::math::PathResults<nyra::math::Vector2F>;

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
    
    void move(const nyra::math::Vector2F& amount)
    {
        $self->moveBy(amount);
    }
    
    nyra::math::PathResults<nyra::math::Vector2F> get_path(
            const nyra::math::Vector2F& start,
            const nyra::math::Vector2F& end) const
    {
        return $self->getNavMesh().getPath(start, end);
    }
    
    PyObject* _getScript() const
    {
        const nyra::script::Object& object = $self->getScript();
        const nyra::script::py3::Object& pyObject =
                dynamic_cast<const nyra::script::py3::Object&>(object);
        return pyObject.getNative().steal();
    }
    
    nyra::math::Vector2F _getVelocity() const
    {
        return $self->getPhysics().getVelocity();
    }
    
    void _setVelocity(const nyra::math::Vector2F& velocity)
    {
        return $self->getPhysics().setVelocity(velocity);
    }
}

%extend nyra::game::Map<nyra::game::twod::GameType>
{
    static nyra::game::Actor<nyra::game::twod::GameType>& _getActor(const std::string& name)
    {
        return  nyra::game::Map<nyra::game::twod::GameType>::getActor(name);
    }
    
    static nyra::game::Actor<nyra::game::twod::GameType>& _spawn(const std::string& filename,
                       const std::string& name)
    {
        nyra::game::Actor<nyra::game::twod::GameType>& actor =
                nyra::game::Map<nyra::game::twod::GameType>::getMap().spawnActor(
                        filename, name, true);
        return actor;
    }
}

%rename(Actor) Actor2D;

%pythoncode
%{
import nyra.game2d
from collections import namedtuple

def _get_script(self):
    if self.hasScript():
        return self._getScript()
    return self
    
def get_actor(name):
    actor = nyra.game2d.map._getActor(name)
    return actor._get_script()

def spawn(filename,
          name='',
          position=None,
          rotation=None,
          scale=None):
    actor = nyra.game2d.map._spawn(filename, name)
    
    if position is not None:
        actor.position = position
    if scale is not None:
        actor.scale = scale
    if rotation is not None:
        actor.rotation = rotation
    return actor._get_script()

Actor2D.position = property(Actor2D._getPosition, Actor2D._setPosition)
Actor2D.size = property(Actor2D._getSize)
Actor2D.tile_size = property(Actor2D._getTileSize)
Actor2D.animation = property(Actor2D.getAnimation, Actor2D.playAnimation)
Actor2D.velocity = property(Actor2D._getVelocity, Actor2D._setVelocity)
Actor2D._get_script = _get_script
map.spawn = spawn
map.get_actor = get_actor
%}