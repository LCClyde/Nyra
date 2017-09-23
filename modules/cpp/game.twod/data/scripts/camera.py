import nyra.game2d as nyra

class Camera(nyra.Actor2D):
    def initialize(self):
        self.tilemap = nyra.map.get_actor('tilemap')
        
    def update(self, delta):
        if nyra.input.is_down("move_cam"):
            self.move(nyra.Vector2D(
                    -nyra.input.value("cam_x"),
                    -nyra.input.value("cam_y")))
        position = self.position
        tile_map_size = self.tilemap.size
        cam_size = self.size
        half_cam = nyra.Vector2D(cam_size.x / 2, cam_size.y / 2)
        self.position = nyra.Vector2D(
                max(position.x, half_cam.x),
                max(position.y, half_cam.y))
        position = self.position
        self.position = nyra.Vector2D(
                min(position.x, tile_map_size.x - half_cam.x),
                min(position.y, tile_map_size.y - half_cam.y))
