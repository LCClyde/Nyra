import nyra.game2d as nyra
from character_grid import CharacterGrid
from character_mover import CharacterMover

class Character(nyra.Actor2D):
    def initialize(self):
        self.speed = 3
        self.grid = CharacterGrid(self.speed)
        self.tilemap = nyra.map.get_actor('tilemap')
        self.camera = nyra.map.get_actor('camera')
        
        starting_tile = (5, 5)
        self.position = self.tilemap.tile_to_position(starting_tile)
        self.grid.reset(starting_tile)
        self.state = 'wait'

    def update(self, delta):
        if self.state == 'wait':
            if nyra.input.is_pressed('select'):
                self.select_tile()
        elif self.state == 'moving':
            self.mover.update(delta, self)
            if self.mover.is_complete():
                self.state  = 'wait'
                self.grid.reset(self.tilemap.get_tile(self.position))

    def select_tile(self):
        cam_pos = self.camera.position
        cam_size = self.camera.size
        mouse_tile = self.tilemap.get_cam_tile((nyra.input.value('x'),
                                                nyra.input.value('y')))
        char_tile = self.tilemap.get_tile(self.position)
        rel_tile = (mouse_tile[0] - char_tile[0],
                    mouse_tile[1] - char_tile[1])
        
        if self.grid.get(rel_tile) > 0:
            self.mover = CharacterMover([self.position,
                                         self.tilemap.tile_to_position(mouse_tile)])
            self.state = 'moving'
