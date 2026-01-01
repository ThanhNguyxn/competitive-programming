from collections import Counter

class Solution:
    def frequencySort(self, s: str) -> str:
        # 1. Count the frequency of each character: O(N)
        # Counter produces a dictionary-like object: {'a': 3, 'b': 1, ...}
        counts = Counter(s)
        
        # 2. Sort the characters by frequency in descending order: O(K log K) where K is unique chars
        # most_common() returns a list of (char, count) tuples sorted by count desc
        sorted_chars = counts.most_common()
        
        # 3. Build the result string: O(N)
        # Multiply character by its count and join them
        return "".join(char * freq for char, freq in sorted_chars)
