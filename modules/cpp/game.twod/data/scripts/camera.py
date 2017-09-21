import nyra.game2d as nyra

class Camera(nyra.Actor2D):
    def initialize(self):
        self.tilemap = nyra.map.get_actor('tilemap')
        
    def update(self, delta):
        if nyra.input.is_down("move_cam"):
            self.move((-nyra.input.value("cam_x"),
                       -nyra.input.value("cam_y")))
        position = self.position
        tile_map_size = self.tilemap.size
        cam_size = self.size
        half_cam = (cam_size[0] / 2, cam_size[1] / 2)
        self.position = (max(position[0], half_cam[0]),
                         max(position[1], half_cam[1]))
        position = self.position
        self.position = (min(position[0], tile_map_size[0] - half_cam[0]),
                         min(position[1], tile_map_size[1] - half_cam[1]))
