#!/usr/bin/env python3
import unittest

class TestCore(unittest.TestCase):

    # There is not really anything to test here. Just make sure
    # we can import the module
    def test_import(self):
        import nyra.core

if __name__ == '__main__':
    unittest.main()
