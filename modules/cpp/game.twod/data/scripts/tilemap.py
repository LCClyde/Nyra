import nyra.game2d as nyra

class MyTileMap(nyra.Actor2D):
    def initialize(self):
        self.camera = nyra.map.get_actor('camera')

    def update(self, delta):
        foo = self.get_tile(nyra.Vector2D(
                nyra.input.value('x'),
                nyra.input.value('y')))
        
    def get_cam_tile(self, position):
        cam_pos = self.camera.position
        cam_size = self.camera.size
        return self.get_tile(nyra.Vector2D(
                int(cam_pos.x - cam_size.x / 2 + position.x),
                int(cam_pos.y - cam_size.y / 2 + position.y)))

    def get_tile(self, position):
        tile_size = self.tile_size
        return nyra.Vector2D(int(position.x / tile_size.x),
                             int(position.y / tile_size.y))
        
    def tile_to_position(self, tile):
        tile_size = self.tile_size
        return nyra.Vector2D(tile.x * tile_size.x + tile_size.x / 2,
                             tile.y * tile_size.y + tile_size.y / 2)
