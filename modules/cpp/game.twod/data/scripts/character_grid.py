import nyra.game2d as nyra

class CharacterGrid:
    def __init__(self, speed):
        self.tiles = []
        self.actors = []
        self.tilemap = nyra.map.get_actor('tilemap')
        size = self.tilemap['tilemap'].transform.size
        tile_size = self.tilemap['tilemap'].tile_map.tile_size
        self.tilemap_size = (size[0] / tile_size[0], size[1] / tile_size[1])
        
        self.speed = speed
        num_tiles = speed * 2 + 1
        self.tiles = []
        for x in range(num_tiles):
            self.tiles.append([0] * num_tiles)
        
    def reset(self, position):
        for actor in self.actors:
            actor.destroy()
        self.actors = []
        
        for x in range(-self.speed, self.speed + 1):
            for y in range(-self.speed, self.speed + 1):
                self.set(x, y, position)
        
        for x in range(-self.speed, self.speed + 1):
            for y in range(-self.speed, self.speed + 1):
                value = (self.get((x, y)) * 10000 +
                         (self.get((x, y - 1)) ^ 1) * 1000 +
                         (self.get((x + 1, y)) ^ 1) * 100 +
                         (self.get((x, y + 1)) ^ 1) * 10 +
                         (self.get((x - 1, y)) ^ 1))
                if value > 10000:
                    pos = self.tilemap.tile_to_position((position[0] + x, position[1] + y))
                    self.actors.append(nyra.map.spawn('edge_' + str(value) + '.json', position=pos))
        
        
    def set(self, x,  y, pos):
        result = 1
        if x + pos[0] < 0 or y + pos[1] < 0 or \
           x + pos[0] >= self.tilemap_size[0] or \
           y + pos[1] >= self.tilemap_size[1]:
            result = 0
        
        self.tiles[self.speed + x][self.speed + y] = result
        
    def get(self, pos):
        x = pos[0] + self.speed
        y = pos[1] + self.speed 
        
        if x < 0 or y < 0 or x >=  len(self.tiles) or y >= len(self.tiles[0]):
            return 0
        
        return self.tiles[pos[0] + self.speed][pos[1] + self.speed]