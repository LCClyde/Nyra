import nyra.game2d as nyra
import math

class MoverInfo:
    def __init__(self, animation, direction, start, end, time):
        self.animation = animation
        self.direction = direction
        self.start = start
        self.end = end
        self.time = time

class CharacterMover:
    def __init__(self, positions):
        self.speed = 150
        self.animations = []
        time = 0
        self.time = 0
        for x in range(1, len(positions)):
            direction = nyra.Vector2D(positions[x][0] - positions[x - 1][0],
                                      positions[x][1] - positions[x - 1][1])
            length = direction.length()
            direction.normalize()
            time += length / self.speed

            angle = math.atan2(direction.y, direction.x)
            name = self.angle_to_direction(math.degrees(angle))
            entry = MoverInfo('walk_' + name, direction, positions[x - 1], positions[x], time)
            self.animations.append(entry)
        self.animations.append(MoverInfo('idle_down', nyra.Vector2D(), positions[-1], positions[-1], time))
        self.index = 0

    def update(self, delta, actor):
        self.time += delta

        # Keep incrementing index until we catch up to the animiation length
        while self.index < len(self.animations) - 1 and self.animations[self.index].time < self.time:
            actor.position = self.animations[self.index].end
            self.index += 1

        anim = self.animations[self.index]
        actor.animation = anim.animation
        pos_x, pos_y = actor.position
        pos_x += anim.direction.x * self.speed * delta
        pos_y += anim.direction.y * self.speed * delta
        actor.position = (pos_x, pos_y)
        
    def is_complete(self):
        return self.index == len(self.animations) - 1

    def angle_to_direction(self, angle):
        if angle < -135 or angle > 135:
            return 'left'
        if angle < 45 and angle > -45:
            return 'right'
        if angle < 0:
            return 'up'
        return 'down'