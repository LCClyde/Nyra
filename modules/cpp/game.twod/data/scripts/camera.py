import nyra.game2d as nyra

class Camera(nyra.Actor2D):
    def initialize(self):
        self.tilemap = nyra.map.get_actor('tilemap')
        
    def update(self, delta):
        if nyra.input.is_down("move_cam"):
            self.transform.move((-nyra.input.value("cam_x"),
                                 -nyra.input.value("cam_y")))
        position = self.transform.position
        cam_size = self['camera'].transform.size
        self.transform.position = (max(position[0], cam_size[0] / 2),
                                   max(position[1], cam_size[1] / 2))
