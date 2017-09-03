import nyra.game2d as nyra

class TestActor(nyra.Actor2D):
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
