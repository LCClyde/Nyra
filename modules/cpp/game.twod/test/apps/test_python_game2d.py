#!/usr/bin/env python3
import unittest
import nyra.game2d as nyra

class TestGame2D(unittest.TestCase):
    def test_actor(self):
        a = nyra.Actor2D();
        a.transform.position = (2, 4)
        self.assertEqual(a.transform.position, (2, 4))
        
    def test_pointer(self):
        a = nyra.Actor2D()
        self.assertEqual(a.nyra_pointer(), int(a.this))

if __name__ == '__main__':
    unittest.main()
