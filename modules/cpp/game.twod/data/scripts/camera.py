import nyra.game2d as nyra

class Camera(nyra.Actor2D):
    def update(self, delta):
        if nyra.input.is_down("move_cam"):
            self.transform.move((-nyra.input.value("cam_x"),
                                 -nyra.input.value("cam_y")))
