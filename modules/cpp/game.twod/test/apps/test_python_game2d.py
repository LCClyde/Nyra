#!/usr/bin/env python3
import unittest
import nyra.game2d as nyra

class TestGame2D(unittest.TestCase):
    def test_actor(self):
        a = nyra.Actor2D();
        a.position = nyra.Vector2D(2, 4)
        self.assertEqual(a.position, nyra.Vector2D(2, 4))
        self.assertEqual(a.animation, '')

        #TODO: Find a way to test setting animation. It won't work because
        #      it needs the framework to load the animation.
        #self.assert(a.animation = 'foo')

        # TOOD: Find a way to test input.
        #self.assert(a.input.is_down("A"))

    def test_pointer(self):
        a = nyra.Actor2D()
        self.assertEqual(a.nyra_pointer(), int(a.this))

if __name__ == '__main__':
    unittest.main()
