import nyra.game2d as nyra

class MyTileMap(nyra.Actor2D):
    def initialize(self):
        self.camera = nyra.map.get_actor('camera')

    def update(self, delta):
        foo = self.get_tile((nyra.input.value('x'),
                             nyra.input.value('y')))
        
    def get_tile(self, position):
        cam_pos = self.camera.transform.position
        cam_size = self.camera['camera'].transform.size
        tile_size = self['tilemap'].tile_map.tile_size
        return (int((cam_pos[0] - cam_size[0] / 2 + position[0]) / tile_size[0]),
                int((cam_pos[1] - cam_size[1] / 2 + position[1]) / tile_size[1]))
