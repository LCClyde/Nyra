import nyra.game2d as nyra

class TestActor(nyra.Actor2D):        
    def update(self, delta):
        pos = self.transform.position
        self.transform.position = (pos[0] + delta * 20, pos[1] + delta * 20)
