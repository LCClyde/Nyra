import nyra.game2d as nyra

class CharacterGrid:
    def __init__(self, speed):
        self.tiles = []
        self.actors = []
        self.tilemap = nyra.map.get_actor('tilemap')
        size = self.tilemap.size
        tile_size = self.tilemap.tile_size
        self.tilemap_size = nyra.Vector2D(size.x / tile_size.x, size.y / tile_size.y)
        
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
                value = (self.get_valid(nyra.Vector2D(x, y)) * 10000 +
                         (self.get_valid(nyra.Vector2D(x, y - 1)) ^ 1) * 1000 +
                         (self.get_valid(nyra.Vector2D(x + 1, y)) ^ 1) * 100 +
                         (self.get_valid(nyra.Vector2D(x, y + 1)) ^ 1) * 10 +
                         (self.get_valid(nyra.Vector2D(x - 1, y)) ^ 1))
                if value > 10000:
                    pos = self.tilemap.tile_to_position(nyra.Vector2D(position.x + x, position.y + y))
                    self.actors.append(nyra.map.spawn('edge_' + str(value) + '.json', position=pos))

    def set(self, x,  y, pos):
        result = 1
        if x + pos.x < 0 or y + pos.y < 0 or \
           x + pos.x >= self.tilemap_size.x or \
           y + pos.y >= self.tilemap_size.y:
            result = None

        if result is not None:
            result = self.tilemap.get_path(pos, nyra.Vector2D(pos.x + x, pos.y + y))
            if result.distance == 0 or result.distance > self.speed:
                result = None
        
        self.tiles[self.speed + x][self.speed + y] = result
        
    def get(self, pos):
        x = pos.x + self.speed
        y = pos.y + self.speed 
        
        if x < 0 or y < 0 or x >=  len(self.tiles) or y >= len(self.tiles[0]):
            return None
        
        return self.tiles[int(pos.x + self.speed)][int(pos.y + self.speed)]
    
    def get_valid(self, pos):
        if self.get(pos) is not None:
            return 1
        return 0