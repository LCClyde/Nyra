import nyra.game2d as nyra

class MyTileMap(nyra.Actor2D):
    def initialize(self):
        self.camera = nyra.map.get_actor('camera')

    def update(self, delta):
        foo = self.get_tile((nyra.input.value('x'),
                             nyra.input.value('y')))
        
    def get_cam_tile(self, position):
        cam_pos = self.camera.transform.position
        cam_size = self.camera['camera'].transform.size
        return self.get_tile((int(cam_pos[0] - cam_size[0] / 2 + position[0]),
                              int(cam_pos[1] - cam_size[1] / 2 + position[1])))

    def get_tile(self, position):
        tile_size = self['tilemap'].tile_map.tile_size
        return (int(position[0] / tile_size[0]),
                int(position[1] / tile_size[1]))
        
    def tile_to_position(self, tile):
        tile_size = self['tilemap'].tile_map.tile_size
        return (tile[0] * tile_size[0] + tile_size[0] / 2,
                tile[1] * tile_size[1] + tile_size[1] / 2)
