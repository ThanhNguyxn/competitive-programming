from collections import Counter

class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        # Two strings are anagrams if they have the same characters with the same frequencies.
        # Counter creates a hash map of character counts.
        return Counter(s) == Counter(t)
