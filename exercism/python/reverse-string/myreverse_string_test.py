import unittest

from reverse_string import *


class ReverseStringTests(unittest.TestCase):
  def test_empty_string(self):
    self.assertEqual(reverse(), '')

  def test_normal_string(self):
    self.assertEqual(reverse('Hello world'), 'dlrow olleH')

  def test_space_separate_string(self):
    self.assertEqual(reverse("Nice to see you"), 'uoy ees ot eciN')

  def test_punctuated_string(self):
    self.assertEqual(reverse('I don\'t care!'), '!erac t\'nod I')




if __name__ == '__main__':
  unittest.main()



'''
tests:

1. test input string
2. test space-separate string 
3. test normal string 

'''