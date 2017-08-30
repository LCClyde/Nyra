#!/usr/bin/env python3
import unittest
import nyra.math as nyra

class TestMath(unittest.TestCase):
    def test_vector(self):
        v = nyra.Vector2F();
        v.x = 10.0
        v.y = 20.0
        self.assertEqual(v.x, 10.0)
        self.assertEqual(v.y, 20.0)
        
    def test_transform(self):
        t = nyra.Transform2D()
        t.position = (1, 2)
        t.rotation = 3
        t.scale = (4, 5)
        t.pivot = (6, 7)
        self.assertEqual(t.position, (1, 2))
        self.assertEqual(t.rotation, 3)
        self.assertEqual(t.scale, (4, 5))
        self.assertEqual(t.pivot, (6, 7))
        

if __name__ == '__main__':
    unittest.main()
