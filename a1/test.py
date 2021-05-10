#!/usr/bin/env python3
# A simple unit test example. Replace by your own tests

import sys
import unittest
from graph import *
from street import *

class MyTest(unittest.TestCase):
    
    def test_add_street(self):
        """Test isupper() function of class string"""
        g = Graph()
        self.assertTrue('FOO'.isupper())
        self.assertFalse('foo'.isupper())
        self.assertFalse('foo'.isupper())
        self.assertFalse('Foo'.isupper())

    def test_failing(self):
        """A test that fails"""
        self.assertEqual(True, False)


if __name__ == '__main__':
    unittest.main()
