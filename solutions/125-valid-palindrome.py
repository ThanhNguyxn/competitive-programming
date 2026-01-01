import re

class Solution:
    def isPalindrome(self, s: str) -> bool:
        # 1. Filter out non-alphanumeric characters and convert to lowercase
        # regex '[^a-zA-Z0-9]' matches any character that is NOT a letter or number
        cleaned = re.sub(r'[^a-zA-Z0-9]', '', s).lower()
        
        # 2. Check if the string reads the same forwards and backwards
        return cleaned == cleaned[::-1]
