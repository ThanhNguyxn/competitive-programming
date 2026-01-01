#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        // Two-pointer approach
        // 'lastNonZeroFoundAt' points to the position where the next non-zero element should go.
        int lastNonZeroFoundAt = 0;
        
        // If the current element is not 0, then we need to append it just in front of the last non 0 element we found. 
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                swap(nums[lastNonZeroFoundAt++], nums[i]);
            }
        }
        
        // After the loop, all non-zero elements are at the beginning of the array in their original order.
        // The remaining elements from 'lastNonZeroFoundAt' to the end are already 0 because of the swap logic 
        // (or effectively 0 because we swapped non-zeros to the front).
    }
};
