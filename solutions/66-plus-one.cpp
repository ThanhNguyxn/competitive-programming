#include <vector>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        
        // Iterate from the last digit backwards
        for (int i = n - 1; i >= 0; --i) {
            if (digits[i] < 9) {
                digits[i]++;
                return digits;
            }
            // If digit is 9, it becomes 0 and we carry over 1 to the next iteration
            digits[i] = 0;
        }
        
        // If we're here, it means all digits were 9 (e.g., 999 -> 000)
        // We need to insert 1 at the beginning (e.g., 1000)
        digits.insert(digits.begin(), 1);
        return digits;
    }
};
