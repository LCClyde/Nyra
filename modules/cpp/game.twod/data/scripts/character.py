import nyra.game2d as nyra
from character_grid import CharacterGrid

class Character(nyra.Actor2D):
    def initialize(self):
        self.speed = 3
        self.grid = CharacterGrid(self.speed)
        self.tilemap = nyra.map.get_actor('tilemap')
        self.camera = nyra.map.get_actor('camera')
        
        starting_tile = (5, 5)
        self.transform.position = self.tilemap.tile_to_position(starting_tile)
        self.grid.reset(starting_tile)

    def update(self, delta):
        vec = nyra.Vector2D()

        if nyra.input.is_down("move_up"):
            vec.y -= 1
        if nyra.input.is_down("move_down"):
            vec.y += 1
        if nyra.input.is_down("move_left"):
            vec.x -= 1
        if nyra.input.is_down("move_right"):
            vec.x += 1

        vec.normalize()
        self.transform.move((vec.x * delta * 100.0, vec.y * delta * 100.0))

        if vec.x < 0.0:
            self.animation = "walk_left"
        elif vec.x > 0.0:
            self.animation ="walk_right"
        elif vec.y < 0.0:
            self.animation = "walk_up"
        elif vec.y > 0.0:
            self.animation = "walk_down"
        else:
            self.animation = "idle_" + self.animation.split('_')[1]
            
        if nyra.input.is_pressed('select'):
            cam_pos = self.camera.transform.position
            cam_size = self.camera['camera'].transform.size
            mouse_tile = self.tilemap.get_cam_tile((nyra.input.value('x'),
                                                    nyra.input.value('y')))
            char_tile = self.tilemap.get_tile(self.transform.position)
            rel_tile = (mouse_tile[0] - char_tile[0],
                        mouse_tile[1] - char_tile[1])
            
            if self.grid.get(rel_tile) > 0:
                self.transform.position = self.tilemap.tile_to_position(mouse_tile)
                self.grid.reset(mouse_tile)
                
        
