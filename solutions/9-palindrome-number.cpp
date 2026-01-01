class Solution {
public:
    bool isPalindrome(int x) {
        // Negative numbers are not palindromes
        // Numbers ending with 0 (except 0 itself) are not palindromes
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        
        // Reverse half of the number and compare
        int reversedHalf = 0;
        while (x > reversedHalf) {
            reversedHalf = reversedHalf * 10 + x % 10;
            x /= 10;
        }
        
        // For even length: x == reversedHalf (e.g., 1221 -> x=12, rev=12)
        // For odd length: x == reversedHalf/10 (e.g., 12321 -> x=12, rev=123)
        return x == reversedHalf || x == reversedHalf / 10;
    }
};
