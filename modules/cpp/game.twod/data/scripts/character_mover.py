import nyra.game2d as nyra
import math

class MoverInfo:
    def __init__(self, animation, direction, start, end, time,):
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
        tilemap = nyra.map.get_actor('tilemap')
        self.tile_size = tilemap.tile_size
        for x in range(1, len(positions)):
            this_pos = self.update_pos(positions[x])
            prev_pos = self.update_pos(positions[x - 1])
            direction = nyra.Vector2D(this_pos.x - prev_pos.x,
                                      this_pos.y - prev_pos.y)
            length = direction.length()
            direction.normalize()
            time += length / self.speed

            angle = math.atan2(direction.y, direction.x)
            name = self.angle_to_direction(math.degrees(angle))
            entry = MoverInfo('walk_' + name, direction, prev_pos, this_pos, time)
            self.animations.append(entry)
        final_pos = self.update_pos(positions[-1])
        self.animations.append(MoverInfo('idle_down', nyra.Vector2D(), final_pos, final_pos, time))
        self.index = 0
        
    def update_pos(self, pos):
        return nyra.Vector2D(self.tile_size.x / 2 + pos.x * self.tile_size.x,
                             self.tile_size.y / 2 + pos.y * self.tile_size.y)

    def update(self, delta, actor):
        self.time += delta

        # Keep incrementing index until we catch up to the animiation length
        while self.index < len(self.animations) - 1 and self.animations[self.index].time < self.time:
            actor.position = self.animations[self.index].end
            self.index += 1

        anim = self.animations[self.index]
        actor.animation = anim.animation
        pos = actor.position
        pos.x += anim.direction.x * self.speed * delta
        pos.y += anim.direction.y * self.speed * delta
        actor.position = pos
        
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